// XTControlBar.h : interface for the CXTControlBar class.
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

#if !defined(__XTCONTROLBAR_H__)
#define __XTCONTROLBAR_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CXTControlBar window
/////////////////////////////////////////////////////////////////////////////
class _XT_EXT_CLASS CXTControlBar : public CControlBar
{
	DECLARE_DYNAMIC(CXTControlBar)

protected:
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	CXTControlBar();
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual void SetBorders(LPCRECT lpRect);
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual void SetBorders(int cxLeft = 0, int cyTop = 0, int cxRight = 0, int cyBottom = 0);
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual CRect GetBorders() const;

	int				m_nPos;		// index of the pop-up menu contained in the menu
	bool			m_bInReBar;	// true if parent is a rebar.
	UINT			m_menuID;	// popup menu resource id
	XT_BARPLACEMENT	m_bp;		// placement struct to hold size and style information.

public:

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	bool InRebar() const;

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual ~CXTControlBar();
	
	// -> Parameters:	
	// -> Return Value:		The current CBRS_XT_ (control bar) settings for the control bar. 
	//						See ModifyXTBarStyle for the complete list of available styles.
	// -> Remarks:			Call this function to determine which CBRS_XT_ (control bar) 
	//						settings are currently set for the control bar. Does not 
	//						handle WS_ (window style) or CBRS_ (control bar style).
	virtual DWORD GetXTBarStyle();

	// -> Parameters:		dwStyle	-	New CBRS_XT_ style for the control bar, see 
	//									SetXTBarStyle() for availiable styles.
	// -> Return Value:		
	// -> Remarks:			This member function will set style for the control bar. Does not 
	//						handle WS_ (window style) or CBRS_ (control bar style).
	virtual void SetXTBarStyle(DWORD dwStyle);

	// -> Parameters:		dwRemove -	Specifies CBRS_XT_ styles to be removed during style 
	//									modification.
	//						dwAdd	 -	Specifies CBRS_XT_ styles to be added during style 
	//									modification.
	//
	//                      The desired styles for the control bar can be one or more of the 
	//						following:
	//
	//						CBRS_XT_BUTTONS			-	The control bar has a minimize and 
	//													close button when docked.
	//						CBRS_XT_GRIPPER			-	The control bar has a gripper when 
	//													docked.
	//						CBRS_XT_GRIPPER_FLAT	-	The control bar has a flat gripper, 
	//													use with CBRS_XT_GRIPPER.
	//						CBRS_XT_GRIPPER_GRAD	-	The control bar has a gradient flat 
	//													gripper use with CBRS_XT_GRIPPER_FLAT.
	//						CBRS_XT_GRIPPER_TEXT	-	The control bar draws text in the 
	//													gripper area, use with CBRS_XT_GRIPPER.
	//						CBRS_XT_BUTTONS_FLAT	-	The control bar min and max buttons 
	//													are flat, use with CBRS_XT_BUTTONS.
	//						CBRS_XT_BORDERS_FLAT	-	The control bar borders are flat.
	//						CBRS_XT_CLIENT_OUTLINE	-	Draw a single black border outline 
	//													around the client area.
	//						CBRS_XT_CLIENT_STATIC	-	Draw a static rect around the client
	//													area.
	//						CBRS_XT_CLIENT_MODAL	-	Draw a modal rect around the client 
	//													area.
	//						CBRS_XT_ALL_FLAT		-	The following styles combined by using 
	//													the bitwise OR (|) operator CBRS_XT_GRIPPER_FLAT, 
	//													CBRS_XT_BUTTONS_FLAT and CBRS_XT_BORDERS_FLAT.
	//						CBRS_XT_DEFAULT			-	The following styles combined by using 
	//													the bitwise OR (|) operator CBRS_XT_BUTTONS, 
	//													CBRS_XT_GRIPPER, CBRS_XT_GRIPPER_TEXT.
	//
	// -> Return Value:		Nonzero if style was successfully modified; otherwise, 0.
	// -> Remarks:			Call this member function to modify a control bar style. Styles to 
	//						be added or removed can be combined by using the bitwise OR (|) 
	//						operator. See SetXTBarStyle for information about the available 
	//						control bar styles.
	virtual BOOL ModifyXTBarStyle(DWORD dwRemove, DWORD dwAdd, BOOL bRedraw=TRUE);

	// -> Parameters:		menuID	 -	Resource ID of the menu to be used.
	//						nPos	 -	Zero based index of the popup menu located in the
	//									menu resource. For example IDR_MAINFRAME's "File"
	//									popup menu would be 0.
	// -> Return Value:	
	// -> Remarks:			This member function is used to set the resource id for the 
	//						popup menu associated with the control bar.
	virtual void SetMenuID(UINT menuID, int nPos=0);

	// -> Parameters:	
	// -> Return Value:		A UNIT value that represents the popup menu ID associated
	//						with the control bar.
	// -> Remarks:			This member function returns the resource id of the popup menu.
	virtual UINT GetMenuID();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual void DoPaint(CDC* pDC);
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual void DrawGripper(CDC* pDC, const CRect& rect);
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual LRESULT WindowProc(UINT nMsg, WPARAM wParam, LPARAM lParam);
	
