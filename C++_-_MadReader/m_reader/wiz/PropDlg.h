#if !defined(AFX_PROPDLG_H__31C25F61_65F2_11D4_AAC6_A2A6FC50B372__INCLUDED_)
#define AFX_PROPDLG_H__31C25F61_65F2_11D4_AAC6_A2A6FC50B372__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PropDlg.h : header file
//
#include "wiz.h"
/////////////////////////////////////////////////////////////////////////////
// CPropDlg dialog

class CPropDlg : public CPropertyPage
{
	DECLARE_DYNCREATE(CPropDlg)

// Construction
public:
	CToolTipCtrl tl;	
	CPropDlg();
	~CPropDlg();

    int page1,kb1,wrd1;
    int run_mode;

// Dialog Data
	//{{AFX_DATA(CPropDlg)
	enum { IDD = IDD_DIALOGBAR };
	CSpinButtonCtrl	m_spin3;
	CSpinButtonCtrl	m_spin2;
	    CSpinButtonCtrl m_spin;
        CSpinButtonCtrl m_spiin;
        UINT    m_str;
        BOOL    m_bookm;
        BOOL    m_saver;
        BOOL    m_tips;
        BOOL    m_run;
        UINT    m_runsec;
        BOOL    m_showbm;
        BOOL    m_tip_of_day;
	BOOL	m_bigicon;
	BOOL	m_openSUp;
	BOOL	m_jmp;
	BOOL	m_ampm;
	int		m_infopos;
	UINT	m_run_kb;
	UINT	m_run_wrd;
	BOOL	m_pointer;
	int		m_pos_panel;
	BOOL	m_run1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPropDlg)
	public:
	virtual void OnOK();
	virtual BOOL OnSetActive();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPropDlg)
        afx_msg void OnDeltaposSpin2(NMHDR* pNMHDR, LRESULT* pResult);
        afx_msg void Onrun();
	afx_msg void OnCheck9();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPDLG_H__31C25F61_65F2_11D4_AAC6_A2A6FC50B372__INCLUDED_)
