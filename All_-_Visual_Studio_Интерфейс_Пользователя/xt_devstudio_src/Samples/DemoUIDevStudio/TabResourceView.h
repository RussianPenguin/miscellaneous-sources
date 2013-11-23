// TabResourceView.h : interface of the CTabResourceView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TABRESOURCEVIEW_H__1CA9DB53_2253_11D3_A634_00105A98E9A1__INCLUDED_)
#define AFX_TABRESOURCEVIEW_H__1CA9DB53_2253_11D3_A634_00105A98E9A1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CTabResourceView : public CTreeView
{
protected: // create from serialization only
	CTabResourceView();
	DECLARE_DYNCREATE(CTabResourceView)

// Attributes
public:
	CTabResourceDoc* GetDocument();
	
	CTreeCtrl*	m_pTreeCtrl;
	CImageList	m_ImageList;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTabResourceView)
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
	virtual ~CTabResourceView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTabResourceView)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg UINT OnNcHitTest(CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in TabResourceView.cpp
inline CTabResourceDoc* CTabResourceView::GetDocument()
   { return (CTabResourceDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABRESOURCEVIEW_H__1CA9DB53_2253_11D3_A634_00105A98E9A1__INCLUDED_)
