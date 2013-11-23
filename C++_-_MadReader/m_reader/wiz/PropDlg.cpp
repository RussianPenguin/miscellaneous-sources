// PropDlg.cpp : implementation file
//

#include "stdafx.h"
//#include "wiz.h"
#include "PropDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropDlg property page

IMPLEMENT_DYNCREATE(CPropDlg, CPropertyPage)

CPropDlg::CPropDlg() : CPropertyPage(CPropDlg::IDD)
{
	 
	//{{AFX_DATA_INIT(CPropDlg)
	m_str=    maindlg3()->Info.lines;
	m_bookm=  maindlg3()->Info.askbookm;
	m_saver = maindlg3()->Info.lock_saver;
	m_tips=   maindlg3()->Info.tips;
	m_run=    maindlg3()->Info.run;
	m_runsec= maindlg3()->Info.runsec;
	m_showbm= maindlg3()->Info.show_bm;
    m_tip_of_day= maindlg3()->Info.tip_day;
	m_bigicon = maindlg3()->Info.bigIcon;
	m_openSUp = maindlg3()->Info.openSUp;
	m_jmp     = maindlg3()->Info.jumpLast;
	m_ampm    = maindlg3()->Info.AMpm;
	m_infopos = maindlg3()->Info.info_pos;
	m_run_kb = maindlg3()->Info.run_kb;
	m_run_wrd = maindlg3()->Info.run_wrd;
	m_pointer = maindlg3()->Info.run_pointer;
	m_pos_panel = maindlg3()->Info.pos_panel;
	m_run1 = 0 ;// maindlg3()->Info.run1;
	//}}AFX_DATA_INIT
}

CPropDlg::~CPropDlg()
{
}

void CPropDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropDlg)
	DDX_Control(pDX, IDC_SPIN12, m_spin3);
	DDX_Control(pDX, IDC_SPIN11, m_spin2);
		 DDX_Control(pDX, IDC_SPIN2, m_spin);
        DDX_Control(pDX, IDC_SPIN3, m_spiin);
        DDX_Text(pDX, IDC_EDIT1, m_str);
        DDX_Check(pDX, IDC_CHECK1, m_bookm);
        DDX_Check(pDX, IDC_CHECK2, m_saver);
        DDX_Check(pDX, IDC_CHECK3, m_tips);
        DDX_Check(pDX, IDC_CHECK4, m_run);
        DDX_Text(pDX, IDC_EDIT3, m_runsec);
        DDX_Check(pDX, IDC_CHECK5, m_showbm);
	DDX_Check(pDX, IDC_CHECK7, m_bigicon);
	DDX_Check(pDX, IDC_CHECK9, m_openSUp);
	DDX_Check(pDX, IDC_CHECK10, m_jmp);
	DDX_Check(pDX, IDC_CHECK11, m_ampm);
	DDX_CBIndex(pDX, IDC_COMBO5, m_infopos);
	DDX_Text(pDX, IDC_EDIT23, m_run_kb);
	DDX_Text(pDX, IDC_EDIT24, m_run_wrd);
	DDX_Check(pDX, IDC_CHECK16, m_pointer);
	DDX_CBIndex(pDX, IDC_COMBO6, m_pos_panel);
    DDX_Radio(pDX,IDC_RADIO4,page1);
    DDX_Radio(pDX,IDC_RADIO5,kb1);
    DDX_Radio(pDX,IDC_RADIO6,wrd1);
	DDX_Check(pDX, IDC_CHECK18, m_run1);
	//}}AFX_DATA_MAP
        //if (!m_run) (GetDlgItem(IDC_EDIT3))->EnableWindow(false);
         //(GetDlgItem(IDC_EDIT3))->EnableWindow(true);

        SendDlgItemMessage(IDC_EDIT3,WM_ENABLE,m_run,0);
        SendDlgItemMessage(IDC_SPIN3,WM_ENABLE,m_run,0);
        SendDlgItemMessage(IDC_EDIT23,WM_ENABLE,m_run,0);
        SendDlgItemMessage(IDC_SPIN11,WM_ENABLE,m_run,0);
        SendDlgItemMessage(IDC_EDIT24,WM_ENABLE,m_run,0);
        SendDlgItemMessage(IDC_SPIN12,WM_ENABLE,m_run,0);
        m_spiin.EnableWindow(m_run);
        m_spin2.EnableWindow(m_run);
        m_spin3.EnableWindow(m_run);
        //SendDlgItemMessage(IDC_RADIO5,WM_ENABLE,m_run,0);
        //SendDlgItemMessage(IDC_RADIO6,WM_ENABLE,m_run,0);
        GetDlgItem(IDC_RADIO4)->EnableWindow(m_run);
        GetDlgItem(IDC_RADIO5)->EnableWindow(m_run);
        GetDlgItem(IDC_RADIO6)->EnableWindow(m_run);
        this->GetDlgItem(IDC_CHECK16)->EnableWindow( m_run );

		this->GetDlgItem(IDC_CHECK10)->EnableWindow( (!m_openSUp) ? false:true);
        this->GetDlgItem(IDC_CHECK15)->EnableWindow( (!m_openSUp) ? false:true);

}


