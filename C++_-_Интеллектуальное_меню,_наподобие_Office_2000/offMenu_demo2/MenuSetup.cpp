// MenuSetup.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "MenuSetup.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifndef ENGLISH
#define MENU_SAVE "Salvare le modifiche?"
#else
#define MENU_SAVE "Do you wish to save modifications?"
#endif

/////////////////////////////////////////////////////////////////////////////
// CMenuSetup dialog


CMenuSetup::CMenuSetup(CWnd* pParent /*=NULL*/)
	: CDialog(CMenuSetup::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMenuSetup)
	//}}AFX_DATA_INIT
	m_IsModified=0;
	m_CurComboSel=0;
	m_CurMode=0;
	m_bSaved=FALSE;
	m_pMenuBar=NULL;
	m_pToolBar=NULL;
}


void CMenuSetup::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMenuSetup)
	DDX_Control(pDX, IDC_TAB1, m_Tab);
	DDX_Control(pDX, IDC_COMBO, m_Combo);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_PAGER_CTRL1, m_Pager1);
}


BEGIN_MESSAGE_MAP(CMenuSetup, CDialog)
	//{{AFX_MSG_MAP(CMenuSetup)
	ON_CBN_SELCHANGE(IDC_COMBO, OnComboSelChange)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, OnTabSelChange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMenuSetup message handlers

BOOL CMenuSetup::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message!=WM_COMMAND)
		return CDialog::PreTranslateMessage(pMsg);
	else 
	{
		if (pMsg->wParam== IDCANCEL) {OnCancel();return TRUE;}
		CMenuEx* pTopMenu = (CMenuEx*)m_pMenuBar->GetMenu();
		ChangeMenuState(pTopMenu,pMsg->wParam);
		return TRUE;
	}
}

CMenuEx* CMenuSetup::ChangeMenuState(CMenuEx * pTopMenu,UINT com)
{
	// Locate the submenu
	int iPos;
	CMenuEx* pMenu;
	for (iPos = pTopMenu->GetMenuItemCount()-1; iPos >= 0; iPos--)
	{
			if (pMenu = pTopMenu->GetSubMenu(iPos))
			{
				pMenu=ChangeMenuState(pMenu,com);
				if (pMenu) return pMenu;
			}
			else if (com!= (signed)-1 && pTopMenu->GetMenuItemID(iPos) == (signed)com)
			{
				m_IsModified=TRUE;
				m_MenuList[m_CurComboSel].m_bModified=TRUE;
				UINT t=pTopMenu->GetMenuState(iPos,MF_BYPOSITION);
				if (t& MF_CHECKED) 
				{
					pTopMenu->CheckMenuItem(iPos, MF_BYPOSITION|MF_UNCHECKED);
				}
				else
				{
					
					UINT t=((CMenuEx*)pTopMenu)->GetFlagsEx(iPos);
					if (t&MF_DRAWGRAYED)
					{
						((CMenuEx*)pTopMenu)->SetFlagsEx(iPos,t&(~MF_DRAWGRAYED));
						pTopMenu->CheckMenuItem(iPos, MF_BYPOSITION|MF_CHECKED);
					}
					else
					{
						((CMenuEx*)pTopMenu)->SetFlagsEx(iPos,t|MF_DRAWGRAYED);
					}
				}
				return pMenu;
			}
			else if (com==-1)
			{
				if (pTopMenu->GetMenuItemID(iPos)== ID_SEPARATOR) continue;
				pTopMenu->CheckMenuItem(iPos, MF_BYPOSITION|MF_CHECKED);
				((CMenuEx*)pTopMenu)->SetFlagsEx(iPos,0xFFFF);
			}
	}
	return NULL;
}

BOOL CMenuSetup::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_IsModified=FALSE;
	m_bSaved=FALSE;
	m_CurMode=0;
	m_CurComboSel=0;
	
	m_Tab.InsertItem(0,"Menu");
	m_Tab.InsertItem(1,"Toolbar");
	m_Tab.SetCurSel(0);

	for(int i=0;i<m_MenuList.GetSize();i++)
		m_Combo.InsertString(i,m_MenuList[i].m_MenuName);
	m_Combo.SetCurSel(0);

	m_pMenuBar=new CMenuBar();
	if (!m_pMenuBar->CreateEx(&m_Pager1, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_SIZE_DYNAMIC ,CRect(1,4,1,4)))
	{
		TRACE0("Failed to create menubar\n");
		return -1;      // fail to create
	}	

    // Finally, center the dialog on the screen
	CenterWindow();

	ChangeMode(0,0);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CMenuSetup::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
	if(nCode == CN_COMMAND)
	{
		if (nID==IDOK) OnOK();
		else if (nID==IDCANCEL) OnCancel();
		else if (nID==IDC_COMBO) return CDialog::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
		else if (nID==IDC_TAB1) return CDialog::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
		else 
		{
			int n=m_pToolBar->CommandToIndex(nID);
			if (n>=0)
			{
				CToolBarCtrl& r=m_pToolBar->GetToolBarCtrl();
				r.CheckButton(nID,!r.IsButtonChecked(nID));
				m_IsModified=TRUE;
				m_ToolBarList[m_CurComboSel].m_bModified=TRUE;
			}
		}
		return TRUE;
	}
	
	return CDialog::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

