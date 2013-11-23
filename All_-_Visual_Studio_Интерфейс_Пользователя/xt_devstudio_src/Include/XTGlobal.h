// XTGlobal.h interface for the XT_AUX_DATA struct.
//
// This file is a part of the Xtreme MFC Toolkit.
// ©2000 Codejock.com Software, All Rights Reserved.
//
// CODEJOCK.COM SOFTWARE GRANTS TO YOU (ONE SOFTWARE PROGRAMMER) THE
// LIMITED RIGHT TO USE THIS SOFTWARE ON A SINGLE COMPUTER FOR EVALUATION
// PURPOSES ONLY. THESE SOURCE FILE ARE CONSIDERED CONFIDENTIONAL AND ARE 
// THE PROPERTY OF CODEJOCK.COM SOFTWARE AND ARE NOT TO BE RE-DISTRIBUTED
// BY ANY MEANS WHATSOEVER WITHOUT THE EXPRESSED WRITTEN CONSENT OF 
// CODEJOCK.COM SOFTWARE.
//
// support@codejock.com
// http://www.codejock.com

//
//////////////////////////////////////////////////////////////////////

#if !defined(__XTGLOBALS_H__)
#define __XTGLOBALS_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

//----------------
// XT_TRACK_STATE:
//----------------
typedef enum XT_TRACK_STATE
{
	TRACK_NONE = 0,   // * normal, not tracking anything
	TRACK_BUTTON,     // * tracking buttons (F10/Alt mode)
	TRACK_POPUP       // * tracking popups
};

//--------------
// XT_DATA_TYPE:
//--------------
typedef enum XT_DATA_TYPE
{
	DT_INT = 1,		// sort type int
	DT_STRING,		// sort type string
	DT_DATETIME,	// sort type date / time
	DT_DEC			// sort type decimal
};

//---------
// XT_RCOB:
//---------
typedef enum XT_RCOB
{
	RC_OB_ICON = 1,
	RC_OB_LABEL,
	RC_OB_BOTH
};

//---------------------------------------------------
// XT_LVID - helper struct that holds list item data:
//---------------------------------------------------
typedef struct tagXT_LVID
{
   LPSHELLFOLDER lpsfParent;
   LPITEMIDLIST  lpi;
   ULONG         ulAttribs;
} XT_LVITEMDATA, *LPXT_LVITEMDATA;

//---------------------------------------------------
// XT_TVID - helper struct that holds tree item data:
//---------------------------------------------------
typedef struct tagXT_TVID
{
   LPSHELLFOLDER lpsfParent;
   LPITEMIDLIST  lpi;
   LPITEMIDLIST  lpifq;
} XT_TVITEMDATA, *LPXT_TVITEMDATA;

//------------
// XT_CMDINFO:
//------------
struct XT_CMDINFO
{
	LPCTSTR lpszItem;
	HICON	hIcon;
	UINT	nCmdID;
};

//----------------
// XT_OLDTOOLINFO:
//----------------
struct XT_OLDTOOLINFO
{
	UINT cbSize;
	UINT uFlags;
	HWND hwnd;
	UINT uId;
	RECT rect;
	HINSTANCE hinst;
	LPTSTR lpszText;
};

//----------------
// XT_OUTBAR_INFO:
//----------------
struct XT_OUTBAR_INFO 
{
	int		nIndex;
	int		nDragFrom;
	int		nDragTo;
	LPCTSTR	lpszText;
};

//-----------------
// XT_BARPLACEMENT:
//-----------------
struct XT_BARPLACEMENT
{
    CSize	sizeVert;
    CSize	sizeHorz;
    CSize	sizeFloat;
	CSize	sizeDefault;
	BOOL	bUnique;
	BOOL	bMaximized;
	DWORD	dwStyle;
};

//-------------------
// XT_DROPDOWNBUTTON:
//-------------------
struct XT_DROPDOWNBUTTON
{
	UINT	idButton;	// command ID of button
	UINT	idMenu;		// popup menu to display
};

