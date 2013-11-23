// Find.cpp : implementation file
//

#include "stdafx.h"
#include "wiz.h"
#include "Find.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFind property page

IMPLEMENT_DYNCREATE(CFind, CPropertyPage)

CFind::CFind() : CPropertyPage(CFind::IDD)
{
	//{{AFX_DATA_INIT(CFind)
	m_text = _T("");
	m_statist = _T("");
	m_case = FALSE;
	//}}AFX_DATA_INIT
	down=0;
	display_pos=0;
	fnds=0;
		
}

CFind::~CFind()
{
}

void CFind::DoDataExchange(CDataExchange* pDX)
{
	m_statist.Format("Page:%d (%s...) %s (finded:%d)", mainwnd3()->pages, curr_fnd, ( s1.IsEmpty() ) ? (down==0)?"Reach the end":"Reach the begin":" ",fnds );

	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFind)
	DDX_Control(pDX, IDC_BUTTON4, m_findall);
	DDX_Control(pDX, IDC_LIST2, m_list);
	DDX_Control(pDX, IDC_BUTTON8, m_bookm);
	DDX_Control(pDX, IDC_BUTTON6, m_stop);
	DDX_Control(pDX, IDC_BUTTON9, m_find);
	DDX_Text(pDX, IDC_EDIT20, m_text);
	DDX_Text(pDX, IDC_EDIT2, m_statist);
	DDX_Radio( pDX,IDC_RADIO2,down);
	DDX_Check(pDX, IDC_CHECK17, m_case);
	//}}AFX_DATA_MAP


	if ( mainwnd3()->isOpened())
	{
	m_find.EnableWindow(!m_text.IsEmpty() );
	m_stop.EnableWindow(!m_text.IsEmpty() );
	m_bookm.EnableWindow(display_pos );
    m_findall.EnableWindow(!m_text.IsEmpty());	
	//m_findall.EnableWindow(!m_text.IsEmpty() && !this->GetDlgItem(IDC_LIST2)->IsWindowVisible() );	
	}	
	
}


BEGIN_MESSAGE_MAP(CFind, CPropertyPage)
	//{{AFX_MSG_MAP(CFind)
	ON_BN_CLICKED(IDC_BUTTON9, OnFind)
	ON_EN_CHANGE(IDC_EDIT20, OnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON4, OnFindAll)
	ON_BN_CLICKED(IDC_RADIO1, OnUPRatio)
	ON_BN_CLICKED(IDC_RADIO2, OnDNratio)
	ON_NOTIFY(NM_RCLICK, IDC_LIST2, OnListMenu)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST2, OnDblclkList2)
	ON_BN_CLICKED(IDC_BUTTON6, Onstop)
	ON_BN_CLICKED(IDC_BUTTON8, OnBookm)
	
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFind message handlers

void CFind::OnFind() 
{	
    UpdateData();
	CProgressCtrl* prgs = (CProgressCtrl*)this->GetDlgItem(IDC_PROGRESS1);
	prgs->ShowWindow(true);	
	prgs->SetRange( 0, 100 );	

	bool show_p = false;	
	stop=false;

    if ( !m_case) m_text.MakeLower();
    //s1.Empty();
    
	while ( (display_pos=s1.Find(m_text,display_pos+1)) == -1 && !s1.IsEmpty() && !stop )
	{		
		prgs->SetPos(mainwnd3()->read_hide( (down==0)?1:2, s1));
        if ( !m_case) s1.MakeLower();
		show_p=true;
		display_pos=0;							
	}	
	prgs->ShowWindow(false);	
	//UpdateData(false);	
	
	if ( s1.IsEmpty() )
	{		
		MessageBeep(1);		
		mainwnd3()->Seek_to(curr_pos);
		mainwnd3()->read_hide( 0 , s1);
		return;
	}
	
	if (show_p) // If new page loaded by read_hide() ^ , then Show it and Set selection
	{
		mainwnd3()->show_curr_page(0,0); 
		mainwnd3()->read_hide( 0, s1);
        if ( !m_case) s1.MakeLower();
		display_pos=s1.Find(m_text,0);
	} 
	mainwnd3()->m_edit->SetSel(display_pos,display_pos+m_text.GetLength());		
	curr_fnd=s1.Mid(display_pos,display_pos+m_text.GetLength()+10);		
	int l=curr_fnd.FindOneOf("\n\x9");
	curr_fnd=curr_fnd.Left( (l==-1)? 20:l );				
	m_bookm.EnableWindow(true);	
	curr_pos=mainwnd3()->get_dim();	
	UpdateData(false);	
	
}

