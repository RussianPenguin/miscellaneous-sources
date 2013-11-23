//*************************************************************************
// CMenuEx.cpp : implementation file
// Version : 2.3
// Date : June 22, 1998
// Author : Brent Corkum
// 
// Portions of code supplied by:
// Ben Ashley,Girish Bharadwaj,Jean-Edouard Lachand-Robert,
// Robert Edward Caldecott,Kenny Goers,Leonardo Zide,
// Stefan Kuhr
//
// Bug Fixes:
// Stefan Kuhr,Martin Vladic,Kim Yoo Chul
//
// You are free to use/modify this code but leave this header intact.
//

#include "stdafx.h"        // Standard windows header file
#include "resource.h"        // Standard windows header file
#include "MenuEx.h"        // CMenuEx class declaration
#include <afxpriv.h>       //SK: makes A2W and other spiffy AFX macros work
#ifdef ASK_APP_DRAW
#include "WinAppEx.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define GAP 1
#ifndef OBM_CHECK
#define OBM_CHECK 32760 // from winuser.h
#endif

#if _MFC_VER <0x400
#error This code does not work on Versions of MFC prior to 4.0
#endif

/////////////////////////////////////////////////////////////////////////////
// CMenuEx
IMPLEMENT_DYNAMIC( CMenuEx, CMenu );

static CPINFO CPInfo;

enum Win32Type{
Win32s,
Windoze95,
WinNT3,
WinNT4orHigher
};


Win32Type IsShellType()
{
  Win32Type  ShellType;
  DWORD winVer;
  OSVERSIONINFO *osvi;

  winVer=GetVersion();
  if(winVer<0x80000000){/*NT */
    ShellType=WinNT3;
    osvi= (OSVERSIONINFO *)malloc(sizeof(OSVERSIONINFO));
    if (osvi!=NULL){
      memset(osvi,0,sizeof(OSVERSIONINFO));
      osvi->dwOSVersionInfoSize=sizeof(OSVERSIONINFO);
      GetVersionEx(osvi);
      if (osvi->dwMajorVersion>=4L)
        ShellType=WinNT4orHigher;//yup, it is NT 4 or higher!
      free(osvi);
    }
  }
  else if  (LOBYTE(LOWORD(winVer))<4)
    ShellType=Win32s;/*Win32s*/
  else
    ShellType=Windoze95;/*Windoze95*/
  return ShellType;
}

static Win32Type g_Shell=IsShellType();

void CMenuExData::SetAnsiString(LPCSTR szAnsiString)
{
ASSERT(szAnsiString);
USES_CONVERSION;
SetWideString(A2W(szAnsiString));  //SK:  see MFC Tech Note 059
}

CString CMenuExData::GetString(void)//returns the menu text in ANSI or UNICODE
//depending on the MFC-Version we are using
{
CString strText;
if (m_szMenuText)
    {
#ifdef UNICODE
    strText = m_szMenuText;
#else
USES_CONVERSION;
    strText=W2A(m_szMenuText);     //SK:  see MFC Tech Note 059
#endif    
    }
return strText;
}


/*
 
===============================================================================
  CMenuEx::CMenuEx()
  TCMeny::~CMenuEx()
  -----------------

  Constructor and Destructor.
 
===============================================================================
*/

CMenuEx::CMenuEx(BOOL bDrawGrayed, BOOL bShowLastArrow)
{
  m_bDrawOnlyGray=FALSE;
  disable_old_style=FALSE;
  m_bEnableArrows=bShowLastArrow;
  m_iconX = 16;            // Icon sizes default to 16 x 16
  m_iconY = 15;            // ...
  m_selectcheck = -1;
  m_unselectcheck = -1;
  checkmaps=NULL;
  checkmapsshare=FALSE;
  // set the color used for the transparent background in all bitmaps
  m_bitmapBackground=RGB(192,192,192); //gray
  m_bitmapBackgroundFlag=FALSE;
  GetCPInfo(CP_ACP,&CPInfo);
  hGlobal=NULL;
  COLORREF m_clrBack=GetSysColor(COLOR_MENU);
  m_clrHlt=GetSysColor(COLOR_3DHIGHLIGHT);
  DWORD rr,gg,bb;
  rr=((m_clrBack&0xff)+(m_clrHlt&0xff))>>1;
  gg=(((m_clrBack>>8)&0xff)+((m_clrHlt>>8)&0xff))>>1;
  bb=(((m_clrBack>>16)&0xff)+((m_clrHlt>>16)&0xff))>>1;
  m_clrHlt=rr+(gg<<8)+(bb<<16);
  m_bShowLastArrow=bShowLastArrow;
  m_bDrawGrayed=bDrawGrayed;
}

CMenuEx::~CMenuEx()
{
  DestroyMenu();
}

BOOL CMenuEx::IsNewShell ()
{
return (Windoze95==g_Shell || WinNT4orHigher==g_Shell);
}


CMenuExData::~CMenuExData()
{
  if(bitmap)
    delete(bitmap);

  delete[] m_szMenuText; //Need not check for NULL because ANSI X3J16 allows "delete NULL"
}


void CMenuExData::SetWideString(const wchar_t *szWideString)
{
delete[] m_szMenuText;//Need not check for NULL because ANSI X3J16 allows "delete NULL"

if (szWideString)
    {
    m_szMenuText = new wchar_t[sizeof(wchar_t)*(wcslen(szWideString)+1)];
    if (m_szMenuText)
        wcscpy(m_szMenuText,szWideString);
    }
else
    m_szMenuText=NULL;//set to NULL so we need not bother about dangling non-NULL Ptrs
}

BOOL CMenuEx::IsMenu(CMenu *submenu)
{
  int m;

  int numSubMenus = m_SubMenus.GetUpperBound();
  for(m=0;m<=numSubMenus;++m){
    if(submenu==m_SubMenus[m])return(TRUE);
  }
  return(FALSE);
}

BOOL CMenuEx::DestroyMenu()
{
  // Destroy Sub menus:
  if (!::IsMenu(m_hMenu)) return TRUE;
  int m;
  int numSubMenus = m_SubMenus.GetUpperBound();
  for(m = numSubMenus; m >= 0; m--)delete(m_SubMenus[m]);
  m_SubMenus.RemoveAll();
  // Destroy menu data
  int numItems = m_MenuList.GetUpperBound();
  for(m = 0; m <= numItems; m++)delete(m_MenuList[m]);
  m_MenuList.RemoveAll();
  if(checkmaps&&!checkmapsshare){
    delete checkmaps;
    checkmaps=NULL;
  }
  // Call base-class implementation last:
  return(CMenu::DestroyMenu());
};


///////////////////////////////////////////////////////////////////////////
//
// CMenuEx message handlers


/*
==========================================================================
void CMenuEx::DrawItem(LPDRAWITEMSTRUCT)
---------------------------------------

Called by the framework when a particular item needs to be drawn.  We
overide this to draw the menu item in a custom-fashion, including icons
and the 3D rectangle bar.
==========================================================================
*/

static OFFSET=0;

