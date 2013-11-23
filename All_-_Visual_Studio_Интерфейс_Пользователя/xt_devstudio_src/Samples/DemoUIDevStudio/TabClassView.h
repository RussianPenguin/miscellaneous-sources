// TabClassView.h : interface of the CTabClassView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TABCLASSVIEW_H__1CA9DB27_2253_11D3_A634_00105A98E9A1__INCLUDED_)
#define AFX_TABCLASSVIEW_H__1CA9DB27_2253_11D3_A634_00105A98E9A1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTabClassView : public CTreeView
{
protected: // create from serialization only
	CTabClassView();
	DECLARE_DYNCREATE(CTabClassView)

// Attributes
public:
	CTabClassDoc* GetDocument();
	
	CTreeCtrl*	m_pTreeCtrl;
	CImageList	m_ImageList;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTabClassView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	void UpdateView();
	virtual ~CTabClassView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTabClassView)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg UINT OnNcHitTest(CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in TabClassView.cpp
inline CTabClassDoc* CTabClassView::GetDocument()
   { return (CTabClassDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABCLASSVIEW_H__1CA9DB27_2253_11D3_A634_00105A98E9A1__INCLUDED_)
