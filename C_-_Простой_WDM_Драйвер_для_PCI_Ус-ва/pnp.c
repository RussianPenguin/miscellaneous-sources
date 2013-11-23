///////////////////////////////////////////////////////////////////////////////
//
//    (C) Copyright 1995 - 1999 OSR Open Systems Resources, Inc.
//    All Rights Reserved
//
//    This sofware is supplied for instructional purposes only.
//
//    OSR Open Systems Resources, Inc. (OSR) expressly disclaims any warranty
//    for this software.  THIS SOFTWARE IS PROVIDED  "AS IS" WITHOUT WARRANTY
//    OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING, WITHOUT LIMITATION,
//    THE IMPLIED WARRANTIES OF MECHANTABILITY OR FITNESS FOR A PARTICULAR
//    PURPOSE.  THE ENTIRE RISK ARISING FROM THE USE OF THIS SOFTWARE REMAINS
//    WITH YOU.  OSR's entire liability and your exclusive remedy shall not
//    exceed the price paid for this material.  In no event shall OSR or its
//    suppliers be liable for any damages whatsoever (including, without
//    limitation, damages for loss of business profit, business interruption,
//    loss of business information, or any other pecuniary loss) arising out
//    of the use or inability to use this software, even if OSR has been
//    advised of the possibility of such damages.  Because some states/
//    jurisdictions do not allow the exclusion or limitation of liability for
//    consequential or incidental damages, the above limitation may not apply
//    to you.
//
//    OSR Open Systems Resources, Inc.
//    105 Route 101A Suite 19
//    Amherst, NH 03031  (603) 595-6500 FAX: (603) 595-6503
//    email bugs to: bugs@osr.com
//
//
//    MODULE:
//
//        PnP.C -- Plug and Play module for OSR WDM Sample PCI Driver
//
//    ABSTRACT:
//
//          This file contains the Plug and Play support routines for
//          the OSR WDM Sample PCI Driver.
//
//    AUTHOR(S):
//
//        OSR Open Systems Resources, Inc.
// 
//    REVISION:   
//
//
///////////////////////////////////////////////////////////////////////////////
//
// The GUID needs to be defined SOMEwhere!
//
#define INITGUID                // define GUID_SIMPLE

#include "osr-pci.h"

//
// Instantiate the GUID for this device
//
#if !defined(FAR)
    #define FAR
#endif // !defined(FAR)

#include <initguid.h>

DEFINE_GUID(OSR_GUID, 0xd0fbbbe6, 0x8631, 0x11d2,0xb1, 0x62, 0x00, 0x60, 0xb0, 0xef, 0xd4, 0xaa);

VOID OsrUnload(PDRIVER_OBJECT DriverObject);

#if DBG
VOID OsrPrintState(POSR_DEVICE_EXT devExt);
#endif

VOID OsrRequestIncrement(POSR_DEVICE_EXT devExt);
VOID OsrRequestDecrement(POSR_DEVICE_EXT devExt);
VOID OsrWaitForStop(POSR_DEVICE_EXT devExt);
VOID OsrWaitForRemove(POSR_DEVICE_EXT devExt);
VOID OsrReturnResources(POSR_DEVICE_EXT devExt);
NTSTATUS OsrStartDevice (IN POSR_DEVICE_EXT devExt,IN PIO_STACK_LOCATION IrpSp);
NTSTATUS OsrCanStopDevice(POSR_DEVICE_EXT devExt, PIRP Irp);
NTSTATUS OsrCanRemoveDevice(POSR_DEVICE_EXT devExt, PIRP Irp);
static NTSTATUS OsrPnpComplete (IN PDEVICE_OBJECT DeviceObject,IN PIRP Irp,IN PVOID Context);

extern PUNICODE_STRING OsrWDMSample_RegistryPath;

static PSTR pnpMinorCodes[] = 
{
    "IRP_MN_START_DEVICE",
    "IRP_MN_QUERY_REMOVE_DEVICE",
    "IRP_MN_REMOVE_DEVICE",
    "IRP_MN_CANCEL_REMOVE_DEVICE",
    "IRP_MN_STOP_DEVICE",
    "IRP_MN_QUERY_STOP_DEVICE",
    "IRP_MN_CANCEL_STOP_DEVICE",
    "IRP_MN_QUERY_DEVICE_RELATIONS",
    "IRP_MN_QUERY_INTERFACE",
    "IRP_MN_QUERY_CAPABILITIES",
    "IRP_MN_QUERY_RESOURCES",
    "IRP_MN_QUERY_RESOURCE_REQUIREMENTS",
    "IRP_MN_QUERY_DEVICE_TEXT",
    "IRP_MN_FILTER_RESOURCE_REQUIREMENTS",
    "***** FUNCTION 0x0e",
    "IRP_MN_READ_CONFIG",
    "IRP_MN_WRITE_CONFIG",
    "IRP_MN_EJECT",
    "IRP_MN_SET_LOCK",
    "IRP_MN_QUERY_ID",
    "IRP_MN_QUERY_PNP_DEVICE_STATE",
    "IRP_MN_QUERY_BUS_INFORMATION",
    "IRP_MN_DEVICE_USAGE_NOTIFICATION",
    "IRP_MN_SURPRISE_REMOVAL"
};


#if DBG
VOID OsrPrintResourceList(PCM_RESOURCE_LIST);
VOID OsrPrintConfig(PPCI_COMMON_CONFIG  configInfo);
#endif