void CMenuEx::DrawItem (LPDRAWITEMSTRUCT lpDIS)
{
  ASSERT(lpDIS != NULL);
  BOOL grayedflag,lastarrowflag;
  if (lpDIS->rcItem.bottom-lpDIS->rcItem.top==0) 
	  return;
  grayedflag=(((CMenuExData*) (lpDIS->itemData))->nFlagsEx) & MF_DRAWGRAYED;
  int t;
  if((!m_bEnableArrows)&&(((CMenuExData*) (lpDIS->itemData))->nFlags & MF_POPUP))
  {
	  CMenuEx*pMenu=this;
	  t=FindMenuPos((CMenuExData*) (lpDIS->itemData),pMenu);
	  if (t>=0)grayedflag=pMenu->CheckIfGrayed(pMenu->GetSubMenu(t));
  }
  CDC* pDC = CDC::FromHandle(lpDIS->hDC);
  CRect rect;
  CBrush m_brLightBackground;
  m_brLightBackground.CreateSolidBrush(m_clrHlt);
  UINT state = (((CMenuExData*)(lpDIS->itemData))->nFlags);
  if(state & MF_SEPARATOR)
  {
		if(grayedflag && !m_bDrawOnlyGray)
			pDC->FillRect (&(lpDIS->rcItem),&m_brLightBackground);
		rect.CopyRect(&lpDIS->rcItem);
		rect.top+=rect.Height()>>1;
		pDC->DrawEdge(&rect,EDGE_ETCHED,BF_TOP);
  }
  else
  {
	lastarrowflag=(((CMenuExData*)(lpDIS->itemData))->nFlagsEx) & MF_LASTARROW;
	if (lastarrowflag)
	{
	    if((lpDIS->itemState&ODS_SELECTED)&&(!m_bDrawOnlyGray))
		{
			CRect rect=lpDIS->rcItem;
			int k=(rect.bottom-rect.top-12)>>1;
			if (k<0) k=0;
			rect.top+=k;
			rect.bottom-=k;
			pDC->FillRect (rect,&m_brLightBackground);
			pDC->Draw3dRect (rect,GetSysColor(COLOR_3DHIGHLIGHT),GetSysColor(COLOR_3DSHADOW));
	    }
		else
		{
			CBrush m_brSelect;
			m_brSelect.CreateSolidBrush(GetSysColor(COLOR_MENU));

			pDC->FillRect (&lpDIS->rcItem,&m_brSelect);
			m_brSelect.DeleteObject();
	    }
		const int width=5,height=8;
	    COLORREF crText;
			crText = GetSysColor(COLOR_MENUTEXT);
		int x,y;
		x=(lpDIS->rcItem.left>>1)+((lpDIS->rcItem.right-width)>>1);
		y=(lpDIS->rcItem.top>>1)+((lpDIS->rcItem.bottom-height)>>1);
		DrawLastArrow(pDC,x,y,crText);
		m_brLightBackground.DeleteObject();
		return;
	}
    CRect rect2;
    BOOL standardflag=FALSE,selectedflag=FALSE,disableflag=FALSE;
    BOOL checkflag=FALSE;
    CBitmap bitmapstandard;
    COLORREF crText = GetSysColor(COLOR_MENUTEXT);
    COLORREF m_clrBack=GetSysColor(COLOR_MENU);
    CBrush m_brBackground,m_brSelect;
    CPen m_penBack;
    int x0,y0,dy;
    int nIconNormal=-1,xoffset=-1;
    CImageList *bitmap=NULL;
    CFont m_fontMenu;
    LOGFONT m_lf;

    // set some colors and the font
    m_penBack.CreatePen (PS_SOLID,0,GetSysColor(COLOR_MENU));
    m_brBackground.CreateSolidBrush(GetSysColor(COLOR_MENU));
    m_brSelect.CreateSolidBrush(GetSysColor(COLOR_HIGHLIGHT));
    ZeroMemory ((PVOID) &m_lf,sizeof (LOGFONT));
    NONCLIENTMETRICS nm;
    nm.cbSize = sizeof (NONCLIENTMETRICS);
    VERIFY (SystemParametersInfo(SPI_GETNONCLIENTMETRICS,nm.cbSize,&nm,0)); 
    m_lf =  nm.lfMenuFont;
    m_fontMenu.CreateFontIndirect (&m_lf);

    // draw the colored rectangle portion
  
    rect.CopyRect(&lpDIS->rcItem);
    rect2=rect;
 
    // draw the up/down/focused/disabled state

    UINT action = lpDIS->itemAction;
    UINT state = lpDIS->itemState;
    CString strText;
    LOGFONT lf;
    lf = m_lf;

    CFont dispFont;
    CFont *pFont;
      
    if(lpDIS->itemData != NULL){
      nIconNormal = (((CMenuExData*)(lpDIS->itemData))->menuIconNormal);
      xoffset = (((CMenuExData*)(lpDIS->itemData))->xoffset);
      bitmap = (((CMenuExData*)(lpDIS->itemData))->bitmap);
      strText = ((CMenuExData*) (lpDIS->itemData))->GetString();
    
      if(state&ODS_CHECKED && nIconNormal<0){
        if(state&ODS_SELECTED && m_selectcheck>0)checkflag=TRUE;
        else if(m_unselectcheck>0) checkflag=TRUE;
      }
      else if(nIconNormal != -1){
        standardflag=TRUE;
        if(state&ODS_SELECTED && !(state&ODS_GRAYED))selectedflag=TRUE;
        else if(state&ODS_GRAYED) disableflag=TRUE;
      }
    }
    else{
      strText.Empty();
    }

    if(state&ODS_SELECTED){ // draw the down edges

      CPen *pOldPen = pDC->SelectObject (&m_penBack);

      // You need only Text highlight and thats what you get
     
      if(checkflag||standardflag||selectedflag||disableflag||state&ODS_CHECKED)
        rect2.SetRect(rect.left+m_iconX+4+GAP,rect.top,rect.right,rect.bottom);
      pDC->FillRect (rect2,&m_brSelect);

      pDC->SelectObject (pOldPen);
      if((HFONT)dispFont != NULL)dispFont.DeleteObject ();
      dispFont.CreateFontIndirect (&lf);
      crText = GetSysColor(COLOR_HIGHLIGHTTEXT);
    }
    else 
	{
      CPen *pOldPen = pDC->SelectObject (&m_penBack);
	  if(grayedflag && !m_bDrawOnlyGray)
		pDC->FillRect (rect,&m_brLightBackground);
	  else
		pDC->FillRect (rect,&m_brBackground);
      pDC->SelectObject (pOldPen);

      // draw the up edges

	  if(grayedflag && !m_bDrawOnlyGray)
			pDC->Draw3dRect (rect,m_clrHlt,m_clrHlt);
	  else
			pDC->Draw3dRect (rect,m_clrBack,m_clrBack);
      if ((HFONT)dispFont != NULL) dispFont.DeleteObject ();
      dispFont.CreateFontIndirect (&lf); //Normal
    }

    // draw the text if there is any
    //We have to paint the text only if the image is nonexistant

    dy = (rect.Height()-4-m_iconY)/2;
    dy = dy<0 ? 0 : dy;

    if(checkflag||standardflag||selectedflag||disableflag)
	{
      rect2.SetRect(rect.left+1,rect.top+1+dy,rect.left+m_iconX+3,
                    rect.top+m_iconY+3+dy);
	  if(grayedflag && !m_bDrawOnlyGray)
			pDC->Draw3dRect (rect2,m_clrHlt,m_clrHlt);
	  else
			pDC->Draw3dRect (rect2,m_clrBack,m_clrBack);
      if(checkflag && checkmaps)
	  {
		if(grayedflag && !m_bDrawOnlyGray)
          pDC->FillRect (rect2,&m_brLightBackground);
	    else
		  pDC->FillRect (rect2,&m_brBackground);
        rect2.SetRect(rect.left,rect.top+dy,rect.left+m_iconX+4,
                      rect.top+m_iconY+4+dy);
        
		if(grayedflag && !m_bDrawOnlyGray)
			pDC->Draw3dRect (rect2,m_clrHlt,m_clrHlt);
		else
			pDC->Draw3dRect (rect2,m_clrBack,m_clrBack);
        CPoint ptImage(rect.left+2,rect.top+2+dy);
       
        if(state&ODS_SELECTED)checkmaps->Draw(pDC,1,ptImage,ILD_TRANSPARENT);
        else checkmaps->Draw(pDC,0,ptImage,ILD_TRANSPARENT);
      }
      else if(disableflag)
	  {
        if(!selectedflag)
		{
          HBITMAP hbmp=LoadSysColorBitmap(nIconNormal);
          if(hbmp)
		  {
            bitmapstandard.Attach(hbmp);
            rect2.SetRect(rect.left,rect.top+dy,rect.left+m_iconX+4,
                          rect.top+m_iconY+4+dy);
			if(grayedflag && !m_bDrawOnlyGray)
				pDC->Draw3dRect (rect2,m_clrHlt,m_clrHlt);
			else
				pDC->Draw3dRect (rect2,m_clrBack,m_clrBack);
            if(disable_old_style)
              DitherBlt(lpDIS->hDC,rect.left+2,rect.top+2+dy,m_iconX,m_iconY,
                       (HBITMAP)(bitmapstandard),xoffset*m_iconX,0);
            else
              DitherBlt2(pDC,rect.left+2,rect.top+2+dy,m_iconX,m_iconY,
                         bitmapstandard,xoffset*m_iconX,0);
            bitmapstandard.DeleteObject();
          }
        }
      }
      else if(selectedflag)
	  {
		if(grayedflag && !m_bDrawOnlyGray)
			pDC->FillRect (rect2,&m_brLightBackground);
		else
			pDC->FillRect (rect2,&m_brBackground);
        rect2.SetRect(rect.left,rect.top+dy,rect.left+m_iconX+4,
                      rect.top+m_iconY+4+dy);
        if (IsNewShell())
		{
          if(state&ODS_CHECKED)
            pDC->Draw3dRect(rect2,GetSysColor(COLOR_3DSHADOW),
                            GetSysColor(COLOR_3DHILIGHT));
          else
            pDC->Draw3dRect(rect2,GetSysColor(COLOR_3DHILIGHT),
                            GetSysColor(COLOR_3DSHADOW));
        }
        CPoint ptImage(rect.left+2,rect.top+2+dy);
        if(bitmap)bitmap->Draw(pDC,xoffset,ptImage,ILD_TRANSPARENT);
      }
      else
	  {
        if(state&ODS_CHECKED)
		{
          CBrush brush;
          COLORREF col =GetSysColor(COLOR_3DLIGHT);
          brush.CreateSolidBrush(col);
          pDC->FillRect(rect2,&brush);
          brush.DeleteObject();
          rect2.SetRect(rect.left,rect.top+dy,rect.left+m_iconX+4,
                        rect.top+m_iconY+4+dy);
          if (IsNewShell())
            pDC->Draw3dRect(rect2,GetSysColor(COLOR_3DSHADOW),
                            GetSysColor(COLOR_3DHILIGHT));
        }
        else
		{
		  if(grayedflag && !m_bDrawOnlyGray)
            pDC->FillRect (rect2,&m_brLightBackground);
		  else
            pDC->FillRect (rect2,&m_brBackground);
          rect2.SetRect(rect.left,rect.top+dy,rect.left+m_iconX+4,
                        rect.top+m_iconY+4+dy);
		  if(grayedflag && !m_bDrawOnlyGray)
			pDC->Draw3dRect (rect2,m_clrHlt,m_clrHlt);
		  else
			pDC->Draw3dRect (rect2,m_clrBack,m_clrBack);
        }
        CPoint ptImage(rect.left+2,rect.top+2+dy);
        if(bitmap)bitmap->Draw(pDC,xoffset,ptImage,ILD_TRANSPARENT);
      }
    }
    if(nIconNormal<0 && state&ODS_CHECKED && !checkflag)
	{
      rect2.SetRect(rect.left+1,rect.top+2+dy,rect.left+m_iconX+1,
                    rect.top+m_iconY+2+dy);
      CMenuItemInfo info;
      info.fMask = MIIM_CHECKMARKS;
      ::GetMenuItemInfo((HMENU)lpDIS->hwndItem,lpDIS->itemID,
                      MF_BYCOMMAND, &info);
      if(state&ODS_CHECKED || info.hbmpUnchecked) 
	  {
        /*Draw3DCheckmark(pDC, rect2, state&ODS_SELECTED,
                        state&ODS_CHECKED ? info.hbmpChecked :
                        info.hbmpUnchecked);*/
		if(grayedflag && !m_bDrawOnlyGray)
          Draw3DCheckmark2(pDC, rect2, state&ODS_SELECTED,&m_brLightBackground,
                        state&ODS_CHECKED ? info.hbmpChecked :
                        info.hbmpUnchecked);
		else
          Draw3DCheckmark2(pDC, rect2, state&ODS_SELECTED,&m_brBackground,
                        state&ODS_CHECKED ? info.hbmpChecked :
                        info.hbmpUnchecked);
      }
    }

    //This is needed always so that we can have the space for check marks

    x0=rect.left;y0=rect.top;
    rect.left = rect.left + m_iconX + 8 + GAP; 

    if(!strText.IsEmpty())
	{
      CRect rectt(rect.left,rect.top-1,rect.right,rect.bottom-1);

      //   Find tabs

      CString leftStr,rightStr;
      leftStr.Empty();rightStr.Empty();
      int tablocr=strText.ReverseFind(_T('\t'));
      if(tablocr!=-1)
	  {
        rightStr=strText.Mid(tablocr+1);
        leftStr=strText.Left(strText.Find(_T('\t')));
        rectt.right-=m_iconX;
      }
      else leftStr=strText;

      int iOldMode = pDC->GetBkMode();
      pDC->SetBkMode( TRANSPARENT);

      // Draw the text in the correct colour:

      UINT nFormat  = DT_LEFT|DT_SINGLELINE|DT_VCENTER;
      UINT nFormatr = DT_RIGHT|DT_SINGLELINE|DT_VCENTER;
      if(!(lpDIS->itemState & ODS_GRAYED))
	  {
        pDC->SetTextColor(crText);
        pDC->DrawText (leftStr,rectt,nFormat);
        if(tablocr!=-1) pDC->DrawText (rightStr,rectt,nFormatr);
      }
      else
	  {
        // Draw the disabled text
        if(!(state & ODS_SELECTED))
		{
          RECT offset = *rectt;
          offset.left+=1;
          offset.right+=1;
          offset.top+=1;
          offset.bottom+=1;
          pDC->SetTextColor(GetSysColor(COLOR_BTNHILIGHT));
          pDC->DrawText(leftStr,&offset, nFormat);
          if(tablocr!=-1) pDC->DrawText (rightStr,&offset,nFormatr);
          pDC->SetTextColor(GetSysColor(COLOR_GRAYTEXT));
          pDC->DrawText(leftStr,rectt, nFormat);
          if(tablocr!=-1) pDC->DrawText (rightStr,rectt,nFormatr);
        }
        else
		{
        // And the standard Grey text:
          pDC->SetTextColor(m_clrBack);
          pDC->DrawText(leftStr,rectt, nFormat);
          if(tablocr!=-1) pDC->DrawText (rightStr,rectt,nFormatr);
        }
      }
      pFont = pDC->SelectObject (&dispFont);
      pDC->SetBkMode( iOldMode );
      pDC->SelectObject (pFont); //set it to the old font
    }

    m_penBack.DeleteObject();
    m_brBackground.DeleteObject();
    m_fontMenu.DeleteObject();
    m_brSelect.DeleteObject();
    dispFont.DeleteObject ();
  }
  m_brLightBackground.DeleteObject();
}


