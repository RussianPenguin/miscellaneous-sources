// DSound.h : main header file for the DSOUND application
//

#if !defined(AFX_DSOUND_H__BC88D1E4_9A2F_11D3_8740_0080ADC92595__INCLUDED_)
#define AFX_DSOUND_H__BC88D1E4_9A2F_11D3_8740_0080ADC92595__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CDSoundApp:
// See DSound.cpp for the implementation of this class
//

class CDSoundApp : public CWinApp
{
public:
	CDSoundApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDSoundApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CDSoundApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DSOUND_H__BC88D1E4_9A2F_11D3_8740_0080ADC92595__INCLUDED_)
