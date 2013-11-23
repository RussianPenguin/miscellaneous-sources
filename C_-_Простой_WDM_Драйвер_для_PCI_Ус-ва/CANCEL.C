///////////////////////////////////////////////////////////////////////////////
//
//    (C) Copyright 1995 - 1997 OSR Open Systems Resources, Inc.
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
//        CANCEL.C
//
//    ABSTRACT:
//
//      This file contains the routines that handle cancle processing for the 
//      OSR Sample PCI Busmaster DMA device driver for the AMCC 5933 chip.  It
//      also contains code for the watchdog timer.
//
//    AUTHOR(S):
//
//        OSR Open Systems Resources, Inc.
// 
//    REVISION:   
//
//
///////////////////////////////////////////////////////////////////////////////

#include "osr-pci.h"

//
// Forward declarations
// 
BOOLEAN CancelInProgressRead(IN PVOID SynchronizeContext);
BOOLEAN CancelInProgressWrite(IN PVOID SynchronizeContext);
PIRP OsrFindQueuedRequest(PLIST_ENTRY ListHead);

///////////////////////////////////////////////////////////////////////////////
//
//  OsrCancelFromReadQueue
//
//    This is the cancel routine, called when a READ IRP needs to be
//    cancelled.  The I/O manager calls this entry point at IRQL DISPATCH_LEVEL
//    with cancel spin lock held.
//
//    When we return from here one of two things will have occurred:
//
//    1.We found the IRP to cancel on our read queue. In this case, we simply
//      remove the IRP from the READ queue, complete it with STATUS_CANCELLED
//      and return from this routine.
//
//    2.We did not find the IRP to cancel on our read queue.  In this case,
//      we just return.  This could only happen when the request is in
//      progress, or is in the process of being moved from the queue to
//      being to being in progress.
//
//  Note that we take our own advice in this function, and don't worry about
//  cancelling requests that are in-progress on the device.  It's not that it's
//  not possible to cancel such requests, but rather that in-progress requests
//  will complete quickly, so there's no reason to add the extra complexity
//  of trying to cancel these requests on the hardware.
//
//  INPUTS:
//
//      DeviceObject - Address of our DEVICE_OBJECT.
//
//      Irp - Address of IRP to cancel.
//
//  OUTPUTS:
//
//      None.
//
//  RETURNS:
//
//    None.
//
//  IRQL:
//
//    This routine is called at IRQL DISPATCH_LEVEL with the SYSTEM WIDE 
//    cancel spin lock held.
//
//  NOTES:
//
//
///////////////////////////////////////////////////////////////////////////////
VOID OsrCancelFromReadQueue(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp)
{
    PIRP irpToCancel;
    POSR_DEVICE_EXT devExt;
    KIRQL   oldIrql;

    devExt = DeviceObject->DeviceExtension;

#if DBG
    DbgPrint("OsrCancelFromReadQueue... Passed IRP = 0x%0x\n", Irp);
#endif 

    //
    // Drop the SYSTEM WIDE cancel spin lock.  There's no need for us to
    // hold it
    //
    IoReleaseCancelSpinLock(Irp->CancelIrql);

    //
    // Take out the read queue lock while running the list
    //
    KeAcquireSpinLock(&devExt->ReadQueueLock, &oldIrql);

    //
    // See if we can find the request to cancel on the appropriate queue
    //
    irpToCancel = OsrFindQueuedRequest(&devExt->ReadQueue);
    
    //
    // Drop the lock that protects the Read queue.  We're done running
    // the list.
    //
    KeReleaseSpinLock(&devExt->ReadQueueLock, oldIrql);

    //
    // If we found the request to cancel, we cancel it
    //
    if(irpToCancel)  {
        
#if DBG
        DbgPrint("OsrCancelFromReadQueue: Cancelling IRP 0x%0x\n", irpToCancel);
#endif
        
        IoSetCancelRoutine(irpToCancel, NULL);
        
        irpToCancel->IoStatus.Status = STATUS_CANCELLED;
        irpToCancel->IoStatus.Information = 0;

        IoCompleteRequest(irpToCancel, IO_NO_INCREMENT);

    }

#if DBG
    DbgPrint("OsrCancelFromReadQueue: Leaving\n");
#endif

}    

