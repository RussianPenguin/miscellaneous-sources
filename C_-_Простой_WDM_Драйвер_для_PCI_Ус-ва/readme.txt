README.TXT
==========

WDM_SAMPLE V1.4

This is a WDM-compliant driver, based on the example Busmaster DMA
device driver that accompanies the book Windows NT Device Driver
Development, by Peter Viscarola and W. Anthony Mason, (c) 1998
OSR Open Systems Resources, Inc. and published by MacMillan
Technical Publishing ISBN 1578700582.  

While previous versions of the driver have been tested on both Win98
and Windows NT, THIS version has only been tested on Windows 2000 RC1.
Sorry, we just can't bring ourselves to actually work on Win98 any more
than absolutely necessary.

Notes for V1.4
--------------
Acquire correct lock for the write queue during cancel;  Fix a reference
in PnP IRP processing that referenced the device extenstion after the
device object had been deleted (duh!);  Update the .inf script for NT
(only) to NOT use the "forbidden" class Unknown, but rather to add a
custom OSR class.

Notes for V1.3
--------------
Various fixes

Notes for V1.2
--------------
This version fixes yet ANOTHER bug in PNP.C, introduced in V1.1, and
found during remove testing.


Notes for V1.1
--------------
This version fixes a number of rather obvious errors in the released
version of the driver (seems as if a bad source file got stuffed into
the ZIP archive).

A number of comments have been added for clarity, especially to the 
state handling code in PNP.C.  The Remove Device code has been fixed.
Again.  Also, the code in the PnP Irp completion routine was updated
(some might say "corrected") from the Beta 1 practice of always calling
IoMarkIrpPending(...).  Indeed, even if it works the other way (and it
does) one should only set SL_PENDING if one's driver returns STATUS_PENDING
to its dispatch entry point.  Since we always wait, and then return a
STATUS_SUCCESS in these cases, marking the IRP pending is not the right
thing to do.