	// -> Parameters:		input CRect should be client rectangle size
	// -> Return Value:		
	// -> Remarks:			adjusts borders etc
	virtual void CalcInsideRect(CRect& rect, BOOL bHorz) const;
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual void EraseNonClient();
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual void DrawBorders(CDC* pDC, CRect& rect);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			added to use always CXTDockContext	
	virtual void EnableDocking(DWORD dwDockStyle);

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

	// -> Parameters:		
	// -> Return Value:		Nonzero if docked on the left side; otherwise 0.
	// -> Remarks:			This member function is used to determine if the control bar 
	//						is docked on the left side.
	virtual BOOL IsLeftDocked() const;

	// -> Parameters:		
	// -> Return Value:		Nonzero if docked on the right side; otherwise 0.
	// -> Remarks:			This member function is used to determine if the control bar 
	//						is docked on the right side.
	virtual BOOL IsRightDocked() const;

	// -> Parameters:		
	// -> Return Value:		Nonzero if docked on the top side; otherwise 0.
	// -> Remarks:			This member function is used to determine if the control bar 
	//						is docked on the top side.
	virtual BOOL IsTopDocked() const;

	// -> Parameters:		
	// -> Return Value:		Nonzero if docked on the bottom side; otherwise 0.
	// -> Remarks:			This member function is used to determine if the control bar 
	//						is docked on the bottom side.
	virtual BOOL IsBottomDocked() const;

	// -> Parameters:		
	// -> Return Value:		Nonzero if docked on the top or bottom side; otherwise 0.
	// -> Remarks:			This member function is used to determine if the control bar 
	//						is docked on the top or bottom side.
	virtual BOOL IsHorzDocked() const;

	// -> Parameters:		
	// -> Return Value:		Nonzero if docked on the left or right side; otherwise 0.
	// -> Remarks:			This member function is used to determine if the control bar 
	//						is docked on the left or right side.
	virtual BOOL IsVertDocked() const;

	// -> Parameters:		
	// -> Return Value:		Nonzero if floating; otherwise 0.
	// -> Remarks:			This member function is used to determine if the control bar 
	//						is docked or floating.
	virtual BOOL IsFloating() const;

protected:
	
	//{{AFX_VIRTUAL(CXTControlBar)
	//}}AFX_VIRTUAL
	
	//{{AFX_MSG(CXTControlBar)
	afx_msg void OnWindowPosChanging(LPWINDOWPOS lpWndPos);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnNcPaint();
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

	friend class CXTReBar;
};

//---------------------------------------------------------------------------
inline bool CXTControlBar::InRebar() const
	{ ASSERT(::IsWindow(m_hWnd)); return m_bInReBar; }
//---------------------------------------------------------------------------
inline void CXTControlBar::SetBorders(LPCRECT lpRect)
	{ /*ASSERT(::IsWindow(m_hWnd));*/ SetBorders(lpRect->left, lpRect->top, lpRect->right, lpRect->bottom); }
//---------------------------------------------------------------------------
inline CRect CXTControlBar::GetBorders() const
	{ /*ASSERT(::IsWindow(m_hWnd));*/ return CRect(m_cxLeftBorder, m_cyTopBorder, m_cxRightBorder, m_cyBottomBorder); }
//---------------------------------------------------------------------------
inline UINT CXTControlBar::GetMenuID()
	{ /*ASSERT(::IsWindow(m_hWnd));*/ return m_menuID; }
//---------------------------------------------------------------------------
inline void CXTControlBar::SetMenuID(UINT menuID, int nPos)
	{ /*ASSERT(::IsWindow(m_hWnd));*/ m_menuID=menuID; m_nPos=nPos; }
//---------------------------------------------------------------------------
inline BOOL CXTControlBar::IsVertDocked() const
	{ ASSERT(::IsWindow(m_hWnd)); return (IsLeftDocked() || IsRightDocked()); }
//---------------------------------------------------------------------------
inline BOOL CXTControlBar::IsHorzDocked() const
	{ ASSERT(::IsWindow(m_hWnd)); return (IsTopDocked() || IsBottomDocked()); }
//---------------------------------------------------------------------------
inline BOOL CXTControlBar::IsBottomDocked() const
	{ ASSERT(::IsWindow(m_hWnd)); return (GetParent()->GetDlgCtrlID()==AFX_IDW_DOCKBAR_BOTTOM); }
//---------------------------------------------------------------------------
inline BOOL CXTControlBar::IsTopDocked() const
	{ ASSERT(::IsWindow(m_hWnd)); return (GetParent()->GetDlgCtrlID()==AFX_IDW_DOCKBAR_TOP); }
//---------------------------------------------------------------------------
inline BOOL CXTControlBar::IsRightDocked() const
	{ ASSERT(::IsWindow(m_hWnd)); return (GetParent()->GetDlgCtrlID()==AFX_IDW_DOCKBAR_RIGHT); }
//---------------------------------------------------------------------------
inline BOOL CXTControlBar::IsLeftDocked() const
	{ ASSERT(::IsWindow(m_hWnd)); return (GetParent()->GetDlgCtrlID()==AFX_IDW_DOCKBAR_LEFT); }
//---------------------------------------------------------------------------
inline BOOL CXTControlBar::IsFloating() const
	{ ASSERT(::IsWindow(m_hWnd)); return (!IsHorzDocked() && !IsVertDocked()); }
//---------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // #if !defined(__XTCONTROLBAR_H__)
