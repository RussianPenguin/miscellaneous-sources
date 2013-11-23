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
//        OSR_PCI.H
//
//    ABSTRACT:
//
//      This file contains PCI definitions for the OSR Sample
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
#ifndef __OSR_PCI_H__
#define __OSR_PCI_H__ (1) // suppress duplicate loading of this file

#include <WDM.H>

#include "OSR-IOCTL.h"

//
// These are AMCC's Vendor ID and Device ID
//
// (Note: The VID and DID pre-programmed into the
//  PCI Config ROM on the AMCC 5933 Eval Board changes
//  from time to time.  So this may not be the
//  correct VID and DID for every board).
//
#define OSR_PCI_VID 0x10E8
#define OSR_PCI_DID 0x4750

//
// Maxmimum transfer size supported
// 64K sounds right.
// 
#define OSR_PCI_MAX_TXFER	65535

//
// The watchdog interval.  Any request pending
// for this number of seconds is subject to
// being cancelled.  Note, this is a ONE SECOND GRANULARITY TIMER
// so provide a length of time at least one second greater
// than the minimum.
//
#define OSR_WATCHDOG_INTERVAL	5


//
// Device State definitions
//
// These values are used to track the state of the device
// with regard to PnP events.
//
// NOTE: The code makes assumptions about the order of these
// states, and the fact that their values are in the high
// word of a longword.
//
//

//
// We use a set of dummy states to delineate the actions we take
// on receipt and completion of an IRP.  These also appear below.
//

//
// In STATE_REMOVED, we immediately fail any received I/O requests
//
#define STATE_REMOVED           0X00000000

//
// In STATE_SURPRISE_REMOVED, we immediately fail all incoming requests
//
#define STATE_SURPRISE_REMOVED   0x00010000

//
// In STATE_NEVER_STARTED, we also immediately fail all incoming requests
//
#define STATE_NEVER_STARTED     0x00020000

//
// Dummy State -- When the state is < this value, no H/W access is
// allowed
//
#define STATE_ALL_BELOW_NO_HW   0x00030000	// ******************

//
// In STATE_REMOVE_PENDING, we also immediately fail all incoming requests
//
#define STATE_REMOVE_PENDING    0x00100000

//
// Dummy state -- When an IRP arrives at the driver, if the current
// device state is below this value, it is immediately failed
//
#define STATE_ALL_BELOW_FAIL    0x00FF0000	// ******************

//
// In STATE_STARTED, requests are processed and removed from the
// queues normally
//
#define STATE_STARTED           0X01000000

//
// Dummy state -- When an IRP arrives at the driver, if the current
// device state is above this value, it is queued, not initiated on
// the device (even if the device is free)
//
#define STATE_ALL_ABOVE_QUEUE   0x0FFF0000	// ******************

//
// Dummy State -- When an IRP is COMPLETED on the device, if
// the device state is below this value, we'll start another
// IRP in an attempt to drain the queue of pending requests.
//
#define STATE_ALL_BELOW_DRAIN   STATE_ALL_ABOVE_QUEUE	// ******************

//
// In STATE_STOP_PENDING, we queue incoming requests
//
#define STATE_STOP_PENDING      0x10000000

//
// In STATE_STOPPED, we queue incoming requests
//
#define STATE_STOPPED           0x10010000


//
// Device Extension
//
// This is the per-device component of the device object.
//
typedef struct
{
    //
    // Adapter information
    //
	PDMA_ADAPTER		ReadAdapter;
	ULONG				ReadMapRegsGot;
	PDMA_ADAPTER		WriteAdapter;
	ULONG				WriteMapRegsGot;

	//
	// Device information
	//
	PDEVICE_OBJECT		FunctionalDeviceObject;
	PDEVICE_OBJECT		PhysicalDeviceObject;
	PDEVICE_OBJECT		DeviceToSendIrpsTo;

	//
	// Data structure elements for Read IRPs
	//
	KSPIN_LOCK			ReadQueueLock;
	LIST_ENTRY			ReadQueue;

	//
	// Pending READ information
	//
	PIRP				CurrentReadIrp;
	PHYSICAL_ADDRESS	ReadPaToDevice;
	ULONG				ReadLength;
	ULONG				ReadTotalLength;
	ULONG				MapRegsThisRead;
	ULONG				ReadSoFar;
	ULONG				ReadStartingOffset;
	PVOID				ReadMapRegBase;

	//
	// Data structure elements for Write IRPs
	//
	KSPIN_LOCK			WriteQueueLock;
	LIST_ENTRY			WriteQueue;

	//
	// Pending WRITE information
	//
	PIRP				CurrentWriteIrp;
	PHYSICAL_ADDRESS	WritePaToDevice;
	ULONG				WriteLength;
	ULONG				WriteTotalLength;
	ULONG				MapRegsThisWrite;
	ULONG				WriteSoFar;
	ULONG				WriteStartingOffset;
	PVOID				WriteMapRegBase;

	//
	// Interrupt Object
	//
	PKINTERRUPT			InterruptObject;

	//
	// PCI Configuration infomration; once set at configuration time,
	// this information remains the same.
	//
	INTERFACE_TYPE		InterfaceType;
	ULONG				BusType;
	ULONG				BusNumber;
	ULONG				MapRegsGot;
	UCHAR				InterruptLevel;
	ULONG				InterruptVector;
	ULONG				InterruptAffinity;
	ULONG				InterruptMode;
	BOOLEAN				MappedPorts;

	//
	// PNP Events
	//
	KEVENT				StartEvent;
    KEVENT              StopEvent;
	KEVENT				RemoveEvent;

    //
    // Device State for PnP Purposes
    //
    ULONG               State;

	//
	// PNP Flags
	//
	BOOLEAN				Removed;
	BOOLEAN				Started;
	BOOLEAN				HoldNewRequests;

	// 
	// Power States
	//
	SYSTEM_POWER_STATE	SystemPowerState;
	DEVICE_POWER_STATE	DevicePowerState;

	//
	// Outstanding I/O counters
	//
	ULONG				OutstandingIO;

	//
	// Adapter's port base address
	//
	PULONG				AmccBaseRegisterAddress;

	//
	// COPY of Read and Write complete bits from INTCSR
	// in device.  ***NOTE: ACCESSED ONLY WHILE HOLDING
	// THIS DEVICE'S INTERRUPT SPIN LOCK***
	//
	ULONG				IntCsr;

} OSR_DEVICE_EXT, *POSR_DEVICE_EXT;

