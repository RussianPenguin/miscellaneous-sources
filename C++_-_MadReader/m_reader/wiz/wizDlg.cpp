// wizDlg.cpp : implementation file
//

#include "stdafx.h"
#include "winuser.h"

#include "PropDlg.h"
#include "Face.h"
#include "Find.h"
#include "Print.h"
#include "BookmText.h"
#include "About.h"
#include "MySheet.h"
#include "AdvProp.h"
#include "EvalDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define ID_TIMER_1                      1003
#define ID_TIMER_2                      1004
#define ID_TIMER_3                      1005

#define recent_cnt 25


//#define FILEMON_SETTINGS_KEY  TEXT("Software\\MadReader");
//#define FILEMON_SETTINGS_VALUE    TEXT("Settings");
//#define FILEMON_RECENT_CONNECT_VALUE  TEXT("Recent")



/////////////////////////////////////////////////////////////////////////////
// CWizDlg dialog

CWizDlg::CWizDlg(CWnd* pParent /*=NULL*/)
: CDialog(CWizDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWizDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWizDlg::DoDataExchange(CDataExchange* pDX)
{
    //MessageBeep(1);
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWizDlg)	
	DDX_Control(pDX, IDC_EDIT1, m_name);
	DDX_Control(pDX, IDC_STATIC3, m_prop);
	//}}AFX_DATA_MAP

    //m_name.EnableWindow( (wnd.isOpened()) ? true:false);
	//this->GetDlgItem(IDC_BUTTON3)->EnableWindow( (wnd.isOpened()) ? true:false);
	this->GetDlgItem(IDC_code)->EnableWindow( (wnd.isOpened()) ? true:false);
	this->GetDlgItem(ID_COLOR)->EnableWindow( (wnd.isOpened()) ? true:false);
	this->GetDlgItem(IDC_BUTTON1)->EnableWindow( (wnd.isOpened()) ? true:false);
	this->GetDlgItem(IDC_hist2)->EnableWindow( (wnd.isOpened()) ? true:false);

}

BEGIN_MESSAGE_MAP(CWizDlg, CDialog)
//{{AFX_MSG_MAP(CWizDlg)
ON_WM_TIMER()
ON_BN_CLICKED(ID_COLOR, On_Options)
ON_BN_CLICKED(IDC_OPEN, OnButton3)
ON_WM_SYSCOMMAND()	
ON_BN_CLICKED(ID_hide, Onhide)
ON_BN_CLICKED(ID_close, Onclose)
ON_WM_DROPFILES()
ON_BN_CLICKED(IDC_code, Oncode)
ON_BN_CLICKED(IDC_hist, Onhist)	
ON_UPDATE_COMMAND_UI(ID_1_DOS, OnUpdate1Dos)
ON_WM_ACTIVATEAPP()
ON_BN_CLICKED(IDC_BUTTON1, OnBookText)
ON_BN_CLICKED(IDC_hist2, OnBookmm)
ON_WM_HELPINFO()
	ON_WM_ENTERIDLE()
ON_UPDATE_COMMAND_UI(ID_1_WIN1251, OnUpdate1Dos)
ON_UPDATE_COMMAND_UI(ID_1_ISO, OnUpdate1Dos)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWizDlg message handlers

