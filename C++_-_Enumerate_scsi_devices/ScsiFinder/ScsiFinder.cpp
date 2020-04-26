// ScsiFinder.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#pragma comment(lib,"setupapi")


int _tmain(int argc, _TCHAR* argv[])
{
	USES_CONVERSION;//initialize symbol conversion
	//global variables
	HDEVINFO hDevInfo = NULL;
	SP_DEVICE_INTERFACE_DATA			interfaceData;
	PSP_DEVICE_INTERFACE_DETAIL_DATA	interfaceDetailData = NULL;
	BOOL status; //operation result
	DWORD reqSize;
	DWORD interfaceDetailDataSize;
	DWORD Index = 0;
	DWORD errorCode;

	do{
		hDevInfo = SetupDiGetClassDevs(
							(LPGUID) &DiskClassGuid,
							NULL,
							NULL, 
							(DIGCF_PRESENT | DIGCF_INTERFACEDEVICE)   // Only Devices present & Interface class
						);
		if(hDevInfo == INVALID_HANDLE_VALUE){
			puts("Cannot get device information");
			break;
		}
		while(TRUE){
			interfaceData.cbSize = sizeof(SP_INTERFACE_DEVICE_DATA);
			status = SetupDiEnumDeviceInterfaces ( 
							hDevInfo,               // Interface Device Info handle
							0,                      // Device Info data
							(LPGUID)&DiskClassGuid, // Interface registered by driver
							Index,                  // Member
							&interfaceData          // Device Interface Data
						);
			
			if(!status){
				errorCode = GetLastError();
				if(errorCode == ERROR_NO_MORE_ITEMS)
					puts("that's all");
				else
					puts("Error while getting interface infomation");
				break;
			}
			status = SetupDiGetDeviceInterfaceDetail (
							hDevInfo,         // Interface Device info handle
							&interfaceData,     // Interface data for the event class
							NULL,               // Checking for buffer size
							0,                  // Checking for buffer size
							&reqSize,           // Buffer size required to get the detail data
							NULL                // Checking for buffer size
						);
			if(!status){
				errorCode = GetLastError();
				if(errorCode != ERROR_INSUFFICIENT_BUFFER){
					printf("SetupDiGetDeviceInterfaceDetail failed with error: %d\n", errorCode);
					break;
				}
			}
			
			interfaceDetailDataSize = reqSize;
			interfaceDetailData = (PSP_INTERFACE_DEVICE_DETAIL_DATA)malloc(interfaceDetailDataSize);
			if(interfaceDetailData == NULL){
				puts("Unable to allocate memory to get the interface detail data.\n" );
				break;
			}
			interfaceDetailData->cbSize = sizeof(SP_INTERFACE_DEVICE_DETAIL_DATA);

			status = SetupDiGetDeviceInterfaceDetail (
							hDevInfo,               // Interface Device info handle
							&interfaceData,           // Interface data for the event class
							interfaceDetailData,      // Interface detail data
							interfaceDetailDataSize,  // Interface detail data size
							&reqSize,                 // Buffer size required to get the detail data
							NULL);                    // Interface device info
			puts(W2A(interfaceDetailData->DevicePath));

			free(interfaceDetailData);
			Index++;
		}
		SetupDiDestroyDeviceInfoList(hDevInfo);
	}while(FALSE);
	getchar();
	return 0;
}
