// About.cpp : implementation file
//

#include "stdafx.h"
#include "wiz.h"
#include "About.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAbout property page

IMPLEMENT_DYNCREATE(CAbout, CPropertyPage)

CAbout::CAbout() : CPropertyPage(CAbout::IDD)
{
	//{{AFX_DATA_INIT(CAbout)
	m_about = _T("Z47GgZHIhZDJhfclPLYRkvK2jnAREqCleBc3EqAUEqc3FBAOByOykL9MkLD0jZK1hSNlyZ4KQ87oiaKzjvV2kv9vByNG8rJlFqA3F83RFBA4cCDzhfllpvmOja91jTG2Pl==");
	m_owner = _T("");
	m_key = _T("");
	m_regto = _T("");
	//}}AFX_DATA_INIT
    m_owner= _T(maindlg3()->Info.owner);
    m_regto = _T(maindlg3()->Info.owner);    
    //m_key= _T(maindlg3()->Info.key);    
	reg=false;
	m_about=decode_b64((char*)(LPCTSTR)m_about);
    b = (HBITMAP)LoadImage(AfxGetApp()->m_hInstance, (LPCTSTR)IDB_BITMAP9, IMAGE_BITMAP, 106, 112, LR_LOADMAP3DCOLORS) ;
}

CAbout::~CAbout()
{
}

void CAbout::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAbout)
	DDX_Control(pDX, IDC_STATIC5, m_bitm);
	DDX_Text(pDX, IDC_STATIC1, m_about);
	DDX_Text(pDX, IDC_EDIT4, m_owner);
	DDX_Text(pDX, IDC_EDIT5, m_key);
	DDX_Text(pDX, IDC_EDIT1, m_regto);
	//}}AFX_DATA_MAP
    
    showf(reg);
}


BEGIN_MESSAGE_MAP(CAbout, CPropertyPage)
	//{{AFX_MSG_MAP(CAbout)
	ON_BN_CLICKED(IDC_BUTTON25, OnMenub)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
    END_MESSAGE_MAP()
    
    /////////////////////////////////////////////////////////////////////////////
    // CAbout message handlers
    
BOOL CAbout::OnSetActive() 
{	
    char str[1000];    
    LoadString(AfxGetApp()->m_hInstance,IDS_STRING33,str,1000);
    SetDlgItemText(IDC_EDIT21,decode_b64(str) );    

    timer = SetTimer(1001,1000,NULL);       
    m_bitm.SetBitmap(b );
 

    return CPropertyPage::OnSetActive();
}

void CAbout::OnMenub() 
{
    CMenu templm; 	
    templm.LoadMenu(IDR_ABOUT   );    

    CRect r; 	
    this->GetDlgItem(IDC_BUTTON25)->GetWindowRect(r); 	
    templm.GetSubMenu(0)->TrackPopupMenu(0, r.left, r.bottom, this);			
 	
}

BOOL CAbout::OnCommand(WPARAM wParam, LPARAM lParam) 
{      
    
    switch (  wParam )
    {
    case ID_1_HOWTOREGISTER:        
        reg=false;
        LoadString(AfxGetApp()->m_hInstance,IDS_STRING30,str,1000);
        this->SetDlgItemText(IDC_EDIT21,decode_b64(str) );
            ///64("Registration Procedures:\n\nCash payment...\nAddress:\nMoldova\n2051\nsrt. Paris 27\nShilonosov Alexander \n\nBank pa ...\n My bank count is ..");
        UpdateData(false); 
        break;
    case ID_1_PRICES:
        reg=false;
        LoadString(AfxGetApp()->m_hInstance,IDS_STRING32,str,1000);
        this->SetDlgItemText(IDC_EDIT21,decode_b64(str) );
        UpdateData(false); 
        break;
    case ID_1_ENTERREGISTRATIONCODE:               
        reg = true;
        UpdateData(false);                            
        break;
    case ID_1_WWW:
        ShellExecute(maindlg3()->m_hWnd, "open", "http://www.shilonosov.f2s.com/about_soft.htm", NULL, "", 0);
        EndDialog(IDCANCEL);
        break;    
    case ID_1_FEEDBAK_BAGREPORT:        
        ShellExecute(m_hWnd, "open", "mailto:shilonosov@mail.md", NULL, "", 0);
        EndDialog(IDCANCEL);
        break;
    case ID_1_WEBBOOKSSTORAGE_WWWMOSHKOV:
        ShellExecute(NULL, "open", "www.lib.ru", NULL, "", 0);
        EndDialog(IDCANCEL);
        break;
    case ID_1_WEBBOOKSSTORAGE_WWWINKWEELRU:
        ShellExecute(m_hWnd, "open", "http://kulichki.rambler.ru/inkwell", NULL, "", 0);       
        EndDialog(IDCANCEL);
        break;
    case ID_1_WEBBOOKSSTORAGES_SYMPAD:
        ShellExecute(m_hWnd, "open", "http://www.sympad.net", NULL, "", 0);       
        EndDialog(IDCANCEL);
        break;
    }    
	
	return CPropertyPage::OnCommand(wParam, lParam);

}