//-------------
// XT_TCB_ITEM:
//-------------
struct XT_TCB_ITEM
{
	CWnd    *pWnd;			// this points to the window associated with a tab
	CString szTabLabel;		// label for the tab
	CString szToolTipLabel;	// tooltip text for the tab
    UINT    uiToolTipId;	// resource id for tooltip
};

//----------------
// XT_TOOLBARDATA:
//----------------
struct XT_TOOLBARDATA
{
	WORD wVersion;		// version # should be 1
	WORD wWidth;		// width of one bitmap
	WORD wHeight;		// height of one bitmap
	WORD wItemCount;	// number of items
	WORD items[1];		// array of command IDs, actual size is wItemCount
	
	WORD GetItem(int nItem) {
		return items[nItem];
	}

};

//-------------------
// XT_DLLVERSIONINFO:
//-------------------
struct XT_DLLVERSIONINFO
{
	DWORD cbSize;
	DWORD dwMajorVersion;	// Major version
	DWORD dwMinorVersion;	// Minor version
	DWORD dwBuildNumber;	// Build number
	DWORD dwPlatformID;		// DLLVER_PLATFORM_*
};

//---------------
// XT_CONTROLPOS:
//---------------
struct XT_CONTROLPOS
{
	int	  nID;
	int	  nIndex;
	CRect rectOldPos;
};

//------------
// XT_LOGFONT:
//------------
struct XT_LOGFONT : public LOGFONT
{
	XT_LOGFONT() {
		::ZeroMemory(this, sizeof(XT_LOGFONT));
		dwType = 0;
	}
	XT_LOGFONT(LOGFONT& logfont) {
		::CopyMemory((void*)&*this, (const void*)
			&logfont, (DWORD)sizeof(LOGFONT));
		dwType = 0;
	}
	void operator = (LOGFONT& logfont) {
		::CopyMemory((void*)&*this, (const void*)
			&logfont, (DWORD)sizeof(LOGFONT));
	}
	DWORD dwType;
};

//---------------
// XT_COLOR_FONT:
//---------------
struct XT_CLRFONT
{
	COLORREF   color;
	XT_LOGFONT logfont;
};

//-----------------
// XT_MENUITEMINFO:
//-----------------
struct XT_MENUITEMINFO : public MENUITEMINFO
{
	XT_MENUITEMINFO() {
		::ZeroMemory(this, sizeof(MENUITEMINFO));
		cbSize = sizeof(MENUITEMINFO);
	}
};

//--------------
// XT_SORT_ITEM:
//--------------
struct XT_SORT_ITEM
{
	XT_SORT_ITEM(const DWORD dwData, const CString &strItemText) {
		m_dwData = dwData;
		m_strItemText = strItemText;
	}
	DWORD	m_dwData;
	CString m_strItemText;
};

//----------------
// Class forwards:
//----------------
class CXTDateEdit;

//-------------------------
// XT_AUX_DATA global data:
//-------------------------
struct _XT_EXT_CLASS XT_AUX_DATA
{
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Constructor - handles default initialization
	XT_AUX_DATA();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Destructor - handles clean up.
	virtual ~XT_AUX_DATA();

	// (RGB) System colors used by Xtreme Toolkit
	COLORREF clr3DFace;			// Face color for three-dimensional display elements.
	COLORREF clr3DShadow;		// Shadow color for three-dimensional display elements.
	COLORREF clr3DDkShadow;		// Dark shadow for three-dimensional display elements.
	COLORREF clr3DHilight;		// Highlight color for three-dimensional display elements.
	COLORREF clr3DLight;		// Light color for three-dimensional display elements.
	COLORREF clrBtnText;		// Text on push buttons.
	COLORREF clrGrayText;		// Grayed (disabled) text.
	COLORREF clrHighlight;		// Item(s) selected in a control.
	COLORREF clrHighlightText;	// Text of item(s) selected in a control.
	COLORREF clrMenu;			// Menu background.
	COLORREF clrMenuText;		// Text in menus.
	COLORREF clrWindow;			// Window background.
	COLORREF clrWindowFrame;	// Window frame.
	COLORREF clrWindowText;		// Text in windows.
	COLORREF clrActiveCaption;	// Active window title bar.

