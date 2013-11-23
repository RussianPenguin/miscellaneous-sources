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
//        READ_WRITE.C
//
//    ABSTRACT:
//
//      This file contains read and write routines used by the
//      PCI Busmaster DMA device driver for the AMCC 5933 chip.
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
// forward declarations
//
BOOLEAN OsrStartReadOnDevice(IN PVOID SynchronizeContext);
BOOLEAN OsrStartWriteOnDevice(IN PVOID SynchronizeContext);

IO_ALLOCATION_ACTION  OsrAdapterControlRead(IN PDEVICE_OBJECT DeviceObject,
                                IN PIRP NotUsed, IN PVOID MapRegisterBase,
                                IN PVOID Context);
IO_ALLOCATION_ACTION  OsrAdapterControlWrite(IN PDEVICE_OBJECT DeviceObject,
                                IN PIRP NotUsed, IN PVOID MapRegisterBase,
                                IN PVOID Context);

///////////////////////////////////////////////////////////////////////////////
//
//  OsrWrite
//
//    This is the write dispatch entry point for the driver, called when the
//    I/O Manager has an IRP_MJ_WRITE request for the driver to process.
//
//  INPUTS:
//
//      DeviceObject - Address of the DEVICE_OBJECT for our device.
//  
//    Irp - Address of the IRP representing the IRP_MJ_WRITE call.
//
//  OUTPUTS:
//
//      None.
//
//  RETURNS:
//
//    STATUS_PENDING, since we are putting the IRP on our internal queue.
//
//  IRQL:
//
//    This routine is called at IRQL_PASSIVE_LEVEL.
//
//  NOTES:
//
//    Since we set the DO_DIRECT_IO bit in the Device Object, all buffers
//    passed to us will have been probed and locked and described by an MDL.
//    The I/O manager will provides us the MDL address in Irp->MdlAddress.
//
///////////////////////////////////////////////////////////////////////////////
NTSTATUS OsrWrite(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
    POSR_DEVICE_EXT devExt = DeviceObject->DeviceExtension;
    KIRQL oldIrql;
    NTSTATUS code = STATUS_SUCCESS;
    BOOLEAN listWasEmpty;
    PIO_STACK_LOCATION ioStack;
    ULONG temp;
            
#if DBG
    DbgPrint("OsrWrite: entered\n");
#endif

    //
    // See what sort of state we're in
    //
    if (devExt->State < STATE_ALL_BELOW_FAIL) {

        code = STATUS_UNSUCCESSFUL;

        Irp->IoStatus.Information = 0;
        Irp->IoStatus.Status = code;

        IoCompleteRequest (Irp, IO_NO_INCREMENT);

		return code;

	}

    OsrRequestIncrement(devExt);

    //
    // Validate the IRP we've received
    //
    ioStack = IoGetCurrentIrpStackLocation(Irp);

    //
    // If the length of the requested transfer is either zero or too long,
    // we immediately compelte the IRP with an error status.
    //
    if (ioStack->Parameters.Write.Length == 0 ||
        ioStack->Parameters.Write.Length > OSR_PCI_MAX_TXFER)  {
            
        Irp->IoStatus.Status = STATUS_INVALID_USER_BUFFER;
        Irp->IoStatus.Information = 0;

        IoCompleteRequest(Irp, IO_NO_INCREMENT);

        return(STATUS_INVALID_USER_BUFFER);

    }
    
    // Take out the Write list lock, since we'll insert this IRP
    // onto the write queue
    //
    KeAcquireSpinLock(&devExt->WriteQueueLock, &oldIrql);

    //
    // Since we'll probably be queuing this request, set a routine 
    // to be called by the I/O Manager in case he needs to cancel
    // this IRP.
    //
    IoSetCancelRoutine(Irp, OsrCancelFromWriteQueue);

    //
    // Before we queue this request, has it been cancelled??
    //
    // What we're doing here is closing that tiny window between the time
    // the Dispatch routine is called and when we acquired the queue spin
    // lock.  Once the queue spin lock is held, and the IRP is queued, the
    // cancellation routine will deal with any requests to cancel the IRP.
    //
    if (Irp->Cancel)  {
        
        //
        // Can't complete a request with a valid cancel routine!
        //
        // TECHNICAL ERRATA: Page 466, Example 17.5 has the following
        // line, which is obviously in error:
        //
        // IoSetCancelRoutine(Irp, OsrCancelFromWriteQueue);
        // 
        // This line SHOULD READ:
        //
        IoSetCancelRoutine(Irp, NULL);
         
        KeReleaseSpinLock(&devExt->WriteQueueLock, oldIrql);

        Irp->IoStatus.Status = STATUS_CANCELLED;
        Irp->IoStatus.Information = 0;

        IoCompleteRequest(Irp, IO_NO_INCREMENT);

        return(STATUS_CANCELLED);
    }

    //
    // If we get this far, we will return with this request pending
    //
    IoMarkIrpPending(Irp);

    //
    // Do we need to start this request on the device?
    //
    // If there is no IRP currently in progress, we'll start the
    // one we've just received, if the device state allows it.
    //
    if (devExt->CurrentWriteIrp == NULL &&
        devExt->State == STATE_STARTED)  {
                
        //
        // No write presently active.  Start this request...
        // (Note that we're still holding the queue lock here)
        //
        OsrStartWriteIrp(DeviceObject,Irp);

    } else {

        //
        // Put this request on the end of the write queue
        //
        InsertTailList(&devExt->WriteQueue, &Irp->Tail.Overlay.ListEntry);

    }

    //
    // We're done playing with the write queue now
    //
    KeReleaseSpinLock(&devExt->WriteQueueLock, oldIrql);
    
#if DBG
    DbgPrint("OsrWrite: exiting\n");
#endif

    return(STATUS_PENDING);
}

