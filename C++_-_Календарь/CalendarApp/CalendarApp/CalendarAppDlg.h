// CalendarAppDlg.h : header file
//

#if !defined(AFX_CALENDARAPPDLG_H__841F058C_7E88_4BAE_82F8_F062B2B71B08__INCLUDED_)
#define AFX_CALENDARAPPDLG_H__841F058C_7E88_4BAE_82F8_F062B2B71B08__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCalendarAppDlg dialog

// #INCLUDE HERE#
#include "CalWnd.h"

class CCalendarAppDlg : public CDialog
{
// Construction
public:
	CCalendarAppDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCalendarAppDlg)
	enum { IDD = IDD_CALENDARAPP_DIALOG };
	CEdit	m_edtText;
	CDateTimeCtrl	m_ctrlDatePicker;
	CListBox	m_lbxLog;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCalendarAppDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

	// #DEFINE HERE#
	CCalWnd	m_ctrlCalendar; 


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCalendarAppDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnAdd();
	afx_msg void OnRemove();
	afx_msg void OnClearAll();
	afx_msg void OnSpinners();
	//}}AFX_MSG
	afx_msg LRESULT OnDateNotify(WPARAM wParam, LPARAM nId);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CALENDARAPPDLG_H__841F058C_7E88_4BAE_82F8_F062B2B71B08__INCLUDED_)
