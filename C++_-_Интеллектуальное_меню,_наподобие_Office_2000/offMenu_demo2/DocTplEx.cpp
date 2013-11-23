// DocTplEx.cpp : implementation file
//

#include "stdafx.h"
#include "DocTplEx.h"
#include "MDIFrmEx.h"
#include "WinAppEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMultiDocTemplateEx

IMPLEMENT_DYNAMIC(CMultiDocTemplateEx, CMultiDocTemplate)

CMultiDocTemplateEx::CMultiDocTemplateEx( UINT nIDResource, 
						 CRuntimeClass* pDocClass, CRuntimeClass* pFrameClass, 
						 CRuntimeClass* pViewClass ,UINT *arID,int n):
						 CMultiDocTemplate(nIDResource,pDocClass,pFrameClass,pViewClass),
						 m_mnuDocMenu(FALSE,TRUE)
{
	// Load the menu from the resources
	m_nIDResource=nIDResource;
    m_mnuDocMenu.LoadMenu(nIDResource);

	if (arID && n>0) m_mnuDocMenu.LoadToolbars(arID,n);
		else m_mnuDocMenu.LoadToolbar(nIDResource);
	
	SetMenuToolbars(arID,n);

	if (nIDResource != 0 && m_hMenuShared == NULL)
	{
		m_hMenuShared = m_mnuDocMenu.GetSafeHmenu();
		m_hAccelTable =
			::LoadAccelerators(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(nIDResource));
	}

}

CMultiDocTemplateEx::~CMultiDocTemplateEx()
{
	CString strTmp;
	strTmp.Format("Menu%d",m_nIDResource);
	((CWinAppEx*)AfxGetApp())->SaveMenuChanges(&m_mnuDocMenu,strTmp);
}


/////////////////////////////////////////////////////////////////////////////
// CMultiDocTemplateEx diagnostics

#ifdef _DEBUG
void CMultiDocTemplateEx::AssertValid() const
{
	CMultiDocTemplate::AssertValid();
}

void CMultiDocTemplateEx::Dump(CDumpContext& dc) const
{
	CMultiDocTemplate::Dump(dc);
}
#endif //_DEBUG


void CMultiDocTemplateEx::LoadTemplate()
{
	CDocTemplate::LoadTemplate();
}

CFrameWnd* CMultiDocTemplateEx::CreateNewFrame(CDocument *pDoc, CFrameWnd *pOther)
{
	CMDIChildHook *pHookFrame;

	CFrameWnd* pFrame=CMultiDocTemplate::CreateNewFrame(pDoc, pOther);
	CMDIFrameEx* pMainFrame=(CMDIFrameEx*)AfxGetMainWnd();
	ASSERT(pMainFrame->IsKindOf(RUNTIME_CLASS(CMDIFrameEx)));
	if(pFrame && pFrame->IsKindOf(RUNTIME_CLASS(CMDIChildWnd))) 
	{
		pHookFrame=new CMDIChildHook;
		ASSERT(pHookFrame);
		pHookFrame->Install(pMainFrame->GetMenuBar(), pFrame->GetSafeHwnd());
	}
	return pFrame;
}

CMenuEx* CMultiDocTemplateEx::GetMenu()
{
	return &m_mnuDocMenu;
}

void CMultiDocTemplateEx::LoadMenuToolBars()
{
	if (m_arID.GetSize()) m_mnuDocMenu.LoadToolbars(m_arID.GetData(),m_arID.GetSize());
		else m_mnuDocMenu.LoadToolbar(m_nIDResource);
}

void CMultiDocTemplateEx::SetMenuToolbars(UINT *arID, int n)
{
	m_arID.SetSize(n);
	for(int i=0;i<n;i++)
		m_arID[i]=arID[i];
}
