// XTFlatTabCtrl.h interface for the CXTFlatTabCtrl class.
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

#if !defined(__XTFLATTABCTRL_H__)
#define __XTFLATTABCTRL_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "XTButton.h"

/////////////////////////////////////////////////////////////////////////////
// CXTFTButton is a CXTButton derived class used to create owner drawn buttons
// that display an icon for enabled and disabled states.
/////////////////////////////////////////////////////////////////////////////
class _XT_EXT_CLASS CXTFTButton : public CXTButton
{
	DECLARE_DYNAMIC(CXTFTButton)

public:
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Constructor - handles default initialization.
	CXTFTButton();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Destructor - handles cleanup and de-allocation.
	virtual ~CXTFTButton();

	// -> Parameters:		size		  -	CSize object that represents the size of the icon.
	//						hIconEnabled  -	Handle to the enabled icon.
	//						hIconDisabled -	Handle to the disabled icon.
	//						bRedraw		  -	Specifies whether the button is to be redrawn. A 
	//										nonzero value redraws the button. A 0 value does not 
	//										redraw the button. The button is redrawn by default.
	// -> Return Value:		TRUE if successful, otherwise FALSE.
	// -> Remarks:			This member function will set the enabled and disabled state icons
	//						for the push button.
	virtual BOOL SetIcon(CSize size, HICON hIconEnabled, HICON hIconDisabled, BOOL bRedraw=TRUE);

protected:

	HICON m_hIconEnabled;	// handle to the icon to be displayed when the button is enabled.
	HICON m_hIconDisabled;	// handle to the icon to be displayed when the button is disabled.

	// -> Parameters:		pDC		-	A CDC pointer that represents the current device 
	//									context.
	//						nState	-	A UINT value that represents the current state 
	//									for the button.
	//						rcItem	-	A CRect reference that represents the current 
	//									size for the button.
	// -> Return Value:		
	// -> Remarks:			This member function draws the icon for the button, if any.
	virtual void DrawButtonIcon(CDC* pDC, UINT nState, CRect& rcItem);

	//{{AFX_MSG(CXTFTButton)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CXTFlatTabCtrl window
/////////////////////////////////////////////////////////////////////////////
class _XT_EXT_CLASS CXTFlatTabCtrl : public CWnd
{
	DECLARE_DYNAMIC(CXTFlatTabCtrl)

public:

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Constructor - handles default initialization.
	CXTFlatTabCtrl();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Destructor - handles cleanup and de-allocation.
	virtual ~CXTFlatTabCtrl();

protected:

    CToolTipCtrl	m_ToolTip;				// Tooltip for the flat tab control.
	CXTFTButton		m_btnHome;				// Home arrow button.
	CXTFTButton		m_btnLeft;				// Left arrow button.
	CXTFTButton		m_btnRight;				// Right arrow button.
	CXTFTButton		m_btnEnd;				// End arrow button.
	HICON			m_hIconHome;			// Handle to the home arrow icon.
	HICON			m_hIconHomeDisabled;	// Handle to the disabled home arrow icon.
	HICON			m_hIconLeft;			// Handle to the left arrow icon.
	HICON			m_hIconLeftDisabled;	// Handle to the disabled left arrow icon.
	HICON			m_hIconRight;			// Handle to the right arrow icon.
	HICON			m_hIconRightDisabled;	// Handle to the disabled right arrow icon.
	HICON			m_hIconEnd;				// Handle to the home end icon.
	HICON			m_hIconEndDisabled;		// Handle to the disabled end arrow icon.
	DWORD			m_dwStyle;				// Tab control style.
	int				m_cx;					// Width for each arrow button.
	int				m_cy;					// Height for each arrow button.
	int				m_nCurSel;				// Index of the currently selected tab.
	int				m_nClientWidth;			// Height in pixels of the tab control client area.
	int				m_nClientHeight;		// Width in pixels of the tab control client area.
	int				m_nTotalTabWidth;		// Width in pixels of all the tabs combined.
	int				m_nOffset;				// Ammount in pixels of the displayed tab offset.
	CStringArray	m_TabList;				// Array of CString objects that represent each tab.
	CStringArray	m_TabTipList;			// Array of CString objects that represent each tabs tool tip.

public:

	// -> Parameters:		nItem	-	Index of the tab to insert.
	//						nTextID	-	String resource ID of the tab label.
	// -> Return Value:		TRUE if successful; otherwise FALSE.
	//						otherwise FALSE.
	// -> Remarks:			This member function will insert a tab into the flat tab control.
	virtual BOOL InsertItem(int nItem, UINT nTextID);

	// -> Parameters:		nItem		-	Index of the tab to insert.
	//						lpszItem	-	NULL terminated string that represents the tab label.
	// -> Return Value:		TRUE if successful; otherwise FALSE.
	//						otherwise FALSE.
	// -> Remarks:			This member function will insert a tab into the flat tab control.
	virtual BOOL InsertItem(int nItem, LPCTSTR lpszItem);

	// -> Parameters:		nItem		-	Index of the tab to delete.
	// -> Return Value:		TRUE if successful; otherwise FALSE.
	// -> Remarks:			This member function will delete the tab specified by nItem from 
	//						the tab control.
	virtual BOOL DeleteItem(int nItem);

	// -> Parameters:		
	// -> Return Value:		TRUE if successful; otherwise FALSE.
	// -> Remarks:			This member function will remove all of the tabs from the tab control.
	virtual BOOL DeleteAllItems();

