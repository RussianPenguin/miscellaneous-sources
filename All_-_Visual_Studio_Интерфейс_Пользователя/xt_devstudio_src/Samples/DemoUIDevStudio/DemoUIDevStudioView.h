// DemoUIDevStudioView.h : interface of the CDemoUIDevStudioView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEMOUIDEVSTUDIOVIEW_H__1D0FB132_4A25_11D4_82DA_D868EA325637__INCLUDED_)
#define AFX_DEMOUIDEVSTUDIOVIEW_H__1D0FB132_4A25_11D4_82DA_D868EA325637__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// class forwards
class CDemoUIDevStudioDoc;

class CDemoUIDevStudioView : public CView
{
protected: // create from serialization only
	CDemoUIDevStudioView();
	DECLARE_DYNCREATE(CDemoUIDevStudioView)

// Attributes
public:
	CDemoUIDevStudioDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDemoUIDevStudioView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDemoUIDevStudioView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDemoUIDevStudioView)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in DemoUIDevStudioView.cpp
inline CDemoUIDevStudioDoc* CDemoUIDevStudioView::GetDocument()
   { return (CDemoUIDevStudioDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEMOUIDEVSTUDIOVIEW_H__1D0FB132_4A25_11D4_82DA_D868EA325637__INCLUDED_)
