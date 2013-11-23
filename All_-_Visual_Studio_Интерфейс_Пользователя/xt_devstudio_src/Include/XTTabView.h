// XTTabView.h interface for the CXTTabView class.
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
// Used with permission Copyright © 1999 Mike Manzo
// mailto:mmanzo@ieee.org
//
//////////////////////////////////////////////////////////////////////

#if !defined(__XTTABVIEW_H__)
#define __XTTABVIEW_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CXTTabView is a CCtrlView derived class which can be used to
// create a view that contains a tab control
/////////////////////////////////////////////////////////////////////////////
class _XT_EXT_CLASS CXTTabView : public CCtrlView
{
	DECLARE_DYNCREATE(CXTTabView)

protected:

	// Default constructor
	//
	CXTTabView();

	// Virtual destructor
	//
	virtual ~CXTTabView();

protected:
	
	CView*			m_pActiveView;	// pointer to the active view
	int				m_nActiveTab;	// index of the active tab
	CTabCtrl*		m_pTabCtrl;		// pointer to the tab control
	CToolTipCtrl*	m_pToolTip;		// pointer to the tooltip control
	CFont			m_TabFont;		// font used by tab control

	// template list containing tab information
	CList <XT_TCB_ITEM*, XT_TCB_ITEM *>	m_views;

public:

	// this member function is called to add a view to the tab control
	//
	virtual BOOL AddView(
		// tab text
		LPCTSTR lpszLabel,
		// CView object associated with tab
		CRuntimeClass *pViewClass,
		// CDocument associated with view
		CDocument* pDoc = NULL,
		// create context for view
		CCreateContext *pContext = NULL);

	// this member function will modify the style for the
	// tab control associated with this control.
	//
	virtual BOOL ModifyTabStyle(DWORD dwRemove, DWORD dwAdd, UINT nFlags=0);

	// this member function will set a view active
	// based on a CView object
	//
	virtual void SetActiveView(CRuntimeClass *pViewClass);

	// this member function will set a view active
	// based on index
	//
	virtual void SetActiveView(int nNewTab);

	// this member function will remove a view based on its index
	//
	virtual void RemoveView(int nView);

	// this member function returns a pointer to a view
	// based on a CView object
	//
	virtual CView* GetView(CRuntimeClass *pViewClass);

	// this member function returns a pointer to a view
	// based on its index
	//
	virtual CView* GetView(int nView);

	// this member function returns a pointer to the
	// active view in the tab control
	//
	virtual CView* GetActiveView();

	// this member function initializes the image list
	// for the tab control
	//
	virtual CImageList* SetTabImageList(CImageList *pImageList);

	// this member function returns a pointer to the
	// tab control associated with this control
	//
	virtual CTabCtrl* GetTabCtrl();

	// this member function is called by the view, and
	// can be overloaded in derived classes to return the rect
	// for the child window associated with the control bar.
	//
	virtual void GetChildRect(
		// reference to a CRect object which contains the size of
		// the child window associated with the control bar.
		CRect &rect);

private:

	void CalcViewRect(CRect* pRect);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXTTabView)
	//}}AFX_VIRTUAL

	// Generated message map functions
protected:
	//{{AFX_MSG(CXTTabView)
	afx_msg void OnWindowPosChanged(WINDOWPOS FAR* lpwndpos);
	afx_msg void OnSelchange(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//---------------------------------------------------------------------------
inline CTabCtrl* CXTTabView::GetTabCtrl()
	{ return m_pTabCtrl; }
//---------------------------------------------------------------------------
inline CView* CXTTabView::GetActiveView()
	{ return m_pActiveView; }
//---------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // #if !defined(__XTTABVIEW_H__)
