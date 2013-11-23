// TabFileDoc.cpp : implementation of the CTabFileDoc class
//

#include "stdafx.h"
#include "DemoUIDevStudio.h"

#include "TabFileDoc.h"
#include "TabFileView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTabFileDoc

IMPLEMENT_DYNCREATE(CTabFileDoc, CDocument)

BEGIN_MESSAGE_MAP(CTabFileDoc, CDocument)
	//{{AFX_MSG_MAP(CTabFileDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTabFileDoc construction/destruction

CTabFileDoc::CTabFileDoc()
{
	// TODO: add one-time construction code here

}

CTabFileDoc::~CTabFileDoc()
{
}

BOOL CTabFileDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CTabFileDoc serialization

void CTabFileDoc::Serialize(CArchive& ar)
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
// CTabFileDoc diagnostics

#ifdef _DEBUG
void CTabFileDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTabFileDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTabFileDoc commands

void CTabFileDoc::UpdateTabView()
{
	if(!m_viewList.IsEmpty()) {
		((CTabFileView*)m_viewList.GetHead())->UpdateView();
	}
}
