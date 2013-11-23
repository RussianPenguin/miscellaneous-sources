// transfDlg.h : header file
//

#if !defined(AFX_TRANSFDLG_H__F81C1447_A46C_11D4_AC0B_C27E7B624D1E__INCLUDED_)
#define AFX_TRANSFDLG_H__F81C1447_A46C_11D4_AC0B_C27E7B624D1E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define WM_NOTIFYICON (WM_USER+10)

/////////////////////////////////////////////////////////////////////////////
// CTransfDlg dialog

class CTransfDlg : public CDialog
{
// Construction
public:
	void Store();

//	afx_msg LRESULT OnNotifyIcon(WPARAM wParam, LPARAM lParam);
	CTransfDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTransfDlg)
	enum { IDD = IDD_TRANSF_DIALOG };
	int		m_mode;
	BOOL	m_Alt;
	BOOL	m_Ctrl;
	BOOL	m_Shift;
	int 	m_F;
	BOOL    IsHide;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTransfDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	LRESULT OnHotKey(WPARAM wParam, LPARAM lParam);


	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTransfDlg)
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnNotifyIcon(WPARAM wParam, LPARAM lParam);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDo();
	virtual void OnOK();
	afx_msg void OnButton1();
	afx_msg void OnDo2();
	afx_msg void OnDestroy();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRANSFDLG_H__F81C1447_A46C_11D4_AC0B_C27E7B624D1E__INCLUDED_)
