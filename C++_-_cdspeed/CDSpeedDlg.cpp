//////////////////////////////////////////////////////////////////////////
//                               CDSpeed v1.0                           //
//                      (c) Copyright 2002, Киселёв М.С.                //
//                      E-Mail: KS-Soft@Mail.ru                         //
//                         WWW: http://www.ks-soft.narod.ru             //
//////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CDSpeed.h"
#include "CDSpeedDlg.h"
#include "Wnaspi32.h"
#include "SCSIdefs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define X1   176

BYTE  HCount;
BYTE  ASPIStatus;
DWORD SupportInfo;

int CurrentHost = 0, CurrentTarget = 1;
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
// CCDSpeedDlg dialog

CCDSpeedDlg::CCDSpeedDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCDSpeedDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCDSpeedDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCDSpeedDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCDSpeedDlg)
	DDX_Control(pDX, IDC_SPIN, m_Spinner);
	DDX_Control(pDX, IDC_CD_ROM, m_CD);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCDSpeedDlg, CDialog)
	//{{AFX_MSG_MAP(CCDSpeedDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_SET_SPEED, OnSetSpeed)
	ON_BN_CLICKED(ID_ABOUT, OnAbout)
	ON_BN_CLICKED(ID_EXIT, OnExit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCDSpeedDlg message handlers

BOOL CCDSpeedDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	MessageBox("Внимание! Изменение скорости будет работать только при вставленном диске.", "Информация", MB_ICONINFORMATION);
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

//************************************************************************
//Загружаем WNASPI32.DLL, просто для проверки его работоспособности.
//************************************************************************
	HINSTANCE hinstWNASPI32;
	if((hinstWNASPI32 = LoadLibrary("WNASPI32")) == NULL)
	{
        AfxMessageBox("Ошибка инициализации WNASPI32.DLL.", MB_OK|MB_ICONERROR);
        exit(1);
	}
	else
	{
		FreeLibrary(hinstWNASPI32);               //Выгружаем WNASPI32.DLL
//------------------------------------------------------------------------
//Перед началом работы с ASPI необходимо вызвать GetASPI32SupportInfo()
//------------------------------------------------------------------------
		SupportInfo = GetASPI32SupportInfo();
        ASPIStatus  = HIBYTE(LOWORD(SupportInfo));
        HCount      = LOBYTE(LOWORD(SupportInfo));
        if(ASPIStatus != SS_COMP && ASPIStatus != SS_NO_ADAPTERS)
		{
      		AfxMessageBox("Ошибка ASPI.", MB_ICONERROR);
			exit(1);
		}
	}
//------------------------------------------------------------------------
	

//------------------------------------------------------------------------
//Производим поиск CD-приводов...
//------------------------------------------------------------------------
	BYTE byHaId;
    BYTE byTarget;
	CString drv;
    SRB_GDEVBlock srbGDEVBlock;
    for(byHaId = 0; byHaId<MAX_NUM_HA; byHaId++)
	{
        for(byTarget = 0; byTarget<MAXTARG; byTarget++)
		{
           memset(&srbGDEVBlock, 0, sizeof(SRB_GDEVBlock));
           srbGDEVBlock.SRB_Cmd = SC_GET_DEV_TYPE;
           srbGDEVBlock.SRB_HaId = byHaId;
           srbGDEVBlock.SRB_Target = byTarget;
           SendASPI32Command((LPSRB)&srbGDEVBlock);
           if(srbGDEVBlock.SRB_Status != SS_COMP) continue;
           if(srbGDEVBlock.SRB_DeviceType == DTYPE_CROM)
		   {
			   drv.Format("[%d:%d] %s", srbGDEVBlock.SRB_HaId, srbGDEVBlock.SRB_Target, GetDriveName(srbGDEVBlock.SRB_HaId, srbGDEVBlock.SRB_Target));
			   m_CD.AddString(drv);
		   }
		}
//------------------------------------------------------------------------
}
	        m_CD.SetCurSel(0);
			m_Spinner.SetRange(0, 1000);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCDSpeedDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCDSpeedDlg::OnPaint() 
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
HCURSOR CCDSpeedDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//////////////////////////////////////////////////////////////////////////
//Функция: GetDriveName
//Возвращает имя CD-привода.
//////////////////////////////////////////////////////////////////////////
CString CCDSpeedDlg::GetDriveName(BYTE Host, BYTE Target)
{
	BYTE byInquiry[256];
	char stringbuffer[28];
    DWORD dwASPIStatus;
    HANDLE heventSRB;
    SRB_ExecSCSICmd srbExec;
    heventSRB = CreateEvent(NULL, TRUE, FALSE, NULL);
  
    memset(&srbExec, 0, sizeof(SRB_ExecSCSICmd));
    srbExec.SRB_Cmd = SC_EXEC_SCSI_CMD;
    srbExec.SRB_Flags = SRB_DIR_IN | SRB_EVENT_NOTIFY;
    srbExec.SRB_Target = Target;
	srbExec.SRB_HaId   = Host;
	srbExec.SRB_Lun    = 0;
    srbExec.SRB_BufLen = 100;
    srbExec.SRB_BufPointer = byInquiry;
    srbExec.SRB_SenseLen = SENSE_LEN;
    srbExec.SRB_CDBLen = 6;
    srbExec.SRB_PostProc = (LPVOID)heventSRB;
    srbExec.CDBByte[0] = 0x012;
    srbExec.CDBByte[4] = 100;
    ResetEvent(heventSRB);
    dwASPIStatus = SendASPI32Command((LPSRB)&srbExec);
    if( dwASPIStatus == SS_PENDING )
	{
      WaitForSingleObject(heventSRB, INFINITE);
	}
    if(srbExec.SRB_Status != SS_COMP)
	{
		AfxMessageBox("Error processing the SRB.", MB_ICONERROR);
	}
	for(int i = 8; i < 36; i++)
    stringbuffer[i-8] = byInquiry[i];
    stringbuffer[28] = NULL;
	return stringbuffer;
}

//////////////////////////////////////////////////////////////////////////
//Функция: GetDriveMAXSpeed
//Возвращает максимальную скорость CD-привода.
//////////////////////////////////////////////////////////////////////////
int CCDSpeedDlg::GetDriveMAXSpeed(BYTE Host, BYTE Target)
{
	int Speed = 0;
	BYTE byInquiry[256];
    DWORD dwASPIStatus;
    HANDLE heventSRB;
    SRB_ExecSCSICmd srbExec;
    heventSRB = CreateEvent(NULL, TRUE, FALSE, NULL);
  
    memset(&srbExec, 0, sizeof(SRB_ExecSCSICmd));
    srbExec.SRB_Cmd = SC_EXEC_SCSI_CMD;
    srbExec.SRB_Flags = SRB_DIR_IN | SRB_EVENT_NOTIFY;
    srbExec.SRB_Target = Target;
	srbExec.SRB_HaId   = Host;
	srbExec.SRB_Lun    = 0;
    srbExec.SRB_BufLen = 100;
    srbExec.SRB_BufPointer = byInquiry;
    srbExec.SRB_SenseLen = SENSE_LEN;
    srbExec.SRB_CDBLen = 12;
    srbExec.SRB_PostProc = (LPVOID)heventSRB;
    srbExec.CDBByte[0] = 0x05A;
    srbExec.CDBByte[2] = 0x02A;
	srbExec.CDBByte[7] = 0x001;
    srbExec.CDBByte[8] = 0x000;
    ResetEvent(heventSRB);
    dwASPIStatus = SendASPI32Command((LPSRB)&srbExec);
    if( dwASPIStatus == SS_PENDING )
	{
      WaitForSingleObject(heventSRB, INFINITE);
	}
    if( srbExec.SRB_Status != SS_COMP )
	{
		AfxMessageBox("Error processing the SRB.", MB_ICONERROR);
	}

	_asm
	{
		xor eax, eax
	    mov ah, byInquiry[16]
	    mov al, byInquiry[17]
		mov Speed, eax
	}
	return Speed/176;
}


//////////////////////////////////////////////////////////////////////////
//Функция: SetDriveSpeed
//Устанавливает скорость CD-привода.
//////////////////////////////////////////////////////////////////////////
void CCDSpeedDlg::SetDriveSpeed(BYTE Host, BYTE Target, int Speed)
{
	BYTE byInquiry[256];
    DWORD dwASPIStatus;
    HANDLE heventSRB;
    SRB_ExecSCSICmd srbExec;
	if(Speed < X1) return;
    heventSRB = CreateEvent(NULL, TRUE, FALSE, NULL);
  
    memset(&srbExec, 0, sizeof(SRB_ExecSCSICmd));
    srbExec.SRB_Cmd = SC_EXEC_SCSI_CMD;
    srbExec.SRB_Flags = SRB_DIR_IN | SRB_EVENT_NOTIFY;
    srbExec.SRB_Target = Target;
	srbExec.SRB_HaId   = Host;
	srbExec.SRB_Lun    = 0;
    srbExec.SRB_BufLen = 100;
    srbExec.SRB_BufPointer = byInquiry;
    srbExec.SRB_SenseLen = SENSE_LEN;
    srbExec.SRB_CDBLen = 12;
    srbExec.SRB_PostProc = (LPVOID)heventSRB;
    srbExec.CDBByte[0] = 0x0BB;
    srbExec.CDBByte[2] = (BYTE)(Speed >> 8);
	srbExec.CDBByte[3] = (BYTE)Speed;
    srbExec.CDBByte[4] = 0xFF;
	srbExec.CDBByte[5] = 0xFF;
    ResetEvent(heventSRB);
    dwASPIStatus = SendASPI32Command((LPSRB)&srbExec);
    if( dwASPIStatus == SS_PENDING )
	{
      WaitForSingleObject(heventSRB, INFINITE);
	}
    if( srbExec.SRB_Status != SS_COMP )
	{
		AfxMessageBox("Error processing the SRB.", MB_ICONERROR);
	}
}

void CCDSpeedDlg::OnSetSpeed() 
{
	CString tmp, Title;
	m_CD.GetWindowText(tmp);

	CurrentHost   = tmp.GetAt(1) - 48;
	CurrentTarget = tmp.GetAt(3) - 48;

	Title.Format("CDSpeed - %dx\\%dx", GetDriveMAXSpeed(CurrentHost, CurrentTarget), GetDlgItemInt(IDC_SPEED));
	SetWindowText(Title);

	SetDriveSpeed(CurrentHost, CurrentTarget, GetDlgItemInt(IDC_SPEED)*X1);
}

void CCDSpeedDlg::OnAbout() 
{
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}

void CCDSpeedDlg::OnExit() 
{
	exit(0);
}