BOOL CWizDlg::OnInitDialog()
{
	CDialog::OnInitDialog();	    
	
    
	DafaultSettings();	
	GetSettings(&Info,sizeof(Info));	
    
    SYSTEMTIME time;
    GetSystemTime(&time);
    if ( Info.date!=time.wDayOfWeek)     
    {
        if ( Info.days > 0) Info.days--;
        Info.date=time.wDayOfWeek;        
    }

    open_recent();		
    repos_all();
    
	wnd.Create(NULL," ",WS_CHILD|WS_VISIBLE|WS_POPUP,  CRect(10,5,58,52), this, 1110);	
	dlg_start=false;		
    
	wnd.change_color();		          
	wnd.change_font();	    
    wnd.BringUP();	
    
    
    // давайте читать книги
	
	SetWindowText("MadReader");
	this->SetIcon(AfxGetApp()->LoadIcon(IDR_MAINFRAME),true);
	this->SetIcon(AfxGetApp()->LoadIcon(IDR_MAINFRAME1),false);	 			  
		  
		  code.LoadMenu(IDR_MENU2);
          load_menu_ch();	  
		  
		  m_tooltip.Create(this);
		  m_tooltip.Activate(Info.tips);		  		  
		  
		  b[0] = (HBITMAP)LoadImage(AfxGetApp()->m_hInstance, (LPCTSTR)IDB_BITMAP1, IMAGE_BITMAP, 14, 15, LR_LOADMAP3DCOLORS);
          SendDlgItemMessage(ID_COLOR, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)b[0]);
		  m_tooltip.AddTool(GetDlgItem(ID_COLOR), 1);
		  m_tooltip.AddTool(GetDlgItem(IDC_hist), 2);
		  m_tooltip.AddTool(GetDlgItem(IDC_code), 3);
		  m_tooltip.AddTool(GetDlgItem(IDC_EDIT1), "enter file name + <enter> = open");
		  m_tooltip.AddTool(GetDlgItem(IDC_BUTTON1),10);
		  m_tooltip.AddTool(GetDlgItem(IDC_hist2),11);		  
		  
		  for ( int i=3; i<=5; ++i)
		  {			 
			  b[i-2]=::LoadBitmap(AfxGetApp()->m_hInstance,LPCTSTR(136+i));
			  SendDlgItemMessage(1011+i, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)b[i-2]);
			  m_tooltip.AddTool(GetDlgItem(1011+i), 4+i);
		  }
          b[6]=LoadBitmap(AfxGetApp()->m_hInstance,LPCTSTR(IDB_BITMAP6));
           SendDlgItemMessage(IDC_hist2, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)b[6]);
           SendDlgItemMessage(IDC_hist, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)b[6]);
		  
           showing=true;
		  timer=SetTimer(ID_TIMER_1,300,NULL);
		  timer2=SetTimer(ID_TIMER_2,1000,NULL);    // 1 sec
		  timer3=SetTimer(ID_TIMER_3,30000,NULL);   //  30 sec
		  //::SetCursorPos(1,1 );
		  //timer_sec=0;		 
		  //timer_sec_run=Info.runsec;		  

		  
		  
		  if ( strlen(AfxGetApp()->m_lpCmdLine)>5 )		  
			  wnd.RedFile(AfxGetApp()->m_lpCmdLine,Info.decod);		  
		  else		  
			  wnd.m_edit->SetWindowText(decode_b64("zH4GgZHIhZDJhfclhL9RcDPOjLH2PTFlebPTPRVSiaKzjvV2kv9vELHmEMdueytepbYSi87xkaY1c8m2kn73kLYSkRA6hZVthfc+eyteByOchZ43wltecCg4cBtliaYzkAtecDYShIA6cKGKjLylYa6ncCumhDdKgZHKkqUljZY1PI7LkL90cCYUka42kLYRByN="));
			  /*MadReader for Windows (www.shilonosov.da.ru)
Push Open (or press <enter>)

Help:
> Move mouse to right edge of Display and push LButton/RButton - next/prev page
> Move mouse to low edge - shows panel
> press long button to set/clear boomark
> Use <Send to> menu for read files from explorer
> Drag&Drop files to read
> Hit Shift and move mouse = change the view range
> use history (^) menu for recently opened files


 Keyboard:
<enter> - open file or choose from history
<a> - set/clear bookmark
<alt+a> - set last bookmark to current page
<z> - choose bookmark jump
<tab> - jump to next bookmark
<ctrl> - show infotip
<esc> - dlg_startize all*/
		  

		  if ( !wnd.isOpened() && Info.openSUp)
		  {	
			  if ( Recents.GetHeadPosition() )
			  {
				  OnCommand(100,0);
				  if (Info.jumpLast) from_readerwnd(7,0,0,NULL);
			  }
		  }

          //cursor1 = LoadCursor(AfxGetApp()->m_hInstance,(LPCTSTR)IDC_POINTER_COPY);
          cursor1 = AfxGetApp()->LoadCursor(IDC_POINTER_COPY);

		  return TRUE;  
}


BOOL CWizDlg::DestroyWindow() 
{	
    set_file_settings();	
    SaveSettings(&Info,sizeof(Info));
	save_recent();
	KillTimer(timer); KillTimer(timer2); KillTimer(timer3);	
    for ( int i=0; i<=7; ++i) DeleteObject( b[i] ); 			
    DeleteObject(cursor1);
    KillTimer(timer);
    KillTimer(timer2);
    KillTimer(timer3);

	return CDialog::DestroyWindow();
}

void CWizDlg::start_show()
{	
 //   MessageBeep(1);
    showing=true;
    int w=30;
     bool l  = ( p_rect.top > 1 );    

    for (int step = 1; step<=w; step++)        
        SetWindowPos(&wndTopMost,
        p_rect.left, 
        p_rect.top - ( (!l) ? (w-step) : (step-w) )  ,
        0,0,
        SWP_NOSIZE | SWP_SHOWWINDOW   );   

    SetWindowPos(&wndTopMost,
        p_rect.left, 
        ( (l) ? p_rect.top:0 ),
        p_rect.right,
        p_rect.bottom,
        SWP_NOSIZE | SWP_SHOWWINDOW );    
}

void CWizDlg::start_hide()
{    
    GetWindowRect(p_rect);    
    bool l = ( p_rect.top > 1 );

    int w=30;
    for (int step = 1; step<=w; step++)        
        SetWindowPos(&wndTopMost,
        p_rect.left, 
        p_rect.top + ( (!l) ? -step : step )  ,
        0,0,
        SWP_NOSIZE | SWP_SHOWWINDOW | SWP_NOACTIVATE   );    
   
    showing=false;
}