CMenuEx* CMenuSetup::LoadMenuState(CMenuEx * pTopMenu, const char* section)
{
	// Locate the submenu
	int iPos,tt;
	UINT nID;
	CMenuEx* pMenu;
	for (iPos = pTopMenu->GetMenuItemCount()-1; iPos >= 0; iPos--)
	{
			if (pMenu = pTopMenu->GetSubMenu(iPos))
			{
				pMenu=LoadMenuState(pMenu,section);
			}
			else
			{
				CString str;
				nID=pTopMenu->GetMenuItemID(iPos);
				if (nID==ID_SEPARATOR)
				{
					pTopMenu->SetFlagsEx(iPos,0x8000);
					continue;
				}
				str.Format("ID_%d",nID);
				UINT t;
				t=AfxGetApp()->GetProfileInt(section,str,0x8000);
				if (t>0xffff) t=0xffff;
				if (t==0) 
				{
					((CMenuEx*)pTopMenu)->SetFlagsEx(iPos,t);
				}
				if (t==0xFFFF) 
					((CMenuEx*)pTopMenu)->SetFlagsEx(iPos,0x8000);
				else
					pTopMenu->CheckMenuItem(iPos, MF_BYPOSITION|MF_UNCHECKED);
				if (t>0 && t<0xFFFF) 
				{
					((CMenuEx*)pTopMenu)->SetFlagsEx(iPos,MF_DRAWGRAYED|t);
				}
				if (!m_MenuList[m_CurComboSel].m_Loaded)
				{
					tt=m_MenuList[m_CurComboSel].m_IDs.GetSize();
					m_MenuList[m_CurComboSel].m_IDs.SetSize(tt+1);
					m_MenuList[m_CurComboSel].m_IDs[tt]=(DWORD)(t<<16)+(WORD)nID;
				}
			}
	}
	return NULL;
}

CMenuEx* CMenuSetup::SaveMenu(CMenuEx * pTopMenu, const char* section)
{
	int iPos;
	CMenuEx* pMenu;
	m_bSaved=TRUE;
	for (iPos = pTopMenu->GetMenuItemCount()-1; iPos >= 0; iPos--)
	{
			if (pMenu = pTopMenu->GetSubMenu(iPos))
			{
				pMenu=SaveMenu(pMenu,section);
			}
			else
			{
				CString str;
				if (pTopMenu->GetMenuItemID(iPos)== ID_SEPARATOR) continue;
				UINT t=pTopMenu->GetMenuState(iPos,MF_BYPOSITION);
				if ((t&MF_CHECKED)!=MF_CHECKED)
				{
					t=pTopMenu->GetFlagsEx(iPos);
					if (t&MF_DRAWGRAYED)
					{
						str.Format("ID_%d",pTopMenu->GetMenuItemID(iPos));
						if ((t&0xffff)==0) t=0x8000;
						AfxGetApp()->WriteProfileInt(section,str,t&0xffff);
					}
					else
					{
						str.Format("ID_%d",pTopMenu->GetMenuItemID(iPos));
						AfxGetApp()->WriteProfileInt(section,str,0);
					}
				}
				else
				{
					str.Format("ID_%d",pTopMenu->GetMenuItemID(iPos));
					AfxGetApp()->WriteProfileInt(section,str,0xFFFF);
				}
			}
	}
	return NULL;
}

int CMenuSetup::SaveMenu(FILE* f, int n, CMenuEx* pTopMenu)
{
	if (pTopMenu==NULL) pTopMenu = (CMenuEx*)m_pMenuBar->GetMenu();
	int iPos;
	CString str;
	for (iPos = 0; iPos<(signed)pTopMenu->GetMenuItemCount(); iPos++)
	{
		for(int i=0;i<n;i++) putc(' ',f);
		CMenuEx* pMenu = pTopMenu->GetSubMenu(iPos);
		if (pMenu)
		{
			if (pMenu->GetMenuItemCount()) SaveMenu(f,n+1,pMenu);
			pMenu->GetMenuString(iPos,str,MF_BYPOSITION);
			fputs(str,f);
			putc('=',f);
			fprintf(f,"%d\n",pMenu->GetMenuItemID(iPos));
		}
	}
	return 0;
}