void CAbout::OnButton1() 
{  
    UpdateData();
    strcpy(name,m_owner);
    strcpy(key,m_key);    
///// **********************
    int x=1,y;
    char *dd=name,ss[30];
    while ( *dd )
    {
        if ( x>28) x=0;
        ss[x++]=*dd++;
        ss[x+5]=key[1];
    }
    
    HKEY    hKey;
    int x1;
    DWORD Size=sizeof(DWORD);	
    RegCreateKey(HKEY_CURRENT_USER, "software\\shilonosov\\MadReader",&hKey);
    RegQueryValueEx( hKey,"LicenseKey", NULL, NULL, (LPBYTE)&x1, &Size );	
    if ( x1 )     
        press=strlen("Thanks For Registration!");
    else
        press=strlen("Wrong code");
    ///// **********************  
}

void CAbout::showf(bool sw)
{
    GetDlgItem(IDC_EDIT21)->ShowWindow( (!sw) ? SW_SHOW:SW_HIDE);

    GetDlgItem(IDC_STATIC2)->ShowWindow( (sw) ? SW_SHOW:SW_HIDE);
    GetDlgItem(IDC_STATIC3)->ShowWindow( (sw) ? SW_SHOW:SW_HIDE);
    GetDlgItem(IDC_EDIT4)->ShowWindow( (sw) ? SW_SHOW:SW_HIDE);
    GetDlgItem(IDC_EDIT5)->ShowWindow( (sw) ? SW_SHOW:SW_HIDE);
    GetDlgItem(IDC_BUTTON1)->ShowWindow( (sw) ? SW_SHOW:SW_HIDE);  

}

void CAbout::OnOK() 
{
    strcpy(maindlg3()->Info.key,m_key);    	
    CPropertyPage::OnOK();
    KillTimer(timer);
}

void CAbout::OnCancel() 
{
    KillTimer(timer); 
    CPropertyPage::OnCancel();
}

void CAbout::OnTimer(UINT nIDEvent) 
{   
   // каждую сек таймер проверяет введеные данные и если они правильные то ОК

    
    if ( strchr(decode_b64(key),'+') && ( (hash( strchr(key+2,'+')+1 )/ 1000)+11 == strlen(key+2) ) )
    {            
        LoadString(AfxGetApp()->m_hInstance,IDS_STRING34,str,1000);
        SetDlgItemText(IDC_EDIT21,decode_b64(str) );
        strcpy(maindlg3()->Info.owner,m_owner);
        reg=false;
        UpdateData();
    }

// примеры правильных ключей
    // зашифрованный ключ -  "Crake_dfjgo_Go!" 
    // расшифрованный ключ - "hlH7jaYUFI0BkLDshY9JhLOMju9bjRC="
// hash("Crake_dfjgo_Go!") / 1000 + 11 = 21
// len(Alex1+Crake_dfjgo_Go!) = 21 

    // Shilonosov+Crackers_Go_Go!111111111111111111:)
    // sAPoiaKzjvV2kv9vetGRgZGshfdSftP2ftP2coC4FoC4FoC4FoC4FoC4FoC4FoNO                
// hash("Crackers_Go_Go!111111111111111111:)") / 1000 + 11 = 46
// len(Alex1+Crake_dfjgo_Go!) = 46

    // 11111+Crackers_Go_Go!:)
    // 7ly4FoC4FI0BkLDqivYRku9bju9bjRCWey==      
	
// ключ делаеться с помощью утилиты Hash2.exe и base64.exe
// при создании надо учесть что-бы :
// 	длина всего расшифр. ключа совпала с Хэш суммой букв после знака "+" ,
//	деленной на 1000 плюс 11
// ( в прогу надо вводить зашифрованный ключ ) 

	CPropertyPage::OnTimer(nIDEvent);
}