///////////////////////////////////////////////////////////////////////////////
//
//  OsrAddDevice
//
//      We are called at this entry point by the Plug and Play Manager
//      to add a Functional Device Object for a Physical Device Object.
//      Note that we may NOT access the device in this routine, as the
//      Plug and Play Manager has not yet given us any hardware resoruces.
//      We get these hardware resources via the IRP_MJ_PNP IRP with
//      a minor function IRP_MN_START_DEVICE.
//
//
//  INPUTS:
//
//      DriverObj - Address of our DRIVER_OBJECT.
//
//  OUTPUTS:
//
//      None.
//
//  RETURNS:
//
//      None.
//
//  IRQL:
//
//    This routine is called at IRQL_PASSIVE_LEVEL.
//
//  NOTES:
//
///////////////////////////////////////////////////////////////////////////////
NTSTATUS OsrAddDevice(IN PDRIVER_OBJECT DriverObject,
                      IN PDEVICE_OBJECT PhysicalDeviceObject)
{
    POSR_DEVICE_EXT devExt;
    PDEVICE_OBJECT  functionalDeviceObject;
    UNICODE_STRING  devName;
    UNICODE_STRING  linkName;
    NTSTATUS code = STATUS_SUCCESS;     

#if DBG
    DbgPrint("OsrAddDevice: entered\n");
#endif

#if DBG
    DbgPrint("OsrAddDevice: PDO = 0x%0x\n", PhysicalDeviceObject);
#endif

    //
    // Initialize the UNICODE device name.  This will be the "native NT" name
    // for our device.
    //
    RtlInitUnicodeString(&devName, L"\\Device\\OSRPCI");

    //
    // Ask the I/O Manager to create the device object and
    // device extension.  In PnP terms, this is the FUNCTIONAL
    // Device Object (FDO) for the device.
    //
    code = IoCreateDevice(DriverObject,
                          sizeof(OSR_DEVICE_EXT),
                          &devName,
                          FILE_DEVICE_OSR,
                          0,       
                          FALSE,
                          &functionalDeviceObject);

        
    if(!NT_SUCCESS(code))  {
        
#if DBG
        DbgPrint("IoCreateDevice failed.  Status = 0x%0x\n", code);
#endif
        return(STATUS_UNSUCCESSFUL);
    }    

    //
    // Get a pointer to our device extension
    //
    devExt = (POSR_DEVICE_EXT)functionalDeviceObject->DeviceExtension;
    
#if DBG
    DbgPrint("OsrAddDevice: FDO = 0x%0x\n", functionalDeviceObject);
#endif

    //
    // Zero out the device extension.  While not strictly necessary
    // (the documentation says the device extension is zeroed) it's
    // better to be safe.
    //
    RtlZeroMemory(devExt, sizeof(OSR_DEVICE_EXT));

    //
    // Save the device object pointer away for future reference
    //
    devExt->FunctionalDeviceObject = functionalDeviceObject;

    //
    // Save the address of the physical device object away for future reference
    //
    devExt->PhysicalDeviceObject = PhysicalDeviceObject;

    //
    //  Clear the Device Initializing bit since the Device Object was created
    //  outside of DriverEntry.
    //
    functionalDeviceObject->Flags &= ~DO_DEVICE_INITIALIZING;

    //
    // Create a familiar name for this device, so that non-kernel mode
    // programs can open the device.
    //
    // NOTE: WDM Drivers on Win98 MUST create this link in the 
    // \DosDevices directory.  \?? will NOT work.
    //
    RtlInitUnicodeString(&linkName, L"\\DosDevices\\OSRPCI");

    //
    // IoCreateSymbolicLink IS a WDM function...
    //
    code = IoCreateSymbolicLink(&linkName, &devName);
    
    if (!NT_SUCCESS(code))
    {

        DbgPrint("IoCreateSymbolicLink failed.  Status = 0x%x\n", code);

        code = STATUS_SUCCESS;

        //
        // Clean up the mess
        //
        OsrUnload(DriverObject);

        //
        // Indicate load failure to the I/O manager; driver image is deleted...
        //
        return(code);
    }

    //
    // Initialize our IRP queues
    //
    InitializeListHead(&devExt->ReadQueue);
    InitializeListHead(&devExt->WriteQueue);
    
    //
    // Initialize our Spin Locks
    //
    KeInitializeSpinLock(&devExt->ReadQueueLock);
    KeInitializeSpinLock(&devExt->WriteQueueLock);
    
    //
    // Ask the I/O Manager to use describe user read/write buffers using MDLs
    //
    functionalDeviceObject->Flags |= DO_DIRECT_IO;

    //
    // Set up the "Remove Event" and "Stop Event".
    //
    // Note that we can't use an official "Remove Lock" here, because
    // the Remove Lock related calls are not in WDM.
    //
    KeInitializeEvent(&devExt->RemoveEvent, NotificationEvent, FALSE);
    KeInitializeEvent(&devExt->StopEvent, NotificationEvent, TRUE);

    //
    // Init the count of in-progress I/O requests to zero.  We use this
    // to keep track of when we can remove the device.
    //
    devExt->OutstandingIO = 0;

    //
    // Internal device state flags, used for managing PnP state of device
    //
    devExt->Started = FALSE;
    devExt->HoldNewRequests = TRUE;
    devExt->Removed = FALSE;

    //
    // Set initial state
    //
    devExt->State = STATE_NEVER_STARTED;

    //
    // Attach our FDO to the underlying PDO
    //
    devExt->DeviceToSendIrpsTo = 
                     IoAttachDeviceToDeviceStack(functionalDeviceObject,
                                                 PhysicalDeviceObject);

    //
    // If that didn't work...
    //
    if (!devExt->DeviceToSendIrpsTo)
    {

        DbgPrint("IoAttachDeviceToDeviceStack failed to attach to Target Device");

        //
        // Clean up the mess
        //
        OsrUnload(DriverObject);

        //
        // Indicate load failure to the I/O manager; driver image is deleted...
        //
        return(STATUS_UNSUCCESSFUL);
    }

#if DBG
    DbgPrint("OsrAddDevice: done\n");
#endif

    return code;
}

