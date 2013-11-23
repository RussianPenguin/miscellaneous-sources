#if !defined(AFX_TOOLBAREX_H__EA341333_E1ED_11D2_B892_0048540133F7__INCLUDED_)
#define AFX_TOOLBAREX_H__EA341333_E1ED_11D2_B892_0048540133F7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ToolBarEx.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CToolbarEx window

class CToolbarEx : public CToolBar
{
	DECLARE_DYNAMIC(CToolbarEx);

// Construction
public:
	CToolbarEx();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolbarEx)
	//}}AFX_VIRTUAL

// Implementation
public:
	UINT m_nIDResource;
	virtual BOOL LoadToolBar(UINT nIDResource);
	virtual ~CToolbarEx();

	// Generated message map functions
protected:
	//{{AFX_MSG(CToolbarEx)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TOOLBAREX_H__EA341333_E1ED_11D2_B892_0048540133F7__INCLUDED_)
