// MDIFrmEx.cpp : implementation of the CMDIFrameEx class
//

// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1997 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.


#include "stdafx.h"
#include "resource.h"

#include "MDIFrmEx.h"
#include "ToolbarEx.h"
#include "WinAppEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMDIFrameEx

IMPLEMENT_DYNAMIC(CMDIFrameEx, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMDIFrameEx, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMDIFrameEx)
	ON_COMMAND(ID_INTMODE, OnIntMode)
	ON_UPDATE_COMMAND_UI(ID_INTMODE, OnUpdateIntMode)
	//}}AFX_MSG_MAP
	ON_WM_MEASUREITEM()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMDIFrameEx construction/destruction

CMDIFrameEx::CMDIFrameEx():m_MainMenu(FALSE,TRUE)
{
}

CMDIFrameEx::~CMDIFrameEx()
{
	CString strTmp;
	strTmp.Format("Menu%d",m_nIDResource);
	((CWinAppEx*)AfxGetApp())->SaveMenuChanges(&m_MainMenu,strTmp);
}

BOOL CMDIFrameEx::PreCreateWindow(CREATESTRUCT& cs)
{
	return CMDIFrameWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMDIFrameEx diagnostics

#ifdef _DEBUG
void CMDIFrameEx::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMDIFrameEx::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMDIFrameEx message handlers

BOOL CMDIFrameEx::PreTranslateMessage(MSG* pMsg) 
{
	if (m_wndMenuBar.TranslateFrameMessage(pMsg))
		return TRUE;
	
	return CMDIFrameWnd::PreTranslateMessage(pMsg);
}

BOOL CMDIFrameEx::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, CWnd *pParentWnd, CCreateContext *pContext)
{
	// only do this once
	ASSERT_VALID_IDR(nIDResource);
	ASSERT(m_nIDHelp == 0 || m_nIDHelp == nIDResource);

	m_wndMenuBar.SetParent((CWnd*)this);
	m_nIDHelp = nIDResource;    // ID for help context (+HID_BASE_RESOURCE)
	m_nIDResource = nIDResource;    // ID for menu

	CString strFullString;
	if (strFullString.LoadString(nIDResource))
		AfxExtractSubString(m_strTitle, strFullString, 0);    // first sub-string

	// attempt to create the window
	LPCTSTR lpszClass = GetIconWndClass(dwDefaultStyle, nIDResource);
	LPCTSTR lpszTitle = m_strTitle;
	if (!Create(lpszClass, lpszTitle, dwDefaultStyle, rectDefault,
	  pParentWnd, NULL, 0L, pContext))
	{
		return FALSE;   // will self destruct on failure normally
	}

	// save the default menu handle
	ASSERT(m_hWnd != NULL);
	m_hMenuDefault = ::GetMenu(m_hWnd);

	// load accelerator resource
	LoadAccelTable(MAKEINTRESOURCE(nIDResource));

	if (pContext == NULL)   // send initial update
		SendMessageToDescendants(WM_INITIALUPDATE, 0, 0, TRUE, TRUE);

	return TRUE;
}

BOOL CMDIFrameEx::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	CMenu* pMenu = NULL;
	if (m_hMenuDefault == NULL)
	{
		// default implementation for MFC V1 backward compatibility
		pMenu = GetMenu();
		if(pMenu != NULL)
		{
			HMENU hMenu=GetWindowMenuPopup(pMenu->GetSafeHmenu());
			pMenu=CMenu::FromHandle(hMenu);
			ASSERT(pMenu->IsKindOf(RUNTIME_CLASS(CMenuEx)));
		}
	}

	return CreateClient(lpcs, pMenu);}

HMENU CMDIFrameEx::GetWindowMenuPopup( HMENU hMenuBar )
{
	int n=GetMenuItemCount(hMenuBar);
	int i,j,m;
	HMENU t;
	UINT Id;
	for(i=n-1;i>=0;i--)
		{
			t=GetSubMenu(hMenuBar,i);
			m=GetMenuItemCount(t);
			for(j=0;j<=m;j++)
			{
				Id=GetMenuItemID(t,j);
				if (Id==ID_WINDOW_ARRANGE ||
					Id==ID_WINDOW_CASCADE ||
					Id==ID_WINDOW_TILE_HORZ ||
					Id==ID_WINDOW_TILE_VERT)
				return t;
			}
		}
		return NULL;
}