///////////////////////////////////////////////////////////////////////////////
//
//  OsrRead
//
//    This is the read dispatch entry point for the driver, called when the
//    I/O Manager has an IRP_MJ_READ request for the driver to process.
//
//  INPUTS:
//
//      DeviceObject - Address of the DEVICE_OBJECT for our device.
//  
//    Irp - Address of the IRP representing the IRP_MJ_READ call.
//
//  OUTPUTS:
//
//      None.
//
//  RETURNS:
//
//    STATUS_PENDING, since we are putting the IRP on our internal queue.
//
//  IRQL:
//
//    This routine is called at IRQL_PASSIVE_LEVEL.
//
//  NOTES:
//
//    Since we set the DO_DIRECT_IO bit in the Device Object, all buffers
//    passed to us will have been probed and locked and described by an MDL.
//    The I/O manager will provides us the MDL address in Irp->MdlAddress.
//
///////////////////////////////////////////////////////////////////////////////
NTSTATUS OsrRead(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
    POSR_DEVICE_EXT devExt = DeviceObject->DeviceExtension;
    KIRQL oldIrql;
    NTSTATUS code = STATUS_SUCCESS;
    BOOLEAN listWasEmpty;
    PIO_STACK_LOCATION ioStack;
    ULONG temp;
            
#if DBG
    DbgPrint("OsrRead: entered\n");
#endif

    //
    // See what sort of state we're in
    //
    if (devExt->State < STATE_ALL_BELOW_FAIL) {

        code = STATUS_UNSUCCESSFUL;

        Irp->IoStatus.Information = 0;
        Irp->IoStatus.Status = code;

        IoCompleteRequest (Irp, IO_NO_INCREMENT);

		return code;

	}

    OsrRequestIncrement(devExt);

    //
    // Validate the IRP we've received
    //
    ioStack = IoGetCurrentIrpStackLocation(Irp);

    //
    // If the length of the requested transfer is either zero or too long,
    // we immediately compelte the IRP with an error status.
    //
    if (ioStack->Parameters.Read.Length == 0 ||
        ioStack->Parameters.Read.Length > OSR_PCI_MAX_TXFER)  {
            
        Irp->IoStatus.Status = STATUS_INVALID_USER_BUFFER;
        Irp->IoStatus.Information = 0;

        IoCompleteRequest(Irp, IO_NO_INCREMENT);

        return(STATUS_INVALID_USER_BUFFER);

    }

    //
    // Get the Read Queue lock, so we can insert our IRP
    //
    KeAcquireSpinLock(&devExt->ReadQueueLock, &oldIrql);

    //
    // Since we'll probably be queuing this request, set a routine 
    // to be called by the I/O Manager in case he needs to cancel
    // this IRP.
    //
    IoSetCancelRoutine(Irp, OsrCancelFromReadQueue);

    //
    // Do we need to cancel this IRP, instead of queue it?
    //
    if (Irp->Cancel)  {
        
        //
        // Can't complete a request with a valid cancel routine!
        //
        IoSetCancelRoutine(Irp, NULL);
    
        KeReleaseSpinLock(&devExt->ReadQueueLock, oldIrql);

        Irp->IoStatus.Status = STATUS_CANCELLED;
        Irp->IoStatus.Information = 0;

        IoCompleteRequest(Irp, IO_NO_INCREMENT);

        return(STATUS_CANCELLED);
    }

    //
    // We'll be returning with this request pending
    //
    IoMarkIrpPending(Irp);

    //
    // Do we need to start this request on the device?
    //
    // If there is no IRP currently in progress, we'll start the
    // one we've just received, if the device state allows it.
    //
    if (devExt->CurrentReadIrp == NULL &&
        devExt->State == STATE_STARTED)  {
                
        //
        // No read operation presently active.  Start this request...
        // (Note that we're still holding the queue lock here)
        //
        OsrStartReadIrp(DeviceObject,Irp);

    } else {

        //
        // Put this request on the end of the write queue
        //
        InsertTailList(&devExt->ReadQueue, &Irp->Tail.Overlay.ListEntry);

    }

    //
    // We're done
    //
    KeReleaseSpinLock(&devExt->ReadQueueLock, oldIrql);
    
#if DBG
    DbgPrint("OsrRead: exiting\n");
#endif

      return(STATUS_PENDING);
}