//
// Structures used for power configuration.
//
typedef struct _FDO_POWER_CONTEXT
{
	POWER_STATE_TYPE	newPowerType;
	POWER_STATE			newPowerState;
} FDO_POWER_CONTEXT, *PFDO_POWER_CONTEXT;

//
// The following offsets describe the layout of the control registers
// for the AMCC controller chip.
//
// Note that each register is a LONGword, and that these offsets are
// offsets from DeviceExtension->AmccBaseRegisterAddress, which is
// a PULONG.  Thus, each of these offsets is in terms of LONGWORDS,
// not bytes.
//
#define OMB1_OFF 0x0
#define OMB2_OFF 0x1
#define OMB3_OFF 0x2
#define OMB4_OFF 0x3
#define IMB1_OFF 0x4
#define IMB2_OFF 0x5
#define IMB3_OFF 0x6
#define IMB4_OFF 0x7
#define FIFO_OFF 0x8
#define MWAR_OFF 0x9
#define MWTC_OFF 0xA
#define MRAR_OFF 0xB
#define MRTC_OFF 0xC
#define MBEF_OFF 0xD
#define ICSR_OFF 0xE
#define MCSR_OFF 0xF

//
// MCSR Register Bits
//
#define AMCC_MCSR_NVRAM_CTRL	(7<<29)
#define AMCC_MCSR_FIFO_LOOP		(1<<28)

#define AMCC_MCSR_MBX_RESET		(1<<27)
#define AMCC_MCSR_ATOP_RESET    (1<<26)
#define AMCC_MCSR_PTOA_RESET    (1<<25)
#define AMCC_MCSR_ADDON_RESET	(1<<24)

#define AMCC_MCSR_NVRAM_ADDR	0x00FF0000

#define AMCC_MCSR_READ_MULT_ENA	(1<<15)
#define AMCC_MCSR_READ_ENABLE	(1<<14)
#define AMCC_MCSR_READ_FIFO_MGMT (1<<13)
#define AMCC_MCSR_READ_PRIORITY	(1<<12)

#define	AMCC_MCSR_RESERVED11	(1<<11)
#define AMCC_MCSR_WRITE_ENABLE	(1<<10)
#define AMCC_MCSR_WRITE_FIFO_MGMT (1<<9)
#define AMCC_MCSR_WRITE_PRIORITY (1<<8)

#define AMCC_MCSR_ATOP_COUNT_ZERO (1<<7)
#define AMCC_MCSR_PTOA_COUNT_ZERO (1<<6)
#define AMCC_MCSR_ATOP_FIFO_EMPTY (1<<5)
#define AMCC_MCSR_ATOP_FIFO_4WORDS (1<<4)

#define AMCC_MCSR_ATOP_FIFO_FULL (1<<3)
#define AMCC_MCSR_PTOA_FIFO_EMPTY (1<<2)
#define AMCC_MCSR_PTOA_FIFO_4SPACES (1<<1)
#define AMCC_MCSR_PTOA_FIFO_FULL (1<<0)

//
// INTCSR Register Bits
//
#define AMCC_INT_OUT_FIFO_CTRL		(1<<31)
#define AMCC_INT_IN_FIFO_CTRL		(1<<30)
#define AMCC_INT_FIFO_ADVA_BYTE0		0
#define	AMCC_INT_FIFO_ADVA_BYTE1		(1<<28)
#define AMCC_INT_FIFO_ADVA_BYTE2		(1<<29)
#define AMCC_INT_FIFO_ADVA_BYTE3		(3<<28)

