// CalendarAppDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CalendarApp.h"
#include "CalendarAppDlg.h"

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
// CCalendarAppDlg dialog

CCalendarAppDlg::CCalendarAppDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCalendarAppDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCalendarAppDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCalendarAppDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCalendarAppDlg)
	DDX_Control(pDX, IDC_TEXT, m_edtText);
	DDX_Control(pDX, IDC_DATE, m_ctrlDatePicker);
	DDX_Control(pDX, IDC_LOG, m_lbxLog);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCalendarAppDlg, CDialog)
	//{{AFX_MSG_MAP(CCalendarAppDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_REMOVE, OnRemove)
	ON_BN_CLICKED(IDC_CLEAR_ALL, OnClearAll)
	ON_BN_CLICKED(IDC_SPINNERS, OnSpinners)
	//}}AFX_MSG_MAP

	// DATE NOTIFICATION MESSAGE
	ON_MESSAGE(WM_DATE_NOTIFY,OnDateNotify)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCalendarAppDlg message handlers

BOOL CCalendarAppDlg::OnInitDialog()
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
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	// Note on the Rectangle window position - size is ignored
	m_ctrlCalendar.Create(NULL,NULL, WS_VISIBLE | WS_CHILD, CRect(5,5,5,5), this, 0x0001);

	COleDateTime date(COleDateTime::GetCurrentTime());

	m_ctrlCalendar.AddNote(date, _T("Go ahead make a note"), TRUE);

	date -= COleDateTimeSpan(5);
	m_ctrlCalendar.AddNote(date, _T("Historical Info..."), TRUE);

	date += COleDateTimeSpan(10);
	m_ctrlCalendar.AddNote(date, _T("Big night out"), TRUE);

	m_edtText.SetWindowText(_T("Enter note here..."));
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCalendarAppDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCalendarAppDlg::OnPaint() 
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
HCURSOR CCalendarAppDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CCalendarAppDlg::OnAdd() 
{
	CString str;

	m_edtText.GetWindowText(str);

	COleDateTime date;
	m_ctrlDatePicker.GetTime(date);

	m_ctrlCalendar.AddNote(date, str, TRUE);

	// TODO:` Add your control notification handler code here
	
}

LRESULT CCalendarAppDlg::OnDateNotify(WPARAM wParam, LPARAM nControlId)
{
	COleDateTime tm = m_ctrlCalendar.GetDate();

	CString str;
	str.Format("Date Pressed: %s, ID=0x%04x",tm.Format("%d/%m/%y"),nControlId);

	m_lbxLog.InsertString(0,str);
	m_lbxLog.SetCurSel(0);

	return 0;
}

void CCalendarAppDlg::OnRemove() 
{
	COleDateTime date;
	m_ctrlDatePicker.GetTime(date);

	m_ctrlCalendar.DeleteNote(date);
	
}

void CCalendarAppDlg::OnClearAll() 
{
	m_ctrlCalendar.ClearAllNotes();
	
}

void CCalendarAppDlg::OnSpinners() 
{
	m_ctrlCalendar.ShowSpinner(!m_ctrlCalendar.IsSpinnerVisible());
	
}