void CFind::OnBookm() 
{	
	CString s2;
	mainwnd3()->m_edit->GetWindowText(s2);
	int x1,x2;	
	if ( x1!=x2) 
	{		
		parse_templ(s2,maindlg3()->Info.fonts[6].templ,curr_fnd,maindlg3()->Recents.GetHead()->bookms_count()+1);
		maindlg3()->Recents.GetHead()->is_page_bookmarked(0,0);
		maindlg3()->Recents.GetHead()->add_bookm(s2,curr_pos,0);
	}
	maindlg3()->load_menub();
}

void CFind::OnChangeEdit1() 
{
	display_pos = 0;
	UpdateData();			
}

BOOL CFind::OnSetActive() 
{
	if ( mainwnd3()->isOpened() )
	{
		curr_pos =begin_pos =mainwnd3()->get_dim();
		curr_page= mainwnd3()->pages;	
		mainwnd3()->read_hide(0,s1);
	}

    //if ( m_list.GetColumnWidth(0) )
    //{        
       /* m_list.DeleteAllItems();
        m_list.DeleteColumn(0); m_list.DeleteColumn(0); m_list.DeleteColumn(0);
        m_list.InsertColumn(1,"Page",LVCFMT_LEFT,40);
        m_list.InsertColumn(2,"#",LVCFMT_LEFT,30);
        m_list.InsertColumn(3,"text",LVCFMT_LEFT,240);*/
        
        m_list.SetExtendedStyle(m_list.GetExtendedStyle()|LVS_EX_HEADERDRAGDROP|LVS_EX_FULLROWSELECT );
    //}
    stop=false;
	
	return CPropertyPage::OnSetActive();

	
	//UpdateData(false);

}

void CFind::OnFindAll() 
{
    UpdateData();
    
    m_list.DeleteAllItems();
    m_list.DeleteColumn(0); m_list.DeleteColumn(0); m_list.DeleteColumn(0);
    m_list.InsertColumn(1,"Page",LVCFMT_LEFT,40);
    m_list.InsertColumn(2,"#",LVCFMT_LEFT,30);
    m_list.InsertColumn(3,"text",LVCFMT_LEFT,240);
    
	CProgressCtrl* prgs = (CProgressCtrl*)this->GetDlgItem(IDC_PROGRESS1);
	prgs->ShowWindow(true);	
	prgs->SetRange( 0, 100 );
		
	this->GetDlgItem(IDC_LIST2)->SetRedraw(false);	

	CString s2,s3,orig;
	fnds=0;	
	stop=false;

    if ( !m_case) m_text.MakeLower();
	
	while ( !s1.IsEmpty() && !stop)
	{		
		prgs->SetPos(mainwnd3()->read_hide( (down==0)?1:2, s1));		

        orig = s1;
        if ( !m_case) s1.MakeLower();
		display_pos=0;
		int col=0;
		while ( (display_pos=s1.Find(m_text,display_pos+1)) != -1 )
		{
			if ( col==0) s3=orig.Mid(display_pos,m_text.GetLength()+100 );
			++col;
		}
        //s1=orig;

		if  ( col>0 )
		{
			++fnds;
			int c = m_list.GetItemCount();
			s2.Format("%d",mainwnd3()->pages);
			m_list.InsertItem(c,s2);						
			s2.Format("%d",col);
			m_list.SetItemText(c,1,s2);      
			m_list.SetItemText(c,2,s3);
			m_list.SetItemData(c,mainwnd3()->get_dim()-50);
		}		
	}
	mainwnd3()->Seek_to(curr_pos);
	prgs->ShowWindow(false);	
	this->GetDlgItem(IDC_LIST2)->ShowWindow(true);	
	this->GetDlgItem(IDC_EDIT2)->MoveWindow(10,340,310,20);
	this->GetDlgItem(IDC_LIST2)->SetRedraw(true);
	
	UpdateData(false);		
	
}

void CFind::OnCancel() 
{
	mainwnd3()->Seek_to(begin_pos);		
	CPropertyPage::OnCancel();
}

void CFind::OnUPRatio() 
{
	down=1;	
	
}

void CFind::OnDNratio() 
{
	down=0;		
}

void CFind::OnListMenu(NMHDR* pNMHDR, LRESULT* pResult) 
{
    if ( m_list.GetItemCount()==0 ) return ;
	popup.LoadMenu(IDR_MENU3);		
	bool en = m_list.GetSelectedCount()>1;	
    
	popup.GetSubMenu(0)->EnableMenuItem(4,MF_BYPOSITION  | (( en ) ? MF_DISABLED | MF_GRAYED :0 ) );	
	popup.GetSubMenu(0)->EnableMenuItem(0,MF_BYPOSITION  | (( en ) ? MF_DISABLED | MF_GRAYED :0 ) );		
	popup.GetSubMenu(0)->SetDefaultItem(4,true);

	
	CPoint mouse;
	::GetCursorPos(&mouse);	
	popup.GetSubMenu(0)->TrackPopupMenu(TPM_RIGHTALIGN,mouse.x+50,mouse.y-20,this);			
	*pResult = 0;
}

