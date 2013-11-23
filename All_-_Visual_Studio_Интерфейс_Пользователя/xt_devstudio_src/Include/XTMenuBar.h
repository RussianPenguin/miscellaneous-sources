// XTMenuBar.h interface for the CXTMenuBar class.
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

#if !defined(__XTMENUBAR_H__)
#define __XTMENUBAR_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "XTToolBar.h"
#include "XTWndHook.h"

/////////////////////////////////////////////////////////////////////////////
// CXTMenuBar implements an Office style menu bar. Use it the way you would
// a CToolBar, only you need to call LoadMenuBar instead of LoadToolbar.
/////////////////////////////////////////////////////////////////////////////
class _XT_EXT_CLASS CXTMenuBar : public CXTToolBar
{
	DECLARE_DYNAMIC(CXTMenuBar)

public:

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Constructor - handles default initialization
	CXTMenuBar();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Destructor - handles clean up.
	virtual ~CXTMenuBar();

protected:

	int					m_iPopupTracking;		// which popup I'm tracking if any
	int					m_iNewPopup;			// next menu to track
	int					m_iTracking;			// which button I'm tracking
	int					m_xMin;					// min x pos for min/restore/close buttons
	BOOL				m_bProcessRightArrow;	// process l/r arrow keys?
	BOOL				m_bProcessLeftArrow;	// ...
	BOOL				m_bEscapeWasPressed;	// user pressed escape to exit menu
	BOOL				m_bMenuRemoved;			// TRUE when the system menu is removed from a floating menubar.
	BOOL				m_bDown;				// whether it's up or down
	BOOL				m_bMDIMaximized;		// whether on or not
	CRect				m_rects[4];				// rects: icon, min, restore, close
	CPoint				m_ptMouse;				// mouse location when tracking popup
	HWND				m_hWndMDIClient;		// if this is an MDI app
	HMENU				m_hMenu;				// the currently active menu
	HMENU				m_hAppMenu;				// handle to the menu loaded via LoadMenuBar.
	HMENU				m_hMenuTracking;		// current popup I'm tracking
	HMENU				m_hMenuWindow;			// "Window" menu
	XT_TRACK_STATE		m_iTrackingState;		// current tracking state
	CXTMBarWndHook		m_frameHook;			// hooks frame window messages
	CXTMBarWndHook		m_childFrameHook;		// hooks MDI client messages

	CList<CString*, CString*>	m_arStrings;	// array of menu strings

