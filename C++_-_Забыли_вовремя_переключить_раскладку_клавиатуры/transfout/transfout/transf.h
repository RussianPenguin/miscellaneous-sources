// transf.h : main header file for the TRANSF application
//

#if !defined(AFX_TRANSF_H__F81C1445_A46C_11D4_AC0B_C27E7B624D1E__INCLUDED_)
#define AFX_TRANSF_H__F81C1445_A46C_11D4_AC0B_C27E7B624D1E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTransfApp:
// See transf.cpp for the implementation of this class
//

class CTransfApp : public CWinApp
{
public:
	CTransfApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTransfApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTransfApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRANSF_H__F81C1445_A46C_11D4_AC0B_C27E7B624D1E__INCLUDED_)
