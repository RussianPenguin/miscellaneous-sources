// DemoUIDevStudio.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "DemoUIDevStudio.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "DemoUIDevStudioDoc.h"
#include "DemoUIDevStudioView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDemoUIDevStudioApp

BEGIN_MESSAGE_MAP(CDemoUIDevStudioApp, CWinApp)
	//{{AFX_MSG_MAP(CDemoUIDevStudioApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(IDC_TIPOFTHEDAY, OnTipoftheday)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDemoUIDevStudioApp construction

CDemoUIDevStudioApp::CDemoUIDevStudioApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CDemoUIDevStudioApp object

CDemoUIDevStudioApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CDemoUIDevStudioApp initialization

BOOL CDemoUIDevStudioApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Codejock.com Software"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_DEMOUITYPE,
		RUNTIME_CLASS(CDemoUIDevStudioDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CDemoUIDevStudioView));
	AddDocTemplate(pDocTemplate);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	{
		// Restore the frame size and window position.
		CMainFrame* pFrameWnd = (CMainFrame*)m_pMainWnd;
		pFrameWnd->m_wndPos.LoadWindowPos(pFrameWnd);
		m_nCmdShow = pFrameWnd->m_wndPos.showCmd;
	}

	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	// This method handles the 'Tip of the Day' component.
	ShowTipAtStartup();

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CXTHyperLink m_txtURL;
	CXTHyperLink m_txtEmail;
	CStatic		 m_txtVersion;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Control(pDX, IDC_TXT_URL, m_txtURL);
	DDX_Control(pDX, IDC_TXT_EMAIL, m_txtEmail);
	DDX_Control(pDX, IDC_TXT_VERSION, m_txtVersion);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// Set the default font for child items.
	_xtAfxChangeWindowFont(this, &xtAfxData.font);
	
	// Set the bold font for the version text and.
	m_txtVersion.SetFont(&xtAfxData.fontBold);

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

// App command to run the dialog
void CDemoUIDevStudioApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CDemoUIDevStudioApp message handlers

void CDemoUIDevStudioApp::ShowTipAtStartup()
{
	// This method handles the 'Tip of the Day' component.
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
	if (cmdInfo.m_bShowSplash)
	{
		CXTTipOfTheDay dlg;
		if (dlg.m_bStartup)
			dlg.DoModal();
	}
}

void CDemoUIDevStudioApp::OnTipoftheday() 
{
	// This method handles the 'Tip of the Day' component.
	CXTTipOfTheDay dlg;
	dlg.DoModal();
}
