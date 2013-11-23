// RotaryCtrl.h : main header file for the ROTARYCTRL application
//

#if !defined(AFX_ROTARYCTRL_H__EB2B06E8_8ED9_11D4_B26C_0090275090B3__INCLUDED_)
#define AFX_ROTARYCTRL_H__EB2B06E8_8ED9_11D4_B26C_0090275090B3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CRotaryCtrlApp:
// See RotaryCtrl.cpp for the implementation of this class
//

class CRotaryCtrlApp : public CWinApp
{
public:
	CRotaryCtrlApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRotaryCtrlApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CRotaryCtrlApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ROTARYCTRL_H__EB2B06E8_8ED9_11D4_B26C_0090275090B3__INCLUDED_)
