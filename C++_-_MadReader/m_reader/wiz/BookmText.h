#if !defined(AFX_BOOKMTEXT_H__59952904_5571_11D4_AAC5_AC11F0673A5A__INCLUDED_)
#define AFX_BOOKMTEXT_H__59952904_5571_11D4_AAC5_AC11F0673A5A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BookmText.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBookmText dialog

class CBookmTextDlg : public CDialog
{
// Construction
public:
	CBookmTextDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBookmTextDlg)
	enum { IDD = IDD_DIALOGBAR1 };
	CString	m_text;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBookmTextDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBookmText)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BOOKMTEXT_H__59952904_5571_11D4_AAC5_AC11F0673A5A__INCLUDED_)