///////////////////////////////////////////////////////////////////////////////
//
//  OsrPnp
//
//    This is the dispatch entry point for IRP_MJ_PNP requests.  The
//    driver processes these requets, based on the current state of
//    the device.
//
//
//  INPUTS:
//
//      DeviceObject - Address of the Functional DEVICE_OBJECT for our device.
//  
//      Irp - Address of the IRP representing the IRP_MJ_PNP request.
//
//  OUTPUTS:
//
//      None.
//
//  RETURNS:
//
//
//  IRQL:
//
//    This routine is called at IRQL_PASSIVE_LEVEL.
//
//  NOTES:
//
//      There are several difficulties implementing Plug and Play.
//      Perhaps the greatest difficulty is deciding precisely how you
//      want your device to work, given the various requests the driver
//      can receive and the states the device can be in.  In our driver,
//      we've decided to implement the following policies:
//
//      1) When a removal of the device is requested, we will reject
//         any new IRPs we receive (completing them with an error
//         status in the dispatch routine).  We will wait until all IRPs
//         that are already present on the device's queue are complete
//         and then allow the remove.
//
//      2) When a stop of the device is requested, we'll queue any
//         newly received IRPs, but not initiate them.  We will wait
//         until any IRPs that are presently ACTIVE in progress on the
//         device complete, and then allow the stop.
//
//      3) When a SUPRISE removal of the device is indicated, we
//         immediately cancel any requests that are queued, reject any
//         newly arriving requests.
//
//      Of course, the second complexity in implementing plug and play
//      is getting the logic in your driver correct, so that it works
//      as you intend. According to our experience, this is easier said
//      than done.
//
///////////////////////////////////////////////////////////////////////////////
NTSTATUS 
OsrPnp(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
    PIO_STACK_LOCATION ioStackLocation;
    NTSTATUS code = STATUS_SUCCESS;
    POSR_DEVICE_EXT devExt;
    KEVENT eventWaitLowerDrivers;
    PDEVICE_OBJECT targetDevice;

#if DBG
    DbgPrint("OsrPnp: called\n");
#endif

    //
    // Get a pointer to our (FUNCTIONAL) device object's device
    // extension.
    //
    devExt = (POSR_DEVICE_EXT)DeviceObject->DeviceExtension;

    //
    // Up the count of in-progress requests
    //
    OsrRequestIncrement(devExt);

    ioStackLocation = IoGetCurrentIrpStackLocation(Irp);

    KeInitializeEvent(&eventWaitLowerDrivers, NotificationEvent, FALSE);

#if DBG
    DbgPrint("OsrPnp: Current state: ");
    OsrPrintState(devExt);

    DbgPrint("OsrPnp: *** PNP Minor Function is %s\n", 
                        pnpMinorCodes[ioStackLocation->MinorFunction]);
#endif

    switch( devExt->State + ioStackLocation->MinorFunction ) {


        //
        // STATE:   STOPPED or NEVER_STARTED
        // IRP_MN:  _START_DEVICE
        //
        // We're here if we've received an AddDevice() call, but we
        // do not have a set of hardware resources from the PnP Manager.
        //
        // The PnP Manager is now giving us a set of resources, and 
        // asking us to start the device.
        //
        // In this case, we pass the IRP all the way down.  When it's
        // done (and our completion routine is called) we can then
        // read the list of device resources pointed to in the IRP
        // Stack Location.
        //
        case STATE_STOPPED + IRP_MN_START_DEVICE:
        case STATE_NEVER_STARTED + IRP_MN_START_DEVICE:

#if DBG
            DbgPrint("OsrPnp: PROCESSING START_DEVICE\n");
#endif
            //
            // The BUS DRIVER handles this IRP before we do
            //
            IoCopyCurrentIrpStackLocationToNext(Irp);

            //
            // Call OsrPnpComplete() when this IRP is done...
            //
            IoSetCompletionRoutine(Irp,
                                  OsrPnpComplete,
                                  &eventWaitLowerDrivers,
                                  TRUE,
                                  TRUE,
                                  TRUE);

            //
            // Send the IRP to the bus driver.  Let's see what HE
            // thinks.
            //
            code = IoCallDriver(devExt->DeviceToSendIrpsTo, Irp);

            if (STATUS_PENDING == code) {

                KeWaitForSingleObject(&eventWaitLowerDrivers,
                                   Executive,
                                   KernelMode,
                                   FALSE,
                                   NULL);

                code = Irp->IoStatus.Status;
            }

            //
            // Can the bus driver do the start?
            //
            if (NT_SUCCESS (code)) {

                //
                // Yup.  Go initialize the device.  The CmResourceLists
                // are pointed to by the IoStackLocation.
                //
                code = OsrStartDevice(devExt, ioStackLocation);

                //
                // If the our StartDevice function succeeded, the
                // device is now "officially" started!
                //
                if(NT_SUCCESS(code)) {

                    devExt->State = STATE_STARTED;

                }

            } else {

                //
                // The bus driver has declined to start the device.
                // Oh well...
                //
#if DBG
                DbgPrint("OsrPnp: IoCallDriver() for START fails! 0x%0x \n", code);
#endif

            }

            //
            // We must now complete the IRP, since we stopped it in the
            // completetion routine with MORE_PROCESSING_REQUIRED.
            //
            Irp->IoStatus.Status = code;

            Irp->IoStatus.Information = 0;

            IoCompleteRequest(Irp, IO_NO_INCREMENT);
            
            break;



        //
        // STATE:   STARTED
        // IRP_MN:  _QUERY_REMOVE
        //
        // We're here because we're running, and the PnP Manager wants
        // to "nicely" remove our device.  This is the orderly way
        // PnP Manager handles device disconnections (as opposed to
        // doing a SURPRISE_REMOVAL).
        //
        // What we do here is (a) change the state of the device such
        // that newly arriving requests will be rejected, (b) wait for
        // all requests to complete on the device, and (c) pass the
        // request on down.
        //
        case STATE_STARTED + IRP_MN_QUERY_REMOVE_DEVICE:

#if DBG
            DbgPrint("OsrPnp: PROCESSING QUERY_REMOVE_DEVICE\n");
#endif
            //
            // WE process this request FIRST
            //
 
            //
            // See if we're OK with removing the device at this point.
            // We do NOT actually RETURN the resources here... we
            // just affirm or deny that we're OK with returning them.
            //
            code = OsrCanRemoveDevice(devExt, Irp);
            
            //
            // Replace status code that's in the IRP to indicate our
            // opinion about stopping the device.  If we're
            // OK with returning the resources, this will be
            // STATUS_SUCCESS.
            //
            Irp->IoStatus.Status = code;

            if(!NT_SUCCESS(code)) {

                //
                // NOPE.  Can't remove the device because, for some
                // reason (perhaps because we can't return our
                // resources).  Too bad. Tell the PnP Manager that
                // stopping right now is not an option for us.
                //
                // NOTE: NO NEED to pass IRP down if WE can't stop
                // it doesn't matter if the Bus Driver can.
                //
                IoCompleteRequest(Irp, IO_NO_INCREMENT);
                        
                
            } else {                    

#if DBG
                DbgPrint("OsrPnp: Waiting for pending requests to complete. (%d. remain)\n", devExt->OutstandingIO);
#endif

                //
                // Set new state -- This state results in any new
                // requests received at our dispatch entry points
                // being REJECTED... any request still on the queues
                // are allowed to complete, however.
                //
                devExt->State = STATE_REMOVE_PENDING;

                //
                // Decrement our reference on the device here, and then
                // wait until there are no requests active or on the
                // device's queues.
                //
                OsrRequestDecrement(devExt);

                OsrWaitForRemove(devExt);
                
                //
                // OK.  No further requests remain.  Let the bus driver
                // know.

                //
                // DECREMENTED REQUEST COUNT above.  Return immediately
                // below.
                //
#if DBG
                DbgPrint("OsrPnp: Leaving With state: ");
                OsrPrintState(devExt);
#endif
                //
                // Pass this request on down to the bus driver
                //
                IoSkipCurrentIrpStackLocation(Irp);

                return(IoCallDriver(devExt->DeviceToSendIrpsTo, Irp));

            }
            break;

        //
        // STATE:   REMOVE_PENDING
        // IRP_MN:  _REMOVE_DEVICE
        //
        // We're here because we've previously received notification
        // of the intention to remove the device in an orderly way.
        // We return our resources here, and then tear down our device
        // object.  Note that there can be no requests pending at this
        // point, because we finished them all during QUERY_REMOVE
        // processing (before entering RemovePending state)
        //
        case STATE_REMOVE_PENDING + IRP_MN_REMOVE_DEVICE:

            //
            // All queued and active IRPs are complete at this point.
            //

            //
            // Return any resources we're using.
            //
            OsrReturnResources(devExt);

            //
            // Fall through...
            //

        //
        // STATE:   SURPRISE_REMOVED
        // IRP_MN:  _REMOVE_DEVICE
        //
        // We're here because we've previously received notification
        // of a "surprise" removal.  At this point, we just tear down
        // our device object
        //
        case STATE_SURPRISE_REMOVED + IRP_MN_REMOVE_DEVICE:

            //
            // Removing the device at this point is NOT optional.
            //
            #if DBG
            DbgPrint("OsrPnp: REMOVE_DEVICE\n");
            #endif

            //
            // Device has been removed
            //
            devExt->State = STATE_REMOVED;

            //
            // Decrement our reference on the device here, and then
            // wait until we can remove the device.  Because we would
            // have gotten a prior warning of this removal (via an
            // IRP_MN_SUPRISE_REMOVAL or an IRP_MN_QUERY_REMOVE) and
            // at that time transitioned state appropriately, there
            // should be no requests outstanding here.
            //
            OsrRequestDecrement(devExt);
        
#if DBG
            DbgPrint("OsrPnp: Waiting for pending requests to complete. %d. remain\n", devExt->OutstandingIO);
#endif
            OsrWaitForRemove(devExt);
            
            //
            // WE process this request first
            //

            //
            // Detach from the PDO 
            //
            IoDetachDevice(devExt->DeviceToSendIrpsTo);

            targetDevice = devExt->DeviceToSendIrpsTo;

#if DBG
            devExt->DeviceToSendIrpsTo = NULL;

            devExt = NULL;
#endif
            //
            // Return our device object
            //
            IoDeleteDevice(devExt->FunctionalDeviceObject);

            //
            // Indidcate that we've successfully processed the IRP
            //
            Irp->IoStatus.Status = STATUS_SUCCESS;

            //
            // Pass this request on down to the bus driver
            //
            IoSkipCurrentIrpStackLocation(Irp);

            code = IoCallDriver(targetDevice, Irp);
            
            ASSERT(code != STATUS_PENDING);

            //
            // IMPORTANT: We decremented our I/O In Progress count
            // above... We don't want to decrement it again, so we
            // return right here.
            //
#if DBG
            DbgPrint("OsrPnp: Leaving with state: STATE_REMOVE");
#endif
            return(code);

            break;

        //
        // STATE:   STARTED
        // IRP_MN:  _SURPRISE_REMOVAL
        //
        // We're here when the device is running, and a device is
        // forcibly removed.  PnP Manager will send us a remove device
        // IRP when we're supposed to actually return our resources
        // and the like.
        //
        // Note that this is a "best effort" activity.  It is quite
        // possible, due to timing issues etc, that we'll crash the
        // system because the device is gone.  While we'll TRY not
        // to do this, it is within the rules.
        //
        // THIS IRP IS NOT SENT ON Win9x.
        //
        case STATE_STARTED + IRP_MN_SURPRISE_REMOVAL:

            devExt->State = STATE_SURPRISE_REMOVED;

            //
            // We handle this request before the bus driver
            //

            //
            // Cancel any pending requests... make sure
            // the active requests get stopped within a second (with
            // no hardware access, as a result of setting the state
            // above).
            //
            OsrClearQueues(devExt);

            //
            // We're happy... sort of.  Note that it's not "legal"
            // to fail this request.  Afterall, what woudl that MEAN?
            //
            Irp->IoStatus.Status = STATUS_SUCCESS;

            //
            // Pass this request on down to the bus driver
            //
            IoSkipCurrentIrpStackLocation(Irp);

            code = IoCallDriver(devExt->DeviceToSendIrpsTo, Irp);

            break;

        //
        // STATE:   STARTED
        // IRP_MN:  _REMOVE_DEVICE
        //
        // We're here when the device is running, and a device is
        // forcibly removed.
        //
        // Note that like getting a SUPRISE_REMOVAL IRP on NT trying
        // to handle a removal directly from started state is a "best
        // effort" type of activity.  We'll do what we can but it's
        // possible, due to timing issues etc, that we'll crash the
        // system because the device is gone.  While we'll TRY not
        // to do this, it could be unavoidable.  Oh well.
        //
        // ON NT, we'd get an IRP_MN_SURPRISE_REMOVAL instead of this
        // IRP in this state.  We get this only on Win9x systems.
        //
        case STATE_STARTED + IRP_MN_REMOVE_DEVICE:

#if DBG
            DbgPrint("OsrPnp: REMOVE_DEVICE\n");
#endif
            devExt->State = STATE_REMOVED;

            //
            // We handle this request before the bus driver
            // Note that this is another one of those requests we're
            // not "allowed" to fail.
            //

            //
            // Cancel any pending requests... make sure
            // the active requests get stopped within a second (with
            // no hardware access, as a result of setting the state
            // above).
            //
            OsrClearQueues(devExt);

            //
            // Removing the device at this point is NOT optional.
            //

            //
            // Detach from the PDO 
            //
            IoDetachDevice(devExt->DeviceToSendIrpsTo);

            targetDevice = devExt->DeviceToSendIrpsTo;

#if DBG
            devExt->DeviceToSendIrpsTo = NULL;

            devExt = NULL;
#endif

            //
            // Decrement our reference on the device here, and then
            // wait until we can remove the device.
            //
            OsrRequestDecrement(devExt);
        
#if DBG
            DbgPrint("OsrPnp: Waiting for pending requests to complete. %d. remain\n", devExt->OutstandingIO);
#endif

            OsrWaitForRemove(devExt);
            
            //
            // OK!  Now we can return our device object
            //
            IoDeleteDevice(devExt->FunctionalDeviceObject);

            //
            // Tell the underlying driver we're cool
            //
            Irp->IoStatus.Status = STATUS_SUCCESS;

            //
            // Pass this request on down to the bus driver
            //
            IoSkipCurrentIrpStackLocation(Irp);

            code = IoCallDriver(targetDevice, Irp);
            
            ASSERT(code != STATUS_PENDING);

            //
            // IMPORTANT: We decremented our I/O In Progress count
            // above... We don't want to decrement it again, so we
            // return right here.
            //
#if DBG
            DbgPrint("OsrPnp: Leaving with state: STATE_REMOVED");
#endif
            return(code);

            break;

        //
        // STATE:   STARTED
        // IRP_MN:  _QUERY_STOP_DEVICE
        //
        // We're here if we're running and the PnP Manager sends us
        // a QUERY_STOP_DEVICE request.  He'll do this if he wants to
        // rebalance resources, to see if we're willing to give up the
        // hardware resources that were allocated for us when we got
        // our IRP_MN_START_DEVICE.
        //
        // To proess this QUERY_STOP, we check to see if the stop is
        // acceptable to us (in this driver it always is), and then
        // we just transition the device to STOP_PENDING state.  In
        // this state, new requests that arrive are queued.  When a
        // currently in-progress request is completed, a new request
        // is NOT started.  Thus, ON OUR DEVICE, we sort of hope that
        // between the QUERY_STOP IRP arrive and actual STOP IRP arriving
        // that any in-progress I/O will complete of its own accord.
        // We like this scheme, particularly because at least on NT
        // during startup the device seems to get lots of QUERY_STOP
        // IRPs, that are just followed by CANCEL_STOP.  Thus, we think
        // it would be unfortunate to do anything radical with the
        // outstanding requests (like cancel them) when we receive a
        // QUERY_STOP.
        //
        case STATE_STARTED + IRP_MN_QUERY_STOP_DEVICE:

#if DBG
            DbgPrint("OsrPnp: PROCESSING QUERY_STOP_DEVICE\n");
#endif
            //
            // WE process this request before the BUS DRIVER
            //

            //
            // See if we're OK with stopping the device at this point.
            // We do NOT actually RETURN the resources here... we
            // just affirm or deny that we're OK with returning them.
            //
            code = OsrCanStopDevice(devExt, Irp);
            
            //
            // Replace status code that's in the IRP to indicate our
            // opinion about stopping the device.  If we're
            // OK with returning the resources, this will be
            // STATUS_SUCCESS.
            //
            Irp->IoStatus.Status = code;

            if(!NT_SUCCESS(code)) {

                //
                // NOPE.  Can't stop the device because, for some
                // reason (perhaps because we can't return our
                // resources).  Too bad. Tell the PnP Manager that
                // stopping right now is not an option for us.
                //
                // NOTE: NO NEED to pass IRP down if WE can't stop
                // it doesn't matter if the Bus Driver can.
                //
                IoCompleteRequest(Irp, IO_NO_INCREMENT);
                        
                
            } else {                    

                //
                // We CAN stop our device and return the resources.
                // Pass the IRP down to see if the bus driver is
                // equally ammenable to the request.
                //
#if DBG
                DbgPrint("OsrPnp: Agreeing to stop device.\n");
#endif

                //
                // Set new state. This state results in no new
                // requests being started on the device, but incoming
                // requests are still allowed and queued.
                //
                devExt->State = STATE_STOP_PENDING;

                //
                // Pass this request on down to the bus driver
                //
                IoSkipCurrentIrpStackLocation(Irp);

                code = IoCallDriver(devExt->DeviceToSendIrpsTo, Irp);

            }
            break;

        //
        // STATE:   STOP_PENDING
        // IRP_MN:  _STOP_DEVICE
        //
        // We're in this state because we previously received a 
        // QUERY_STOP_DEVICE, that we agreed that we could grant.
        // Thus, we're waiting to receive a STOP_DEVICE request.
        // To process this request, we first wait for any in-progress
        // requests to complete (note that no NEW requests have been
        // started since the transition to STOP_PENDING state as a
        // result of receiving the QUERY_STOP IRP).  After all in-
        // progress requests are complete, we return our resources
        // and wait for further instructions from the PnP Manager (
        // which better include a START_DEVICE someplace down the line!).
        // 
        // While in this state, any IRPs we receive will be queued
        // for processing after we get the START_DEVICE.
        //
        case STATE_STOP_PENDING + IRP_MN_STOP_DEVICE:

#if DBG
            DbgPrint("OsrPnp: PROCESSING STOP_DEVICE\n");
#endif
            //
            // Assume success
            //
            devExt->State = STATE_STOPPED;
        
#if DBG
            DbgPrint("OsrPnp: Waiting for in-progress requests to complete\n");
#endif

            //
            // We process this request before passing it to the bus
            // driver
            //

            //
            // Wait until all active requests on the device have
            // completed...
            //
            OsrWaitForStop(devExt);
            
            //
            // There are NO ACTIVE IRPs on the device at this point.
            //

            //
            // Return any resources we're using.
            //
            OsrReturnResources(devExt);

            //
            // NOTE: We DO NOT delete our device object here.  This is
            // one difference between a _STOP_DEVICE and _REMOVE_DEVICE.
            //
#if DBG
            DbgPrint("OsrPnp: Passing along request\n");
#endif

            //
            // Pass this request on down to the bus driver
            //
            IoSkipCurrentIrpStackLocation(Irp);
            
            //
            // We're cool with the stop...
            //
            Irp->IoStatus.Status = STATUS_SUCCESS;

            code = IoCallDriver(devExt->DeviceToSendIrpsTo, Irp);
            break;        


        //
        // STATE:   STOP_PENDING
        // IRP_MN:  _CANCEL_STOP_DEVICE
        //
        // We're here because we've already received a QUERY_STOP,
        // that we've agreed to.  We've completed any pending I/O
        // requests.  Now we've received a CANCEL_STOP_DEVICE
        // IRP, that sort of says "never mind" about that stop.
        //
        // We restart our queues and return to Started state.
        //
        case STATE_STOP_PENDING + IRP_MN_CANCEL_STOP_DEVICE:
#if DBG
            DbgPrint("OsrPnp: PROCESSING CANCEL_STOP\n");
#endif

            //
            // fall through...
            //

        //
        // STATE:   REMOVE_PENDING
        // IRP_MN:  _CANCEL_REMOVE_DEVICE
        //
        // We're here because we've already received a QUERY_REMOVE,
        // that we've agreed to.  We've completed any pending I/O
        // requests.  Now we've received a CANCEL_REMOVE_DEVICE
        // IRP, that sort of says "never mind" about that remove.
        //
        // We restart our queues and return to Started state.
        //
        case STATE_REMOVE_PENDING + IRP_MN_CANCEL_REMOVE_DEVICE:

#if DBG
            if( devExt->State == STATE_REMOVE_PENDING) {
            
                DbgPrint("OsrPnp: PROCESSING CANCEL_REMOVE\n");
       
            }
#endif

            //
            // The Underlying BUS DRIVER must handle these IRPs
            // before we do...
            //

            //
            // We need to wait for the underlying bus driver to
            // get restarted, before we can continue processing.
            //
            IoCopyCurrentIrpStackLocationToNext(Irp);

            IoSetCompletionRoutine(Irp,
                                   OsrPnpComplete,
                                   &eventWaitLowerDrivers,
                                   TRUE,
                                   TRUE,
                                   TRUE);

            code = IoCallDriver(devExt->DeviceToSendIrpsTo, Irp);

            if(code == STATUS_PENDING) {

                KeWaitForSingleObject(&eventWaitLowerDrivers,
                                      Executive,
                                      KernelMode,
                                      FALSE,
                                      NULL);
            }


            //
            // We're now in STARTED state
            //
            devExt->State = STATE_STARTED;

            //
            // Go see if there's a request that we can start now
            //
            OsrProcessQueuedRequests(devExt);

            code = STATUS_SUCCESS;

            Irp->IoStatus.Status = code;

            Irp->IoStatus.Information = 0;

            IoCompleteRequest(Irp, IO_NO_INCREMENT);

            break;

        default:

            //
            // DEFAULT CASE
            // Just pass the request to the lower driver
            //
#if DBG
            DbgPrint("OsrPnp: Default case: Just pass it along...\n");
#endif
            IoSkipCurrentIrpStackLocation (Irp);

            code = IoCallDriver (devExt->DeviceToSendIrpsTo, Irp);

            break;
    }

    //
    // Adjust in-progress request count
    //
    OsrRequestDecrement(devExt);

#if DBG
    DbgPrint("OsrPnp: Leaving with new state ");

    OsrPrintState(devExt);

    DbgPrint("OsrPnp: exit (%d.).\n", devExt->OutstandingIO);
#endif

    //
    // We always finish our work in this function
    //
    ASSERT(code != STATUS_PENDING);

    return(code);
}

