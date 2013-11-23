// XTDockWindow.h interface for the CXTDockWindow class.
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

#if !defined(__XTDOCKWINDOW_H__)
#define __XTDOCKWINDOW_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "XTControlBar.h"

// forwards
class CXTBarButton;

/////////////////////////////////////////////////////////////////////////////
// CXTDockWindow is a CXTControlBar derived class which is simular to
// the sizing / docking windows that are seen in Developer Studio.
/////////////////////////////////////////////////////////////////////////////
class _XT_EXT_CLASS CXTDockWindow : public CXTControlBar
{
	DECLARE_DYNAMIC(CXTDockWindow)

public:
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Constructor - handles default initialization.
	CXTDockWindow();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Destructor - handles cleanup and de-allocation.
	virtual ~CXTDockWindow();

protected:

	int				m_cxOffset;		// used to offset the horizontal client area to allow room for the caption when docked.
	int				m_nBtnIndex;	// used to determine which button icon to display when the control bar is minimized or maximized depending on which side docked.
	CWnd*			m_pChildWnd;	// CWnd pointer which is contains child window that is displayed in the control bar, see SetChild(CWnd* pWnd).
	CXTBarButton*	m_pBtnClose;	// close button used in caption area.
	CXTBarButton*	m_pBtnMinim;	// minimize button used in the caption area.
	CToolTipCtrl	m_ToolTip;		// tooltip used for caption buttons.

public:

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

	// -> Parameters:		pParentWnd	-	Pointer to the window that is the control bar’s 
	//										parent.
	//						nID			-	The control bar’s window ID.
	//						lpszCaption -	Points to a null-terminated character string that 
	//										represents the control bar name. Used as text for 
	//										the caption.
	//						size		-	Specifies the default size of the control bar.
	//						dwStyle		-	The control bar style. Additional toolbar styles 
	//										supported are: 
	//
	//										CBRS_TOP			-	Control bar is at top 
	//																of the frame window.
	//										CBRS_BOTTOM			-	Control bar is at bottom 
	//																of the frame window.
	//										CBRS_NOALIGN		-	Control bar is not repositioned
	//																when the parent is resized.
	//										CBRS_TOOLTIPS		-	Control bar displays tool tips.
	//										CBRS_SIZE_DYNAMIC   -	Control bar is dynamic.
	//										CBRS_SIZE_FIXED		-	Control bar is fixed.
	//										CBRS_FLOATING		-	Control bar is floating.
	//										CBRS_FLYBY			-	Status bar displays information
	//																about the button. 
	//										CBRS_HIDE_INPLACE   -	Control bar is not displayed 
	//																to the user. 
	//						dwBarStyle	-	Specifies CBRS_XT_ styles to be used during creation,
	//										see SetXTBarStyle for information about the available 
	//										control bar styles.
	// -> Return Value:		Nonzero if successful; otherwise 0.
	// -> Remarks:			This member function creates a CXTDockWindow (a docking window). 
	//						It also sets the control bar default size, style, ID and caption text.
	virtual BOOL Create( CWnd* pParentWnd, UINT nID, LPCTSTR lpszCaption=NULL, 
		CSize size=CSize(200,100), DWORD dwStyle=CBRS_LEFT, DWORD dwBarStyle=CBRS_XT_DEFAULT);

	// -> Parameters:		rect	-	Reference to a CRect object that is to receive the
	//									size of the insize rect for the child window associated 
	//									with the control bar.
	// -> Return Value:		
	// -> Remarks:			This member function is called to return the default size for 
	//						a the child window associated with the control bar.
	virtual void GetInsideRect(CRect& rect);

	// -> Parameters:		
	// -> Return Value:		The minimum extent for a minimized control bar.
	// -> Remarks:			This member function is called to determine the minimum extent 
	//						of the control bar when miminized or maximized.
	virtual int GetMinExt();

	// -> Parameters:		
	// -> Return Value:		Nonzero if docked control bar is maximized; otherwise 0.
	// -> Remarks:			This member function is used to determine if the docked control 
	//						bar is maximized.
	virtual BOOL IsMaximized() const;

	// -> Parameters:		size -	A reference to a CSize object that contains the normal
	//								size that the control bar should be.
	// -> Return Value:	
	// -> Remarks:			This member function is called to set the normal size the for 
	//						the control bar.
	virtual void SetNormalSize(const CSize &size);

