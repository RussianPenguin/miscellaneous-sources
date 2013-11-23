//////
// EZMenu - Owner drawn menu with Icons & progressbars
// Copyright V.Lakshmi Narasimhan,ezlux@Yahoo.com.
// Feel free to use,modify,twist,turn or even 
// digest the code for any non commercial purposes.
// I would appreciate constructive suggestions & bug reports.
// Please dont delete the above lines.
///////

//Implementation file for owner drawn menu EZMenu
#include "stdafx.h" 
#include "EZMenu.h"
#include "resource.h"

CEZMenu::CEZMenu()
{
	m_bLargeIcons=FALSE;
	m_szBitmapSize=CSize(20,60);
	m_nCount=m_nItems=0;
	m_nAveHeight=16;
	m_clrExtend=RGB(0,0,255);
	CMenu::CMenu();

}



void CEZMenu::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	m_nCount++;
	LPEZMENUITEMDATA lpez=(LPEZMENUITEMDATA)lpDrawItemStruct->itemData;

	CDC* pdc=CDC::FromHandle(lpDrawItemStruct->hDC);

	//lpDrawItemStruct->itemState
	
    if(lpez->bSeperator)
	{
		int nWidth=0;
		if(m_bitmap.m_hObject)
			nWidth+=(m_szBitmapSize.cx+lpDrawItemStruct->rcItem.left);
	    CRect rcSep(lpDrawItemStruct->rcItem);
		rcSep.left+=nWidth;
		pdc->DrawEdge(&rcSep,EDGE_ETCHED,BF_TOP);
		
		return;
	}
	
	// Rects Definition
	CRect rect(lpDrawItemStruct->rcItem);//general
	CRect rcBmp(rect);
	CRect rcIcon(rect);//Icon rect	
	CRect rcText(rect);//Text rect;
	
	//Rects Initialization
	   
	rcBmp.right=rcBmp.left+m_szBitmapSize.cx;
	rcIcon.left=rcBmp.right+2;
	rcIcon.right=rcIcon.left+(m_bLargeIcons?32:16);	
	rcText.left=rcIcon.right+2;
	bool dis = lpDrawItemStruct->itemState & ODS_DISABLED;
	
	//Drawing code	
	
	
	HICON hItemIcon=(m_bLargeIcons?lpez->hItemIconLarge:lpez->hItemIconSmall);
	CSize szIcon=(m_bLargeIcons?CSize(32,32):CSize(16,16));
	
	//Draws the whole thing
	
	if (lpDrawItemStruct->itemAction & ODA_DRAWENTIRE)
	{		
		
		//Draw the Icon
	 int nOldMap=pdc->SetMapMode(MM_TEXT);
	 
	 if(hItemIcon)
		 pdc->DrawState(rcIcon.TopLeft(),szIcon,hItemIcon,DST_ICON|DSS_NORMAL | ( (dis) ? DSS_DISABLED : 0 ) ,(CBrush*)NULL);
	 
	 //Finally draw the text
	 
	    CBrush *pBrush=new CBrush(::GetSysColor(COLOR_BTNFACE));
		pdc->SetMapMode(nOldMap);		
		pdc->FillRect(rcText,pBrush);				
		delete pBrush;
		(dis) ?
			pdc->SetTextColor(::GetSysColor(COLOR_GRAYTEXT)) : pdc->SetTextColor(::GetSysColor(COLOR_MENUTEXT));
		pdc->SetBkColor(::GetSysColor(COLOR_BTNFACE));
		pdc->DrawText(lpez->strItemText,&rcText,DT_LEFT|DT_NOCLIP|DT_SINGLELINE|DT_VCENTER);
		//pdc->set

		//Draw the bitmap at the end
		if(m_nCount==m_nItems)
		{
			m_nCount=0;
			if(m_bitmap.m_hObject)
			{
				CDC memdc;
				memdc.CreateCompatibleDC(pdc);
				memdc.SelectObject(m_bitmap);
				if(m_nAveHeight>m_szBitmapSize.cy)
				{
					int nTop=rect.bottom-m_szBitmapSize.cy;
					pdc->BitBlt(rect.left,nTop,m_szBitmapSize.cx,m_szBitmapSize.cy,&memdc,0,0,SRCCOPY);	   
					pdc->FillSolidRect(rect.left,rect.bottom-m_nAveHeight,m_szBitmapSize.cx,m_nAveHeight-m_szBitmapSize.cy,m_clrExtend);
				}
				else
					pdc->BitBlt(rect.left,rect.bottom-m_nAveHeight,m_szBitmapSize.cx,m_nAveHeight,&memdc,0,0,SRCCOPY );	   
				
				
			}
		}
	}
	
	
	//Draws the selected item
	
	if ((lpDrawItemStruct->itemState & ODS_SELECTED) &&
		(lpDrawItemStruct->itemAction & (ODA_SELECT | ODA_DRAWENTIRE)))
	{	
		CRect iconr(lpDrawItemStruct->rcItem);//Icon rect			    
		CRect textrect(rcText);
		iconr.left=rcIcon.left;		
		if( hItemIcon)
		{
			CRect rcIconHilite(rcIcon);
			rcIconHilite.DeflateRect(-1,-1);			
			if ( !dis) pdc->Draw3dRect(&rcIconHilite,::GetSysColor(COLOR_3DHILIGHT),::GetSysColor(COLOR_3DDKSHADOW));
			iconr.left=textrect.left;       								
		}		
        //Text						
		
		
		
		COLORREF crBgOld=pdc->SetBkColor(::GetSysColor(COLOR_HIGHLIGHT));
		COLORREF crOld=	(dis  ) ?
			pdc->SetTextColor(::GetSysColor(COLOR_GRAYTEXT)) : pdc->SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
		
		CFont* pFont=pdc->GetCurrentFont();
		LOGFONT* pLf=new LOGFONT;
		pFont->GetLogFont(pLf);
		pLf->lfWeight=FW_SEMIBOLD;			
		CFont* pNewFont=new CFont;
		pNewFont->CreateFontIndirect(pLf);		
		pFont=pdc->SelectObject(pNewFont);
		
		CBrush *pBr = new CBrush(PS_SOLID,::GetSysColor(COLOR_HIGHLIGHT));
		CBrush *OldpBr =  pdc->SelectObject( pBr);
    	CPen *pPen = (CPen*) pdc->SelectStockObject(NULL_PEN);			
		pdc->Rectangle(iconr);
		pdc->SelectObject(pPen);
		pdc->SelectObject(OldpBr);		
		
		pdc->DrawText(lpez->strItemText,&textrect,DT_LEFT|DT_NOCLIP|DT_SINGLELINE|DT_VCENTER);
		pdc->SetTextColor(crOld);
		pdc->SetBkColor(crBgOld);
		
		delete pdc->SelectObject(pFont);
		delete pLf;        
	}
	
	
	//Draws the deselected item	
	
	if (!(lpDrawItemStruct->itemState & ODS_SELECTED) &&
		(lpDrawItemStruct->itemAction & ODA_SELECT))
	{		
		if(hItemIcon)
		{
			CRect rcIconHilite(rcIcon);
			rcIconHilite.DeflateRect(-1,-1);			
			pdc->Draw3dRect(&rcIconHilite,::GetSysColor(COLOR_BTNFACE),::GetSysColor(COLOR_BTNFACE));			
		} 

		(dis) ?
			pdc->SetTextColor(::GetSysColor(COLOR_GRAYTEXT)) : pdc->SetTextColor(::GetSysColor(COLOR_MENUTEXT));
		pdc->SetBkColor(::GetSysColor(COLOR_BTNFACE));
		CRect textrect(rcText);
        CBrush *pBrush=new CBrush(::GetSysColor(COLOR_MENU));		
		if  (!hItemIcon) //
		{
			rcIcon.right+=5;
			pdc->FillRect(rcIcon,pBrush);}

		pdc->FillRect(&textrect,pBrush);
		delete pBrush;

		pdc->DrawText(lpez->strItemText,&textrect,DT_LEFT|DT_NOCLIP|DT_SINGLELINE|DT_VCENTER);
		textrect.DeflateRect(-1,2);		
		pdc->Draw3dRect(&textrect,::GetSysColor(COLOR_BTNFACE),::GetSysColor(COLOR_BTNFACE));
		
	}       
	
	
}



