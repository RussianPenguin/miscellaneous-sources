// StickyNotes.cpp : main source file for StickyNotes.exe
//

#include "stdafx.h"
#include "resource.h"
#include "HiddenWnd.h"

CAppModule _Module;

// This class is used to make only one application instance run
class CSingleInstance
{
protected:
	HANDLE m_hMutex;

public:
	CSingleInstance()
	{
		ATLTRACE(_T("CSingleInstance::CSingleInstance()\n"));

		m_hMutex = NULL;
	}

	~CSingleInstance()
	{
		ATLTRACE(_T("CSingleInstance::~CSingleInstance()\n"));

		// Delete the mutex
		if (m_hMutex != NULL)
		{
			::ReleaseMutex(m_hMutex);
			::CloseHandle(m_hMutex);
		}
	}

	bool Init()
	{
		// Create the mutex
		m_hMutex = ::CreateMutex(NULL, TRUE, APP_NAME);

		// If failure
		if (m_hMutex == NULL)
		{
			ATLTRACE(_T("Mutex was not created!\n"));
			return false;
		}

		// If the mutex already exists, which means an instance is already running.
		if (GetLastError() == ERROR_ALREADY_EXISTS)
		{
			ATLTRACE(_T("Mutex already exists!\n"));

			// Reset the mutex handle (in this case I do not want to release the mutex
			// in the destructor)
			m_hMutex = NULL;
			// Do not do anything, just return failure
			return false;
		}

		// Success - no instance is running
		return true;
	}
};

int Run(LPTSTR /*lpstrCmdLine*/ = NULL, int nCmdShow = SW_SHOWDEFAULT)
{
	CMessageLoop theLoop;
	_Module.AddMessageLoop(&theLoop);

	// Create a hidden window
	CHiddenWindow wndHidden;
	if (wndHidden.Create(NULL, CWindow::rcDefault,
						APP_NAME, WS_OVERLAPPEDWINDOW) == NULL)
	{
		ATLTRACE(_T("Hidden window was not created!\n"));
		return 0;
	}

	wndHidden.ShowWindow(SW_HIDE);
	int nRet = theLoop.Run();

	_Module.RemoveMessageLoop();

	return nRet;
}

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR lpstrCmdLine, int nCmdShow)
{
	// Memory check
#if defined(_DEBUG)
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_CHECK_ALWAYS_DF |
		_CRTDBG_LEAK_CHECK_DF );
#endif

	// I want to have only one instance of an application to run at a time
	CSingleInstance OneInstance;
	if (!OneInstance.Init())
		return 0;

	HRESULT hRes = ::CoInitialize(NULL);
//	If you are running on NT 4.0 or higher you can use the following call instead to
//	make the EXE free threaded. This means that calls come in on a random RPC thread.
//	HRESULT hRes = ::CoInitializeEx(NULL, COINIT_MULTITHREADED);
	ATLASSERT(SUCCEEDED(hRes));

#if (_WIN32_IE >= 0x0300)
	INITCOMMONCONTROLSEX iccx;
	iccx.dwSize = sizeof(iccx);
	iccx.dwICC = ICC_BAR_CLASSES;	// change to support other controls
	BOOL bRet = ::InitCommonControlsEx(&iccx);
	bRet;
	ATLASSERT(bRet);
#else
	::InitCommonControls();
#endif

	hRes = _Module.Init(NULL, hInstance);
	ATLASSERT(SUCCEEDED(hRes));

	HINSTANCE hInstRich = ::LoadLibrary(CRichEditCtrl::GetLibraryName());
	ATLASSERT(hInstRich != NULL);

	int nRet = Run(lpstrCmdLine, nCmdShow);

	::FreeLibrary(hInstRich);
	_Module.Term();
	::CoUninitialize();

	return nRet;
}