void CWizDlg::OnTimer(UINT nIDEvent) 
{		
	::GetCursorPos(&pnt);	
    if (p_rect.top < 2 ) pnt.y+=1;
	switch (nIDEvent)
	{
	case  ID_TIMER_1:        
        if ( p_rect.PtInRect(pnt) && !dlg_start && !showing && !IsIconic())
            start_show();     			
        if ( !p_rect.PtInRect(pnt) && !dlg_start && !IsIconic() && showing)
            start_hide();		
		break;	
	case ID_TIMER_2:  // 1 sec;        
		if ( !showing && !IsIconic() && !dlg_start && wnd.isOpened() )         
            wnd.timer_1sec(Info.run_mode,0,Info.run);        
		break;
	case ID_TIMER_3:   // 30 sec
		if ( wnd.IsWindowVisible() && Info.lock_saver ) 
			keybd_event(0,0,KEYEVENTF_KEYUP,NULL);			
        if ( *decode_b64("z37ygZhLf3==") != 'P' ) // Check the AntiCracking
            SendMessage(WM_SYSCOMMAND,SC_CLOSE	,0);					
		break;
	}	

	if ( !first_e)      // first timer event , move mouse after opening ...
	{ 
        if ( wnd.isOpened() )
        {
            ::SetCursorPos(metX,metY-120 ); 
            strcpy(str1,Info.key);              
            first_e=true; 
            if ( !strchr(decode_b64(str1),'+') || ( (hash( strchr(str1+2,'+')+1 )/ 1000)+11 != strlen(str1+2) ) )
            {
                CEvalDlg dlg((CWnd*)&wnd);
                dlg_start=true;
                if ( dlg.DoModal(Info.days) == IDCANCEL)                 
                    SendMessage(WM_SYSCOMMAND,SC_CLOSE	,0);                
                dlg_start=false;
            }
        }
        else
            ::SetCursorPos(290,p_rect.top+10 ); 
		first_e=true; 
	}
	
}


void CWizDlg::On_Options() 
{
    start_hide();
	ShowTools();
}


void CWizDlg::OnButton3() 
{
	if (dlg_start) return;	
    if ( showing) start_hide();
	CFileDialog fil (true,"txt",NULL,OFN_ENABLESIZING | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY ,"All Files (*.*)|*.*|Text Files(*.txt;*.doc)|*.txt;*.doc",(CWnd*)&wnd);	
 
	dlg_start=true;		
	activedlg = (CDialog*)&fil;
	if ( fil.DoModal()!=IDCANCEL )	
		wnd.RedFile(fil.m_ofn.lpstrFile,Info.decod);         
    activedlg =NULL;	
	dlg_start=false;	
}


void CWizDlg::OnSysCommand(UINT nID, LPARAM lParam) 
{
	if (nID==SC_RESTORE)   { wnd.BringUP();	 }	
	CDialog::OnSysCommand(nID, lParam);

    if ( metX != GetSystemMetrics(SM_CXSCREEN) )
        repos_all();
}

void CWizDlg::Onhide() 
{
	wnd.ShowWindow(SW_HIDE);	 
    SetWindowPos(&wndTopMost,
        p_rect.left, 
        ( (p_rect.top >1) ? p_rect.top:0 ),
        0,0,
        SWP_NOSIZE  );    
	SendMessage(WM_SYSCOMMAND,SC_MINIMIZE,0);    
	
}


void CWizDlg::Onclose() 
{    
	SendMessage(WM_SYSCOMMAND,SC_CLOSE	,0);	
}


void CWizDlg::OnDropFiles(HDROP hDropInfo) 
{
	char name[500];
	::DragQueryFile(hDropInfo,0,(CHAR*)&name,490);	
	if ( wnd.RedFile(name,Info.decod) ==0 )    
        wnd.m_edit->SetWindowText("Error opening File !");              
	CDialog::OnDropFiles(hDropInfo);
}

void CWizDlg::Oncode() 
{  
	::GetCursorPos(&pnt);
	dlg_start=true;
	code.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN |TPM_RIGHTBUTTON,pnt.x,pnt.y,this);
	dlg_start=false;  
}

void CWizDlg::Onhist() 
{
	::GetCursorPos(&pnt);
	dlg_start=true;
	//hist.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN |TPM_RIGHTBUTTON,pnt.x,pnt.y,this);
	popup.TrackPopupMenu(TPM_LEFTALIGN |TPM_RIGHTBUTTON, pnt.x, pnt.y, this);
	
	dlg_start=false;
	
}

