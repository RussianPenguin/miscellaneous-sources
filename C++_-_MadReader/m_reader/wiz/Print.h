#if !defined(AFX_PRINT_H__31C25F64_65F2_11D4_AAC6_A2A6FC50B372__INCLUDED_)
#define AFX_PRINT_H__31C25F64_65F2_11D4_AAC6_A2A6FC50B372__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Print.h : header file
//


/////////////////////////////////////////////////////////////////////////////
// CPrint dialog

class CPrint : public CPropertyPage
{
	DECLARE_DYNCREATE(CPrint)

// Construction
public:	
	int templ_pos;
	CMenu templm;
	CFont fnt1;		
	CPrint();
	~CPrint();

// Dialog Data
	//{{AFX_DATA(CPrint)
	enum { IDD = IDD_DIALOGBAR2 };
	CEdit	m_templ1;
	CStatic	m_sample;
	CString	m_templ;
	int		m_choose;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPrint)
	public:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPrint)
	afx_msg void OnChoosef();
	afx_msg void OnChoosefnt();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnMacroMenu();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRINT_H__31C25F64_65F2_11D4_AAC6_A2A6FC50B372__INCLUDED_)
