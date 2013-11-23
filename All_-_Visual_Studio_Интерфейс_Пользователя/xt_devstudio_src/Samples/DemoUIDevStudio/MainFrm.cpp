// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "DemoUIDevStudio.h"
#include "MainFrm.h"

#include "TabClassDoc.h"
#include "TabClassView.h"
#include "TabFileDoc.h"
#include "TabFileView.h"
#include "TabResourceDoc.h"
#include "TabResourceView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CXTMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CXTMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CLOSE()
	ON_WM_CREATE()
	ON_COMMAND(ID_SAVE_ALL, OnDoNothing)
	ON_COMMAND(ID_WORKSPACE, OnWorkspace)
	ON_COMMAND(ID_OUTPUT, OnOutput)
	ON_UPDATE_COMMAND_UI(ID_WORKSPACE, OnUpdateWorkspace)
	ON_UPDATE_COMMAND_UI(ID_OUTPUT, OnUpdateOutput)
	ON_COMMAND(ID_REDO, OnDoNothing)
	ON_COMMAND(ID_UNDO, OnDoNothing)
	ON_COMMAND(ID_WINDOW_LIST, OnDoNothing)
	ON_COMMAND(ID_FIND_IN_FILES, OnDoNothing)
	ON_COMMAND(ID_COMPILE, OnDoNothing)
	ON_COMMAND(ID_BUILD, OnDoNothing)
	ON_COMMAND(ID_STOP_BUILD, OnDoNothing)
	ON_COMMAND(ID_EXECUTE_PROG, OnDoNothing)
	ON_COMMAND(ID_GO, OnDoNothing)
	ON_COMMAND(ID_INSERT_BREAK, OnDoNothing)
	ON_COMMAND(ID_SEARCH, OnSearch)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
	m_TabImages.DeleteImageList();
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CXTMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// Create the menu bar.
	if (!m_wndMenuBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndMenuBar.LoadMenuBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create menubar\n");
		return -1;      // fail to create
	}
	
	// Create the "Standard" toolbar.
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CLIPCHILDREN | WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	// Create the "Build" toolbar.
	if (!m_wndBuildBar.CreateEx(this, TBSTYLE_FLAT, WS_CLIPCHILDREN | WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC, CRect(0,0,0,0), ID_VIEW_BUILDBAR) ||
		!m_wndBuildBar.LoadToolBar(IDR_BUILDBAR))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;		// fail to create
	}

	// Create the "Output" docking window.
	if( !m_wndOutputBar.Create(this, ID_VIEW_OUTPUTBAR, _T("Output"),
		CSize(150, 150), CBRS_BOTTOM ))
	{
		TRACE0("Failed to create output dock window\n");
		return -1;		// fail to create
	}

	// Create the "Workspace" docking window.
	if( !m_wndWrkspBar.Create(this, ID_VIEW_WORKSPACEBAR, _T("Workspace"),
		CSize(225,100), CBRS_LEFT ))
	{
		TRACE0("Failed to create workspace dock window\n");
		return -1;		// fail to create
	}

	// Create the combo box control to be inserted into the Standard toolbar.
	if (!m_wndComboFind.Create( WS_CHILD|WS_VISIBLE|CBS_DROPDOWN|WS_CLIPCHILDREN,
		CRect(0,0,140,150), &m_wndToolBar, ID_FIND ))
	{
		TRACE0("Failed to create combo box.\n");
		return -1;      // fail to create
	}

	// Create the combo box control to be inserted into the Build toolbar.
	if (!m_wndComboProj.Create( WS_CHILD|WS_VISIBLE|CBS_DROPDOWNLIST|WS_CLIPCHILDREN,
		CRect(0,0,140,150), &m_wndBuildBar, ID_ACTIVE_PROJECT ))
	{
		TRACE0("Failed to create combo box.\n");
		return -1;      // fail to create
	}

	// Create the combo box control to be inserted into the Build toolbar.
	if (!m_wndComboConf.Create( WS_CHILD|WS_VISIBLE|CBS_DROPDOWNLIST|WS_CLIPCHILDREN,
		CRect(0,0,140,150), &m_wndBuildBar, ID_ACTIVE_CONFIG ))
	{
		TRACE0("Failed to create combo box.\n");
		return -1;      // fail to create
	}

	// Create the image list to use with the tab control
	if (!m_TabImages.Create( IDB_IL_TAB, 16, 1, RGB( 0,255,0 )))
	{
		TRACE0("Failed to create image list.\n");
		return -1;
	}

	// Create the status bar.
	if (!m_wndStatusBar.Create(this) || 
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// Add views to the tabbed "Workspace" docking window..
	m_wndWrkspBar.AddView(_T("Class"),
		RUNTIME_CLASS(CTabClassView), new CTabClassDoc);
	m_wndWrkspBar.AddView(_T("Resource"), 
		RUNTIME_CLASS(CTabResourceView), new CTabResourceDoc);
	m_wndWrkspBar.AddView(_T("File"),
		RUNTIME_CLASS(CTabFileView), new CTabFileDoc);

	// Set the image list for the tabbed "Workspace" docking window..
	m_wndWrkspBar.SetTabImageList( &m_TabImages );

	// Add drop down arrows to the Standard tooblar.
	m_wndToolBar.AddDropDownButton(ID_UNDO);
	m_wndToolBar.AddDropDownButton(ID_REDO);

	// Insert the combo boxes into the toolbars.
	m_wndToolBar.InsertControl(&m_wndComboFind);
	m_wndBuildBar.InsertControl(&m_wndComboProj);
	m_wndBuildBar.InsertControl(&m_wndComboConf);

	// Disable toolbar customization for toolbars.
	m_wndToolBar.SetCustomBar(FALSE);
	m_wndBuildBar.SetCustomBar(FALSE);

	// Set the toolbar titles.
	m_wndToolBar.SetWindowText(_T("Standard"));
	m_wndBuildBar.SetWindowText(_T("Build"));

	// Add strings to the combo boxes and set the selection.
	m_wndComboFind.AddString(_T("m_wndComboBox"));
	m_wndComboFind.SetCurSel(0);

	m_wndComboProj.AddString(_T("DemoUIDevStudio"));
	m_wndComboProj.SetCurSel(0);

	m_wndComboConf.AddString(_T("Win32 Release"));
	m_wndComboConf.AddString(_T("Win32 Debug"));
	m_wndComboConf.SetCurSel(0);

	// Set the font for the first combo box to be bold. When a control is
	// inserted into a toolbar, the font is automatically set to the library
	// default, to set the font to something other than the library defaults,
	// you will need to do it after the call to InsertControl has been made.
	m_wndComboFind.SetFont(&xtAfxData.fontBold);

	m_wndMenuBar.EnableDockingEx(CBRS_ALIGN_ANY, CBRS_XT_TWOGRIP);
	m_wndToolBar.EnableDockingEx(CBRS_ALIGN_ANY, CBRS_XT_TWOGRIP);
	m_wndBuildBar.EnableDockingEx(CBRS_ALIGN_ANY, CBRS_XT_TWOGRIP);
	m_wndWrkspBar.EnableDockingEx(CBRS_ALIGN_ANY, CBRS_XT_TWOGRIP);
	m_wndOutputBar.EnableDockingEx(CBRS_ALIGN_ANY, CBRS_XT_TWOGRIP);

	EnableDocking(CBRS_ALIGN_ANY);

	DockControlBar(&m_wndMenuBar);
	DockControlBar(&m_wndToolBar);
	DockControlBar(&m_wndBuildBar);
	DockControlBar(&m_wndWrkspBar);
	DockControlBar(&m_wndOutputBar);

	// TODO: Remove this line if you don't want cool menus.
	InstallCoolMenus(IDR_MAINFRAME);

	// Restore the control bar size and window position.
	LoadBarState(_T("Bar State"));
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CXTMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;

	cs.lpszClass = AfxRegisterWndClass( 0, NULL, NULL,
		AfxGetApp()->LoadIcon(IDR_MAINFRAME));

	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.style &= ~FWS_ADDTOTITLE;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CXTMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CXTMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


void CMainFrame::OnClose() 
{
	// Save the frame size and window position.
	m_wndPos.SaveWindowPos(this);

	// Save the control bar size and window position.
	SaveBarState(_T("Bar State"));

	// TODO: Add your message handler code here and/or call default
	
	CXTMDIFrameWnd::OnClose();
}

void CMainFrame::OnDoNothing() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnWorkspace() 
{
	ShowControlBar(&m_wndWrkspBar, !m_wndWrkspBar.IsWindowVisible(), FALSE);
}

void CMainFrame::OnUpdateWorkspace(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_wndWrkspBar.IsWindowVisible());
}

void CMainFrame::OnOutput() 
{
	ShowControlBar(&m_wndOutputBar, !m_wndOutputBar.IsWindowVisible(), FALSE);
}

void CMainFrame::OnUpdateOutput(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_wndOutputBar.IsWindowVisible());
}

void CMainFrame::OnSearch() 
{
	// TODO: Add your command handler code here
	
}