BOOL CWizDlg::PreTranslateMessage(MSG* pMsg) 
{    
    
    // CG: The following block was added by the ToolTips component.
    m_tooltip.RelayEvent(pMsg);
    
    switch (pMsg->message)
    {
        
    case WM_KEYDOWN :		
        if ( pMsg->wParam >='A' &&  pMsg->wParam<='Z' && showing )
        {         
            pMsg->hwnd=m_name.m_hWnd;
            m_name.SetFocus();
            break;
        }
        switch (pMsg->wParam)
        {           
        case VK_RETURN:             
            if (pMsg->hwnd==m_name.m_hWnd)
            {
                char *s = new char[200];
                m_name.GetWindowText(s,199);
                if ( !wnd.RedFile(s,0) )
                {
                    while ((long)ShellExecute(this->m_hWnd, "explore", s, "", NULL, 1)<33 && strrchr(s,'\\')	)						
                        *(strrchr(s,'\\'))='\0';												
                }
                delete s;
            } else
             //if (pMsg->hwnd==m_hWnd)
            {

                if ( !Recents.IsEmpty() )  Onhist();
                else OnButton3();
            }
            return 1;              
            break;
        case VK_ESCAPE:                         
            Onhide();            
            return 1;
            break;
        case VK_NEXT: 
            wnd.readnext(1); return 1;break;
        case VK_PRIOR: 
            wnd.readnext(0); return 1;break;                     			            
        }		
        break;			
        case WM_SYSKEYDOWN:		
            {			
                switch (pMsg->wParam)
                {							
                case 'F': 
                    from_readerwnd(9,4,0,NULL);					
                    break;
                case 'O':
                    from_readerwnd(9,1,0,NULL);					
                    break;
                case 'M':
                    from_readerwnd(9,3,0,NULL);					
                    break;
                }
            }
            break;
        /*se WM_CHAR+1: 
            if ( pMsg->wParam== 138 )
            {
                 wnd.RedFile((char*)pMsg->lParam,Info.decod);		  
            }               
            return 1;
            break;	*/
        case WM_SYSCOMMAND:
            if ( pMsg->wParam== SC_CLOSE )     EndDialog(1);
            break;
    }
    
    return CDialog::PreTranslateMessage(pMsg);
}

bool CWizDlg::showstat()
{	    
	m_prop.SetWindowText(wnd.GetStatName(1));			
	return 1;
}

void CWizDlg::OnUpdate1Dos(CCmdUI* pCmdUI) 
{
	char s[10];
	UINT charset;
    if (Info.lastm==pCmdUI->m_nID) return ;
	code.CheckMenuItem(Info.lastm,MF_BYCOMMAND	|MF_UNCHECKED	);
	Info.lastm=pCmdUI->m_nID;
	switch ( Info.lastm )
	{
	case ID_1_DOS: charset=1;	break;
	case ID_1_WIN1251:charset=0;  break;
	case ID_1_ISO: charset=2;break;		
	}
    Info.decod=charset;
	wnd.update_viewPort(1);    
	
	code.CheckMenuItem(Info.lastm,MF_BYCOMMAND	|MF_CHECKED	);
	code.GetMenuString(Info.lastm,(char*)&s,9,MF_BYCOMMAND)	;
	this->SetDlgItemText(IDC_code,(char*)&s);
	//code.
}


bool CWizDlg::DafaultSettings()
{	
	Info.lines=22;
	Info.decod=0;
	Info.lastm=ID_1_WIN1251;	
	Info.askbookm=true;
	Info.lock_saver=true;
	
	Info.show_bm=true;
	Info.tip_day=true;
	Info.tips=true;
	Info.pos.SetRectEmpty();
    Info.bigIcon=false;	

	Info.runsec=10;
    Info.run_kb = 0;
    Info.run_mode = 0;
    Info.run_pointer = false;
    Info.run_wrd = 40;
    Info.pos_panel = 1;
    Info.info_pos = 4;    
    strcpy(Info.key,"");
    strcpy(Info.owner,"Unregistered version");
    Info.date=0;
    Info.days=30;	
	
	strcpy(Info.fonts[0].templ,"===[page %PAGE% (%PERS%) from  %PATH%%FILE%]==============");
	strcpy(Info.fonts[1].templ,"Print Text");
	strcpy(Info.fonts[2].templ,"===[%DATE%, MadReader]====================================");
    strcpy(Info.fonts[3].templ,"Text");
	strcpy(Info.fonts[4].templ,"page %PAGE% (%PERS%%)\x0D\x0A%TIME%\x0D\x0A%BOOKM_TEXT%\x0D\x0A%DAY% ");	 // info
    strcpy(Info.fonts[5].templ,"====[page %PAGE%, (%DATE% , OFS:%KB%bytes ) ]============"); //memo
    strcpy(Info.fonts[6].templ,"стр.%PAGE%,(%PERS%%)  %TEXT% (%TIME%)"); //bookm    
    strcpy(Info.fonts[7].templ,"from %NAME%");
    strcpy(Info.fonts[8].templ,"%PAGE% (%PERS%)  %PATH%\\%NAME% ");
	
	for ( int x=0; x<=6; x++)
	{
        GetObject( GetStockObject(DEFAULT_GUI_FONT), sizeof LOGFONT, &Info.fonts[x] );		
        Info.fonts[x].clr=RGB(0,0,0);
        Info.fonts[x].clr_bk=RGB(220,220,160);
        Info.fonts[x].fnt.lfHeight=14;
        Info.fonts[x].fnt.lfWeight=FW_BOLD;
	}
    strcpy(Info.fonts[3].fnt.lfFaceName,"Arial");
	Info.fonts[3].fnt.lfHeight=24;
	Info.fonts[3].fnt.lfWeight=FW_BOLD;
	Info.fonts[3].clr=RGB(190,190,125);
	Info.fonts[3].clr_bk=RGB(0,0,0);

    strcpy(Info.fonts[1].fnt.lfFaceName,"Arial");
    Info.fonts[1].fnt.lfHeight=24;
    Info.fonts[1].fnt.lfWeight=FW_NORMAL;

	//*********
	create_shorcut();	
	return true;
}


