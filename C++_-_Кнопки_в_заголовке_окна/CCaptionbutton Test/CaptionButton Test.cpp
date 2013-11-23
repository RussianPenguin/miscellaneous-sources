// CaptionButton Test.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"
#include "CaptionButton.h"

#define MAX_LOADSTRING 100
#define IDC_STATIC_STATUS 101

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// The title bar text
CCaptionButton cbExtra;
HWND hStatusWnd = NULL;

// Foward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
void DisplayStatus(const char *pMessage);

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_CAPTIONBUTTONTEST, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_CAPTIONBUTTONTEST);

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage is only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_CAPTIONBUTTONTEST);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= (LPCSTR)IDC_CAPTIONBUTTONTEST;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= (HICON)LoadImage(hInstance,MAKEINTRESOURCE(IDI_CAPTIONBUTTONTEST),IMAGE_ICON,16,16,LR_LOADMAP3DCOLORS|LR_DEFAULTCOLOR);

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HANDLE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	hInst = hInstance; // Store instance handle in our global variable

	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
	  CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
	  return FALSE;
	}

	// subclass the window
	cbExtra.Init(hWnd);
	// set type of caption CB_APPWINDOW/CB_TOOLWINDOW
	cbExtra.SetCaptionType(CB_APPWINDOW);
	// what type of window CB_SDIMDI/CB_DIALOG
	cbExtra.SetWindowType(CB_SDIMDI);
	// set the number of regular captions
	cbExtra.SetNumOfDefaultCaptions(3);
	// set the images' transparency color
	COLORREF crTransparent = RGB(255,0,255);
	cbExtra.SetTransparentColor(crTransparent);
	// set the bitmap to be displayed
	cbExtra.SetSelectionBitmap((HBITMAP)LoadImage(hInstance,MAKEINTRESOURCE(IDB_SELECTION),IMAGE_BITMAP,0,0,LR_LOADMAP3DCOLORS|LR_DEFAULTCOLOR));
	// create our mouseover bitmaps (you could load them, but this way saves memory)
	HBITMAP hMouseOverBitmap = (HBITMAP)LoadImage(hInstance,MAKEINTRESOURCE(IDB_MOUSEOVER),IMAGE_BITMAP,0,0,LR_LOADMAP3DCOLORS|LR_DEFAULTCOLOR);
	// caption AM Productions
	HBITMAP hCaptionAMBitmap = (HBITMAP)LoadImage(hInstance,MAKEINTRESOURCE(IDB_BITMAP_AM),IMAGE_BITMAP,0,0,LR_LOADMAP3DCOLORS|LR_DEFAULTCOLOR);
	HBITMAP hCaptionAMBitmapHilite = CCaptionButton::CombineBitmaps(hCaptionAMBitmap,hMouseOverBitmap,crTransparent);
	// caption 2
	HBITMAP hCaption2Bitmap = (HBITMAP)LoadImage(hInstance,MAKEINTRESOURCE(IDB_BITMAP2),IMAGE_BITMAP,0,0,LR_LOADMAP3DCOLORS|LR_DEFAULTCOLOR);
	HBITMAP hCaption2BitmapHilite = CCaptionButton::CombineBitmaps(hCaption2Bitmap,hMouseOverBitmap,crTransparent);
	// caption 3
	HBITMAP hCaption3Bitmap = (HBITMAP)LoadImage(hInstance,MAKEINTRESOURCE(IDB_BITMAP3),IMAGE_BITMAP,0,0,LR_LOADMAP3DCOLORS|LR_DEFAULTCOLOR);
	HBITMAP hCaption3BitmapHilite = CCaptionButton::CombineBitmaps(hCaption3Bitmap,hMouseOverBitmap,crTransparent);

	cbExtra.New(1,hCaptionAMBitmapHilite,hCaptionAMBitmap,"AM Productions - Visit Now!");
	cbExtra.New(2,hCaption2BitmapHilite,hCaption2Bitmap,"Caption 2");
	cbExtra.New(3,hCaption3BitmapHilite,hCaption3Bitmap,"Caption 3");
	cbExtra.New(4,
	(HBITMAP)LoadImage(hInstance,MAKEINTRESOURCE(IDB_BITMAP5),IMAGE_BITMAP,0,0,LR_LOADMAP3DCOLORS|LR_DEFAULTCOLOR),
	(HBITMAP)LoadImage(hInstance,MAKEINTRESOURCE(IDB_BITMAP6),IMAGE_BITMAP,0,0,LR_LOADMAP3DCOLORS|LR_DEFAULTCOLOR),
	"Caption 4");

	// clean up
	DeleteObject(hMouseOverBitmap);

	// create a status static control
	hStatusWnd = CreateWindow("STATIC","Status",WS_CHILD|WS_VISIBLE|WS_BORDER,0,0,300,50,hWnd,(HMENU)IDC_STATIC_STATUS,hInst,NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;

	switch (message) 
	{
	case WM_CBLBUTTONCLICKED:
		switch(wParam)
		{// begin wParam
		case 1:
			DisplayStatus("AM Productions Caption pressed - Going to http://am-productions.yi.org/");
			ShellExecute(NULL,"open","http://am-productions.yi.org/",NULL,NULL,SW_SHOWNORMAL);
			break;
		case 2:
			cbExtra.New(8,
			(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(IDB_BITMAP5),IMAGE_BITMAP,0,0,LR_LOADMAP3DCOLORS|LR_DEFAULTCOLOR),
			(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(IDB_BITMAP6),IMAGE_BITMAP,0,0,LR_LOADMAP3DCOLORS|LR_DEFAULTCOLOR),
			"Caption 8",1);
			DisplayStatus("Caption 2 pressed - Created Caption 8 and inserted it at index 1");
			break;
		case 3:
			cbExtra.Delete(3);
			DisplayStatus("Caption 3 pressed - Deleted Caption 3");
			break;
		case 4:
			DisplayStatus("Caption 4 pressed");
			break;
		case 7:
			DisplayStatus("Caption 7 pressed");
			break;
		case 8:
			cbExtra.Replace(8,7,
			(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(IDB_BITMAP5),IMAGE_BITMAP,0,0,LR_LOADMAP3DCOLORS|LR_DEFAULTCOLOR),
			(HBITMAP)LoadImage(hInst,MAKEINTRESOURCE(IDB_BITMAP6),IMAGE_BITMAP,0,0,LR_LOADMAP3DCOLORS|LR_DEFAULTCOLOR),
			"Caption 7");
			DisplayStatus("Caption 8 pressed - Replaced Caption 8 with Caption 7");
			break;
		}// end wParam
		break;
		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// Parse the menu selections:
			switch (wmId)
			{
				case IDM_ABOUT:
				   DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
				   break;
				case IDM_EXIT:
				   DestroyWindow(hWnd);
				   break;
				default:
				   return DefWindowProc(hWnd, message, wParam, lParam);
			}
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}

// Mesage handler for about box.
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_INITDIALOG:
				return TRUE;

		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
			{
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			break;
	}
    return FALSE;
}

void DisplayStatus(const char *pMessage)
{// begin DisplayStatus
	if(hStatusWnd)
	{
		SetWindowText(hStatusWnd,pMessage);
	}
}// end DisplayStatus