///////////////////////////////////////////////////////////////////////////////
//
//
// OsrCancelFromWriteQueue
//
//    Called at IRQL DISPATCH_LEVEL with cancel spin lock held.  See the
//    comments at OsrCancelFromReadQueue, above.  They apply to this routine
//    as well, except for WRITE instead of READ.
//
//
//  INPUTS:
//
//      DeviceObject - Address of our DEVICE_OBJECT.
//
//      Irp - Address of IRP to cancel.
//
//  OUTPUTS:
//
//      None.
//
//  RETURNS:
//
//    None.
//
//  IRQL:
//
//    This routine is called at IRQL DISPATCH_LEVEL with the SYSTEM WIDE 
//    cancel spin lock held.
//
//  NOTES:
//
//
///////////////////////////////////////////////////////////////////////////////
VOID OsrCancelFromWriteQueue(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp)
{
    PIRP irpToCancel;
    POSR_DEVICE_EXT devExt;
    KIRQL oldIrql;

    devExt = DeviceObject->DeviceExtension;

#if DBG
    DbgPrint("OsrCancelFromWriteQueue... Passed IRP = 0x%0x\n", Irp);
#endif

    //
    // Drop the SYSTEM WIDE cancel spin lock.  There's no need for us to
    // hold it
    //
    IoReleaseCancelSpinLock(Irp->CancelIrql);

    //
    // Take out the read queue lock while running the list
    //
    KeAcquireSpinLock(&devExt->WriteQueueLock, &oldIrql);

    //
    // See if there's an IRP to be canceled on the WRITE queue
    //
    irpToCancel = OsrFindQueuedRequest(&devExt->WriteQueue);
    
    //
    // Drop the lock that protects the Write queue.  We're done running
    // the list.
    //
    KeReleaseSpinLock(&devExt->WriteQueueLock, oldIrql);

    //
    // If we found one, we cancel it
    //
    if(irpToCancel)  {
        
#if DBG
        DbgPrint("OsrCancelFromWriteQueue: Cancelling IRP 0x%0x\n", irpToCancel);
#endif
        
        //
        // We found a request to cancel.
        // We just need to complete the IRP.
        //

        IoSetCancelRoutine(irpToCancel, NULL);
        
        irpToCancel->IoStatus.Status = STATUS_CANCELLED;
        irpToCancel->IoStatus.Information = 0;

        IoCompleteRequest(irpToCancel, IO_NO_INCREMENT);

    }

#if DBG
    DbgPrint("OsrCancelFromWriteQueue: Leaving\n");
#endif

}    

///////////////////////////////////////////////////////////////////////////////
//
// OsrFindQueuedRequest
//
//    Searches the list starting with ListHead for request to cancel
//
//    NOTE: **MUST** be called with appropriate list spin lock held
//
//  INPUTS:
//
//      ListHead - Address of the List head to search.
//
//  OUTPUTS:
//
//      None.
//
//  RETURNS:
//
//    NULL        IRP not found on list
//    PIRP        Pointer to IRP found on queue to cancel. In this case, IRP
//                is NOT the in-progress IRP, and is REMOVED from the list.
//
//  IRQL:
//
//    **MUST** be called with appropriate list spin lock held.
//
//  NOTES:
//
//
///////////////////////////////////////////////////////////////////////////////
PIRP OsrFindQueuedRequest(PLIST_ENTRY ListHead)
{
    PLIST_ENTRY entry;
    PIRP irp;

    //
    // Run the list, looking for an IRP with it's Cancel field set to TRUE
    //    
    for(entry = ListHead->Flink; entry != ListHead; entry = entry->Flink) {
        
        irp = CONTAINING_RECORD(entry, IRP, Tail.Overlay.ListEntry);

        //
        // Found it!
        //
        if(irp->Cancel)  {
            break;
        }
    }

    //
    // If we exited the loop without finding an IRP to cancel, just
    // return NULL
    //
    if(entry == ListHead)  {
        return(NULL);
    }


    RemoveEntryList(entry);

    return(irp);
}    