/*
==========================================================================
void CMenuEx::MeasureItem(LPMEASUREITEMSTRUCT)
---------------------------------------------

Called by the framework when it wants to know what the width and height
of our item will be.  To accomplish this we provide the width of the
icon plus the width of the menu text, and then the height of the icon.
 
==========================================================================
*/

void CMenuEx::MeasureItem( LPMEASUREITEMSTRUCT lpMIS )
{
  UINT state = (((CMenuExData*)(lpMIS->itemData))->nFlags);
  UINT grayed= (((CMenuExData*)(lpMIS->itemData))->nFlagsEx) & MF_DRAWGRAYED;
  UINT larrow= (((CMenuExData*)(lpMIS->itemData))->nFlagsEx) & MF_LASTARROW;
  /*if ((!m_bEnableArrows) && (state & MF_POPUP))
  {
	  CMenuEx* pMenu=this;
	  int t=FindMenuPos((CMenuExData*) (lpMIS->itemData),pMenu);
	  if (t>=0)grayed=CheckIfGrayed(pMenu->GetSubMenu(t));
  }*/
  if (larrow)
  {
	  if(m_bDrawGrayed || !m_bShowLastArrow)
	  {
		lpMIS->itemWidth = 0;
		lpMIS->itemHeight = 0;
		return;
	  }
  }
#ifdef ASK_APP_DRAW
  CWinAppEx* app=(CWinAppEx*)AfxGetApp();
  ASSERT(app->IsKindOf(RUNTIME_CLASS(CWinAppEx)));
  if (grayed && !app->CheckForGrayedMenuPaint())
#else
  if (grayed && !m_bDrawGrayed) 
#endif
  {
    lpMIS->itemWidth = 0;
    lpMIS->itemHeight = 0;
	return;
  }
  if(state & MF_SEPARATOR && !((((CMenuExData*)(lpMIS->itemData))->nFlagsEx) & MF_LASTARROW))
  {
    lpMIS->itemWidth = 0;
    lpMIS->itemHeight = GetSystemMetrics(SM_CYMENU)>>1;
  }
  else{
    CFont m_fontMenu;
    LOGFONT m_lf;
    ZeroMemory ((PVOID) &m_lf,sizeof (LOGFONT));
    NONCLIENTMETRICS nm;
    nm.cbSize = sizeof (NONCLIENTMETRICS);
    VERIFY(SystemParametersInfo(SPI_GETNONCLIENTMETRICS,
           nm.cbSize,&nm,0)); 
    m_lf =  nm.lfMenuFont;
    m_fontMenu.CreateFontIndirect (&m_lf);

    // Obtain the width of the text:
    CWnd *pWnd = AfxGetMainWnd();            // Get main window
    CDC *pDC = pWnd->GetDC();              // Get device context
    CFont* pFont;    // Select menu font in...
    
    if (IsNewShell())
        pFont = pDC->SelectObject (&m_fontMenu);// Select menu font in...
        
    //Get pointer to text SK
    const wchar_t *lpstrText = ((CMenuExData*)(lpMIS->itemData))->GetWideString();//SK: we use const to prevent misuse
    
        
    SIZE size;

    if (Win32s!=g_Shell)
      VERIFY(::GetTextExtentPoint32W(pDC->m_hDC,lpstrText,
             wcslen(lpstrText),&size)); //SK should also work on 95
#ifndef UNICODE //can't be UNICODE for Win32s
    else{//it's Win32suckx
      RECT rect;
      rect.left=rect.top=0;
      size.cy=DrawText(pDC->m_hDC,(LPCTSTR)lpstrText,
                       wcslen(lpstrText),&rect,
                       DT_SINGLELINE|DT_LEFT|DT_VCENTER|DT_CALCRECT);
      //+3 makes at least three pixels space to the menu border
      size.cx=rect.right-rect.left+3;
      size.cx += 3*(size.cx/wcslen(lpstrText));
    }
#endif    

    CSize t = CSize(size);
    if(IsNewShell())
      pDC->SelectObject (pFont);  // Select old font in
    AfxGetMainWnd()->ReleaseDC(pDC);  // Release the DC

    // Set width and height:

    lpMIS->itemWidth = m_iconX + t.cx + m_iconX + GAP;
    int temp = GetSystemMetrics(SM_CYMENU);
    lpMIS->itemHeight = temp>m_iconY+4 ? temp : m_iconY+4;
    m_fontMenu.DeleteObject();
  }
}

void CMenuEx::SetIconSize (int width, int height)
{
  m_iconX = width;
  m_iconY = height;
}

BOOL CMenuEx::AppendODMenuA(LPCSTR lpstrText,UINT nFlags,UINT nID,
                           int nIconNormal,int nFlagsEx)
{
	CHAR chr='\0';
	if (!lpstrText)lpstrText=&chr;
	USES_CONVERSION;
	return AppendODMenuW(A2W(lpstrText),nFlags,nID,nIconNormal,nFlagsEx);//SK: See MFC Tech Note 059
}


BOOL CMenuEx::AppendODMenuW(wchar_t *lpstrText,UINT nFlags,UINT nID,
                           int nIconNormal,int nFlagsEx)
{
  // Add the MF_OWNERDRAW flag if not specified:
  WCHAR chr='\0';
  if (!lpstrText)lpstrText=&chr;
  if(!nID)nFlags=MF_SEPARATOR|MF_OWNERDRAW;
  
  nFlags |= MF_OWNERDRAW;

  CMenuExData *mdata = new CMenuExData;
  m_MenuList.Add(mdata);
  mdata->SetWideString(lpstrText);    //SK: modified for dynamic allocation
  
  mdata->menuIconNormal = nIconNormal;
  mdata->xoffset=-1;
  if(nIconNormal>=0){
    mdata->xoffset=0;
    LoadFromToolBar(nID,nIconNormal,mdata->xoffset);
    if(mdata->bitmap)mdata->bitmap->DeleteImageList();
    else mdata->bitmap=new(CImageList);
    mdata->bitmap->Create(m_iconX,m_iconY,ILC_COLORDDB|ILC_MASK,1,1);
    AddBitmapToImageList(mdata->bitmap,nIconNormal);
  }
  mdata->nFlags = nFlags;
  mdata->nFlagsEx=nFlagsEx;
  mdata->nID = nID;
  return(CMenu::AppendMenu(nFlags, nID, (LPCTSTR)mdata));
}


BOOL CMenuEx::ModifyODMenuA(const char * lpstrText,UINT nID,int nIconNormal, int nFlagsEx)
{
USES_CONVERSION;
return ModifyODMenuW(A2W(lpstrText),nID,nIconNormal,nFlagsEx);//SK: see MFC Tech Note 059
}

