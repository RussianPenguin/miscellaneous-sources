// CMeterIcon Test.cpp : Defines the entry point for the application.
//
// Created: 04/02/2001 {mm/dm/yyyyy}
// Written by: Anish Mistry http://am-productions.yi.org/
/* This code is licensed under the GNU GPL.  See License.txt or (http://www.gnu.org/copyleft/gpl.html). */

#include "stdafx.h"
#include "resource.h"

BOOL CALLBACK DlgProc(HWND hwndDlg,UINT uMsg,WPARAM wParam,LPARAM lParam);
bool LoadStaticIcon(UINT ctrlID,HICON hIcon,HWND parentWnd);
bool OnInitDialog(HWND hDlg);
void OnRedraw(HWND hDlg);
void Draw(HWND hDlg);
void OnDestroy(HWND hDlg);
void OnAnimate(HWND hDlg);

CMeterIcon mi32;
CMeterIcon mi16;
HICON hFrame32 = NULL;
HICON hFrame16 = NULL;
HINSTANCE hInst = NULL;

int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{// begin WinMain
 	// TODO: Place code here.
	hInst = hInstance;
	DialogBox(hInstance,MAKEINTRESOURCE(IDD_DIALOG_MAIN),NULL,DlgProc);
 	return 0;
}// end WinMain

BOOL CALLBACK DlgProc(HWND hwndDlg,UINT uMsg,WPARAM wParam,LPARAM lParam)
{// begin DlgProc
	switch(uMsg)
	{// begin message switch
	case WM_INITDIALOG:
		return OnInitDialog(hwndDlg);
	case WM_COMMAND:
		switch(wParam)
		{// begin ctrl ID switch
		case IDOK: case IDCANCEL:
			EndDialog(hwndDlg,wParam);
			break;
		case IDC_BUTTON_REDRAW:
			OnRedraw(hwndDlg);
			break;
		case IDC_BUTTON_ANIMATE:
			OnAnimate(hwndDlg);
			break;
		}// end ctrl ID switch
		break;
	case WM_DESTROY:
		OnDestroy(hwndDlg);
		break;
	}// end message switch
	return false;
}// end DlgProc

bool LoadStaticIcon(UINT ctrlID,HICON hIcon,HWND parentWnd)
{// begin LoadStaticIcon
	// get control HWND
	HWND hwnd = GetDlgItem(parentWnd,ctrlID);
	// set icon
	DestroyIcon((HICON)SendMessage(hwnd,STM_SETIMAGE ,(WPARAM)IMAGE_ICON,(LPARAM)(HANDLE)hIcon));
	return true;
}// end LoadStaticIcon

bool OnInitDialog(HWND hDlg)
{// begin OnInitDialog
	// load the overlay icons
	hFrame32 = (HICON)LoadImage(hInst,MAKEINTRESOURCE(IDI_ICON_FRAME),IMAGE_ICON,32,32,LR_DEFAULTCOLOR);
	hFrame16 = (HICON)LoadImage(hInst,MAKEINTRESOURCE(IDI_ICON_FRAME),IMAGE_ICON,16,16,LR_DEFAULTCOLOR);
	// set the inital values for the bars
	SetDlgItemInt(hDlg,IDC_EDIT_VAL1,25,false);
	SetDlgItemInt(hDlg,IDC_EDIT_VAL2,90,false);
	SetDlgItemInt(hDlg,IDC_EDIT_VAL3,50,false);
	SetDlgItemInt(hDlg,IDC_EDIT_SPACING,3,false);
	SetDlgItemInt(hDlg,IDC_EDIT_MAXVAL,100,false);
	Draw(hDlg);
	// write the about box info
	SetDlgItemText(hDlg,IDC_EDIT_ABOUT,"CMeterIcon Test\r\nCopyright 2001 Anish Mistry\r\nhttp://am-productions.yi.org/\r\namistry@am-productions.yi.org");
	return true;
}// end OnInitDialog

void OnRedraw(HWND hDlg)
{// begin OnRedraw
	Draw(hDlg);	
}// end OnRedraw