void CWizDlg::OnActivateApp(BOOL bActive, HTASK hTask) 
{	
    if ( !bActive && !context_h) 
    {
        CloseAlldlg();		
        Onhide();                  
    }
    if (wnd.afterHLP)     
        wnd.SetWindowPos(&wndTopMost,0,0,0,0,SWP_NOREDRAW   |SWP_NOMOVE   |SWP_NOSIZE  );                
    
    context_h=false;    
    CDialog::OnActivateApp(bActive, hTask);	    
    
}

short CWizDlg::create_shorcut()
{
	/*HKEY    hKey; 
	char *s = new char[MAX_PATH];    
	
	RegCreateKey(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders", &hKey);    
	DWORD Size=190;		
    RegQueryValueEx( hKey,"SendTo", NULL,  NULL, (LPBYTE)s, (LPDWORD)&Size );	
	strcat(s,"\\MadReader.lnk");
	//if ( !_access(s,0) ) return 0;
	
	char *lpszPathObj =new char [MAX_PATH];
	char *lpszDesc   =new char [200];
	char *lpszPathLink =new char [MAX_PATH];
	
	strcpy(lpszPathObj,::AfxGetApp()->m_pszHelpFilePath);
	strcpy(strrchr(lpszPathObj,'\\')+1, "\0");
	strcat(lpszPathObj,::AfxGetApp()->m_pszExeName);
	strcat(lpszPathObj,".exe");
	
	strcpy(lpszDesc,"MadReader for Windows");
	strcpy(lpszPathLink,s);
	
	IShellLink* psl;
	HRESULT hres;
	
    // Get a pointer to the IShellLink interface.
	CoInitialize(NULL);	
    hres = CoCreateInstance(CLSID_ShellLink,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IShellLink,
		(void**)&psl);
	
    if (SUCCEEDED(hres))
    {
        IPersistFile* ppf;   
        psl->SetPath(lpszPathObj);
        psl->SetDescription(lpszDesc); 
        hres = psl->QueryInterface(IID_IPersistFile,(void**)&ppf);
        if (SUCCEEDED(hres))
        {
			WORD wsz[MAX_PATH];                
			MultiByteToWideChar(CP_ACP, 0, lpszPathLink, -1, wsz, MAX_PATH);                
			hres = ppf->Save(wsz, TRUE);
			ppf->Release();
        }
        psl->Release();
	}
	
	delete s;
	delete lpszDesc;
	delete lpszPathObj;
	delete  lpszPathLink;*/
	return 1;
}


void CWizDlg::repos_all()
{	
	RECT r,par;	
	
	metX=GetSystemMetrics(SM_CXSCREEN);
    metY=GetSystemMetrics(SM_CYSCREEN);
    if (Info.pos_panel==1) 
        p_rect.SetRect(0,metY-30,metX,30); // bott
    else
        p_rect.SetRect(0,1,metX,30); // up

	//SetWindowPos(&wndTopMost,0,metY-30,metX,30,SWP_NOREDRAW	  );
    SetWindowPos(&wndTopMost,
                p_rect.left,p_rect.top, p_rect.right,p_rect.bottom,
                SWP_NOREDRAW );
	
	this->GetClientRect(&par);
	int rig=GetSystemMetrics(SM_CXSCREEN);
	
	this->GetDlgItem(ID_close)->GetClientRect(&r);
	rig-=r.right;
	r.left=rig;
	r.right+=r.left;
	r.top=par.top;
	r.bottom=par.bottom;
	this->GetDlgItem(ID_close)->MoveWindow(&r,false);
	
	this->GetDlgItem(ID_hide)->GetClientRect(&r);	
	rig-=r.right;
	r.left=rig;
	r.top=par.top;
	r.bottom=par.bottom;
	r.right+=r.left;
	this->GetDlgItem(ID_hide)->MoveWindow(&r,false);
	
	this->GetDlgItem(IDC_STATIC3)->GetClientRect(&r);	
	rig-=r.right;
	r.left=rig;
	r.top=par.top+3;
	r.bottom=par.bottom;
	r.right+=r.left;
	this->GetDlgItem(IDC_STATIC3)->MoveWindow(&r,false);	
	
	this->GetDlgItem(IDC_EDIT1)->MoveWindow(400,1,rig-400,par.bottom,false);
	return;
}

