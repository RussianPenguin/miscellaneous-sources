// EvalDlg.cpp : implementation file
//

#include "stdafx.h"
#include "wiz.h"
#include "EvalDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEvalDlg dialog


CEvalDlg::CEvalDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEvalDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEvalDlg)
	m_str = _T("");
	m_day = _T("");
	//}}AFX_DATA_INIT
}


void CEvalDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEvalDlg)
	DDX_Text(pDX, IDC_STATIC1, m_str);
	DDX_Text(pDX, IDC_STATIC2, m_day);
	//}}AFX_DATA_MAP
    GetDlgItem(IDOK)->EnableWindow(x1);
}


BEGIN_MESSAGE_MAP(CEvalDlg, CDialog)
	//{{AFX_MSG_MAP(CEvalDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEvalDlg message handlers

int CEvalDlg::DoModal(int x) 
{
    char str[1000];    
    LoadString(AfxGetApp()->m_hInstance,IDS_STRING35,str,1000);    
    m_str=_T(decode_b64(str));        
    x1=x;
    m_day.Format("%d days left",x);    

    //if (x1+10==10);
    //maindlg3()->save_recent();
    
 	return CDialog::DoModal();
}