	// Cursors used by Xtreme Toolkit
	HCURSOR hcurBeginDrag;		// Begin drag
	HCURSOR hcurDrag;			// Drag
	HCURSOR hcurHand;			// Hand
	HCURSOR hcurNoHand;			// No Hand
	HCURSOR hcurHSplitBar;		// Horzontal Splitter 
	HCURSOR hcurVSplitBar;		// Vertical Splitter
	HCURSOR hcurNoDrop;			// No drop

	// Icons used by Xtreme Toolkit
	HICON hIconHide;			// hide button icon
	HICON hIconMaxHDisable;		// horz max button icon disabled
	HICON hIconMaxHEnable;		// horz max button icon enabled
	HICON hIconMaxVDisable;		// vert max button icon disabled
	HICON hIconMaxVEnable;		// vert max button icon enabled
	HICON hIconHDisable;		// horz button icon disabled
	HICON hIconHEnabled;		// horz button icon enabled
	HICON hIconVDisable;		// vert button icon disabled
	HICON hIconVEnabled;		// vert button icon enabled
	HICON hIconPushed;			// pushed pin icon
	HICON hIconNormal;			// normal pin icon
	HICON hIconClose;			// close button.
	HICON hIconXtreme;			// 
	HICON hIconHomeDisable;		// 
	HICON hIconHomeEnable;		// 
	HICON hIconEndDisable;		// 
	HICON hIconEndEnable;		// 

	// System metrics for small icons.
	int cxSmIcon;				// cx small icon size.
	int cySmIcon;				// cy small icon size.
	int cxSize;					// Width in pixels, of a button in a window's caption or title bar.
	int cySize;					// Height, in pixels, of a button in a window's caption or title bar.
	int cxHThumb;				// Width, in pixels, of the thumb box in a horizontal scroll bar.
	int cyVThumb;				// Height, in pixels, of the thumb box in a vertical scroll bar.
	int cyMenuItem;				// Height, in pixels, of single-line menu bar. 

	CFont font;					// default GUI font.
	CFont fontBold;				// default bold GUI font.
	CFont fontULine;			// default underlined GUI font.
	CFont fontHCapt;			// default horz control bar caption font.
	CFont fontVCapt;			// default vert control bar caption font.

	CList<CWnd*,CWnd*> toolBarList;

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Loads cursors used by Xtreme Toolkit.
	void LoadSysCursors();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Creates image lists used by Xtreme Toolkit.
	void LoadSysIcons();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Creates fonts used by Xtreme Toolkit.
	void LoadSysFonts();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Frees cursor resources.
	void FreeSysCursors();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Frees icon resources.
	void FreeSysIcons();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Frees font resources.
	void FreeSysFonts();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Updates system colors used by Xtreme Toolkit.
	void UpdateSysColors();	

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Updates system metrics used by Xtreme Toolkit.
	void UpdateSysMetrics();

	static BOOL CALLBACK AFX_EXPORT EnumFontFamiliesExProc(
		ENUMLOGFONTEX* pelf, NEWTEXTMETRICEX* /*lpntm*/, int FontType,
		LPVOID pThis);
};

//-----------------------
// Access to global data:
//-----------------------
extern _XT_EXT_CLASS XT_AUX_DATA xtAfxData;

//-----------------------------
// UNICODE support definitions:
//-----------------------------
#ifdef	_UNICODE
#define	 UNICODE
#endif // _UNICODE

//-------------------------
// VC5 support definitions:
//-------------------------
#if _MSC_VER < 1200

#define _VC_VERSION_5