BOOL CWizDlg::OnCommand(WPARAM wParam, LPARAM lParam) 
{ 
	if ( wParam>=100 &&  wParam<=100+25 )     // file history
    {
        if ( wParam-100 == popup.GetMenuItemCount()-1 ) // Click on 1st item
        {                       
            CString s1("");            
            POSITION pos = Recents.GetHeadPosition();
            while (pos)
            {         
                s1+=Recents.GetNext(pos)->GetPath();		
                s1+="\x0D\x0A";                            
            }            
            export_text(s1,&wnd);           
            return 1;            
        }        
        del_pos = Recents.GetHeadPosition();		
        for ( int x=1; x<wParam-99; x++)
            Recents.GetNext(del_pos);						

        if ( ctrl ) // delete it
        {               
            if ( wnd.isOpened() &&  wParam-100 == 0 )   { del_pos=NULL; return 1; }
            Recents.RemoveAt(del_pos);            
            Load_menu();
            del_pos=NULL;          
        } else
             wnd.RedFile((char*)(LPCTSTR)(Recents.GetAt(del_pos))->GetPath(),0);                
            load_menu_ch();		
    }
	if ( wParam>=150 && wParam<=150+50+5 )    // Bookm menu
	{
        if ( wParam-150 == bookm.GetMenuItemCount()-1 ) // Click on 1st item
        {            
            CStringList lst;
            CString s1("");
            
            Recents.GetHead()->load_menu_bm(lst);
            POSITION p=lst.GetHeadPosition();
            while (p)
            { s1+=lst.GetNext(p); s1+="\x0D\x0A";}
             Recents.GetHead()->add_memo(s1);            
            return 1;            
        }        
        if ( ctrl ) // delete it
        {   
            Recents.GetHead()->del_at(wParam-150);            
            load_menub();
            check_bookm();

        } else
        {
            Recents.GetHead()->jmp_to(wParam-150); //>first_bookm();		
            wnd.Seek_to((Recents.GetHead())->cur_pos);		
        }
    }	
	return CDialog::OnCommand(wParam, lParam);
}
/////////////////////////////////////////////////////
//////////////////////////////////////////////////////


void CWizDlg::Load_menu()
{
	
	UINT itm=100;
	
	popup.DestroyMenu();
	popup.CreatePopupMenu();        
	CString s;
    POSITION pos = Recents.GetHeadPosition();
	while (pos)
	{         
		s.Format("%3d%s   %s",
            itm-99,
            (Recents.GetAt(pos)->bookms_count()>0 ) ? "*":" ",            
            (Recents.GetNext(pos))->GetPath());		
		popup.AppendMenu(MF_STRING,itm++,s);
        
	}
	popup.SetDefaultItem(0,true); 

    popup.AppendMenu(MF_SEPARATOR,itm++);		
    popup.AppendMenu(MF_STRING,itm++,"Save filelist ...");
    popup.EnableMenuItem(itm-1, ( Recents.IsEmpty() )? MF_GRAYED:0);
}

void CWizDlg::save_recent()
{
	CFile f;
	char name[MAX_PATH];
	GetModuleFileName( GetModuleHandle(NULL),name,sizeof(name) );
	if ( strrchr(name,'\\') ); *(strrchr(name,'\\')+1)=0;
	strcat(name,"reader.dat");
    
    if ( Info.days+10 == 10)
    {
        DeleteFile(name);
        return;
    }
    
	if ( f.Open(name, CFile::modeCreate | CFile::modeWrite ) )
	{
		CArchive  ar( &f, CArchive::store );
		Recents.Serialize(ar);
		ar.Close();
		f.Close();
	}
	
}

void CWizDlg::open_recent()
{
	char name[MAX_PATH];
	GetModuleFileName( GetModuleHandle(NULL),name,sizeof(name) );
	if ( strrchr(name,'\\') ); *(strrchr(name,'\\')+1)=0;
	strcat(name,"reader.dat");
    
    if ( Info.days+10 == 10)
    {
        DeleteFile(name);
        return;
    }
    
    CFile f;
	if ( f.Open(name, CFile::modeRead ) )
	{
		CArchive  ar( &f, CArchive::load );
		Recents.Serialize(ar);
		ar.Close();
		f.Close();
		Load_menu();
	}    
}

void CWizDlg::add_recent(CString &path)
{
	if (del_pos)
	{		
		Recents.AddHead(Recents.GetAt(del_pos));
		Recents.RemoveAt(del_pos);
		del_pos=NULL;
	} else
	{		
		if (Recents.GetCount() >= recent_cnt) Recents.RemoveTail();
        CRecent* pPath = new CRecent(path);       
		Recents.AddHead(pPath);
        
        Recents.GetHead()->GetViewPort()= CRect(60,40,metX-40,metY-40);        
        Recents.GetHead()->GetCharset()=Info.decod;        
	}
	Load_menu();
}


//DEL BOOL CWizDlg::PreCreateWindow(CREATESTRUCT& cs) 
//DEL {
//DEL 	//cs.dwExStyle= WS_EX_TOOLWINDOW | WS_EX_ACCEPTFILES | WS_EX_TOPMOST;	
//DEL 	return CDialog::PreCreateWindow(cs);
//DEL }


void CWizDlg::OnBookText() 
{
	if ( !wnd.isOpened()) return;
	if ( Recents.GetHead()->bookms_count()>50 ) {AfxMessageBox("No more than 50 bookmarks"); return; }
	if ( marked_page ) { Recents.GetHead()->del_curr_bookm(); load_menub(); check_bookm(); return; }	
	
	CString s1;
	if ( Info.askbookm )		
	{
		if (dlg_start) return;
		dlg_start=true;			
		CBookmTextDlg cb((CWnd*)&wnd);		
		activedlg = (CDialog*)&cb;
		if ( cb.DoModal()==IDOK )
		{		
			parse_templ(s1,Info.fonts[6].templ,cb.m_text,Recents.GetHead()->bookms_count()+1);
			Recents.GetHead()->add_bookm(s1,wnd.get_dim(),0);						
		}			
		dlg_start=false; 
		
	} else
	{
		char text[50];
		wnd.m_edit->GetWindowText(text,30);
		text[29]=0;
		parse_templ(s1,Info.fonts[6].templ,CString(text),Recents.GetHead()->bookms_count()+1);
		Recents.GetHead()->add_bookm(s1,wnd.get_dim(),0);			
	} 
	load_menub();		
	check_bookm();
	save_recent();
}

