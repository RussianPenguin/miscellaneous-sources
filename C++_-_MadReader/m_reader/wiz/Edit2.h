#if !defined(AFX_EDIT2_H__58314E41_66BF_11D4_AAC6_F7D5B1A1F15E__INCLUDED_)
#define AFX_EDIT2_H__58314E41_66BF_11D4_AAC6_F7D5B1A1F15E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Edit2.h : header file
//


/////////////////////////////////////////////////////////////////////////////
// CEdit2 window

class CEdit2 : public CEdit
{
// Construction
public:
	CEdit2();
	CWnd *wnd;

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEdit2)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	char s[300];
	void ShowMenu();
	virtual ~CEdit2();

	// Generated message map functions
protected:
	//{{AFX_MSG(CEdit2)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDIT2_H__58314E41_66BF_11D4_AAC6_F7D5B1A1F15E__INCLUDED_)
