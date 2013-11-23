#if !defined(AFX_ABOUT_H__8DF6F4A1_6F91_11D4_AAC6_BFA99F50185F__INCLUDED_)
#define AFX_ABOUT_H__8DF6F4A1_6F91_11D4_AAC6_BFA99F50185F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// About.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAbout dialog

class CAbout : public CPropertyPage
{
	DECLARE_DYNCREATE(CAbout)

// Construction
public:
	HBITMAP b;
	void showf(bool sw);
	bool reg;
    char str[1000];
    int timer;
    int press;
    char name[300];
    char key[300];
	CAbout();
	~CAbout();

// Dialog Data
	//{{AFX_DATA(CAbout)
	enum { IDD = IDD_DIALOGBAR5 };
	CStatic	m_bitm;
	CString	m_about;
	CString	m_owner;
	CString	m_key;
	CString	m_regto;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CAbout)
	public:
	virtual BOOL OnSetActive();
	virtual void OnOK();
	virtual void OnCancel();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CAbout)
	afx_msg void OnMenub();
	afx_msg void OnButton1();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ABOUT_H__8DF6F4A1_6F91_11D4_AAC6_BFA99F50185F__INCLUDED_)