///////////////////////////////////////////////////////////////////////////////
//
//  OsrStartWriteIrp
//
//    This is routine is called by the OsrWrite and DpcForIsr routine to
//    start a new Write operation.  The request started is the IRP located
//    at the head of the write queue.
//
//  INPUTS:
//
//      DeviceObject - Address of the DEVICE_OBJECT for our device.
//  
//      Irp - Address of the IRP representing the IRP_MJ_WRITE call.
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
//      This routine is called at IRQL_DISPATCH_LEVEL.
//
//  NOTES:
//      *** Called (and returns) with the WriteQueueLock held.
//
///////////////////////////////////////////////////////////////////////////////
VOID
OsrStartWriteIrp(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
    POSR_DEVICE_EXT devExt = DeviceObject->DeviceExtension;
    PIO_STACK_LOCATION ioStack;
    ULONG mapRegsNeeded;
    
    ioStack = IoGetCurrentIrpStackLocation(Irp);

    //
    // In progress IRPs cannot be cancelled
    //
    IoSetCancelRoutine(Irp, NULL);

#if DBG
    DbgPrint("OsrWrite: Transfer length %d.\n",
                                ioStack->Parameters.Write.Length);
#endif

    //
    // We're starting a request... therefore, we clear the StopEvent
    // flag.
    //
    KeClearEvent(&devExt->StopEvent);

    //
    // There is no in-progress request.  Start this request on the
    // device.
    //
    devExt->CurrentWriteIrp = Irp;

    devExt->WriteTotalLength = ioStack->Parameters.Write.Length;

    devExt->WriteSoFar = 0;

    devExt->WriteStartingOffset = 0;

    //
    // Start the watchdog timer on this IRP
    //
    (ULONG)Irp->Tail.Overlay.DriverContext[0] = OSR_WATCHDOG_INTERVAL;

    //
    // Since we're about to initiate a DMA operation, ensure the user's data
    // buffer is flushed from the cache back into memory, on processors that
    // are non-DMA cache coherent.
    //
    KeFlushIoBuffers(Irp->MdlAddress, FALSE, TRUE);

    //
    // Determine the number of map registers we'll need for this transfer
    //
    mapRegsNeeded = 
        ADDRESS_AND_SIZE_TO_SPAN_PAGES(MmGetMdlVirtualAddress(Irp->MdlAddress),
                                        ioStack->Parameters.Write.Length);
        
#if DBG
    DbgPrint("StartWrite: %d. map regs needed\n", mapRegsNeeded);
#endif

    //
    // If the number of map registers required for this transfer exceeds the
    // maximum we're allowed to use (as reported to us from HalGetAdapter() ),
    // we'll need to limit ourselves to the maximum we're allowed.
    //
    devExt->MapRegsThisWrite = ((mapRegsNeeded > devExt->WriteMapRegsGot) ? 
                              devExt->WriteMapRegsGot : mapRegsNeeded);

#if DBG
    DbgPrint("StartWrite: %d. map regs this xfer\n", devExt->MapRegsThisWrite);
#endif

    //
    // Ready to GO! Allocate the appropriate Adapter Object and map registers.
    //
    IoAllocateAdapterChannel(devExt->WriteAdapter,
                             DeviceObject, 
                             devExt->MapRegsThisWrite,
                             OsrAdapterControlWrite,
                             Irp);
}


