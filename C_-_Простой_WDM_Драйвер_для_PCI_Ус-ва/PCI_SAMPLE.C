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
//        PCI_SAMPLE.C
//
//    ABSTRACT:
//
//      This file contains the initial entry point for the OSR Sample
//      WDM PCI Busmaster DMA device driver for the AMCC 5933 chip.
//
//    AUTHOR(S):
//
//        OSR Open Systems Resources, Inc.
// 
//    REVISION:   
//
//
///////////////////////////////////////////////////////////////////////////////

#include "osr-pci.h"        // include <WDM.H> for us

//
// Forward Declarations
//
NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObj, PUNICODE_STRING RegistryPath);
VOID OsrUnload(PDRIVER_OBJECT DriverObject);
static VOID OsrReturnPool(PPCI_COMMON_CONFIG  configInfo, PDEVICE_DESCRIPTION
            deviceDescription,  PCM_RESOURCE_LIST resources);

#if DBG
VOID OsrPrintResourceList(PCM_RESOURCE_LIST);
VOID OsrPrintConfig(PPCI_COMMON_CONFIG  configInfo);
#endif

//
// Globals used by WDM Sample.
//
PUNICODE_STRING OsrWDMSample_RegistryPath = NULL;


//
// The following pragma allows the DriverEntry code to be discarded once
// initialization is completed
//
//#pragma alloc_text(INIT,DriverEntry)

///////////////////////////////////////////////////////////////////////////////
//
//  DriverEntry
//
//      This routine is called by NT when the driver is first loaded.  It is the
//    responsibility of this routine to find it's device and create whatever
//    device objects it needs.
//
//  INPUTS:
//
//      DriverObj - Address of the DRIVER_OBJECT created by NT for this driver.
//
//      RegistryPath - UNICODE_STRING which represents this drivers KEY in the
//                   Registry.  
//
//  OUTPUTS:
//
//      None.
//
//  RETURNS:
//
//      STATUS_SUCCESS. Otherwise an error indicating why the driver could not
//                    Load.
//
//  IRQL:
//
//    This routine is called at IRQL_PASSIVE_LEVEL.
//
//  NOTES:
//
//
///////////////////////////////////////////////////////////////////////////////
NTSTATUS
DriverEntry(PDRIVER_OBJECT DriverObj, PUNICODE_STRING RegistryPath)
{
    
    DbgPrint("\nOSR WDM PCI Sample Driver v1.4 -- Compiled %s %s\n",__DATE__, __TIME__);
    DbgPrint("(c) 1998-1999 OSR Open Systems Resources, Inc.\n\n");

    //
    // Establish dispatch entry points for the functions we support
    //
    DriverObj->MajorFunction[IRP_MJ_CREATE]         =  OsrCreateClose;
    DriverObj->MajorFunction[IRP_MJ_CLOSE]          =  OsrCreateClose;

    DriverObj->MajorFunction[IRP_MJ_READ]           =  OsrRead;
    DriverObj->MajorFunction[IRP_MJ_WRITE]          =  OsrWrite;
    DriverObj->MajorFunction[IRP_MJ_DEVICE_CONTROL] =  OsrDeviceControl;

    //
    // PnP and Power entry points
    //
    DriverObj->MajorFunction[IRP_MJ_PNP]            =  OsrPnp;
//    DriverObj->MajorFunction[IRP_MJ_POWER]          =  OsrPower;

    //
    // WMI entry point
    //
    DriverObj->MajorFunction[IRP_MJ_SYSTEM_CONTROL] =  OsrSystemControl;

    //
    // AddDevice Function
    //
    DriverObj->DriverExtension->AddDevice = OsrAddDevice;

    //
    // Unload function
    //
    DriverObj->DriverUnload = OsrUnload;

    //
    // Save the registry path for later use.
    //
    OsrWDMSample_RegistryPath = RegistryPath;

#if DBG
    DbgPrint("DriverEntry: done\n");
#endif
    
    return(STATUS_SUCCESS);
    
}

