////////////////////////////////////////////////////////////////////
// (���� ExampleTest.cpp)
// ���������� ���������� ��� ������������ �������� Example.sys
//	22-Feb-2003  1.0.0 SVP
////////////////////////////////////////////////////////////////////

// ������������ �����, ������� ���������� � ������ ����������:
#include <windows.h>
#include <stdio.h>
#include <winioctl.h>
#include <tchar.h>

// ��������! ���� Ioctl.h ������ ���� ������� �� ����� Driver.h
// (��. ������������ � Driver.h) � �������� � ����� ���������� �
// ������ ������ (TestExam.cpp).
#include "Ioctl.h"

// ��� ������� �������� � �������������� ������������ ����� 
#define DRIVERNAME    _T("Example")
//#define DRIVERBINARY  _T("C:\\Example\\Example.sys")
//#define DRIVERBINARY  _T("C:\\Ex\\objchk_w2k\\i386\\Example.sys")
#define DRIVERBINARY  _T("C:\\Ex\\tester\\Example.sys")

// ������� ��������� �������� �� ������ SCM �������
BOOL InstallDriver( SC_HANDLE  scm, LPCTSTR DriverName, LPCTSTR driverExec )
{
	SC_HANDLE Service =
			CreateService ( scm,    // �������� ���������� � SCManager
							DriverName,      // ��� ������� - Example
							DriverName,      // ��� ������ �� �����
							SERVICE_ALL_ACCESS,    // �������� ������
							SERVICE_KERNEL_DRIVER, // ��� �������
							SERVICE_DEMAND_START,  // ��� ������� 
							SERVICE_ERROR_NORMAL,  // ��� �������������� ������
							driverExec,            // ���� � ��������� �����
							// ��������� ��������� �� ������������ � ������ NULL
							NULL,    // �� ���������� ������ ��������
							NULL, NULL, NULL, NULL);
	if (Service == NULL) // �������
	{
		DWORD err = GetLastError();
		if (err == ERROR_SERVICE_EXISTS) {/* ��� ���������� */}
		// ����� ��������� ������: 
		else  printf ("ERR: Can�t create service. Err=%d\n",err);
		// (^^ ���� ��� ������ ����� ���������� � ErrLook):
		return FALSE;
	}
	CloseServiceHandle (Service);
return TRUE;
}

// ������� �������� �������� �� ������ SCM �������
BOOL RemoveDriver(SC_HANDLE scm, LPCTSTR DriverName)
{
	SC_HANDLE Service =
			OpenService (scm, DriverName, SERVICE_ALL_ACCESS);
	if (Service == NULL) return FALSE;
	BOOL ret = DeleteService (Service);
	if (!ret) { /* ������� ��� �������� �������� */ } 

	CloseServiceHandle (Service);
return ret;
}

// ������� ������� �������� �� ������ SCM �������
BOOL StartDriver(SC_HANDLE  scm, LPCTSTR DriverName)
{
	SC_HANDLE Service =
			OpenService(scm, DriverName, SERVICE_ALL_ACCESS);
	if (Service == NULL) return FALSE; /* open failed */
	BOOL ret =
			StartService( Service, // ����������
						  0,       // ����� ����������
						  NULL  ); // ���������  �� ���������
	if (!ret) // �������
	{ 
		DWORD err = GetLastError();
		if (err == ERROR_SERVICE_ALREADY_RUNNING)
			ret = TRUE; // OK, ������� ��� ��������!
		else { /* ������ �������� */}
	}

	CloseServiceHandle (Service);
return ret;
}
// ������� �������� �������� �� ������ SCM �������
BOOL StopDriver(SC_HANDLE  scm, LPCTSTR DriverName)
{
	SC_HANDLE Service =
			OpenService (scm, DriverName, SERVICE_ALL_ACCESS );
	if (Service == NULL)  // ���������� ��������� ������� ��������
	{
		DWORD err = GetLastError();
		return FALSE;
	}
	SERVICE_STATUS serviceStatus;
	BOOL ret = 
	ControlService(Service, SERVICE_CONTROL_STOP, &serviceStatus);
	if (!ret)
	{
		DWORD err = GetLastError();
		// �������������� �����������
	}

	CloseServiceHandle (Service);
return ret;
}


// ������� ������ �������� �� ���������, �������, ��������
// � �������� �������� (��� ��������� ��������).
// (������ ������������ ���� �������� � ������ ������� �� ��������.)
/* �������������� ��.
void Test_SCM_Installation(void)
{
	SC_HANDLE scm = OpenSCManager(NULL,NULL,SC_MANAGER_ALL_ACCESS);
	if(scm == NULL) // �������
	{ 
		// �������� ��� ������ � �� ��������� ����������
		unsigned long err = GetLastError();
		PrintErrorMessage(err); // ��. �. 2.1.5
		return;
	}
	BOOL res;
	res = InstallDriver(scm, DRIVERNAME, DRIVERBINARY );
	// ������ ����� ��������� �� ���������. ����������:
	res = StartDriver  (scm, DRIVERNAME );
	if(res)
	{
		//� ����� ������� ���������� ������� ������ � ���������
		.. .. ..
		res = StopDriver   (scm, DRIVERNAME );
		if(res) res = RemoveDriver (scm, DRIVERNAME );
	}
CloseServiceHandle(scm);
return;
}
*/