///////////////////////////////////////////////////////////////////////////////
//
//  OsrStartReadIrp
//
//    This is routine is called by the OsrRead and Dpc routine in order to
//    begin a new Read operation.
//
//  INPUTS:
//
//      DeviceObject - Address of the DEVICE_OBJECT for our device.
//  
//      Irp - Address of the IRP representing the IRP_MJ_READ call.
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
//      This routine is called at IRQL_DISPATCH_LEVEL.
//
//  NOTES:
//      *** Called (and returns) with the WriteQueueLock held.
//
///////////////////////////////////////////////////////////////////////////////
VOID
OsrStartReadIrp(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
    POSR_DEVICE_EXT devExt = DeviceObject->DeviceExtension;
    PIO_STACK_LOCATION ioStack;
    ULONG mapRegsNeeded;

    ioStack = IoGetCurrentIrpStackLocation(Irp);

    //
    // In progress IRPs cannot be cancelled
    //
    IoSetCancelRoutine(Irp, NULL);

#if DBG
    DbgPrint("OsrRead: Transfer length %d.\n",
                                ioStack->Parameters.Read.Length);
#endif

    //
    // We're starting a request... therefore, we clear the StopEvent
    // flag.
    //
    KeClearEvent(&devExt->StopEvent);

    //
    // There is no in-progress request.  Start this request on the
    // device.
    //
    devExt->CurrentReadIrp = Irp;

    devExt->ReadTotalLength = ioStack->Parameters.Read.Length;

    devExt->ReadSoFar = 0;

    devExt->ReadStartingOffset = 0;

    //
    // Start the watchdog timer on this IRP
    //
    (ULONG)Irp->Tail.Overlay.DriverContext[0] = OSR_WATCHDOG_INTERVAL;

    //
    // Flush the requestor's buffer back from cache on non-dma coherent
    // machines.
    //
    KeFlushIoBuffers(Irp->MdlAddress, TRUE, TRUE);

    //
    // Determine number of map registers required by this read
    //
    mapRegsNeeded = 
        ADDRESS_AND_SIZE_TO_SPAN_PAGES(MmGetMdlVirtualAddress(Irp->MdlAddress),
                                        ioStack->Parameters.Read.Length);
        
#if DBG
    DbgPrint("StartReadIrp: %d. map regs needed\n", mapRegsNeeded);
#endif

    //
    // Limit the number of map registers used to the maximum allowed by the
    // HAL.  We determined this max when we called HalGetAdapter() during
    // our DriverEntry processing.
    //
    devExt->MapRegsThisRead = ((mapRegsNeeded > devExt->ReadMapRegsGot) ? 
                              devExt->ReadMapRegsGot : mapRegsNeeded);

#if DBG
    DbgPrint("StartReadIrp: %d. map regs this xfer\n", devExt->MapRegsThisRead);
#endif

    IoAllocateAdapterChannel(devExt->ReadAdapter,
                             DeviceObject, 
                             devExt->MapRegsThisRead,
                             OsrAdapterControlRead,
                             Irp);


}