BEGIN_MESSAGE_MAP(CPropDlg, CPropertyPage)
	//{{AFX_MSG_MAP(CPropDlg)
		
        ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN3, OnDeltaposSpin2)
        ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN11, OnDeltaposSpin2)
        ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN12, OnDeltaposSpin2)
        ON_BN_CLICKED(IDC_CHECK4, Onrun)
	    ON_BN_CLICKED(IDC_CHECK9, OnCheck9)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropDlg message handlers



void CPropDlg::OnDeltaposSpin2(NMHDR* pNMHDR, LRESULT* pResult)
{
    NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;        
    
    pNMUpDown->iDelta*=-1; 
    *pResult = 0;
}


void CPropDlg::Onrun()
{
   UpdateData();
}

void CPropDlg::OnOK() 
{
	UpdateData();
	maindlg3()->Info.askbookm = m_bookm;
	maindlg3()->Info.runsec   =  m_runsec;
	maindlg3()->Info.run=m_run;
	maindlg3()->Info.lock_saver=  m_saver ;
	maindlg3()->Info.show_bm=     m_showbm;
	maindlg3()->Info.tip_day=m_tip_of_day;
	maindlg3()->Info.tips=        m_tips;	
	maindlg3()->Info.bigIcon=   m_bigicon;
	maindlg3()->Info.openSUp=   m_openSUp;
	maindlg3()->Info.jumpLast=  m_jmp    ;
	maindlg3()->Info.AMpm=      m_ampm   ;
    maindlg3()->Info.info_pos=  m_infopos;	
    maindlg3()->Info.run_kb= m_run_kb ;
	maindlg3()->Info.run_wrd=m_run_wrd;
    maindlg3()->Info.run_pointer=m_pointer;
    maindlg3()->Info.pos_panel=m_pos_panel;
//    maindlg3()->Info.run1 = m_run1;

   // maindlg3()->Info.lines=m_str;   
//    maindlg3()->wnd.SetDimens( m_str);

    run_mode = (page1) ? 0:1;
    if (run_mode==0) run_mode = (kb1) ? 0:2;
    if (run_mode==0) run_mode==3;

    maindlg3()->Info.run_mode=run_mode;
    
    	
	CPropertyPage::OnOK();
}

void CPropDlg::OnCheck9() 
{
	UpdateData(true);	
}

BOOL CPropDlg::OnSetActive() 
{	
	
    run_mode = maindlg3()->Info.run_mode;
    page1 = kb1 = wrd1 = 1;

    switch ( run_mode )
    {
        case 1: page1=0; break;
        case 2: kb1=0; break;
        case 0: wrd1 = 0; break;
    }
    UpdateData(false);
    return CPropertyPage::OnSetActive();
}

BOOL CPropDlg::PreTranslateMessage(MSG* pMsg) 
{
     maindlg3()->m_tooltip.RelayEvent(pMsg);	
	return CPropertyPage::PreTranslateMessage(pMsg);
}
