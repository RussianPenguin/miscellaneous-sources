// XTFrameWnd.h interface for the CXTFrameWnd class.
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

#if !defined(__XTFRAMEWND_H__)
#define __XTFRAMEWND_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "XTCoolMenu.h"
#include "XTMenuBar.h"

/////////////////////////////////////////////////////////////////////////////
// CXTFrameWnd extends the standard CFrameWnd class to allow CXTDockWindow
// and CXTToolBar docking, customization and cool menu support.
/////////////////////////////////////////////////////////////////////////////
class _XT_EXT_CLASS CXTFrameWnd : public CFrameWnd
{
	DECLARE_DYNCREATE(CXTFrameWnd)

public:

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Constructor - handles default initialization
	CXTFrameWnd();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Destructor - handles clean up.
	virtual ~CXTFrameWnd();

protected:

	CXTCoolMenu	m_coolMenu;		// 
	CXTMenuBar	m_wndMenuBar;	// 
	CXTToolBar* m_pWndToolBar;	// 

public:

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	CXTCoolMenu* GetCoolMenu();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	CXTMenuBar* GetMenuBar();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	void InstallCoolMenus(const UINT* nIDToolBars, int nSize);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	void InstallCoolMenus(const UINT nIDToolBar);

	// -> Parameters:		lpszProfileName -	Name of a section in the initialization 
	//											file or a key in the Windows registry 
	//											where state information is stored.
	// -> Return Value:		
	// -> Remarks:			This member function is called by the frame window to 
	//						restore the settings of the control bar.
	virtual void LoadBarState(LPCTSTR lpszProfileName);

	// -> Parameters:		lpszProfileName -	Name of a section in the initialization 
	//											file or a key in the Windows registry 
	//											where state information is stored.
	// -> Return Value:		
	// -> Remarks:			This member function is called by the frame window to 
	//						save the settings of the control bar.
	virtual void SaveBarState(LPCTSTR lpszProfileName) const;

	// -> Parameters:		dwDockStyle -	Specifies whether the control bar supports 
	//										docking and the sides of its parent window to 
	//										which the control bar can be docked, if supported.
	//										Can be one or more of the following: 
	//
	//										CBRS_ALIGN_TOP		Allows docking at the top of 
	//															the client area.
	//										CBRS_ALIGN_BOTTOM   Allows docking at the bottom 
	//															of the client area.
	//										CBRS_ALIGN_LEFT		Allows docking on the left 
	//															side of the client area.
	//										CBRS_ALIGN_RIGHT	Allows docking on the right 
	//															side of the client area.
	//										CBRS_ALIGN_ANY		Allows docking on any side 
	//															of the client area.
	//										CBRS_FLOAT_MULTI	Allows multiple control bars 
	//															to be floated in a single 
	//															mini-frame window.
	//
	//										If 0 (that is, indicating no flags), the control 
	//										bar will not dock.
	// -> Return Value:		
	// -> Remarks:			Call this function to enable a control bar to be docked. 
	//						The sides specified must match one of the sides enabled for 
	//						docking in the destination frame window, or the control bar 
	//						cannot be docked to that frame window.
	void EnableDocking(DWORD dwDockStyle);

	// -> Parameters:		dwDockStyle -	Specifies whether the control bar supports 
	//										docking and the sides of its parent window to 
	//										which the control bar can be docked, if supported.
	//										Can be one or more of the following: 
	//
	//										CBRS_ALIGN_TOP		Allows docking at the top of 
	//															the client area.
	//										CBRS_ALIGN_BOTTOM   Allows docking at the bottom 
	//															of the client area.
	//										CBRS_ALIGN_LEFT		Allows docking on the left 
	//															side of the client area.
	//										CBRS_ALIGN_RIGHT	Allows docking on the right 
	//															side of the client area.
	//										CBRS_ALIGN_ANY		Allows docking on any side 
	//															of the client area.
	//										CBRS_FLOAT_MULTI	Allows multiple control bars 
	//															to be floated in a single 
	//															mini-frame window.
	//
	//										If 0 (that is, indicating no flags), the control 
	//										bar will not dock.
	//						dwFlatStyle	-	Specifies the spliters inside dock bars look
	//										Can be one of the following: 
	//
	//										CBRS_XT_NONFLAT		Thick devstudio like non flat 
	//															splitters
	//										CBRS_XT_SEMIFLAT	Thin 3D non flat splitters
	//										CBRS_XT_FLAT		Flat splitters
	// -> Return Value:		
	// -> Remarks:			Call this function to enable a control bar to be docked. 
	//						The sides specified must match one of the sides enabled for 
	//						docking in the destination frame window, or the control bar 
	//						cannot be docked to that frame window.
	void EnableDockingEx(DWORD dwDockStyle, DWORD dwFlatStyle);