///////////////////////////////////////////////////////////////////////////////
//
//  OsrAdapterControlRead
//
//    This is routine is called by the I/O Manager when the Adapter resources
//    (such as map registers) requested by the OsrStartReadIrp function are
//    available for our use.
//
//  INPUTS:
//
//      DeviceObject - Address of the DEVICE_OBJECT for our device.
//  
//      MapRegisterBase - Base address of the Map registers that have been
//                        reserved for us use.
//
//       Context - address of the Read Irp for the operation to be started
//
//  OUTPUTS:
//
//      None.
//
//  RETURNS:
//
//    DeallocateObjectKeepRegisters - indicates that the Mapping Registers that
//              were allocated to us should not be deallocated at this time.  We
//              will deallocate them from the DpcForIsr when the Read completes.
//
//  IRQL:
//
//    This routine is called at IRQL_DISPATCH_LEVEL.
//
//  NOTES:
//
///////////////////////////////////////////////////////////////////////////////
IO_ALLOCATION_ACTION 
OsrAdapterControlRead(IN PDEVICE_OBJECT DeviceObject, IN PIRP NotUsed, 
                                  IN PVOID MapRegisterBase, IN PVOID Context)
{
    PIRP irp = (PIRP) Context;
    PIO_STACK_LOCATION ioStack;
    POSR_DEVICE_EXT devExt;
    PUCHAR baseVa;

#if DBG
    DbgPrint("AdapterControlRead: Irp = 0x%0x\n", irp);
    DbgPrint("AdapterControlRead: Map Register Base = 0x%0x\n", MapRegisterBase);
#endif

    devExt = DeviceObject->DeviceExtension;
    
    ioStack = IoGetCurrentIrpStackLocation(irp);

    devExt->ReadLength = ioStack->Parameters.Read.Length - devExt->ReadSoFar;

#if DBG
    DbgPrint("AdapterControlRead: Length remaining = %d. \n", devExt->ReadLength);
#endif

    //
    // Get set-up for the transfer
    //
    devExt->ReadMapRegBase = MapRegisterBase;

    devExt->ReadStartingOffset =  devExt->ReadSoFar;

    //
    // Get requestor's virtual address of the buffer.  This is used by
    // IoMapTransfer() as an index into the buffer to track the progress
    // of the map operation.
    //
    baseVa = MmGetMdlVirtualAddress(irp->MdlAddress);

    //
    // Get the logical base address and length of a fragment of the 
    // requestor's buffer.
    //
    // Even though we are a Busmaster device, our device does not support
    // scatter/gather.  Thus, we can only use a single base address and length
    // at a time.  If the requestor's buffer has more fragments, we will
    // do additional DMA operations (one for each fragment) until the entire
    // transfer has been completed.
    //
    devExt->ReadPaToDevice = IoMapTransfer(devExt->ReadAdapter,
                                   irp->MdlAddress,
                                   MapRegisterBase,
                                   baseVa+(devExt->ReadSoFar),
                                   &devExt->ReadLength,
                                   FALSE);  // FALSE = READ from device


    //
    // Track the length of the requestor's buffer we've read so far.
    //
    devExt->ReadSoFar += devExt->ReadLength;

    //
    // Start the request on the device -- Base Address and Length
    // of this fragment are stored in the device extension
    //
    (VOID)KeSynchronizeExecution(devExt->InterruptObject,
                            OsrStartReadOnDevice,
                            DeviceObject);

    return(DeallocateObjectKeepRegisters);
}        