//
// OsrPnpComplete
// 
// This is the completion routine for IRP_MJ_PNP requests
//
NTSTATUS
OsrPnpComplete(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp, IN PVOID Context)
{
    PIO_STACK_LOCATION  iostack;
    PKEVENT pEvent = (PKEVENT) Context;
    NTSTATUS status = STATUS_SUCCESS;

    UNREFERENCED_PARAMETER (DeviceObject);

    iostack = IoGetCurrentIrpStackLocation (Irp);

//
// Driver Writers, please note:
//
//  The following code is only necessary IF (a) WE have a completion
//  routine, AND (b) WE return STATUS_PENDING from our dispatch entry
//  point after re-claiming the IRP.  Since neither of these things
//  is true... this code does not belong here.
//
//    if (Irp->PendingReturned) {
//
//        IoMarkIrpPending( Irp );
//
//    }

    switch (iostack->MajorFunction) {

        case IRP_MJ_PNP:

            KeSetEvent(pEvent, 0, FALSE);

            //
            // Take the IRP back so that we can continue using it during
            // the IRP_MN_START_DEVICE dispatch routine.
            // NB: we will have to call IoCompleteRequest
            //
            return STATUS_MORE_PROCESSING_REQUIRED;

            break;

        case IRP_MJ_POWER:
#if DBG
            DbgPrint("OsrPnpComplete: NOT MJ_POWER support in this driver!\n");
#endif

            break;

        default:
#if DBG
            DbgPrint("OsrPnpComplete: NOT MJ_PNP or MJ_POWER IRP??\n");
#endif

            break;
    }

    return status;
}

