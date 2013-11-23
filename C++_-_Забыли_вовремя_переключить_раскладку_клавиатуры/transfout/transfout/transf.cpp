// transf.cpp : Defines the class behaviors for the application.
//Author Demo_S s_daemon@yahoo.com>
//if ypu want to use this program in commercial purposes? you have to mail me about it

#include "stdafx.h"
#include "transf.h"
#include "transfDlg.h"
#include "io.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTransfApp

BEGIN_MESSAGE_MAP(CTransfApp, CWinApp)
	//{{AFX_MSG_MAP(CTransfApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTransfApp construction

CTransfApp::CTransfApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CTransfApp object

CTransfApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CTransfApp initialization

BOOL CTransfApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Проверим, чтобы в памяти не было еще одной копии программы, иначе не запускаемся
	HANDLE m_Mutex=NULL;
	m_Mutex=OpenMutex(MUTEX_ALL_ACCESS,TRUE,_T("Transf synchronizer"));
	if (m_Mutex) return false;//Такая программа уже зарущена
	m_Mutex=CreateMutex(NULL,TRUE,_T("Transf synchronizer"));
	
	SetRegistryKey("Demo_S products");
	
	CTransfDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	
	return FALSE;
}
