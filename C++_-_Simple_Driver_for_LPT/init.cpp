/////////////////////////////////////////////////////////////////////
// init.cpp:		������������� ��������
// ���������. ������� ������ ������� �������� ������ ���� 
// �������������� ��� ��-WDM ������. � ��������� ������ - �������
// �� ������ ��������� ����������� � ����������� � ��������������
// ��������� monitor (����� Numega Driver Studio) � �������� SCM
// ���������.

/////////////////////////////////////////////////////////////////////
//	DriverEntry	          ������� ����� ����� � �������
//	UnloadRoutine	    ��������� �������� ��������
//	DeviceControlRoutine  ���������� DeviceIoControl IRP �������
/////////////////////////////////////////////////////////////////////
#include "Driver.h"

// ��������������� ���������� �������:
NTSTATUS DeviceControlRoutine( IN PDEVICE_OBJECT fdo, IN PIRP Irp );

VOID     UnloadRoutine(IN PDRIVER_OBJECT DriverObject);

NTSTATUS
ReadWrite_IRPhandler( IN PDEVICE_OBJECT fdo, IN PIRP Irp );

NTSTATUS
Create_File_IRPprocessing(IN PDEVICE_OBJECT fdo, IN PIRP Irp);

NTSTATUS
Close_HandleIRPprocessing(IN PDEVICE_OBJECT fdo, IN PIRP Irp);

// ���� � �������� ������ ���������� ���������� � ��������...
KSPIN_LOCK      MySpinLock;
#pragma code_seg("INIT") // ������ ������ INIT
/////////////////////////////////////////////////////////////////////
// (���� init.cpp)
//	DriverEntry - ������������� �������� � ����������� ��������
//	���������:  ��������� �� ������ ��������
//                ������ ������� (driver service key) � UNICODE
//  ����������:   STATUS_Xxx

