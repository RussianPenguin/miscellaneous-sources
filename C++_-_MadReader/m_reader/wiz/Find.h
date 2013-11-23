#if !defined(AFX_FIND_H__D49EC121_6885_11D4_AAC6_E4C2EA9D225E__INCLUDED_)
#define AFX_FIND_H__D49EC121_6885_11D4_AAC6_E4C2EA9D225E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Find.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFind dialog

class CFind : public CPropertyPage
{
	DECLARE_DYNCREATE(CFind)

// Construction
public:
	CString curr_fnd;
	bool stop;
	//typedef void (
	//typedef 
	//void (CFind::*pFunc)(int);

    void save_sel(CDWordArray &arr);
	void delete_sel(CDWordArray &arr);
	void bookm_sel(CDWordArray &arr);
	void memo_sel(CDWordArray &arr);
	int cross_items(short p);
	int fnds;
	CMenu popup;
	CString s1;
	int down;
	long begin_pos;
	long curr_pos;
	long curr_page;
	bool page_point;
	int display_pos;
	CFind();
	~CFind();

// Dialog Data
	//{{AFX_DATA(CFind)
	enum { IDD = IDD_DIALOGBAR3 };
	CButton	m_findall;
	CListCtrl	m_list;
	CButton	m_bookm;
	CButton	m_stop;
	CButton	m_find;
	CString	m_text;
	CString	m_statist;
	BOOL	m_case;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CFind)
	public:
	virtual BOOL OnSetActive();
	virtual void OnCancel();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CFind)
	afx_msg void OnFind();
	afx_msg void OnChangeEdit1();
	afx_msg void OnFindAll();	
	afx_msg void OnUPRatio();
	afx_msg void OnDNratio();
	afx_msg void OnListMenu(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkList2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void Onstop();
	afx_msg void OnBookm();
	
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FIND_H__D49EC121_6885_11D4_AAC6_E4C2EA9D225E__INCLUDED_)
