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
//        ISR_DPC.C
//
//    ABSTRACT:
//
//      This file contains the ISR and DPC for the OSR Sample
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

///////////////////////////////////////////////////////////////////////////////
//
//  OsrHandleInterrupt
//
//      When the AMCC device generates an interrupt, this function is called.
//      Note that in our simple model of the world here, every transfer is
//      completed successfully.  We just don't bother with error detection
//      and handling.  If you wanted this to be a REAL driver, you'd have to
//      do the appropriate error detection and handling.
//
//  INPUTS:
//
//      Interupt - Address of the KINTERRUPT Object for our device.
//  
//      ServiceContext - Address of our device extension.
//
//  OUTPUTS:
//
//      None.
//
//  RETURNS:
//
//      TRUE if our device is interrupting, FALSE otherwise.
//
//  IRQL:
//
//      This routine is called at IRQL == DIRQL.
//
//  NOTES:
//
//      As is true for all ISR's in NT, this routine is called with the
//      interrupt spin lock held.
//
///////////////////////////////////////////////////////////////////////////////
BOOLEAN OsrHandleInterrupt(PKINTERRUPT Interupt, PVOID ServiceContext)
{
    BOOLEAN ourDeviceInterrupting = FALSE;
    POSR_DEVICE_EXT devExt = (POSR_DEVICE_EXT)ServiceContext;
    ULONG intRegister;
    ULONG csrRegister;

#if DBG
    DbgPrint("OSRPCI: ISR entered\n");
#endif    
    
    //
    // Get the current interrupt CSR from our device
    //
    intRegister = READ_PORT_ULONG(devExt->AmccBaseRegisterAddress+ICSR_OFF);

#if DBG
    DbgPrint("*****************AMCC INTCSR = 0x%0x\n",intRegister);
    OsrPrintIntcsr(intRegister);
#endif


    //
    // Is our device presently interrupting?
    //
    if (intRegister & AMCC_INT_INTERRUPTED) {
    
        //
        // Yes, it is!
        //
        ourDeviceInterrupting = TRUE;

#if DBG
        DbgPrint("\tInterrupt is ours.\n");
#endif

        //
        // Store away some context so when we get to our DpcForIsr we'll know
        // what caused the interrupt.  Specifically, we accumulate bits in the
        // "IntCsr" field of our device extenstion indicating what interrupts
        // we've seen from the device.  Note that since we support simultaneous
        // read and write DMA operations, we could get both a read complete
        // interrupt and a write complete interrupt before the DpcForIsr has
        // had a chance to execute.  Thus, we must carefully ACCUMULATE the
        // bits.
        //
        // N.B.  We guard these bits with the Interrupt Spin Lock.  The bits
        //       cannot be set or cleared unless holding that lock.
        //
        devExt->IntCsr |= (intRegister & AMCC_INT_ACK_BITS);
                        
        //
        // Acknowledge the interrupt on the device
        //
        WRITE_PORT_ULONG(devExt->AmccBaseRegisterAddress+ICSR_OFF, intRegister);

        //
        // IF the interrupt was as a result of a READ or WRITE operation
        // completing (either with success or error) request our DpcForIsr.
        //
        if(intRegister & (AMCC_INT_READ_COMP | AMCC_INT_WRITE_COMP))  {

#if DBG
            DbgPrint("Requesting DPC\n");
#endif
            IoRequestDpc(devExt->FunctionalDeviceObject, 0, NULL);
        }
        
    }

    return(ourDeviceInterrupting);
}
    


//
// Synchronize Functions
//

