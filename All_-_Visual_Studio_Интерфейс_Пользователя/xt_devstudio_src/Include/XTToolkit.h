// XTToolkit.h : header file
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

#if !defined(__XTTOOLKIT_H__)
#define __XTTOOLKIT_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

//----------------------------
// X~treme version definition:
//----------------------------
#define _XTLIB_VERSION_			0x10000
#define _XTLIB_VERSION_MAJOR	1
#define _XTLIB_VERSION_MINOR	02

#define _XT_EXT_CLASS	__declspec( dllimport )

#if defined( _DEBUG )
	#pragma comment(lib, "XT102DemoLibd.lib") 
	#pragma message("Automatically linking with XT102DemoLibd.dll")
#else
	#pragma comment(lib, "XT102DemoLib.lib")
	#pragma message("Automatically linking with XT102DemoLib.dll")
#endif

//---------------------
// MFC support classes:
//---------------------
#include <afxole.h>         // MFC OLE classes
#include <afxpriv.h>		// MFC support for docking windows
#include <afxtempl.h>		// MFC template classes
#include <afxcview.h>		// MFC ListView / TreeView support
#include <..\src\afximpl.h>	// MFC Global data
#include <shlobj.h>			// MFC support for shell extensions

//-----------------------------------------
// X~treme global and resource definitions:
//-----------------------------------------
#include "XTGlobal.h"
#include "XTResource.h"

//-----------------------------------------------
// X~treme control bars -
// Replaces: CControlBar, CDockBar, CDockContext:
//-----------------------------------------------
#include "XTControlBar.h"
#include "XTDialogBar.h"
#include "XTDockBar.h"
#include "XTDockWindow.h"
#include "XTTabCtrlBar.h"
#include "XTDockContext.h"
#include "XTSplitterDock.h"

//------------------------------------------------------
// X~treme toolbars - 
// Replaces: CToolBar, CToolBarCtrl, CReBar, CReBarCtrl:
//------------------------------------------------------
#include "XTToolBar.h"
#include "XTMenuBar.h"
#include "XTToolBarCtrl.h"
#include "XTReBar.h"
#include "XTReBarCtrl.h"

//------------------------------------------------------------------------------------
// X~treme frame windows -
// Replaces: CFrameWnd, CMDIFrameWnd, CMDIChildWnd, COleIPFrameWnd, CMiniDockFrameWnd:
//------------------------------------------------------------------------------------
#include "XTFrameWnd.h"
#include "XTMDIFrameWnd.h"
#include "XTMDIChildWnd.h"
#include "XTOleIPFrameWnd.h"
#include "XTMiniDockFrameWnd.h"

//--------------------------
// X~treme shell extensions:
//--------------------------
#include "XTShell.h"
#include "XTShellList.h"
#include "XTShellTree.h"
#include "XTTrayIcon.h"
#include "XTBrowseDialog.h"

//-------------------------
// X~treme control classes:
//-------------------------
#include "XTButton.h"
#include "XTHexEdit.h"
#include "XTMaskEdit.h"
#include "XTBrowseEdit.h"
#include "XTCaption.h"
#include "XTCaptionPopupWnd.h"
#include "XTColorPicker.h"
#include "XTColorPopup.h"
#include "XTFontCombo.h"
#include "XTFlatComboBox.h"
#include "XTComboBoxEx.h"
#include "XTTabCtrl.h"
#include "XTFlatTabCtrl.h"
#include "XTTreeCtrl.h"
#include "XTListCtrl.h"
#include "XTEditListBox.h"
#include "XTFlatHeaderCtrl.h"
#include "XTOutBarCtrl.h"
#include "XTOutlookBar.h"
#include "XTPagerCtrl.h"
#include "XTDateTimeCtrl.h"
#include "XTHyperLink.h"
#include "XTTipWindow.h"
#include "XTTipOfTheDay.h"
#include "XTSplitterWnd.h"
#include "XTStatusBar.h"
#include "XTLogoPane.h"

//-----------------------
// X~treme CView classes:
//-----------------------
#include "XTHtmlView.h"
#include "XTListView.h"
#include "XTPreviewView.h"
#include "XTTabView.h"

//----------------------------
// X~treme utility classes:
//----------------------------
#include "XTMemDC.h"
#include "XTWindowPos.h"
#include "XTWndHook.h"
#include "XTCoolMenu.h"
#include "XTMemFile.h"
#include "XTSortClass.h"

/////////////////////////////////////////////////////////////////////////////

#endif // #if !defined(__XTTOOLKIT_H__)
