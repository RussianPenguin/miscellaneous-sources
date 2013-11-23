// AdvProp.cpp : implementation file
//

#include "stdafx.h"
#include "wiz.h"
#include "AdvProp.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAdvProp property page

IMPLEMENT_DYNCREATE(CAdvProp, CPropertyPage)

CAdvProp::CAdvProp() : CPropertyPage(CAdvProp::IDD)
{
	//{{AFX_DATA_INIT(CAdvProp)
	m_fnt_item = 0;
	m_templ_item = 0;
	m_templ = _T("");
	//}}AFX_DATA_INIT
	p1=3;
	p2=4;
}

CAdvProp::~CAdvProp()
{
}

void CAdvProp::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAdvProp)
	DDX_Control(pDX, IDC_BUTTON14, m_clr);
	DDX_Control(pDX, IDC_BUTTON13, m_bk_clr);
	DDX_Control(pDX, IDC_EDIT7, m_templ1);	
	DDX_Control(pDX, IDC_STATIC1, m_sample);
	DDX_CBIndex(pDX, IDC_COMBO4, m_fnt_item);
	DDX_CBIndex(pDX, IDC_COMBO3, m_templ_item);
	DDX_Text(pDX, IDC_EDIT7, m_templ);
	DDV_MaxChars(pDX, m_templ, 490);
	//}}AFX_DATA_MAP
	/*if ( pDX->m_bSaveAndValidate )
	{
		m_fnt_item+p1+=3;
		m_templ_item+p2+=3;
	}*/
}


BEGIN_MESSAGE_MAP(CAdvProp, CPropertyPage)
	//{{AFX_MSG_MAP(CAdvProp)
	ON_WM_CTLCOLOR()
	ON_CBN_SELCHANGE(IDC_COMBO4, OnSelFont)
	ON_CBN_SELCHANGE(IDC_COMBO3, OnSelTempl)
	ON_BN_CLICKED(IDC_BUTTON2, OnChoosef)
	ON_BN_CLICKED(IDC_BUTTON13, OnButton13)
	ON_BN_CLICKED(IDC_BUTTON14, Onclr)
	ON_BN_CLICKED(IDC_BUTTON1, OnMacro)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAdvProp message handlers



void CAdvProp::OnOK() 
{	
	strcpy(maindlg3()->Info.fonts[m_templ_item+p2].templ,m_templ);		
	//mainwnd3()->change_font();
	//mainwnd3()->change_color();

	CPropertyPage::OnOK();
}

BOOL CAdvProp::OnSetActive() 
{	
	UpdateData();
	m_templ=maindlg3()->Info.fonts[m_templ_item+p2].templ;	
	if ( fnt1.CreateFontIndirect(&maindlg3()->Info.fonts[m_fnt_item+p1].fnt) )	
		m_sample.SetFont(&fnt1,true);			
	bk_clr=maindlg3()->Info.fonts[m_fnt_item+p1].clr_bk;
	tx_clr = maindlg3()->Info.fonts[m_fnt_item+p1].clr;
	GetDlgItem(IDC_STATIC1)->SetWindowText("Font sample \ מבנאחוצ ״נטפעא");
	m_bk_clr.SetColor(maindlg3()->Info.fonts[m_fnt_item+p1].clr_bk);
	m_clr.SetColor(maindlg3()->Info.fonts[m_fnt_item+p1].clr);
	UpdateData(false);
	
	return CPropertyPage::OnSetActive();
}

HBRUSH CAdvProp::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);

	switch ( nCtlColor)
	{  
	case CTLCOLOR_STATIC   :		
		if (pWnd->m_hWnd == m_sample.m_hWnd )						
		{
			pDC->SetTextColor(maindlg3()->Info.fonts[m_fnt_item+p1].clr);							
			pDC->SetBkColor(maindlg3()->Info.fonts[m_fnt_item+p1].clr_bk);										
		} 		
		break;
	}			
	return hbr;
}

void CAdvProp::OnSelFont() 
{	
	//////////		
	UpdateData(true);		
	fnt1.DeleteObject();
	if ( fnt1.CreateFontIndirect(&maindlg3()->Info.fonts[m_fnt_item+p1].fnt) )	
		m_sample.SetFont(&fnt1,true);			
	m_sample.SetFont(&fnt1,true);				
	m_bk_clr.SetColor(maindlg3()->Info.fonts[m_fnt_item+p1].clr_bk);
	m_clr.SetColor(maindlg3()->Info.fonts[m_fnt_item+p1].clr);
}

void CAdvProp::OnSelTempl() 
{
	int s =m_templ_item+p2;	
	UpdateData(true);		
	strcpy(maindlg3()->Info.fonts[s].templ,m_templ);
	m_templ= maindlg3()->Info.fonts[m_templ_item+p2].templ;	
	UpdateData(false);		
}