	// -> Parameters:	
	// -> Return Value:	
	// -> Remarks:			This member function is called to return the control bar to 
	//						its normal size.
	virtual void Normalize();

	// -> Parameters:	
	// -> Return Value:	
	// -> Remarks:			This member function is called to minimize the control bar.
	virtual int Minimize();
	
	// -> Parameters:	
	// -> Return Value:	
	// -> Remarks:			This member function is called to maximize the control bar.
	virtual void Maximize(int size);

	// -> Parameters:		dwStyle	-	Specifies whether the control bar supports docking 
	//									and the sides of its parent window to which the 
	//									control bar can be docked, if supported. Can be one 
	//									or more of the following: 
	//
	//										CBRS_ALIGN_TOP	  -	Allows docking at the 
	//															top of the client area.
	//										CBRS_ALIGN_BOTTOM -	Allows docking at the 
	//															bottom of the client area.
	//										CBRS_ALIGN_LEFT   -	Allows docking on the left 
	//															side of the client area.
	//										CBRS_ALIGN_RIGHT  -	Allows docking on the right 
	//															side of the client area.
	//										CBRS_ALIGN_ANY	  - Allows docking on any side 
	//															of the client area.
	//										CBRS_FLOAT_MULTI  -	Allows multiple control bars 
	//															to be floated in a single 
	//															mini-frame window. If 0 (that 
	//															is, indicating no flags), the 
	//															control bar will not dock.
	// -> Return Value:	
	// -> Remarks:			Call this function to enable a control bar to be docked. The sides 
	//						specified must match one of the sides enabled for docking in the 
	//						destination frame window, or the control bar cannot be docked to 
	//						that frame window.
	virtual void EnableDocking(DWORD dwDockStyle);

	// -> Parameters:	
	// -> Return Value:		An int value that represents the current width of the control
	//						bar when docked vertical.
	// -> Remarks:			This member function is used to determine the width of the
	//						control bar when docked vertical.
	virtual int GetVertSize();

	// -> Parameters:	
	// -> Return Value:		An int value that represents the current height of the control
	//						bar when docked horizontal.
	// -> Remarks:			This member function is used to determine the width of the
	//						control bar when docked horizontal.
	virtual int GetHorzSize();

	// -> Parameters:	strSection	-	Name of a section in the initialization file or a key 
	//									in the Windows registry where state information is stored.
	// -> Return Value:	
	// -> Remarks:		Call this function to restore the settings of each control bar owned by 
	//					the frame window. This information is written to the initialization file 
	//					using SaveBarSize. Information restored includes visibility, 
	//					horizontal/vertical orientation, docking state, and control-bar position.
	//					This function call is handled by CXTFrameWnd::LoadBarState, and should
	//					not be called directly.
	void LoadBarSize(CString strSection);

	// -> Parameters:	strSection	-	Name of a section in the initialization file or a key 
	//									in the Windows registry where state information is stored.
	// -> Return Value:	
	// -> Remarks:		Call this function to store information about each control bar owned by 
	//					the frame window. This information can be read from the initialization file 
	//					using LoadBarSize. Information stored includes visibility, 
	//					horizontal/vertical orientation, docking state, and control bar position.
	//					This function call is handled by CXTFrameWnd::SaveBarState, and should
	//					not be called directly.
	void SaveBarSize(CString strSection);

protected:

	// -> Parameters:	
	// -> Return Value:	
	// -> Remarks:		
	virtual void DelayShow(BOOL bShow);

	// -> Parameters:	
	// -> Return Value:	Returns a CRect value that represents the size and location of the first 
	//					grip line in the caption area when docked.
	// -> Remarks:		This member function is called to caluclate the size of the gripper displayed
	//					in the caption area of a docked control bar.
	virtual CRect GetGripperRect();

	// -> Parameters:	
	// -> Return Value:	Returns a CRect value that represents the size and location of the 
	//					close frame button when the docked.
	// -> Remarks:		This member function is called to calculate the size of the frame buttons
	//					used in the caption area of a docked control bar.
	virtual CRect GetButtonRect();