#define VERSION_WIN4					MAKELONG(0, 4)
#define VERSION_IE3						MAKELONG(70,4)
#define VERSION_IE4						MAKELONG(71,4)
#define VERSION_IE401					MAKELONG(72,4)

#define CBRS_GRIPPER					0x00400000L
#define AFX_IDW_REBAR					0x0000E804
#define AFX_IDW_DIALOGBAR				0x0000E805

#endif // _MSC_VER < 1200

#define AFX_IDW_MENUBAR					0x0000E806

//---------------------
// Registry key values:
//---------------------
static const TCHAR _xtAfxSettings[]			= _T("Settings");
static const TCHAR _xtAfxBarPlacement[]		= _T("Bar Position");
static const TCHAR _xtAfxWindowPlacement[]	= _T("Window Position");
static const TCHAR _xtAfxBarSection[]		= _T("%s-Bar%d");
static const TCHAR _xtAfxBarID[]			= _T("BarID");

//----------------
// Utility macros:
//----------------
#define _delete(p)			if(p){delete p;p=NULL;}
#define _deleteArray(p)		if(p){delete[] p;p=NULL;}
#define _IsDockWindow(p)	(BOOL)((CControlBar*)p)->IsKindOf(RUNTIME_CLASS(CXTDockWindow))
#define _IsMenuBar(p)		(BOOL)((CControlBar*)p)->IsKindOf(RUNTIME_CLASS(CXTMenuBar))
#define _cs2ch(cstring)		(TCHAR*)(LPCTSTR)cstring

//------------------------------------------------------
// Control bar ID's, all bars must be within this range:
//------------------------------------------------------
#define	XT_IDW_CONTROLBAR_MIN	0x00004268
#define	XT_IDW_CONTROLBAR_MAX	0x0000445C

//-------------------------
// Splitter Dock constants:
//-------------------------
#define XT_SPLITTER_VERT		0x00000001L
#define XT_SPLITTER_HORZ		0x00000002L

//-----------------------
// Docking Window styles:
//-----------------------
#define CBRS_XT_BUTTONS			0x00000001L	// has frame buttons
#define CBRS_XT_GRIPPER			0x00000002L	// has a gripper when docked
#define CBRS_XT_GRIPPER_FLAT	0x00000004L	// has a flat gripper must be used with CBRS_XT_GRIPPER
#define CBRS_XT_GRIPPER_GRAD	0x00000008L	// has a gradient flat gripper must be used with CBRS_XT_GRIPPER_FLAT
#define CBRS_XT_GRIPPER_TEXT	0x00000010L	// draws text in the gripper area when docked only valid with CBRS_XT_GRIPPER styles
#define CBRS_XT_BUTTONS_FLAT	0x00000020L	// draws buttons flat, only valid with CBRS_XT_BUTTONS style.
#define CBRS_XT_BORDERS_FLAT	0x00000040L	// draws the borders flat.
#define CBRS_XT_CLIENT_OUTLINE	0x00000080L	// draws an outline around the client area.
#define CBRS_XT_CLIENT_STATIC	0x00000100L // draws a static rect around the client area.
#define CBRS_XT_CLIENT_MODAL    0x00000200L // draws a modal rect around the client area.
#define CBRS_XT_SEMIFLAT		0x00000400L
#define CBRS_XT_NEWDOCKED		0x00000800L
#define CBRS_XT_TWOGRIP			0x00001000L
#define CBRS_XT_ALL_FLAT		0x00000064L
#define CBRS_XT_DEFAULT			0x00000013L

//--------------------
// Docking Bar styles:
//--------------------
#define CBRS_XT_NONFLAT			0x00000000L 
#define CBRS_XT_FLAT			CBRS_XT_BORDERS_FLAT 

//---------------
// Button Styles:
//---------------
#define BS_XT_FLAT				0x00000001L
#define BS_XT_SEMIFLAT			0x00000002L
#define BS_XT_CENTER    		0x00000004L
#define BS_XT_SHOWFOCUS 		0x00000008L

