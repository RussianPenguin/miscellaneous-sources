// XTEditGroup.h interface for the CXTEditGroup class.
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

#if !defined(__XTEDITLISTBOX_H__)
#define __XTEDITLISTBOX_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "XTButton.h"

/////////////////////////////////////////////////////////////////////////////
// CXTEditGroup window
/////////////////////////////////////////////////////////////////////////////
class _XT_EXT_CLASS CXTEditGroup : public CStatic
{
	DECLARE_DYNAMIC(CXTEditGroup)

public:

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Constructor - handles default initialization
	CXTEditGroup();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Destructor - handles clean up.
	virtual ~CXTEditGroup();

protected:

	CWnd*			m_pNotifyWnd;	// Points to a CWnd object where notification messages are sent.
	CXTButton		m_btnNew;		// New edit button
	CXTButton		m_btnDelete;	// Delete edit button
	CXTButton		m_btnUp;		// Move Up edit button
	CXTButton		m_btnDown;		// Move Down edit button
	CImageList		m_ImageList;	// Holds the images for the edit buttons.
	CToolTipCtrl	m_tooltip;		// Tooltip control for edit buttons.
	CSize			m_sizeBtn;		// Initial size of the edit buttons.

public:
	
	// -> Parameters:		pNotifyWnd	-	A CWnd object that represents the window that
	//										is to receive notification messages.
	// -> Return Value:		
	// -> Remarks:			This member function will initialize the edit group control.
	virtual void Initialize(CWnd* pNotifyWnd);

	//{{AFX_VIRTUAL(CXTEditGroup)
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CXTEditGroup)
	afx_msg void OnButtonNew();
	afx_msg void OnButtonDelete();
	afx_msg void OnButtonUp();
	afx_msg void OnButtonDown();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
// CXTListBox - Simple wrapper for flicker free drawing.
/////////////////////////////////////////////////////////////////////////////
class _XT_EXT_CLASS CXTListBox : public CListBox
{
	DECLARE_DYNAMIC(CXTListBox)

public:

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Constructor - handles default initialization
	CXTListBox();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Destructor - handles clean up.
	virtual ~CXTListBox();

	//{{AFX_VIRTUAL(CXTListBox)
	public:
	virtual BOOL Create( DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID );
	//}}AFX_VIRTUAL

protected:

	//{{AFX_MSG(CXTListBox)
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
// CXTEditListBox window
/////////////////////////////////////////////////////////////////////////////
class _XT_EXT_CLASS CXTEditListBox : public CXTListBox
{
	DECLARE_DYNAMIC(CXTEditListBox)

public:

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Constructor - handles default initialization
	CXTEditListBox();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Destructor - handles clean up.
	virtual ~CXTEditListBox();

	// -> Parameters:		lpszTitle -	NULL terminated string that represents the caption title.
	//						dwLStyle -	Style for list edit control, pass in LBS_XT_NOTOOLBAR
	//									if you do not wish the caption edit navigation control
	//									bar to be displayed.
	// -> Return Value:		
	// -> Remarks:			This member function will create the edit group control.
	void SetListEditStyle(LPCTSTR lpszTitle, DWORD dwLStyle=0x0);

	// -> Parameters:		nTitle	 -	Resource ID of the string to load for the caption title.
	//						dwLStyle -	Style for list edit control, pass in LBS_XT_NOTOOLBAR
	//									if you do not wish the caption edit navigation control
	//									bar to be displayed.
	// -> Return Value:		
	// -> Remarks:			This member function will create the edit group control.
	void SetListEditStyle(UINT nTitle, DWORD dwLStyle=0x0);

protected:

	int				m_nIndex;		// Current index when edit functions are performed.
	BOOL			m_bNewItem;		// TRUE if a new item is being entered into the list box.
	CString			m_strItemText;	// Current text of a selected item during edit.
	CXTEditGroup	m_editGroup;	// The edit group (toolbar) that appears above the list box.
	DWORD			m_dwLStyle;		// List edit styles.
	CString			m_strTitle;		// Caption area title.

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			This member function will create the edit group control.
	virtual BOOL CreateEditGroup();

	//{{AFX_VIRTUAL(CXTEditListBox)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CXTEditListBox)
	afx_msg void OnEndLabelEdit();
	afx_msg void OnEditCancel();
	afx_msg void OnNewItem();
	afx_msg void OnDeleteItem();
	afx_msg void OnMoveItemUp();
	afx_msg void OnMoveItemDown();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // #if !defined(__XTEDITLISTBOX_H__)
