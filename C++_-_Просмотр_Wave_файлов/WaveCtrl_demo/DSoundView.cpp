// DSoundView.cpp : implementation of the CDSoundView class
//

#include "stdafx.h"
#include "DSound.h"

#include "DSoundDoc.h"
#include "DSoundView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDSoundView

IMPLEMENT_DYNCREATE(CDSoundView, CView)

BEGIN_MESSAGE_MAP(CDSoundView, CView)
	//{{AFX_MSG_MAP(CDSoundView)
	ON_WM_SIZE()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_COMMAND_RANGE(ID_COMMAND_PLAY,ID_COMMAND_STOP,OnCommandPlay)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDSoundView construction/destruction

CDSoundView::CDSoundView()
{
	// TODO: add construction code here
	memset(&m_text,-1,sizeof(TEXTMETRIC));
	dr=false;
	create=false;
}

CDSoundView::~CDSoundView()
{
}

BOOL CDSoundView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDSoundView drawing
void CDSoundView::OnDraw(CDC* pDC)
{
	CDSoundDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}

/////////////////////////////////////////////////////////////////////////////
// CDSoundView printing

BOOL CDSoundView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDSoundView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDSoundView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CDSoundView diagnostics

#ifdef _DEBUG
void CDSoundView::AssertValid() const
{
	CView::AssertValid();
}

void CDSoundView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDSoundDoc* CDSoundView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDSoundDoc)));
	return (CDSoundDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDSoundView message handlers



void CDSoundView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	Invalidate();
}


BOOL CDSoundView::OnScroll(UINT nScrollCode, UINT nPos, BOOL bDoScroll) 
{
	// TODO: Add your specialized code here and/or call the base class
	Invalidate();
	
	return CView::OnScroll(nScrollCode, nPos, bDoScroll);
}

void CDSoundView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	CDSoundDoc* pDoc = GetDocument();

	CRect rect;
	GetClientRect(&rect);
	pDoc->m_wave->Create(WS_VISIBLE | WS_CHILD, rect, this, 1000);
	create=true;
	
}

void CDSoundView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	CRect rect;
	GetClientRect(&rect);
	DWORD siz=0;
	siz=(WORD)cy;//(rect.Height ());
	siz=siz<<16;
	siz=siz|(WORD)cx;
	// TODO: Add your message handler code here
	CDSoundDoc* pDoc = GetDocument();
	
	
	if(create)
		pDoc->m_wave->MoveWindow(0,0 , rect.Width (), rect.Height () ,true);
	
}

void CDSoundView::OnSetFocus(CWnd* pOldWnd) 
{
	CView::OnSetFocus(pOldWnd);
	
	// TODO: Add your message handler code here
	CDSoundDoc* pDoc = GetDocument();
	if(create)
		pDoc->m_wave->PostMessage(WM_SETFOCUS,NULL,NULL);
}

void CDSoundView::OnKillFocus(CWnd* pNewWnd) 
{
	CView::OnKillFocus(pNewWnd);
	CDSoundDoc* pDoc = GetDocument();
	if(create)
		pDoc->m_wave->PostMessage(WM_KILLFOCUS,NULL,NULL);
	
	// TODO: Add your message handler code here
	
}

void CDSoundView::OnCommandPlay(UINT nIndex) 
{
	// TODO: Add your command handler code here
	CDSoundDoc* pDoc = GetDocument();
	if(nIndex==ID_COMMAND_PLAY)
		pDoc->m_wave->Command();
	else
		pDoc->m_wave->Command(false);

}
