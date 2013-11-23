// DemoUIDevStudio.h : main header file for the DEMOUIDEVSTUDIO application
//

#if !defined(AFX_DEMOUIDEVSTUDIO_H__1D0FB128_4A25_11D4_82DA_D868EA325637__INCLUDED_)
#define AFX_DEMOUIDEVSTUDIO_H__1D0FB128_4A25_11D4_82DA_D868EA325637__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CDemoUIDevStudioApp:
// See DemoUIDevStudio.cpp for the implementation of this class
//

class CDemoUIDevStudioApp : public CWinApp
{
public:
	CDemoUIDevStudioApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDemoUIDevStudioApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CDemoUIDevStudioApp)
	afx_msg void OnAppAbout();
	afx_msg void OnTipoftheday();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:

	void ShowTipAtStartup();
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEMOUIDEVSTUDIO_H__1D0FB128_4A25_11D4_82DA_D868EA325637__INCLUDED_)