BOOL CMenuEx::ModifyODMenuW(wchar_t *lpstrText,UINT nID,int nIconNormal, int nFlagsEx)
{
  int nLoc;
  CMenuExData *mdata;

  // Find the old CMenuExData structure:
  CMenuEx *psubmenu = FindMenuOption(nID,nLoc);
  if(psubmenu && nLoc>=0)
	  mdata = psubmenu->m_MenuList[nLoc];
  else{
  // Create a new CMenuExData structure:
    mdata = new CMenuExData;
    m_MenuList.Add(mdata);
  }
  ASSERT(mdata);
  if(lpstrText)
     mdata->SetWideString(lpstrText);  //SK: modified for dynamic allocation
  mdata->menuIconNormal = nIconNormal;
  mdata->xoffset=-1;
  if(nIconNormal>=0){
    mdata->xoffset=0;
    LoadFromToolBar(nID,nIconNormal,mdata->xoffset);
    if(mdata->bitmap)mdata->bitmap->DeleteImageList();
    else mdata->bitmap=new(CImageList);
    mdata->bitmap->Create(m_iconX,m_iconY,ILC_COLORDDB|ILC_MASK,1,1);
    AddBitmapToImageList(mdata->bitmap,nIconNormal);
  }
  mdata->nFlags = MF_BYCOMMAND | MF_OWNERDRAW;
  mdata->nID = nID;
  if(nFlagsEx>=0) mdata->nFlagsEx=nFlagsEx;
  return (CMenu::ModifyMenu(nID,mdata->nFlags,nID,(LPCTSTR)mdata));
}


BOOL CMenuEx::ModifyODMenuA(const char *lpstrText,const char *OptionText,
                           int nIconNormal, int nFlagsEx)
{
USES_CONVERSION;
return ModifyODMenuW(A2W(lpstrText),A2W(OptionText),nIconNormal,nFlagsEx);//SK: see MFC  Tech Note 059
}


BOOL CMenuEx::ModifyODMenuW(wchar_t *lpstrText,wchar_t *OptionText,
                           int nIconNormal, int nFlagsEx)
{
  CMenuExData *mdata;

  // Find the old CMenuExData structure:
  mdata=FindMenuOption(OptionText);
  if(mdata){
    if(nFlagsEx>=0) mdata->nFlagsEx=nFlagsEx;
    if(lpstrText)
        mdata->SetWideString(lpstrText);//SK: modified for dynamic allocation
    mdata->menuIconNormal = nIconNormal;
    mdata->xoffset=-1;
    if(nIconNormal>=0){
      mdata->xoffset=0;
      if(mdata->bitmap)mdata->bitmap->DeleteImageList();
      else mdata->bitmap=new(CImageList);
      mdata->bitmap->Create(m_iconX,m_iconY,ILC_COLORDDB|ILC_MASK,1,1);
      AddBitmapToImageList(mdata->bitmap,nIconNormal);
    }
    return(TRUE);
  }
  return(FALSE);
}

CMenuExData *CMenuEx::NewODMenu(UINT pos,UINT nFlags,UINT nID,CString string)
{
  CMenuExData *mdata;

  mdata = new CMenuExData;
  mdata->menuIconNormal = -1;
  mdata->xoffset=-1;
  #ifdef UNICODE
  mdata->SetWideString((LPCTSTR)string);//SK: modified for dynamic allocation
  #else
  mdata->SetAnsiString(string);
  #endif
  mdata->nFlags = nFlags;
  mdata->nID = nID;
  
  
  if (nFlags&MF_OWNERDRAW){
    ASSERT(!(nFlags&MF_STRING));
    ModifyMenu(pos,nFlags,nID,(LPCTSTR)mdata);
  }
  else if (nFlags&MF_STRING){
    ASSERT(!(nFlags&MF_OWNERDRAW));
    ModifyMenu(pos,nFlags,nID,mdata->GetString());
  }
  else{
    ASSERT(nFlags&MF_SEPARATOR);
    ModifyMenu(pos,nFlags,nID);
  }

  return(mdata);
};

BOOL CMenuEx::LoadToolbars(const UINT *arID,int n)
{
  ASSERT(arID);
  BOOL bRet=TRUE;
  for(int i=0;i<n;++i)
    bRet |= LoadToolbar(arID[i]);
  return(bRet);
}

BOOL CMenuEx::LoadToolbar(UINT nToolBar)
{
  UINT nID;
  BOOL returnflag=FALSE;
  CToolBar bar;

  bar.Create(AfxGetMainWnd());
  if(bar.LoadToolBar(nToolBar)){
    for(int i=0;i<bar.GetCount();++i){
      nID = bar.GetItemID(i); 
      if(nID && GetMenuState(nID, MF_BYCOMMAND)
        !=0xFFFFFFFF)ModifyODMenu(NULL,nID,nToolBar);
    }
    returnflag=TRUE;
  }
  return(returnflag);
}

BOOL CMenuEx::LoadFromToolBar(UINT nID,UINT nToolBar,int& xoffset)
{
  int xset,offset;
  UINT nStyle;
  BOOL returnflag=FALSE;
  CToolBar bar;

  bar.Create(AfxGetMainWnd());
  if(bar.LoadToolBar(nToolBar)){
    offset=bar.CommandToIndex(nID);
    if(offset>=0){
      bar.GetButtonInfo(offset,nID,nStyle,xset);
      if(xset>0)xoffset=xset;
      returnflag=TRUE;
    }
  }
  return(returnflag);
}

CMenuEx *CMenuEx::FindMenuOption(int nId,int& nLoc)
{
  int i;
  CMenuEx *psubmenu,*pgoodmenu;

  for(i=0;i<(int)(CMenu::GetMenuItemCount());++i){
#ifdef _CPPRTTI 
	  psubmenu=dynamic_cast<CMenuEx *>(CMenu::GetSubMenu(i));
#else
    psubmenu=(CMenuEx *)CMenu::GetSubMenu(i);
#endif
    if(psubmenu){
      pgoodmenu=psubmenu->FindMenuOption(nId,nLoc);
      if(pgoodmenu)return(pgoodmenu);
    }
    else if(nId==(int)GetMenuItemID(i)){
      nLoc=i;
      return(this);
    }
  }
  nLoc = -1;
  return(NULL);
}

CMenuExData *CMenuEx::FindMenuOption(wchar_t *lpstrText)
{
  int i;
  CMenuEx *psubmenu;
  CMenuExData *pmenulist;

  for(i=0;i<(int)(CMenu::GetMenuItemCount());++i){
#ifdef _CPPRTTI 
    psubmenu=dynamic_cast<CMenuEx *>(CMenu::GetSubMenu(i));
#else
    psubmenu=(CMenuEx *)CMenu::GetSubMenu(i);
#endif
    if(psubmenu){
      pmenulist=psubmenu->FindMenuOption(lpstrText);
      if(pmenulist)return(pmenulist);
    }
    else{
      const wchar_t *szWide;//SK: we use const to prevent misuse of this Ptr
      for(i=0;i<=m_MenuList.GetUpperBound();++i){     
        szWide = m_MenuList[i]->GetWideString ();
        if(szWide && !wcscmp(lpstrText,szWide))//SK: modified for dynamic allocation
          return(m_MenuList[i]);
      }
    }
  }
  return(NULL);
}


BOOL CMenuEx::LoadMenu(int nResource)
{
  return(CMenuEx::LoadMenu(MAKEINTRESOURCE(nResource)));
};

BOOL CMenuEx::LoadMenu(LPCTSTR lpszResourceName)
{
	//DestroyMenu();
	if(!PreLoadMenu(lpszResourceName)) return FALSE;
	return PostLoadMenu();
}

void CMenuEx::InsertSpaces(void)
{
  int i,j,numitems,maxlength;
  CString string,newstring;
  CSize t;
  CFont m_fontMenu;
  LOGFONT m_lf;

  ZeroMemory ((PVOID) &m_lf,sizeof (LOGFONT));
  NONCLIENTMETRICS nm;
  nm.cbSize = sizeof (NONCLIENTMETRICS);
  VERIFY (SystemParametersInfo (SPI_GETNONCLIENTMETRICS,nm.cbSize,&nm,0)); 
  m_lf =  nm.lfMenuFont;
  m_fontMenu.CreateFontIndirect (&m_lf);

  CWnd *pWnd = AfxGetMainWnd();  
  CDC *pDC = pWnd->GetDC();
  CFont* pFont = pDC->SelectObject (&m_fontMenu);
  
  numitems=CMenu::GetMenuItemCount();
  maxlength = -1;
  for(i=0;i<numitems;++i){
    string=m_MenuList[i]->GetString();
    j=string.Find((char)9);
    newstring.Empty();
    if(j!=-1)newstring.Left(j);
    else newstring=string;
    newstring+=_T(" ");//SK: modified for Unicode correctness. 
    LPCTSTR lpstrText = (LPCTSTR)newstring;
    t=pDC->GetTextExtent(lpstrText,_tcslen(lpstrText));
    if(t.cx>maxlength)maxlength = t.cx;
  }
  for(i=0;i<numitems;++i){
    string=m_MenuList[i]->GetString();

    j=string.Find((char)9);
    if(j!=-1){
      newstring.Empty();
      newstring=string.Left(j);
      LPCTSTR lpstrText = (LPCTSTR)(newstring);
      t=pDC->GetTextExtent(lpstrText,_tcslen(lpstrText));
      while(t.cx<maxlength){
        newstring+=_T(' ');//SK: modified for Unicode correctness
        LPCTSTR lpstrText = (LPCTSTR)(newstring);
        t=pDC->GetTextExtent(lpstrText,_tcslen(lpstrText));
      }
      newstring+=string.Mid(j);
#ifdef UNICODE      
      m_MenuList[i]->SetWideString(newstring);//SK: modified for dynamic allocation
#else
      m_MenuList[i]->SetAnsiString(newstring);
#endif
    }
  }
  pDC->SelectObject (pFont);              // Select old font in
  AfxGetMainWnd()->ReleaseDC(pDC);       // Release the DC
  m_fontMenu.DeleteObject();
}