//--------------------
// Browse Edit Styles:
//--------------------
#define BES_XT_CHOOSEDIR   		0x00000001L
#define BES_XT_CHOOSEFILE		0x00000002L
#define BES_XT_POPUPMENU		0x00000004L

//--------------------
// Color Popup Styles:
//--------------------
#define CPS_XT_NOFILL			0x00000001L
#define CPS_XT_EXTENDED			0x00000002L
#define CPS_XT_MORECOLORS		0x00000004L
#define CPS_XT_PICKBOX			0x00000008L
#define CPS_XT_DEFAULT			0x00000010L

//---------------------
// Edit Listbox Styles:
//---------------------
#define LBS_XT_CHOOSEDIR 		BES_XT_CHOOSEDIR
#define LBS_XT_CHOOSEFILE		BES_XT_CHOOSEFILE
#define LBS_XT_NOTOOLBAR		0x00000008L

//-------------------
// Tip Window Styles:
//-------------------
#define TWS_XT_THICKBORDER		0x00000001L
#define TWS_XT_DROPSHADOW		0x00000002L

//-----------------------------
// Caption Popup Window Styles:
//-----------------------------
#define CPWS_EX_FLATEDGE		0x00000001L

//--------------------------------
// Flat Tab Control Window Styles:
//--------------------------------
#define FTS_XT_BOTTOM           0x00000001L
#define FTS_XT_HASARROWS        0x00000002L
#define FTS_XT_HASHOMEEND       0x00000004L // Must be used with FTS_XT_HASARROWS
#define FTS_XT_TOOLTIPS			0x00000008L
#define FTS_XT_DEFAULT 			0x0000000FL 

//-----------------------------------
// Outlook Bar Control Window Styles:
//-----------------------------------
#define OBS_XT_SMALLICON		0x00000001L
#define OBS_XT_LARGEICON		0x00000002L
#define OBS_XT_EDITGROUPS		0x00000004L
#define OBS_XT_EDITITEMS		0x00000008L
#define OBS_XT_REMOVEGROUPS		0x00000010L
#define OBS_XT_REMOVEITEMS		0x00000020L
#define OBS_XT_ADDGROUPS		0x00000040L
#define OBS_XT_DRAGITEMS		0x00000080L
#define OBS_XT_ANIMATION		0x00000100L
#define OBS_XT_SELHIGHLIGHT		0x00000200L
#define OBS_XT_DEFAULT			(OBS_XT_DRAGITEMS|OBS_XT_EDITGROUPS|OBS_XT_EDITITEMS|OBS_XT_REMOVEGROUPS|OBS_XT_REMOVEITEMS|OBS_XT_ADDGROUPS|OBS_XT_ANIMATION|OBS_XT_SELHIGHLIGHT)

//--------------------------------
// Color Popup Notification Codes:
//--------------------------------
#define CPN_XT_SELCHANGE		(WM_USER+1001)	// Color Picker Selection change
#define CPN_XT_DROPDOWN			(WM_USER+1002)	// Color Picker drop down
#define CPN_XT_CLOSEUP			(WM_USER+1003)	// Color Picker close up
#define CPN_XT_SELENDOK			(WM_USER+1004)	// Color Picker end OK
#define CPN_XT_SELENDCANCEL		(WM_USER+1005)	// Color Picker end (cancelled)
#define CPN_XT_SELNOFILL		(WM_USER+1006)	// Color Picker no fill

//---------------------------------
// Listbox Edit Notification Codes:
//---------------------------------
#define BEN_XT_LABELEDITEND		(WM_USER+1007)
#define BEN_XT_LABELEDITCANCEL	(WM_USER+1008)
#define LBN_XT_NEWITEM			(WM_USER+1009)
#define LBN_XT_DELETEITEM		(WM_USER+1010)
#define LBN_XT_MOVEITEMUP		(WM_USER+1011)
#define LBN_XT_MOVEITEMDOWN		(WM_USER+1012)

