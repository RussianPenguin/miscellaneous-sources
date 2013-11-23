// Print.cpp : implementation file
//

#include "stdafx.h"
#include "wiz.h"
#include "Print.h"
//#include "FontCombo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPrint property page

IMPLEMENT_DYNCREATE(CPrint, CPropertyPage)

CPrint::CPrint() : CPropertyPage(CPrint::IDD)
{
	//{{AFX_DATA_INIT(CPrint)
	m_choose = 1;
	m_templ = "";
	
	//}}AFX_DATA_INIT
}

CPrint::~CPrint()
{
}

void CPrint::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPrint)
	DDX_Control(pDX, IDC_EDIT7, m_templ1);
	DDX_Control(pDX, IDC_STATIC1, m_sample);
	DDX_Text(pDX, IDC_EDIT7, m_templ);
	DDX_CBIndex(pDX, IDC_COMBO3, m_choose);
	//}}AFX_DATA_MAP
	
	this->GetDlgItem(IDC_EDIT7)->ShowWindow( (m_choose==1) ? false:true);
	this->GetDlgItem(IDC_BUTTON1)->ShowWindow( (m_choose==1) ? false:true);	
	this->GetDlgItem(IDC_STATIC2)->ShowWindow( (m_choose==1) ? false:true);		
	CString s1;
	s1.Format("(%s) Font sample / Образец",maindlg3()->Info.fonts[m_choose].fnt.lfFaceName);	
	m_sample.SetWindowText(s1);
	
}


BEGIN_MESSAGE_MAP(CPrint, CPropertyPage)
	//{{AFX_MSG_MAP(CPrint)
	ON_CBN_SELCHANGE(IDC_COMBO3, OnChoosef)
	ON_BN_CLICKED(IDC_BUTTON2, OnChoosefnt)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON1, OnMacroMenu)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPrint message handlers

BOOL CPrint::OnSetActive() 
{		

	fnt1.DeleteObject();
	if ( fnt1.CreateFontIndirect(&maindlg3()->Info.fonts[m_choose].fnt) )	
		m_sample.SetFont(&fnt1,true);			
	m_templ=maindlg3()->Info.fonts[m_choose].templ;
	

	return CPropertyPage::OnSetActive();
}

void CPrint::OnChoosef() 
{
	//UpdateData(false);	
	int s =m_choose;	
	UpdateData(true);		
	strcpy(maindlg3()->Info.fonts[s].templ,m_templ);
	
	fnt1.DeleteObject();
	if ( fnt1.CreateFontIndirect(&maindlg3()->Info.fonts[m_choose].fnt) )	
		m_sample.SetFont(&fnt1,true);			
	m_templ=maindlg3()->Info.fonts[m_choose].templ;
	UpdateData(false);	
}

void CPrint::OnChoosefnt() 
{
	choose_font( &maindlg3()->Info.fonts[m_choose].fnt, maindlg3()->Info.fonts[m_choose].clr , this->m_hWnd);
	fnt1.DeleteObject();
	if ( fnt1.CreateFontIndirect(&maindlg3()->Info.fonts[m_choose].fnt) )	
		m_sample.SetFont(&fnt1,true);		
	m_sample.SetWindowText(maindlg3()->Info.fonts[m_choose].fnt.lfFaceName);	
}


HBRUSH CPrint::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);	
	switch ( nCtlColor)
	{  
	case CTLCOLOR_STATIC   :		
		if (pWnd->m_hWnd == m_sample.m_hWnd )				
			pDC->SetTextColor(maindlg3()->Info.fonts[m_choose].clr);					
		break;
	}	
	return hbr;
}


void CPrint::OnMacroMenu() 
{
    UpdateData();
	int x1;
	
	templm.LoadMenu(IDR_TEMPL);
    for ( x1= 1; x1 <= 9; x1++)
	templm.GetSubMenu(0)->DeleteMenu(8,MF_BYPOSITION);
	

    m_templ1.GetSel(templ_pos,x1);
	POINT pnt;
	::GetCursorPos(&pnt);

	templm.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN |TPM_RIGHTBUTTON, pnt.x, pnt.y, this);		
	
}

BOOL CPrint::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	if ( wParam >= ID_1_PAGE && wParam <=ID_1_PAGE+15)
	{		
		CString s2;
		templm.GetMenuString(wParam,s2,MF_BYCOMMAND);				
        s2.Insert(0,"%");
        s2+="% ";
		m_templ.Insert(templ_pos,(LPCTSTR)s2);
		UpdateData(false);
	}			
	return CPropertyPage::OnCommand(wParam, lParam);
}

BOOL CPrint::OnKillActive() 
{
     strcpy(maindlg3()->Info.fonts[m_choose].templ,m_templ);	
	return CPropertyPage::OnKillActive();
}