extern "C"
NTSTATUS DriverEntry(	IN PDRIVER_OBJECT DriverObject,
						IN PUNICODE_STRING RegistryPath  )
{
	NTSTATUS status = STATUS_SUCCESS;
	PDEVICE_OBJECT  fdo;
	UNICODE_STRING  devName;

	#if DBG
	DbgPrint("=Example= In DriverEntry.");
	DbgPrint("=Example= RegistryPath = %ws.", RegistryPath->Buffer);
	#endif

	// ������� ����� ����� � ������� (AddDevice ��������� �� �����)
	// DriverObject->DriverExtension->AddDevice=
	//                                 OurAddDeviceRoutine;
	DriverObject->DriverUnload = UnloadRoutine;
	DriverObject->MajorFunction[IRP_MJ_CREATE]= Create_File_IRPprocessing;
	DriverObject->MajorFunction[IRP_MJ_CLOSE] = Close_HandleIRPprocessing;
	DriverObject->MajorFunction[IRP_MJ_READ]  = ReadWrite_IRPhandler;
	DriverObject->MajorFunction[IRP_MJ_WRITE] = ReadWrite_IRPhandler;
	DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL]=
											  DeviceControlRoutine;
	//========================================================
	// �������� �� �������� ���������� ������
	// (�� ����� ���� �� ������ � OurAddDeviceRoutine, �� � ���
	//  ����� ������� ������� � ��� ��������� �����������):
	RtlInitUnicodeString( &devName, L"\\Device\\EXAMPLE" );

	// ������� ��� Functional Device Object (FDO) � �������� 
	// ��������� �� ��������� FDO � ����� ���������� fdo.
	// (� WDM �������� ��� ������ ����� ��������� �� ���������
	// � ��������� OurAddDeviceRoutine.) ��� �������� FDO 
	// ����� �������� ����� � ��� ��������� ���������� ����������
	// EXAMPLE_DEVICE_EXTENSION (��� ����� �� �������� � ����� 
	// �� ������, ����������� ���������� sizeof):
	status = IoCreateDevice(DriverObject,
							sizeof(EXAMPLE_DEVICE_EXTENSION),
							&devName, // ����� ���� � NULL
							FILE_DEVICE_UNKNOWN,
							0,
							FALSE, // ��� ������������� �������
							&fdo);
	if(!NT_SUCCESS(status)) return status;

	// �������� ��������� �� �������, ��������������� ���
	// ��������� ���������� ����������
	PEXAMPLE_DEVICE_EXTENSION dx =
					(PEXAMPLE_DEVICE_EXTENSION)fdo->DeviceExtension;
	dx->fdo = fdo;  // ��������� �������� ���������

	// �������� ����� �������� ����������, ������ ������� DbgPrint,
	// ��������� ������� �� ������ ������� � ���� DebugView, ����
	// �������� ������ ������ �������� ��� checked (����������)
	// ������:
	#if DBG
	DbgPrint("=Example= FDO %X, DevExt=%X.",fdo,dx);
	#endif

	//=======================================
	// �������� �� �������� ���������� ������
	// (�� ����� ���� �� ������ � OurAddDeviceRoutine, �� � ���
	//  ����� ������� �������):

	UNICODE_STRING symLinkName;   // ������������ ���������� ���:
	// #define   SYM_LINK_NAME   L"\\??\\Example"
	// ������ ���� ���������� ������ ^^ �������� ������ � NT.
	// (�� ����, ���� ��������� �������� ���� �������� � 
	// Windows 98, �� ���������������� ���������� �������� 
	// �� ������ ������� ���� �� ����� ���������� ������.)
	// ��� ����, ����� ������ �������� � � Windows 98 � � NT,
	// ���������� ��������� ��������� ������� :

	#define	SYM_LINK_NAME	L"\\DosDevices\\Example"
	RtlInitUnicodeString( &symLinkName, SYM_LINK_NAME );
	dx->ustrSymLinkName = symLinkName;
	
	// ������� ���������� ������
	status = IoCreateSymbolicLink( &symLinkName, &devName );
	if (!NT_SUCCESS(status))
	{ // ��� ������� � ������� Device Object � ������� ����������
		IoDeleteDevice( fdo );
		return status;
	} // ������ ����� �������� CreateFile("\\\\.\\Example",...);
	// � ���������������� �����������

	// ������ ����-����������, ������� ����� ������������ ���
	// ���������� �� ������� ���������� ���� �����������
	// IOCTL ��������. �������������� ���:
	KeInitializeSpinLock(&MySpinLock);

	// ����� ���������� �������� ����������, ����� �������� ���,
	// ������������� � ���������� ������ � �� ������������� �
	// ������ free (��������):
	#if DBG
	DbgPrint("=Example= DriverEntry successfully completed.");
	#endif
	return status;
}
#pragma code_seg() // end INIT section

//
// (���� init.cpp)
// CompleteIrp: ������������� IoStatus � ��������� ��������� IRP
// ������ �������� � ��������� �� ������ ������ FDO.
// 
NTSTATUS CompleteIrp( PIRP Irp, NTSTATUS status, ULONG info)
{
	Irp->IoStatus.Status = status;
	Irp->IoStatus.Information = info;
	IoCompleteRequest(Irp,IO_NO_INCREMENT);
return status;
}

//
// (���� init.cpp)
// ReadWrite_IRPhandler: ����� �� ���� ��������� �������� 
// ������/������ � ��������� ��������� IRP ������� CompleteIrp
// � ������ ����������/���������� ���� (BytesTxd) ������ ����.
// ���������: 
// ��������� �� ������ ������ FDO
// ��������� �� ��������� IRP, ������������ �� ���������� �����/
// ������
NTSTATUS ReadWrite_IRPhandler( IN PDEVICE_OBJECT fdo, IN PIRP Irp )
{
	ULONG BytesTxd = 0;
	NTSTATUS status = STATUS_SUCCESS; //���������� � ����� status
	// ������ ������ ���������� ��������� � ���� ������ ����������
	#if DBG
	DbgPrint("-Example- in ReadWrite_IRPhandler.");
	#endif
	return CompleteIrp(Irp,status,BytesTxd); 
}