void Draw(HWND hDlg)
{// begin Draw
	// get variables
	int nSpacing = GetDlgItemInt(hDlg,IDC_EDIT_SPACING,NULL,false);
	int nVal1 = GetDlgItemInt(hDlg,IDC_EDIT_VAL1,NULL,false);
	int nVal2 = GetDlgItemInt(hDlg,IDC_EDIT_VAL2,NULL,false);
	int nVal3 = GetDlgItemInt(hDlg,IDC_EDIT_VAL3,NULL,false);
	int nMaxVal = GetDlgItemInt(hDlg,IDC_EDIT_MAXVAL,NULL,false);
	// initilize the meter
	const int nNumBars32 = 3;
	const int nLevels32 = 4;
	const int nNumBars16 = 2;
	const int nLevels16 = 3;
	// set the limits of where the bar color changes (low-high)
	int pLimits32[nLevels32] = {25,35,87,100};
	int pLimits16[nLevels16] = {33,66,99};
	// set the corresponding color for each level
	COLORREF pColors32[nLevels32] = {RGB(255,0,0),RGB(255,255,0),RGB(0,255,0),RGB(0,255,255)};
	COLORREF pColors16[nLevels16] = {RGB(255,0,0),RGB(255,255,0),RGB(0,255,0)};
	// start it up
	mi32.Init(hFrame32,nMaxVal,nNumBars32,nSpacing,32,32,RGB(0,0,0));
	mi16.Init(hFrame16,nMaxVal,nNumBars16,nSpacing,16,16,RGB(0,0,0));
	// load our limit and color info
	mi32.SetColorLevels(pLimits32,pColors32,nLevels32);
	mi16.SetColorLevels(pLimits16,pColors16,nLevels16);
	// create an array of values for the bars
	int pVals32[nNumBars32] = {nVal1,nVal2,nVal3};
	int pVals16[nNumBars16] = {nVal1,nVal2};
	// generate the icon (destroy these icon using DestroyIcon())
	HICON hIcon32 = mi32.Create(pVals32);
	HICON hIcon16 = mi16.Create(pVals16);
	// load it into the control
	LoadStaticIcon(IDC_STATIC_32,hIcon32,hDlg);
	LoadStaticIcon(IDC_STATIC_16,hIcon16,hDlg);
}// end Draw

void OnDestroy(HWND hDlg)
{// begin OnDestroy
	DeleteObject(mi32.SetFrame(NULL));
	DeleteObject(mi16.SetFrame(NULL));
	LoadStaticIcon(IDC_STATIC_32,NULL,hDlg);
	LoadStaticIcon(IDC_STATIC_16,NULL,hDlg);
}// end OnDestroy

void OnAnimate(HWND hDlg)
{// begin OnAnimate
	HWND hIconWnd32 = GetDlgItem(hDlg,IDC_STATIC_32);
	HWND hIconWnd16 = GetDlgItem(hDlg,IDC_STATIC_16);
	HWND hVal1Wnd = GetDlgItem(hDlg,IDC_EDIT_VAL1);
	HWND hVal2Wnd = GetDlgItem(hDlg,IDC_EDIT_VAL2);
	HWND hVal3Wnd = GetDlgItem(hDlg,IDC_EDIT_VAL3);
	int nMaxVal = GetDlgItemInt(hDlg,IDC_EDIT_MAXVAL,NULL,false);
	for(int i = 0,j = nMaxVal;i <= nMaxVal;i++,j--)
	{
		SetDlgItemInt(hDlg,IDC_EDIT_VAL1,(i/2)+(j/3),false);
		SetDlgItemInt(hDlg,IDC_EDIT_VAL2,j,false);
		SetDlgItemInt(hDlg,IDC_EDIT_VAL3,i,false);
		OnRedraw(hDlg);
		UpdateWindow(hIconWnd32);
		UpdateWindow(hIconWnd16);
		UpdateWindow(hVal1Wnd);
		UpdateWindow(hVal2Wnd);
		UpdateWindow(hVal3Wnd);
		Sleep(15);
	}
}// end OnAnimate