///////////////////////////////////////////////////////////////////////////////
//
// OsrStartDevice
//
//      This function is called from the DispatchPnp Entry Point to
//      actually start the hardware.
//
//  INPUTS:
//
//      DevExt  - Address of our device extension.
//      IoStackLocation -- Pointer to I/O Stack Location containing
//                  configuration information
//
//  OUTPUTS:
//
//      None.
//
//  RETURNS:
//
//    STATUS_SUCCESS;
//
//  IRQL:
//
//
//  NOTES:
//
//
///////////////////////////////////////////////////////////////////////////////
NTSTATUS
OsrStartDevice(IN POSR_DEVICE_EXT DevExt,
               IN PIO_STACK_LOCATION IoStackLocation)
{
    NTSTATUS code = STATUS_SUCCESS;
    ULONG index;
    PDEVICE_DESCRIPTION deviceDescription;
    PCM_RESOURCE_LIST pResourceList, pResourceListTranslated;
    PCM_PARTIAL_RESOURCE_LIST prl, prlTranslated;
    PCM_PARTIAL_RESOURCE_DESCRIPTOR prd, prdTranslated;
    PCM_FULL_RESOURCE_DESCRIPTOR frd, frdTranslated;

    pResourceList = IoStackLocation->Parameters.StartDevice.AllocatedResources;
    pResourceListTranslated = IoStackLocation->Parameters.StartDevice.AllocatedResourcesTranslated;

    frd = &pResourceList->List[0];
    frdTranslated = &pResourceListTranslated->List[0];

    prl = &frd->PartialResourceList;
    prlTranslated = &frdTranslated->PartialResourceList;

#if DBG
    OsrPrintResourceList(pResourceList);
    OsrPrintResourceList(pResourceListTranslated);
#endif

    //
    // Ensure the base address starts as NULL
    //
    DevExt->AmccBaseRegisterAddress = NULL;

    //
    // Walk through the partial resource descriptors to find the
    // hardware resources that have been allocated to us
    //
    // We need one range of port addresses (0x40 bytes long) and
    // and interrupt resource.
    //
    for (index = 0,
         prd = &prl->PartialDescriptors[index],
         prdTranslated = &prlTranslated->PartialDescriptors[index];
         index < prl->Count && NT_SUCCESS(code);
         index++, prd++, prdTranslated++) {

        switch (prd->Type) {

            case CmResourceTypePort:

                //
                // Newer AMCC Demo Boards have more than just one BAR
                // programmed in the PCI configuration ROM.  We want
                // the FIRST BAR, which is the base address of the
                // device itself.  So, we ignore any ports reported to
                // us after the first one.
                //
                if (DevExt->AmccBaseRegisterAddress) {
#if DBG
                    DbgPrint("Ignoring additional port resource ...\n");

                    if(prdTranslated->Type == CmResourceTypePort) {
                        DbgPrint("(Translated port 0x%0x)\n",
                         prdTranslated->u.Port.Start.LowPart);


                    } else {
                        DbgPrint("(Translated memory 0x%0x)\n",
                         prdTranslated->u.Memory.Start);
                    }

#endif
                    break;                    
                }

#if DBG
                DbgPrint("Configuring port resource ...\n");
#endif
                //
                // Should only get ONE port resources
                //
                ASSERT(DevExt->AmccBaseRegisterAddress == NULL);

                //
                // Our port space on this card is 0x40 bytes longs
                //
                ASSERT(prd->u.Memory.Length == 0x40);

                //
                // Do the device ports appear in port I/O space or
                // in memory space on this machine.
                //
                if(prdTranslated->Type == CmResourceTypePort) {

                    //
                    // The port is in port space on this machine.  Just
                    // store away the address
                    //
                    DevExt->MappedPorts = FALSE;

                    DevExt->AmccBaseRegisterAddress =
                        (PVOID) prdTranslated->u.Port.Start.LowPart;

#if DBG
                    DbgPrint("Translated resource is a port at 0x%0x\n",
                                DevExt->AmccBaseRegisterAddress);
#endif

                } else {


                    ASSERT(prdTranslated->Type == CmResourceTypeMemory);

                    //
                    // The port is in memory space on this machine.  We
                    // need to map some virtual addresses over the physical
                    // address provided us, and remember to do an UNMAP
                    // if/when we have to return the resources.
                    //
                    DevExt->MappedPorts = TRUE;

                    DevExt->AmccBaseRegisterAddress =
                        MmMapIoSpace(prdTranslated->u.Memory.Start,
                                      prdTranslated->u.Memory.Length,
                                      MmNonCached);


#if DBG
                    DbgPrint("Translated resource is MEMORY at 0x%0x\n",
                                DevExt->AmccBaseRegisterAddress);
#endif

                }

                break;


            case CmResourceTypeInterrupt:

#if DBG
                DbgPrint("Configuring Interrupt resource ...\n");
#endif
                //
                // Be sure we get only ONE interrupt resource
                //
                ASSERT(DevExt->InterruptLevel == 0);

                //
                // Again, assume that the translated and raw resources
                // are in the same order and number
                //
                ASSERT(CmResourceTypeInterrupt == prdTranslated->Type);

                DevExt->InterruptLevel       = (UCHAR)prdTranslated->u.Interrupt.Level;
                DevExt->InterruptVector      = prdTranslated->u.Interrupt.Vector;
                DevExt->InterruptAffinity    = prdTranslated->u.Interrupt.Affinity;
                
                if (prdTranslated->Flags & CM_RESOURCE_INTERRUPT_LATCHED) {
                
                    DevExt->InterruptMode = Latched;

                } else {
                
                    DevExt->InterruptMode = LevelSensitive;
                }

                //
                // Because this is a PCI device, we KNOW it must be
                // a LevelSensitive Interrupt
                //
                ASSERT(DevExt->InterruptMode == LevelSensitive);

#if DBG
                DbgPrint("Interrupt level: 0x%0x, Vector: 0x%0x, Affinity: 0x%0x\n",
                            DevExt->InterruptLevel,
                            DevExt->InterruptVector,
                            DevExt->InterruptAffinity);
#endif
                break;

            default:
#if DBG
                DbgPrint("OSRPCI: Unhandled Resource -- CmResourceType received 0x%x\n", prd->Type);
#endif
                break;
        }
    }

    //
    // We NEED the interrupt info AND one port
    //
    ASSERT(DevExt->InterruptLevel && DevExt->AmccBaseRegisterAddress);

    //
    // Register our DPCforISR routine.  This is the routine which will
    // be used to complete our interrupt processing.
    //
    IoInitializeDpcRequest(DevExt->FunctionalDeviceObject, OsrDpcForIsr);

    //
    // Connect to interrupt from the device.  After this call,
    // interrupts from the device will result in calls to our OsrHandleInterrupt
    // function.
    //
    code = IoConnectInterrupt(&DevExt->InterruptObject,
                              OsrHandleInterrupt,
                              DevExt,                   // ISR Context
                              NULL,
                              DevExt->InterruptVector,
                              DevExt->InterruptLevel,
                              DevExt->InterruptLevel,
                              DevExt->InterruptMode,
                              TRUE,
                              DevExt->InterruptAffinity,
                              FALSE);

    if (!NT_SUCCESS(code))  {

#if DBG
        DbgPrint("IoConnectInterrupt failed with error 0x%x", code);
#endif
        //
        // We're outa here 
        //
        return(code);
    }
    
    //
    // Now we reset the adapter card.
    //
    OsrResetAdapter(DevExt->FunctionalDeviceObject, FALSE);

    //
    // Finally, we get our adapter object from the HAL.  When we do this,
    // we describe out device to the HAL, in pretty gory detail.  In
    // return, the HAL gives us a pointer to our adapter object, and
    // tells us the maximum number of mapping registers we can ever
    // hope to get.
    // 
    deviceDescription = ExAllocatePoolWithTag(PagedPool,
                                            sizeof(DEVICE_DESCRIPTION), 
                                            'pRSO');

    //
    // Important: Zero out the entire structure first!
    //
    RtlZeroMemory(deviceDescription, sizeof(DEVICE_DESCRIPTION));

    deviceDescription->Version = DEVICE_DESCRIPTION_VERSION;
    deviceDescription->Master = TRUE;
    deviceDescription->ScatterGather = FALSE;
    deviceDescription->Dma32BitAddresses = TRUE;
    deviceDescription->InterfaceType = PCIBus;

    //
    // Maximum size of transfer that we support on this device.  Choose
    // anything you like, really.
    //
    deviceDescription->MaximumLength = OSR_PCI_MAX_TXFER;

    //
    // Allocate one Adapter for WRITE
    //
    DevExt->WriteAdapter = IoGetDmaAdapter(DevExt->PhysicalDeviceObject,
                                          deviceDescription,
                                          &DevExt->WriteMapRegsGot);

    if(!DevExt->WriteAdapter)  {

#if DBG
        DbgPrint("IoGetDmaAdapter for WRITE FAILED!!\n");    
#endif
        //
        // Clean up the mess
        //
        ExFreePool(deviceDescription);

        //OsrUnload(DriverObj);

        return(STATUS_UNSUCCESSFUL);
    }

#if DBG
    DbgPrint("Max Map Regs for WRITE = %d.\n", DevExt->WriteMapRegsGot);
#endif

    //
    // And then another for READ
    //
    DevExt->ReadAdapter = IoGetDmaAdapter(DevExt->PhysicalDeviceObject,
                                          deviceDescription,
                                          &DevExt->ReadMapRegsGot);

    if(!DevExt->ReadAdapter)  {

#if DBG
        DbgPrint("IoGetDmaAdapter for READ FAILED!!\n");    
#endif
        //
        // Clean up the mess
        //
        ExFreePool(deviceDescription);

        //OsrUnload(DriverObj);

        return(STATUS_UNSUCCESSFUL);
    }

#if DBG
    DbgPrint("Max Map Regs for READ = %d.\n", DevExt->ReadMapRegsGot);
#endif

   //
    // Return the memory allocated from pool during initialization
    //
    ExFreePool(deviceDescription);    

    return STATUS_SUCCESS;
}


