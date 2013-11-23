#ifndef _DRIVER_H_04802_BASHBD_1UIWQ1_8239_1NJKDH832_901_
#define _DRIVER_H_04802_BASHBD_1UIWQ1_8239_1NJKDH832_901_
// Выше приведены две строки (в конце файла имеется еще #endif),
// которые в больших проектах запрещают повторные  проходы по тексту,
// который находится внутри h-файла (что весьма удобно для повышения
// скорости компиляции).
// (Файл Driver.h)

#ifdef __cplusplus
extern "C"
{
#endif

#include "ntddk.h"

//#include "wdm.h" 
// ^^^^^^^^^^^^^^ если выбрать эту строку и закомментировать 
// предыдущую, то компиляция  в среде DDK (при помощи утилиты Build)  
// также пройдет успешно, однако драйвер Example не станет от этого 
// настоящим WDM драйвером.

#ifdef __cplusplus
}
#endif
// Определяем структуру расширения устройства. Включим в нее 
// указатель на FDO (для удобства последующей работы UnloadRoutine) и 
// имя символьной ссылки в формате UNOCODE_STRING.

typedef struct _EXAMPLE_DEVICE_EXTENSION
{
	PDEVICE_OBJECT	fdo;
	UNICODE_STRING	ustrSymLinkName; // L"\\DosDevices\\Example"
} EXAMPLE_DEVICE_EXTENSION, *PEXAMPLE_DEVICE_EXTENSION;

// Определяем собственные коды IOCTL, с которыми можно будет 
// обращаться к драйверу при помощи вызова DeviceIoControl.
// Определение макроса CTL_CODE можно найти в файле DDK Winioctl.h.
// Там же можно найти и численные значения, скрывающиеся под именами
// METHOD_BUFFERED и METHOD_NEITHER.

// Внимание! Текст приведенный ниже должен войти в файл Ioctl.h,
// который будет необходим для компиляции тестового приложения.
// (Разумеется, за исключением последней строки с ‘#endif’.)

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

// Вариант :
//#define IOCTL_SEND_BYTE_TO_USER CTL_CODE( \
//    FILE_DEVICE_UNKNOWN, 0x805, METHOD_NEITHER, FILE_ANY_ACCESS)
#endif
