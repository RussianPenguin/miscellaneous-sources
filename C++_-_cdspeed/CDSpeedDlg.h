// CDSpeedDlg.h : header file
//

#if !defined(AFX_CDSPEEDDLG_H__E60246E8_5946_11D6_976F_C429DA41F719__INCLUDED_)
#define AFX_CDSPEEDDLG_H__E60246E8_5946_11D6_976F_C429DA41F719__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCDSpeedDlg dialog

class CCDSpeedDlg : public CDialog
{
// Construction
public:
	CCDSpeedDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCDSpeedDlg)
	enum { IDD = IDD_CDSPEED_DIALOG };
	CSpinButtonCtrl	m_Spinner;
	CComboBox	m_CD;
	//}}AFX_DATA

	virtual CString GetDriveName(BYTE Host, BYTE Target);
	virtual int GetDriveMAXSpeed(BYTE Host, BYTE Target);
	virtual void SetDriveSpeed(BYTE Host, BYTE Target, int Speed);
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCDSpeedDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCDSpeedDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSetSpeed();
	afx_msg void OnAbout();
	afx_msg void OnExit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CDSPEEDDLG_H__E60246E8_5946_11D6_976F_C429DA41F719__INCLUDED_)
