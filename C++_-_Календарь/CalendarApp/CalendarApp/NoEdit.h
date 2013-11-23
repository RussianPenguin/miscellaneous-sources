/////////////////////////////////////////////////////////////////////////////
//
// Disclaimer Notice
// ------------------
// The Author cannot guarantee this software is error free.
// The author also disclaims all responsibility for damages or 
// loss of profits caused by the failure of this software
//. Your usage of these modifications indicates your willingness to 
// accept complete responsibility.
//
//
// Developed by: Norm Almond for www.codeproject.com 
//
// Please use this software freely, if you fix or make any modifications to
// the software you can let me know so I can improve future versions.
//
// Version 1.00 - First Release 24 Nov 2000
/////////////////////////////////////////////////////////////////////////////
// NoEdit.h : header file
//
/////////////////////////////////////////////////////////////////////////////

// CNoEdit window
#ifndef __NOEDIT__
#define __NOEDIT__

class CNoEdit : public CEdit
{
// Construction
public:
	CNoEdit();

// Attributes
protected:
	CFont m_Font;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNoEdit)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CNoEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CNoEdit)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

#endif

/////////////////////////////////////////////////////////////////////////////
