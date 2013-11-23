// CalendarApp.h : main header file for the CALENDARAPP application
//

#if !defined(AFX_CALENDARAPP_H__6CE9BFC0_A0C0_41B8_A758_FA08DFEB94D5__INCLUDED_)
#define AFX_CALENDARAPP_H__6CE9BFC0_A0C0_41B8_A758_FA08DFEB94D5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCalendarAppApp:
// See CalendarApp.cpp for the implementation of this class
//

class CCalendarAppApp : public CWinApp
{
public:
	CCalendarAppApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCalendarAppApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCalendarAppApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CALENDARAPP_H__6CE9BFC0_A0C0_41B8_A758_FA08DFEB94D5__INCLUDED_)