///////////////////////////////////////////////////////////////////////////////
//
//
// OsrWatchdogTimer
//
//  This function is called once per second per device object support.
//  It's role is to check to ensure that the currently active read and write
//  requests don't "hang" on the device.  If either requests take longer
//  than the prescribed time to complete, this function cancels the request.
//
//  INPUTS:
//
//      DeviceObject - Address of our DEVICE_OBJECT.
//
//      Context - Not used.
//
//  OUTPUTS:
//
//      None.
//
//  RETURNS:
//
//    None.
//
//  IRQL:
//
//    This routine is called at IRQL DISPATCH_LEVEL
//
//  NOTES:
//
//
///////////////////////////////////////////////////////////////////////////////
VOID
OsrWatchdogTimer(PDEVICE_OBJECT DeviceObject,
                 PVOID Context) 
{
    POSR_DEVICE_EXT devExt;
    KIRQL oldIrql;

    devExt = DeviceObject->DeviceExtension;

    //
    // Take out the write queue lock while checking the in-progress write
    //
    KeAcquireSpinLock(&devExt->WriteQueueLock, &oldIrql);

    //
    // If there's a write operation in progress
    //
    if(devExt->CurrentWriteIrp) {

        //
        // If the watchdog count on the current write IRP has expired
        //
        if(! --((ULONG)(devExt->CurrentWriteIrp->Tail.Overlay.DriverContext[0])) ) {

#if DBG
            DbgPrint("OsrWatchdogTimer: WRITE killed 0x%0x\n", devExt->CurrentWriteIrp);
#endif
            //            
            // Soft reset the write processing on this device, and
            // queue a DpcForIsr() to cancel the in progress request.
            //
            (void)KeSynchronizeExecution(devExt->InterruptObject,
                                    CancelInProgressWrite,
                                    devExt);
        }

    }

    //
    // Drop the lock
    //
    KeReleaseSpinLock(&devExt->WriteQueueLock, oldIrql);


    //
    // Take out the read queue lock while checking the in-progress read
    //
    KeAcquireSpinLock(&devExt->ReadQueueLock, &oldIrql);

    //
    // If there's a write operation in progress
    //
    if(devExt->CurrentReadIrp) {

        //
        // If the watchdog count on the current write IRP has expired
        //
        if(! --((ULONG)(devExt->CurrentReadIrp->Tail.Overlay.DriverContext[0])) ) {

#if DBG
            DbgPrint("OsrWatchdogTimer: READ killed 0x%0x\n", devExt->CurrentReadIrp);
#endif
            //            
            // Soft reset the write processing on this device, and
            // queue a DpcForIsr() to cancel the in progress request.
            //
            (void)KeSynchronizeExecution(devExt->InterruptObject,
                                    CancelInProgressRead,
                                    devExt);
        }

    }

    //
    // Drop the lock
    //
    KeReleaseSpinLock(&devExt->ReadQueueLock, oldIrql);

}

///////////////////////////////////////////////////////////////////////////////
//
// CancelInProgressRead
//
//    This is a synchronize function, called with the ISR spinlock, and the
//    read queue spin lock HELD.
//    Returns with these locks HELD.
//
//  INPUTS:
//
//      SynchronizeContext - Address of our device extension.
//
//  OUTPUTS:
//
//      None.
//
//  RETURNS:
//
//      TRUE.
//
//  IRQL:
//
//      DIRQL
//
//  NOTES:
//
//
///////////////////////////////////////////////////////////////////////////////
BOOLEAN
CancelInProgressRead(IN PVOID SynchronizeContext)
{
    POSR_DEVICE_EXT devExt = (POSR_DEVICE_EXT)SynchronizeContext;
    ULONG temp;

    //
    // Get the current MCSR register value, mask off the bits that need
    // to be preserved, and CLEAR the WRITE_ENABLE bit... thus STOPPING
    // the transfer dead in its tracks. (Yes, it IS WRITE_ENABLE)
    //
    if(devExt->State > STATE_ALL_BELOW_NO_HW) {
        temp = READ_PORT_ULONG(devExt->AmccBaseRegisterAddress+MCSR_OFF);
    }

    //
    // Preserve these bits
    //
    temp &= (AMCC_MCSR_READ_ENABLE|
                AMCC_MCSR_READ_FIFO_MGMT|
                AMCC_MCSR_READ_PRIORITY|
                AMCC_MCSR_WRITE_ENABLE|
                AMCC_MCSR_WRITE_FIFO_MGMT|
                AMCC_MCSR_WRITE_PRIORITY);
    //
    // Clear this bit
    //
    temp &= ~AMCC_MCSR_WRITE_ENABLE;

    //
    // DO it on the device
    //
    if(devExt->State > STATE_ALL_BELOW_NO_HW) {
        WRITE_PORT_ULONG(devExt->AmccBaseRegisterAddress+MCSR_OFF, temp); 
    }

    //
    // Indicate the read is complete (setting _WRITE_COMP bit)
    //
    devExt->IntCsr |= AMCC_INT_WRITE_COMP;

    //
    // Indicate to the DpcforIsr that the request is being
    // cancelled.  The DpcForIsr specifically looks at the
    // ReadTotalLength flag to determine if the requsest is being
    // cancelled.
    //
    devExt->ReadTotalLength = 0;
    devExt->ReadSoFar = 0;
    
    //
    // Request the DPC for ISR, just as if the read were
    // ordinarily completing.  NOTE: NO CHANCE OF RACE HERE, since
    // we're HOLDING THE ISR SPINLOCK.
    //
    IoRequestDpc(devExt->FunctionalDeviceObject, 0, NULL);

    return(TRUE);
}    