	// -> Parameters:		nItem	-	Index of the tab.
	//						lpRect	-	Points to a RECT structure to receive the size of the tab.
	// -> Return Value:		TRUE if successful; otherwise FALSE.
	// -> Remarks:			This member function will retrieve the size of the tab specified 
	//						by nItem.
	virtual BOOL GetItemRect(int nItem, LPRECT lpRect);

	// -> Parameters:		pHitTestInfo	-	Pointer to aTCHITTESTINFO structure, as 
	//											described in the Platform SDK, which specifies 
	//											the screen position to test.
	// -> Return Value:		Returns the zero-based index of the tab or  – 1 if no tab is at 
	//						the specified position.
	// -> Remarks:			Call this function to determine which tab, if any, is at the 
	//						specified screen position.
	virtual int HitTest(TCHITTESTINFO *pHitTestInfo) const;

	// -> Parameters:		
	// -> Return Value:		Zero-based index of the selected tab if successful or  – 1 if 
	//						no tab is selected.
	// -> Remarks:			Call this function to retrieve the currently selected tab in a 
	//						flat tab control.
	virtual int GetCurSel() const;

	// -> Parameters:		nItem	-	The zero-based index of the item to be selected.
	// -> Return Value:		Zero-based index of the previously selected tab if successful, 
	//						otherwise  – 1.
	// -> Remarks:			Selects a tab in a flat tab control.
	virtual int SetCurSel(int nItem);

	// -> Parameters:		
	// -> Return Value:		Number of items in the tab control.
	// -> Remarks:			Call this function to retrieve the number of tabs in the tab control.
	virtual int GetItemCount() const;

	// -> Parameters:		nItem		-	The zero-based index of tab to receive the tooltip text.
	//						lpszTabTip	-	A pointer to a string containing the tooltip text.
	// -> Return Value:		
	// -> Remarks:			This member function will set the tooltip for the tab specified
	//						by nItem.
    virtual void SetTipText(int nItem, LPCTSTR lpszTabTip);

	// -> Parameters:		nItem	-	The zero-based index of the tab to retrieve the tooltip 
	//									text for.
	// -> Return Value:		A CString object containing the text to be used in the tooltip.
	// -> Remarks:			This member function will return the tooltip text assocaited with
	//						the tab specified by nItem.
    virtual CString GetTipText(int nItem);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			This member function will cause the tab control to reposition
	//						the tabs to the home position.
    virtual void Home();

	//{{AFX_VIRTUAL(CXTFlatTabCtrl)
	virtual BOOL Create(DWORD dwStyle, const CRect& rect, CWnd* pParentWnd, UINT nID);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

protected:

	// -> Parameters:		nItem	-	The zero-based index of the tab to retrieve the width for.
	// -> Return Value:		Returns the width in pixels of the tab.
	// -> Remarks:			This member function will return the width in pixels of the tab
	//						specified by nItem.
	int GetTabWidth(int nItem) const;

	// -> Parameters:		
	// -> Return Value:		Returns the total width in pixels of all the tabs in the flat tab
	//						control combined.
	// -> Remarks:			This member function will return the total width of all of the tabs
	//						in the flat tab control.
	int GetTotalTabWidth() const;

	// -> Parameters:		
	// -> Return Value:		Returns the total width in pixels of all the visible arrow buttons.
	// -> Remarks:			This member function will return the total width of all of the arrow
	//						buttons that are visible in the flat tab control.
	int GetTotalArrowWidth() const;

	// -> Parameters:		pDC			 -	Points to the device context to draw the tab to.
	//						pt			 -	XY location of the top left corner of the tab to draw.
	//						bSelected	 -	true if the tab is currently selected.
	//						lpszTabLabel -	A NULL terminated string that represents the tab label.
	// -> Return Value:		Returns the x position of the next tab to be drawn.
	// -> Remarks:			This member function will draw a tab to the device context specified
	//						by pDC.
	int DrawTab(CDC* pDC, const CPoint& pt, bool bSelected, LPCTSTR lpszTabLabel) const;

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			This member function will force all of the tabs to be repainted.
	void InvalidateTabs();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			This member function will enable / disable the arrow buttons
	//						depending on the current tab display state.
	void EnableButtons();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			This member function will free the resources allocated for the
	//						icons used by the arrow buttons.
	void FreeButtonIcons();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			This member function will create the icon resources that are
	//						used by the arrow buttons.
	void CreateButtonIcons();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			This member function will update the system metrics for tab
	//						navigation buttons and create fonts used by the tabs.
	void UpdateMetrics();

	//{{AFX_MSG(CXTFlatTabCtrl)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLeftArrow();
	afx_msg void OnRightArrow();
	afx_msg void OnHomeArrow();
	afx_msg void OnEndArrow();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

//---------------------------------------------------------------------------
// NOTE: The following methods are obsolete, and are included here only for
// support to users who have upgraded from CJLibrary.
//---------------------------------------------------------------------------
public:
	inline BOOL Create( LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL) {
		return Create(dwStyle, rect, pParentWnd, nID);
	}
};

//---------------------------------------------------------------------------
inline BOOL CXTFlatTabCtrl::InsertItem(int nItem, UINT nTextID)
	{ ASSERT(IsWindow(m_hWnd)); CString strItem; strItem.LoadString(nTextID); return InsertItem(nItem, strItem); }
//---------------------------------------------------------------------------
inline int CXTFlatTabCtrl::GetCurSel() const
	{ ASSERT(IsWindow(m_hWnd)); return m_nCurSel; }
//---------------------------------------------------------------------------
inline int CXTFlatTabCtrl::GetItemCount() const
	{ ASSERT(IsWindow(m_hWnd)); return m_TabList.GetSize(); }
//---------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // #if !defined(__XTFLATTABCTRL_H__)