///////////////////////////////////////////////////////////////////////////////
//
//  OsrAdapterControlWrite
//
//    This is routine is called by the I/O Manager when the Adapter resources
//    (such as map registers) requested by the OsrStartWriteIrp function are
//    available for our use.
//
//  INPUTS:
//
//      DeviceObject - Address of the DEVICE_OBJECT for our device.
//  
//      MapRegisterBase - Base address of the Map registers that have been
//                      reserved by the I/O Manager and HAL for our use.
//
//      Context - address of the Write Irp for the operation to be started on the 
//              device.
//
//  OUTPUTS:
//
//      None.
//
//  RETURNS:
//
//    DeallocateObjectKeepRegisters - indicates that the map registers that
//            were allocated to us should not be deallocated at this time.
//            We will deallocate them with the Read operation completes.
//
//  IRQL:
//
//    This routine is called at IRQL_DISPATCH_LEVEL.
//
//  NOTES:
//
///////////////////////////////////////////////////////////////////////////////
IO_ALLOCATION_ACTION 
OsrAdapterControlWrite(IN PDEVICE_OBJECT DeviceObject, IN PIRP NotUsed, 
                                  IN PVOID MapRegisterBase, IN PVOID Context)
{
    PIRP irp = (PIRP) Context;
    PIO_STACK_LOCATION ioStack;
    POSR_DEVICE_EXT devExt;
    PUCHAR baseVa;

#if DBG
    DbgPrint("AdapterControlWrite: Irp = 0x%0x\n", irp);
#endif

    devExt = DeviceObject->DeviceExtension;

    ioStack = IoGetCurrentIrpStackLocation(irp);

    devExt->WriteLength = ioStack->Parameters.Write.Length - devExt->WriteSoFar;

#if DBG
    DbgPrint("AdapterControlWrite: Length remaining = %d. \n", devExt->WriteLength);
#endif

    //
    // Get set-up for the transfer
    //
    devExt->WriteMapRegBase = MapRegisterBase;

    baseVa = MmGetMdlVirtualAddress(irp->MdlAddress);

    devExt->WriteStartingOffset =  devExt->WriteSoFar;

    //
    // Get the base address and length of the segment to write.
    //
    devExt->WritePaToDevice = IoMapTransfer(devExt->WriteAdapter,
                                   irp->MdlAddress,
                                   MapRegisterBase,
                                   baseVa+(devExt->WriteSoFar),
                                   &devExt->WriteLength,
                                   TRUE);      // WriteToDevice

    //
    // Update the length transfered so far
    //
    devExt->WriteSoFar += devExt->WriteLength;

    //
    // Put the request on the device
    //
    (VOID)KeSynchronizeExecution(devExt->InterruptObject,
                            OsrStartWriteOnDevice,
                            DeviceObject);

    return(DeallocateObjectKeepRegisters);
}        


///////////////////////////////////////////////////////////////////////////////
//
//  OsrStartReadOnDevice
//
//      This function performs all the actual hardware manipulation to initiate
//      a new read request on the AMCC device.  When called, all resources
//      (mapping registers) have been allocated for the operation, and we have
//      a base address and length of a buffer fragment to be DMA'ed.
//
//  INPUTS:
//
//      DeviceObject - Address of the DEVICE_OBJECT for our device.
//  
//      BaseAddress  - Logical base address of the requestor's buffer fragment
//                      to be used as the base address of the transfer
//
//      Length - Length in bytes of this fragment to be transfered.
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
//      This routine is called at IRQL_DISPATCH_LEVEL.
//
//  NOTES:
//
//      When this routine is called, no other Read operations are in progress on
//      the device.
//
///////////////////////////////////////////////////////////////////////////////
BOOLEAN
OsrStartReadOnDevice(IN PVOID SynchronizeContext)
{
    ULONG temp;
    PDEVICE_OBJECT deviceObject = (PDEVICE_OBJECT)SynchronizeContext;
    PHYSICAL_ADDRESS baseAddress;
    ULONG length;
    POSR_DEVICE_EXT devExt = deviceObject->DeviceExtension;

    baseAddress = devExt->ReadPaToDevice;
    length = devExt->ReadLength;

#if DBG
    DbgPrint("StartReadOnDev: Reading BA = 0x%0x, Length = %d.\n",
                        baseAddress.LowPart, length);
#endif

    //
    // Pass the device the Physical Base Address of the buffer
    //
    ASSERT(!baseAddress.HighPart);

    WRITE_PORT_ULONG(devExt->AmccBaseRegisterAddress+MWAR_OFF,
                     baseAddress.LowPart);

    //
    // ...and the length of the read
    //
    WRITE_PORT_ULONG(devExt->AmccBaseRegisterAddress+MWTC_OFF, length);

    //
    // Tell the device to interrupt when the read is complete.
    //
    // NOTE: In this particular device, "read" operations from the
    // device are called "WRITE" operations... since they write to
    // MEMORY.  Thus, we set the INT_ON_WRITE bit in the Interrupt
    // CSR.
    //
    temp = READ_PORT_ULONG(devExt->AmccBaseRegisterAddress+ICSR_OFF);

#if DBG
    DbgPrint("StartDmaRead: Current INTCSR State:\n");
    OsrPrintIntcsr(temp);
#endif

    temp &= ~AMCC_INT_ACK_BITS;
    temp |= AMCC_INT_INT_ON_WRITE;
    
    WRITE_PORT_ULONG(devExt->AmccBaseRegisterAddress+ICSR_OFF, temp);

    //
    // Yeeeeha!  Start the request by settting the "Write Enable"
    // bit in the master CSR
    //
    temp = READ_PORT_ULONG(devExt->AmccBaseRegisterAddress+MCSR_OFF);
    temp &= (AMCC_MCSR_READ_ENABLE        |
                AMCC_MCSR_READ_FIFO_MGMT  |
                AMCC_MCSR_READ_PRIORITY   |
                AMCC_MCSR_WRITE_ENABLE    |
                AMCC_MCSR_WRITE_FIFO_MGMT |
                AMCC_MCSR_WRITE_PRIORITY);

    temp |= AMCC_MCSR_WRITE_ENABLE;

    WRITE_PORT_ULONG(devExt->AmccBaseRegisterAddress+MCSR_OFF, temp); 

    return(TRUE);
}    

