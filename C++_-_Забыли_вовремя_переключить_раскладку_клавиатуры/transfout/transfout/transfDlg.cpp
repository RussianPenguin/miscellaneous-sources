// transfDlg.cpp : implementation file
//Author Demo_S <s_dameon@yahoo.com>
//if ypu want to use this program in commercial purposes? you have to mail me about it

#include "stdafx.h"
#include "transf.h"
#include "transfDlg.h"
#include "stdio.h"
//#include <string>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//const 
CString rus;
//const 
CString eng;
UINT flags;
int id;
//int TimerID;
short mode;
//bool IsTimerWorking;

void Change(LPTSTR lpData)
{ 
	CString in=lpData;
 	CString out=""; 

 	for(int i=0;i<in.GetLength();i++)
 	{
 		short n=eng.Find(in[i]); 
 		if(n==-1){
 		out+=in[i];}
 		else{
 		out+=rus.GetAt(n);}
 	}
	lstrcpy(lpData,(LPCTSTR)out);
}


bool Changeclip()
{
bool ability=false;
bool res=false;
UINT Format;
LPTSTR lpClipData;//=new char[];
HANDLE h;
 if (OpenClipboard(AfxGetMainWnd()->m_hWnd))  
 {
	 if(IsClipboardFormatAvailable(CF_TEXT)){Format=CF_TEXT; ability=true;}
	 else{if(IsClipboardFormatAvailable(CF_OEMTEXT)){Format=CF_OEMTEXT;ability=true;}}
	 if(ability)
	 {
		res=true;
		h=::GetClipboardData(Format);
		lpClipData=(LPTSTR)h;
	//	lstrcpy(lpClipData,(LPTSTR)h);
		Change(lpClipData);
		CString temp=lpClipData;//used to store converted text, in order to paste it to clipboard later
		EmptyClipboard();
	//	HANDLE h2=static_cast<HANDLE>(lpClipData);
	//	CopyMemory(h,(PVOID)lpClipData,lstrlen(lpClipData)+1);
		::SetClipboardData(Format,(void*)(LPCTSTR)temp);


	 }
 }
 CloseClipboard();
 return res;
}



BOOL CALLBACK EXPORT EnumChildProc(HWND hwnd, LPARAM lParam)
{

	LPTSTR buf=new char[16];
	::GetClassName(hwnd,buf,16);
	LPTSTR lpszText=new char[4096];
	if ((lstrcmp(buf,"Edit")==0)||(lstrcmp(buf,"RICHEDIT")==0)||(lstrcmp(buf,"RichEdit20A")==0)||(lstrcmp(buf,"TEdit")==0))
	{
	
		switch(mode)
		{
		case 0:
		//if (mode==0)//mode 0 - change all text
		{
			UINT uLng=::SendMessage(hwnd,WM_GETTEXTLENGTH,0,0);
			::SendMessage(hwnd,WM_GETTEXT,uLng+1,(LPARAM)lpszText);
			Change(lpszText);
			::SendMessage(hwnd,WM_SETTEXT,uLng+1,(LPARAM)lpszText);
		}break;
		case 1:
		//else if(mode==1)//mode 1 -  change only selected text
		{
			if(OpenClipboard(AfxGetMainWnd()->m_hWnd))
			{	
				EmptyClipboard();
				CloseClipboard();
				::SendMessage(hwnd,WM_CUT,0,0);
				Changeclip();
				::SendMessage(hwnd,WM_PASTE,0,0);
			}
		}break;
		//case 2:Changeclip();
		}
		//Организовать замену букв тут. Вызовом функции например change;
	}else
	if (lstrcmp(buf,"RichEdit")==0)
	{
		switch(mode)
		{
		case 0:
		//if (mode==0)//mode 0 - change all text
		{
			UINT uLng=::SendMessage(hwnd,WM_GETTEXTLENGTH,0,0);
			::SendMessage(hwnd,WM_GETTEXT,uLng+1,(LPARAM)lpszText);
			Change(lpszText);
			::SendMessage(hwnd,WM_SETTEXT,uLng+1,(LPARAM)lpszText);
		}break;
		case 1:
		//else if(mode==1)//mode 1 - change only selected text
		{
			::SendMessage(hwnd,EM_GETSELTEXT,0,(LPARAM)lpszText);
			Change(lpszText);
			::SendMessage(hwnd,EM_REPLACESEL,(WPARAM)true,(LPARAM)lpszText);

		}break;
		}
		

	}
	else
		if(lstrcmp(buf,"ToolbarWindow32")==0)
		{
			LPTSTR pname=new char[10];
			::GetClassName(::GetParent(::GetParent(::GetParent(hwnd))),pname,9);
			if(lstrcmp(pname,"ATH_Note")==0)//Для безопасности, чтоб не исправляло у других приложений
			
			if(mode==1)// case 1 - change only selected text
			{
				if(OpenClipboard(AfxGetMainWnd()->m_hWnd))
				{	
					EmptyClipboard();
					CloseClipboard();
					::SendMessage(hwnd,WM_COMMAND,0x00009D26,(LPARAM)hwnd);
					Changeclip();
					::SendMessage(hwnd,WM_COMMAND,0x00009D27,(LPARAM)hwnd);
				}
			
			}
		}
	delete[] buf;
	delete[] lpszText;

	return true;

}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTransfDlg dialog

