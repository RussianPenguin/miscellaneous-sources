// DSoundView.h : interface of the CDSoundView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DSOUNDVIEW_H__BC88D1EC_9A2F_11D3_8740_0080ADC92595__INCLUDED_)
#define AFX_DSOUNDVIEW_H__BC88D1EC_9A2F_11D3_8740_0080ADC92595__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDSoundView : public CView
{
protected: // create from serialization only
	CDSoundView();
	DECLARE_DYNCREATE(CDSoundView)

// Attributes
public:
	CDSoundDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDSoundView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnScroll(UINT nScrollCode, UINT nPos, BOOL bDoScroll = TRUE);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDSoundView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDSoundView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnCommandPlay(UINT nIndex);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	TEXTMETRIC m_text;
	bool dr; 
	CPoint m_p;
	bool create;
};

#ifndef _DEBUG  // debug version in DSoundView.cpp
inline CDSoundDoc* CDSoundView::GetDocument()
   { return (CDSoundDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DSOUNDVIEW_H__BC88D1EC_9A2F_11D3_8740_0080ADC92595__INCLUDED_)