//-----------------------------------------
// Browse Edit (button) Notification Codes:
//-----------------------------------------
#define BEN_XT_BROWSEBUTTON		(WM_USER+1013)

//------------------------------
// Tray Icon Notification Codes:
//------------------------------
#define TIN_XT_TRAYICON			(WM_USER+1014)

//--------------------------------
// Control Bar Notification Codes:
//--------------------------------
#define CBRN_XT_CONTEXTMENU 	(WM_USER+1015)
#define CBRN_XT_DROPDOWN		(WM_USER+1016)

//----------------------------
// Menubar Notification Codes:
//----------------------------
#define MBN_XT_DESTROYMENU 		(WM_USER+1017)

//-----------------------------------------
// Caption Popup Window Nofification Codes:
//-----------------------------------------
#define CPWN_XT_PUSHPINBUTTON	(WM_USER+1018)
#define CPWN_XT_PUSHPINCANCEL	(WM_USER+1019)

//----------------------------------------
// Outlook Bar Control Nofification Codes:
//----------------------------------------
#define XTWM_OUTBAR_NOTIFY		(WM_USER+1020)
#define OBN_XT_ITEMCLICK		1
#define OBN_XT_ONLABELENDEDIT	2
#define OBN_XT_ONGROUPENDEDIT	3
#define OBN_XT_DRAGITEM			4
#define OBN_XT_FOLDERCHANGE		5
#define OBN_XT_ITEMHOVER		6

//--------------------------
// Shell Notification Codes:
//--------------------------
#define XTWM_SHELL_NOTIFY		(WM_USER+1021)
#define SHN_XT_SHELLMENU		1

//--------------------------------
// Color Popup Notification Codes:
//--------------------------------
#define ON_CPN_XT_SELCHANGE(id, memberFxn) \
	ON_CONTROL(CPN_XT_SELCHANGE, id, memberFxn)
#define ON_CPN_XT_DROPDOWN(id, memberFxn) \
	ON_CONTROL(CPN_XT_DROPDOWN, id, memberFxn)
#define ON_CPN_XT_CLOSEUP(id, memberFxn) \
	ON_CONTROL(CPN_XT_CLOSEUP, id, memberFxn)
#define ON_CPN_XT_SELENDOK(id, memberFxn) \
	ON_CONTROL(CPN_XT_SELENDOK, id, memberFxn)
#define ON_CPN_XT_SELENDCANCEL(id, memberFxn) \
	ON_CONTROL(CPN_XT_SELENDCANCEL, id, memberFxn)
#define ON_CPN_XT_SELNOFILL(id, memberFxn) \
	ON_CONTROL(CPN_XT_SELNOFILL, id, memberFxn)

//---------------------------------
// Listbox Edit Notification Codes:
//---------------------------------
#define ON_BEN_XT_LABELEDITEND(id, memberFxn) \
	ON_CONTROL(BEN_XT_LABELEDITEND, id, memberFxn)
#define ON_BEN_XT_LABELEDITCANCEL(id, memberFxn) \
	ON_CONTROL(BEN_XT_LABELEDITCANCEL, id, memberFxn)
#define ON_LBN_XT_NEWITEM(id, memberFxn) \
	ON_CONTROL(LBN_XT_NEWITEM, id, memberFxn)
#define ON_LBN_XT_DELETEITEM(id, memberFxn) \
	ON_CONTROL(LBN_XT_DELETEITEM, id, memberFxn)
#define ON_LBN_XT_MOVEITEMUP(id, memberFxn) \
	ON_CONTROL(LBN_XT_MOVEITEMUP, id, memberFxn)
#define ON_LBN_XT_MOVEITEMDOWN(id, memberFxn) \
	ON_CONTROL(LBN_XT_MOVEITEMDOWN, id, memberFxn)