	static CXTMenuBar*	m_pMenuBar;				// 
	static HHOOK		m_hMsgHook;				// 

public:

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			This function translates special menu keys and mouse actions, and
	//						is called from CXTFrameWnd's PreTranslateMessage.
	virtual BOOL TranslateFrameMessage(MSG* pMsg);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Load a different menu. The HMENU must not belong to any CMenu, and 
	//						you must free it when you're done. Returns old menu hMenuWindow is 
	//						MDI "Window" menu, if any (similar to WM_MDISETMENU).
	HMENU LoadMenu(HMENU hMenu, HMENU hMenuWindow);
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	HMENU GetMenu();
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	BOOL LoadMenuBar(UINT nMenuID);
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	BOOL LoadMenuBar(LPCTSTR lpszMenuName);
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	XT_TRACK_STATE GetTrackingState(int& iPopup);
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual BOOL Create(CWnd* pParentWnd,
		DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_TOP,
		UINT nID = AFX_IDW_MENUBAR);
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual BOOL CreateEx(CWnd* pParentWnd, DWORD dwCtrlStyle = TBSTYLE_FLAT,
		DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP,
		CRect rcBorders = CRect(0, 0, 0, 0),
		UINT nID = AFX_IDW_MENUBAR);

protected:

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Adjust client rectangle of menubar by shrinking it to 
	//						allow room for MDI icon and min/max/close
	virtual void	AdjustClientRect(CRect& rcClient);
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Compute the rectangles for icon and min/restore/close buttons.
	virtual void	CalcSysButtonLayout();
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Determine which button, if any, a point is in (pt in client coords).
	virtual int		MDIHitTest(CPoint pt);
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Given button rectangle, compute point and "exclude rect" for
	//						TrackPopupMenu, based on current docking style, so that the menu will
	//						appear always inside the window.
	virtual CPoint  ComputeMenuTrackPoint(const CRect& rcButton, TPMPARAMS& tpm);
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Initialize MDI "Window" menu by adding names of all the MDI children.
	//						This duplicates what the default handler for WM_MDISETMENU does, but
	//						it's necessary to reinvent the wheel since menu bars manage the menu
	//						themselves. This function is called when the frame gets WM_INITMENUPOPUP.
	virtual void	OnInitWindowMenu();
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Draw single button in up or down state
	virtual void	DrawButton(CDC& dc, int i, BOOL bPressed);
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Handle a mouse message: look for click on one of my buttons.
	//						Returns TRUE if handled; ie, caller should eat the mouse message.
	virtual BOOL OnMouseMessage(UINT message, UINT nFlags, CPoint pt);
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Make frame recalculate control bar sizes after menu change
	void  RecomputeToolbarSize();
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Recompute layout of menu bar: ie client/non-client layout,
	//						when MDI maximized state has chagned
	void	RecomputeMenuLayout();
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Get button index before/after a given button
	int	GetNextOrPrevButton(int iButton, BOOL bPrev);
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Set tracking state: none, button, or popup
	void	SetTrackingState(XT_TRACK_STATE iState, int iButton=-1);
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Track the popup submenu associated with the i'th button in the menu bar.
	//						This fn actually goes into a loop, tracking different menus until the user
	//						selects a command or exits the menu.
	void	TrackPopup(int iButton);
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Toggle state from home state to button-tracking and back
	void	ToggleTrackButtonMode();
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Cancel the current popup menu by posting WM_CANCELMODE, and track a new
	//						menu. iNewPopup is which new popup to track (-1 to quit).
	void	CancelMenuAndTrackNewOne(int iButton);
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	void	OnInitMenuPopup();
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			When user selects a new menu item, note whether it has a submenu
	//						and/or parent menu, so I know whether right/left arrow should
	//						move to the next popup.
	void  OnMenuSelect(HMENU hMenu, UINT nItemID);
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			MDI maximized state may have changed: if so, need
	//						to add/delete min/max/close buttons from menu bar
	void  CheckMinMaxState();
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	BOOL	IsValidButton(int iButton) const;
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Handle menu input event: Look for left/right to change popup menu,
	//						mouse movement over over a different menu button for "hot" popup effect.
	//						Returns TRUE if message handled (to eat it).
	virtual BOOL OnMenuInput(MSG& m);
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Bar style changed: eg, moved from left to right dock or floating
	virtual void OnBarStyleChange(DWORD dwOldStyle, DWORD dwNewStyle);
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			This is to correct a bug in the system toolbar control: TB_HITTEST only
	//						looks at the buttons, not the size of the window. So it returns a button
	//						hit even if that button is totally outside the size of the window!
	int HitTest(CPoint p) const;
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	void WrapMenuBar(BOOL bWrapMenuBar);
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	CSize CalcFloatingLayout();

	//{{AFX_VIRTUAL(CXTMenuBar)
	virtual CSize CalcFixedLayout(BOOL bStretch, BOOL bHorz);
	virtual CSize CalcDynamicLayout(int nLength, DWORD nMode);
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CXTMenuBar)
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint pt);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnNcCalcSize(BOOL bCalc, NCCALCSIZE_PARAMS* pncp);
	afx_msg void OnNcPaint();
	afx_msg void OnWindowPosChanged(WINDOWPOS FAR* lpwndpos);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG

	afx_msg LRESULT OnDestroyMenu(WPARAM wParam, LPARAM lParam);
	afx_msg void OnUpdateMenuButton(CCmdUI* pCmdUI);
	
	DECLARE_MESSAGE_MAP()

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Menu filter hook just passes to virtual CXTMenuBar function
	static LRESULT CALLBACK MenuInputFilter(int code, WPARAM wParam, LPARAM lParam);

	friend class CXTMBarWndHook;

//---------------------------------------------------------------------------
// NOTE: The following methods are obsolete, and are included here only for
// support to users who have upgraded from CJLibrary.
//---------------------------------------------------------------------------
public:
	inline 	BOOL LoadMenu(UINT nID) {
		return LoadMenuBar(nID);
	}
};

//---------------------------------------------------------------------------
inline BOOL CXTMenuBar::IsValidButton(int iButton) const
	{ ASSERT(::IsWindow(m_hWnd)); return 0 <= iButton && iButton < GetButtonCount(); }
//---------------------------------------------------------------------------
inline XT_TRACK_STATE CXTMenuBar::GetTrackingState(int& iPopup)
	{ ASSERT(::IsWindow(m_hWnd)); iPopup = m_iPopupTracking; return m_iTrackingState; }
//---------------------------------------------------------------------------
inline HMENU CXTMenuBar::GetMenu()
	{ ASSERT(::IsWindow(m_hWnd)); return m_hMenu; }
//---------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // #if !defined(__XTMENUBAR_H__)