///////////////////////////////////////////////////////////////////////////////
//
//  ReadIsDone
//
//    This is a synchronize function, called with the ISR spinlock held, that 
//    checks and potentially updates the READ COMPLETE bit in the IntCsr copy
//    that we keep in our device extension.  These bits must be updated under
//    lock.
//
//  INPUTS:
//
//    ServiceContext - Address of our device extension.
//
//  OUTPUTS:
//
//      None.
//
//  RETURNS:
//
//      TRUE, if a read is complete, FALSE otherwise.
//
//  IRQL:
//
//      This routine is called at IRQL == DIRQL, specifically the Synchronize
//      IRQL for the device.
//
//  NOTES:
//
//      Remember: A read operation to us is actually called a WRITE operation
//                on the AMCC device.  Ugh.  HARDWARE people!
//
///////////////////////////////////////////////////////////////////////////////
BOOLEAN
ReadIsDone(IN PVOID SynchronizeContext)
{
    POSR_DEVICE_EXT devExt = (POSR_DEVICE_EXT)SynchronizeContext;

    //
    // Is a READ operation complete on the device?
    // (Yes, the correct bit to check is _WRITE_COMP!)
    //
    if(devExt->IntCsr & AMCC_INT_WRITE_COMP)  {

        devExt->IntCsr &=  ~AMCC_INT_WRITE_COMP;

        return(TRUE);
    }
        
   return(FALSE);
}    


///////////////////////////////////////////////////////////////////////////////
//
//  WriteIsDone
//
//    This is a synchronize function, called with the ISR spinlock held, that 
//    checks and potentially updates the WRITE COMPLETE bit in the IntCsr copy
//    that we keep in our device extension.  These bits must be updated under
//    lock.
//
//  INPUTS:
//
//    ServiceContext - Address of our device extension.
//
//  OUTPUTS:
//
//      None.
//
//  RETURNS:
//
//      TRUE, if a write is complete, FALSE otherwise.
//
//  IRQL:
//
//      This routine is called at IRQL == DIRQL, specifically the Synchronize
//      IRQL for the device.
//
//  NOTES:
//
//      Remember: A write operation to us is actually called a READ operation
//                on the AMCC device.  Go figure...
//
///////////////////////////////////////////////////////////////////////////////
BOOLEAN
WriteIsDone(IN PVOID SynchronizeContext)
{
    POSR_DEVICE_EXT devExt = (POSR_DEVICE_EXT)SynchronizeContext;

    //
    // Is a WRITE operation complete on the device?
    // (Yes, the correct bit to check is _READ_COMP!)
    //
    if(devExt->IntCsr & AMCC_INT_READ_COMP)  {

        devExt->IntCsr &=  ~AMCC_INT_READ_COMP;

        return(TRUE);
    }
        
   return(FALSE);
}    

