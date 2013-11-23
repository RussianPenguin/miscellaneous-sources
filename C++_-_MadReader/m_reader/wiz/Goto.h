#if !defined(AFX_GOTO_H__A8677B63_71F4_11D4_AAC6_BD9E37696F5C__INCLUDED_)
#define AFX_GOTO_H__A8677B63_71F4_11D4_AAC6_BD9E37696F5C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Goto.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGoto dialog

class CGoto : public CDialog
{
// Construction
public:
	CGoto(CWnd* pParent = NULL);   // standard constructor
    int pers,page,ofs,choose; // 1-pg, 2-pc, 3-ofs
    long pos;
    long size;
    CString s1;
 

// Dialog Data
	//{{AFX_DATA(CGoto)
	enum { IDD = IDD_GOTO };
	UINT	m_to;
	CString	m_stat;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGoto)
	public:
	virtual int DoModal();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGoto)
	afx_msg void OnGoto();
	afx_msg void OnCancel();
	afx_msg void OnDeltaposSpin1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GOTO_H__A8677B63_71F4_11D4_AAC6_BD9E37696F5C__INCLUDED_)
