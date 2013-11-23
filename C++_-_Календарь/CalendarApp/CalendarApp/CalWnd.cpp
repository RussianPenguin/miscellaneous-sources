// CalWnd.cpp : implementation file
//

/////////////////////////////////////////////////////////////////////////////
//
// Disclaimer Notice
// ------------------
// The Author cannot guarantee this software is error free.
// The author also disclaims all responsibility for damages or 
// loss of profits caused by the failure of this software.
// Your usage of these modifications indicates your willingness to 
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
#include "stdafx.h"
#include "CalWnd.h"
#include "CalBtn.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Change these at your own peril!!!
const int Pos_Base = 46;	// Window Controls Position
const int Min_Year = 1900;	// Earliest Year
const int Max_Year = 2200;	// Latest Year

/////////////////////////////////////////////////////////////////////////////
// CCalWnd
//

BEGIN_MESSAGE_MAP(CCalWnd, CWnd)
	//{{AFX_MSG_MAP(CCalWnd)
	ON_WM_PAINT()
	ON_WM_CONTEXTMENU()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_NOTIFY(UDN_DELTAPOS, ID_SPINYEAR, OnSpinYear)
	ON_NOTIFY(UDN_DELTAPOS, ID_SPIN_CAL, OnSpinCalendar)
	ON_CBN_SELCHANGE(ID_COMBO_MONTH, OnSelchangeComboMonth)
	ON_COMMAND(IDM_POPUP_TODAY, OnPopupToday)
	ON_COMMAND(IDM_POPUP_SELECTED, OnPopupSelected)
	ON_COMMAND(IDM_POPUP_RESTORE, OnPopupRestore)
	ON_WM_CREATE()
	ON_WM_RBUTTONUP()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
    ON_NOTIFY_EX_RANGE( TTN_NEEDTEXTW, 0, 0xFFFF, OnToolTipText)
    ON_NOTIFY_EX_RANGE( TTN_NEEDTEXTA, 0, 0xFFFF, OnToolTipText)
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
END_MESSAGE_MAP()

////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:		CCalWnd::CCalWnd
// 
// DESCRIPTION:		Constructor
// 
// ACCESSIBILTY:	Public
// 
// MODIFICATIONS:
// Name                  Date       Version    Comments
// N T ALMOND            23NOV200   1.0        Origin
// 
////////////////////////////////////////////////////////////////////////////////
CCalWnd::CCalWnd()
{
	// Load up the spinner controls...
	INITCOMMONCONTROLSEX icc;
	icc.dwSize = sizeof(icc);
	icc.dwICC = ICC_UPDOWN_CLASS;

	InitCommonControlsEx(&icc);

	m_bSpinner = TRUE;
	m_bCapture = FALSE;
	
	m_timeMin = COleDateTime(Min_Year,12,1,0,0,0); // Minimum Date we process
	m_timeMax = COleDateTime(Max_Year,1,31,0,0,0); // Maximum Date we process

	// Default font for this control
	m_Font.Attach(GetStockObject(DEFAULT_GUI_FONT));

	m_nEdge=GetSystemMetrics(SM_CXEDGE);
	m_pbtnSelected = NULL;
	m_pbtnHiLite = NULL;
	m_pbtnCurrent = NULL;

	m_bTrackLeave = FALSE;
	m_bTipInit = FALSE;
}

////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:		CCalWnd::~CCalWnd
// 
// DESCRIPTION:		Constructor
// 
// ACCESSIBILTY:	Public
// 
// MODIFICATIONS:
// Name                  Date       Version    Comments
// N T ALMOND            23NOV200   1.0        Origin
// 
////////////////////////////////////////////////////////////////////////////////
CCalWnd::~CCalWnd()
{
	// Clear up buttons
	while (!m_btnList.IsEmpty())
	{
		CCalBtn* pBtn = m_btnList.GetTail();
		ASSERT(pBtn);
		delete pBtn;
		m_btnList.RemoveTail();

	}

	m_Font.Detach();
}


///////////////////////////////////////////////////////////
//
// Function:	SetDate
//
// Description:	Sets Selected Date
//
// Returns :	TRUE if date was set
//
//
//
///////////////////////////////////////////////////////////
BOOL CCalWnd::SetDate(COleDateTime tm)
{
	// Zeroize timefield
	COleDateTime tmDate = MakeDate(tm);
	m_sTime = tmDate;
	m_cTime = tmDate;

	m_nMonth = m_nYear = 0;
	m_rTime = SyncDate(m_cTime);
	
	SelectMonth(m_rTime);	

	return TRUE;
}

