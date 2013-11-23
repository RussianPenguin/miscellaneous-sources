// WinAppEx.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "WinAppEx.h"
#include "MDIFrmEx.h"
#include "DocTplEx.h"
#include "MenuSetup.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWinAppEx

IMPLEMENT_DYNCREATE(CWinAppEx, CWinApp)

CWinAppEx::CWinAppEx()
{
	m_bDrawGrayed=FALSE;
}

CWinAppEx::~CWinAppEx()
{
}

BOOL CWinAppEx::InitInstance()
{
	m_lpWndClass=AfxRegisterWndClass(CS_CLASSDC|CS_GLOBALCLASS|CS_VREDRAW|CS_HREDRAW|CS_NOCLOSE|CS_SAVEBITS,
										(HCURSOR) 0,::GetSysColorBrush(COLOR_MENU));
	BOOL bReturn=CWinApp::InitInstance();
	m_iMenuParameter=GetProfileInt("MenuParameter","Thresold",5);
	AdjustToolBars();
	CMDIFrameEx* pFrame=(CMDIFrameEx*)m_pMainWnd;
	ASSERT (pFrame->IsKindOf(RUNTIME_CLASS(CMDIFrameEx)));
	CString strTmp;
	CMenuEx* pMenu=pFrame->GetMainMenu();
	if (pMenu)
	{
		strTmp.Format("Menu%d",pFrame->m_nIDResource);
		SetupMenu(pMenu,strTmp);
		pFrame->RefreshMenuBar(pMenu,pFrame->GetWindowMenuPopup(pMenu));
	}
	POSITION pos;
	pos=GetFirstDocTemplatePosition();
	while(pos)
	{
		CMultiDocTemplateEx* pTemplate=(CMultiDocTemplateEx*)GetNextDocTemplate(pos);
		ASSERT(pTemplate->IsKindOf(RUNTIME_CLASS(CMultiDocTemplateEx)));
		CMenuEx* pMenu=pTemplate->GetMenu();
		if (pMenu)
		{
			strTmp.Format("Menu%d",pTemplate->m_nIDResource);
			SetupMenu(pMenu,strTmp);
		}
	}
	pFrame->PostMessage(WM_ACTIVATE,WA_ACTIVE,0);
	AfxGetApp()->DoWaitCursor(-1);
	return bReturn;
}

int CWinAppEx::ExitInstance()
{
	return CWinApp::ExitInstance();
}

BEGIN_MESSAGE_MAP(CWinAppEx, CWinApp)
	//{{AFX_MSG_MAP(CWinAppEx)
	ON_COMMAND(IDM_MENU, OnMenuSetup)
	ON_COMMAND(ID_SHOWFULL, OnShowfull)
	ON_UPDATE_COMMAND_UI(ID_FILE_MRU_FILE1, OnUpdateRecentFileMenu)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWinAppEx message handlers

void CWinAppEx::OnMenuSetup() 
{
	CMenuSetup dlg(AfxGetMainWnd());
	CMDIFrameEx* pFrame=(CMDIFrameEx*)AfxGetMainWnd();
	ASSERT (pFrame->IsKindOf(RUNTIME_CLASS(CMDIFrameEx)));
	CString strTmp;
	
	dlg.m_MenuList.SetSize(1);
	dlg.m_MenuList[0].m_nIDResource=pFrame->m_nIDResource;
	dlg.m_MenuList[0].m_MenuName=m_pszAppName;
	CMenuEx* pMenu=pFrame->GetMainMenu();
	if (pMenu)
	{
		strTmp.Format("Menu%d",pFrame->m_nIDResource);
		SaveMenuChanges(pMenu,strTmp);
	}
	UINT n=2;
	POSITION pos;
	pos=GetFirstDocTemplatePosition();
	CMultiDocTemplateEx* pTemplate;
	while(pos)
	{
		pTemplate=(CMultiDocTemplateEx*)GetNextDocTemplate(pos);
		ASSERT(pTemplate->IsKindOf(RUNTIME_CLASS(CMultiDocTemplateEx)));
		dlg.m_MenuList.SetSize(n);
		dlg.m_MenuList[n-1].m_nIDResource=pTemplate->m_nIDResource;
		pTemplate->GetDocString(dlg.m_MenuList[n-1].m_MenuName,CDocTemplate::regFileTypeName);
		n++;
		CMenuEx* pMenu=pTemplate->GetMenu();
		if (pMenu)
		{
			strTmp.Format("Menu%d",pTemplate->m_nIDResource);
			SaveMenuChanges(pMenu,strTmp);
		}
	}
	n=pFrame->m_ToolBarList.GetSize();
	dlg.m_ToolBarList.SetSize(n);
	CToolbarEx* pBar;
	for(UINT i=0;i<n;i++)
	{
		pBar=pFrame->m_ToolBarList[i];
		if (pBar)
		{
			dlg.m_ToolBarList[i].m_nIDResource=pBar->m_nIDResource;
			dlg.m_ToolBarList[i].m_MenuName.Format("ToolBar #%d",i+1);
		}
	}

	if(dlg.DoModal()==IDOK)	OnMenuSilent();
}