///////////////////////////////////////////////////////////////////////////////
//
//  OsrDpcForIsr
//
//      This is the DPC for ISR function.  It is called as a result of a
//      call to IoRequestDpc() in the interrupt service routine.  It handles
//      request completion, and propagation of the driver (i.e. checking the
//      queue and starting the next queued request if one is pending).
//
//  INPUTS:
//
//    Dpc - Address of our DPC Object.
//
//    Unused - Unused.
//
//    Context - Address of our device extension.
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
//    This routine is called at IRQL == IRQL_DISPATCH_LEVEL
//
//  NOTES:
//
///////////////////////////////////////////////////////////////////////////////
VOID
OsrDpcForIsr(PKDPC Dpc, PDEVICE_OBJECT DeviceObject, PIRP Unused, PVOID Context)
{
    POSR_DEVICE_EXT devExt = (POSR_DEVICE_EXT) DeviceObject->DeviceExtension;
    PLIST_ENTRY entry;
    PIRP irp;
    PVOID baseVa;
    ULONG mapRegsNeeded;
       
#if DBG
    DbgPrint("----------OSRPCI DPC\n");
#endif

    //
    // Check to see if a read or Write operation has completed.  Recall that
    // this device can have both a single read and a single write in progress
    // simultaneously.
    // 
    // For each read or write complete, we need to:
    //
    //      o See if the entire buffer has been DMA'ed.  It is possible that
    //          due to physical buffer fragmentation (since this driver does
    //          not support scatter/gather), or due to map register limitations,
    //          we have had to break the user's request up into multiple DMA
    //          transfers.
    //
    //      o If the entire buffer has not been DMA'ed, and the current request
    //          has not been cancelled, we set up another DMA transfer, starting
    //          from where the previous DMA left off. 
    //
    //      o If the entire buffer HAS been DMA'ed, or the current request has
    //          been cancelled, we complete the request with the appropriate
    //          status. We then try to remove an entry from the relevant queue
    //          and start it on the device.  If we happen to remove an IRP with
    //          the cancel flag set, we cancel it, and try to get another IRP
    //          from the queue.  Note this cancel check is required to catch
    //          the case of the IRP being cancelled while we are in the DpcForIsr.
    //  
    // Note that in our simple model of the world, transfer complete means
    // transfer SUCCESSFULLY complete.  This sample driver does not attempt
    // error detection, reporting, or recovery.
    //

    //
    // Write complete??
    //
    if( KeSynchronizeExecution(devExt->InterruptObject,
                                WriteIsDone,
                                devExt) )  {
#if DBG
        DbgPrint("---Write Done\n");
#endif

        //
        // Get the write queue lock
        //
        KeAcquireSpinLockAtDpcLevel(&devExt->WriteQueueLock);

        //
        // Get the address of the in-progress request
        //
        irp = devExt->CurrentWriteIrp;

        //
        // See if there's an entry on the Write queue that needs to be
        // completed or continued.
        //
        if (irp)  {
            
            //
            // There is an IRP currently in progress.
            //
            baseVa = (PUCHAR)MmGetMdlVirtualAddress(irp->MdlAddress)+
                                    devExt->WriteStartingOffset;

            IoFlushAdapterBuffers(devExt->WriteAdapter,
                                 irp->MdlAddress,
                                 devExt->WriteMapRegBase,
                                 baseVa,
                                 devExt->WriteSoFar-devExt->WriteStartingOffset,
                                 TRUE);     // writeToDevice == TRUE

            //
            // Tell the HAL the map registers we were using are free
            //
            IoFreeMapRegisters(devExt->WriteAdapter,
                               devExt->WriteMapRegBase,
                               devExt->MapRegsThisWrite);

            //
            // See if there's more of the user's buffer left for us to DMA.
            // Be sure the request was not cancelled whilst in progress.
            //
            if( (devExt->WriteTotalLength - devExt->WriteSoFar) &&
                (!irp->Cancel) )  {
#if DBG
                DbgPrint("---CONTINUING:\n");
#endif
                //
                // The user buffer has NOT been completely DMA'ed.
                // How many map regs can we use this time?
                //
                mapRegsNeeded = 
                    ADDRESS_AND_SIZE_TO_SPAN_PAGES((PUCHAR)MmGetMdlVirtualAddress(irp->MdlAddress)+
                                 devExt->WriteSoFar,
                                 devExt->WriteTotalLength-devExt->WriteSoFar);
                    
                devExt->MapRegsThisWrite = ((mapRegsNeeded > devExt->WriteMapRegsGot) ? 
                                          devExt->WriteMapRegsGot : mapRegsNeeded);

#if DBG
                DbgPrint("Continuing: %d. map regs this xfer\n",
                        devExt->MapRegsThisWrite);
#endif

                IoAllocateAdapterChannel(devExt->WriteAdapter,
                                         DeviceObject, 
                                         devExt->MapRegsThisWrite,
                                         OsrAdapterControlWrite,
                                         irp);
            } else  {

                //
                // We're going to complete this request
                //

                //
                // Information field contains number of bytes written
                //
                irp->IoStatus.Information = devExt->WriteTotalLength;

                // and all requests are completed with success...
                //
                irp->IoStatus.Status = STATUS_SUCCESS;


                //
                //
                // ...unless the in-progress I/O operation is cancelled.
                //
                if(irp->Cancel == TRUE)  {

#if DBG
                    DbgPrint("---CANCEL flag set in WRITE IRP to be completed!\n");
#endif
                    irp->IoStatus.Status = STATUS_CANCELLED;
                    irp->IoStatus.Information = 0;

                }

#if DBG
                DbgPrint("---Completing Write IRP 0x%0x\n",irp);
#endif
                //
                // Complete the request now
                //
                IoCompleteRequest(irp, IO_NO_INCREMENT);    

                //
                // No write in progress right now
                //
                devExt->CurrentWriteIrp = NULL;

                //
                // Count one less request...
                //
                OsrRequestDecrement(devExt);

                //
                // N.B.  We're STILL HOLDING the write queue lock.
                //

                //
                // Keep removing entries until we start one.
                //
                while (devExt->State < STATE_ALL_BELOW_DRAIN &&
                        !devExt->CurrentWriteIrp &&
                        !IsListEmpty(&devExt->WriteQueue) ) {

                    entry = RemoveHeadList(&devExt->WriteQueue);

                    irp =  CONTAINING_RECORD(entry, IRP, Tail.Overlay.ListEntry);
#if DBG
                    DbgPrint("---IRP removed from queue in DpcForIsr = 0x%0x\n",irp);
#endif
                    //
                    // If this IRP is cancelled, cancel it now, without
                    // initiating it on the device
                    //
                    if (irp->Cancel) {
#if DBG
                        DbgPrint("---CANCEL flag set in IRP removed from queue 0x%0x\n",irp);
#endif
                        irp->IoStatus.Status = STATUS_CANCELLED;
                        irp->IoStatus.Information = 0;

                        //
                        // Complete the request now
                        //
                        IoCompleteRequest(irp, IO_NO_INCREMENT);    

                        //
                        // Count one less request...
                        //
                        OsrRequestDecrement(devExt);

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
                        OsrStartWriteIrp(DeviceObject, irp);                
                    }

                }   // while (!devExt->CurrentWriteIrp && 
                    //        !IsListEmpty(devExt->WriteQueue) )
            }
        }                              

        //
        // Drop the lock
        //
        KeReleaseSpinLockFromDpcLevel(&devExt->WriteQueueLock);
    }

    //
    // Read Complete??
    //
    if( KeSynchronizeExecution(devExt->InterruptObject,
                                ReadIsDone,
                                devExt) )  {

#if DBG
        DbgPrint("---Read Done\n");
#endif

        //
        // Get the read queue lock.  We'll hold it throughout the entire
        // process.
        //
        KeAcquireSpinLockAtDpcLevel(&devExt->ReadQueueLock);

        //
        // Get the address of the in-progress request
        //
        irp = devExt->CurrentReadIrp;

        //
        // See if there's an entry on the Read queue that needs to be
        // completed or continued.
        //
        if (irp)  {
            
            //
            // There is an IRP currently in progress.
            //
            baseVa = (PUCHAR)MmGetMdlVirtualAddress(irp->MdlAddress)+
                                    devExt->ReadStartingOffset;

            IoFlushAdapterBuffers(devExt->ReadAdapter,
                                 irp->MdlAddress,
                                 devExt->ReadMapRegBase,
                                 baseVa,
                                 devExt->ReadSoFar-devExt->ReadStartingOffset,
                                 FALSE);     // read == FALSE

            //
            // Tell the HAL the map registers we were using are free
            //
            IoFreeMapRegisters(devExt->ReadAdapter,
                               devExt->ReadMapRegBase,
                               devExt->MapRegsThisRead);

            //
            // See if there's more of the user's buffer left for us to DMA.
            // Be sure the request was not cancelled whilst in progress.
            //
            if( (devExt->ReadTotalLength - devExt->ReadSoFar) &&
                (!irp->Cancel) )  {
#if DBG
                DbgPrint("---CONTINUING:\n");
#endif
                //
                // The user buffer has NOT been completely DMA'ed.
                // How many map regs can we use this time?
                //
                mapRegsNeeded = 
                    ADDRESS_AND_SIZE_TO_SPAN_PAGES((PUCHAR)MmGetMdlVirtualAddress(irp->MdlAddress)+
                                 devExt->ReadSoFar,
                                 devExt->ReadTotalLength-devExt->ReadSoFar);
                    
                devExt->MapRegsThisRead = ((mapRegsNeeded > devExt->ReadMapRegsGot) ? 
                                          devExt->ReadMapRegsGot : mapRegsNeeded);

#if DBG
                DbgPrint("Continuing: %d. map regs this xfer\n",
                        devExt->MapRegsThisRead);
#endif

                IoAllocateAdapterChannel(devExt->ReadAdapter,
                                         DeviceObject, 
                                         devExt->MapRegsThisRead,
                                         OsrAdapterControlRead,
                                         irp);
            } else  {

                //
                // We're going to complete this request
                //

                //
                // Information field contains number of bytes written
                //
                irp->IoStatus.Information = devExt->ReadTotalLength;

                // and all requests are completed with success...
                //
                irp->IoStatus.Status = STATUS_SUCCESS;


                //
                //
                // ...unless the in-progress I/O operation is cancelled.
                //
                if(irp->Cancel == TRUE)  {

#if DBG
                    DbgPrint("---CANCEL flag set in READ IRP to be completed!\n");
#endif
                    irp->IoStatus.Status = STATUS_CANCELLED;
                    irp->IoStatus.Information = 0;

                }

#if DBG
                DbgPrint("---Completing Read IRP 0x%0x\n",irp);
#endif
                //
                // Complete the request now
                //
                IoCompleteRequest(irp, IO_NO_INCREMENT);    

                //
                // No read in progress right now
                //
                devExt->CurrentReadIrp = NULL;

                //
                // Count one less request...
                //
                OsrRequestDecrement(devExt);

                //
                // N.B.  We're STILL HOLDING the read queue lock.
                //

                //
                // Keep removing entries until we start one.
                //
                while ( devExt->State < STATE_ALL_BELOW_DRAIN &&
                        !devExt->CurrentReadIrp &&
                        !IsListEmpty(&devExt->ReadQueue) ) {

                    entry = RemoveHeadList(&devExt->ReadQueue);

                    irp =  CONTAINING_RECORD(entry, IRP, Tail.Overlay.ListEntry);
#if DBG
                    DbgPrint("---IRP removed from queue in DpcForIsr = 0x%0x\n",irp);
#endif
                    //
                    // If this IRP is cancelled, cancel it now, without
                    // initiating it on the device
                    //
                    if (irp->Cancel) {
#if DBG
                        DbgPrint("---CANCEL flag set in IRP removed from queue 0x%0x\n",irp);
#endif
                        irp->IoStatus.Status = STATUS_CANCELLED;
                        irp->IoStatus.Information = 0;

                        //
                        // Complete the request now
                        //
                        IoCompleteRequest(irp, IO_NO_INCREMENT);    

                        //
                        // Count one less request...
                        //
                        OsrRequestDecrement(devExt);

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
                        OsrStartReadIrp(DeviceObject, irp);                
                    }

                }   // while (!devExt->CurrentReadIrp && 
                    //        !IsListEmpty(devExt->ReadQueue) )
            }
        }                              

        //
        // Drop the read queue lock
        //
        KeReleaseSpinLockFromDpcLevel(&devExt->ReadQueueLock);
    }
    

    //
    // Finally, before we leave, check to see if we're leaving
    // the DpcForIsr with NO requests in progress.  IF we are,
    // then it's safe to stop the device.
    //
    KeAcquireSpinLockAtDpcLevel(&devExt->ReadQueueLock);
    KeAcquireSpinLockAtDpcLevel(&devExt->WriteQueueLock);

    if( devExt->CurrentReadIrp == NULL &&
        devExt->CurrentWriteIrp == NULL) {
        
        KeSetEvent(&devExt->StopEvent,0,FALSE);

    }

    KeReleaseSpinLockFromDpcLevel(&devExt->WriteQueueLock);
    KeReleaseSpinLockFromDpcLevel(&devExt->ReadQueueLock);

    //
    // We're outa here...
    //
    return;
}

