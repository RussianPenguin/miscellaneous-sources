// dialogDlg.h : header file
//

#if !defined(AFX_DIALOGDLG_H__CD71A8CF_FCC9_11D4_BF96_000102FAA55C__INCLUDED_)
#define AFX_DIALOGDLG_H__CD71A8CF_FCC9_11D4_BF96_000102FAA55C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDialogDlg dialog

class CDialogDlg : public CDialog
{
// Construction
public:
	CDialogDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogDlg)
	enum { IDD = IDD_DIALOG_DIALOG };
	CString	m_Address;
	CString	m_Mask;
	CString	m_Interface;
	CString	m_Ms;
	CString	m_Mr;
	int		m_Port;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDialogDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnNew();
	afx_msg void OnDelete();
	afx_msg void OnPing();
	afx_msg void OnInfo();
	afx_msg void OnSend();
	afx_msg void OnServer();
	afx_msg void OnClient();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnHelp();
	afx_msg void OnChangeEdit4();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGDLG_H__CD71A8CF_FCC9_11D4_BF96_000102FAA55C__INCLUDED_)