	// -> Parameters:		pBar		-	Points to the control bar to be docked.
	//						pDockBar	-	
	//						lpRect		-	Determines, in screen coordinates, where the 
	//										control bar will be docked in the nonclient area 
	//										of the destination frame window.
	// -> Return Value:		
	// -> Remarks:			Causes a control bar to be docked to the frame window. The control
	//						bar will be docked to one of the sides of the frame window 
	//						specified in the calls to both CXTDockWindow::EnableDocking and 
	//						CXTFrameWnd::EnableDocking. The side chosen is determined by 
	//						pDockBar.
	void DockControlBar(CControlBar* pBar, CDockBar* pDockBar,	LPCRECT lpRect = NULL);

	// -> Parameters:		pBar		-	
	//						nDockBarID	-	Determines which sides of the frame window to 
	//										consider for docking. It can be 0, or one or 
	//										more of the following: 
	//
	//										AFX_IDW_DOCKBAR_TOP		Dock to the top side of 
	//																the frame window.
	//										AFX_IDW_DOCKBAR_BOTTOM	Dock to the bottom side 
	//																of the frame window.
	//										AFX_IDW_DOCKBAR_LEFT	Dock to the left side of 
	//																the frame window.
	//										AFX_IDW_DOCKBAR_RIGHT	Dock to the right side of 
	//																the frame window.
	//
	//										If 0, the control bar can be docked to any side 
	//										enabled for docking in the destination frame window.
	//						lpRect		-	Determines, in screen coordinates, where the 
	//										control bar will be docked in the nonclient area 
	//										of the destination frame window.
	// -> Return Value:		
	// -> Remarks:			Causes a control bar to be docked to the frame window. The control
	//						bar will be docked to one of the sides of the frame window 
	//						specified in the calls to both CXTDockWindow::EnableDocking and 
	//						CXTFrameWnd::EnableDocking. The side chosen is determined by 
	//						nDockBarID.
	void DockControlBar(CControlBar* pBar, UINT nDockBarID = 0,	LPCRECT lpRect = NULL);

	// -> Parameters:		pBar	-	Control bar to dock to the right of
	//						LeftOf	-	Already docked control bar
	// -> Return Value:		
	// -> Remarks:			This member function will dock the control bar passed in 
	//						as the first argument, and dock the control bar that is passed 
	//						in as the second argument to the left of the first one.
	virtual void DockControlBarLeftOf(CControlBar* Bar, CControlBar* LeftOf);

protected:

	//{{AFX_VIRTUAL(CXTFrameWnd)
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs, UINT uIcon);
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CXTFrameWnd)
	afx_msg void OnClose();
	afx_msg void OnSysColorChange();
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
	//}}AFX_MSG
	afx_msg LONG OnBarContextMenu(WPARAM wParam, LPARAM lParam);
	afx_msg void OnCustomizeBar();

	DECLARE_MESSAGE_MAP()
//---------------------------------------------------------------------------
// NOTE: The following methods are obsolete, and are included here only for
// support to users who have upgraded from CJLibrary.
//---------------------------------------------------------------------------
public:
	inline void EnableDockingSizeBar(DWORD dwDockStyle) {
		EnableDocking(dwDockStyle);
	}
	inline void DockSizeBar(CControlBar* pBar, CDockBar* pDockBar=NULL, LPRECT lpRect=NULL) {
		DockControlBar(pBar, pDockBar, lpRect);
	}
};

//---------------------------------------------------------------------------
inline CXTCoolMenu* CXTFrameWnd::GetCoolMenu()
	{ ASSERT(::IsWindow(m_hWnd)); return &m_coolMenu; }
//---------------------------------------------------------------------------
inline CXTMenuBar* CXTFrameWnd::GetMenuBar()
	{ ASSERT(::IsWindow(m_hWnd)); return &m_wndMenuBar; }
//---------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // #if !defined(__XTFRAMEWND_H__)
