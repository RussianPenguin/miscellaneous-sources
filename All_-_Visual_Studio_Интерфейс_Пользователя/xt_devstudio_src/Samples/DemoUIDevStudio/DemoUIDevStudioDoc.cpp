// DemoUIDevStudioDoc.cpp : implementation of the CDemoUIDevStudioDoc class
//

#include "stdafx.h"
#include "DemoUIDevStudio.h"

#include "DemoUIDevStudioDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDemoUIDevStudioDoc

IMPLEMENT_DYNCREATE(CDemoUIDevStudioDoc, CDocument)

BEGIN_MESSAGE_MAP(CDemoUIDevStudioDoc, CDocument)
	//{{AFX_MSG_MAP(CDemoUIDevStudioDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDemoUIDevStudioDoc construction/destruction

CDemoUIDevStudioDoc::CDemoUIDevStudioDoc()
{
	// TODO: add one-time construction code here

}

CDemoUIDevStudioDoc::~CDemoUIDevStudioDoc()
{
}

BOOL CDemoUIDevStudioDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDemoUIDevStudioDoc serialization

void CDemoUIDevStudioDoc::Serialize(CArchive& ar)
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
// CDemoUIDevStudioDoc diagnostics

#ifdef _DEBUG
void CDemoUIDevStudioDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDemoUIDevStudioDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDemoUIDevStudioDoc commands
