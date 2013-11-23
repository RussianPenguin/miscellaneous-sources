// MySheet.cpp : implementation file
//

#include "stdafx.h"
#include "wiz.h"
#include "MySheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMySheet

IMPLEMENT_DYNAMIC(CMySheet, CPropertySheet)

CMySheet::CMySheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
}

CMySheet::CMySheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
}

CMySheet::~CMySheet()
{
}


BEGIN_MESSAGE_MAP(CMySheet, CPropertySheet)
	//{{AFX_MSG_MAP(CMySheet)
	ON_WM_HELPINFO()
    ON_BN_CLICKED(IDHELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMySheet message handlers

BOOL CMySheet::OnInitDialog() 
{
	BOOL bResult = CPropertySheet::OnInitDialog();	
	ModifyStyleEx(0,WS_EX_CONTEXTHELP  );	
	
	return bResult;
}


BOOL CMySheet::PreTranslateMessage(MSG* pMsg) 
{		
	switch ( pMsg->message )
	{	
	case WM_KEYDOWN:		
		switch ( pMsg->wParam )
		{				
            case VK_ESCAPE:            
                pMsg->wParam=0;
                this->EndDialog(0);
                return 1;
		}
		break;			
	} 
	return CPropertySheet::PreTranslateMessage(pMsg);
}

BOOL CMySheet::OnHelpInfo(HELPINFO* pHelpInfo) 
{   
 
    if (this->GetActiveIndex()==6) return true;    
    maindlg3()->context_h=true;
    WinHelp(pHelpInfo->iCtrlId, HELP_CONTEXTPOPUP	);	      
    return true;    
}
void CMySheet::OnHelp() 
{  
     WinHelp(0,HELP_CONTENTS);	
}

