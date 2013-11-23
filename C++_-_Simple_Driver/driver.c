#include "ntddk.h" 
#include "driver.h" 
#include "parallel.h" 

#define NT_DEVICE_NAME L"DevicemyDrv" 
#define DOS_DEVICE_NAME L"DosDevicesmyDrv" 

//структура расширения устройства 
typedef struct _DEVICE_EXTENSION 
{ 
	PDRIVER_OBJECT DriverObject; 
	PDEVICE_OBJECT DeviceObject; 
	PFILE_OBJECT FileObject; 
	HANDLE Handle; 

} DEVICE_EXTENSION, *PDEVICE_EXTENSION; 

//прототипы функций 
NTSTATUS DriverDeviceControl(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp); 

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject); 

NTSTATUS DriverOpen(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp); 

NTSTATUS DriverClose(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp); 

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////реализация функций 

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath) 
{ 
	PDEVICE_OBJECT deviceObject; 
	UNICODE_STRING deviceNameUnicodeString; 
	UNICODE_STRING deviceLinkUnicodeString; 
	PDEVICE_EXTENSION extension; 
	NTSTATUS ntStatus; 

	RtlInitUnicodeString(&deviceNameUnicodeString, NT_DEVICE_NAME); 

	ntStatus = IoCreateDevice(DriverObject, 
	sizeof (DEVICE_EXTENSION), &deviceNameUnicodeString, FILE_DEVICE_UNKNOWN, 0, 
	FALSE, 
	&deviceObject); 

	if (!NT_SUCCESS(ntStatus)) return ntStatus; 

	DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = DriverDeviceControl; 
	DriverObject->DriverUnload = DriverUnload; 
	DriverObject->MajorFunction[IRP_MJ_CREATE] = DriverOpen; 
	DriverObject->MajorFunction[IRP_MJ_CLOSE] = DriverClose; 

	extension = (PDEVICE_EXTENSION) deviceObject->DeviceExtension; 
	extension->DeviceObject = deviceObject; 
	extension->DriverObject = DriverObject; 

	// Create counted string version of our Win32 device name. 
	RtlInitUnicodeString(&deviceLinkUnicodeString, DOS_DEVICE_NAME); 

	// Create a link from our device name to a name in the Win32 namespace. 
	ntStatus = IoCreateSymbolicLink(&deviceLinkUnicodeString, &deviceNameUnicodeString); 
	if (!NT_SUCCESS(ntStatus)) 
	{ 
		IoDeleteDevice(deviceObject); 
		return ntStatus; 
	} 

	return STATUS_SUCCESS; 
} 


//------------------------------------------------------------------------------------------------------------------- 
VOID DriverUnload(IN PDRIVER_OBJECT DriverObject) 
{ 
	UNICODE_STRING deviceLinkUnicodeString; 
	PDEVICE_EXTENSION extension; 
	PIRP pNewIrp = NULL; 
	ULONG m_size; 
	NTSTATUS ntStatus; 
	extension = DriverObject->DeviceObject->DeviceExtension; 

	// Create counted string version of our Win32 device name. 
	RtlInitUnicodeString(&deviceLinkUnicodeString, DOS_DEVICE_NAME); 


	// Delete the link from our device name to a name in the Win32 namespace. 
	IoDeleteSymbolicLink(&deviceLinkUnicodeString); 


	// Finally delete our device object 
	IoDeleteDevice(DriverObject->DeviceObject); 
} 

//------------------------------------------------------------------------------------------------------------------- 
NTSTATUS DriverOpen(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp) 
{ 
	Irp->IoStatus.Status = STATUS_SUCCESS; 
	Irp->IoStatus.Information = 0; 
	IoCompleteRequest(Irp, IO_NO_INCREMENT); 
	return STATUS_SUCCESS; 
} 

//------------------------------------------------------------------------------------------------------------------- 
NTSTATUS DriverClose(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp) 
{ 
	Irp->IoStatus.Status = STATUS_SUCCESS; 
	Irp->IoStatus.Information = 0; 
	IoCompleteRequest(Irp, IO_NO_INCREMENT); 
	return STATUS_SUCCESS; 
} 

//------------------------------------------------------------------------------------------------------------------- 
NTSTATUS DriverDeviceControl(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp) 
{ 
	NTSTATUS ntStatus; 
	PIO_STACK_LOCATION irpStack; 
	PDEVICE_EXTENSION extension; 
	PULONG ioBuffer; 
	ULONG ioControlCode; 
	ULONG port = 0; 

	Irp->IoStatus.Status = STATUS_SUCCESS; 
	Irp->IoStatus.Information = 0; 
	irpStack = IoGetCurrentIrpStackLocation(Irp); 
	extension = DeviceObject->DeviceExtension; 
	ioBuffer = Irp->AssociatedIrp.SystemBuffer; 
	ioControlCode = irpStack->Parameters.DeviceIoControl.IoControlCode; 
	switch (ioControlCode) 
	{ 
		case TEST_SMTH: 
			ioBuffer[0] =(ULONG)DriverEntry;//В буфер обмена адрес функции DriverEntry 
			Irp->IoStatus.Information = 4; 
		break; 

		default: 
			Irp->IoStatus.Status = STATUS_INVALID_PARAMETER; 
		break; 
	} 

	ntStatus = Irp->IoStatus.Status; 
	IoCompleteRequest(Irp, IO_NO_INCREMENT); 
	return ntStatus; 
}