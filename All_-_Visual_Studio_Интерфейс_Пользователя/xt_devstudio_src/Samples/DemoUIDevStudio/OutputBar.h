// OutputBar.h : header file
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_OUTPUTBAR_H__1D0FB134_4A25_11D4_82DA_D868EA325637__INCLUDED_)
#define AFX_OUTPUTBAR_H__1D0FB134_4A25_11D4_82DA_D868EA325637__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// COutputBar dock window class

class COutputBar : public CXTDockWindow
{
	DECLARE_DYNAMIC(COutputBar)

// Construction / destruction
public:
	COutputBar();
	virtual ~COutputBar();

// Attributes
protected:
	int				m_cy;
	CXTFlatTabCtrl	m_flatTabCtrl;
	CXTListBox		m_sheet1;
	CXTListBox		m_sheet2;
	CXTListBox		m_sheet3;
	CXTListBox		m_sheet4;
	CXTListBox		m_sheet5;
	CXTListBox		m_sheet6;

// Operations
public:
	void SelectTabView(int nTab);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COutputBar)
	protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(COutputBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnWindowPosChanged(WINDOWPOS FAR* lpwndpos);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OUTPUTBAR_H__1D0FB134_4A25_11D4_82DA_D868EA325637__INCLUDED_)

