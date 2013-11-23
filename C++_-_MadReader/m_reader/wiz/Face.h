#if !defined(AFX_FACE_H__31C25F62_65F2_11D4_AAC6_A2A6FC50B372__INCLUDED_)
#define AFX_FACE_H__31C25F62_65F2_11D4_AAC6_A2A6FC50B372__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Face.h : header file
//
#include "wiz.h"

/////////////////////////////////////////////////////////////////////////////
// CFace dialog

class CFace : public CPropertyPage
{
	DECLARE_DYNCREATE(CFace)

// Construction
public:
	CFace();	
	~CFace();
	

// Dialog Data
	//{{AFX_DATA(CFace)
	enum { IDD = IDD_DIALOG1 };
	CEdit	m_memo2;
	CString	m_memo;
	CString	m_size;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CFace)
	public:
	virtual void OnOK();
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CFace)
	afx_msg void OnSave();
	afx_msg void OnClear();
	afx_msg void OnChangeEdit8();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FACE_H__31C25F62_65F2_11D4_AAC6_A2A6FC50B372__INCLUDED_)