//
// (���� init.cpp)
// Create_File_IRPprocessing: ����� �� ���� ��������� �������� � 
// ����� IRP_MJ_CREATE.
// ���������: 
// ��������� �� ������ ������ FDO
// ��������� �� ��������� IRP, ������������ �� ���������� ��
//
NTSTATUS Create_File_IRPprocessing(IN PDEVICE_OBJECT fdo,IN PIRP Irp)
{
	PIO_STACK_LOCATION IrpStack = IoGetCurrentIrpStackLocation(Irp);
	// ������ ������ ���������� ��������� � ���� ������ ����������
	#if DBG
	DbgPrint("-Example- Create File is %ws",
	&(IrpStack->FileObject->FileName.Buffer));
	#endif

return CompleteIrp(Irp,STATUS_SUCCESS,0); // �������� ����������
}


// (���� init.cpp)
// Close_File_IRPprocessing: ����� �� ���� ��������� �������� � 
// ����� IRP_MJ_CLOSE.
// ���������: 
// ��������� �� ������ ������ FDO
// ��������� �� ��������� IRP, ������������ �� ���������� 
// �����/������
NTSTATUS Close_HandleIRPprocessing(IN PDEVICE_OBJECT fdo,IN PIRP Irp)
{
	#if DBG
	// ������ ������ ���������� ��������� � ���� ������ ����������
	DbgPrint("-Example- In Close handler."); 
	#endif
return CompleteIrp(Irp,STATUS_SUCCESS,0);// �������� ����������
}



// (���� init.cpp)
// DeviceControlRoutine: ���������� IRP_MJ_DEVICE_CONTROL ��������
// ���������: 
// ��������� �� ������ ������ FDO
// ��������� �� ��������� IRP, ������������ �� ���������� ��
//	����������:  STATUS_XXX
// #define SMALL_VERSION
// � ��� ������, ���� �� ���������������� ������� ������� � ����� 
// ��������� ���������� ������, � ������� ����� �������������� ������ 
// ���� ��� IOCTL �������� -- IOCTL_MAKE_SYSTEM_CRASH