///////////////////////////////////////////////////////////////////////////////
//
// CancelInProgressWrite
//
//    This is a synchronize function, called with the ISR spinlock,and the write
//    queue spin lock ALL HELD. Returns with these locks HELD.
//
//  INPUTS:
//
//      SynchronizeContext - Address of our device extension.
//
//  OUTPUTS:
//
//      None.
//
//  RETURNS:
//
//    TRUE.
//
//  IRQL:
//
//      DIRQL
//
//  NOTES:
//
//
///////////////////////////////////////////////////////////////////////////////
BOOLEAN
CancelInProgressWrite(IN PVOID SynchronizeContext)
{
    POSR_DEVICE_EXT devExt = (POSR_DEVICE_EXT)SynchronizeContext;
    ULONG temp;

    //
    // Get the current MCSR register value, mask off the bits that need
    // to be preserved, and CLEAR the READ_ENABLE bit... thus STOPPING
    // the transfer dead in its tracks.
    //
    if(devExt->State > STATE_ALL_BELOW_NO_HW) {
        temp = READ_PORT_ULONG(devExt->AmccBaseRegisterAddress+MCSR_OFF);
    }

    //
    // Preserve these bits
    //
    temp &= (AMCC_MCSR_READ_ENABLE|
                AMCC_MCSR_READ_FIFO_MGMT|
                AMCC_MCSR_READ_PRIORITY|
                AMCC_MCSR_WRITE_ENABLE|
                AMCC_MCSR_WRITE_FIFO_MGMT|
                AMCC_MCSR_WRITE_PRIORITY);

    //
    // Clearing READ_ENABLE stops the WRITE operation
    //
    temp &= ~AMCC_MCSR_READ_ENABLE;

    //
    // Tell it to the device
    //
    if(devExt->State > STATE_ALL_BELOW_NO_HW) {
        WRITE_PORT_ULONG(devExt->AmccBaseRegisterAddress+MCSR_OFF, temp); 
    }

    //
    // Fake the write completion by setting the appropriate bit in
    // our private copy of the IntCSR
    //
    devExt->IntCsr |= AMCC_INT_READ_COMP;

    //
    // Indicate to the DPC for ISR that the request is being
    // cancelled
    //
    devExt->WriteTotalLength = 0;
    devExt->WriteSoFar = 0;
    
    //
    // Request the DPC for ISR, just as if the read were
    // ordinarily completing.
    //
    IoRequestDpc(devExt->FunctionalDeviceObject, 0, NULL);

    return(TRUE);
}    

//
// OsrClearQueues
//
VOID OsrClearQueues(POSR_DEVICE_EXT DevExt)
{
    PLIST_ENTRY entry;
    PIRP irp;
    KIRQL oldIrql;

    //
    // Cancel everything on the read queue
    //
    KeAcquireSpinLock(&DevExt->ReadQueueLock, &oldIrql);

    //
    // Ensure the current read request gets cancelled at the first
    // opportunity
    //
    if(DevExt->CurrentReadIrp) {
        (ULONG)DevExt->CurrentReadIrp->Tail.Overlay.DriverContext[0] = 1;
    }

    while(TRUE) {

        entry = RemoveHeadList(&DevExt->ReadQueue);

        if(entry == &DevExt->ReadQueue) {
            break;
        }

        irp = CONTAINING_RECORD(entry, IRP, Tail.Overlay.ListEntry);

        irp->IoStatus.Status = STATUS_DEVICE_OFF_LINE;
        irp->IoStatus.Information = 0;
    
        OsrRequestDecrement(DevExt);

        IoCompleteRequest(irp, IO_NO_INCREMENT);

    }

    KeReleaseSpinLock(&DevExt->ReadQueueLock, oldIrql);


    //
    // Cancel everything on the write queue
    //
    KeAcquireSpinLock(&DevExt->WriteQueueLock, &oldIrql);

    //
    // Ensure the current write IRP gets cancelled in the next second
    //
    if(DevExt->CurrentWriteIrp) {
        (ULONG)DevExt->CurrentWriteIrp->Tail.Overlay.DriverContext[0] = 1;
    }

    while(TRUE) {

        entry = RemoveHeadList(&DevExt->WriteQueue);

        if(entry == &DevExt->WriteQueue) {
            break;
        }

        irp = CONTAINING_RECORD(entry, IRP, Tail.Overlay.ListEntry);

        irp->IoStatus.Status = STATUS_DEVICE_OFF_LINE;
        irp->IoStatus.Information = 0;
    
        OsrRequestDecrement(DevExt);

        IoCompleteRequest(irp, IO_NO_INCREMENT);

    }

    KeReleaseSpinLock(&DevExt->WriteQueueLock, oldIrql);


}    