void CEZMenu::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{


	LPEZMENUITEMDATA  lpez=(LPEZMENUITEMDATA  )lpMeasureItemStruct->itemData;
	if(lpez->bSeperator) 
	{
		lpMeasureItemStruct->itemHeight=5;
		return;
	}
	CDC* pdc=new CDC;
	pdc->Attach(::GetDC(AfxGetMainWnd()->m_hWnd));
    CSize szText=pdc->GetTextExtent(lpez->strItemText);  
	::ReleaseDC(AfxGetMainWnd()->m_hWnd,pdc->m_hDC);
	delete pdc;
	
	lpMeasureItemStruct->itemWidth=szText.cx+(m_bLargeIcons?32:16)+m_szBitmapSize.cx+8;
	lpMeasureItemStruct->itemHeight=__max(m_bLargeIcons?32:16,szText.cy)+3;
    m_nAveHeight=m_nItems*lpMeasureItemStruct->itemHeight;
      
}
			



CEZMenu::~CEZMenu()
{

	DestroyMenu();
	CMenu::~CMenu();
}


void CEZMenu::SetMenuBitmap(HBITMAP hBitmap)
{
	m_bitmap.Attach(hBitmap);
	

}


void CEZMenu::SetLargeIcon(BOOL bLarge)
{

	m_bLargeIcons=bLarge;
}

void CEZMenu::AppendOwnerDrawnItem(UINT nID, LPEZMENUITEMDATA lpez)
{

	VERIFY(AppendMenu(MF_ENABLED | MF_OWNERDRAW, nID,(LPCTSTR)lpez));

}

void CEZMenu::SetBitmapDimension(CSize sz)
{

	m_szBitmapSize=sz;
}

void CEZMenu::InsertOwnerDrawnMenuItem(UINT nID, LPEZMENUITEMDATA lpez,int nPos)
{

		VERIFY(InsertMenu(nPos,MF_BYPOSITION|MF_ENABLED | MF_OWNERDRAW, nID,(LPCTSTR)lpez));
}

void CEZMenu::SetExtensionColor(COLORREF clrExtend)
{
	m_clrExtend=clrExtend; 

}

void CEZMenu::SetTotalItems(int nItems)
{
	m_nItems=nItems;

}

CEZMenuItemData::CEZMenuItemData()
{
	bChecked=FALSE;
	
    bSeperator=FALSE;
	hItemIconLarge=hItemIconSmall=NULL;	
	strItemText.Empty();
}

void CEZMenu::ModifyOwnerDrawnMenuItem(int nPos, UINT nID, int nTotalCheck,LPEZMENUITEMDATA lpez)
{
    //Iam not sure how to implement this.Suggestions are welcome.    
	//if(GetMenuItemCount()>(UINT)nTotalCheck)?
			VERIFY(ModifyMenu(nPos,MF_BYPOSITION|MF_OWNERDRAW,nID,(LPCTSTR)lpez));
	//else
	//	InsertOwnerDrawnMenuItem(nID,lpez,nPos);
	
}
