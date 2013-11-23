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
//        MISC.C
//
//    ABSTRACT:
//
//      This file contains miscellaneous routines used by the
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
//  OsrDeviceControl
//
//    This is the dispatch entry point for processing IRP_MJ_DEVICE_CONTROL
//    Irps.  
//
//
//  INPUTS:
//
//      DeviceObject - Address of the DEVICE_OBJECT for our device.
//  
//      Irp - Address of the IRP representing the IRP_MJ_DEVICE_CONTROL call.
//
//  OUTPUTS:
//
//      None.
//
//  RETURNS:
//
//    STATUS_SUCCESS if success, otherwise an appropriate status is returned.
//
//  IRQL:
//
//    This routine is called at IRQL_PASSIVE_LEVEL.
//
//  NOTES:
//
//    We presently only support the IOCTL_OSR_RESET IOCTL.
//
///////////////////////////////////////////////////////////////////////////////
NTSTATUS OsrDeviceControl(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
    PIO_STACK_LOCATION ioStack;
    NTSTATUS code;
    POSR_DEVICE_EXT devExt = DeviceObject->DeviceExtension;
    
    ioStack = IoGetCurrentIrpStackLocation(Irp);

    OsrRequestIncrement(devExt);

    //
    // Set some appropriate defaults
    //
    code = STATUS_SUCCESS;
    Irp->IoStatus.Information = 0;

    //
    // Since IOCTLs to this device are synchronously processed,
    // we will only allow IOCTLs when we're in STARTED state.
    //
    if (devExt->State != STATE_STARTED) {

        code = STATUS_UNSUCCESSFUL;

    } else {

        //
        // Switch based on the I/O Control code
        //
        switch (ioStack->Parameters.DeviceIoControl.IoControlCode) {

            case IOCTL_OSR_RESET:
                  
                OsrResetAdapter(DeviceObject, FALSE);

                break;            

            default:
                
                //
                // This is the case for a bogus request code.
                //
                code = STATUS_INVALID_PARAMETER;

#if DBG
                DbgPrint("OsrDeviceControl: Invalid IOCTL code 0x%0x\n",
                              ioStack->Parameters.DeviceIoControl.IoControlCode);
#endif

                break;
        }
    }
    
    //
    // Complete the I/O Request
    //
    Irp->IoStatus.Status = code;
   
    IoCompleteRequest(Irp, IO_NO_INCREMENT);
 
    OsrRequestDecrement(devExt);

    return(code);
}

///////////////////////////////////////////////////////////////////////////////
//
//  OsrResetAdapter
//
//    This function performs a MASTER RESET.  Callers should not presume
//    the state of the adapter is maintained after this call.  In-progress
//    transfers are shut-down, pending interrupts are cancelled.
//
//  INPUTS:
//
//      DeviceObject - Address of the DEVICE_OBJECT for our device.
//
//      EnableInts - Unused (obsolete).
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
//      This routine is called at IRQL PASSIVE_LEVEL.
//
//  NOTES:
//
///////////////////////////////////////////////////////////////////////////////
VOID OsrResetAdapter(PDEVICE_OBJECT devobj,BOOLEAN EnableInts)
{
    ULONG counter;
    POSR_DEVICE_EXT devExt = (POSR_DEVICE_EXT)(devobj)->DeviceExtension;
    LARGE_INTEGER timeToWait;
    ULONG temp;

#if DBG
      DbgPrint("OsrResetAdapter called\n");
#endif
    
    if(devExt->State < STATE_ALL_BELOW_NO_HW) {

#if DBG
        DbgPrint("OsrResetAdapter: State indicates no hw access.\n");
#endif
        return;

    }

    //
    // Request a reset
    //
    WRITE_PORT_ULONG(devExt->AmccBaseRegisterAddress+MCSR_OFF,
                AMCC_MCSR_MBX_RESET |
                AMCC_MCSR_ATOP_RESET|
                AMCC_MCSR_PTOA_RESET|
                AMCC_MCSR_ADDON_RESET);
 
    //
    // Wait for 10 milliseconds, to make sure the "add on" is properly
    // reset....  This is not really necessary for this driver, but it's
    // pretty standard for REAL devices.
    //
    timeToWait.QuadPart = (LONGLONG) -100000; // waits for 10 milliseconds

    KeDelayExecutionThread(KernelMode, FALSE, &timeToWait);

    //
    // Clear the reset state
    //
    WRITE_PORT_ULONG(devExt->AmccBaseRegisterAddress+MCSR_OFF, 0x00);
    
    //
    // Get the Interrupt control/status register
    //
    temp = READ_PORT_ULONG(devExt->AmccBaseRegisterAddress+ICSR_OFF);
    temp &= AMCC_INT_ACK_BITS;
    WRITE_PORT_ULONG(devExt->AmccBaseRegisterAddress+ICSR_OFF, temp);

    //
    // The following suspends the current thread for ten milliseconds; since it is
    // designed to de-schedule, this is not antisocial (we are not busy-waiting).
    //
    timeToWait.QuadPart = (LONGLONG) -100000; // waits for 10 milliseconds

    KeDelayExecutionThread(KernelMode, FALSE, &timeToWait);
}