#define SCM_SERVICE
// ^^^^^^^^^^^^^^^^ ������ ������� �������� ����������, ��� ������ 
// �������� ����� ��������� ������������� SCM ��������� ��������
// � ������ ������� ����������. (����� � ������������� SCM ��������.)

// �������� ������� ������������ ����������.
// ����� ������� �������� ������ ����������� ��������� ��������.
// � ������������� ������� ����������� ������� ������� �����
// ������ ��������!

int __cdecl main(int argc, char* argv[])
{
	#ifdef SCM_SERVICE
	// ���������� ������ SCM ��� ������� ��������.
	BOOL res; // �������� ������ � SCM :
	SC_HANDLE scm = OpenSCManager(NULL,NULL,SC_MANAGER_ALL_ACCESS);
	if(scm == NULL) return -1; // �������

	// ������ ������� ��������� ��������
	res = InstallDriver(scm, DRIVERNAME, DRIVERBINARY );
	if(!res) // �������, �� ��������, �� ��� �������������
		printf("Cannot install service");

	res = StartDriver  (scm, DRIVERNAME );
	if(!res)
	{
		printf("Cannot start driver!");
		res = RemoveDriver (scm, DRIVERNAME );
		if(!res)
		{
			printf("Cannot remove driver!");
		}
		CloseServiceHandle(scm); // ����������� �� SCM
		return -1;
	}
	#endif

	HANDLE hHandle =           // �������� ������ � ��������
			CreateFile( "\\\\.\\Example",
						GENERIC_READ | GENERIC_WRITE,
						FILE_SHARE_READ | FILE_SHARE_WRITE,
						NULL,
						OPEN_EXISTING,
						FILE_ATTRIBUTE_NORMAL,
						NULL );
	if(hHandle==INVALID_HANDLE_VALUE)
	{
		printf("ERR: can not access driver Example.sys !\n");
		return (-1);
	}
	DWORD BytesReturned;    // ���������� ��� �������� �����
							// ���������� ����
	// ��������������� ��������� ��������� � �������� 
	// � ���������� ������ IOCTL:

	unsigned long ioctlCode=IOCTL_PRINT_DEBUG_MESS;
	if( !DeviceIoControl(   hHandle,
					ioctlCode,
					NULL, 0,	// Input
					NULL, 0,	// Output
					&BytesReturned,
					NULL )  )
	{
		printf( "Error in IOCTL_PRINT_DEBUG_MESS!" );
		return(-1);
	}

	ioctlCode=IOCTL_CHANGE_IRQL;
	if( !DeviceIoControl(   hHandle,
					ioctlCode,
					NULL, 0,	// Input
					NULL, 0,	// Output
					&BytesReturned,
					NULL )  )
	{
		printf( "Error in IOCTL_CHANGE_IRQL!" );
		return(-1);
	}

	ioctlCode=IOCTL_TOUCH_PORT_378H;
	if( !DeviceIoControl(   hHandle,
					ioctlCode,
					NULL, 0,  // Input
					NULL, 0,  // Output
					&BytesReturned,
					NULL )  )
	{
		printf( "Error in IOCTL_TOUCH_PORT_378H!" );
		return(-1);
	}

	// ��������� ����. �������� 1 ���� ������ �� ��������.
	// �� ��������� ������� ������ ���������� xdata ������ 
	// ��������� �������� 33:
	unsigned char xdata = 0x88;
	ioctlCode=IOCTL_SEND_BYTE_TO_USER;
	if( !DeviceIoControl(   hHandle,
					ioctlCode,
					NULL, 0,  // Input
					&xdata, sizeof(xdata),// Output
					&BytesReturned,
					NULL )  )
	{
		printf( "Error in IOCTL_SEND_BYTE_TO_USER!" );
		return(-1);
	}

	// ����� ���������������� ��������� � ���������� ����:
	printf("IOCTL_SEND_BYTE_TO_USER: BytesReturned=%d xdata=%d",
		            BytesReturned, xdata);

	// ���������� ���������� ����� � Windows NT �������� �
	// ���������� ���� ������������ ������� (��������� �����������
	// ������� �� ����� ���� ������� ��� ��������, ��������, 
	// ����������� crash dump ����� � ������ � ����������).
	/*
	ioctlCode=IOCTL_MAKE_SYSTEM_CRASH;
	if( !DeviceIoControl(   hHandle,
					ioctlCode,
					NULL, 0,		        // Input
					NULL, 0,	// Output
					&BytesReturned,
					NULL )  )
	{
		printf( "Error in IOCTL_MAKE_SYSTEM_CRASH!" );
		return(-1);
	}
	*/
	// ��������� ���������� ������� � ��������:
	CloseHandle(hHandle);


	#ifdef SCM_SERVICE
	// ������������� � ������� �������. ����������� �� SCM.
	res = StopDriver   (scm, DRIVERNAME );
	if(!res)
	{
		printf("Cannot stop driver!");
		CloseServiceHandle(scm);
		return -1;
	}

	res = RemoveDriver (scm, DRIVERNAME );
	if(!res)
	{
		printf("Cannot remove driver!");
		CloseServiceHandle(scm);
		return -1;
	}

	CloseServiceHandle(scm);
	#endif

return 0;
}
