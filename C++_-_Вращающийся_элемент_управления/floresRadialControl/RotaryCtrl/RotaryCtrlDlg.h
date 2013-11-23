// RotaryCtrlDlg.h : header file
//

#if !defined(AFX_ROTARYCTRLDLG_H__EB2B06EA_8ED9_11D4_B26C_0090275090B3__INCLUDED_)
#define AFX_ROTARYCTRLDLG_H__EB2B06EA_8ED9_11D4_B26C_0090275090B3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CRadialCtrl.h"
/////////////////////////////////////////////////////////////////////////////
// CRotaryCtrlDlg dialog

class CRotaryCtrlDlg : public CDialog
{
// Construction
public:
	CRotaryCtrlDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CRotaryCtrlDlg)
	enum { IDD = IDD_ROTARYCTRL_DIALOG };
	CRadialCtrl	m_ctrlRadial2;
	CRadialCtrl	m_ctrlRadial;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRotaryCtrlDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CRotaryCtrlDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ROTARYCTRLDLG_H__EB2B06EA_8ED9_11D4_B26C_0090275090B3__INCLUDED_)