#define AMCC_INT_FIFO_ADVP_BYTE0		0
#define	AMCC_INT_FIFO_ADVP_BYTE1		(1<<26)
#define AMCC_INT_FIFO_ADVP_BYTE2		(1<<27)
#define AMCC_INT_FIFO_ADVP_BYTE3		(3<<26)
#define AMCC_INT_ENDIAN_NOCONV			0
#define	AMCC_INT_ENDIAN_16BIT			(1<<24)
#define AMCC_INT_ENDIAN_32BIT			(1<<25)
#define AMCC_INT_ENDIAN_64BIT			(3<<24)

#define AMCC_INT_INTERRUPTED 	(1<<23)
#define AMCC_INT_RESERVED22		(1<<22)
#define AMCC_INT_TARG_ABORT		(1<<21)
#define AMCC_INT_MAST_ABORT		(1<<20)


#define AMCC_INT_READ_COMP		(1<<19)
#define AMCC_INT_WRITE_COMP		(1<<18)
#define AMCC_INT_INMBX_ACK		(1<<17)
#define AMCC_INT_OUTMBX_ACK		(1<<16)

#define AMCC_INT_INT_ON_READ	(1<<15)
#define AMCC_INT_INT_ON_WRITE	(1<<14)
#define AMCC_INT_RESERVED13		(1<<13)
#define AMCC_INT_ENABLE_OUTMBX_INT	(1<<12)

#define AMCC_INT_ENABLE_INMBX_INT	(1<<4)

#define AMCC_INT_ACK_BITS		(AMCC_INT_INTERRUPTED|AMCC_INT_TARG_ABORT|\
								AMCC_INT_MAST_ABORT|AMCC_INT_READ_COMP|\
								AMCC_INT_WRITE_COMP|AMCC_INT_OUTMBX_ACK|\
								AMCC_INT_INMBX_ACK )
//
// Shared routines
//

BOOLEAN OsrHandleInterrupt(PKINTERRUPT Interupt, PVOID ServiceContext);
VOID OsrDpcForIsr(PKDPC Dpc, PDEVICE_OBJECT DeviceObject, PIRP Unused, PVOID Context);
NTSTATUS OsrCreateClose(PDEVICE_OBJECT DeviceObject, PIRP Irp);
NTSTATUS OsrRead(PDEVICE_OBJECT DeviceObject, PIRP Irp);
NTSTATUS OsrWrite(PDEVICE_OBJECT DeviceObject, PIRP Irp);
NTSTATUS OsrDeviceControl(PDEVICE_OBJECT DeviceObject, PIRP Irp);
NTSTATUS OsrCleanup(PDEVICE_OBJECT DeviceObject, PIRP Irp);
NTSTATUS OsrPnp(PDEVICE_OBJECT DeviceObject, PIRP Irp);
NTSTATUS OsrPower(PDEVICE_OBJECT DeviceObject, PIRP Irp);
NTSTATUS OsrAddDevice(IN PDRIVER_OBJECT  DriverObject,IN PDEVICE_OBJECT  PhysicalDeviceObject);
VOID OsrWriteToDevice(PDEVICE_OBJECT DeviceObject);
VOID OsrResetAdapter(PDEVICE_OBJECT,BOOLEAN);
VOID OsrStartWriteIrp(PDEVICE_OBJECT DeviceObject, PIRP Irp);
VOID OsrStartReadIrp(PDEVICE_OBJECT DeviceObject, PIRP Irp);
IO_ALLOCATION_ACTION 
OsrAdapterControlRead(IN PDEVICE_OBJECT DeviceObject, IN PIRP NotUsed, 
	                              IN PVOID MapRegisterBase, IN PVOID Context);
IO_ALLOCATION_ACTION 
OsrAdapterControlWrite(IN PDEVICE_OBJECT DeviceObject, IN PIRP NotUsed, 
	                              IN PVOID MapRegisterBase, IN PVOID Context);

VOID OsrCancelFromReadQueue(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp);
VOID OsrCancelFromWriteQueue(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp);

VOID OsrProcessQueuedRequests(IN OUT POSR_DEVICE_EXT FDO_devExt);

NTSTATUS OsrSystemControl(PDEVICE_OBJECT DeviceObject, PIRP Irp);
VOID OsrUnload(PDRIVER_OBJECT DriverObject);
VOID OsrRequestIncrement(POSR_DEVICE_EXT devExt);
VOID OsrRequestDecrement(POSR_DEVICE_EXT devExt);
VOID OsrWaitForStop(POSR_DEVICE_EXT devExt);
VOID OsrWaitForRemove(POSR_DEVICE_EXT devExt);
VOID OsrClearQueues(POSR_DEVICE_EXT DevExt);

#if DBG
VOID OsrPrintIntcsr(ULONG Intcsr);
#endif


#endif /* __OSR_PCI_H__ */
