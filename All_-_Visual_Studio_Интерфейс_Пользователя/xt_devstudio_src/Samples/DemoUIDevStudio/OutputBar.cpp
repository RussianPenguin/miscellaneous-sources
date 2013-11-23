// OutputBar.cpp : implementation file
//
/////////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "DemoUIDevStudio.h"
#include "OutputBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COutputBar

COutputBar::COutputBar()
{
	m_cy = ::GetSystemMetrics(SM_CYHSCROLL);
}

COutputBar::~COutputBar()
{
	// TODO: add destruction code here.
}

IMPLEMENT_DYNAMIC(COutputBar, CXTDockWindow)

BEGIN_MESSAGE_MAP(COutputBar, CXTDockWindow)
	//{{AFX_MSG_MAP(COutputBar)
	ON_WM_CREATE()
	ON_WM_WINDOWPOSCHANGED()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COutputBar message handlers

int COutputBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CXTDockWindow::OnCreate(lpCreateStruct) == -1)
		return -1;

	// Create  the flat tab control.
	if (!m_flatTabCtrl.Create(WS_CHILD|WS_VISIBLE|FTS_XT_DEFAULT,
		CRect(0,0,0,0), this, IDC_FLATTABCTRL))
	{
		TRACE0( "Failed to create flattab control\n" );
		return -1;
	}

	// Insert tabs into the flat tab control.
	m_flatTabCtrl.InsertItem(0, _T("Build"));
	m_flatTabCtrl.InsertItem(1, _T("Debug"));
	m_flatTabCtrl.InsertItem(2, _T("Find in Files 1"));
	m_flatTabCtrl.InsertItem(3, _T("Find in Files 2"));
	m_flatTabCtrl.InsertItem(4, _T("Results"));
	m_flatTabCtrl.InsertItem(5, _T("SQL Debugging"));

	// Define the default style for the output list boxes.
	DWORD dwStyle = WS_CHILD | WS_VISIBLE | LBS_NOINTEGRALHEIGHT | 
		WS_VSCROLL | WS_TABSTOP;

	// Create the sheet1 list box.
	if (!m_sheet1.Create( dwStyle, CRect(0,0,0,0), this, IDC_SHEET1 ))
	{
		TRACE0( "Failed to create sheet1.\n" );
		return -1;
	}

	// Create the sheet2 list box.
	if (!m_sheet2.Create( dwStyle, CRect(0,0,0,0), this, IDC_SHEET2 ))
	{
		TRACE0( "Failed to create sheet2.\n" );
		return -1;
	}

	// Create the sheet3 list box.
	if (!m_sheet3.Create( dwStyle, CRect(0,0,0,0), this, IDC_SHEET3 ))
	{
		TRACE0( "Failed to create sheet3.\n" );
		return -1;
	}

	// Create the sheet4 list box.
	if (!m_sheet4.Create( dwStyle, CRect(0,0,0,0), this, IDC_SHEET4 ))
	{
		TRACE0( "Failed to create sheet4.\n" );
		return -1;
	}

	// Create the sheet5 list box.
	if (!m_sheet5.Create( dwStyle, CRect(0,0,0,0), this, IDC_SHEET5 ))
	{
		TRACE0( "Failed to create sheet5.\n" );
		return -1;
	}

	// Create the sheet6 list box.
	if (!m_sheet6.Create( dwStyle, CRect(0,0,0,0), this, IDC_SHEET6 ))
	{
		TRACE0( "Failed to create sheet6.\n" );
		return -1;
	}

	// Insert text into the list box.
	m_sheet1.AddString(_T("Build Tab Output..."));
	m_sheet2.AddString(_T("Debug Tab Output..."));
	m_sheet3.AddString(_T("Find in Files 1 Tab Output..."));
	m_sheet4.AddString(_T("Find in Files 2 Tab Output..."));
	m_sheet5.AddString(_T("Results Tab Output..."));
	m_sheet6.AddString(_T("SQL Debugging Tab Output..."));

	// Set the current tab.
	SelectTabView(0);
	SetXTBarStyle(CBRS_XT_DEFAULT|CBRS_XT_CLIENT_OUTLINE);

	return 0;
}

BOOL COutputBar::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	if(IDC_FLATTABCTRL == (UINT)wParam)
	{
		NMHDR* pNMHDR = (NMHDR*)lParam;

		switch(pNMHDR->code)
		{
		case TCN_SELCHANGING:
			break;
		case TCN_SELCHANGE:
			SelectTabView(m_flatTabCtrl.GetCurSel());
			break;
		}
	}
	
	return CXTDockWindow::OnNotify(wParam, lParam, pResult);
}

void COutputBar::SelectTabView(int nTab)
{
	m_sheet1.ShowWindow((nTab==0)?SW_SHOW:SW_HIDE);
	m_sheet2.ShowWindow((nTab==1)?SW_SHOW:SW_HIDE);
	m_sheet3.ShowWindow((nTab==2)?SW_SHOW:SW_HIDE);
	m_sheet4.ShowWindow((nTab==3)?SW_SHOW:SW_HIDE);
	m_sheet5.ShowWindow((nTab==4)?SW_SHOW:SW_HIDE);
	m_sheet6.ShowWindow((nTab==5)?SW_SHOW:SW_HIDE);
}

void COutputBar::OnWindowPosChanged(WINDOWPOS FAR* lpWP) 
{
	CXTDockWindow::OnWindowPosChanged(lpWP);
	
	CRect rc;
	GetInsideRect(rc);
	rc.DeflateRect(1,1);

	// Resize the flat tab control...
	if (m_flatTabCtrl.GetSafeHwnd()) {
		m_flatTabCtrl.MoveWindow(rc.left, rc.bottom-m_cy+1,
			rc.Width(), m_cy-1);
	}
	
	// and resize each list box control.
	if (m_sheet1.GetSafeHwnd()) {
		m_sheet1.MoveWindow(rc.left, rc.top, 
			rc.Width(), rc.Height()-m_cy+1);
	}
	if (m_sheet2.GetSafeHwnd()) {
		m_sheet2.MoveWindow(rc.left, rc.top, 
			rc.Width(), rc.Height()-m_cy+1);
	}
	if (m_sheet3.GetSafeHwnd()) {
		m_sheet3.MoveWindow(rc.left, rc.top, 
			rc.Width(), rc.Height()-m_cy+1);
	}
	if (m_sheet4.GetSafeHwnd()) {
		m_sheet4.MoveWindow(rc.left, rc.top, 
			rc.Width(), rc.Height()-m_cy+1);
	}
	if (m_sheet5.GetSafeHwnd()) {
		m_sheet5.MoveWindow(rc.left, rc.top, 
			rc.Width(), rc.Height()-m_cy+1);
	}
	if (m_sheet6.GetSafeHwnd()) {
		m_sheet6.MoveWindow(rc.left, rc.top, 
			rc.Width(), rc.Height()-m_cy+1);
	}
}