///////////////////////////////////////////////////////////////////////////////
//
//  OsrUnload
//
//      This routine is our dynamic unload entry point.  We are called here when
//    the OS wants to unload our driver.  It is our responsibility to release any
//    resources we allocated.
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
//    No doubt we pool leak at this entry point by not properly returning everything.
//
///////////////////////////////////////////////////////////////////////////////
VOID OsrUnload(PDRIVER_OBJECT DriverObject)
{
    POSR_DEVICE_EXT devExt;
    PDEVICE_OBJECT devObj;
    IO_RESOURCE_REQUIREMENTS_LIST reqList;
    NTSTATUS code;
    UNICODE_STRING linkName;
    CM_RESOURCE_LIST returnResources;
    BOOLEAN conflictDetected;
            
#if DBG
    DbgPrint("SAMPLE-PCI: UNLOAD called.\n");
#endif

    //
    // For THIS driver, there will only ever be a single device object.
    // Because of this, we just get it from the DriverObj.  If this were
    // a multiple device driver, we would do this in a while loop...
    //
    devObj = DriverObject->DeviceObject;

    if (!devObj) {

        return;
    }

    devExt= (POSR_DEVICE_EXT)devObj->DeviceExtension;

    RtlInitUnicodeString(&linkName, L"\\DosDevices\\OSRPCI");

    IoDeleteSymbolicLink(&linkName);

    //
    // Reset the adapter card
    //
    OsrResetAdapter(devObj, FALSE);

    if (devExt->InterruptObject) {
        //
        // Disconnect the interrupt.
        //
        IoDisconnectInterrupt(devExt->InterruptObject);
    }

    //
    // Unmap any ports that were mapped
    //
    if (devExt->MappedPorts) {

        MmUnmapIoSpace(devExt->AmccBaseRegisterAddress, 0x40);

        devExt->MappedPorts = FALSE;
        devExt->AmccBaseRegisterAddress = 0;
        
    }

    //
    // Delete the device object
    //
    IoDeleteDevice(devObj);
}

#if DBG
///////////////////////////////////////////////////////////////////////////////
//
//  OsrPrintConfig
//
//    This routine is called to print out the PCI configuration information for
//    our device. This output is pretty "chatty" but it can be extremely
//    useful during initial debugging. And, hey, it's only output when
//    we get a START_DEVICE.
//
//  INPUTS:
//
//      configInfo - Address of the PCI_COMMON_CONFIG information for our device.
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
//    We only use this for debugging purposes.
//
///////////////////////////////////////////////////////////////////////////////
VOID OsrPrintConfig(PPCI_COMMON_CONFIG  configInfo)
{
    ULONG index;

    DbgPrint("Displaying PCI Configuration Information\n");
    DbgPrint("\tRevisionID is 0x%x\n", (int)configInfo->RevisionID);
    DbgPrint("\tProgIf is 0x%x\n", (int) configInfo->ProgIf);
    DbgPrint("\tSubClass is 0x%x\n", (int) configInfo->SubClass);
    DbgPrint("\tBaseClass is 0x%x\n", (int) configInfo->BaseClass);
    DbgPrint("\tCacheLineSize is 0x%x\n", (int) configInfo->CacheLineSize);
    DbgPrint("\tLatencyTimer is 0x%x\n", (int) configInfo->LatencyTimer);
    DbgPrint("\tHeaderType is 0x%x\n", (int) configInfo->HeaderType);
    DbgPrint("\tBIST is 0x%x\n", (int) configInfo->HeaderType);

    for (index = 0; index < PCI_TYPE0_ADDRESSES; index++)  {

        DbgPrint("\tBaseAddresses[%d] is 0x%x\n",index, configInfo->u.type0.BaseAddresses[index]);

    }

    DbgPrint("\tROMBaseAddress is 0x%x\n", configInfo->u.type0.ROMBaseAddress);
    DbgPrint("\tInterruptLine is 0x%x\n", configInfo->u.type0.InterruptLine);
    DbgPrint("\tInterruptPin is 0x%x\n", configInfo->u.type0.InterruptPin);
    DbgPrint("****************************\n");

}    