NTSTATUS DeviceControlRoutine( IN PDEVICE_OBJECT fdo, IN PIRP Irp )
{
	NTSTATUS status = STATUS_SUCCESS;
	ULONG BytesTxd =0; // ����� ����������/���������� ���� (���� 0)
	PIO_STACK_LOCATION IrpStack=IoGetCurrentIrpStackLocation(Irp);

	// �������� ��������� �� ���������� ����������
	PEXAMPLE_DEVICE_EXTENSION dx =
				 (PEXAMPLE_DEVICE_EXTENSION)fdo->DeviceExtension;
	//-------------------------------
	// �������� �� IRP ���������� �������� IOCTL ����, �� ������ 
	// �������� �������� �����:
	ULONG ControlCode = 
	IrpStack->Parameters.DeviceIoControl.IoControlCode;
	ULONG method = ControlCode & 0x03;

	// �������� ������� �������� ������ IRQL � ����������,
	// �� ������� ����������� ����� (������ ������, ����� �����):
	KIRQL irql, 
	currentIrql = KeGetCurrentIrql();

	#if DBG
	DbgPrint("-Example- In DeviceControlRoutine (fdo= %X)\n",fdo);
	DbgPrint("-Example- DeviceIoControl: IOCTL %x.", ControlCode );
	if(currentIrql==PASSIVE_LEVEL)
		DbgPrint("-Example- PASSIVE_LEVEL (val=%d)",currentIrql);
	#endif
	// ����������� �������� �������� ����-����������. � ������ 
	// ������� �� ����������� ������� ��������� ��������, ��, 
	// ������ ������, ���� ����� ����� ���� ������� � ���� 
	// ���������, ���� � ����������� ���� ���� ������ �����
	// ��������� �����������, ������� ����� ������ ������
	// �����������. ���� ������ ������� ������ ����-���������� � 
	// ������� ������ ����� �� ������ ����� � �������� switch:
	KeAcquireSpinLock(&MySpinLock,&irql);

	// ��������������� �� IOCTL �����:
	switch( ControlCode) {

	#ifndef SMALL_VERSION
	case IOCTL_PRINT_DEBUG_MESS:
	{     // ������ ������ ��������� � ������ � ���������� ������
		#if DBG
		DbgPrint("-Example- IOCTL_PRINT_DEBUG_MESS.");
		#endif
		break;
	}
	case IOCTL_CHANGE_IRQL:
	{
		#if DBG
		// ������������ �� �������������� ��������� 
		// IRQL � ������ � ���������� ������!
		DbgPrint("-Example- IOCTL_CHANGE_IRQL.");
		KIRQL dl = DISPATCH_LEVEL, // ������ ��� ���������� (2)
		oldIrql,
		newIrql=25; // ����� ������� IRQL (��������, 25)
		// ������������� newIrql, �������� ������� � oldIrql:
		KeRaiseIrql(newIrql,&oldIrql);
		newIrql=KeGetCurrentIrql(); // ��� ������� ��������?

		DbgPrint("-Example- DISPATCH_LEVEL value =%d",dl);
		DbgPrint("-Example- IRQLs are old=%d new=%d", 
						oldIrql,newIrql);
		KeLowerIrql(oldIrql); // ���������� ������ ��������
		#endif
		break;
	}
	#endif // SMALL_VERSION


	case IOCTL_MAKE_SYSTEM_CRASH:
	{
		int errDetected=0;
		char x = (char)0xFF;

		#if	DBG  // ������ ������, ��� NT �� ����� ��� �� ������:
		DbgPrint("-Example- IOCTL_MAKE_SYSTEM_CRASH.");
		#endif
		// �������� ��������� ���� ���������� �� �������� ������
		__try { 
		x = *(char*)0x0L; // ��������� ��������
			//^^^^^^^^^^^^ ����� �������� ���� NT, �� �� Win98
		}
		__except(EXCEPTION_EXECUTE_HANDLER)
		{   // �������� ���������� �� ��������!
			// ��� ������������� �������� ��������� � 10.2.6,
			// ��� ������������ �������� ����-����������.
			errDetected=1;
		};
		#if DBG
		DbgPrint("-Example- Value of x is %X.",x);
		if(errDetected)
			DbgPrint("-Example- Except detected in Example driver.");
		#endif
		break;
	}

	#ifndef SMALL_VERSION
	case IOCTL_TOUCH_PORT_378H:
	{	 
		unsigned short ECRegister = 0x378+0x402;
		#if DBG
		DbgPrint("-Example- IOCTL_TOUCH_PORT_378H.");
		#endif
		// ������� ���������� ��������� ������������ ���� 378, 
		// ������������������ ���������� BIOS ��� ECP+EPP, �
		// ����� EPP.
		_asm  {
			mov dx,ECRegister ;
			xor al,al    ;
			out dx,al    ;    ���������� EPP mode 000
			mov al,095h  ;    ���� 7:5 = 100
			out dx,al    ;    ���������� EPP mode 100
		}
		// �������� �������� � ���������� �����������������
		// ������ ��� NT  ����������� ������� �� � ��������� 
		// �������� ���������� � ���������� �� ������!
		// ����������� ��� ���� ����� �������������, ��� �����
		// �������� � LPT ������ ��� Windows NT !
		break;
	}

	case IOCTL_SEND_BYTE_TO_USER:
	{	 
		// ������ ������, ����������� �� ������������:
		ULONG InputLength = //������ ���� ��� �������
			IrpStack->Parameters.DeviceIoControl.InputBufferLength;
		// ������ ������ ��� ������, ��������� �������������
		ULONG OutputLength = 
		IrpStack->Parameters.DeviceIoControl.OutputBufferLength;
		#if DBG
		DbgPrint("-Example- Buffer outlength %d",OutputLength);
		#endif

		if( OutputLength<1 )
		{// ���� �� ������������ ����� � ��������� IRP � �������
			status = STATUS_INVALID_PARAMETER;
			break;
		}
		UCHAR *buff; // unsigned char, ��������� � ����� �������
		if(method==METHOD_BUFFERED)
		{
			buff = (PUCHAR)Irp->AssociatedIrp.SystemBuffer;
			#if DBG
			DbgPrint("-Example- Method : BUFFERED.");
			#endif
		}
		else
			if (method==METHOD_NEITHER)
			{
				buff=(unsigned char*)Irp->UserBuffer;
				#if DBG
				DbgPrint("-Example- Method : NEITHER.");
				#endif
			}
			else 
			{
				#if DBG
				DbgPrint("-Example- Method : unsupported.");
				#endif
				status = STATUS_INVALID_DEVICE_REQUEST;
				break;
			}
		#if DBG
		DbgPrint("-Example- Buffer address is %08X",buff);
		#endif
		*buff=33;     // ������� ����� ��������
		BytesTxd = 1; // �������� 1 ����
		break;
	}
	#endif // SMALL_VERSION
	// ��������� ������ (��� IOCTL, ������� �� ��������������):
	default: status = STATUS_INVALID_DEVICE_REQUEST;
	}
	// ������������ ����-����������
	KeReleaseSpinLock(&MySpinLock,irql);

	#if DBG
	DbgPrint("-Example- DeviceIoControl: %d bytes written.", (int)BytesTxd);
	#endif

return CompleteIrp(Irp,status,BytesTxd); // ���������� IRP
}


