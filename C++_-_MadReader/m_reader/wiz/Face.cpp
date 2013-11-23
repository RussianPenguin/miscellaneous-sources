// Face.cpp : implementation file
//

#include "stdafx.h"
#include "Face.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFace property page

IMPLEMENT_DYNCREATE(CFace, CPropertyPage)

CFace::CFace(): CPropertyPage(CFace::IDD)
{
	/*if (maindlg->wnd.isOpened())
	    m_memo = maindlg->Recents.GetHead()->GetMemo();
	else	
	*/

	//{{AFX_DATA_INIT(CFace)		
		m_memo =_T("");
	m_size = _T("");
	//}}AFX_DATA_INIT

		
}

CFace::~CFace()
{
}

void CFace::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFace)
	DDX_Control(pDX, IDC_EDIT8, m_memo2);
	DDX_Text(pDX, IDC_EDIT8, m_memo);
	DDX_Text(pDX, IDC_STATIC1, m_size);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFace, CPropertyPage)
	//{{AFX_MSG_MAP(CFace)
	ON_BN_CLICKED(IDC_BUTTON21, OnSave)
	ON_BN_CLICKED(IDC_BUTTON22, OnClear)
	ON_EN_CHANGE(IDC_EDIT8, OnChangeEdit8)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFace message handlers


void CFace::OnOK() 
{
	UpdateData();
	maindlg3()->Recents.GetHead()->GetMemo()=m_memo;
	
	CPropertyPage::OnOK();
}

void CFace::OnSave() 
{
	CString s1;
    
	parse_templ(s1,maindlg3()->Info.fonts[7].templ);
	CFileDialog fil (false,"txt",s1,OFN_ENABLESIZING ,"All Files (*.*)|*.*|Text Files(*.txt;*.doc)|*.txt;*.doc",this);	
	maindlg3()->minim=maindlg3()->dlg_start=true;		
	if ( fil.DoModal()!=IDCANCEL   )
	{
		CFile f1;
		int x1,x2;	
		
		f1.Open(fil.m_ofn.lpstrFile,CFile::modeCreate |CFile::modeWrite | CFile::typeText | CFile::shareDenyWrite   );		
		f1.Write(m_memo,m_memo.GetLength());
	}		
	maindlg3()->minim=maindlg3()->dlg_start=false;	
}



BOOL CFace::OnSetActive() 
{
	(maindlg3()->wnd.isOpened()) ?
	    m_memo = maindlg3()->Recents.GetHead()->GetMemo() :			
		m_memo =_T("");
    m_size.Format("Size: %d",m_memo.GetLength() );
		UpdateData(false);

	return CPropertyPage::OnSetActive();
}

void CFace::OnClear() 
{
	m_memo.Empty();
    m_size.Format("Size: %d",m_memo.GetLength() );		
	UpdateData(false);
}

void CFace::OnChangeEdit8() 
{
	m_size.Format("Size: %d",m_memo2.GetWindowTextLength() );
    GetDlgItem(IDC_STATIC1)->SetWindowText(m_size);    	
}
