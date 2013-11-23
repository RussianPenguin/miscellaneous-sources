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
//        OSR_IOCTL.H
//
//    ABSTRACT:
//
//      This file contains IOCTL definitions for the OSR Sample
//      PCI Busmaster DMA device driver for the AMCC 5933 chip.
//
//		The point of putting these IOCTL definitions in a file all by themselves
//		is that the file can be used by both the driver and by user applications
//		that might use these IOCTLs.  User applications need to ensure that
//		winioctl.h is #included before this file.
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
// This header file contains all declarations shared between driver and user
// applications.
//

#ifndef __OSR_IOCTL_H__
#define __OSR_IOCTL_H__ (1)

//
// The following value is arbitrarily chosen from the space defined by Microsoft
// as being "for non-Microsoft use"
//
#define FILE_DEVICE_OSR 0xCF53

//
// Device control codes - values between 2048 and 4095 arbitrarily chosen
//
#define IOCTL_OSR_RESET CTL_CODE(FILE_DEVICE_OSR, 2049, METHOD_BUFFERED, FILE_ANY_ACCESS)

#endif /* __OSR_IOCTL_H__ */