void CMenuEx::LoadCheckmarkBitmap(int unselect, int select)
{
  if(unselect>=0 && select>=0){
    m_selectcheck=select;
    m_unselectcheck=unselect;
    if(checkmaps)checkmaps->DeleteImageList();
    else checkmaps=new(CImageList);
    checkmaps->Create(m_iconX,m_iconY,TRUE,2,1);
    AddBitmapToImageList(checkmaps,unselect);
    AddBitmapToImageList(checkmaps,select);
  }
}

BOOL CMenuEx::GetMenuText(UINT id, CString& string)
{
  BOOL returnflag=FALSE;

  UINT numMenuItems = m_MenuList.GetUpperBound();
  if(id<=numMenuItems){
    string=m_MenuList[id]->GetString();
    returnflag=TRUE;
  }
  return(returnflag);
}

void CMenuEx::DrawRadioDot(CDC *pDC,int x,int y,COLORREF color)
{
  CRect rcDot(x,y,x+6,y+6);
  CBrush brush;
  CPen pen;
  brush.CreateSolidBrush(color);
  pen.CreatePen(PS_SOLID,0,color);
  pDC->SelectObject(&brush);
  pDC->SelectObject(&pen);
  pDC->Ellipse(&rcDot);
  pen.DeleteObject();
  brush.DeleteObject();
}

void CMenuEx::DrawCheckMark(CDC* pDC,int x,int y,COLORREF color)
{
  pDC->SetPixel(x,y+2,color);
  pDC->SetPixel(x,y+3,color);
  pDC->SetPixel(x,y+4,color);

  pDC->SetPixel(x+1,y+3,color);
  pDC->SetPixel(x+1,y+4,color);
  pDC->SetPixel(x+1,y+5,color);

  pDC->SetPixel(x+2,y+4,color);
  pDC->SetPixel(x+2,y+5,color);
  pDC->SetPixel(x+2,y+6,color);

  pDC->SetPixel(x+3,y+3,color);
  pDC->SetPixel(x+3,y+4,color);
  pDC->SetPixel(x+3,y+5,color);

  pDC->SetPixel(x+4,y+2,color);
  pDC->SetPixel(x+4,y+3,color);
  pDC->SetPixel(x+4,y+4,color);

  pDC->SetPixel(x+5,y+1,color);
  pDC->SetPixel(x+5,y+2,color);
  pDC->SetPixel(x+5,y+3,color);

  pDC->SetPixel(x+6,y,color);
  pDC->SetPixel(x+6,y+1,color);
  pDC->SetPixel(x+6,y+2,color);
}

CMenuExData *CMenuEx::FindMenuList(UINT nID)
{
  for(int i=0;i<=m_MenuList.GetUpperBound();++i){
    if((UINT)m_MenuList[i]->nID==nID && !m_MenuList[i]->syncflag){
      m_MenuList[i]->syncflag=1;
      return(m_MenuList[i]);
    }
  }
  return(NULL);
}

void CMenuEx::InitializeMenuList(int value)
{
  for(int i=0;i<=m_MenuList.GetUpperBound();++i)
    m_MenuList[i]->syncflag=value;
}

void CMenuEx::DeleteMenuList(void)
{
  for(int i=0;i<=m_MenuList.GetUpperBound();++i){
    if(!m_MenuList[i]->syncflag){
      delete m_MenuList[i];
    }
  }
}

void CMenuEx::SynchronizeMenu(void)
{
  CTypedPtrArray<CPtrArray, CMenuExData*> temp;
  CMenuExData *mdata;
  CString string;
  UINT submenu,nID,state,j;

  InitializeMenuList(0);
  for(j=0;j<CMenu::GetMenuItemCount();++j){
    mdata=NULL;
    state=GetMenuState(j,MF_BYPOSITION);
    if(state&MF_POPUP){
      submenu=(UINT)CMenu::GetSubMenu(j)->m_hMenu;
      mdata=FindMenuList(submenu);
      GetMenuString(j,string,MF_BYPOSITION);
      if(!mdata)mdata=NewODMenu(j,
        state|MF_BYPOSITION|MF_POPUP|MF_OWNERDRAW,submenu,string);
      else if(string.GetLength()>0)
#ifdef UNICODE
        mdata->SetWideString(string);  //SK: modified for dynamic allocation
#else
        mdata->SetAnsiString(string);
#endif
    }
    else if(state&MF_SEPARATOR){
      mdata=FindMenuList(0);
      if(!mdata)mdata=NewODMenu(j,
        state|MF_BYPOSITION|MF_SEPARATOR|MF_OWNERDRAW,0,_T(""));//SK: modified for Unicode correctness
      else ModifyMenu(j,mdata->nFlags,nID,(LPCTSTR)mdata);
    }
    else{
      nID=GetMenuItemID(j);
      mdata=FindMenuList(nID);
      GetMenuString(j,string,MF_BYPOSITION);
      if(!mdata)mdata=NewODMenu(j,state|MF_BYPOSITION|MF_OWNERDRAW,
        nID,string);
      else{
        mdata->nFlags=state|MF_BYPOSITION|MF_OWNERDRAW;
        if(string.GetLength()>0)
#ifdef UNICODE
		    mdata->SetWideString(string);//SK: modified for dynamic allocation
#else
            mdata->SetAnsiString(string);
#endif
            
        ModifyMenu(j,mdata->nFlags,nID,(LPCTSTR)mdata);
      }
    }
    if(mdata)temp.Add(mdata);
  }
  DeleteMenuList();
  m_MenuList.RemoveAll();
  m_MenuList.Append(temp);
  temp.RemoveAll(); 
}

void CMenuEx::UpdateMenu(CMenu *pmenu)
{
#ifdef _CPPRTTI 
  CMenuEx *psubmenu = dynamic_cast<CMenuEx *>(pmenu);
#else
  CMenuEx *psubmenu = (CMenuEx *)pmenu;
#endif
  if(psubmenu)psubmenu->SynchronizeMenu();
}

LRESULT CMenuEx::FindKeyboardShortcut(UINT nChar, UINT nFlags,
                                     CMenu *pMenu)
{
#ifdef _CPPRTTI 
  CMenuEx *pCMenuEx = dynamic_cast<CMenuEx *>(pMenu);
#else
  CMenuEx *pCMenuEx = (CMenuEx *)pMenu;
#endif
  if(pCMenuEx && nFlags&MF_POPUP){
    CString key(_T('&'),2);//SK: modified for Unicode correctness
	key.SetAt(1,(TCHAR)nChar);
	key.MakeLower();
    CString menutext;
    int menusize = (int)pCMenuEx->CMenu::GetMenuItemCount();
    if(menusize!=(pCMenuEx->m_MenuList.GetUpperBound()+1))
      pCMenuEx->SynchronizeMenu();
    for(int i=0;i<menusize;++i){
      if(pCMenuEx->GetMenuText(i,menutext)){
        menutext.MakeLower();
        if(menutext.Find(key)>=0)return(MAKELRESULT(i,2));
      }
    }
  }
  return(0);
}

void CMenuEx::DitherBlt (HDC hdcDest, int nXDest, int nYDest, int nWidth, 
                        int nHeight, HBITMAP hbm, int nXSrc, int nYSrc)
{
  ASSERT(hdcDest && hbm);
  ASSERT(nWidth > 0 && nHeight > 0);
  
  // Create a generic DC for all BitBlts
  HDC hDC = CreateCompatibleDC(hdcDest);
  ASSERT(hDC);
  
  if (hDC)
  {
    // Create a DC for the monochrome DIB section
    HDC bwDC = CreateCompatibleDC(hDC);
    ASSERT(bwDC);
    
    if (bwDC)
    {
      // Create the monochrome DIB section with a black and white palette
      struct {
        BITMAPINFOHEADER bmiHeader; 
        RGBQUAD      bmiColors[2]; 
      } RGBBWBITMAPINFO = {
        
        {    // a BITMAPINFOHEADER
          sizeof(BITMAPINFOHEADER),  // biSize 
            nWidth,         // biWidth; 
            nHeight,        // biHeight; 
            1,            // biPlanes; 
            1,            // biBitCount 
            BI_RGB,         // biCompression; 
            0,            // biSizeImage; 
            0,            // biXPelsPerMeter; 
            0,            // biYPelsPerMeter; 
            0,            // biClrUsed; 
            0            // biClrImportant; 
        },    
        {
          { 0x00, 0x00, 0x00, 0x00 }, { 0xFF, 0xFF, 0xFF, 0x00 }
        } 
      };
      VOID *pbitsBW;
      HBITMAP hbmBW = CreateDIBSection(bwDC,
        (LPBITMAPINFO)&RGBBWBITMAPINFO, DIB_RGB_COLORS, &pbitsBW, NULL, 0);
      ASSERT(hbmBW);
      
      if (hbmBW)
      {
        // Attach the monochrome DIB section and the bitmap to the DCs
        HBITMAP olddib = (HBITMAP)SelectObject(bwDC, hbmBW);
        SelectObject(hDC, hbm);
        
        // BitBlt the bitmap into the monochrome DIB section
        BitBlt(bwDC, 0, 0, nWidth, nHeight, hDC, nXSrc, nYSrc, SRCCOPY);
        
        // Paint the destination rectangle in gray
        FillRect(hdcDest, CRect(nXDest, nYDest, nXDest + nWidth, nYDest +
			nHeight), GetSysColorBrush((IsNewShell())?COLOR_3DFACE:COLOR_MENU));
		            //SK: looks better on the old shell
        // BitBlt the black bits in the monochrome bitmap into COLOR_3DHILIGHT
        // bits in the destination DC
        // The magic ROP comes from the Charles Petzold's book
        HBRUSH hb = CreateSolidBrush(GetSysColor(COLOR_3DHILIGHT));
        HBRUSH oldBrush = (HBRUSH)SelectObject(hdcDest, hb);
        BitBlt(hdcDest,nXDest+1,nYDest+1,nWidth,nHeight,bwDC,0,0,0xB8074A);
        
        // BitBlt the black bits in the monochrome bitmap into COLOR_3DSHADOW
        // bits in the destination DC
        hb = CreateSolidBrush(GetSysColor(COLOR_3DSHADOW));
        DeleteObject(SelectObject(hdcDest, hb));
        BitBlt(hdcDest, nXDest, nYDest, nWidth, nHeight,bwDC,0,0,0xB8074A);
        DeleteObject(SelectObject(hdcDest, oldBrush));
        VERIFY(DeleteObject(SelectObject(bwDC, olddib)));
      }
      
      VERIFY(DeleteDC(bwDC));
    }
    
    VERIFY(DeleteDC(hDC));
  }
}