int CMDIFrameEx::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	AfxGetApp()->m_pMainWnd=this;
	m_wndMenuBar.SetParent((CWnd*)this);

	if (!m_wndMenuBar.CreateEx(this, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_SIZE_DYNAMIC ,CRect(1,4,1,4)))
	{
		TRACE0("Failed to create menubar\n");
		return -1;      // fail to create
	}	

	m_MainMenu.LoadMenu(m_nIDResource);
	LoadMenuToolBars();
	CMenuEx* pMenu = &m_MainMenu;
	HMENU hMenu=GetWindowMenuPopup(pMenu->GetSafeHmenu());
	pMenu=(CMenuEx*)CMenu::FromHandle(hMenu);
	if(pMenu) ASSERT(pMenu->IsKindOf(RUNTIME_CLASS(CMenuEx)));
	m_wndMenuBar.LoadMenu(&m_MainMenu,pMenu);
	m_wndMenuBar.EnableDockingEx(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndMenuBar);

	m_wndMenuBar.SetWindowText(_T("Menu"));

	return 0;
}

CMenuEx* CMDIFrameEx::GetWindowMenuPopup(CMenuEx *pMenu)
{
	if(!pMenu) return NULL;
	int n=pMenu->GetMenuItemCount();
	int i,j,m;
	CMenuEx* t;
	UINT Id;
	for(i=n-1;i>=0;i--)
		{
			t=pMenu->GetSubMenu(i);
			if(!t) continue;
			m=t->GetMenuItemCount();
			for(j=0;j<=m;j++)
			{
				Id=t->GetMenuItemID(j);
				if (Id==ID_WINDOW_ARRANGE ||
					Id==ID_WINDOW_CASCADE ||
					Id==ID_WINDOW_TILE_HORZ ||
					Id==ID_WINDOW_TILE_VERT)
				return t;
			}
		}
		return NULL;
}

CMenuBar* CMDIFrameEx::GetMenuBar()
{
	return &m_wndMenuBar;
}

void CMDIFrameEx::EnableMenuChange(BOOL bEnable)
{
	m_wndMenuBar.EnableMenuChange(bEnable);
}

void CMDIFrameEx::SetMenuToolBars(UINT *puArray, int n)
{
	m_MenuToolBars.SetSize(n);
	for(int i=0;i<n;i++)
		m_MenuToolBars[i]=puArray[i];
}

void CMDIFrameEx::LoadMenuToolBars()
{
	if (!m_MenuToolBars.GetSize())
		m_MainMenu.LoadToolbar(m_nIDResource);
	else
		m_MainMenu.LoadToolbars(m_MenuToolBars.GetData(),m_MenuToolBars.GetSize());
}

void CMDIFrameEx::RegisterToolBar(CToolbarEx* pToolBar)
{
	int i,n=m_ToolBarList.GetSize();
	m_ToolBarList.SetSize(n+1);
	BOOL Found=TRUE;
	while (Found)
	{
		Found=FALSE;
		for (i=0;i<n;i++)
		{
			if (m_ToolBarList[i]->m_nIDResource==pToolBar->m_nIDResource)
			{
				Found=TRUE;
				(pToolBar->m_nIDResource)++;
			}
		}
	}
	m_ToolBarList[n]=pToolBar;
}

void CMDIFrameEx::RemoveToolbar(CToolbarEx *pToolbar)
{
	int i,n=m_ToolBarList.GetSize();
	BOOL Found=FALSE;
	for (i=0;i<n;i++)
	{
		if (m_ToolBarList[i]==pToolbar)
		{
			Found=TRUE;
			break;
		}
	}
	if (Found)
	{
		for(;i<n-1;i++)
			m_ToolBarList[i]=m_ToolBarList[i+1];
		m_ToolBarList.SetSize(n-1);
	}
}

//This handler ensure that the popup menu items are drawn correctly
void CMDIFrameEx::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{  
	BOOL setflag=FALSE;  
	if(lpMeasureItemStruct->CtlType==ODT_MENU)
	{
		m_wndMenuBar.MeasureItem(nIDCtl,lpMeasureItemStruct);
		return;
	}  
	if(!setflag)CMDIFrameWnd::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}

void CMDIFrameEx::RefreshMenuBar(CMenuEx *pMenu, CMenuEx *pWindowMenu)
{
	if (pMenu==NULL) 
	{
		pMenu=&m_MainMenu;
		pWindowMenu=GetWindowMenuPopup(pMenu);
	}
	m_wndMenuBar.LoadMenu(pMenu,pWindowMenu);
}

void CMDIFrameEx::OnIntMode() 
{
	m_wndMenuBar.SetIntelligentMode(!m_wndMenuBar.GetIntelligentMode());
}

void CMDIFrameEx::OnUpdateIntMode(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_wndMenuBar.GetIntelligentMode());
}
