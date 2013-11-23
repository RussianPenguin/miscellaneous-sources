// DSoundDoc.cpp : implementation of the CDSoundDoc class
//

#include "stdafx.h"
#include "DSound.h"

#include "DSoundDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDSoundDoc

IMPLEMENT_DYNCREATE(CDSoundDoc, CDocument)

BEGIN_MESSAGE_MAP(CDSoundDoc, CDocument)
	//{{AFX_MSG_MAP(CDSoundDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDSoundDoc construction/destruction

CDSoundDoc::CDSoundDoc()
{
	// TODO: add one-time construction code here
	m_wave=new CWaveViewCtrl();

}

CDSoundDoc::~CDSoundDoc()
{
}

BOOL CDSoundDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDSoundDoc serialization

void CDSoundDoc::Serialize(CArchive& ar)
{
	m_wave->Serialize(ar);
	//ar>>m_wave;
	CObject::Serialize(ar);

	/*if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}*/
}

/////////////////////////////////////////////////////////////////////////////
// CDSoundDoc diagnostics

#ifdef _DEBUG
void CDSoundDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDSoundDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDSoundDoc commands

void CDSoundDoc::DeleteContents() 
{
	// TODO: Add your specialized code here and/or call the base class
	if(m_wave!=NULL)
		delete m_wave;
	m_wave=new CWaveViewCtrl();
	CDocument::DeleteContents();
}
