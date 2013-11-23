// XTColorPopup.h : interface for the CXTColorPopup class.
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

#if !defined(__XTCOLORPOPUP_H__)
#define __XTCOLORPOPUP_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "XTButton.h"

/////////////////////////////////////////////////////////////////////////////
// CXTCPButton window
/////////////////////////////////////////////////////////////////////////////
class _XT_EXT_CLASS CXTCPButton : public CXTButton
{
	DECLARE_DYNAMIC(CXTCPButton)

public:

	// -> Parameters:		pParentWnd	-	A pointer to the parent window.
	//						clrColor	-	RGB color value the button is to display
	//						bPickBox	-	TRUE if the button is a color pick box.
	//						bDefault	-	TRUE if the button is a default button.
	// -> Return Value:		
	// -> Remarks:			Constructor - handles default initialization
	CXTCPButton(CWnd* pParentWnd, COLORREF clrColor, DWORD dwPopup);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Destructor - handles clean up.
	virtual ~CXTCPButton();

	int		 m_nIndex;		// 0 based index for color button, set after creation.

protected:

	DWORD	 m_dwPopup;		// Represents the current style of the color popup window.
	BOOL	 m_bDefault;	// TRUE if the button should behave like a standard CXTButton.
	BOOL	 m_bPickBox;	// TRUE if the button is a color box pick button.
	COLORREF m_clrColor;	// Represents the color the button should display, only valid when m_bPickBox is TRUE.
	CWnd*	 m_pParentWnd;	// Points to the parent color popup window.
	CRect	 m_rcWnd;		// Size of the popup window.

	//{{AFX_VIRTUAL(CXTCPButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CXTCPButton)
	afx_msg void OnClicked();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

	friend class CXTColorPopup;
};

/////////////////////////////////////////////////////////////////////////////
// CXTColorPopup window
/////////////////////////////////////////////////////////////////////////////
class _XT_EXT_CLASS CXTColorPopup : public CWnd
{
	DECLARE_DYNAMIC(CXTColorPopup)

public:

	// -> Parameters:		bAutoDelete	-	TRUE if the color picker window is to be self deleting.
	// -> Return Value:		
	// -> Remarks:			Constructor - handles default initialization
	CXTColorPopup(BOOL bAutoDelete=FALSE);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Destructor - handles clean up.
	virtual ~CXTColorPopup();

	// -> Parameters:		pButton -	A return pointer to the currently selected button.
	// -> Return Value:		Returns the zero (0) based index of the currently selected button.
	// -> Remarks:			This member function will return the index of the currently
	//						selected button and will initialize pButton to the current button.
	virtual int GetCurSel(CXTCPButton* pButton = NULL);

	// -> Parameters:		nIndex -	An interger value that represents the zero (0) based
	//									index of the button to be selected.
	// -> Return Value:		
	// -> Remarks:			This member function will select a button based upon its index.
	virtual void SetCurSel(int nIndex);

	// -> Parameters:		rect		-	A reference to a CRect object that represents the
	//										size of the color popup window.
	//						pParentWnd	-	Points to the parent window for the color popup.
	//						dwPopup		-	Style for the popup window. Styles to can be one or 
	//										more of the following:
	//
	//										CPS_NOFILL		-	The color picker will display a 
	//															No Fill button rather than the 
	//															default Automatic Color button.
	//										CPS_EXTENDED	-	The color picker will display 40 
	//															extended colors rather than the 
	//															default 16 colors.
	//										CPS_MORECOLORS	-	The color picker will display a 
	//															More Colors
	//
	//						clrColor	-	Currently selected RGB color value for the popup window.
	//						clrDefault	-	Specifies the default color for the color popup. If the
	//										current style includes CPS_NOFILL this parameter is
	//										ignored.
	// -> Return Value:		Returns TRUE if successful.
	// -> Remarks:			This member function handles the creation of the color popup window.
	virtual BOOL Create(CRect& rect, CWnd* pParentWnd, DWORD dwPopup, COLORREF clrColor, COLORREF clrDefault=CLR_DEFAULT);

protected:

	// -> Parameters:		nCurSel		-	Current index of the selected color box or button
	//										in the color popup window.
	//						clrColor	-	RGB color value of the selected color box or button
	//										in the color popup window.
	// -> Return Value:		
	// -> Remarks:			This member function will finish the selection process for the color
	//						box or button in color popup window.
	virtual void EndSelection(int nCurSel, COLORREF clrColor);

	DWORD			m_dwPopup;		// color popup window style.
	int				m_nRows;		// Number of rows in the color popup window.
	int				m_nCols;		// Number of columns in the color popup window.
	int				m_nLastIndex;	// Index of the last button on the popup window.
	int				m_nBtnCount;	// Number of buttons in this window.
	int				m_nCurSel;		// Currently selected index.
	CSize			m_sizeButton;	// cx and cy size for a color pick button.
	CWnd*			m_pParentWnd;	// Points to the parent window for the popup window.
	CToolTipCtrl	m_tooltip;		// Tooltip control.
	COLORREF		m_clrColor;		// RGB value of the currently selected color.
	COLORREF		m_clrDefault;	// Represents the default color for the popup window.
	CRect			m_rcWnd;		// Rect for popup window.
	BOOL			m_bAutoDelete;	// TRUE if the popup window is to be self deleting.
	BOOL			m_bColorDlg;

	// CList array which contains all of the buttons that are to be displayed.
	CList<CButton*, CButton*>	m_btnList;

	//{{AFX_VIRTUAL(CXTColorPopup)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Generated message map functions
protected:
	//{{AFX_MSG(CXTColorPopup)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnDestroy();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	friend class CXTCPButton;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // #if !defined(__XTCOLORPOPUP_H__)