int CMenuEx::AddBitmapToImageList(CImageList *bmplist,UINT nResourceID)
{
  int bReturn;

  HBITMAP hbmp=LoadSysColorBitmap(nResourceID);
  if(hbmp){
    CBitmap bmp;
    bmp.Attach(hbmp);
    if(m_bitmapBackgroundFlag) bReturn=bmplist->Add(&bmp,m_bitmapBackground);
    else bReturn=bmplist->Add(&bmp,GetSysColor(COLOR_3DFACE));
    bmp.Detach();
    DeleteObject(hbmp);
  }
  else bReturn = -1;
  return(bReturn);
}

void CMenuEx::SetBitmapBackground(COLORREF color)
{
  m_bitmapBackground=color;
  m_bitmapBackgroundFlag=TRUE;
}

void CMenuEx::UnSetBitmapBackground(void)
{
  m_bitmapBackgroundFlag=FALSE;
}

// Given a toolbar, append all the options from it to this menu
// Passed a ptr to the toolbar object and the toolbar ID
// Author : Robert Edward Caldecott
void CMenuEx::AddFromToolBar(CToolBar* pToolBar, int nResourceID)
{
  for (int i = 0; i < pToolBar->GetCount(); i++) {
    UINT nID = pToolBar->GetItemID(i);
    // See if this toolbar option
    // appears as a command on this
    // menu or is a separator
    if (nID == 0 || GetMenuState(nID, MF_BYCOMMAND) == 0xFFFFFFFF)
      continue; // Item doesn't exist
    UINT nStyle;
    int nImage;
    // Get the toolbar button info
    pToolBar->GetButtonInfo(i, nID, nStyle, nImage);
    // OK, we have the command ID of the toolbar
    // option, and the tollbar bitmap offset
    int nLoc;
    CMenuExData* pData;
    CMenuEx *pSubMenu = FindMenuOption(nID, nLoc);
    if (pSubMenu && nLoc >= 0)pData = pSubMenu->m_MenuList[nLoc];
    else {
      // Create a new CMenuExData structure
      pData = new CMenuExData;
      m_MenuList.Add(pData);
    }
    // Set some default structure members
    pData->menuIconNormal = nResourceID;
    pData->nID = nID;
    pData->nFlags =  MF_BYCOMMAND | MF_OWNERDRAW;
    pData->xoffset = nImage;
    if (pData->bitmap)pData->bitmap->DeleteImageList();
    else pData->bitmap = new CImageList;
    pData->bitmap->Create(m_iconX, m_iconY,ILC_COLORDDB|ILC_MASK, 1, 1);
    AddBitmapToImageList(pData->bitmap, nResourceID);
    // Modify our menu
    ModifyMenu(nID,pData->nFlags,nID,(LPCTSTR)pData);
  }
}

BOOL CMenuEx::Draw3DCheckmark(CDC *dc, const CRect& rc,
                             BOOL bSelected, HBITMAP hbmCheck)
{
  CRect rcDest = rc;
  CBrush brush;
  COLORREF col=GetSysColor((bSelected||!IsNewShell())?COLOR_MENU:COLOR_3DLIGHT);//SK: Looks better on the old shell
  brush.CreateSolidBrush(col);
  dc->FillRect(rcDest,&brush);
  brush.DeleteObject();
  if (IsNewShell()) //SK: looks better on the old shell
    dc->DrawEdge(&rcDest, BDR_SUNKENOUTER, BF_RECT);
  if (!hbmCheck)DrawCheckMark(dc,rc.left+4,rc.top+4,GetSysColor(COLOR_MENUTEXT));
  else DrawRadioDot(dc,rc.left+5,rc.top+4,GetSysColor(COLOR_MENUTEXT));
  return TRUE;
}

BOOL CMenuEx::Draw3DCheckmark2(CDC *dc, const CRect& rc,
                             BOOL bSelected, CBrush* pBrush, HBITMAP hbmCheck)
{
  CRect rcDest = rc;
  if (!pBrush)
  {
	CBrush brush;
	COLORREF col=GetSysColor((bSelected||!IsNewShell())?COLOR_MENU:COLOR_3DLIGHT);//SK: Looks better on the old shell
	brush.CreateSolidBrush(col);
	dc->FillRect(rcDest,&brush);
	brush.DeleteObject();
  }
  else
  {
	dc->FillRect(rcDest,pBrush);
  }
  if (IsNewShell()) //SK: looks better on the old shell
    dc->DrawEdge(&rcDest, BDR_SUNKENOUTER, BF_RECT);
  if (!hbmCheck)DrawCheckMark(dc,rc.left+4,rc.top+4,GetSysColor(COLOR_MENUTEXT));
  else DrawRadioDot(dc,rc.left+5,rc.top+4,GetSysColor(COLOR_MENUTEXT));
  return TRUE;
}

void CMenuEx::DitherBlt2(CDC *drawdc, int nXDest, int nYDest, int nWidth, 
                        int nHeight, CBitmap &bmp, int nXSrc, int nYSrc)
{
	// create a monochrome memory DC
	CDC ddc;
	ddc.CreateCompatibleDC(0);
  CBitmap bwbmp;
	bwbmp.CreateCompatibleBitmap(&ddc, nWidth, nHeight);
	CBitmap * pddcOldBmp = ddc.SelectObject(&bwbmp);

  CDC dc;
	dc.CreateCompatibleDC(0);
  CBitmap * pdcOldBmp = dc.SelectObject(&bmp);
	
	// build a mask
	ddc.PatBlt(0, 0, nWidth, nHeight, WHITENESS);
	dc.SetBkColor(GetSysColor(COLOR_BTNFACE));
	ddc.BitBlt(0, 0, nWidth, nHeight, &dc, nXSrc,nYSrc, SRCCOPY);
	dc.SetBkColor(GetSysColor(COLOR_BTNHILIGHT));
	ddc.BitBlt(0, 0, nWidth, nHeight, &dc, nXSrc,nYSrc, SRCPAINT);

	// Copy the image from the toolbar into the memory DC
	// and draw it (grayed) back into the toolbar.
	dc.FillSolidRect(0,0, nWidth, nHeight, GetSysColor((IsNewShell())?COLOR_3DFACE:COLOR_MENU));
        //SK: Looks better on the old shell
	dc.SetBkColor(RGB(0, 0, 0));
	dc.SetTextColor(RGB(255, 255, 255));
	CBrush brShadow, brHilight;
	brHilight.CreateSolidBrush(GetSysColor(COLOR_BTNHILIGHT));
	brShadow.CreateSolidBrush(GetSysColor(COLOR_BTNSHADOW));
	CBrush * pOldBrush = dc.SelectObject(&brHilight);
	dc.BitBlt(0,0, nWidth, nHeight, &ddc, 0, 0, 0x00E20746L);
	drawdc->BitBlt(nXDest+1,nYDest+1,nWidth, nHeight, &dc,0,0,SRCCOPY);
	dc.BitBlt(1,1, nWidth, nHeight, &ddc, 0, 0, 0x00E20746L);
	dc.SelectObject(&brShadow);
	dc.BitBlt(0,0, nWidth, nHeight, &ddc, 0, 0, 0x00E20746L);
	drawdc->BitBlt(nXDest,nYDest,nWidth, nHeight, &dc,0,0,SRCCOPY);
	// reset DCs
	ddc.SelectObject(pddcOldBmp);
	ddc.DeleteDC();
	dc.SelectObject(pOldBrush);
	dc.SelectObject(pdcOldBmp);
	dc.DeleteDC();

	bwbmp.DeleteObject();
}

void CMenuEx::SetDisableOldStyle(void)
{
  disable_old_style=TRUE;
}

void CMenuEx::UnSetDisableOldStyle(void)
{
  disable_old_style=FALSE;
}

BOOL CMenuEx::GetDisableOldStyle(void)
{
  return(disable_old_style);
}


HBITMAP CMenuEx::LoadSysColorBitmap(int nResourceId)
{
  HINSTANCE hInst = 
    AfxFindResourceHandle(MAKEINTRESOURCE(nResourceId),RT_BITMAP);
  HRSRC hRsrc = 
    ::FindResource(hInst,MAKEINTRESOURCE(nResourceId),RT_BITMAP);
	if (hRsrc == NULL)
		return NULL;
	return AfxLoadSysColorBitmap(hInst, hRsrc, FALSE);
}


//*************************************************************************

BOOL CMenuEx::PreLoadMenu(LPCTSTR lpszResourceName)
{
  TRACE(_T(
    "IMPORTANT:Use CMenuEx::DestroyMenu to destroy Loaded Menu's\n"));
  ASSERT_VALID(this);
  ASSERT(lpszResourceName != NULL);

  // Find the Menu Resource:
  HINSTANCE m_hInst = AfxFindResourceHandle(lpszResourceName,RT_MENU);
  HRSRC hRsrc = ::FindResource(m_hInst,lpszResourceName,RT_MENU);
  if(hRsrc == NULL)return FALSE;

  // Get size of resource:

  DWORD dwSize = SizeofResource(NULL, hRsrc);

  // Load the Menu Resource:

  hGlobal = LoadResource(m_hInst, hRsrc);
  if(hGlobal == NULL)return FALSE;

  // Attempt to create us as a menu...

  if(!CMenu::CreateMenu())return FALSE;
  return TRUE;
}

