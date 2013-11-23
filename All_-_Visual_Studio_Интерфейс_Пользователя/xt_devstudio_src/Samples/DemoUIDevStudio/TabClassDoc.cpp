// TabClassDoc.cpp : implementation of the CTabClassDoc class
//

#include "stdafx.h"
#include "DemoUIDevStudio.h"

#include "TabClassDoc.h"
#include "TabClassView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTabClassDoc

IMPLEMENT_DYNCREATE(CTabClassDoc, CDocument)

BEGIN_MESSAGE_MAP(CTabClassDoc, CDocument)
	//{{AFX_MSG_MAP(CTabClassDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTabClassDoc construction/destruction

CTabClassDoc::CTabClassDoc()
{
	// TODO: add one-time construction code here

}

CTabClassDoc::~CTabClassDoc()
{
}

BOOL CTabClassDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CTabClassDoc serialization

void CTabClassDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CTabClassDoc diagnostics

#ifdef _DEBUG
void CTabClassDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTabClassDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTabClassDoc commands

void CTabClassDoc::UpdateTabView()
{
	if(!m_viewList.IsEmpty()) {
		((CTabClassView*)m_viewList.GetHead())->UpdateView();
	}
}
