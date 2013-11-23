#if !defined(AFX_ADVPROP_H__6C5151A1_7109_11D4_AAC6_D57E7B86684D__INCLUDED_)
#define AFX_ADVPROP_H__6C5151A1_7109_11D4_AAC6_D57E7B86684D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AdvProp.h : header file
//
#include "CButt.h"

/////////////////////////////////////////////////////////////////////////////
// CAdvProp dialog

class CAdvProp : public CPropertyPage
{
	DECLARE_DYNCREATE(CAdvProp)

// Construction
public:
	bool hit;
	HBRUSH brsh,brsh2;
	void CAdvProp::OnMacro();

	COLORREF tx_clr, bk_clr;
	int templ_pos, p1,p2;
	CMenu templm;
	CFont fnt1;		
	CAdvProp();
	~CAdvProp();

// Dialog Data
	//{{AFX_DATA(CAdvProp)
	enum { IDD = IDD_DIALOGBAR6 };
	CCoolButton	m_clr;
	CCoolButton	m_bk_clr;
	CEdit	m_templ1;
	CStatic	m_stat17;
	CStatic	m_sample;
	int		m_fnt_item;
	int		m_templ_item;
	CString	m_templ;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CAdvProp)
	public:
	virtual void OnOK();
	virtual BOOL OnSetActive();
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CAdvProp)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSelFont();
	afx_msg void OnSelTempl();
	afx_msg void OnChoosef();
	afx_msg void OnButton13();
	afx_msg void Onclr();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADVPROP_H__6C5151A1_7109_11D4_AAC6_D57E7B86684D__INCLUDED_)
