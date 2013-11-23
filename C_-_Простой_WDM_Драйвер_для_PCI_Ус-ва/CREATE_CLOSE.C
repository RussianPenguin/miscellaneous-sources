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
//        CREATE_CLOSE.C
//
//    ABSTRACT:
//
//      This file contains the Create and Close dispatch entry points for the 
//      OSR Sample PCI Busmaster DMA device driver.
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
//  OsrCreateClose
//
//    This is the dispatch entry point for processing both IRP_MJ_CREATE
//    and IRP_MJ_CLOSE functions.  Since this is a simple device driver,
//    there's really nothing to do here by complete the requests with success.
//
//
//  INPUTS:
//
//      DeviceObject - Address of the DEVICE_OBJECT for our device.
//  
//      Irp - Address of the IRP representing the IRP_MJ_CREATE or IRP_MJ_CLOSE
//          call.
//
//  OUTPUTS:
//
//      None.
//
//  RETURNS:
//
//    STATUS_SUCCESS.   We never fail this function.        
//
//  IRQL:
//
//      This routine is called at IRQL PASSIVE_LEVEL.
//
//  NOTES:
//
///////////////////////////////////////////////////////////////////////////////
NTSTATUS OsrCreateClose(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
    PIO_STACK_LOCATION ioStack = IoGetCurrentIrpStackLocation(Irp);
    POSR_DEVICE_EXT devExt = DeviceObject->DeviceExtension;

#if DBG
    DbgPrint("CreateClose: called");
#endif

    //
    // Nothing much to do....
    //
    Irp->IoStatus.Status = STATUS_SUCCESS;

    //
    // If the current device state doesn't allow creates, change
    // the status
    //
    if(ioStack->MajorFunction == IRP_MJ_CREATE &&
        devExt->State < STATE_ALL_BELOW_FAIL) {

        Irp->IoStatus.Status = STATUS_UNSUCCESSFUL;
    }

    Irp->IoStatus.Information = 0;

    IoCompleteRequest(Irp, IO_NO_INCREMENT);
    
#if DBG
    DbgPrint("CreateClose: exit");
#endif

    return(STATUS_SUCCESS);
}