void CMenuSetup::OnOK() 
{
	if(m_IsModified) 
	{
		if (m_Tab.GetCurSel()==0)
			SaveCurMenu();
		else
			SaveCurToolbar();
	}
	CDialog::OnOK();
}

void CMenuSetup::LoadToolbarState(CToolBar & Toolbar, const char * section)
{
	CToolBarCtrl &t=Toolbar.GetToolBarCtrl();
	CString str;

	int n=t.GetButtonCount();
	int tb;
	int nn=0;
	for (int i=0;i<n;i++)
	{
		int nID=Toolbar.GetItemID(i);
		if (nID==ID_SEPARATOR) continue;
		else
		{
			str.Format("ID_%d",nID);
			tb=AfxGetApp()->GetProfileInt(section,str,0x8000);
			t.CheckButton(nID,tb);
			if (!m_MenuList[m_CurComboSel].m_Loaded)
			{
				nn++;
				m_ToolBarList.SetSize(nn);
				m_ToolBarList[m_CurComboSel].m_IDs[nn]=(DWORD)(tb<<16)+(WORD)nID;
			}
		}
	}
}

void CMenuSetup::SaveToolbar(CToolBar & Toolbar, const char * section)
{
	CToolBarCtrl &t=Toolbar.GetToolBarCtrl();
	CString str;

	m_bSaved=TRUE;
	int n=t.GetButtonCount();
	for (int i=0;i<n;i++)
	{
		int nID=Toolbar.GetItemID(i);
		if (nID==ID_SEPARATOR) continue;
		else
		{
			str.Format("ID_%d",nID);
			if (t.IsButtonChecked(nID))
				AfxGetApp()->WriteProfileInt(section,str,1);
			else
				AfxGetApp()->WriteProfileInt(section,str,0);
		}
	}
}

void CMenuSetup::UpdateMenu()
{
	CString str;
	str.Format("Menu%d",m_MenuList[m_CurComboSel].m_nIDResource);
	CMenuEx* pTopMenu = (CMenuEx*)m_pMenuBar->GetMenu();
	ChangeMenuState(pTopMenu,-1);
	LoadMenuState(pTopMenu,str);
	m_MenuList[m_CurComboSel].m_Loaded=TRUE;
}

void CMenuSetup::ChangeMode(int iMode, int iSel)
{
	int i;

	if (iMode==0 && iMode !=m_CurMode)
	{
		for(i=m_Combo.GetCount()-1;i>=0;i--)
			m_Combo.DeleteString(0);
		for(i=0;i<m_MenuList.GetSize();i++)
			m_Combo.InsertString(i,m_MenuList[i].m_MenuName);

		m_Combo.SetCurSel(0);
		if(m_pToolBar)
		{
			if (IsWindow(m_pToolBar->m_hWnd))m_pToolBar->DestroyWindow();
			delete m_pToolBar;
			m_pToolBar=NULL;
		}
		m_pMenuBar=new CMenuBar;
		if (!m_pMenuBar->CreateEx(&m_Pager1, WS_CHILD | WS_VISIBLE | CBRS_TOP
			| CBRS_GRIPPER | CBRS_SIZE_DYNAMIC ,CRect(1,4,1,4)))
		{
			TRACE0("Failed to create menubar\n");
			return ;      // fail to create
		}	
	}
	else if (iMode==1 && iMode !=m_CurMode)
	{
		for(i=m_Combo.GetCount()-1;i>=0;i--)
			m_Combo.DeleteString(0);
		for(i=0;i<m_ToolBarList.GetSize();i++)
			m_Combo.InsertString(i,m_ToolBarList[i].m_MenuName);

		m_Combo.SetCurSel(0);
		if(m_pMenuBar)
		{
			if (IsWindow(m_pMenuBar->m_hWnd))m_pMenuBar->DestroyWindow();
			delete m_pMenuBar;
			m_pMenuBar=NULL;
		}
		m_pToolBar=new CToolBar;
		if (!m_pToolBar->CreateEx(&m_Pager1,TBSTYLE_FLAT,
							   CBRS_GRIPPER|CBRS_TOP|CBRS_TOOLTIPS|CBRS_FLYBY|
							   WS_VISIBLE|CBRS_SIZE_DYNAMIC))
		{
			TRACE0("Failed to create menubar\n");
			return ;      // fail to create
		}	
	}
	if(iMode==0)
	{
		m_Menu.EnableArrows(TRUE);
		m_Menu.DestroyMenu();
		m_Menu.LoadMenu(m_MenuList[iSel].m_nIDResource);
		m_pMenuBar->LoadMenu(&m_Menu,NULL);
		m_Menu.EnableGrayedDraw(TRUE);
		//m_pMenuBar->RefreshMenuPainting(&m_Menu);
		m_Menu.EnableArrows(FALSE);

		// Set the child HWND, button size to 15 and style to PGS_HORZ.
		m_Pager1.SetChild(m_pMenuBar->m_hWnd);
		m_Pager1.ModifyStyle(0,PGS_HORZ);
		m_Pager1.SetButtonSize(15);
	
		// Determine size of child
		CSize MySize=m_pMenuBar->CalcSize();
		// Set the scroll area for pager.
		m_Pager1.SetScrollArea(MySize.cx+15, MySize.cy+15);
		m_Pager1.RecalcSize();
	}
	else if(iMode==1)
	{
		m_pToolBar->LoadToolBar(m_MenuList[iSel].m_nIDResource);

		SIZE Size;

		// Determine size of child
		m_pToolBar->SendMessage(TB_GETMAXSIZE,0,(LPARAM)&Size);
		// Set the child HWND, button size to 15 and style to PGS_HORZ.
		m_Pager1.SetChild(m_pToolBar->m_hWnd);
		m_Pager1.ModifyStyle(0,PGS_HORZ);
		m_Pager1.SetButtonSize(15);
	
		// Set the scroll area for pager.
		m_Pager1.SetScrollArea(Size.cx+15, Size.cy+15);
		m_Pager1.RecalcSize();
	}

	if (iMode==0)
		UpdateMenu();
	else
		UpdateToolbar();
}