	// -> Parameters:	pDC -	Points to a device context. The function draws the gripper into 
	//							this device context. 
	// -> Return Value:	
	// -> Remarks:		This member function is called by the control bar to draw the gripper in
	//					the caption area of a docked control bar.
	virtual void DrawGripper(CDC* pDC);

	// -> Parameters:	pWnd -	Points to the child CWnd object that is associated with the control
	//							bar. This pointer is used to resize the child window accordingly.
	// -> Return Value:	
	// -> Remarks:		This member function is used to associate a child window that is to be 
	//					displayed in the control bar.
	virtual void SetChild(CWnd* pWnd);

	// -> Parameters:	pDC	 -	Points to a device context. The function draws the borders into 
	//							this device context. 
	//					rect -	A reference to a CRect object that represents the size of the
	//							border to be drawn.
	// -> Return Value:	
	// -> Remarks:		This member function is called by the control bar to draw its borders.
	virtual void DrawBorders(CDC *pDC, CRect &rect);

	// -> Parameters:	
	// -> Return Value:	
	// -> Remarks:		This member function is called by the control bar to perform 
	//					paint operations.
	virtual void EraseNonClient();

	// -> Parameters:		pBP -	Points to a XT_BARPLACEMENT struct which is used to
	//								initialize the placement for the control bar.
	// -> Return Value:	
	// -> Remarks:		This member function is called to initialize the XT_BARPLACEMENT struct
	//					which contains size, location and style information for the control bar.
	virtual void SetBarPlacement(XT_BARPLACEMENT* pBP);

	// -> Parameters:		pDC			-	
	//						rect		-	
	// -> Return Value:		
	// -> Remarks:			
	virtual void DrawCaption(CDC* pDC, const CRect& rect);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXTDockWindow)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);
	virtual CSize CalcDynamicLayout(int nLength, DWORD nMode);
	virtual void DoPaint(CDC* pDC);
 	//}}AFX_VIRTUAL

// Generated message map functions
protected:
	//{{AFX_MSG(CXTDockWindow)
	afx_msg UINT OnNcHitTest(CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnWindowPosChanged(WINDOWPOS FAR* lpwndpos);
	afx_msg void OnButtonClose();
	afx_msg void OnUpdateButtonClose(CCmdUI* pCmdUI);
	afx_msg void OnButtonMinimize();
	afx_msg void OnUpdateButtonMinimize(CCmdUI* pCmdUI);
	afx_msg void OnWindowPosChanging(WINDOWPOS FAR* lpwndpos);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

	friend class CXTDockBar;
	friend class CXTFrameWnd;
	friend class CXTSplitterDock;

//---------------------------------------------------------------------------
// NOTE: The following methods are obsolete, and are included here only for
// support to users who have upgraded from CJLibrary.
//---------------------------------------------------------------------------
public:
	DWORD& m_eChildBorder;
	inline void EnableDockingOnSizeBar(DWORD dwDockStyle) {
		EnableDocking(dwDockStyle);
	}
	inline void SetMenuID(UINT menuID, UINT popToolbarID=0, int nPos=0) {
		CXTControlBar::SetMenuID(menuID, nPos);
	}
	inline void EnableFlatLook(BOOL bFlat=TRUE) {
		ModifyXTBarStyle(bFlat?0:CBRS_XT_ALL_FLAT, bFlat?CBRS_XT_ALL_FLAT:0);
	}
	inline void GetChildRect(CRect &rect) {
		GetInsideRect(rect);
	}
};

//---------------------------------------------------------------------------
inline int CXTDockWindow::GetVertSize()
	{ ASSERT(::IsWindow(m_hWnd)); return m_bp.sizeDefault.cx; }
//---------------------------------------------------------------------------
inline int CXTDockWindow::GetHorzSize()
	{ ASSERT(::IsWindow(m_hWnd)); return m_bp.sizeDefault.cy; }
//---------------------------------------------------------------------------
inline void CXTDockWindow::SetChild(CWnd *pWnd)
	{ ASSERT(::IsWindow(m_hWnd)); m_pChildWnd=pWnd; }
//---------------------------------------------------------------------------
inline BOOL CXTDockWindow::IsMaximized() const
	{ ASSERT(::IsWindow(m_hWnd)); return (m_bp.bMaximized); }
//---------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // #if !defined(__XTDOCKWINDOW_H__)