//-----------------------------------------
// Browse Edit (button) Notification Codes:
//-----------------------------------------
#define ON_BEN_XT_BROWSEBUTTON(id, memberFxn) \
	ON_CONTROL(BEN_XT_BROWSEBUTTON, id, memberFxn)

//------------------
// Global functions:
//------------------
extern _XT_EXT_CLASS void    AFXAPI _xtAfxChangeWindowFont(CWnd* pWnd, CFont* pFont);
extern _XT_EXT_CLASS void    AFXAPI _xtAfxDrawEmbossed(CDC* pDC, CImageList& imageList, int nIndex, CPoint point, BOOL bInColor);
extern _XT_EXT_CLASS void	 AFXAPI _xtAfxDrawShadedRect(CDC *pDC, CRect& rect);
extern _XT_EXT_CLASS HBITMAP AFXAPI _xtAfxLoadSysColorBitmap(HINSTANCE hInst, HRSRC hRsrc, BOOL bMono=FALSE);
extern _XT_EXT_CLASS DWORD   AFXAPI _xtAfxGetComCtlVersion();
extern _XT_EXT_CLASS DWORD   AFXAPI _xtAfxRelease(LPUNKNOWN* lplpUnknown);
extern _XT_EXT_CLASS void    AFXAPI _xtAfxMakeOleVariant(COleVariant &ov, LPCITEMIDLIST pidl);
extern _XT_EXT_CLASS HWND    AFXAPI _xtAfxChildWindowFromPoint(HWND hWnd, POINT pt);

//------------------
// Global variables:
//------------------
extern _XT_EXT_CLASS int _xtAfxComCtlVersion;

//-------------------------------------------
// Color Popup Dialog Data Exchange routines:
//-------------------------------------------
extern _XT_EXT_CLASS void AFXAPI DDX_XTColorPicker(CDataExchange* pDX, int nIDC, COLORREF& value);

//-------------------------------------------
// Date Mask Dialog Data Validation routines:
//-------------------------------------------
extern _XT_EXT_CLASS void AFXAPI DDX_XTOleDateTime(CDataExchange* pDX, int nIDC, CXTDateEdit& rControl, COleDateTime& rDateTime);

//-----------------------------------------
// Date Time Dialog Data Exchange routines:
//-----------------------------------------
extern _XT_EXT_CLASS void AFXAPI DDX_XTDateTimeCtrl(CDataExchange* pDX, int nIDC, COleDateTime& value);
extern _XT_EXT_CLASS void AFXAPI DDX_XTDateTimeCtrl(CDataExchange* pDX, int nIDC, CTime& value);
extern _XT_EXT_CLASS void AFXAPI DDX_XTMonthCalCtrl(CDataExchange* pDX, int nIDC, COleDateTime& value);
extern _XT_EXT_CLASS void AFXAPI DDX_XTMonthCalCtrl(CDataExchange* pDX, int nIDC, CTime& value);

//-------------------------------------------
// Date Time Dialog Data Validation routines:
//-------------------------------------------
extern _XT_EXT_CLASS void AFXAPI DDV_XTMinMaxDateTime(CDataExchange* pDX, CTime& refValue, const CTime* pMinRange, const CTime* pMaxRange);
extern _XT_EXT_CLASS void AFXAPI DDV_XTMinMaxDateTime(CDataExchange* pDX,  COleDateTime& refValue, const COleDateTime* pMinRange, const COleDateTime* pMaxRange);
extern _XT_EXT_CLASS void AFXAPI DDV_XTMinMaxMonth(CDataExchange* pDX, CTime& refValue, const CTime* pMinRange, const CTime* pMaxRange);
extern _XT_EXT_CLASS void AFXAPI DDV_XTMinMaxMonth(CDataExchange* pDX, COleDateTime& refValue, const COleDateTime* pMinRange, const COleDateTime* pMaxRange);

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // #if !defined(__XTGLOBALS_H__)