BOOL CMenuEx::PostLoadMenu()
{
  ASSERT(hGlobal!=NULL);
  // Get Item template Header, and calculate offset of MENUITEMTEMPLATES

  MENUITEMTEMPLATEHEADER *pTpHdr=
    (MENUITEMTEMPLATEHEADER*)LockResource(hGlobal);
  BYTE* pTp=(BYTE*)pTpHdr + 
    (sizeof(MENUITEMTEMPLATEHEADER) + pTpHdr->offset);

  // Variables needed during processing of Menu Item Templates:

  int j=0;
  CMenuExData*  pData = NULL;              // New OD Menu Item Data
  WORD    dwFlags = 0;              // Flags of the Menu Item
  WORD    dwID  = 0;              // ID of the Menu Item
  UINT    uFlags;                  // Actual Flags.
  wchar_t *szCaption=NULL;
  int      nLen   = 0;                // Length of caption
  CTypedPtrArray<CPtrArray, CMenuEx*>  m_Stack;    // Popup menu stack
  CArray<BOOL,BOOL>  m_StackEnd;    // Popup menu stack
  m_Stack.Add(this);                  // Add it to this...
  m_StackEnd.Add(FALSE);

  do
  {
    // Obtain Flags and (if necessary), the ID...
    memcpy(&dwFlags, pTp, sizeof(WORD));pTp+=sizeof(WORD);// Obtain Flags
    if(!(dwFlags & MF_POPUP)) //This menu isn't a POPUP (it hasn't any child)
	{
      memcpy(&dwID, pTp, sizeof(WORD)); // Obtain ID
      pTp+=sizeof(WORD);
    }
    else dwID = 0;

    uFlags = (UINT)dwFlags; // Remove MF_END from the flags that will
    if(uFlags & MF_END) // be passed to the Append(OD)Menu functions.
      uFlags -= MF_END;

    // Obtain Caption (and length)
    nLen = 0;
    char *ch = (char*)pTp;
    szCaption=new wchar_t[wcslen((wchar_t *)pTp)+1];
    wcscpy(szCaption,(wchar_t *)pTp);
    pTp=&pTp[(wcslen((wchar_t *)pTp)+1)*sizeof(wchar_t)];//modified SK
    
    // Handle popup menus first....

    //WideCharToMultiByte
    if(dwFlags & MF_POPUP)
	{
      if(dwFlags & MF_END)
		  m_StackEnd.SetAt(m_Stack.GetUpperBound(),TRUE); 
      CMenuEx* pSubMenu = new CMenuEx(m_bDrawGrayed,m_bShowLastArrow);
      pSubMenu->m_unselectcheck=m_unselectcheck;
      pSubMenu->m_selectcheck=m_selectcheck;
      pSubMenu->checkmaps=checkmaps;
      pSubMenu->checkmapsshare=TRUE;
      pSubMenu->CMenu::CreatePopupMenu();
      // Append it to the top of the stack:

      m_Stack[m_Stack.GetUpperBound()]->AppendODMenuW(szCaption,uFlags,
        (UINT)pSubMenu->m_hMenu, -1);
      m_Stack.Add(pSubMenu);
      m_StackEnd.Add(FALSE);
      m_SubMenus.Add(pSubMenu);
    }
    else 
	{
      m_Stack[m_Stack.GetUpperBound()]->AppendODMenuW(szCaption, uFlags, dwID, -1);
      if(dwFlags & MF_END) m_StackEnd.SetAt(m_Stack.GetUpperBound(),TRUE);
      j = m_Stack.GetUpperBound();
      while(j>=0 && m_StackEnd.GetAt(j))
	  {
        m_Stack[m_Stack.GetUpperBound()]->InsertSpaces();
        m_Stack.RemoveAt(j);
        m_StackEnd.RemoveAt(j);
        --j;
      }
    }
    delete[] szCaption;
  } while(m_Stack.GetUpperBound() != -1);

  for(int i=0;i<(int)CMenu::GetMenuItemCount();++i)
  {
    CString str=m_MenuList[i]->GetString();

    if(CMenu::GetSubMenu(i))
	{
      m_MenuList[i]->nFlags=MF_POPUP|MF_BYPOSITION;
      ModifyMenu(i,MF_POPUP|MF_BYPOSITION,(UINT)CMenu::GetSubMenu(i)->m_hMenu,str);
    }
    else
	{
      m_MenuList[i]->nFlags=MF_STRING|MF_BYPOSITION;
      ModifyMenu(i,MF_STRING|MF_BYPOSITION,m_MenuList[i]->nID,str);
    }
  }
  AppendLastArrow();
  PostBuiltMenu(this);
 
  return(TRUE);
}

BOOL CMenuEx::PreLoadMenu(int nResource)
{
	return(CMenuEx::PreLoadMenu(MAKEINTRESOURCE(nResource)));
}

BOOL CMenuEx::DeleteMenu(UINT nPosition, UINT nFlags)
{
	int n=m_MenuList.GetSize();
	UINT pos=nPosition;
	int i;
	if(nFlags==MF_BYCOMMAND)
	{
		for(i=0;i<n;i++)
			if (GetMenuItemID(i)==(signed)nPosition) {pos=i;break;}
		if(i==n || GetMenuItemID(i)!=(signed)nPosition) return FALSE;
	}
	CMenuExData* pData=m_MenuList.ElementAt(pos);
	delete pData;
	for(i=pos;i<n-1;i++)
		m_MenuList.SetAt(i,m_MenuList.ElementAt(i+1));
	m_MenuList.SetAt(n-1,NULL);
	m_MenuList.SetSize(n-1);
	int j=-1;
	int nSub=-1;
	n=m_SubMenus.GetSize();
	for(i=0;i<n;i++)
	{
		if (m_SubMenus.ElementAt(i)==CMenu::GetSubMenu(pos))
		 {j=i;break;}
	}
	if(j>=0)
	{
		CMenuEx* pMenu=m_SubMenus.ElementAt(j);
		delete pMenu;
		for(i=j;i<n-1;i++)
			m_SubMenus.SetAt(i,m_SubMenus.ElementAt(i+1));
		m_SubMenus.SetAt(n-1,NULL);
		m_SubMenus.SetSize(n-1);
	}
	BOOL b=CMenu::DeleteMenu(nPosition, nFlags);
	return b;
}

CMenuEx* CMenuEx::GetSubMenu(UINT iPos)
{
	CMenuEx* pMenu=(CMenuEx*) CMenu::GetSubMenu(iPos);
	if(pMenu!=NULL) ASSERT(pMenu->IsKindOf(RUNTIME_CLASS(CMenuEx)));
	return pMenu;
}

BOOL CMenuEx::AppendMenu(UINT nFlags, UINT nIDNewItem, LPCTSTR lpszNewItem, UINT nFlagsEx)
{
	nFlags|=MF_OWNERDRAW;
	BOOL bReturn;
	DeleteMenu(m_MenuList.GetSize()-1,MF_BYPOSITION);
	bReturn=AppendODMenu(lpszNewItem,nFlags,nIDNewItem,-1,nFlagsEx);
	AppendLastArrow();
	return bReturn;
}


int CMenuEx::GetFlagsEx(UINT nPos)
{
  CMenuExData* pData=m_MenuList.ElementAt(nPos);
  if (pData)
  {
	return pData->nFlagsEx;
  }
  return 0;
}

int CMenuEx::GetFlags(UINT nPos)
{
  CMenuExData* pData=m_MenuList.ElementAt(nPos);
  if (pData)
  {
	return pData->nFlags;
  }
  return 0;
}

int CMenuEx::GetMenuItemID(UINT nPos)
{
  CMenuExData* pData=m_MenuList.ElementAt(nPos);
  if (pData)
  {
	return pData->nID;
  }
  return 0;
}

BOOL CMenuEx::ModifyODSeparator(UINT nPos, int nFlagsEx)
{
	if (nPos<0) return FALSE;
	CMenuExData* pData=m_MenuList.ElementAt(nPos);
	pData->nFlagsEx=nFlagsEx;
	return TRUE;
}

BOOL CMenuEx::CheckIfGrayed(CMenuEx *pMenu)
{
  int i,n;
  BOOL bGrayed;
  if(!pMenu) return TRUE;
  n=pMenu->m_MenuList.GetSize();
  for (i=0;i<n;i++)
  {
	CMenuExData* pData=pMenu->m_MenuList.ElementAt(i);
	if (pData->nFlags&MF_POPUP)
		bGrayed=CheckIfGrayed(pMenu->GetSubMenu(i));
	else 
		bGrayed=pData->nFlagsEx&MF_DRAWGRAYED;
	if(!bGrayed) return FALSE;
  }
  return TRUE;
}

int CMenuEx::FindMenuPos(CMenuExData *pData,CMenuEx* &pFather)
{
  int p;
  CMenuEx* pTmp;
  for(int i=0;i<=pFather->m_MenuList.GetUpperBound();++i)
  {
    if(pFather->m_MenuList[i]==pData) return i;
	if(pFather->m_MenuList[i]->nFlags&MF_POPUP)
	{
		pTmp=pFather->GetSubMenu(i);
		p=FindMenuPos(pData,pTmp);
		if(p>=0) 
		{
			pFather=pTmp;
			return p;
		}
	}
  }
  return -1;
}

void CMenuEx::PostBuiltMenu(CMenuEx *pMenu)
{
  CMenuEx* pSubMenu;
  for(int i=0;i<(int)pMenu->GetMenuItemCount();++i)
  {
	pSubMenu=pMenu->GetSubMenu(i);
    if(pSubMenu)
	{
	  pSubMenu->m_bShowLastArrow=m_bShowLastArrow;
	  pSubMenu->AppendLastArrow();
	  PostBuiltMenu(pSubMenu);
    }
  }
}

