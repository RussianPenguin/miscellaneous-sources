// TimedProgressDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TimedProgress.h"
#include "TimedProgressDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
    CAboutDlg();

// Dialog Data
    //{{AFX_DATA(CAboutDlg)
    enum { IDD = IDD_ABOUTBOX };
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CAboutDlg)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:
    //{{AFX_MSG(CAboutDlg)
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
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
    //{{AFX_MSG_MAP(CAboutDlg)
        // No message handlers
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTimedProgressDlg dialog

CTimedProgressDlg::CTimedProgressDlg(CWnd* pParent /*=NULL*/)
    : CDialog(CTimedProgressDlg::IDD, pParent)
{
    //{{AFX_DATA_INIT(CTimedProgressDlg)
	//}}AFX_DATA_INIT
    // Note that LoadIcon does not require a subsequent DestroyIcon in Win32
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTimedProgressDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CTimedProgressDlg)
	DDX_Control(pDX, IDC_SPEED, m_slider);
	DDX_Control(pDX, IDC_GO, m_btnGo);
	DDX_Control(pDX, IDC_STOP, m_btnStop);
	DDX_Control(pDX, IDC_PROGRESS8, m_progress8);
	DDX_Control(pDX, IDC_PROGRESS7, m_progress7);
	DDX_Control(pDX, IDC_PROGRESS6, m_progress6);
	DDX_Control(pDX, IDC_PROGRESS5, m_progress5);
	DDX_Control(pDX, IDC_PROGRESS4, m_progress4);
	DDX_Control(pDX, IDC_PROGRESS3, m_progress3);
	DDX_Control(pDX, IDC_PROGRESS2, m_progress2);
	DDX_Control(pDX, IDC_PROGRESS1, m_progress1);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTimedProgressDlg, CDialog)
    //{{AFX_MSG_MAP(CTimedProgressDlg)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_GO, OnGo)
    ON_WM_TIMER()
	ON_BN_CLICKED(IDC_STOP, OnStop)
	ON_WM_DESTROY()
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SPEED, OnSpeedReleasedCapture)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTimedProgressDlg message handlers

BOOL CTimedProgressDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // Add "About..." menu item to system menu.

    // IDM_ABOUTBOX must be in the system command range.
    ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
    ASSERT(IDM_ABOUTBOX < 0xF000);

    CMenu* pSysMenu = GetSystemMenu(FALSE);
    if (pSysMenu != NULL)
    {
        CString strAboutMenu;
        strAboutMenu.LoadString(IDS_ABOUTBOX);
        if (!strAboutMenu.IsEmpty())
        {
            pSysMenu->AppendMenu(MF_SEPARATOR);
            pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
        }
    }

    // Set the icon for this dialog.  The framework does this automatically
    //  when the application's main window is not a dialog
    SetIcon(m_hIcon, TRUE);         // Set big icon
    SetIcon(m_hIcon, FALSE);        // Set small icon
    
    m_slider.SetRange(100, 3000);
    m_slider.SetPos(1250);
    
    return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTimedProgressDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
    if ((nID & 0xFFF0) == IDM_ABOUTBOX)
    {
        CAboutDlg dlgAbout;
        dlgAbout.DoModal();
    }
    else
    {
        CDialog::OnSysCommand(nID, lParam);
    }
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTimedProgressDlg::OnPaint() 
{
    if (IsIconic())
    {
        CPaintDC dc(this); // device context for painting

        SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

        // Center icon in client rectangle
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // Draw the icon
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialog::OnPaint();
    }
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTimedProgressDlg::OnQueryDragIcon()
{
    return (HCURSOR) m_hIcon;
}

void CTimedProgressDlg::OnCancel() 
{
    // prevent Esc from closing app
}

void CTimedProgressDlg::OnDestroy() 
{
    this->KillTimer(0);
    CDialog::OnDestroy();
}

void CTimedProgressDlg::OnGo() 
{
    m_progress1.SetRange(0, 100);
    m_progress1.SetStep(1);
    m_progress2.SetRange(0, 100);
    m_progress2.SetStep(1);
    m_progress3.SetRange(0, 100);
    m_progress3.SetStep(1);
    m_progress4.SetRange(0, 100);
    m_progress4.SetStep(1);
    m_progress5.SetRange(0, 100);
    m_progress5.SetStep(1);
    m_progress6.SetRange(0, 100);
    m_progress6.SetStep(1);
    m_progress7.SetRange(0, 100);
    m_progress7.SetStep(1);
    m_progress8.SetRange(0, 100);
    m_progress8.SetStep(1);

    m_btnGo.ShowWindow(SW_HIDE);
    m_btnStop.ShowWindow(SW_SHOW);
    m_btnStop.SetFocus();
    this->SetTimer(0, m_slider.GetPos(), NULL);

    m_progress1.ResetStartTime();
    m_progress1.SetPos(0);
    m_progress2.ResetStartTime();
    m_progress2.SetPos(0);
    m_progress3.ResetStartTime();
    m_progress3.SetPos(0);
    m_progress4.ResetStartTime();
    m_progress4.SetPos(0);

    m_progress5.SetPos(0);
    m_progress6.SetPos(0);
    m_progress7.SetPos(0);
    m_progress8.SetPos(0);
}

void CTimedProgressDlg::OnStop() 
{
    m_btnStop.ShowWindow(SW_HIDE);
    m_btnGo.ShowWindow(SW_SHOW);
    m_btnGo.SetFocus();
    this->KillTimer(0);
}

void CTimedProgressDlg::OnTimer(UINT nIDEvent) 
{
    if (m_progress1.GetPos() == 100)
    {
        m_progress1.ResetStartTime();
        m_progress1.SetPos(0);
        m_progress2.ResetStartTime();
        m_progress2.SetPos(0);
        m_progress3.ResetStartTime();
        m_progress3.SetPos(0);
        m_progress4.ResetStartTime();
        m_progress4.SetPos(0);

        m_progress5.SetPos(0);
        m_progress6.SetPos(0);
        m_progress7.SetPos(0);
        m_progress8.SetPos(0);
    }
    else
    {
        srand(time(NULL));
        int nOffset = rand() % 10;

        m_progress1.OffsetPos(nOffset);
        m_progress2.OffsetPos(nOffset);
        m_progress3.OffsetPos(nOffset);
        m_progress4.OffsetPos(nOffset);
        m_progress5.OffsetPos(nOffset);
        m_progress6.OffsetPos(nOffset);
        m_progress7.OffsetPos(nOffset);
        m_progress8.OffsetPos(nOffset);
    }

    CDialog::OnTimer(nIDEvent);
}

void CTimedProgressDlg::OnSpeedReleasedCapture(NMHDR *pNMHDR, LRESULT *pResult)
{
    if (m_btnStop.IsWindowVisible())
    {
        this->KillTimer(0);
        this->SetTimer(0, m_slider.GetPos(), NULL);
    }

	*pResult = 0;
}