void CMenuSetup::OnComboSelChange() 
{
	if (m_IsModified
#ifdef ASK_ANY_CHANGE
		&& AfxMessageBox(MENU_SAVE /*Salvare le modifiche?*/, MB_YESNO)==IDYES
#endif
		)
	{
		if (m_CurMode==0)
 			SaveCurMenu();
		else
			SaveCurToolbar();
		m_IsModified=FALSE;
	}
	m_CurComboSel=m_Combo.GetCurSel();
 	ChangeMode(m_CurMode,m_CurComboSel);
}

void CMenuSetup::SaveCurMenu()
{
	CString str;
	str.Format("Menu%d",m_MenuList[m_CurComboSel].m_nIDResource);
	CMenuEx* pTopMenu = (CMenuEx*)m_pMenuBar->GetMenu();
	SaveMenu(pTopMenu,str);
}

void CMenuSetup::SaveCurToolbar()
{
	CString str;
	str.Format("Toolbar%d",m_ToolBarList[m_CurComboSel].m_nIDResource);
	SaveToolbar(*m_pToolBar,str);
}

void CMenuSetup::OnTabSelChange(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if (m_IsModified
#ifdef ASK_ANY_CHANGE
		&& AfxMessageBox(MENU_SAVE /*Salvare le modifiche?*/, MB_YESNO)==IDYES
#endif
		)
	{
		if (m_CurMode==0)
		{
 			SaveCurMenu();
		}
		else

			SaveCurToolbar();
		m_IsModified=FALSE;
	}
	m_CurComboSel=0;
 	ChangeMode(m_Tab.GetCurSel(),0);
	m_CurMode=m_Tab.GetCurSel();
	m_Combo.SetCurSel(0);
	if(pResult) *pResult = 0;
}

void CMenuSetup::UpdateToolbar()
{
	CString str;
	str.Format("Toolbar%d",m_MenuList[m_CurComboSel].m_nIDResource);
	LoadToolbarState(*m_pToolBar, str);
	m_ToolBarList[m_CurComboSel].m_Loaded=TRUE;
}

void CMenuSetup::OnCancel() 
{
	int i,n;
	UINT nID,val;
	CString str1,str2;
	n=m_ToolBarList.GetSize();
	for(i=0;i<n;i++)
	{
		if (m_ToolBarList[i].m_bModified)
		{
			m_ToolBarList[i].m_bModified=FALSE;
			str1.Format("Toolbar%d",m_ToolBarList[i].m_nIDResource);
			int nn=m_ToolBarList[i].m_IDs.GetSize();
			for (int j=0;j<nn;j++)
			{
				nID=m_ToolBarList[i].m_IDs[j]&0xFFFF;
				val=m_ToolBarList[i].m_IDs[j]>>16;
				str2.Format("ID_%d",nID);
				AfxGetApp()->WriteProfileInt(str1,str2,val);
			}
		}
	}
	n=m_MenuList.GetSize();
	for(i=0;i<n;i++)
	{
		if (m_MenuList[i].m_bModified)
		{
			m_MenuList[i].m_bModified=FALSE;
			str1.Format("Menu%d",m_MenuList[i].m_nIDResource);
			int nn=m_MenuList[i].m_IDs.GetSize();
			for (int j=0;j<nn;j++)
			{
				nID=m_MenuList[i].m_IDs[j]&0xFFFF;
				val=m_MenuList[i].m_IDs[j]>>16;
				str2.Format("ID_%d",nID);
				AfxGetApp()->WriteProfileInt(str1,str2,val);
			}
		}
	}
	
	CDialog::OnCancel();
}
