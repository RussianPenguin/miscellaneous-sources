// TabFileView.cpp : implementation of the CTabFileView class
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
// CTabFileView

IMPLEMENT_DYNCREATE(CTabFileView, CTreeView)

BEGIN_MESSAGE_MAP(CTabFileView, CTreeView)
	//{{AFX_MSG_MAP(CTabFileView)
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
// CTabFileView construction/destruction

CTabFileView::CTabFileView()
{
	m_pTreeCtrl = NULL;

	// TODO: add construction code here

}

CTabFileView::~CTabFileView()
{
	m_ImageList.DeleteImageList();

	// TODO: add cleanup code here

}

BOOL CTabFileView::PreCreateWindow(CREATESTRUCT& cs)
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
// CTabFileView drawing

void CTabFileView::OnDraw(CDC* pDC)
{
	CTabFileDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

void CTabFileView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

	// TODO: You may populate your TreeView with items by directly accessing
	//  its tree control through a call to GetTreeCtrl().

}

/////////////////////////////////////////////////////////////////////////////
// CTabFileView printing

BOOL CTabFileView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTabFileView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTabFileView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CTabFileView diagnostics

#ifdef _DEBUG
void CTabFileView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CTabFileView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

CTabFileDoc* CTabFileView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTabFileDoc)));
	return (CTabFileDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTabFileView message handlers

void CTabFileView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class

}

void CTabFileView::UpdateView()
{
	if( m_pTreeCtrl && m_pTreeCtrl->GetSafeHwnd( ))
	{
		m_pTreeCtrl->LockWindowUpdate();
		
		CString strTreeItems[] = { _T("Workspace 'demo': 1 project(s)"), _T("Tab files"), _T("File Folder") };
		
		// add the parent item, make it bold
		HTREEITEM htiParent = m_pTreeCtrl->InsertItem (strTreeItems[0]);
		HTREEITEM htiChild; // child item
		
		htiChild = m_pTreeCtrl->InsertItem (strTreeItems[1], 1, 1, htiParent, TVI_LAST);
		m_pTreeCtrl->SetItemState (htiChild, TVIS_BOLD, TVIS_BOLD);
		
		// add the children of the parent item
		for (int i = 1; i < 4; i++) {
			m_pTreeCtrl->InsertItem (strTreeItems[2], 2, 3, htiChild, TVI_LAST);
		}
		
		m_pTreeCtrl->Expand (htiParent, TVE_EXPAND);
		m_pTreeCtrl->Expand (htiChild, TVE_EXPAND);
		
		m_pTreeCtrl->UnlockWindowUpdate();
	}
}

BOOL CTabFileView::OnEraseBkgnd(CDC* pDC) 
{
	UNUSED_ALWAYS(pDC);
	return TRUE;
}

void CTabFileView::OnPaint() 
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

UINT CTabFileView::OnNcHitTest(CPoint point) 
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

int CTabFileView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CTreeView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// Create the image list used by the tree control.
	if (!m_ImageList.Create(IDB_IL_FILE, 16, 1, RGB(0,255,0)))
		return -1;
	
	// Get a pointer to the tree control, and set its imagelist.
	m_pTreeCtrl = &GetTreeCtrl();
	m_pTreeCtrl->SetImageList(&m_ImageList, TVSIL_NORMAL);

	// Initialize the view.
	UpdateView();

	// TODO: Add your specialized creation code here
	
	return 0;
}