CTransfDlg::CTransfDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTransfDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTransfDlg)
	m_mode = 1;
	m_Alt = FALSE;
	m_Ctrl = FALSE;
	m_Shift = FALSE;
	m_F = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
//	IsTimerWorking=false;
}

void CTransfDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTransfDlg)
	DDX_Radio(pDX, IDC_MODE, m_mode);
	DDX_Check(pDX, IDC_ALT, m_Alt);
	DDX_Check(pDX, IDC_CTRL, m_Ctrl);
	DDX_Check(pDX, IDC_SHIFT, m_Shift);
	DDX_Radio(pDX, IDC_HOTKEY, m_F);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTransfDlg, CDialog)
	//{{AFX_MSG_MAP(CTransfDlg)
	ON_MESSAGE( WM_NOTIFYICON, OnNotifyIcon )
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_DO, OnDo)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_DO2, OnDo2)
	ON_WM_DESTROY()
	ON_MESSAGE(WM_HOTKEY, OnHotKey)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTransfDlg message handlers

BOOL CTransfDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	mode=1;
	m_mode=1;

	//Reading to strings. Symbols of first are to be replaced by symbols of second while program is working
	rus="";
	eng="";
	try
	{
		CStdioFile Fin("transf.dat",CFile::modeRead|CStdioFile::typeText);
		Fin.ReadString(rus);
		Fin.ReadString(eng);
		Fin.Close();

	}
	catch(CFileException* e)
	{
		e->ReportError(MB_OK,0);
	//	MessageBox("Failed while opening transf.dat. Defaults will be used","error",MB_OK);
		rus="QWERTYUIOP{ASDFGHJKL:ZXCVBNM<>?qwertyuiop[]asdfghjkl;'zxcvbnm,./\"ЙЦУКЕНГШЩЗХФЫВАПРОЛДЖЯЧСМИТЬБЮ,йцукенгшщзхъфывапролджэячсмитьбю.Э";
		eng="ЙЦУКЕНГШЩЗХФЫВАПРОЛДЖЯЧСМИТЬБЮ,йцукенгшщзхъфывапролджэячсмитьбю.ЭQWERTYUIOP{ASDFGHJKL:ZXCVBNM<>?qwertyuiop[]asdfghjkl;'zxcvbnm,./\"";
		e->Delete();
	}

	int sh=SW_SHOW;
	//Загрузка настроек из реестра
	CWinApp* pApp = AfxGetApp();
	mode=pApp->GetProfileInt("Settings","mode",1);
	m_mode=mode;
	
	m_F=pApp->GetProfileInt("Settings","Key",0);
	m_Alt=pApp->GetProfileInt("Settings","Alt",0);
	m_Ctrl=pApp->GetProfileInt("Settings","Ctrl",0);
	m_Shift=pApp->GetProfileInt("Settings","Shift",0);

	UpdateData(false);

	IsHide=pApp->GetProfileInt("Settings","IsHide",0);
	id=GlobalAddAtom("Hotkey for Diora's transf");
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTransfDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTransfDlg::OnPaint() 
{
	if(IsHide){OnDo();}
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTransfDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTransfDlg::OnDo() 
{
	UpdateData(true);
	mode=m_mode;
	flags=0; //initialization data for registering HotKey;
	if(m_Alt)flags|=MOD_ALT;
	if(m_Ctrl)flags|=MOD_CONTROL;
	if(m_Shift)flags|=MOD_SHIFT;

//	if (!IsTimerWorking) TimerID=SetTimer(1111,5000,0/*&TimerProc*/);
//	IsTimerWorking=true;
	IsHide=true;
	CWnd* wndMain=AfxGetMainWnd();
	UnregisterHotKey(wndMain->m_hWnd,id);
	if(RegisterHotKey(wndMain->m_hWnd,id,flags,m_F+122))
	{
		ShowWindow(SW_HIDE);
		NOTIFYICONDATA nIdIc;
		nIdIc.cbSize=sizeof(NOTIFYICONDATA);
		nIdIc.hWnd=GetSafeHwnd();
		nIdIc.uID=IDR_MAINFRAME;
		nIdIc.uFlags=NIF_MESSAGE|NIF_ICON|NIF_TIP;
		nIdIc.uCallbackMessage=WM_NOTIFYICON;
		nIdIc.hIcon=m_hIcon;
		lstrcpyn(nIdIc.szTip,"Show options window",19);
		Shell_NotifyIcon(NIM_ADD,&nIdIc);
	}
	else AfxMessageBox("Current key combination is already used by another application. Try another combination",MB_OK|MB_ICONEXCLAMATION,0);
/*	if(m_F==0){F=122;}
	else{F=123;}*/


}

void CTransfDlg::OnOK() 
{
//KillTimer	(TimerID);
UnregisterHotKey(AfxGetMainWnd()->m_hWnd,id);
GlobalDeleteAtom(id);
CDialog::OnOK();
}






LRESULT CTransfDlg::OnNotifyIcon(WPARAM wParam, LPARAM lParam)
{
//this function is used when user pressed button "Run and hide"
	IsHide=false;
UINT uID=(UINT)wParam;
UINT uMsg=(UINT)lParam;
if(uMsg==WM_LBUTTONDOWN)
{
	if(uID==IDR_MAINFRAME)
	{
		ShowWindow(SW_SHOW);
		SetFocus();
		NOTIFYICONDATA nIdIc;
		nIdIc.cbSize=sizeof(NOTIFYICONDATA);
		nIdIc.hWnd=GetSafeHwnd();
		nIdIc.uID=IDR_MAINFRAME;
		Shell_NotifyIcon(NIM_DELETE,&nIdIc);
//		KillTimer(TimerID);
//		IsTimerWorking=false;
	}
}
	return 1;
}



LRESULT CTransfDlg::OnHotKey(WPARAM wParam, LPARAM lParam)
{	
	//this function is used when user pressed hotkey, assotiated with this program
	if (mode==2){Changeclip();return 1;}
	else{
		UINT Formatclip;//this is used because while converting in mode 0&1 sometimes we use clipboard, so we want to prevent data, that was in clipboard from being damaged
		HANDLE Hclip;
		unsigned int formats[]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27};
		if(OpenClipboard()){
			Formatclip=GetPriorityClipboardFormat(formats,27);
			Hclip=GetClipboardData(Formatclip);
			CloseClipboard();
		}
		HWND hwndFor=::GetForegroundWindow();
		if(hwndFor!=0){

		EnumChildWindows(hwndFor,EnumChildProc,0);
		if(OpenClipboard()){
			SetClipboardData(Formatclip,Hclip);
			CloseClipboard();
			}
		return 1;
		}
	else {return -1;}
	}

}


