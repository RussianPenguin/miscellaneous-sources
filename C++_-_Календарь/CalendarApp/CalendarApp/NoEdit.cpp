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

// NoEdit.cpp : implementation file
//

#include "stdafx.h"
#include "NoEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNoEdit

CNoEdit::CNoEdit()
{
}

CNoEdit::~CNoEdit()
{
	m_Font.Detach();
}


BEGIN_MESSAGE_MAP(CNoEdit, CEdit)
	//{{AFX_MSG_MAP(CNoEdit)
	ON_WM_CREATE()
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNoEdit message handlers

int CNoEdit::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CEdit::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_Font.Attach(GetStockObject(DEFAULT_GUI_FONT));
	SetFont(&m_Font,TRUE);
	
	return 0;
}

void CNoEdit::OnChar(UINT /*nChar*/, UINT /*nRepCnt*/, UINT /*nFlags*/) 
{
	// Override ---> to prevent editing
}


