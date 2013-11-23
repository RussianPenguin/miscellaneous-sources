/////////////////////////////////////////////////////////////////////////////
//
// Disclaimer Notice
// ------------------
// The Author cannot guarantee this software is error free.
// The author also disclaims all responsibility for damages or 
// loss of profits caused by the failure of this software
//. Your usage of these modifications indicates your willingness to 
// accept complete responsibility.
//
//
// Developed by: Norm Almond for www.codeproject.com 
//
// Please use this software freely, if you fix or make any modifications to
// the software you can let me know so I can improve future versions.
//
// Version 1.00 - First Release 24 Nov 2000
//
/////////////////////////////////////////////////////////////////////////////

// Btn.cpp : implementation file
//

#include "stdafx.h"
#include "CalWnd.h"
#include "CalBtn.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////

CCalBtn::~CCalBtn()
{
}


/////////////////////////////////////////////////////////////////////////////
// CCalBtn message handlers

////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:		CCalBtn::DrawItem
// 
// DESCRIPTION:		Drawing code for date button
// 
// ACCESSIBILTY:	Protected
// 
// MODIFICATIONS:
// Name                  Date       Version    Comments
// N T ALMOND            23NOV200   1.0        Origin
// 
////////////////////////////////////////////////////////////////////////////////
CCalBtn::CCalBtn(CRect& rc, CWnd *pWnd)
{
	Reset();	
	m_pWnd = pWnd;
	m_rcWnd = rc;
	m_bHover = FALSE;
}


////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:		CCalBtn::DrawItem
// 
// DESCRIPTION:		Drawing code for date button
// 
// ACCESSIBILTY:	Protected
// 
// MODIFICATIONS:
// Name                  Date       Version    Comments
// N T ALMOND            23NOV200   1.0        Origin
// 
////////////////////////////////////////////////////////////////////////////////
void CCalBtn::DrawItem(CDC* pDC) 
{

	pDC->SaveDC();
	
	pDC->SetBkMode(TRANSPARENT);

	CRect rc = m_rcWnd;
	CRect rcTemp(rc);
	rc.DeflateRect(1, 0);

	COLORREF crText(GetSysColor(COLOR_GRAYTEXT));

	pDC->SelectObject(GetStockObject(DEFAULT_GUI_FONT));

	// Hi-lited
	if (m_bState)
	{
		// Assume the only selected item
		crText = GetSysColor(COLOR_HIGHLIGHTTEXT);
		pDC->DrawEdge(rc,BDR_SUNKENOUTER,BF_RECT);
		rc.DeflateRect(1,1);

		CBrush br(GetSysColor(COLOR_HIGHLIGHT));
		pDC->FillRect(rc,&br);
		if (!m_strNote.IsEmpty())
		{
			CBrush br(GetSysColor(COLOR_WINDOW));
			rcTemp.DeflateRect(2,2);
			pDC->FrameRect(rcTemp, &br);
		}
	}
	else
	{
		CBrush br(GetSysColor(COLOR_3DFACE));
		pDC->FillRect(rc,&br);

		switch (m_Style)
		{
			case Dimmed:
				if (m_bHover)
					crText = COLOR_WINDOWTEXT;
				break;
				case Recessed: // Fall thru
					pDC->DrawEdge(rc,BDR_SUNKENOUTER,BF_RECT);
				case Normal:
					crText = COLOR_WINDOWTEXT;
				break;

		}

		if (!m_strNote.IsEmpty())
		{
			CBrush br(GetSysColor(COLOR_HIGHLIGHT));
			rcTemp.DeflateRect(1,1);
			pDC->FrameRect(rcTemp, &br);
		}

	}



	// Always draw the text
	pDC->SetTextColor(crText);
	CRect dr(rc);
	dr.DeflateRect(2,0);
	pDC->DrawText(m_strDay,dr,DT_RIGHT|DT_VCENTER|DT_SINGLELINE);
	

	if (m_bFocus)
		pDC->DrawFocusRect(rc);

	pDC->RestoreDC(-1); // Restore last saved context
}

////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:		CCalBtn::Check
// 
// DESCRIPTION:		Check/uncheck button
// 
// ACCESSIBILTY:	Protected
// 
// MODIFICATIONS:
// Name                  Date       Version    Comments
// N T ALMOND            23NOV200   1.0        Origin
// 
////////////////////////////////////////////////////////////////////////////////
void CCalBtn::Check(BOOL bCheck)
{
	m_bState = bCheck;	
	m_pWnd->RedrawWindow(m_rcWnd,NULL,RDW_INVALIDATE | RDW_UPDATENOW); 
}