///////////////////////////////////////////////////////////
//
// Function:	GetDate
//
// Description:	Gets Selected Date
//
// Returns :	Selected date
//
//
//
///////////////////////////////////////////////////////////
COleDateTime CCalWnd::GetDate() 
{ 
	return m_cTime; 
}

///////////////////////////////////////////////////////////
//
// Function:	ShowSpinner
//
// Description:	Shows/Hides Date Spinner
//
// Returns :	Bugger All
//
//
//
///////////////////////////////////////////////////////////
void CCalWnd::ShowSpinner(BOOL bShow)
{
	
	if (m_bSpinner != bShow)
	{
		m_bSpinner = bShow;	
		m_btnCalendar.ShowWindow(bShow ? SW_SHOW : SW_HIDE);
		
		CRect rc;
		GetWindowRect(rc);
		
		m_rc.right-=bShow ? -16 : 16;

		SetWindowPos(0,0,0,rc.Width()-(bShow ? -16 : 16),rc.Height(),SWP_NOZORDER | SWP_NOMOVE);
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:		CCalWnd::SelectMonth
// 
// DESCRIPTION:		Select the month
// 
// ACCESSIBILTY:	Protected
// 
// MODIFICATIONS:
// Name                  Date       Version    Comments
// N T ALMOND            23NOV200   1.0        Origin
// 
////////////////////////////////////////////////////////////////////////////////
void CCalWnd::SelectMonth(COleDateTime tm,int nStartDay)
{	
	int nMonth = tm.GetMonth();
	int nYear = tm.GetYear();

	COleDateTime cm = MakeDate();

	COleDateTime fm(nYear,nMonth,nStartDay,0,0,0);
	
	int nOffSet=fm.GetDayOfWeek();
	if (nOffSet==1)
		nOffSet=8;

	nOffSet--; // Offset to correct position

	COleDateTimeSpan ts(nOffSet,0,0,0);
 
	fm -= ts;

	ts = COleDateTimeSpan(1,0,0,0);

	Styles bState;
	BOOL bFlag;

	POSITION pos = m_btnList.GetHeadPosition();
	while (pos)
	{
		CCalBtn* pBtn = m_btnList.GetNext(pos);
		ASSERT(pBtn);

		pBtn->Reset();
		
		if (nMonth != fm.GetMonth())
			bState = Dimmed;
		else
		{
			bState=Normal;
			UpdateControlCaptions(nYear,nMonth);
		}

		if (fm == cm)
			bFlag = TRUE;
		else
			bFlag = FALSE;


		CString strNote;
		m_listNotes.Lookup(fm, strNote);
		pBtn->SetNote(strNote);
		
		
		pBtn->SetState(bFlag ? Recessed : bState, fm);

		if (fm == m_cTime)
		{
			pBtn->Check();
			m_pbtnHiLite = pBtn;
		}

		fm += ts;
	}
}


////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:		CCalWnd::OnPaint
// 
// DESCRIPTION:		Drawing code for calender
// 
// ACCESSIBILTY:	Protected
// 
// MODIFICATIONS:
// Name                  Date       Version    Comments
// N T ALMOND            23NOV200   1.0        Origin
// 
////////////////////////////////////////////////////////////////////////////////
void CCalWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	dc.SetBkMode(TRANSPARENT);
	CFont *pFont = dc.SelectObject(&m_Font);

	// Draw Day divider
	dc.DrawEdge(m_rc,EDGE_ETCHED,BF_TOP);

	CRect rc(0,Pos_Base-m_nCharHeight,m_nCharWidth,Pos_Base);

	// Draw out Day Initials
	// This should be change for international issuess... 
	dc.DrawText(_T("S"),1,rc,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	rc.OffsetRect(m_nCharWidth,0);
	dc.DrawText(_T("M"),1,rc,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	rc.OffsetRect(m_nCharWidth,0);
	dc.DrawText(_T("T"),1,rc,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	rc.OffsetRect(m_nCharWidth,0);
	dc.DrawText(_T("W"),1,rc,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	rc.OffsetRect(m_nCharWidth,0);
	dc.DrawText(_T("T"),1,rc,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	rc.OffsetRect(m_nCharWidth,0);
	dc.DrawText(_T("F"),1,rc,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	rc.OffsetRect(m_nCharWidth,0);
	dc.DrawText(_T("S"),1,rc,DT_CENTER|DT_VCENTER|DT_SINGLELINE);	


	POSITION pos = m_btnList.GetHeadPosition();
	while (pos)
	{
		CCalBtn* pBtn = m_btnList.GetNext(pos);

		ASSERT(pBtn);

		pBtn->DrawItem(&dc);

	}

	dc.SelectObject(pFont);
}



////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:		CCalWnd::SyncDate
// 
// DESCRIPTION:		This returns the first date of the month with the passed
//					in datetime object.
//					IE. cTime = 23/03/99 
//					Return value = 01/03/99
// 
// ACCESSIBILTY:	Protected
// 
// MODIFICATIONS:
// Name                  Date       Version    Comments
// N T ALMOND            23NOV200   1.0        Origin
// 
////////////////////////////////////////////////////////////////////////////////
COleDateTime CCalWnd::SyncDate(COleDateTime& cTime)
{
	return COleDateTime(cTime.GetYear(),cTime.GetMonth(),1,0,0,0);
}

////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:		CCalWnd::UpdateControlCaptions
// 
// DESCRIPTION:		Select captions for the child controls
//					
// ACCESSIBILTY:	Protected
// 
// MODIFICATIONS:
// Name                  Date       Version    Comments
// N T ALMOND            23NOV200   1.0        Origin
// 
////////////////////////////////////////////////////////////////////////////////
void CCalWnd::UpdateControlCaptions(int nYear,int nMonth)
{
	if (nYear != m_nYear)
	{
		m_nYear = nYear;
		CString str;
		str.Format(_T("%04d"), m_nYear);
		m_YearEdit.SetWindowText(str);
	}

	if (nMonth != m_nMonth)
	{
		m_nMonth = nMonth;
		m_cboMonth.SetCurSel(m_nMonth-1);
	}
}

////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:		CCalWnd::ValidateLimits
// 
// DESCRIPTION:		Validate the limits if the passed in datetime object
//					Return true if time ok else false
// 
// ACCESSIBILTY:	Protected
// 
// MODIFICATIONS:
// Name                  Date       Version    Comments
// N T ALMOND            23NOV200   1.0        Origin
// 
////////////////////////////////////////////////////////////////////////////////
BOOL CCalWnd::ValidateLimits(COleDateTime& tm)
{
	BOOL bOk=TRUE;
	
	if (tm < m_timeMin)
	{
		tm = m_timeMin;
		m_nMonth = tm.GetMonth();
		m_cboMonth.SetCurSel(m_nMonth-1);
		bOk=FALSE;
	}

	if (tm > m_timeMax)
	{
		tm = m_timeMax;
		m_nMonth = tm.GetMonth();
		m_cboMonth.SetCurSel(m_nMonth-1);
		bOk=FALSE;
	}
		
	return bOk;
}


////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:		CCalWnd::CreateCombo
// 
// DESCRIPTION:		Create and size Month Combobox
// 
// ACCESSIBILTY:	Bounding rectangle
// 
// MODIFICATIONS:
// Name                  Date       Version    Comments
// N T ALMOND            23NOV200   1.0        Origin
// 
////////////////////////////////////////////////////////////////////////////////
CRect CCalWnd::CreateCombo()
{
	CRect rectCombo;

	GetClientRect(rectCombo);

	rectCombo.SetRect(rectCombo.left + m_nEdge,
		rectCombo.top + 4,
		rectCombo.left + 82,
		rectCombo.bottom);
	
	BOOL bRet = m_cboMonth.Create( CBS_DROPDOWNLIST|WS_CHILD|WS_VISIBLE|WS_TABSTOP|WS_VSCROLL,
		rectCombo,
		this,
		ID_COMBO_MONTH);

	ASSERT(bRet); // Combo creation failed

	// Load up the months...
	COleDateTime date = MakeDate();

	// Load up months
	CString strMonDate;
	for (int n=1; n < 13; n++)
	{
		date.SetDateTime( date.GetYear(), n, 1,0,0,0);
		strMonDate = date.Format(_T("%B"));
		m_cboMonth.AddString(strMonDate);
	}
	
	m_cboMonth.SetFont(&m_Font);
	m_cboMonth.SetCurSel(0);

	// Size combo dropdown window
	int nSize = m_cboMonth.GetItemHeight(1);
	
	m_cboMonth.GetWindowRect(rectCombo);
	ScreenToClient(rectCombo);
	rectCombo.bottom = rectCombo.top+(14 * nSize);
	m_cboMonth.MoveWindow(rectCombo);

	// Alignment for other controls
	m_cboMonth.GetWindowRect(rectCombo);
	ScreenToClient(rectCombo);

	return rectCombo; // Bounding rectangle;
}

////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:		CCalWnd::OnContextMenu
// 
// DESCRIPTION:		Invoke Popup menu
// 
// ACCESSIBILTY:	Protected
// 
// MODIFICATIONS:
// Name                  Date       Version    Comments
// N T ALMOND            23NOV200   1.0        Origin
// 
////////////////////////////////////////////////////////////////////////////////
void CCalWnd::OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/) 
{
	CPoint pt;
	GetCursorPos(&pt);
	m_PopMenu.TrackPopupMenu( TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RIGHTBUTTON, pt.x, pt.y, this);	
}


////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:		CCalWnd::OnLButtonDown
// 
// DESCRIPTION:		Setup processing mouse coords
// 
// ACCESSIBILTY:	Protected
// 
// MODIFICATIONS:
// Name                  Date       Version    Comments
// N T ALMOND            23NOV200   1.0        Origin
// 
////////////////////////////////////////////////////////////////////////////////
void CCalWnd::OnLButtonDown(UINT nFlags, CPoint point) 
{
	
	CWnd::OnLButtonDown(nFlags, point);

	m_bCapture = TRUE;
	SetCapture();

	if (m_pbtnSelected)
		m_pbtnSelected->Unfocus();

	m_pbtnSelected = HitTest(point);
	
	
}


////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:		CCalWnd::HitTest
// 
// DESCRIPTION:		Returns hittested calendar button or NULL
// 
// ACCESSIBILTY:	Protected
// 
// MODIFICATIONS:
// Name                  Date       Version    Comments
// N T ALMOND            23NOV200   1.0        Origin
// 
////////////////////////////////////////////////////////////////////////////////
CCalBtn* CCalWnd::HitTest(CPoint& point)
{
	POSITION pos = m_btnList.GetHeadPosition();
	while (pos)
	{
		CCalBtn* pBtn = m_btnList.GetNext(pos);
		ASSERT(pBtn);
		
		if (pBtn->HitTest(point))
			return pBtn;
	}

	return NULL;
}

////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:		CCalWnd::OnLButtonUp
// 
// DESCRIPTION:		Button selection code
// 
// ACCESSIBILTY:	Protected
// 
// MODIFICATIONS:
// Name                  Date       Version    Comments
// N T ALMOND            23NOV200   1.0        Origin
// 
////////////////////////////////////////////////////////////////////////////////
void CCalWnd::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CWnd::OnLButtonUp(nFlags, point);

	m_bCapture = FALSE;
	ReleaseCapture();

	if (m_pbtnSelected)
	{
		m_pbtnSelected->Unfocus();
		m_pbtnSelected= NULL;
	}

	if (m_pbtnHiLite)
	{
		m_pbtnHiLite->Check( FALSE);
		m_pbtnHiLite = NULL;
	}

	m_pbtnSelected = HitTest(point);

	if (m_pbtnSelected)
	{
	
		// Check for month change
		// ie. Clicked on grayed botton
		m_cTime = m_pbtnSelected->GetDate();
	
		if (ValidateLimits(m_cTime))
		{
			m_rTime = SyncDate(m_cTime);

			m_pbtnSelected->Check( );
			m_pbtnHiLite = m_pbtnSelected;

			if (m_pbtnSelected->GetStyle() == Dimmed)
				SelectMonth(m_cTime);


			// Tell Parent Date has been selected
			// Process WM_DATE_NOTIFY
			// wParam  contains the id of the calendar

			GetParent()->PostMessage( WM_DATE_NOTIFY, GetDlgCtrlID(), 0);

		}
	}

}

////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:		CCalWnd::OnMouseMove
// 
// DESCRIPTION:		Handle drag selection 
// 
// ACCESSIBILTY:	Protected
// 
// MODIFICATIONS:
// Name                  Date       Version    Comments
// N T ALMOND            23NOV200   1.0        Origin
// 
////////////////////////////////////////////////////////////////////////////////
void CCalWnd::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (!m_bTrackLeave) 
	{
		// First time mouse entered my window:
		// request leave notification
		TRACKMOUSEEVENT tme;
		ZeroMemory(&tme, sizeof (tme));

		tme.cbSize = sizeof(tme);
		tme.hwndTrack = m_hWnd;
		tme.dwFlags = TME_LEAVE;
		_TrackMouseEvent(&tme);
		m_bTrackLeave = TRUE;
	}

 

	CCalBtn* pThisBtn = HitTest(point);

	if (pThisBtn)
	{
		if (m_bCapture)
		{
			if (pThisBtn != m_pbtnSelected && m_pbtnSelected != NULL)
			{
				m_pbtnSelected->Unfocus();
				m_pbtnSelected = NULL;
			}

			pThisBtn->Focus();
			m_pbtnSelected = pThisBtn;		
		}
	}

	


	if (pThisBtn != m_pbtnCurrent)
	{
		if (m_pbtnCurrent)
			m_pbtnCurrent->SetHover(FALSE);

		if (pThisBtn)
			pThisBtn->SetHover(TRUE);

		m_pbtnCurrent = pThisBtn;
	}

	CWnd::OnMouseMove(nFlags, point);
}


////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:		CCalWnd::OnSpinYear
// 
// DESCRIPTION:		Called with the year spinner button is pressed
// 
// ACCESSIBILTY:	Protected
// 
// MODIFICATIONS:
// Name                  Date       Version    Comments
// N T ALMOND            23NOV200   1.0        Origin
// 
////////////////////////////////////////////////////////////////////////////////
void CCalWnd::OnSpinYear(NMHDR* pNMHDR, LRESULT* /*pResult*/) 						 
{
	NM_UPDOWN* pUD = (NM_UPDOWN*)pNMHDR;	

	int nYear = m_rTime.GetYear();
	nYear += pUD->iDelta;

	// Year Back
	if (nYear < Min_Year)
	{
		nYear = Min_Year;
		m_rTime = m_timeMin;
	}

	// Year Forward
	if (nYear > Max_Year)
	{
		nYear = Max_Year;
		m_rTime = m_timeMax;
	}

	ValidateLimits(m_rTime);

	m_nYear = 0; // Force Year Set
	m_rTime = COleDateTime(nYear,m_rTime.GetMonth(),m_rTime.GetDay(),0,0,0);
	m_rTime = SyncDate(m_rTime);

	SelectMonth(m_rTime);	
}

////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:		CCalWnd::OnSpinCalendar
// 
// DESCRIPTION:		Called with the calander spinner button is pressed
// 
// ACCESSIBILTY:	Protected
// 
// MODIFICATIONS:
// Name                  Date       Version    Comments
// N T ALMOND            23NOV200   1.0        Origin
// 
////////////////////////////////////////////////////////////////////////////////
void CCalWnd::OnSpinCalendar(NMHDR* pNMHDR, LRESULT* /*pResult*/)
{

	NM_UPDOWN* pUD = (NM_UPDOWN*)pNMHDR;

	COleDateTimeSpan ts(7,0,0,0);

			// Forward
	if (pUD->iDelta>0)
		m_rTime+=ts;
	else	// Back
		m_rTime-=ts;

	ValidateLimits(m_rTime);

	SelectMonth(m_rTime,MulDiv(m_rTime.GetDay(),7,7));	
}

////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:		CCalWnd::OnPopupSelected
// 
// DESCRIPTION:		Goto todays date
// 
// ACCESSIBILTY:	Protected
// 
// MODIFICATIONS:
// Name                  Date       Version    Comments
// N T ALMOND            23NOV200   1.0        Origin
// 
////////////////////////////////////////////////////////////////////////////////
void CCalWnd::OnSelchangeComboMonth()
{
	m_rTime = COleDateTime(m_rTime.GetYear(),m_cboMonth.GetCurSel()+1,1,0,0,0);
	ValidateLimits(m_rTime);
	SelectMonth(m_rTime);
}

////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:		CCalWnd::OnPopupSelected
// 
// DESCRIPTION:		Goto todays date
// 
// ACCESSIBILTY:	Protected
// 
// MODIFICATIONS:
// Name                  Date       Version    Comments
// N T ALMOND            23NOV200   1.0        Origin
// 
////////////////////////////////////////////////////////////////////////////////
void CCalWnd::OnPopupToday()
{
	m_rTime = MakeDate();
	m_rTime = SyncDate(m_rTime);				
	ValidateLimits(m_rTime);
	SelectMonth(m_rTime);
}

////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:		CCalWnd::OnPopupSelected
// 
// DESCRIPTION:		Goto selected date
// 
// ACCESSIBILTY:	Protected
// 
// MODIFICATIONS:
// Name                  Date       Version    Comments
// N T ALMOND            23NOV200   1.0        Origin
// 
////////////////////////////////////////////////////////////////////////////////
void CCalWnd::OnPopupSelected()
{
	m_rTime = SyncDate(m_cTime);
	ValidateLimits(m_rTime);
	SelectMonth(m_rTime);
}

////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:		CCalWnd::OnPopupRestore
// 
// DESCRIPTION:		Restores selected date
// 
// ACCESSIBILTY:	Protected
// 
// MODIFICATIONS:
// Name                  Date       Version    Comments
// N T ALMOND            23NOV200   1.0        Origin
// 
////////////////////////////////////////////////////////////////////////////////
void CCalWnd::OnPopupRestore()
{
	m_cTime = m_sTime;
	m_rTime = SyncDate(m_cTime);
	ValidateLimits(m_rTime);
	SelectMonth(m_rTime);
}

////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:		CCalWnd::OnCreate
// 
// DESCRIPTION:		Called when the window is created
// 
// ACCESSIBILTY:	Protected
// 
// MODIFICATIONS:
// Name                  Date       Version    Comments
// N T ALMOND            23NOV200   1.0        Origin
// 
////////////////////////////////////////////////////////////////////////////////
int CCalWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	BOOL bShow = lpCreateStruct->style & WS_VISIBLE; // Save and restore later

	lpCreateStruct->style |= WS_CLIPCHILDREN;

	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// Obtain Font metrics
	TEXTMETRIC tm;
	CDC*     pDC = GetDC();
	pDC->SelectObject(GetStockObject(DEFAULT_GUI_FONT));
	pDC->GetTextMetrics(&tm);
	ReleaseDC(pDC);
  		
	m_nCharWidth = tm.tmMaxCharWidth + 2 /* Pad */; 
	m_nCharHeight = tm.tmHeight + 4  /* Pad */; 
	
	int nWidth  = 7 * m_nCharWidth; // Days * CharWidth
	int nHeight = (6 * m_nCharHeight) + (Pos_Base + 8);
	int nYPos= ( Pos_Base + 4 ) - m_nCharHeight;

	CRect wr(lpCreateStruct->x,lpCreateStruct->y,lpCreateStruct->x + nWidth + (m_nEdge*2)+16,lpCreateStruct->y+nHeight);

	// Fix for AdjustWindowRectEx
	if (lpCreateStruct->dwExStyle & WS_EX_TOOLWINDOW)
		lpCreateStruct->style |= WS_CAPTION;

	AdjustWindowRectEx( &wr, lpCreateStruct->style, FALSE, lpCreateStruct->dwExStyle);

	m_rc.SetRect(m_nEdge,Pos_Base,wr.right-m_nEdge,Pos_Base);

	MoveWindow(wr,FALSE);

	CRect rectScroll;
	GetClientRect(rectScroll);


	rectScroll.DeflateRect(1,1);

	rectScroll.left=rectScroll.right - 16;
	rectScroll.top = m_rc.bottom + 2;

	// Set spinner at side of edit window 
	if (!m_btnCalendar.CreateEx( 0,
		UPDOWN_CLASS,
		NULL,
		UDS_WRAP|WS_CHILD|WS_VISIBLE,
		rectScroll,
		this,
		ID_SPIN_CAL))
		return FALSE;


	CRect rcCombo = CreateCombo();
				
	// Combine edit and spinner controls
	CRect yearRect;
	GetClientRect(yearRect);
	yearRect.SetRect(yearRect.left + 90,
		rcCombo.top,
		yearRect.left + 126,
		rcCombo.top + 20);
	
	if (!m_YearEdit.CreateEx(WS_EX_CLIENTEDGE,
		_T("Edit"),
		NULL,
		WS_CHILD|WS_TABSTOP|WS_VISIBLE,
		yearRect,
		this,
		ID_EDITYEAR))
		return FALSE;

	// Create Up Down Controls	
	GetClientRect(rectScroll);
	rectScroll.SetRect(rectScroll.left+126
		,rcCombo.top
		,rectScroll.left + 140,
		rcCombo.top + 20);

	if (!m_btnYear.CreateEx( 0,
		UPDOWN_CLASS,
		NULL,
		UDS_SETBUDDYINT|UDS_AUTOBUDDY|WS_CHILD|WS_VISIBLE|UDS_NOTHOUSANDS,
		rectScroll,
		this,
		ID_SPINYEAR))
		return FALSE;

		
	m_btnYear.SetRange(Min_Year,Max_Year);	

	// Now create buttons
	CRect rcBtn;
	int nXPos = 0;

	for (int n=0;n < glbBtns;n++)
	{
		if (!(n % 7))
		{
			nXPos=0;
			nYPos+=m_nCharHeight;
		}

		rcBtn.left		= nXPos;
		rcBtn.top		= nYPos;
		rcBtn.right		= rcBtn.left + m_nCharWidth;
		rcBtn.bottom	= rcBtn.top + m_nCharHeight;

		CCalBtn* pNew = new CCalBtn(rcBtn, this);

		m_btnList.AddTail(pNew);

		nXPos += m_nCharWidth;
	}


	// Just set selected date to today
	SetDate(MakeDate());

	ShowSpinner(TRUE);


	if (bShow)
		ShowWindow(SW_SHOW);

    EnableToolTips(TRUE);

	return 0;
}


////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:		CCalWnd::OnEraseBkgnd
// 
// DESCRIPTION:		Background Coloring
// 
// ACCESSIBILTY:	Protected
// 
// MODIFICATIONS:
// Name                  Date       Version    Comments
// N T ALMOND            23NOV200   1.0        Origin
// 
////////////////////////////////////////////////////////////////////////////////
BOOL CCalWnd::OnEraseBkgnd(CDC* pDC) 
{
	CRect rc;
	pDC->GetClipBox(rc);


	CBrush brBack(GetSysColor(COLOR_3DFACE));
	CBrush* pOldBrush = pDC->SelectObject(&brBack);

	pDC->PatBlt(rc.left, rc.top, rc.Width(), rc.Height(), PATCOPY);
	pDC->SelectObject(pOldBrush);

	return TRUE;
}


int CCalWnd::OnToolHitTest(CPoint pt, TOOLINFO* pTI) const
{
	int nHit = -1;	// assume none
	if (pTI) {
		// Need to return a unique value from last time:
		// so just return the point as an integer
		//
		nHit = MAKELONG(pt.x, pt.y);
		// setup TOOLINFO structure
		pTI->hwnd = m_hWnd;
		pTI->uId  = nHit;
		GetClientRect(&(pTI->rect));
		pTI->lpszText = LPSTR_TEXTCALLBACK;
		pTI->uFlags |= TTF_ALWAYSTIP ; // OR with TTF_ALWAYSTIP to show
												// tip even when window not active
	}
	return nHit;
}


////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:		CCalWnd::OnToolTipNeedText
// 
// DESCRIPTION:		Tooltip helper
// 
// ACCESSIBILTY:	Protected
// 
// MODIFICATIONS:
// Name                  Date       Version    Comments
// N T ALMOND            23NOV200   1.0        Origin
// 
////////////////////////////////////////////////////////////////////////////////
BOOL CCalWnd::OnToolTipText(UINT /*id*/,  NMHDR * pNMHDR, LRESULT * /*pResult*/)
{
	BOOL bHandledNotify = FALSE;

	CPoint CursorPos;
	VERIFY(::GetCursorPos(&CursorPos));
	ScreenToClient(&CursorPos);

	// Make certain that the cursor is in the client rect, because the
	// mainframe also wants these messages to provide tooltips for the
	// toolbar.
	CCalBtn* pBtn = HitTest(CursorPos);

	if (pBtn)
	{
		TOOLTIPTEXT *pTTT = (TOOLTIPTEXT *)pNMHDR;

		// Adjust the text by filling in TOOLTIPTEXT
		CString strTip;
		strTip.Format(_T("%s"), pBtn->GetTipText());
		ASSERT(strTip.GetLength() < sizeof(pTTT->szText));
		::strncpy(pTTT->szText, strTip,strTip.GetLength());

		// Switch the balloon tips on for Windows 2000
		if (!m_bTipInit &&
			GetOSVersion() == Win2K)
		{
			m_bTipInit = TRUE;
			SetWindowLong(pNMHDR->hwndFrom,GWL_STYLE,GetWindowLong(pNMHDR->hwndFrom,GWL_STYLE) | TTS_BALLOON);
			SetWindowLong(pNMHDR->hwndFrom,GWL_STYLE,GetWindowLong(pNMHDR->hwndFrom,GWL_STYLE) &  ~WS_BORDER);
		}

         bHandledNotify = TRUE;
  
		// Set the text color to same color as you wish...
		

         bHandledNotify = TRUE;
     }
     return bHandledNotify;
 
 
}


////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:		CCalWnd::OnMouseLeave
// 
// DESCRIPTION:		Untrack hitlite button
// 
// ACCESSIBILTY:	Protected
// 
// MODIFICATIONS:
// Name                  Date       Version    Comments
// N T ALMOND            23NOV200   1.0        Origin
// 
////////////////////////////////////////////////////////////////////////////////
LRESULT CCalWnd::OnMouseLeave(WPARAM /*wParam*/, LPARAM /*lParam*/)
{
	if (m_pbtnCurrent)
		m_pbtnCurrent->SetHover(FALSE);

	m_bTrackLeave = FALSE;

	return 0;
}

////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:		CCalWnd::MakeDate
// 
// DESCRIPTION:		Zeroize Time/part for date equalivalence testing
// 
// ACCESSIBILTY:	Protected
// 
// MODIFICATIONS:
// Name                  Date       Version    Comments
// N T ALMOND            23NOV200   1.0        Origin
// 
////////////////////////////////////////////////////////////////////////////////
COleDateTime CCalWnd::MakeDate(COleDateTime date)
{
	COleDateTime tmDate;
	tmDate.SetDateTime(date.GetYear(), date.GetMonth(), date.GetDay(), 0,0,0);
	return tmDate;

}

////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:		CCalWnd::AddNote
// 
// DESCRIPTION:		Add note to date
// 
// ACCESSIBILTY:	Public
// 
// MODIFICATIONS:
// Name                  Date       Version    Comments
// N T ALMOND            23NOV200   1.0        Origin
// 
////////////////////////////////////////////////////////////////////////////////
BOOL CCalWnd::AddNote(COleDateTime& date, CString strNote, BOOL bReplace)
{
	COleDateTime tm = MakeDate(date);

	if (!ValidateLimits(tm))
		return FALSE;

	CString str;
	if (m_listNotes.Lookup(tm,str))
	{
		if (!bReplace)
			return FALSE;

		m_listNotes.RemoveKey(tm);
	}


	m_listNotes.SetAt(tm, strNote);

	// Add note against this date
	POSITION pos = m_btnList.GetHeadPosition();
	while (pos)
	{
		CCalBtn* pBtn = m_btnList.GetNext(pos);
		ASSERT(pBtn);
		if (pBtn->GetDate() == tm)
		{
			pBtn->SetNote(strNote);
			InvalidateRect(pBtn->GetRect(), FALSE);			
			break;
		}
	}
	
	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:		CCalWnd::AddNote
// 
// DESCRIPTION:		Add note to date
// 
// ACCESSIBILTY:	Public
// 
// MODIFICATIONS:
// Name                  Date       Version    Comments
// N T ALMOND            23NOV200   1.0        Origin
// 
////////////////////////////////////////////////////////////////////////////////
void CCalWnd::DeleteNote(COleDateTime& date)
{
	COleDateTime tm = MakeDate(date);

	if (!ValidateLimits(tm))
		return;

	CString str;
	if (m_listNotes.Lookup(tm,str))
	{
		m_listNotes.RemoveKey(tm);

		// Remove note against this date
		POSITION pos = m_btnList.GetHeadPosition();
		while (pos)
		{
			CCalBtn* pBtn = m_btnList.GetNext(pos);
			ASSERT(pBtn);
			if (pBtn->GetDate() == tm)
			{
				pBtn->SetNote(_T(""));
				InvalidateRect(pBtn->GetRect(), FALSE);			
				break;
			}
		}
	}
}
////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:		CCalWnd::IsSpinnerVisible
// 
// DESCRIPTION:		Returns true if month spinners are visible else false
// 
// ACCESSIBILTY:	Public
// 
// MODIFICATIONS:
// Name                  Date       Version    Comments
// N T ALMOND            23NOV200   1.0        Origin
// 
////////////////////////////////////////////////////////////////////////////////
BOOL CCalWnd::IsSpinnerVisible()
{
	return m_bSpinner;
}




////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:		CCalWnd::GetOSVersion
// 
// DESCRIPTION:		Helper function
// 
// ACCESSIBILTY:	Protected
// 
// MODIFICATIONS:
// Name                  Date       Version    Comments
// N T ALMOND            23NOV200   1.0        Origin
// 
////////////////////////////////////////////////////////////////////////////////
WindowsVersion CCalWnd::GetOSVersion()
{
   OSVERSIONINFOEX osvi;
   BOOL bOsVersionInfoEx;

   // Try calling GetVersionEx using the OSVERSIONINFOEX structure,
   // which is supported on Windows 2000.
   //
   // If that fails, try using the OSVERSIONINFO structure.

   ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
   osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);

   if( !(bOsVersionInfoEx = GetVersionEx ((OSVERSIONINFO *) &osvi)) )
   {
      // If OSVERSIONINFOEX doesn't work, try OSVERSIONINFO.

      osvi.dwOSVersionInfoSize = sizeof (OSVERSIONINFO);
      if (! GetVersionEx ( (OSVERSIONINFO *) &osvi) ) 
         return UnSupported;
   }

   switch (osvi.dwPlatformId)
   {
      case VER_PLATFORM_WIN32_NT:

      // Test for the product.

         if ( osvi.dwMajorVersion <= 4 )
		 {
            return WinNT;
		 }

         if ( osvi.dwMajorVersion == 5 )
		 {
            return Win2K;
		 }

        break;

      case VER_PLATFORM_WIN32_WINDOWS:

         if ((osvi.dwMajorVersion > 4) || 
            ((osvi.dwMajorVersion == 4) && (osvi.dwMinorVersion > 0)))
		 {
            return Win98;
		 }
         else 
		 {
            return Win95;
		 }
         break;

   }
   return UnSupported; 
}

////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:		CCalWnd::GetOSVersion
// 
// DESCRIPTION:		Helper function
// 
// ACCESSIBILTY:	Protected
// 
// MODIFICATIONS:
// Name                  Date       Version    Comments
// N T ALMOND            23NOV200   1.0        Origin
// 
////////////////////////////////////////////////////////////////////////////////
void CCalWnd::ClearAllNotes()
{

	m_listNotes.RemoveAll();
	POSITION pos = m_btnList.GetHeadPosition();
	while (pos)
	{
		CCalBtn* pBtn = m_btnList.GetNext(pos);
		ASSERT(pBtn);
		pBtn->SetNote(_T(""));
	}

	RedrawWindow();
}