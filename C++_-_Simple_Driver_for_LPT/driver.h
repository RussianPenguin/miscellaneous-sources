#ifndef _DRIVER_H_04802_BASHBD_1UIWQ1_8239_1NJKDH832_901_
#define _DRIVER_H_04802_BASHBD_1UIWQ1_8239_1NJKDH832_901_
// ���� ��������� ��� ������ (� ����� ����� ������� ��� #endif),
// ������� � ������� �������� ��������� ���������  ������� �� ������,
// ������� ��������� ������ h-����� (��� ������ ������ ��� ���������
// �������� ����������).
// (���� Driver.h)

#ifdef __cplusplus
extern "C"
{
#endif

#include "ntddk.h"

//#include "wdm.h" 
// ^^^^^^^^^^^^^^ ���� ������� ��� ������ � ���������������� 
// ����������, �� ����������  � ����� DDK (��� ������ ������� Build)  
// ����� ������� �������, ������ ������� Example �� ������ �� ����� 
// ��������� WDM ���������.

#ifdef __cplusplus
}
#endif
// ���������� ��������� ���������� ����������. ������� � ��� 
// ��������� �� FDO (��� �������� ����������� ������ UnloadRoutine) � 
// ��� ���������� ������ � ������� UNOCODE_STRING.

typedef struct _EXAMPLE_DEVICE_EXTENSION
{
	PDEVICE_OBJECT	fdo;
	UNICODE_STRING	ustrSymLinkName; // L"\\DosDevices\\Example"
} EXAMPLE_DEVICE_EXTENSION, *PEXAMPLE_DEVICE_EXTENSION;

// ���������� ����������� ���� IOCTL, � �������� ����� ����� 
// ���������� � �������� ��� ������ ������ DeviceIoControl.
// ����������� ������� CTL_CODE ����� ����� � ����� DDK Winioctl.h.
// ��� �� ����� ����� � ��������� ��������, ������������ ��� �������
// METHOD_BUFFERED � METHOD_NEITHER.

// ��������! ����� ����������� ���� ������ ����� � ���� Ioctl.h,
// ������� ����� ��������� ��� ���������� ��������� ����������.
// (����������, �� ����������� ��������� ������ � �#endif�.)

#define IOCTL_PRINT_DEBUG_MESS CTL_CODE( \
	FILE_DEVICE_UNKNOWN, 0x801, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define IOCTL_CHANGE_IRQL CTL_CODE(\
	FILE_DEVICE_UNKNOWN, 0x802, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define IOCTL_MAKE_SYSTEM_CRASH CTL_CODE( \
	FILE_DEVICE_UNKNOWN, 0x803, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define IOCTL_TOUCH_PORT_378H CTL_CODE( \
	FILE_DEVICE_UNKNOWN, 0x804, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define IOCTL_SEND_BYTE_TO_USER CTL_CODE( \
	FILE_DEVICE_UNKNOWN, 0x805, METHOD_BUFFERED, FILE_ANY_ACCESS)

// ������� :
//#define IOCTL_SEND_BYTE_TO_USER CTL_CODE( \
//    FILE_DEVICE_UNKNOWN, 0x805, METHOD_NEITHER, FILE_ANY_ACCESS)
#endif