void CFind::OnDblclkList2(NMHDR* pNMHDR, LRESULT* pResult) 
{		
	mainwnd3()->Seek_to(m_list.GetItemData(m_list.GetSelectionMark())+50);
	curr_pos=mainwnd3()->get_dim();
	UpdateData(false);		
	mainwnd3()->read_hide(0,s1);	
	
	*pResult = 0;
}

BOOL CFind::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	switch ( wParam)
	{
	case ID_1_COPY:				
		if ( OpenClipboard() ) 
		{		
			if( EmptyClipboard() )  
			{ 
				CString mm = m_list.GetItemText(m_list.GetSelectionMark(),2);
				LPTSTR p = mm.GetBuffer( 10 );
				::SetClipboardData( CF_TEXT, (void*)p);				
			}
			::CloseClipboard();
		}
		break;
	
	case ID_1_SELECTALL:
		{
			for (int n=0; n < m_list.GetItemCount(); n++)				
				m_list.SetItemState(n, LVIS_SELECTED, LVIS_SELECTED);			
		}
		break;
	case ID_1_DELETE:				
		cross_items(1);					
		break;
	case ID_1_BOOKMARK:
		cross_items(2);					
		break;
	case ID_1_MEMO:
		cross_items(3);					
		break;
    case ID_1_SAVETEXT:
        cross_items(4);					
        break;
	case ID_1_JUMP:						
		mainwnd3()->Seek_to(m_list.GetItemData(m_list.GetSelectionMark())+50);
		curr_pos=mainwnd3()->get_dim();
		UpdateData(false);		
		mainwnd3()->read_hide(0,s1);			
		break;
	}	
	return CPropertyPage::OnCommand(wParam, lParam);
}

int CFind::cross_items(short p)
{	
    CDWordArray arr;    
    POSITION pos = m_list.GetFirstSelectedItemPosition();		
    while (pos) 	
        arr.Add(m_list.GetNextSelectedItem(pos));				

	switch ( p)
	{
	case 1: delete_sel(arr); break;
	case 2: bookm_sel(arr); break;
	case 3: memo_sel(arr); break;
    case 4: save_sel(arr); break;
	}		
	return 1;
}
//********************************************************
// Tools for Items in List
//********************************************************
void CFind::save_sel(CDWordArray &arr)
{
    CString s2,s3;		
	s2.Empty(); s3.Empty();
    int l;
	
	for ( int x=0 ;  x<=arr.GetSize()-1; ++x)
	{			
		s2=m_list.GetItemText(x,2);		
        l=s2.FindOneOf("\n\x9");
		s3+=s2.Left( (l==-1)? 20:l );				
        s3+="\x0D\x0A";
		m_list.SetItemState(x, 0, LVIS_SELECTED);   
    }    
    export_text(s3,this);
}
void CFind::delete_sel(CDWordArray &arr)
{
	for ( int x = arr.GetSize()-1; x>=0; --x)
	m_list.DeleteItem(arr.GetAt(x));	
}

void CFind::bookm_sel(CDWordArray &arr)
{
	CString s2;	
	maindlg3()->Recents.GetHead()->is_page_bookmarked(0,0);
	for ( int x=0 ;  x<=arr.GetSize()-1; x++)
	{		
		s2=m_list.GetItemText(x,2);
		int l=s2.FindOneOf("\n\x9");
		s2=s2.Left( (l==-1)? 20:l );				
		maindlg3()->Recents.GetHead()->add_bookm(s2,m_list.GetItemData(x)+50,0);						
		m_list.SetItemState(x, 0, LVIS_SELECTED);   
	}
	maindlg3()->load_menub();	

}

void CFind::memo_sel(CDWordArray &arr)
{
	CString s2,s3;	
	maindlg3()->Recents.GetHead()->is_page_bookmarked(0,0);	
    int l;	
	for ( int x=0;  x<=arr.GetSize()-1; x++)
	{			
		s2=m_list.GetItemText(x,2);		
        l=s2.FindOneOf("\n\x9");
		s3+=s2.Left( (l==-1)? 20:l );				
        s3+="\x0D\x0A";
		m_list.SetItemState(x, 0, LVIS_SELECTED);   
    }
    add_memo(s3);
    //if ( !maindlg3()->Recents.GetHead()->add_memo(s3) )
        
}
//********************************************************
//********************************************************

void CFind::Onstop() 
{
	stop=true;
}