///////////////////////////////////////////////////////////////////////////////
//
// OsrCanStopDevice
//
//      This routine determines if the device cab be safely stopped.  In
//      our case we'll assume you can always stop the device.  A device
//      might not be able to be stopped, for example, if it doesn't have
//      a queue for incoming requests or if it was notified that it is
//      in the paging path.
//
//  INPUTS:
//
//      devExt  - Address of our device extension.
//      Irp         - Address of the input IRP.
//
//  OUTPUTS:
//
//      None.
//
//  RETURNS:
//
//    STATUS_SUCCESS;
//
//  IRQL:
//
//
//  NOTES:
//
//
///////////////////////////////////////////////////////////////////////////////
NTSTATUS OsrCanStopDevice(POSR_DEVICE_EXT devExt, PIRP Irp)
{
    UNREFERENCED_PARAMETER(devExt);
    UNREFERENCED_PARAMETER(Irp);

    return STATUS_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
//
// OsrCanRemoveDevice
//
//      This routine determines if the device cab be safely removed.  In our case
//      we'll assume you can always remove the device.  A device might note be able to
//      be removed, for example, if it has opened handles or removing the device would
//      result in the lost of data.
//
//  INPUTS:
//
//      devExt  - Address of our device extension.
//      Irp         - Address of the input IRP.
//
//  OUTPUTS:
//
//      None.
//
//  RETURNS:
//
//    STATUS_SUCCESS;
//
//  IRQL:
//
//
//  NOTES:
//
//
///////////////////////////////////////////////////////////////////////////////
NTSTATUS OsrCanRemoveDevice(POSR_DEVICE_EXT devExt, PIRP Irp)
{
    UNREFERENCED_PARAMETER(devExt);
    UNREFERENCED_PARAMETER(Irp);

    return STATUS_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
//
// OsrReturnResources
//
//      This function is called to return any hardware resources which
//      have been allocated for the device.  In our case, these are
//      the Interrupt Object, and any ports we might have mapped through
//      memory.  Note that we do NOT return our Device Object here.
//
//  INPUTS:
//
//      devExt  - Address of our device extension.
//      Irp         - Address of the input IRP.
//
//  OUTPUTS:
//
//      None.
//
//  RETURNS:
//
//      VOID
//
//  IRQL:
//
//
//  NOTES:
//
//
///////////////////////////////////////////////////////////////////////////////
VOID
OsrReturnResources(POSR_DEVICE_EXT devExt)
{

    //
    // Disconnect from any interrupts
    //
    if (devExt->InterruptObject) {

        //
        // Disconnect from the interrupt
        //
        IoDisconnectInterrupt(devExt->InterruptObject);

        devExt->InterruptObject = NULL;
    }


    //
    // Unmap any ports that were mapped
    //
    if (devExt->MappedPorts) {

        MmUnmapIoSpace(devExt->AmccBaseRegisterAddress, 0x40);

        devExt->MappedPorts = FALSE;
        devExt->AmccBaseRegisterAddress = 0;
        
    }

}


///////////////////////////////////////////////////////////////////////////////
//
// OsrRequestIncrement
// OsrRequestDecrement
//
//      These functions are used to track the number of requests that
//      are presently queued the device indicated by the passed
//      Device Extension.
//
//      This code is based heavily on the PnP Sample Driver in the
//      \General directory of the NTDDK.
//
//  INPUTS:
//
//      devExt  - Address of our device extension.
//
//  OUTPUTS:
//
//      None.
//
//  RETURNS:
//
//    STATUS_SUCCESS;
//
//  IRQL:
//
//
//  NOTES:
//
//
///////////////////////////////////////////////////////////////////////////////
VOID
OsrRequestIncrement(POSR_DEVICE_EXT devExt)
{

    LONG result;
    
    result = InterlockedIncrement(&devExt->OutstandingIO);

    ASSERT(result >= 0);
    
    //
    // Need to clear Remove
    //
    if (result == 1) {

        //
        // The remove event is cleared when the first request is
        // added to the queue.
        //
        KeClearEvent(&devExt->RemoveEvent);
    }

    return;
}

VOID
OsrRequestDecrement(POSR_DEVICE_EXT devExt)
{

    LONG result;
    
    result = InterlockedDecrement(&devExt->OutstandingIO);
    
    ASSERT(result >= 0);

    if (result == 0) {

        //
        // The remove event is set when the queue is totally EMPTY.
        //
        KeSetEvent(&devExt->RemoveEvent, 
                   IO_NO_INCREMENT, 
                   FALSE);
        
    }

}

///////////////////////////////////////////////////////////////////////////////
//
// OsrWaitForStop
//
//      Using the event set by the OsrRequestIncrement() and 
//      OsrRequestDecrement() functions, this function waits until
//      the device can be stopped.
//
//      On our device, STOP implies there are no active requests on
//      the device, even though there are queued requests.
//
//  INPUTS:
//
//      devExt  - Address of our device extension.
//
//  OUTPUTS:
//
//      None.
//
//  RETURNS:
//
//    STATUS_SUCCESS;
//
//  IRQL:
//
//
//  NOTES:
//
//
///////////////////////////////////////////////////////////////////////////////
VOID
OsrWaitForStop(POSR_DEVICE_EXT devExt)
{
    devExt->HoldNewRequests = TRUE;

    ASSERT(devExt->State != STATE_STARTED);

    KeWaitForSingleObject(&devExt->StopEvent,
                           Executive,
                           KernelMode,
                           FALSE,
                           NULL);

}

///////////////////////////////////////////////////////////////////////////////
//
// OsrWaitForRemove
//
//      Using the event set by the OsrRequestIncrement() and 
//      OsrRequestDecrement() functions, this function waits until
//      the device can be removed.
//
//      On our device, REMOVE implies there are no active or queued
//      requests on the device.
//
//  INPUTS:
//
//      devExt  - Address of our device extension.
//
//  OUTPUTS:
//
//      None.
//
//  RETURNS:
//
//    STATUS_SUCCESS;
//
//  IRQL:
//
//
//  NOTES:
//
//
///////////////////////////////////////////////////////////////////////////////
VOID
OsrWaitForRemove(POSR_DEVICE_EXT devExt)
{
#if DBG
    LARGE_INTEGER timeout;
    NTSTATUS status;

    timeout.QuadPart = -5*10*1000*1000;     // 5 seconds
#endif

    devExt->Removed = TRUE;

    ASSERT(devExt->State < STATE_ALL_BELOW_FAIL);

#if DBG

wait_again:

    status = KeWaitForSingleObject(&devExt->RemoveEvent,
                           Executive,
                           KernelMode,
                           FALSE,
                           &timeout);

    if(status == STATUS_TIMEOUT) {
    
        DbgPrint("OsrPci: *** Still Waiting for activity to stop on device??  %d. requests reamin\n", devExt->OutstandingIO);
        goto wait_again;
    }    

    if(status != STATUS_SUCCESS) {

        DbgPrint("OsrPci: *** Wait not ended with success, and not with timeout?? Status = 0x%0x\n", status);
    }

#else

    KeWaitForSingleObject(&devExt->RemoveEvent,
                           Executive,
                           KernelMode,
                           FALSE,
                           NULL);
#endif

}

///////////////////////////////////////////////////////////////////////////////
//
// OsrSystemControl
//
//      This dispatch entry point is used to pass any WMI IRPs that we
//      receive on to the underlying bus driver.
//
//  INPUTS:
//
///     DriverObject - Pointer to driver object.
//      Irp         - Address of the input IRP.
//
//  OUTPUTS:
//
//      None.
//
//  RETURNS:
//
//      VOID
//
//  IRQL:
//
//
//  NOTES:
//
//
///////////////////////////////////////////////////////////////////////////////
NTSTATUS 
OsrSystemControl(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{

    //
    // Since we don't play WMI, pass this request on down to the
    // driver below us...
    //
    IoSkipCurrentIrpStackLocation(Irp);

    return(IoCallDriver(((POSR_DEVICE_EXT)(DeviceObject->DeviceExtension))->DeviceToSendIrpsTo, Irp));

}



#if DBG

VOID
OsrPrintState(POSR_DEVICE_EXT devExt)
{
    if(devExt->State == STATE_REMOVED) {
        DbgPrint("STATE_REMOVED\n");
        return;
    }

    if(devExt->State == STATE_STARTED) {
        DbgPrint("STATE_STARTED\n");
        return;
    }

    if(devExt->State == STATE_REMOVE_PENDING) {
        DbgPrint("STATE_REMOVE_PENDING\n");
        return;
    }

    if(devExt->State == STATE_SURPRISE_REMOVED) {
        DbgPrint("STATE_SURPRISE_REMOVED\n");
        return;
    }


    if(devExt->State == STATE_STOP_PENDING) {
        DbgPrint("STATE_STOP_PENDING\n");
        return;
    }

    if(devExt->State == STATE_STOPPED) {
        DbgPrint("STATE_STOPPED\n");
        return;
    }

    if(devExt->State == STATE_NEVER_STARTED) {
        DbgPrint("STATE_NEVER_STARTED\n");
        return;
    }

    DbgPrint("*********UNKNOWN STATE Value 0x%0x\n", devExt->State);
}

#endif