///////////////////////////////////////////////////////////////////////////////
//
//  OsrStartWriteOnDevice
//
//      This function performs all the actual hardware manipulation to initiate
//      a new read request on the AMCC device.  When called, all resources
//      (mapping registers) have been allocated for the operation, and we have
//      a base address and length of a buffer fragment to be DMA'ed.
//
//  INPUTS:
//
//      DeviceObject - Address of the DEVICE_OBJECT for our device.
//  
//      BaseAddress  - Logical base address of the requestor's buffer fragment
//                      to be used as the base address of the transfer
//
//      Length - Length in bytes of this fragment to be transfered.
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
//    This routine is called at IRQL_DISPATCH_LEVEL.
//
//  NOTES:
//
//    When this routine is called, no other Write operations are in progress on
//    the device.
//
///////////////////////////////////////////////////////////////////////////////
BOOLEAN
OsrStartWriteOnDevice(IN PVOID SynchronizeContext)
{
    ULONG temp;
    PDEVICE_OBJECT deviceObject = (PDEVICE_OBJECT)SynchronizeContext;
    PHYSICAL_ADDRESS baseAddress;
    ULONG length;
    POSR_DEVICE_EXT devExt = deviceObject->DeviceExtension;

    baseAddress = devExt->WritePaToDevice;
    length = devExt->WriteLength;

#if DBG
    DbgPrint("StartWriteOnDev: Writing BA = 0x%0x, Length = %d.\n",
                        baseAddress.LowPart, length);
#endif

    //
    // Pass the device the Physical Base Address of the buffer...
    //
    ASSERT(!baseAddress.HighPart);

    WRITE_PORT_ULONG(devExt->AmccBaseRegisterAddress+MRAR_OFF,
                     baseAddress.LowPart);

    //
    // ...and the length of the write operation
    //
    WRITE_PORT_ULONG(devExt->AmccBaseRegisterAddress+MRTC_OFF, length);

    //
    // Request the device interrupt when the write operation is complete
    //
    temp = READ_PORT_ULONG(devExt->AmccBaseRegisterAddress+ICSR_OFF);

#if DBG
    DbgPrint("StartWriteOnDev: Current INTCSR State:\n");
    OsrPrintIntcsr(temp);
#endif

    temp &= ~AMCC_INT_ACK_BITS;
    temp |= AMCC_INT_INT_ON_READ;
    WRITE_PORT_ULONG(devExt->AmccBaseRegisterAddress+ICSR_OFF, temp);

    //
    // Yeeeeha!  Start the request by setting the appropriate enable bit.
    //
    temp = READ_PORT_ULONG(devExt->AmccBaseRegisterAddress+MCSR_OFF);
    temp &= (AMCC_MCSR_READ_ENABLE|
                AMCC_MCSR_READ_FIFO_MGMT|
                AMCC_MCSR_READ_PRIORITY|
                AMCC_MCSR_WRITE_ENABLE|
                AMCC_MCSR_WRITE_FIFO_MGMT|
                AMCC_MCSR_WRITE_PRIORITY);

    temp |= AMCC_MCSR_READ_ENABLE;

    WRITE_PORT_ULONG(devExt->AmccBaseRegisterAddress+MCSR_OFF, temp); 

    return(TRUE);
}    