////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:		CCalBtn::SetState
// 
// DESCRIPTION:		Set button state
// 
// ACCESSIBILTY:	Protected
// 
// MODIFICATIONS:
// Name                  Date       Version    Comments
// N T ALMOND            23NOV200   1.0        Origin
// 
////////////////////////////////////////////////////////////////////////////////
void CCalBtn::SetState(Styles type,COleDateTime tm)
{
	int nDay = tm.GetDay();
	m_strDay.Format(_T("%d"),nDay);
	m_Style = type;
	
	m_pWnd->RedrawWindow(m_rcWnd,NULL,RDW_NOERASE | RDW_INVALIDATE | RDW_UPDATENOW); 
	m_btnTime = tm;
}


////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:		CCalBtn::Focus
// 
// DESCRIPTION:		Draw focus state
// 
// ACCESSIBILTY:	Protected
// 
// MODIFICATIONS:
// Name                  Date       Version    Comments
// N T ALMOND            23NOV200   1.0        Origin
// 
////////////////////////////////////////////////////////////////////////////////
void CCalBtn::Focus()
{
	if (!m_bFocus)
	{
		m_bFocus = TRUE;
		m_pWnd->RedrawWindow(m_rcWnd,NULL,RDW_NOERASE | RDW_INVALIDATE | RDW_UPDATENOW); 
	}
}

////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:		CCalBtn::Unfocus
// 
// DESCRIPTION:		Draw Unfocus state
// 
// ACCESSIBILTY:	Protected
// 
// MODIFICATIONS:
// Name                  Date       Version    Comments
// N T ALMOND            23NOV200   1.0        Origin
// 
////////////////////////////////////////////////////////////////////////////////
void CCalBtn::Unfocus()
{
	m_bFocus = FALSE;
	m_pWnd->RedrawWindow(m_rcWnd,NULL,RDW_NOERASE | RDW_INVALIDATE | RDW_UPDATENOW); 
}

////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:		CCalBtn::Reset
// 
// DESCRIPTION:		Reset buttons status
// 
// ACCESSIBILTY:	Protected
// 
// MODIFICATIONS:
// Name                  Date       Version    Comments
// N T ALMOND            23NOV200   1.0        Origin
// 
////////////////////////////////////////////////////////////////////////////////
void CCalBtn::Reset()
{
	m_bState=FALSE;
	m_Style = Dimmed;
	m_bFocus = FALSE;
}


////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:		CCalBtn::HitTest
// 
// DESCRIPTION:		Returns true if point hit on button
// 
// ACCESSIBILTY:	Protected
// 
// MODIFICATIONS:
// Name                  Date       Version    Comments
// N T ALMOND            23NOV200   1.0        Origin
// 
////////////////////////////////////////////////////////////////////////////////
BOOL CCalBtn::HitTest(CPoint& point)
{
	return m_rcWnd.PtInRect(point);
}

////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:		CCalBtn::GetTipText
// 
// DESCRIPTION:		Returns text for tool tip
// 
// ACCESSIBILTY:	Protected
// 
// MODIFICATIONS:
// Name                  Date       Version    Comments
// N T ALMOND            23NOV200   1.0        Origin
// 
////////////////////////////////////////////////////////////////////////////////
CString CCalBtn::GetTipText()
{
	return m_strNote;
}

////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:		CCalBtn::SetHover
// 
// DESCRIPTION:		Hi-lite dimmed buttons whilst hovering
// 
// ACCESSIBILTY:	Protected
// 
// MODIFICATIONS:
// Name                  Date       Version    Comments
// N T ALMOND            23NOV200   1.0        Origin
// 
////////////////////////////////////////////////////////////////////////////////
void CCalBtn::SetHover(BOOL bHover)
{
	m_bHover = bHover;
	m_pWnd->RedrawWindow(m_rcWnd,NULL,RDW_NOERASE | RDW_INVALIDATE | RDW_UPDATENOW); 
}



////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:		CCalBtn::SetNote
// 
// DESCRIPTION:		Helper function to attach note to date
// 
// ACCESSIBILTY:	public
// 
// MODIFICATIONS:
// Name                  Date       Version    Comments
// N T ALMOND            23NOV200   1.0        Origin
// 
////////////////////////////////////////////////////////////////////////////////
void CCalBtn::SetNote(const CString& strNote)
{
	m_strNote = strNote;
}