void CTransfDlg::OnButton1() 
{
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}

void CTransfDlg::OnDo2() 
{
	//this function is used when user pressed button "Run"
	UpdateData(true);
	mode=m_mode;
	flags=0; //initialization data for registering HotKey;
	if(m_Alt)flags|=MOD_ALT;
	if(m_Ctrl)flags|=MOD_CONTROL;
	if(m_Shift)flags|=MOD_SHIFT;



	CWnd* wndMain=AfxGetMainWnd();
	UnregisterHotKey(wndMain->m_hWnd,id);
	if(!RegisterHotKey(wndMain->m_hWnd,id,flags,m_F+122))
		AfxMessageBox("Current key combination is already used by another application. Try another combination",MB_OK|MB_ICONEXCLAMATION,0);
}



//DEL bool CTransfDlg::Changeclip()
//DEL {
//DEL bool ability=false;
//DEL bool res=false;
//DEL UINT Format;
//DEL LPTSTR lpClipData;//=new char[];
//DEL HANDLE h;
//DEL  if (OpenClipboard())
//DEL  {
//DEL 	 if(IsClipboardFormatAvailable(CF_TEXT)){Format=CF_TEXT; ability=true;}
//DEL 	 else{if(IsClipboardFormatAvailable(CF_OEMTEXT)){Format=CF_OEMTEXT;ability=true;}}
//DEL 	 if(ability)
//DEL 	 {
//DEL 		res=true;
//DEL 		h=::GetClipboardData(Format);
//DEL 		lpClipData=static_cast<LPTSTR>(h);
//DEL 	//	lstrcpy(lpClipData,(LPTSTR)h);
//DEL 		Change(lpClipData);
//DEL 	//	EmptyClipboard();
//DEL 	//	HANDLE h2=static_cast<HANDLE>(lpClipData);
//DEL 	//	CopyMemory(h,(PVOID)lpClipData,lstrlen(lpClipData)+1);
//DEL 		HANDLE h2=SetClipboardData(Format,h);
//DEL 
//DEL 
//DEL 	 }
//DEL  }
//DEL  CloseClipboard();
//DEL  return res;
//DEL }