void CWinAppEx::OnMenuSilent()
{
	AdjustToolBars();
	CMenuEx TmpMenu;
	CMDIFrameEx* pFrame=(CMDIFrameEx*)AfxGetMainWnd();
	ASSERT (pFrame->IsKindOf(RUNTIME_CLASS(CMDIFrameEx)));
	pFrame->EnableMenuChange(FALSE);
	CString strTmp;
	CMenuEx* pMenu=pFrame->GetMainMenu();
	if (pMenu)
	{
		strTmp.Format("Menu%d",pFrame->m_nIDResource);
		pMenu->DestroyMenu();
		pMenu->LoadMenu(pFrame->m_nIDResource);
		SetupMenu(pMenu,strTmp);
		pFrame->LoadMenuToolBars();
	}
	POSITION pos;
	pos=GetFirstDocTemplatePosition();
	while(pos)
	{
		CMultiDocTemplateEx* pTemplate=(CMultiDocTemplateEx*)GetNextDocTemplate(pos);
		ASSERT(pTemplate->IsKindOf(RUNTIME_CLASS(CMultiDocTemplateEx)));
		CMenuEx* pMenu=pTemplate->GetMenu();
		if (pMenu)
		{
			strTmp.Format("Menu%d",pTemplate->m_nIDResource);
			pMenu->DestroyMenu();
			pMenu->LoadMenu(pTemplate->m_nIDResource);
			SetupMenu(pMenu,strTmp);
			pTemplate->LoadMenuToolBars();
		}
	}
	pFrame->EnableMenuChange(TRUE);
	pFrame->RefreshMenuBar(NULL,NULL);
	pFrame->PostMessage(WM_ACTIVATE,WA_ACTIVE,0);
	AfxGetApp()->DoWaitCursor(-1);
}


void CWinAppEx::AdjustToolBars()
{
	CMDIFrameEx* pFrame=(CMDIFrameEx*)m_pMainWnd;
	ASSERT (pFrame->IsKindOf(RUNTIME_CLASS(CMDIFrameEx)));
	UINT n=pFrame->m_ToolBarList.GetSize();
	CToolbarEx* pBar;
	CString  strTmp;
	for(UINT i=0;i<n;i++)
	{
		pBar=pFrame->m_ToolBarList[i];
		if (pBar)
		{
			strTmp.Format("Toolbar%d",pBar->m_nIDResource);
			SetToolBar(*(pBar), (pBar)->m_nIDResource ,strTmp);
		}
	}
}