//
// Some static string tables we use as part of debugging
//
static PSTR CmResourceTypeStrings[] = 
{
    "CmResourceTypeNull",
    "CmResourceTypePort",
    "CmResourceTypeInterrupt",
    "CmResourceTypeMemory",
    "CmResourceTypeDma",
    "CmResourceTypeDeviceSpecific",
    "CmResourceTypeBusNumber"
};

static PSTR CmResourceTypeStringsAt128[] =
{
    "CmResourceTypeConfigData",
    "CmResourceTypeDevicePrivate",
    "CmResourceTypePcCardConfig"

};
static PSTR CmShareDispositionStrings[] = 
{
    "CmResourceShareUndetermined",
    "CmResourceShareDeviceExclusive",
    "CmResourceShareDriverExclusive",
    "CmResourceShareShared"
};

///////////////////////////////////////////////////////////////////////////////
//
//  OsrPrintResourceList
//
//      This routine is called to print out the Resource descriptor list containing
//    the resources allocated for our device by NT.
//
//  INPUTS:
//
//      Resources - Address of the CM_RESOURCE_LIST information for our device.
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
//    We only use this for debugging purposes.
//
///////////////////////////////////////////////////////////////////////////////
VOID OsrPrintResourceList(PCM_RESOURCE_LIST Resources)
{
    ULONG index, index2;
        
    DbgPrint("%d. resource descriptor list(s) returned\n", Resources->Count);

    for (index = 0; index < Resources->Count; index++)  {
        
        DbgPrint("\t[%d] Version 0x%x\n",
                index, Resources->List[index].PartialResourceList.Version);
        DbgPrint("\t[%d] Revision 0x%x\n",
                index, Resources->List[index].PartialResourceList.Revision);
        
        DbgPrint("\t[%d] Partial Resource Descriptors %d.\n",
                index, Resources->List[index].PartialResourceList.Count);
        for (index2 = 0;
            index2 < Resources->List[index].PartialResourceList.Count;
            index2++)  {

            PCM_PARTIAL_RESOURCE_DESCRIPTOR prd; // Too much to type!
            
            prd = &Resources->List[index].PartialResourceList.PartialDescriptors[index2];

                DbgPrint("\t\t[%d] Type 0x%x (%s)\n",
                        index2, prd->Type, (prd->Type < 128 ? CmResourceTypeStrings[prd->Type] : CmResourceTypeStringsAt128[prd->Type-128]));
                DbgPrint("\t\t[%d] Share Disposition 0x%x (%s)\n",
                        index2, prd->ShareDisposition,
                        CmShareDispositionStrings[prd->ShareDisposition]);
                DbgPrint("\t\t[%d] Flags 0x%x\n", index2, prd->Flags);
                DbgPrint("\t\t[%d] Raw 0x%x %x %x\n",
                        index2, prd->u.DeviceSpecificData.DataSize,
                        prd->u.DeviceSpecificData.Reserved1,
                        prd->u.DeviceSpecificData.Reserved2);

                switch (prd->Type) {
                
                    case CmResourceTypePort:
                        if (prd->Flags == CM_RESOURCE_PORT_MEMORY)
                            DbgPrint("\t\t[%d] port memory starting at 0x%x length 0x%x\n", 
                                          index2, prd->u.Port.Start.LowPart,
                                          prd->u.Port.Length);
                        if (prd->Flags == CM_RESOURCE_PORT_IO)
                           DbgPrint("\t\t[%d] port i/o starting at 0x%x length 0x%x\n", 
                                         index2, prd->u.Port.Start.LowPart,
                                         prd->u.Port.Length);
                        break;

                    case CmResourceTypeInterrupt:
                        if (prd->Flags == CM_RESOURCE_INTERRUPT_LEVEL_SENSITIVE)
                            DbgPrint("\t\t[%d] level interrupt at lvl 0x%x vector 0x%x affinity 0x%x\n", 
                                         index2, prd->u.Interrupt.Level,
                                         prd->u.Interrupt.Vector,
                                         prd->u.Interrupt.Affinity);
                        if (prd->Flags == CM_RESOURCE_INTERRUPT_LATCHED)
                            DbgPrint("\t\t[%d] latched interrupt at lvl 0x%x vector 0x%x affinity 0x%x\n", 
                                         index2, prd->u.Interrupt.Level,
                                         prd->u.Interrupt.Vector,
                                         prd->u.Interrupt.Affinity);
                        break;

                    case CmResourceTypeMemory:
                        if (prd->Flags == CM_RESOURCE_MEMORY_READ_WRITE)
                            DbgPrint("\t\t[%d] r/w memory starting at 0x%x length 0x%x\n",
                                     index2, prd->u.Memory.Start.LowPart,
                                     prd->u.Memory.Length);
                        if (prd->Flags & CM_RESOURCE_MEMORY_READ_ONLY)
                            DbgPrint("\t\t[%d] r/o memory starting at 0x%x length 0x%x\n",
                                     index2, prd->u.Memory.Start.LowPart,
                                     prd->u.Memory.Length);
                        if (prd->Flags & CM_RESOURCE_MEMORY_WRITE_ONLY)
                            DbgPrint("\t\t[%d] w/o memory starting at 0x%x length 0x%x\n",
                                     index2, prd->u.Memory.Start.LowPart,
                                     prd->u.Memory.Length);
                        break;

                    case CmResourceTypeDma:
                        DbgPrint("\t\t[%d] DMA on channel 0x%x\n",
                            index2, prd->u.Dma.Channel);
                        break;

                    case CmResourceTypeDeviceSpecific:
                        DbgPrint("\t\t[%d] Device specific data at 0x%x length 0x%x\n",
                                     index2,
                                     ((ULONG) &prd->u.DeviceSpecificData.Reserved2) + (ULONG)sizeof(ULONG),
                                     prd->u.DeviceSpecificData.DataSize);
                        break;

                    case CmResourceTypeBusNumber:
                        DbgPrint("\t\t[%d] Bus Number 0x%x length 0x%x, Reserved 0x%0x\n",
                                     index2, prd->u.BusNumber.Start,
                                      prd->u.BusNumber.Length,
                                       prd->u.BusNumber.Reserved); 

                        break;

                    case CmResourceTypeDevicePrivate:
                        DbgPrint("\t\t[%d] Device Private data 0x%0x 0x%0x 0x%0x\n",
                                        prd->u.DevicePrivate.Data[0],
                                        prd->u.DevicePrivate.Data[1],
                                        prd->u.DevicePrivate.Data[2]);

                        break;

                    default:
                        //
                        // Say what?!!  Unknown resource type.  Something is pretty wierd here.
                        //
                        DbgPrint("Other resource type %d.\n", prd->Type);
                        break;
                }
            }

        }
            DbgPrint("\t[%d] ***** End dump ******\n", index);
}
///////////////////////////////////////////////////////////////////////////////
//
//  OsrPrintIntcsr
//
//      This routine is called to print out a descriptive view of the bits set
//    in the IntCsr register.
//
//  INPUTS:
//
//      Intcsr - Contents of the IntCsr register.
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
//    This routine is called at IRQL >= IRQL_PASSIVE_LEVEL.
//
//  NOTES:
//
//    We only use this for debugging purposes.  It is called by the ISR as well
//    as by the read and write paths.
//
///////////////////////////////////////////////////////////////////////////////
VOID
OsrPrintIntcsr(ULONG Intcsr) 
{

    if(Intcsr & AMCC_INT_OUT_FIFO_CTRL)  {
        
        DbgPrint("\tOut FIFO Ctrl\n");
    }


    if(Intcsr & AMCC_INT_IN_FIFO_CTRL)  {
        
        DbgPrint("\tIn FIFO Ctrl\n");
    }

    if(Intcsr & AMCC_INT_FIFO_ADVA_BYTE0)  {
        
        DbgPrint("\tADVA BYTE0\n");
    }

    if(Intcsr & AMCC_INT_FIFO_ADVA_BYTE1)  {
        
        DbgPrint("\tADVA BYTE1\n");
    }

    if(Intcsr & AMCC_INT_FIFO_ADVA_BYTE2)  {
        
        DbgPrint("\tADVA BYTE2\n");
    }

    if(Intcsr & AMCC_INT_FIFO_ADVA_BYTE3)  {
        
        DbgPrint("\tADVA BYTE3\n");
    }

    if(Intcsr & AMCC_INT_FIFO_ADVP_BYTE0)  {
        
        DbgPrint("\tADVP BYTE0\n");
    }

    if(Intcsr & AMCC_INT_FIFO_ADVP_BYTE1)  {
       
        DbgPrint("\tADVP BYTE1\n");
    }

    if(Intcsr & AMCC_INT_FIFO_ADVP_BYTE2)  {
        
        DbgPrint("\tADVP BYTE2\n");
    }

    if(Intcsr & AMCC_INT_FIFO_ADVP_BYTE3)  {
        
        DbgPrint("\tADVP BYTE3\n");
    }

    if(Intcsr & AMCC_INT_ENDIAN_16BIT)  {
        
        DbgPrint("\tENDIAN 16BIT\n");
    }

    if(Intcsr & AMCC_INT_ENDIAN_32BIT)  {
        
        DbgPrint("\tENDIAN 32BIT\n");
    }

    if(Intcsr & AMCC_INT_ENDIAN_64BIT)  {
        
        DbgPrint("\tENDIAN 64BIT\n");
    }

    if(Intcsr & AMCC_INT_INTERRUPTED)  {
        
        DbgPrint("\tINTERRUPTED\n");
    }

    if(Intcsr & AMCC_INT_RESERVED22)  {
        
        DbgPrint("\tRESERVED 22\n");
    }

    if(Intcsr & AMCC_INT_TARG_ABORT)  {
        
        DbgPrint("\tTARG_ABORT\n");
    }

    if(Intcsr & AMCC_INT_MAST_ABORT)  {
        
       DbgPrint("\tMAST_ABORT\n");
    }

    if(Intcsr & AMCC_INT_READ_COMP)  {
        
       DbgPrint("\tREAD_COMP\n");
    }

    if(Intcsr & AMCC_INT_WRITE_COMP)  {
        
       DbgPrint("\tWRITE_COMP\n");
    }

    if(Intcsr & AMCC_INT_INMBX_ACK)  {
        
       DbgPrint("\tINMBX_ACK\n");
    }

    if(Intcsr & AMCC_INT_OUTMBX_ACK)  {
        
       DbgPrint("\tOUTMBX_ACK\n");
    }

    if(Intcsr & AMCC_INT_INT_ON_READ)  {
        
       DbgPrint("\tINT_ON_READ\n");
    }

    if(Intcsr & AMCC_INT_INT_ON_WRITE)  {
        
       DbgPrint("\tINT_ON_WRITE\n");
    }

    if(Intcsr & AMCC_INT_RESERVED13)  {
        
       DbgPrint("\tRESERVED13\n");
    }

    if(Intcsr & AMCC_INT_ENABLE_OUTMBX_INT)  {
        
       DbgPrint("\tENABLE_OUTMBX_INT\n");
    }

    if(Intcsr & AMCC_INT_ENABLE_INMBX_INT)  {
        
       DbgPrint("\tENABLE_INMBX_INT\n");
    }


}    

#endif      // DBG