void CWizDlg::OnBookmm() 
{
	::GetCursorPos(&pnt);
	dlg_start=true;	
	bookm.TrackPopupMenu(TPM_LEFTALIGN |TPM_RIGHTBUTTON, pnt.x, pnt.y, this);	
	dlg_start=false;	
}

void CWizDlg::load_menub(POSITION ps)
{
	CStringList bList;
	bookm.DestroyMenu();
	bookm.CreatePopupMenu();        				
	Recents.GetHead()->load_menu_bm(bList);	

	UINT itm=150;		
	POSITION p=bList.GetHeadPosition();
	while (p)
		bookm.AppendMenu(MF_STRING,itm++,bList.GetNext(p));		

    bookm.AppendMenu(MF_SEPARATOR,itm++);		
    bookm.AppendMenu(MF_STRING,itm++,"Store bookmarks list in memo");
    bookm.EnableMenuItem(itm-1, ( bList.IsEmpty() )? MF_GRAYED:0);
}

bool CWizDlg::check_bookm()
{	
	marked_page=false;
	if (Recents.GetHead())
	{				
		int i=Recents.GetHead()->is_page_bookmarked(wnd.get_dim()-50,wnd.page_kb);		        
		marked_page=(i>=0)?true:false;
		bookm.SetDefaultItem((i>=0)?i:-1,true);
		SetDlgItemText(IDC_BUTTON1,Recents.GetHead()->cur_bname);	
	}
	return marked_page;
}

void CWizDlg::from_readerwnd(short v, int v1, int v2, char *v3)
{
	switch ( v)
	{
	case 1: 
        // opened new file;                
        //MessageBeep(1);
		add_recent(CString(v3));					
        get_file_settings();
		m_name.SetWindowText(v3);
        wnd.update_viewPort(1);
        UpdateData();
		//check_bookm();
        first_e=false; // move mouse 		
        load_menub(NULL);	
        //*********************************


        //GetSettings(&Info,sizeof(Info),AfxGetApp()->m_pszRegistryKey);
        /*strcpy(str1,Info.key);              
        if ( !strchr(decode_b64(str1),'+') || ( (hash( strchr(str1+2,'+')+1 )/ 1000)+11 != strlen(str1+2) ) )
        {   
            str1[0] == '1';            
        } */                   
            
        //***************************************************
        
		/*{
			bool expiried=false;
			SYSTEMTIME time;
			FILETIME time2;
			char drv_str[MAX_PATH];
			char* s=drv_str;
			
			WIN32_FIND_DATA fnd;
			HANDLE done;
			bool find=false;
			char name[10];
			
			GetLocalTime(&time);
			if ( time.wMonth > 9 || time.wYear>2000)
			{
				expiried=true;			
			}
			SystemTimeToFileTime(&time,&time2);
			GetLogicalDriveStrings(49,drv_str);
			
				do
				{
					if ( GetDriveType(s)!=DRIVE_FIXED) { s+=4;      continue; }
					strcpy(name,s); strcat(name,"*.*");			
					if ( (done=FindFirstFile(name,&fnd))!=INVALID_HANDLE_VALUE )
						do
						{
							if ( CompareFileTime(&time2,&fnd.ftLastWriteTime)==-1 )
							{						
								expiried=true;
								break;						
							}
						}
						while ( FindNextFile(done,&fnd) );
						s+=4;
						
                } while ( *s );                
                
                GetWindowsDirectory(drv_str,MAX_PATH);
                strcat(drv_str,"\\*.*");		
                if ( (done=FindFirstFile(drv_str,&fnd))!=INVALID_HANDLE_VALUE )
                    do
                    {
                        if ( CompareFileTime(&time2,&fnd.ftLastWriteTime)==-1 )
                        {
                            expiried=true;
                            break;						
                        }
                    }
                    while ( FindNextFile(done,&fnd) );					                    
                    
                if (expiried)
                {
                    this->SendMessage(WM_SYSCOMMAND,SC_CLOSE	,0);
                    //this->EndDialog(1);	
                }
                if (expiried && wnd.isOpened() )
                {
                    wnd.CloseWindow();                                 
                }
        }*/
		
		//******************************
        //break;
    case 2:                 // page changed (pgUp/pgDn)		                
        showstat();
        check_bookm();            
        parse_templ(templ_str,Info.fonts[8].templ);            
        SetWindowText(templ_str);		        
        
        if (Info.show_bm && marked_page) wnd.draw_bm_lable(1);                
        break;
	case 3: OnBookText();                  // pressed "a"
		break;
	case 4: OnBookmm();                    // press "z"
		break;
	case 5: Info.lines=v1;                 // change number of lines ( sizes(); when ReadFile(); );
		    
		break;
	case 6:      //alt+a
		if ( marked_page ) break;		
		Recents.GetHead()->change_top(CString(""),wnd.get_dim(),0);
		load_menub();
		check_bookm();
        if (Info.show_bm && marked_page) wnd.draw_bm_lable(1);
		break;
	case 7:     //tab		
		if ( Recents.GetHead()->jmp_next() )
		wnd.Seek_to((Recents.GetHead())->cur_pos);
		break;
	case 8: // alt-m
		ShowTools(2);
		break;	
	case 9: //alt-f
		ShowTools(v1);
		break;	
    case 27: // close file;
        set_file_settings();
        break;


	}
	/*if (exprd)
		{
			this->SendMessage(WM_SYSCOMMAND,SC_CLOSE	,0);
			this->EndDialog(1);	
		}*/	
}