void CWinAppEx::SetToolBar(CToolBar &ToolBar, UINT id, const char *section)
{
	CToolBarCtrl &t=ToolBar.GetToolBarCtrl();
	CString str;
	int nn;

	ToolBar.LoadToolBar(id);
	nn=t.GetButtonCount();

	UINT *tb,n;
	tb=new UINT[nn];
	UINT *ti;
	ti=new UINT[nn];
	int j=0,ns=0;
	for (int i=0;i<nn;i++)
	{
		int nID=ToolBar.GetItemID(i);
		if (nID==ID_SEPARATOR) 
		{
			ns++;
			if (j!=0 && tb[j-1]!=ID_SEPARATOR) 
			{
				tb[j]=nID; 
				ti[j]=0; 
				j++;
			} 
			continue;
		}
		else
		{
			str.Format("ID_%d",nID);
			n=GetProfileInt(section,str,0x8000);
			if (n) 
			{
				tb[j]=nID;
				ti[j]=i-ns; 
				j++;
			}
		}
	}
	if (j!=0 && tb[j-1]==ID_SEPARATOR) j--;
	ToolBar.SetButtons(tb,j);
	for(i=0;i<j;i++)
	{
		if (tb[i]!=ID_SEPARATOR)
			{ToolBar.SetButtonInfo(i,tb[i],TBBS_BUTTON,ti[i]);}
		else
			{ToolBar.SetButtonInfo(i,0,TBBS_SEPARATOR,0);}
	}
	ToolBar.CalcFixedLayout(TRUE,FALSE);
	CFrameWnd* f=ToolBar.GetDockingFrame();
	if (f) f->RecalcLayout();

	delete[]tb;
	delete[]ti;
}

CMenuEx* CWinAppEx::SetupMenu(CMenuEx *pTopMenu, const char *section)
{
	CMenuEx* pCurMenu = NULL;
	int iPos,iLastSep;
	CMenuEx* pMenu;
	int LastSep;
	int nMenu=pTopMenu->GetMenuItemCount();
	int nPrev=0; 
	LastSep=-1;
	iLastSep=-1;
	for (iPos = nMenu-1; iPos >= 0; iPos--)
	{
			if (pMenu = pTopMenu->GetSubMenu(iPos))
			{
				if (!SetupMenu(pMenu,section))
				{
					pTopMenu->DeleteMenu(iPos,MF_BYPOSITION);
					nMenu--;
					iLastSep--;
				}
				else nPrev++;
			}
			else  
			{
				UINT nID=pTopMenu->GetMenuItemID(iPos);
				if (nID==ID_SEPARATOR)
				{
					if (nPrev==0)
					{
						pTopMenu->DeleteMenu(iPos,MF_BYPOSITION);
						nMenu--;
						iLastSep--;
					}
					else 
					{
						nPrev=0;
						LastSep=iPos;
						iLastSep=iPos;
					}
				}
				else
				{
					CString str;
					str.Format("ID_%d",nID);
					UINT t;
					t=GetProfileInt(section,str,0x8000);
					if (!t) 
					{
						pTopMenu->DeleteMenu(iPos,MF_BYPOSITION);
						nMenu--;
						iLastSep--;
					}
					else
					{
						nPrev++;
						LastSep=-1;
						t&=0xffff;
						if (t<0x8000)
							pTopMenu->ModifyFlagsEx(nID,MF_DRAWGRAYED|t);
						else
							pTopMenu->ModifyFlagsEx(nID,t);
					}
				}
			}
			if (iLastSep==iPos+1)
			{
				int nFlagsEx=pTopMenu->GetFlagsEx(iLastSep+1);
				nFlagsEx&=pTopMenu->GetFlagsEx(iPos);
				if (nFlagsEx&MF_DRAWGRAYED)
					pTopMenu->ModifyODSeparator(iLastSep,MF_DRAWGRAYED);
				iLastSep=-1;
			}
	}
	if (LastSep>=0 && pTopMenu->GetMenuItemID(0)==ID_SEPARATOR) 
		pTopMenu->DeleteMenu(0,MF_BYPOSITION);
	nMenu=pTopMenu->GetMenuItemCount();
	if (nMenu>0 && pTopMenu->GetMenuItemID(nMenu-1)==ID_SEPARATOR)
	{
		pTopMenu->DeleteMenu(nMenu-1,MF_BYPOSITION);
		nMenu--;
	}
	if (nMenu==0) return NULL;
	return pTopMenu;
}

CMenuEx* CWinAppEx::SaveMenuChanges(CMenuEx *pTopMenu, const char *section)
{
	int iPos;
	CMenuEx* pMenu;
	int nMenu=pTopMenu->GetMenuItemCount();
	for (iPos = nMenu-1; iPos >= 0; iPos--)
	{
			if (pMenu = pTopMenu->GetSubMenu(iPos))
			{
				SaveMenuChanges(pMenu,section);
			}
			else  
			{
				UINT nID=pTopMenu->GetMenuItemID(iPos);
				if (nID==ID_SEPARATOR) 
					continue;
				else
				{
					CString str;
					str.Format("ID_%d",nID);
					UINT t=pTopMenu->GetFlagsEx(iPos);
					t&=0xffff;
					WriteProfileInt(section,str,t);
				}
			}
	}
	if (nMenu==0) return NULL;
	return pTopMenu;
}

