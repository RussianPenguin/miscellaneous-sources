#if !defined(AFX_EVALDLG_H__C2062B41_78CD_11D4_AAC6_8AE3F75F635C__INCLUDED_)
#define AFX_EVALDLG_H__C2062B41_78CD_11D4_AAC6_8AE3F75F635C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EvalDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEvalDlg dialog

class CEvalDlg : public CDialog
{
// Construction
public:
	int x1;
	CEvalDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEvalDlg)
	enum { IDD = IDD_REG };
	CString	m_str;
	CString	m_day;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEvalDlg)
	public:
	virtual int DoModal(int x);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEvalDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EVALDLG_H__C2062B41_78CD_11D4_AAC6_8AE3F75F635C__INCLUDED_)
