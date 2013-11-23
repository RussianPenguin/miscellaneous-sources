// XTFlatComboBox.h interface for the CXTFlatComboBox class.
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

#if !defined(__XTFLATCOMBOBOX_H__)
#define __XTFLATCOMBOBOX_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CXTFlatComboBox is a CComboBox derived class which is simular to
// the flat combobox as seen in the Microsoft office products.
/////////////////////////////////////////////////////////////////////////////
class _XT_EXT_CLASS CXTFlatComboBox : public CComboBox
{
	DECLARE_DYNAMIC(CXTFlatComboBox)

public:
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Constructor - handles default initialization.
	CXTFlatComboBox();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Destructor - handles cleanup and de-allocation.
	virtual ~CXTFlatComboBox();

protected:

	// enum used to determine the state the combo box should be
	enum STATE { NORMAL = 1, RAISED = 2, PRESSED = 3 };

	BOOL		m_bLBtnDown;		// TRUE if left mouse button is pressed
	BOOL		m_bPainted;			// used during paint operations
	BOOL		m_bHasFocus;		// TRUE if control has focus
	BOOL		m_bAutoComp;		// Used by Autocompleting.
	BOOL		m_bFlatLook;		// 
	int			m_cxHThumb;			// 

public:

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	void DisableFlatLook(BOOL bDisable);

	// -> Parameters:		bEnable - TRUE to enable auto completion; otherwise FALSE.
	// -> Return Value:		
	// -> Remarks:			This member function enables or disables auto completion.
	virtual void EnableAutoCompletion(BOOL bEnable=TRUE);

	// -> Parameters:		
	// -> Return Value:		TRUE if the mouse is over the combo box; otherwise FALSE.
	// -> Remarks:			This member function determines if the mouse is within the 
	//						controls rect.
	virtual BOOL PointInRect();

protected:

	// -> Parameters:		eState			-	Current state of the combo box, either
	//											NORMAL, RAISED, or PRESSED.
	//						clrTopLeft		-	RGB color value for top left 3D borders.
	//						clrBottomRight	-	RGB color value for bottom right 3D borders.
	//						pDC				-	Points to the current device context.
	// -> Return Value:		
	// -> Remarks:			This member function is called by the combo box whenever 
	//						a paint operation should occur.
	virtual void DrawCombo(STATE eState, COLORREF clrTopLeft, COLORREF clrBottomRight, CDC* pDC=NULL);

	//{{AFX_VIRTUAL(CXTFlatComboBox)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CXTFlatComboBox)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnPaint();
	afx_msg void OnSetFocus();
	afx_msg void OnKillFocus();
	afx_msg void OnEditUpdate();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

//---------------------------------------------------------------------------
inline void CXTFlatComboBox::DisableFlatLook(BOOL bDisable)
	{ m_bFlatLook = !bDisable; }
//---------------------------------------------------------------------------
inline void CXTFlatComboBox::EnableAutoCompletion(BOOL bEnable/*=TRUE*/)
	{ ASSERT(::IsWindow(m_hWnd)); m_bAutoComp = bEnable; }
//---------------------------------------------------------------------------
inline BOOL CXTFlatComboBox::PointInRect()
	{ ASSERT(::IsWindow(m_hWnd)); CPoint pt; GetCursorPos(&pt); CRect rcItem; GetWindowRect(&rcItem); return rcItem.PtInRect(pt); }
//---------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // #if !defined(__XTFLATCOMBOBOX_H__)
