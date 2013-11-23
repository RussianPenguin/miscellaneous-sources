/****************************************************************
 
FILE : TUXIDOW.C
DETAILS : APPLICATION IS INITIALISED , CHECKS CURRENT WINDOWS VERSION
CONTACT : tuxidow@yahoo.com

*****************************************************************/


#include "Tuxidow.h"

/******************************************************************************

   WinMain

******************************************************************************/

int PASCAL WinMain(  HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpCmdLine,
                     int nCmdShow)
{
	MSG  msg;
	HWND hwndMain ;
	if(!FindCurrentOS ())
		PrintError("Incompatible Windows Version.    \n\n    Designed for 2000/XP.  \n"); 
	CheckHardDisks();
	FindExt2FSDrives();

	if(!hPrevInstance)
		if(!InitApplication(hInstance))
			return FALSE;
	
	/* Perform initializations that apply to a specific instance */
	if (!(hwndMain = InitInstance(hInstance, nCmdShow)))
		return FALSE;

	/* Acquire and dispatch messages until a WM_QUIT uMessage is received. */
	while(GetMessage( &msg, NULL, 0x00, 0x00 ))
	{
		if (!TranslateAccelerator( hwndMain,// handle to receiving window 
						hAccTable,			// handle to active accelerator table 
						&msg))				// message data 
		{ 
			TranslateMessage(&msg); 
			DispatchMessage(&msg); 
		} 

	}
	return (int)msg.wParam;
}

void PrintError(char *msg)
{
	MessageBox(NULL , msg , "Error" , MB_OK | MB_ICONEXCLAMATION ) ;
	exit(0);
}

//Find the Operating system version.
//At present this only works in Windows 2000/XP
BOOL FindCurrentOS()
{

	//Microsoft Windows Server&nbsp;2003 family
	if ( _winmajor == 5 && _winminor == 2 ) 
		return TRUE;

	//Microsoft Windows XP 
	if ( _winmajor == 5 && _winminor == 1 )
		return TRUE;

	//Microsoft Windows 2000 
    if ( _winmajor == 5 && _winminor== 0 )
		return TRUE;

	if( _winmajor > 5) return TRUE;

	return FALSE;
             
}

