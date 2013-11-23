// TabResourceView.cpp : implementation of the CTabResourceView class
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
// CTabResourceView

IMPLEMENT_DYNCREATE(CTabResourceView, CTreeView)

BEGIN_MESSAGE_MAP(CTabResourceView, CTreeView)
	//{{AFX_MSG_MAP(CTabResourceView)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_NCHITTEST()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CTreeView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CTreeView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CTreeView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTabResourceView construction/destruction

CTabResourceView::CTabResourceView()
{
	m_pTreeCtrl = NULL;

	// TODO: add construction code here

}

CTabResourceView::~CTabResourceView()
{
	m_ImageList.DeleteImageList();

	// TODO: add cleanup code here

}

BOOL CTabResourceView::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CTreeView::PreCreateWindow( cs ))
		return FALSE;

	// Set the style for the tree control.
	cs.style |= TVS_HASBUTTONS|TVS_HASLINES|TVS_LINESATROOT|TVS_EDITLABELS;

	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CTabResourceView drawing

void CTabResourceView::OnDraw(CDC* pDC)
{
	CTabResourceDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

void CTabResourceView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

	// TODO: You may populate your TreeView with items by directly accessing
	//  its tree control through a call to GetTreeCtrl().

}

/////////////////////////////////////////////////////////////////////////////
// CTabResourceView printing

BOOL CTabResourceView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTabResourceView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTabResourceView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CTabResourceView diagnostics

#ifdef _DEBUG
void CTabResourceView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CTabResourceView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

CTabResourceDoc* CTabResourceView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTabResourceDoc)));
	return (CTabResourceDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTabResourceView message handlers

void CTabResourceView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class

}

void CTabResourceView::UpdateView()
{
	if( m_pTreeCtrl && m_pTreeCtrl->GetSafeHwnd( ))
	{
		m_pTreeCtrl->LockWindowUpdate();
		
		CString strTreeItems[] = { _T("Tab resources"), _T("Accelerator"), _T("Bitmap"), _T("Dialog"), _T("Icon"), _T("Menu"), _T("String Table"), _T("Toolbar"), _T("Version") };
		
		// add the parent item
		HTREEITEM htItem = m_pTreeCtrl->InsertItem (strTreeItems[0], 1, 1);
		m_pTreeCtrl->SetItemState (htItem, TVIS_BOLD, TVIS_BOLD);
		
		// add children items
		for (int i = 1; i < 9; i++) {
			m_pTreeCtrl->InsertItem (strTreeItems[i], 0, 1, htItem, TVI_LAST);
		}
		
		m_pTreeCtrl->Expand (htItem, TVE_EXPAND);
		
		m_pTreeCtrl->UnlockWindowUpdate();
	}
}

BOOL CTabResourceView::OnEraseBkgnd(CDC* pDC) 
{
	UNUSED_ALWAYS(pDC);
	return TRUE;
}

void CTabResourceView::OnPaint() 
{
	// Background is already filled in gray
	CPaintDC dc(this);

	// Get the client rect.
	CRect rectClient;
	GetClientRect(&rectClient);

	// Paint to a memory device context to help
	// eliminate screen flicker.
	CXTMemDC memDC(this, &dc, rectClient);

	// Let the window do its default painting.
	CWnd::DefWindowProc( WM_PAINT, (WPARAM)memDC.m_hDC, 0 );
}

UINT CTabResourceView::OnNcHitTest(CPoint point) 
{
	UINT uFlag=0;

	// Get the cursor location in client coordinates.
	CPoint pt = point;	
	ScreenToClient(&pt);

	// Get a pointer to the tooltip control.
	CToolTipCtrl* pCtrl = m_pTreeCtrl->GetToolTips();

	// If we have a valid tooltip pointer and the cursor
	// is over a tree item, the bring the tooltip control
	// to the top of the Z-order.
	if (pCtrl && m_pTreeCtrl->HitTest(pt, &uFlag)){
		pCtrl->SetWindowPos(&wndTop,0, 0, 0, 0,
			SWP_NOACTIVATE | SWP_NOSIZE |SWP_NOMOVE);
	}
	
	return CTreeView::OnNcHitTest(point);
}

int CTabResourceView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CTreeView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// Create the image list used by the tree control.
	if (!m_ImageList.Create(IDB_IL_RSRC, 16, 1, RGB(0,255,0)))
		return -1;
	
	// Get a pointer to the tree control, and set its imagelist.
	m_pTreeCtrl = &GetTreeCtrl();
	m_pTreeCtrl->SetImageList(&m_ImageList, TVSIL_NORMAL);

	// Initialize the view.
	UpdateView();

	// TODO: Add your specialized creation code here
	
	return 0;
}