void CMenuEx::DrawLastArrow(CDC *pDC, int x, int y, COLORREF color)
{
  pDC->SetPixel(x,y,color);
  pDC->SetPixel(x+4,y,color);

  pDC->SetPixel(x,y+1,color);
  pDC->SetPixel(x+1,y+1,color);
  pDC->SetPixel(x+3,y+1,color);
  pDC->SetPixel(x+4,y+1,color);

  pDC->SetPixel(x+1,y+2,color);
  pDC->SetPixel(x+2,y+2,color);
  pDC->SetPixel(x+3,y+2,color);

  pDC->SetPixel(x+2,y+3,color);

  pDC->SetPixel(x,y+5,color);
  pDC->SetPixel(x+4,y+5,color);

  pDC->SetPixel(x,y+6,color);
  pDC->SetPixel(x+1,y+6,color);
  pDC->SetPixel(x+3,y+6,color);
  pDC->SetPixel(x+4,y+6,color);

  pDC->SetPixel(x+1,y+7,color);
  pDC->SetPixel(x+2,y+7,color);
  pDC->SetPixel(x+3,y+7,color);

  pDC->SetPixel(x+2,y+8,color);
}

BOOL CMenuEx::CreateMenu()
{
  BOOL m_bReturn=CMenu::CreateMenu();
  return m_bReturn;
}

BOOL CMenuEx::CreatePopupMenu()
{
  BOOL bReturn=CMenu::CreatePopupMenu();
  AppendLastArrow();
  return bReturn;
}

BOOL CMenuEx::ModifyFlagsEx(int nID, int nFlagsEx, BOOL byPos)
{
  int nLoc;
  CMenuExData *mdata;

  CMenuEx *psubmenu;
  if (byPos)
  {
	  nLoc=nID;
	  psubmenu=this;
  }
  else
  {
	  // Find the old CMenuExData structure:
	  psubmenu = FindMenuOption(nID,nLoc);
  }
  if(psubmenu && nLoc>=0)
	  mdata = psubmenu->m_MenuList[nLoc];
  else{
  // Create a new CMenuExData structure:
    mdata = new CMenuExData;
    m_MenuList.Add(mdata);
  }
  ASSERT(mdata);
  mdata->nFlags = MF_BYCOMMAND | MF_OWNERDRAW;
  mdata->nID = nID;
  if(nFlagsEx>=0) mdata->nFlagsEx=nFlagsEx;
  return (CMenu::ModifyMenu(nID,mdata->nFlags,nID,(LPCTSTR)mdata));
}

LRESULT CMenuEx::TrapWindowProc(UINT nMsg, WPARAM wParam, LPARAM lParam)
{
	return TRUE;
}

void CMenuEx::EnableGrayedDraw(BOOL bEnable, BOOL bForce)
{
	if (!m_bEnableArrows) return;
	if (!bForce)
		if(m_bDrawGrayed==bEnable) return;
	m_bDrawGrayed=bEnable;
	if(m_bDrawGrayed)
	{
		RemoveLastArrows(this);
	}
	else
	{
		InsertLastArrows(this);
	}
}

void CMenuEx::RemoveLastArrows(CMenuEx *pMenu)
{
	CMenuExData* pData;
	m_bShowLastArrow=FALSE;
	if(!pMenu) return;
	pMenu->m_bDrawGrayed=m_bDrawGrayed;
	pMenu->m_bDrawOnlyGray=m_bDrawOnlyGray;
	int i,m,n;
	n=((CMenu*)pMenu)->GetMenuItemCount();
	m=n-1;
	UINT fex=pMenu->GetFlagsEx(m);
	if (fex&MF_LASTARROW)
	{
		pMenu->DeleteMenu(m, MF_BYPOSITION);
		pMenu->AppendLastArrow();
	}
	else
	{
		pMenu->SetFlagsEx(m, MF_LASTARROW|MF_DRAWGRAYED|0xFFFF);
	}
	for(i=0;i<n;i++)
	{
		pData=pMenu->m_MenuList[i];
		CMenu* ptMenu=((CMenu*)pMenu)->CMenu::GetSubMenu(i);
		if (!ptMenu)
		{
			::DeleteMenu(pMenu->m_hMenu,i, MF_BYPOSITION);
			::InsertMenu(pMenu->m_hMenu,i, MF_BYPOSITION|pData->nFlags|MF_OWNERDRAW,pData->nID,(LPCTSTR) pData);
		}
		else
		{
			RemoveLastArrows((CMenuEx*)ptMenu);
			HMENU hMenu=ptMenu->m_hMenu;
			::RemoveMenu(pMenu->m_hMenu,i, MF_BYPOSITION);
			::InsertMenu(pMenu->m_hMenu,i, MF_BYPOSITION|MF_POPUP|MF_OWNERDRAW,(UINT)hMenu,(LPCTSTR) pData);
		}
	}
}

void CMenuEx::InsertLastArrows(CMenuEx *pMenu)
{
	CMenuExData* pData;
	m_bShowLastArrow=TRUE;
	if(!pMenu) return;
	int i;
	UINT pos=((CMenu*)pMenu)->GetMenuItemCount();
	pMenu->m_bDrawGrayed=m_bDrawGrayed;
	pMenu->m_bDrawOnlyGray=m_bDrawOnlyGray;
	UINT fex=pMenu->GetFlagsEx(pos-1);
	if (fex&MF_LASTARROW)
	{
		pMenu->DeleteMenu(pos-1, MF_BYPOSITION);
		pMenu->AppendLastArrow();
	}
	else
	{
		pMenu->AppendLastArrow();
	}
	for(i=(signed)pos-1;i>=0;i--)
	{
		pData=pMenu->m_MenuList[i];
		CMenu* ptMenu=((CMenu*)pMenu)->CMenu::GetSubMenu(i);
		if (!ptMenu)
		{
			::DeleteMenu(pMenu->m_hMenu,i, MF_BYPOSITION);
			::InsertMenu(pMenu->m_hMenu,i, MF_BYPOSITION|pData->nFlags|MF_OWNERDRAW,pData->nID,(LPCTSTR) pData);
		}
		else
		{
			InsertLastArrows(pMenu->GetSubMenu(i));
			HMENU hMenu=ptMenu->m_hMenu;
			::RemoveMenu(pMenu->m_hMenu,i, MF_BYPOSITION);
			::InsertMenu(pMenu->m_hMenu,i, MF_BYPOSITION|MF_POPUP|MF_OWNERDRAW,(UINT)hMenu,(LPCTSTR) pData);
		}
	}
}

int CMenuEx::FindMenuPos(CMenuEx *pMenu, CMenuEx *&pFather)
{
  int p,n;
  CMenuEx* pTmp;
  n=((CMenu*)pFather)->GetMenuItemCount();
  for(int i=0;i<n;++i)
  {
    if(pFather->GetSubMenu(i)==pMenu) 
	{
		return i;
	}
	if(pFather->m_MenuList[i]->nFlags&MF_POPUP)
	{
		pTmp=pFather->GetSubMenu(i);
		p=FindMenuPos(pMenu,pTmp);
		if(p>=0) 
		{
			pFather=pTmp;
			return p;
		}
	}
  }
  return -1;
}

int CMenuEx::SetFlagsEx(UINT nPos,int nFlagsEx)
{
  int r;
  CMenuExData* pData=m_MenuList.ElementAt(nPos);
  if (pData)
  {
	r=pData->nFlagsEx;
	pData->nFlagsEx=nFlagsEx;
  }
  return r;
}

#ifndef ID_SHOWFULL
#define ID_SHOWFULL -1
#endif

BOOL CMenuEx::AppendLastArrow()
{
	return AppendODMenu(_T("----V----"),MF_STRING|MF_OWNERDRAW,ID_SHOWFULL,-1,MF_LASTARROW);
}

void CMenuEx::UpdateGrayedOnly(CMenuEx *pMenu, BOOL b)
{
	pMenu->m_bDrawOnlyGray=b;
	int i,n;
	n=pMenu->GetMenuItemCount();
	for(i=0;i<n;i++)
	{
		CMenuEx* ptMenu=pMenu->GetSubMenu(i);
		if (ptMenu)
		{
			UpdateGrayedOnly(ptMenu,b);
		}
	}
}

void*& CMenuEx::GetExtraDataPtr(UINT nPos)
{
  CMenuExData* pData=m_MenuList.ElementAt(nPos);
  ASSERT (pData!=NULL);
  return pData->m_pExtraData;
}

BOOL CMenuEx::InsertMenu( UINT nPosition, UINT nFlags, UINT nIDNewItem, LPCTSTR lpszNewItem, UINT nFlagsEx)
{
	nFlags|=MF_OWNERDRAW;
	BOOL bReturn;
	DeleteMenu(m_MenuList.GetSize()-1,MF_BYPOSITION);
	// Add the MF_OWNERDRAW flag if not specified:
	if (!lpszNewItem)lpszNewItem=_T("");
	if(!nIDNewItem)nFlags=MF_SEPARATOR|MF_OWNERDRAW;
  
	CMenuExData *mtdata,*mdata2, *mdata = new CMenuExData;
#ifndef UNICODE
	mdata->SetAnsiString(lpszNewItem);    //SK: modified for dynamic allocation
#else
	mdata->SetWideString(lpszNewItem);    //SK: modified for dynamic allocation
#endif
	mdata->menuIconNormal = -1;
	mdata->xoffset=-1;
	mdata->nFlags = nFlags;
	mdata->nFlagsEx=nFlagsEx;
	mdata->nID = nIDNewItem;
	mdata2=mdata;
	m_MenuList.Add(mdata);
	UINT n=m_MenuList.GetSize();
	n--;
	mtdata=m_MenuList[n];
	for (UINT i=nPosition;i<n;i++)
	{
		mdata=m_MenuList[i];
		m_MenuList[i]=mtdata;
		mtdata=mdata;
	}
	m_MenuList[n]=mtdata;
    bReturn=CMenu::InsertMenu(nPosition, nFlags, nIDNewItem, (LPCTSTR)mdata2);
	AppendLastArrow();
	return bReturn;
}