void CAdvProp::OnChoosef() 
{
	choose_font( &maindlg3()->Info.fonts[m_fnt_item+p1].fnt, maindlg3()->Info.fonts[m_fnt_item+p1].clr , this->m_hWnd);
	fnt1.DeleteObject();
	if ( fnt1.CreateFontIndirect(&maindlg3()->Info.fonts[m_fnt_item+p1].fnt) )	
		m_sample.SetFont(&fnt1,true);		
	
	//tx_clr=maindlg3()->Info.fonts[m_fnt_item+p1].clr;		
	//GetDlgItem(IDC_STATIC4)->Invalidate(true);		

	
}

void CAdvProp::OnMacro() 
 {
 	int x1;
 	m_templ1.GetSel(templ_pos,x1);
 	POINT pnt;
 	::GetCursorPos(&pnt);
 	templm.LoadMenu(IDR_TEMPL);
 	
 	/*
 0	Info text
 1	Memo separator
 	Bookmark (1 line)
 	Save file name
 	Window text
 	*/
 	switch ( m_templ_item) 
 	{
 	case 0:
 	templm.GetSubMenu(0)->EnableMenuItem(7,MF_BYPOSITION  |  MF_GRAYED );
 	templm.GetSubMenu(0)->EnableMenuItem(8,MF_BYPOSITION  |  MF_GRAYED );
    templm.GetSubMenu(0)->EnableMenuItem(9,MF_BYPOSITION  |  MF_GRAYED );
 	break;
 
 	case 1:
 	templm.GetSubMenu(0)->EnableMenuItem(7,MF_BYPOSITION  |  MF_GRAYED );
 	templm.GetSubMenu(0)->EnableMenuItem(8,MF_BYPOSITION  |  MF_GRAYED );
 	templm.GetSubMenu(0)->EnableMenuItem(10,MF_BYPOSITION  | MF_GRAYED );
 	templm.GetSubMenu(0)->EnableMenuItem(11,MF_BYPOSITION  | MF_GRAYED );
 	break;
 
 	case 2:
 	templm.GetSubMenu(0)->EnableMenuItem(10,MF_BYPOSITION  | MF_GRAYED );
 	templm.GetSubMenu(0)->EnableMenuItem(11,MF_BYPOSITION  | MF_GRAYED );
 	templm.GetSubMenu(0)->EnableMenuItem(12,MF_BYPOSITION  | MF_GRAYED );
 	break;
 
 	case 3:	
 	case 4:
 		templm.GetSubMenu(0)->EnableMenuItem(7,MF_BYPOSITION  |  MF_GRAYED );
 	templm.GetSubMenu(0)->EnableMenuItem(8,MF_BYPOSITION  |   MF_GRAYED );
 	templm.GetSubMenu(0)->EnableMenuItem(10,MF_BYPOSITION  |  MF_GRAYED );
 	templm.GetSubMenu(0)->EnableMenuItem(11,MF_BYPOSITION  |  MF_GRAYED );
 	templm.GetSubMenu(0)->EnableMenuItem(12,MF_BYPOSITION  |  MF_GRAYED );
 	}	
    CRect r; 	
    this->GetDlgItem(IDC_BUTTON1)->GetWindowRect(r); 	
    templm.GetSubMenu(0)->TrackPopupMenu(0, r.left, r.bottom, this);			

 //	templm.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN |TPM_RIGHTBUTTON, pnt.x, pnt.y, this);			
 }

BOOL CAdvProp::OnCommand(WPARAM wParam, LPARAM lParam) 
{
if ( wParam >= ID_1_PAGE && wParam <=ID_1_AVERAGESPEED3)
	{		
		CString s2;
		templm.GetMenuString(wParam,s2,MF_BYCOMMAND);				
        s2.Insert(0,"%");
        s2+="% ";
		UpdateData();
		m_templ.Insert(templ_pos,(LPCTSTR)s2);
		UpdateData(false);
		m_templ1.SetSel(templ_pos+s2.GetLength(),templ_pos+s2.GetLength());
	}				
	return CPropertyPage::OnCommand(wParam, lParam);
}

BOOL CAdvProp::DestroyWindow() 
{
	DeleteObject(brsh);	
	DeleteObject(brsh2);	
	return CPropertyPage::DestroyWindow();
}

void CAdvProp::OnButton13() 
{
	if ( choose_color( maindlg3()->Info.fonts[m_fnt_item+p1].clr_bk , this->m_hWnd) )
		m_bk_clr.SetColor(maindlg3()->Info.fonts[m_fnt_item+p1].clr_bk);	
    m_sample.Invalidate();
}

void CAdvProp::Onclr() 
{
	if ( choose_color( maindlg3()->Info.fonts[m_fnt_item+p1].clr , this->m_hWnd) )
		m_clr.SetColor(maindlg3()->Info.fonts[m_fnt_item+p1].clr);	
    m_sample.Invalidate();
}