//
// (���� init.cpp)
// UnloadRoutine: ��������� �������, ���������� ���������� �������
// ���������� ��������, ����� ���������� ��������� �������.
// ��� � ��������� AddDevice, �������������� ����� ���
// ��� ��������� ������� ��������� � �� �������� ������� IRP.
// Arguments:  ��������� �� ������ ��������
//

#pragma code_seg("PAGE")
// ��������� ���������� � ��������� �������������� ������
//
VOID UnloadRoutine(IN PDRIVER_OBJECT pDriverObject)
{
	PDEVICE_OBJECT	pNextDevObj;
	int i;

	// ������ ������ ���������� ��������� � ���� ������ ����������
	#if DBG
	DbgPrint("-Example- In Unload Routine.");
	#endif
	//==========================================================
	// ���������������  �������� � ��������������� WDM ��������
	// ��������� �� ��������� � ����������� IRP_MJ_PNP ��������
	// � �������� IRP_MN_REMOVE_DEVICE, �� � ���� ��������
	// ��������, ������� ��� �����.
	// �������� �� ���� �������� ���������, �������������� 
	// ���������
	pNextDevObj = pDriverObject->DeviceObject;

	for(i=0; pNextDevObj!=NULL; i++)
	{
		PEXAMPLE_DEVICE_EXTENSION dx = 
				(PEXAMPLE_DEVICE_EXTENSION)pNextDevObj->DeviceExtension;
		// ������� ���������� ������ � ���������� FDO:
		UNICODE_STRING *pLinkName = & (dx->ustrSymLinkName);
		// !!! ��������� ���������:
		pNextDevObj = pNextDevObj->NextDevice;

		#if DBG
		DbgPrint("-Example- Deleted device (%d) : pointer to FDO = %X.",
							i,dx->fdo);
		DbgPrint("-Example- Deleted symlink = %ws.", pLinkName->Buffer);
		#endif

		IoDeleteSymbolicLink(pLinkName);
		IoDeleteDevice( dx->fdo);
	}
}
#pragma code_seg() // end PAGE section