void CWinAppEx::OnShowfull() 
{
	// TODO: Add your command handler code here
	
}

/////////////////////////////////////////////////////////////////////////////
// MRU file list custom implementation

void CWinAppEx::OnUpdateRecentFileMenu(CCmdUI* pCmdUI)
{
	ASSERT_VALID(this);
	if (m_pRecentFileList == NULL) // no MRU files
		pCmdUI->Enable(FALSE);
	else
	{
		ASSERT(m_pRecentFileList->m_arrNames != NULL);

		CMenuEx* pMenu = (CMenuEx*)pCmdUI->m_pMenu;
		if (m_pRecentFileList->m_strOriginal.IsEmpty() && pMenu != NULL)
			pMenu->GetMenuString(pCmdUI->m_nID, m_pRecentFileList->m_strOriginal, MF_BYCOMMAND);

		if (m_pRecentFileList->m_arrNames[0].IsEmpty())
		{
			// no MRU files
			if (!m_pRecentFileList->m_strOriginal.IsEmpty())
				pCmdUI->SetText(m_pRecentFileList->m_strOriginal);
			pCmdUI->Enable(FALSE);
			return;
		}

		if (pCmdUI->m_pMenu == NULL)
			return;

		ASSERT(pMenu->IsKindOf(RUNTIME_CLASS(CMenuEx)));

		for (int iMRU = 0; iMRU < m_pRecentFileList->m_nSize; iMRU++)
			pMenu->DeleteMenu(pCmdUI->m_nID + iMRU, MF_BYCOMMAND);

		TCHAR szCurDir[_MAX_PATH];
		GetCurrentDirectory(_MAX_PATH, szCurDir);
		int nCurDir = lstrlen(szCurDir);
		ASSERT(nCurDir >= 0);
		szCurDir[nCurDir] = '\\';
		szCurDir[++nCurDir] = '\0';

		CString strName;
		CString strTemp;
		for (iMRU = 0; iMRU < m_pRecentFileList->m_nSize; iMRU++)
		{
			if (!m_pRecentFileList->GetDisplayName(strName, iMRU, szCurDir, nCurDir))
				break;

			// double up any '&' characters so they are not underlined
			LPCTSTR lpszSrc = strName;
			LPTSTR lpszDest = strTemp.GetBuffer(strName.GetLength()*2);
			while (*lpszSrc != 0)
			{
				if (*lpszSrc == '&')
					*lpszDest++ = '&';
				if (_istlead(*lpszSrc))
					*lpszDest++ = *lpszSrc++;
				*lpszDest++ = *lpszSrc++;
			}
			*lpszDest = 0;
			strTemp.ReleaseBuffer();

			// insert mnemonic + the file name
			TCHAR buf[10];
			wsprintf(buf, _T("&%d "), (iMRU+1+m_pRecentFileList->m_nStart) % 10);
			pMenu->InsertMenu(pCmdUI->m_nIndex++,
				MF_STRING | MF_BYPOSITION, pCmdUI->m_nID++,
				CString(buf) + strTemp);
		}

		// update end menu count
		pCmdUI->m_nIndex--; // point to last menu added
		pCmdUI->m_nIndexMax = pCmdUI->m_pMenu->GetMenuItemCount();

		pCmdUI->m_bEnableChanged = TRUE;    // all the added items are enabled
		int allok=1;
		for (UINT h=0;h<pCmdUI->m_nIndexMax-1;h++)
		{
			if ((pMenu->GetFlagsEx(h)&MF_DRAWGRAYED)!=0
				&& pMenu->GetMenuItemID(h)!=ID_SEPARATOR)
			{
				allok=0;
				break;
			}
		}
		if(allok) pMenu->SetFlagsEx(pCmdUI->m_nIndexMax-1,
									pMenu->GetFlagsEx(pCmdUI->m_nIndexMax-1)|MF_DRAWGRAYED);
	}
}

