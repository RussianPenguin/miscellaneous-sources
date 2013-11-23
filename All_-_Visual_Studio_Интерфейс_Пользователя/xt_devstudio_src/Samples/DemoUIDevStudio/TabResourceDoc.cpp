// TabResourceDoc.cpp : implementation of the CTabResourceDoc class
//

#include "stdafx.h"
#include "DemoUIDevStudio.h"

#include "TabResourceDoc.h"
#include "TabResourceView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTabResourceDoc

IMPLEMENT_DYNCREATE(CTabResourceDoc, CDocument)

BEGIN_MESSAGE_MAP(CTabResourceDoc, CDocument)
	//{{AFX_MSG_MAP(CTabResourceDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTabResourceDoc construction/destruction

CTabResourceDoc::CTabResourceDoc()
{
	// TODO: add one-time construction code here

}

CTabResourceDoc::~CTabResourceDoc()
{
}

BOOL CTabResourceDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CTabResourceDoc serialization

void CTabResourceDoc::Serialize(CArchive& ar)
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
// CTabResourceDoc diagnostics

#ifdef _DEBUG
void CTabResourceDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTabResourceDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTabResourceDoc commands

void CTabResourceDoc::UpdateTabView()
{
	if(!m_viewList.IsEmpty()) {
		((CTabResourceView*)m_viewList.GetHead())->UpdateView();
	}
}
