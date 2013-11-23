// Edit2.cpp : implementation file
//

#include "stdafx.h"
#include "wiz.h"
#include "Edit2.h"
#include "EZMenu.h"
#include "resource.h"	


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEdit2

CEdit2::CEdit2()
{
}

CEdit2::~CEdit2()
{
}


BEGIN_MESSAGE_MAP(CEdit2, CEdit)
	//{{AFX_MSG_MAP(CEdit2)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEdit2 message handlers

BOOL CEdit2::PreTranslateMessage(MSG* pMsg) 
{
	switch (pMsg->message)
	{
	case WM_RBUTTONDOWN:
		{	
			ShowMenu();			
			return 1;			
		}
	}
	
	return CEdit::PreTranslateMessage(pMsg);
}

BOOL CEdit2::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	if ( wParam>99 && wParam<150)		
	{ 
		if ( wParam==103 ) 
		{
			this->SetSel(0,-1);
			ShowMenu();
			return 1;
        }		
		mainwnd3()->from_edit2(wParam);		

	}
	
	return CEdit::OnCommand(wParam, lParam);
}



void CEdit2::ShowMenu()
{
    CEZMenu ezmenu;
    char ss[300];
    CMenu menu;
    menu.CreatePopupMenu();			
    ezmenu.Attach(menu.GetSafeHmenu());
    
    int col=9;
    bool m_bLargeIcons=maindlg3()->Info.bigIcon;
    
    ezmenu.SetTotalItems(col);
    
    strcpy(s,maindlg3()->Info.key);
    if ( !strchr(decode_b64(s),'+') || ( (hash( strchr(s+2,'+')+1 )/ 1000)+11 != strlen(s+2) )  )
    {   
        ezmenu.SetMenuBitmap((HBITMAP)LoadImage(AfxGetInstanceHandle(),(LPCTSTR)IDB_BITMAP8,IMAGE_BITMAP,26,200, LR_LOADMAP3DCOLORS));
        ezmenu.SetBitmapDimension(CSize(26,200));          
        
    } else  
        ezmenu.SetBitmapDimension(CSize(0,0));
    ezmenu.SetLargeIcon(m_bLargeIcons);			
    
    ezmenu.SetExtensionColor(::GetSysColor(/*COLOR_HIGHLIGHT*/COLOR_BTNSHADOW  ));
    CSize szIcon=m_bLargeIcons?CSize(32,32):CSize(16,16);
    
    int ic=0;
    
    for(int i=0;i<col; ++i)
    {
        LPEZMENUITEMDATA  lpez=new CEZMenuItemData;
        char Buff[100];
        if ( i==2  || i==6 ) lpez->bSeperator=true; else
        {
            lpez->hItemIconLarge=(HICON)LoadImage(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_ICON1+ic),IMAGE_ICON,szIcon.cx,szIcon.cy,LR_DEFAULTCOLOR);
            lpez->hItemIconSmall=(HICON)LoadImage(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_ICON1+ic),IMAGE_ICON,szIcon.cx,szIcon.cy,LR_DEFAULTCOLOR);
            LoadString(AfxGetInstanceHandle(),IDS_STRING20+ic,Buff,100);
            lpez->strItemText=Buff;									
            ++ic;
        }	                                       
        ezmenu.AppendOwnerDrawnItem(100+i,lpez);
    }			
    DWORD x = this->GetSel();
    bool en = (LOWORD(x) == HIWORD(x));
    bool op = maindlg3()->wnd.isOpened();
    
    ezmenu.EnableMenuItem(0,MF_BYPOSITION  | ( MF_DISABLED && en) );
    ezmenu.EnableMenuItem(1,MF_BYPOSITION  | ( (!op || en) ? MF_DISABLED : 0));
    ezmenu.EnableMenuItem(2,MF_BYPOSITION  | ( MF_DISABLED ) );			
    ezmenu.EnableMenuItem(4,MF_BYPOSITION  | ( (!op) ? MF_DISABLED : 0 ) );			
    ezmenu.EnableMenuItem(6,MF_BYPOSITION  | ( MF_DISABLED ) );			
    ezmenu.EnableMenuItem(7,MF_BYPOSITION  | ( (!op || en) ? MF_DISABLED : 0 ) );
    ezmenu.EnableMenuItem(8,MF_BYPOSITION  | ( (!op || en) ? MF_DISABLED :0 ) );
    ezmenu.EnableMenuItem(5,MF_BYPOSITION  | ( (!op ) ? MF_DISABLED :0 ) );		
    
    CPoint mouse;
    ::GetCursorPos(&mouse);
    this->SetFocus();
    ezmenu.TrackPopupMenu(TPM_RIGHTALIGN,mouse.x+50,mouse.y-20,this);
    
}
