// BookmText.cpp : implementation file
//

#include "stdafx.h"
#include "wiz.h"
#include "BookmText.h"
//#include "resource.h"		// main symbols

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBookmTextDlg dialog


CBookmTextDlg::CBookmTextDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBookmTextDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBookmTextDlg)`
	m_text = _T("");
	//}}AFX_DATA_INIT
}


void CBookmTextDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBookmTextDlg)
	DDX_Text(pDX, IDC_EDIT2, m_text);
	DDV_MaxChars(pDX, m_text, 100);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBookmTextDlg, CDialog)
	//{{AFX_MSG_MAP(CBookmTextDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBookmTextDlg message handlers

void CBookmTextDlg::OnOK() 
{
  //UpdateDa	
	CDialog::OnOK();
}
