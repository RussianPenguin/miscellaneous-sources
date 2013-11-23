// DemoUIDevStudioView.cpp : implementation of the CDemoUIDevStudioView class
//

#include "stdafx.h"
#include "DemoUIDevStudio.h"

#include "DemoUIDevStudioDoc.h"
#include "DemoUIDevStudioView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDemoUIDevStudioView

IMPLEMENT_DYNCREATE(CDemoUIDevStudioView, CView)

BEGIN_MESSAGE_MAP(CDemoUIDevStudioView, CView)
	//{{AFX_MSG_MAP(CDemoUIDevStudioView)
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDemoUIDevStudioView construction/destruction

CDemoUIDevStudioView::CDemoUIDevStudioView()
{
	// TODO: add construction code here

}

CDemoUIDevStudioView::~CDemoUIDevStudioView()
{
}

BOOL CDemoUIDevStudioView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDemoUIDevStudioView drawing

void CDemoUIDevStudioView::OnDraw(CDC* pDC)
{
	CDemoUIDevStudioDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// Get the client rect.
	CRect rectClient;
	GetClientRect(&rectClient);

	// Paint to a memory device context to help
	// eliminate screen flicker.
	CXTMemDC memDC(this, pDC, rectClient, xtAfxData.clrWindow);
	
	// Paint the text...
}

/////////////////////////////////////////////////////////////////////////////
// CDemoUIDevStudioView printing

BOOL CDemoUIDevStudioView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDemoUIDevStudioView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDemoUIDevStudioView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CDemoUIDevStudioView diagnostics

#ifdef _DEBUG
void CDemoUIDevStudioView::AssertValid() const
{
	CView::AssertValid();
}

void CDemoUIDevStudioView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDemoUIDevStudioDoc* CDemoUIDevStudioView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDemoUIDevStudioDoc)));
	return (CDemoUIDevStudioDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDemoUIDevStudioView message handlers

BOOL CDemoUIDevStudioView::OnEraseBkgnd(CDC* pDC) 
{
	UNUSED_ALWAYS(pDC);
	return TRUE;
}
