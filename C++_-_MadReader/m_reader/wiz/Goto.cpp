// Goto.cpp : implementation file
//

#include "stdafx.h"
#include "wiz.h"
#include "Goto.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGoto dialog


CGoto::CGoto(CWnd* pParent /*=NULL*/)
	: CDialog(CGoto::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGoto)
	m_to = 0;
	m_stat = _T("");
	//}}AFX_DATA_INIT
    
}


void CGoto::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
    
	//{{AFX_DATA_MAP(CGoto)
	DDX_Text(pDX, IDC_EDIT2, m_to);
    DDX_Radio(pDX,IDC_RADIO1,page);
    DDX_Radio(pDX,IDC_RADIO2,pers);
    DDX_Radio(pDX,IDC_RADIO3,ofs);
	DDX_Text(pDX, IDC_STATIC20, m_stat);
	//}}AFX_DATA_MAP
    
}


BEGIN_MESSAGE_MAP(CGoto, CDialog)
	//{{AFX_MSG_MAP(CGoto)
	ON_BN_CLICKED(IDC_BUTTON21, OnGoto)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, OnDeltaposSpin1)
	ON_BN_CLICKED(IDC_BUTTON23, OnCancel)
	ON_WM_HELPINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGoto message handlers

void CGoto::OnGoto() 
{
    UpdateData();

    choose = (page) ? 0:1;
    if (choose==0) choose = (pers) ? 0:2;
    if (choose==0) choose==3;
    
    
    switch ( choose)
    {
    case 1: //page
        mainwnd3()->Seek_toPage(m_to);
        break;
    case 2: //pers
        {
            ldiv_t p= ldiv(size,100 );				
            long ppos = p.quot*m_to;
            if ( ppos>size) ppos=size-mainwnd3()->page_kb+400;
            mainwnd3()->Seek_to(ppos);		                    
        }
        break;
    case 0:                 
        mainwnd3()->Seek_to(m_to);		        
        break;
    }    

    CString s1;
    parse_templ(s1,"Page %PAGE% (%PERS%%) OFS:%KB% bytes");
    this->SetWindowText(s1);
	
}

int CGoto::DoModal() 
{
    size =  mainwnd3()->f.GetLength();
    pos= mainwnd3()->get_dim();	
    choose=0;
    page=0;
    pers=1;    
    ofs=1;
    m_stat.Format("Size:%d kb ~%d pages (~%d b)",size/1024,size/mainwnd3()->page_kb,mainwnd3()->page_kb);  
	return CDialog::DoModal();
}

void CGoto::OnCancel() 
{
    mainwnd3()->Seek_to(pos);			
    EndDialog(0);    
}

void CGoto::OnDeltaposSpin1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;	
     pNMUpDown->iDelta*=-1;
    
	*pResult = 0;
}

BOOL CGoto::PreTranslateMessage(MSG* pMsg) 
{
    switch ( pMsg->message )
    {	
    case WM_KEYDOWN:		
        switch ( pMsg->wParam )
        {				
        case VK_ESCAPE:        
            mainwnd3()->Seek_to(pos);
            pMsg->wParam=0;
            this->EndDialog(0);
            return 1;
        case VK_RETURN:                 
            if ( GetFocus() == GetDlgItem(IDOK) ||  GetFocus() == GetDlgItem(IDCANCEL) )            
            { 
                pMsg->wParam=0;
                EndDialog(1); 
                return 1;  
            }
            break;
        }
        break;			
    } 	
	return CDialog::PreTranslateMessage(pMsg);
}

BOOL CGoto::OnHelpInfo(HELPINFO* pHelpInfo) 
{
    EndDialog(0);
    WinHelp(0,HELP_CONTENTS);		
	return 1; //CDialog::OnHelpInfo(pHelpInfo);
}