///////////////////////////////////////////////////////////////////////////////
//
//  OsrProcessQueuedRequests
//
//      This interface checks the current state of the read and write
//      queues, and starts requests on the device if either are not
//      busy.
//
//  INPUTS:
//
//      devExt - Pointer to device extension of device to start
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
//
//  NOTES:
//
///////////////////////////////////////////////////////////////////////////////
VOID OsrProcessQueuedRequests(IN OUT POSR_DEVICE_EXT devExt)
{
    PVOID entry;
    PIRP irp;
    KIRQL oldIrql;

    //
    // See if there's something to start on the WRITE queue
    //
    KeAcquireSpinLock(&devExt->WriteQueueLock, &oldIrql);

    while ( !devExt->CurrentWriteIrp &&
            !IsListEmpty(&devExt->WriteQueue) ) {

        entry = RemoveHeadList(&devExt->WriteQueue);

        irp =  CONTAINING_RECORD(entry, IRP, Tail.Overlay.ListEntry);
#if DBG
        DbgPrint("OsrProcessQueued: IRP removed from WRITE queue = 0x%0x\n",irp);
#endif
        //
        // If this IRP is cancelled, cancel it now, without
        // initiating it on the device
        //
        if (irp->Cancel) {
#if DBG
            DbgPrint("OsrProcessQueued: CANCEL flag set in READ IRP removed from queue 0x%0x\n",irp);
#endif
            irp->IoStatus.Status = STATUS_CANCELLED;
            irp->IoStatus.Information = 0;

            //
            // Complete the request now
            //
            IoCompleteRequest(irp, IO_NO_INCREMENT);    

        } else {

            //
            // Since we do not cancel in-progress requests
            // on this device, we will reset the cancel
            // routine in the IRP to NULL.
            //
            IoSetCancelRoutine(irp, NULL);

            //
            // Make this IRP the current write IRP, and
            // start the request on the device.  This routine
            // sets devExt->CurrentWriteIrp
            //
            OsrStartWriteIrp(devExt->FunctionalDeviceObject, irp);                
        }

    }   // while (!devExt->CurrentWriteIrp && 
        //        !IsListEmpty(devExt->WriteQueue) )

    //
    // Drop the lock
    //
    KeReleaseSpinLock(&devExt->WriteQueueLock, oldIrql);

    //
    // See if there's something to start on the READ queue
    //
    KeAcquireSpinLock(&devExt->ReadQueueLock, &oldIrql);

    while ( !devExt->CurrentReadIrp &&
            !IsListEmpty(&devExt->ReadQueue) ) {

        entry = RemoveHeadList(&devExt->ReadQueue);

        irp =  CONTAINING_RECORD(entry, IRP, Tail.Overlay.ListEntry);
#if DBG
        DbgPrint("OsrProcessQueued: IRP removed from READ queue = 0x%0x\n",irp);
#endif
        //
        // If this IRP is cancelled, cancel it now, without
        // initiating it on the device
        //
        if (irp->Cancel) {
#if DBG
            DbgPrint("OsrProcessQueued: CANCEL flag set in READ IRP removed from queue 0x%0x\n",irp);
#endif
            irp->IoStatus.Status = STATUS_CANCELLED;
            irp->IoStatus.Information = 0;

            //
            // Complete the request now
            //
            IoCompleteRequest(irp, IO_NO_INCREMENT);    

        } else {

            //
            // Since we do not cancel in-progress requests
            // on this device, we will reset the cancel
            // routine in the IRP to NULL.
            //
            IoSetCancelRoutine(irp, NULL);

            //
            // Make this IRP the current read IRP, and
            // start the request on the device.  This routine
            // sets devExt->CurrentReadIrp
            //
            OsrStartReadIrp(devExt->FunctionalDeviceObject, irp);                
        }

    }   // while (!devExt->CurrentReadIrp && 
        //        !IsListEmpty(devExt->ReadQueue) )

    //
    // Drop the lock
    //
    KeReleaseSpinLock(&devExt->ReadQueueLock, oldIrql);


}
