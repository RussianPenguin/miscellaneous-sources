// ToolBarEx.cpp : implementation file
//

#include "stdafx.h"
#include "ToolBarEx.h"
#include "MDIFrmEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC( CToolbarEx, CToolBar );

/////////////////////////////////////////////////////////////////////////////
// CToolbarEx

CToolbarEx::CToolbarEx()
{
	m_nIDResource=0;
}

CToolbarEx::~CToolbarEx()
{
}


BEGIN_MESSAGE_MAP(CToolbarEx, CToolBar)
	//{{AFX_MSG_MAP(CToolbarEx)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CToolbarEx message handlers

BOOL CToolbarEx::LoadToolBar(UINT nIDResource)
{
	m_nIDResource=nIDResource;
	CMDIFrameEx* pFrame=(CMDIFrameEx*)AfxGetMainWnd();
	ASSERT(pFrame->IsKindOf(RUNTIME_CLASS(CMDIFrameEx)));
	pFrame->RegisterToolBar(this);
	return CToolBar::LoadToolBar(nIDResource);
}
