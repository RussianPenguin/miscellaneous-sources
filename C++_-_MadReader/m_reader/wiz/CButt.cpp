// CoolButton.cpp : implementation file
//

#include "stdafx.h"
#include "CButt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCoolButton

CCoolButton::CCoolButton()

{	
        bHighlight = bLBtnDown = false;
        //hHand = AfxGetApp()->LoadCursor(IDC_HANDCUR);
}

CCoolButton::~CCoolButton()
{
    
}


BEGIN_MESSAGE_MAP(CCoolButton, CButton)
        //{{AFX_MSG_MAP(CCoolButton)
        ON_WM_MOUSEMOVE()
        ON_WM_TIMER()
        ON_WM_LBUTTONUP()
        ON_WM_LBUTTONDOWN()
        ON_WM_ERASEBKGND()
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCoolButton message handlers

void CCoolButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
    CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);    
    CRect rect(lpDrawItemStruct->rcItem);    
    UINT state = lpDrawItemStruct->itemState;           

    
    
    if (state & ODS_DISABLED)
    {
        pDC->Draw3dRect(rect,GetSysColor(COLOR_3DSHADOW), GetSysColor(COLOR_3DHILIGHT));        
    }
    else
    {    if (state & ODS_SELECTED)
            {
                pDC->Draw3dRect(rect,GetSysColor(COLOR_3DSHADOW), GetSysColor(COLOR_3DHILIGHT));
            }
            else
            {
                pDC->Draw3dRect(rect,GetSysColor(COLOR_3DHILIGHT),GetSysColor(COLOR_3DSHADOW));
            }
        rect.DeflateRect(3,3);
        //DrawFrameControl(pDC->m_hDC,rect,DFC_SCROLL	,DFCS_SCROLLDOWN	);
        //pDC->FillSolidRect(rect,cl);
        CBrush *pBr = new CBrush(cl);		
        CBrush *pBrOld = pDC->SelectObject(pBr);

        pDC->Rectangle(rect);

        pDC->SelectObject(pBrOld);
    }


    /*else
    {
        if (bHighlight)
        {
            if (state & ODS_SELECTED)
            {
                pDC->Draw3dRect(rect,GetSysColor(COLOR_3DSHADOW), GetSysColor(COLOR_3DHILIGHT));
            }
            else
            {
                pDC->Draw3dRect(rect,GetSysColor(COLOR_3DHILIGHT),GetSysColor(COLOR_3DSHADOW));
            }
        }
    }*/
}

void CCoolButton::OnMouseMove(UINT nFlags, CPoint point)
{
     //   SetTimer(1,10,NULL);

        CButton::OnMouseMove(nFlags, point);
}


void CCoolButton::OnTimer(UINT nIDEvent)
{
    /*    static bool pPainted = false;
        POINT pt;
        GetCursorPos(&pt);
        CRect rect;
        GetWindowRect (rect);
        if (bLBtnDown)
        {
                KillTimer (1);
                if (pPainted) InvalidateRect (NULL);
                pPainted = FALSE;
                return;
        }

        if (!rect.PtInRect (pt))
        {
                bHighlight = false;
                KillTimer (1);

                if (pPainted)
                        InvalidateRect(NULL);

                pPainted = false;
                return;
        }
        else
        {
                bHighlight = true;
                if (!pPainted)
                {
                        pPainted = true;
                        InvalidateRect(NULL);
                }
        }*/

        CButton::OnTimer(nIDEvent);
}

void CCoolButton::OnLButtonUp(UINT nFlags, CPoint point)
{
        bLBtnDown = false;
  //      if (bHighlight)
        {
                bHighlight = false;
                InvalidateRect(NULL);
        }
        CButton::OnLButtonUp(nFlags, point);
}

void CCoolButton::OnLButtonDown(UINT nFlags, CPoint point)
{
        bLBtnDown = true;
        CButton::OnLButtonDown(nFlags, point);
}



BOOL CCoolButton::PreCreateWindow(CREATESTRUCT& cs)
{
        cs.style |= BS_OWNERDRAW;
        return CButton::PreCreateWindow(cs);
}

BOOL CCoolButton::OnEraseBkgnd(CDC* pDC)
{     
        CRect rc;
        GetClientRect(rc);      
        
		//pDC->FillSolidRect(rc, cl);	
        pDC->FillSolidRect(rc, GetSysColor(COLOR_BTNFACE));	
        return true;
}

void CCoolButton::SetColor(COLORREF &c)
{	
	cl = c;
	Invalidate(true);
}
