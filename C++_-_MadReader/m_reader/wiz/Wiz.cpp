// wiz.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "wiz.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define reg_ver 22

/////////////////////////////////////////////////////////////////////////////
// CWizApp

BEGIN_MESSAGE_MAP(CWizApp, CWinApp)
        //{{AFX_MSG_MAP(CWizApp)
                // NOTE - the ClassWizard will add and remove mapping macros here.
                //    DO NOT EDIT what you see in these blocks of generated code!
        //}}AFX_MSG
        ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWizApp construction

CWizApp::CWizApp()
{
        // TODO: add construction code here,
        // Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CWizApp object

CWizApp theApp;
//CWizDlg* maindlg2;
//CReadWnd* mainwnd2;  

/////////////////////////////////////////////////////////////////////////////
// CWizApp initialization

BOOL CWizApp::InitInstance()
{       
  //  MessageBeep(1);
	/*bool expiried=false;
	{
		SYSTEMTIME time;
        FILETIME time2
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
		if ( !expiried) 
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
		if ( !expiried) 
		{
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
		}
	}*/
    

#ifdef _AFXDLL
        Enable3dControls();                     // Call this when using MFC in a shared DLL
#else
        Enable3dControlsStatic();       // Call this when linking to MFC statically
#endif
        //MessageBeep(1);
		
        //MessageBeep(1);
        


        /* ( is_run1() && strlen(m_lpCmdLine)>3 ) 
        {
            PostMessage(HWND_BROADCAST, WM_CHAR+1 , 138 , LONG(m_lpCmdLine) );         
            return 1;
        } */     

		SetRegistryKey("Shilonosov\\MadReader");        
        CWizDlg dlg;
        m_pMainWnd = &dlg;        
		
		//dlg.exprd=expiried;     
        if ( *decode_b64("SA7oiaKzj3==") == 'S' )
        dlg.DoModal();        		
		
        return FALSE;
}

/////////////////////
////////////////////
IMPLEMENT_SERIAL(CRecent,CObject,2)

CRecent::CRecent() 
{
	bookm_pos=bookmarks.GetHeadPosition();
}

CRecent::CRecent(CString pth)
:path(pth)
{
	charset=0;        
	bookm_pos=NULL;
}

CRecent::~CRecent()
{
	
}

void CRecent::Serialize(CArchive& ar)
{
	    bookmarks.Serialize(ar);
        if (ar.IsStoring())
        {
                ar << path << charset << viewPort << Memo;
        }
        else
        {
                ar >> path >> charset >> viewPort >> Memo;
        }
}
/////////////////////////////////////////////////

IMPLEMENT_SERIAL(CBookm,CObject,2)
CBookm::CBookm() {}
CBookm::CBookm(CString pth, long ps, long pg)  :name(pth) , pos(ps) , page(pg)
{   }

CBookm::~CBookm()
{   }

void CBookm::Serialize(CArchive& ar)
{	    
        if (ar.IsStoring())
        {
                ar << name << pos << page; 
        }
        else
        {
                ar >> name >> pos >> page;
        }
}


//////////////////////////////////////////////////////
/****************************************************/
 // 0-head, 1-cont, 2-foot, 4-text, 5-info, 6-memo, 7-bookm, 8-save, 9-wind 

bool GetSettings(void* p, int size)
{
	HKEY    hKey;        			                   // Call for Default Settings;
	char * Key = new char [300]; 
	//int Ver=reg_ver;
	strcpy(Key,"software\\shilonosov\\MadReader");	
	RegCreateKey(HKEY_CURRENT_USER, Key, &hKey);
	DWORD Size=sizeof(DWORD);	
	DWORD Ver1;
    RegQueryValueEx( hKey,"Reg balance", NULL, NULL, (LPBYTE)&Ver1, &Size );	
	Size=size;	
	if (size==Ver1)
	{
		RegQueryValueEx( hKey,"Settings", NULL, NULL, (LPBYTE)p, &Size );
	}
	
	RegCloseKey( hKey );
	delete Key;
	
	return true;
}

bool SaveSettings(void* p, int size)
{
	HKEY    hKey; 
 	int Ver=reg_ver;
	char * Key = new char [300]; 
	strcpy(Key,"software\\shilonosov\\MadReader");	
	
	Ver=size;//reg_ver;
	RegOpenKey(HKEY_CURRENT_USER, Key,     &hKey );	
	RegSetValueEx( hKey, "Reg balance", 0, REG_DWORD , (LPBYTE)&Ver, sizeof(Ver) );    
    //RegSetValueEx( hKey, "run1", 0, REG_DWORD , (LPBYTE)&maindlg3()->Info.run1, sizeof(Ver) );    
	RegSetValueEx( hKey, "Settings", 0, REG_BINARY	, (LPBYTE)p, size );	
	CloseHandle( hKey );
	delete Key;		
	return true;
}

char b64b_table[]="A78BCDabcdeEFGwxyHIopYZfghijkPQXlmnqJKLMNOrsz01234RStuvTUVW569+/ \0";

union _B64
{
        struct
        {
                unsigned int a4:6;
                unsigned int a3:6;
                unsigned int a2:6;
                unsigned int a1:6;
        } a;
        unsigned char b[3];
        unsigned long num;
} b64;

bool choose_color(COLORREF &clr, HWND own)
{
	CHOOSECOLOR chc;
	COLORREF clrCustom[16];    
	
	chc.lStructSize=sizeof(CHOOSECOLOR);
	chc.hwndOwner=own;
	chc.rgbResult=clr;
	chc.Flags=CC_RGBINIT;
	for (int n=0; n<15; n++)
		clrCustom[n] = GetSysColor(n+2);		
	clrCustom[15] = clr;	
	chc.lpCustColors=clrCustom;
	if ( ChooseColor(&chc)  )
	{
		clr=chc.rgbResult;		
		return true;
	}
	return false;

}

bool choose_font(LOGFONT *fnt, COLORREF &clr, HWND own)
{
	   CHOOSEFONT chf;
	   chf.lStructSize = sizeof (CHOOSEFONT);
	   chf.hwndOwner = own;
	   chf.lpLogFont = fnt;
	   chf.Flags     = CF_SCREENFONTS| CF_INITTOLOGFONTSTRUCT| CF_LIMITSIZE;
	   	   chf.lCustData = 0;
	   chf.hInstance = AfxGetApp()->m_hInstance;
	   chf.lpszStyle = (LPTSTR)NULL;
	   chf.nFontType = SCREEN_FONTTYPE;
	   chf.nSizeMin  = 6;
	   chf.nSizeMax  = 24;
	   chf.lpfnHook  = NULL;
	   chf.lpTemplateName = NULL;
	   if (  ChooseFont( &chf ) )
	   {
		  // clr=chf.rgbColors;
		   return true;
	   }
	   return false;
}



char* decode_b64(char *ss)
{
	int num,n=1,a=0,b=0;
	char ch;
	char *s2=ss;
	
	while ( *(ss+b) )
	{
		ch=*(ss+b++);
		if (ch=='\r' || ch=='\n') continue;
		num=0;
		for (a=strlen(b64b_table); a>0; a--)
		{
			if (b64b_table[a]==ch)  { num=a; break; }
		}
		switch (n)
		{
		case 1: b64.a.a1=num; break;
		case 2: b64.a.a2=num; break;
		case 3: b64.a.a3=num; break;
		case 4: b64.a.a4=num; break;
		};
		n++;
		if (n>=5 )
		{
			n=1;
			*(s2)=b64.b[2];
			*(s2+1)=b64.b[1];
			*(s2+2)=b64.b[0];
			s2+=3;
		}
	}
	
	*s2=0;
	
    n=3;
    __int16 sum64=0,sm2=0;
    while ( *(ss+n++) ) sum64+=(unsigned int)*(ss+n)-30;
    memmove(&sm2,ss,2);
    if ( sum64!=sm2) 
    { 
        /*_asm
        {
            mov eax,23;
            push eax;
            push eax;
            push eax;
        }
        delete ss;
        return (char*)1313 ;*/
        memset(ss,0,2); 
    }
    return ss+2;
}

void export_text(CString &s, CWnd* par)
{
    CString s1;    
    parse_templ(s1,maindlg3()->Info.fonts[7].templ);
    CFileDialog fil (false,"txt",s1,OFN_ENABLESIZING ,"TXT files (*.txt)|*.txt|Text Files(*.txt;*.doc)|*.txt;*.doc",par);	
    maindlg3()->minim=maindlg3()->dlg_start=true;		
    maindlg3()->activedlg=(CDialog*)&fil;
    if ( fil.DoModal()==IDOK   )
    {
        CFile f1;
        f1.Open(fil.m_ofn.lpstrFile,CFile::modeCreate |CFile::modeWrite | CFile::typeText | CFile::shareDenyWrite   );
        f1.Write(s,s.GetLength());
        f1.Close();
    }
    maindlg3()->minim=maindlg3()->dlg_start=false;		    
}

void add_memo(CString &s)
{
    int memo_l =  maindlg3()->Recents.GetHead()->GetMemo().GetLength();
    CString &memo = maindlg3()->Recents.GetHead()->GetMemo();    

    if ( memo_l>30000) { MessageBeep(1); return;}
    
    if ( memo_l+s.GetLength()>30000) 
    {
        s=s.Left(30000 - memo_l);
        s+="\x0D\x0A ==== [Cuted by MadReader, 50000 bytes border] =====";
        MessageBeep(1);
    }
    
    CString s1;
    parse_templ(s1,maindlg3()->Info.fonts[5].templ);
    memo+="\x0D\x0A";
    memo+=s1;    
    memo+="\x0D\x0A";
    memo+=s;    
    memo+="\x0D\x0A";
}

void parse_templ(CString& s1, char* templ, CString& txt1, short nom)
{

	char ss[500];
	char *s2=ss,*tmp;
	strcpy(ss,templ);
	//(i==2) ? strcpy(ss,maindlg3()->Info.memo_templ) : strcpy(ss,maindlg3()->Info.bookm_templ);
	tmp=strchr(s2,'%');
	if ( tmp ==0 ) return;
	s2--;

	/*char PAGE[50];
	char PERS[50];
	char DATE[50];
	char TIME[50];
	char DAY[50];
	char FILE[50];
	char KB[50];
	char NOM[50];
	char TEXT[50];
	char USER[50];
    char PATH[50]; */

	
	bool l= false;
	while ( tmp )
	{
		if ( s2!=tmp) {	*tmp=0;	s1+=s2+1; *tmp='%';} // if not Macro
		l= false;
		switch ( hash(tmp+1) )	
		{
		case 0x2BB: s1+=mainwnd3()->GetStatName(5);	l= true; break;
		case 0x31C: s1+=mainwnd3()->GetStatName(6); l= true; break;
		case 0x2D6: s1+=mainwnd3()->GetStatName(7); l= true;break;
		case 0x2E1: s1+=mainwnd3()->GetStatName(8);	l= true;break;	
		case 0x1D1: s1+=mainwnd3()->GetStatName(9);	l= true;break;	
		case 0x2CB: s1+=mainwnd3()->GetStatName(10); l= true;break;	
		case 0xCF: s1+=mainwnd3()->GetStatName(11);	l= true;break;	
        case 0x2EE: s1+=mainwnd3()->GetStatName(12);	l= true;break;	
        case 0x1B5A: s1+=mainwnd3()->GetStatName(15);	l= true;break;	
        case 0x42A: s1+=mainwnd3()->GetStatName(16);	l= true;break;	
        case 0x1F60: s1+=mainwnd3()->GetStatName(17);	l= true;break;	
        case 0x1014: s1+=mainwnd3()->GetStatName(18);	l= true;break;	
        case 0x312B: s1+=mainwnd3()->GetStatName(19);	l= true;break;	
        case 0x2BE6: s1+=mainwnd3()->GetStatName(20);	l= true;break;	
            
        case 0x336: s1+=txt1; l= true; break;
		case 0x1188: 
			if ( txt1.IsEmpty() ) 				
				tmp+=13;   // len BOOKM_TEXT% +1 (13)
			else
				s1+=txt1; l= true;
			break;
		case 0x7A9: s1.Format("%s%d",s1,nom); l= true; break;
		}
		s2=tmp;
		tmp=strchr(tmp+1,'%');		
		if (l) s2=tmp;                       
	}
	s1+=s2+1;
    //MessageBeep(1);
    /*

  speed2         =%?_SEC_PER_100WORDS% 
speed3         =%?_WORDS_PER_10SEC% 
  */
}

int hash(char *s)
{
	_asm
	{
		mov esi,s;
		xor ebx,ebx;
		xor eax,eax;
		xor ecx,ecx
again:
		mov al,byte ptr [esi+ecx];
		cmp al,0;
		jz exi;		
		cmp al,37;   //"%"
		jz exi;
		
		inc cl;
		mul cl;
		add ebx,eax;
		
		jmp again
exi:
		mov eax,ebx
	}
        return ;
}




/////////////////////////////////////////////
/////////////////////////
void CRecent::add_bookm(CString &name, long pos, long page)
{				
	if ( bookmarks.GetCount()>50 )  return; 
	if (!bookm_pos)	bookmarks.AddHead( new CBookm(name,pos,page) );	
	//this->gco
}

short CRecent::is_page_bookmarked(long pos,long cnt)   // positioning on certain bookmark
{	
	bookm_pos=bookmarks.GetHeadPosition();
	short i =0;
	while (bookm_pos && (   (bookmarks.GetAt(bookm_pos))->pos > pos + cnt   
		                 || (bookmarks.GetAt(bookm_pos))->pos < pos ) ) 	
	{
		bookmarks.GetNext(bookm_pos);
		i++;
	}
	
	if (!bookm_pos) { cur_bname=""; return -1; } else
	{		
		fill_curr_bookmark();
	}
	return i;
}

bool CRecent::del_curr_bookm()  // after  is_page_bookmarked SHOULD be bookm_pos
{
	if (bookm_pos) bookmarks.RemoveAt(bookm_pos);
	return true;
}

int CRecent::bookms_count()
{
	return bookmarks.GetCount();
}

void CRecent::fill_curr_bookmark()
{
	if ( bookm_pos)
	{
		cur_bname=(bookmarks.GetAt(bookm_pos))->name;
		cur_pos=  (bookmarks.GetAt(bookm_pos))->pos;
		cur_page= (bookmarks.GetAt(bookm_pos))->page;
	}
}

void CRecent::change_top(CString &name, long pos, long page) // set last Bm to
{                                                            // cur page
	if ( (bookm_pos=bookmarks.GetHeadPosition()) )
	{
		if (name!="" )(bookmarks.GetAt(bookm_pos))->name=name;
		(bookmarks.GetAt(bookm_pos))->pos=pos;
		(bookmarks.GetAt(bookm_pos))->page=page;
	} else
	{
		CBookm* bm = new CBookm(name,pos,page);
		bookmarks.AddHead(bm);
		bookm_pos=bookmarks.GetHeadPosition();
		(bookmarks.GetAt(bookm_pos))->name="Bookmark";
		(bookmarks.GetAt(bookm_pos))->pos=pos;
		(bookmarks.GetAt(bookm_pos))->page=page;
	}

}

//void CRecent::load_menu_bm(CMenu &menu) // Load BMs to CMenu object
void CRecent::load_menu_bm(CStringList &bList)
{
	//POSITION p=bookmarks.GetHeadPosition();	 //headpos
	bookm_pos=bookmarks.GetHeadPosition();
	if (!bookm_pos) return;	
	//UINT itm=150;		
	while (bookm_pos) 	
	{
		//bookm_pos=p;
		fill_curr_bookmark();		
		//menu.AppendMenu(MF_STRING,itm++,cur_bname);
		bList.AddTail(cur_bname);
		bookmarks.GetNext(bookm_pos);
	}	
}

void CRecent::jmp_to(UINT bm)
{	
	bookm_pos=bookmarks.FindIndex(bm);
    fill_curr_bookmark();   
}

bool CRecent::jmp_next()
{
	if (bookm_pos)
		bookmarks.GetNext(bookm_pos);
	else 
		bookm_pos=bookmarks.GetHeadPosition();	
	if ( !bookm_pos ) bookm_pos=bookmarks.GetHeadPosition();
	   fill_curr_bookmark();   

	   return bookm_pos;
}



CString& CRecent::GetMemo()
{
	return Memo;
}

CString& CRecent::GetPath()
{
	return path;

}

long& CRecent::GetCharset()
{
	return charset;

}

CRect& CRecent::GetViewPort()
{
    return viewPort;
}

void CRecent::del_at(UINT pos)
{    
    bookmarks.RemoveAt(bookmarks.FindIndex(pos));    
}

bool CRecent::add_memo(CString &s)
{
    if ( Memo.GetLength() > 49900 ) return 0;

    CString s1;
    parse_templ(s1,maindlg3()->Info.fonts[5].templ);			
    Memo+="\x0D\x0A";
    Memo+=s1;
    Memo+="\x0D\x0A";

    if ( Memo.GetLength() + s.GetLength() > 50000 )    
    {
        s = s.Left( 49900 -  maindlg3()->Recents.GetHead()->GetMemo().GetLength() );
        s+="\x0D\x0A ==== [Cuted by MadReader, 50000 bytes border] =====";
        Memo+=s;
        return false;
    }
    Memo+=s;
    return true;
}