//DEL BOOL CALLBACK CTransfDlg::EnumChildProc(HWND hwnd, LPARAM lParam)
//DEL {
//DEL 
//DEL 	LPTSTR buf=new char[16];
//DEL 	::GetClassName(hwnd,buf,16);
//DEL 	LPTSTR lpszText=new char[];
//DEL 	if ((lstrcmp(buf,"Edit")==0)|(lstrcmp(buf,"RICHEDIT")==0))
//DEL 	{
//DEL 	
//DEL 		switch(mode)
//DEL 		{
//DEL 		case 0:
//DEL 		//if (mode==0)//mode 0 - change all text
//DEL 		{
//DEL 			UINT uLng=::SendMessage(hwnd,WM_GETTEXTLENGTH,0,0);
//DEL 			::SendMessage(hwnd,WM_GETTEXT,uLng+1,(LPARAM)lpszText);
//DEL 			Change(lpszText);
//DEL 			::SendMessage(hwnd,WM_SETTEXT,uLng+1,(LPARAM)lpszText);
//DEL 		}break;
//DEL 		case 1:
//DEL 		//else if(mode==1)//mode 1 -  change only selected text
//DEL 		{
//DEL 			if(OpenClipboard())
//DEL 			{	
//DEL 				EmptyClipboard();
//DEL 				CloseClipboard();
//DEL 				::SendMessage(hwnd,WM_CUT,0,0);
//DEL 				Changeclip();
//DEL 				::SendMessage(hwnd,WM_PASTE,0,0);
//DEL 			}
//DEL 		}break;
//DEL 		//case 2:Changeclip();
//DEL 		}
//DEL 		//Организовать замену букв тут. Вызовом функции например change;
//DEL 	}else
//DEL 	if (lstrcmp(buf,"RichEdit")==0)
//DEL 	{
//DEL 		switch(mode)
//DEL 		{
//DEL 		case 0:
//DEL 		//if (mode==0)//mode 0 - change all text
//DEL 		{
//DEL 			UINT uLng=::SendMessage(hwnd,WM_GETTEXTLENGTH,0,0);
//DEL 			::SendMessage(hwnd,WM_GETTEXT,uLng+1,(LPARAM)lpszText);
//DEL 			Change(lpszText);
//DEL 			::SendMessage(hwnd,WM_SETTEXT,uLng+1,(LPARAM)lpszText);
//DEL 		}break;
//DEL 		case 1:
//DEL 		//else if(mode==1)//mode 1 - change only selected text
//DEL 		{
//DEL 			::SendMessage(hwnd,EM_GETSELTEXT,0,(LPARAM)lpszText);
//DEL 			Change(lpszText);
//DEL 			::SendMessage(hwnd,EM_REPLACESEL,(WPARAM)true,(LPARAM)lpszText);
//DEL 
//DEL 		}break;
//DEL 		}
//DEL 		
//DEL 
//DEL 	}
//DEL 	else
//DEL 		if(lstrcmp(buf,"ToolbarWindow32")==0)
//DEL 		{
//DEL 			LPTSTR pname=new char[];
//DEL 			::GetClassName(::GetParent(::GetParent(::GetParent(hwnd))),pname,9);
//DEL 			if(lstrcmp(pname,"ATH_Note")==0)//Для безопасности, чтоб не исправляло у других приложений
//DEL 			
//DEL 			if(mode==1)// case 1 - change only selected text
//DEL 			{
//DEL 				if(OpenClipboard())
//DEL 				{	
//DEL 					EmptyClipboard();
//DEL 					CloseClipboard();
//DEL 					::SendMessage(hwnd,WM_COMMAND,0x00009D26,(LPARAM)hwnd);
//DEL 					Changeclip();
//DEL 					::SendMessage(hwnd,WM_COMMAND,0x00009D27,(LPARAM)hwnd);
//DEL 				}
//DEL 			
//DEL 		//	::SendMessage(hwnd,EM_GETSELTEXT,0,(LPARAM)lpszText);
//DEL 		//	Change(lpszText);
//DEL 		//	::SendMessage(hwnd,EM_REPLACESEL,(WPARAM)true,(LPARAM)lpszText);
//DEL 			}
//DEL 		}
//DEL 	delete[] buf;
//DEL 
//DEL 	return true;
//DEL 
//DEL }

void CTransfDlg::OnDestroy() 
{
	WinHelp(0L, HELP_QUIT);
	Store();
	CDialog::OnDestroy();

}


void CTransfDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	Store();//storing current settings in registry
	CDialog::OnClose();
}

void CTransfDlg::Store()
{
	UpdateData(true);	
	CWinApp* pApp = AfxGetApp();
	pApp->WriteProfileInt("Settings", "Mode", m_mode);
	pApp->WriteProfileInt("Settings", "Key", m_F);
	pApp->WriteProfileInt("Settings", "Alt", m_Alt);
	pApp->WriteProfileInt("Settings", "Ctrl", m_Ctrl);
	pApp->WriteProfileInt("Settings", "Shift", m_Shift);
	pApp->WriteProfileInt("Settings", "IsHide", IsHide);	
}