void CWizDlg::load_menu_ch()
{	
	code.CheckMenuItem(Info.lastm,MF_BYCOMMAND |MF_UNCHECKED	);
	int i;
	switch ( Info.decod )
	{
	case 0: Info.lastm=ID_1_WIN1251;  break;
	case 1: Info.lastm=ID_1_DOS; 	break;	
	case 2: Info.lastm=ID_1_ISO; break;		
	}
	code.CheckMenuItem(Info.lastm,MF_BYCOMMAND |MF_CHECKED	);
	code.GetMenuString(Info.lastm,(char*)&str1,9,MF_BYCOMMAND)	;
	SetDlgItemText(IDC_code,(char*)&str1);
}

CWizDlg* maindlg3()
{
	return (CWizDlg*)AfxGetApp()->GetMainWnd();
}

void CWizDlg::ShowTools(int sTpage)
{
	if ( dlg_start || !wnd.isOpened() ) return;				
	
	CMySheet sh("Tools panel",(CWnd*)&wnd);	    
	CPropDlg prop1;	   	
	CAdvProp   prop2;	
	CFace    prop3;
	CPrint   prop4;		
	CFind    prop5;	
	//CInfo    prop6;	
	CAbout   prop7;	
	
	
	(sTpage>0) ? sh.m_psh.nStartPage=sTpage-1 : 0;
	
	sh.AddPage(&prop1);
	sh.AddPage(&prop2);
	sh.AddPage(&prop3);
	sh.AddPage(&prop4);
	sh.AddPage(&prop5);
	//sh.AddPage(&prop6);
	sh.AddPage(&prop7);	
	sh.m_psh.dwFlags|=PSH_USEHICON|PSH_NOAPPLYNOW |PSH_HASHELP;
	
	dlg_start=true;		
	activedlg = (CDialog*)&sh;

    SaveSettings(&Info,sizeof(Info));
	if ( sh.DoModal()==IDOK)
    {		
        wnd.change_font();
        wnd.change_color();       
        m_tooltip.Activate(Info.tips);	   
    } else
        GetSettings(&Info,sizeof(Info));
		
    activedlg = NULL;
	dlg_start=false;	       
}

void CWizDlg::CloseAlldlg()
{
    if (dlg_start && activedlg )
    {
        activedlg->EndDialog(IDCANCEL);  
        activedlg=NULL;
        dlg_start = false;     
    }
}

BOOL CWizDlg::OnHelpInfo(HELPINFO* pHelpInfo) 
{
    WinHelp(0,HELP_CONTENTS);	
    return true;	
    
}

void CWizDlg::set_file_settings()
{
    if ( Recents.GetCount()>0 )
    {
        wnd.m_edit->GetWindowRect(Info.pos);
        
        Recents.GetHead()->GetCharset()=Info.decod;
        Recents.GetHead()->GetViewPort()=Info.pos; 
        Info.lines=wnd.cnt;

           //    CString s1;
        //s1.Format("%d",Info.decod);
          // AfxMessageBox(s1);
    }
}

void CWizDlg::get_file_settings(POSITION pos)
{
    if (pos)
    {
        //MessageBeep(1);
        Info.decod=Recents.GetAt(pos)->GetCharset();
        Info.pos=Recents.GetAt(pos)->GetViewPort();        

     //   CString s1;
       // s1.Format("%d",Info.decod);
         //  AfxMessageBox(s1);

        return;
    }
    if (  Recents.GetHead() )
    {
        Info.decod=Recents.GetHead()->GetCharset();
        Info.pos=Recents.GetHead()->GetViewPort();
    }
}

bool CWizDlg::is_runpointer_enable()
{
    return (Info.run && Info.run_pointer) && 
           (!showing && !IsIconic() && !dlg_start );
}


void CWizDlg::OnEnterIdle(UINT nWhy, CWnd* pWho) 
{
    CDialog::OnEnterIdle(nWhy, pWho);
    if ( GetKeyState(VK_CONTROL) < 0 ) 
    {
        SetCursor(cursor1);	
        ctrl = true;
    }
    else
    {
        SetCursor( LoadCursor(NULL,IDC_ARROW) );  
        ctrl = false;
    }
}
