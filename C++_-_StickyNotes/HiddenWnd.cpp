// HiddenWnd.cpp : implementation of the CHiddenWindow class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "HiddenWnd.h"
#include "FindNote.h"

// Standard shift-operator overload, which takes CNote as a parameter
ostream& operator<<(ostream& os, CNote n)
{
	os << "[NOTE]" << endl;
	os << "[NOTETEXT]:" << n.GetNoteText() << endl;
	os << "[NOTERTF]:" << n.GetNoteRTF() << endl;
	os << "[TITLE]:" << n.GetNoteTitle() << endl;
	os << "[TIMESTAMP]:" << n.GetTimestamp() << endl;
	os << "[BKGNDCOLOR]:" << n.GetNoteColor() << endl;
	os << "[NOTEID]:" << n.GetNoteID() << endl;
	os << "[ALPHA]:" << n.GetNoteAlpha() << endl;
	os << "[POSITION]:" << n.GetNoteRect().left << "," << n.GetNoteRect().top
			<< "," << n.GetNoteRect().right << "," << n.GetNoteRect().bottom << endl;
	os << "[STATUS]:" << n.GetNoteStatus() << endl;
	os << "[ENDNOTE]" << endl;
	return os;
}

CHiddenWindow::CHiddenWindow()
{
	ATLTRACE(_T("CHiddenWindow::CHiddenWindow()\n"));
	m_pSearchDlg = NULL;
	m_bAppClosing = false;
}

CHiddenWindow::~CHiddenWindow()
{
	ATLTRACE(_T("CHiddenWindow::~CHiddenWindow()\n"));

	m_pSearchDlg = NULL;

	// Destroy the menu
	if (m_menuPopup.m_hMenu)
		m_menuPopup.DestroyMenu();
}

LRESULT CHiddenWindow::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	// Load the 'Notes' icon from the application's resources
	m_hIconNotes = (HICON)::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDI_TRAYNOTE),
		IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), LR_DEFAULTCOLOR);
	ATLASSERT(m_hIconNotes);

	// Add the icon to the taskbar status area
	if (!m_TrayIcon.AddIconToTaskBar(m_hWnd, IDI_TRAYNOTE, m_hIconNotes, APP_NAME))
	{
		ATLTRACE(_T("Icon was not added to the taskbar!\n"));
		return 0;
	}

	// Create a name of a file where the application keeps saved notes.
	m_strFileName = GetFileName();

	// Get all saved notes from the file
	LoadNotes();

	// Initialize collection of recently accessed notes
	m_RecNotes.Initialize(this);

	// Display notes that have been open before the app closed
	DisplayPreviouslyOpenNotes();

	return 0;
}

// This message is sent by the system when the user chooses to end the session or
// when any application calls the ExitWindows function.
// Note: If any application returns zero, the session is not ended.
// The system stops sending WM_QUERYENDSESSION messages as soon as one application returns zero.
LRESULT CHiddenWindow::OnEndSession(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	// I do not care if the user is logging off or shutting down the system
	//
	// Even in case of an error it's OK to end the Windows session
	OnDestroy(uMsg, wParam, lParam, bHandled);

	// It's OK to end the Windows session
	return TRUE;
}

LRESULT CHiddenWindow::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	// If there are still some open notes destroy them
	DestroyOpenNotes();

	// Persist saved notes to the file
	SaveNotes();

	// Delete the icon from the taskbar status area
	if (!m_TrayIcon.RemoveIconFromTaskBar(m_hWnd, IDI_TRAYNOTE))
		ATLTRACE(_T("Icon was not removed from the taskbar!\n"));

	::PostQuitMessage(0);
	return 0;
}

// Destroys all open notes
void CHiddenWindow::DestroyOpenNotes()
{
	m_bAppClosing = true;

	map<int, HWND>::iterator iter;

	// Loop through the collection of open notes and destroy them
	for (iter = m_mapOpenNotes.begin(); iter != m_mapOpenNotes.end(); iter++)
	{
		::SendMessage((*iter).second, WM_CLOSE, 0, 0);
	}
}

// Handles tray notification message
LRESULT CHiddenWindow::OnNotifyIcon(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	// Determine the tray message
	switch (lParam)
	{
	// Right mouse button click - display a popup menu
	case WM_RBUTTONUP:
		DisplayShortcutMenu();
		break;
	// Left mouse button double-click - create a new note
	case WM_LBUTTONDBLCLK:
		CreateNewNote();
		break;
	default:
		break;
	}

	return 0;
}

// Displays a notify icon's shortcut menu
LRESULT CHiddenWindow::DisplayShortcutMenu()
{
	// Hide the search dialog if it exists
	if (m_pSearchDlg && ::IsWindow(m_pSearchDlg->m_hWnd))
		m_pSearchDlg->ShowWindow(SW_HIDE);

	// Load the menu resource
	if (!m_menuPopup.LoadMenu(IDR_TRAYMENU))
	{
		ATLTRACE(_T("Menu was not loaded!\n"));
		return 0;
	}

	// Get cursor's position
	POINT pt;
	::GetCursorPos(&pt);

	// Display a shortcut menu at the specified location
	// See "PRB: Menus for Notification Icons Don't Work Correctly" in MSDN
	::SetForegroundWindow(m_hWnd);

	// TrackPopupMenu cannot display the menu bar so get
	// a handle to the first shortcut menu
	CMenuHandle menuTrackPopup = m_menuPopup.GetSubMenu(0);
	if (!menuTrackPopup.m_hMenu)
	{
		ATLTRACE(_T("Handle to the first shortcut menu was not retrieved!\n"));
		m_menuPopup.DestroyMenu();
		m_menuPopup.m_hMenu = NULL;
		return 0;
	}

	// Insert new menu items (recently accessed notes)
	CMenuHandle menuPopupRecent = menuTrackPopup.GetSubMenu(2);
	if (!menuPopupRecent.m_hMenu)
	{
		ATLTRACE(_T("Handle to the recent notes menu was not retrieved!\n"));
		menuTrackPopup.DestroyMenu();
		menuTrackPopup.m_hMenu = NULL;
		m_menuPopup.DestroyMenu();
		m_menuPopup.m_hMenu = NULL;
		return 0;
	}
	m_RecNotes.InsertMenuItems(menuPopupRecent);

	// Display the shortcut menu. Track the right mouse button
	if (!menuTrackPopup.TrackPopupMenu(TPM_RIGHTALIGN|TPM_RIGHTBUTTON, pt.x, pt.y, m_hWnd, NULL))
	{
		ATLTRACE(_T("Shortcut menu was not displayed!\n"));
		return 0;
	}

	::PostMessage(m_hWnd, WM_NULL, 0, 0);

	// Destroy the menu and free any memory that the menu occupies
	menuTrackPopup.DestroyMenu();
	menuPopupRecent.DestroyMenu();
	menuPopupRecent.m_hMenu = NULL;
	m_menuPopup.DestroyMenu();
	m_menuPopup.m_hMenu = NULL;

	return 0;
}

// Creates a brand new note
LRESULT CHiddenWindow::CreateNewNote()
{
	// Create a new Note dialog
	CNoteDlg * pDlgNote = NULL;
	pDlgNote = new CNoteDlg(this);

	// Check if 'new' succeeded and we have a valid pointer to a dialog object
	if (pDlgNote != NULL)
	{
		if (pDlgNote->Create(HWND_DESKTOP) == NULL)	// create failed
		{
			ATLTRACE(_T("Note dialog creation failed!\n"));
			return -1;
		}

		// Add a note's handle to a collection of open notes
		AddToListOfOpenNotes(pDlgNote->GetNoteID(), pDlgNote->m_hWnd);

		::SetForegroundWindow(pDlgNote->m_hWnd);

		pDlgNote->ShowWindow(SW_SHOW);
	}
	else
	{
		ATLTRACE(_T("Dialog object creation failed!\n"));
		return -1;
	}

	return 0;
}

// Handles selecting 'New Note' item from the menu
LRESULT CHiddenWindow::OnNewNote(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if (CreateNewNote() == -1)
		ATLTRACE(_T("New Note creation failed!\n"));

	return 0;
}

// Handles selecting 'Search' item from the menu
LRESULT CHiddenWindow::OnSearch(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	// If a search dialog already exists then show it, do not create a new one
	if (m_pSearchDlg && ::IsWindow(m_pSearchDlg->m_hWnd))
	{
		m_pSearchDlg->ShowWindow(SW_SHOW);
		return 0;
	}

	// If a search dialog does not exist then create a new one
	m_pSearchDlg = new CSearchDlg(this);

	// Check if 'new' succeeded and we have a valid pointer to a dialog object
	if (m_pSearchDlg != NULL)
	{
		if (m_pSearchDlg->Create(m_hWnd) == NULL)	// create failed
		{
			ATLTRACE(_T("Search dialog creation failed!\n"));
			return 0;
		}
		m_pSearchDlg->ShowWindow(SW_SHOW);
	}
	else
		ATLTRACE(_T("Search dialog object creation failed!\n"));

	return 0;
}

// Handles selecting 'About' item from the menu
LRESULT CHiddenWindow::OnAbout(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CAboutDlg dlg;
	dlg.DoModal();
	return 0;
}

// Handles selecting 'Exit' item from the menu
LRESULT CHiddenWindow::OnExit(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	// Destroy the hidden window
	DestroyWindow();
	return 0;
}

// Reads the file and populates the vector which'll contain the list of all saved notes
bool CHiddenWindow::LoadNotes()
{
	// Lets check if the file name is valid
	if (m_strFileName.length() == 0)
	{
		MessageBox(_T("Could not retrieve the file name.\nCould not load notes!"),
					_T("Sticky Notes - Error"), MB_OK|MB_ICONEXCLAMATION);
		return false;
	}

	// Open a file which contain all saved notes
	CNotesArchive NotesArchive(m_strFileName.c_str(), ios::in | ios::out | ios::app);
	if (!NotesArchive.IsOpen())
	{
		MessageBox(_T("The file to load notes from was not opened.\nCould not load notes!"),
					_T("Sticky Notes - Error"), MB_OK|MB_ICONEXCLAMATION);
		return false;
	}

	NotesArchive.LoadNotesFromFile(&m_vecNotes);

	return true;
}

// Handler for WMU_PERSISTNOTES message.
LRESULT CHiddenWindow::OnPersistNotes(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	SaveNotes();
	return 0;
}

// Writes vector containing list of saved notes to the file
bool CHiddenWindow::SaveNotes()
{
	// Lets check if the file name is valid
	if (m_strFileName.length() == 0)
	{
		MessageBox(_T("Could not retrieve the file name.\nCould not save notes!"),
					_T("Sticky Notes - Error"), MB_OK|MB_ICONEXCLAMATION);
		return false;
	}

	// Open a file and delete the old one (if it already exists)
	CNotesArchive NotesArchive(m_strFileName.c_str(), ios::in | ios::out | ios::trunc);
	if (!NotesArchive.IsOpen())
	{
		MessageBox(_T("The file to save notes was not opened.\nCould not save notes!"),
					_T("Sticky Notes - Error"), MB_OK|MB_ICONEXCLAMATION);
		return false;
	}

	NotesArchive.SaveNotesToFile(m_vecNotes);

	return true;
}

// Handler for WMU_DISPLAYNOTE message.
// WPARAM contains ID of the note that we are going to display.
// When the hidden window receives this message it'll search for this note and display it.
LRESULT CHiddenWindow::OnDisplayNote(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	DWORD dwID = (DWORD)wParam;		// note's id

	return DisplayNote(dwID);
}

// Displays an existing note
// dwID - note's id
LRESULT CHiddenWindow::DisplayNote(DWORD dwID)
{
	vector<CNote> vecResult;		// vector to hold the search matches

	// See if this note is already open
	HWND hwndNote = IsNoteOpen(dwID);

	if (hwndNote)		// note is already open, bring it to the front
		::SetForegroundWindow(hwndNote);
	else				// note is not open, create it
	{
		// Create the function object
		CFindNoteById findNotes(dwID, &vecResult);

		// Iterate over the contents of the vector.
		// Instance of CFindNoteById class is passed to the 'for_each()' algorithm as its
		// third argument and its operator() is called for each element in the vector.
		// Each element's m_nID value is searched for the specified integer.
		for_each(m_vecNotes.begin(), m_vecNotes.end(), findNotes);

		// Since I'm searching by unique id it can be only one match (I hope)
		if (vecResult.size() != 0)
		{
			// Create a new Note dialog
			CNoteDlg * pDlgNote = NULL;
			pDlgNote = new CNoteDlg(this, vecResult[0]);

			// Check if 'new' succeeded and we have a valid pointer to a dialog object
			if (pDlgNote != NULL)
			{
				if (pDlgNote->Create(HWND_DESKTOP) == NULL)	// create failed
				{
					ATLTRACE(_T("Note dialog creation failed!\n"));
					return -2;
				}

				// Add a note's handle to a collection of open notes
				AddToListOfOpenNotes(pDlgNote->GetNoteID(), pDlgNote->m_hWnd);

				// Show it.
				// pDlgNote->GetNoteRect().Height() > 50 fixes the issue when a note is contracted
				// you can't double click on a title bar and restore its size
				if (pDlgNote->GetNoteRect().Width() != 0 && pDlgNote->GetNoteRect().Height() > 50)
					pDlgNote->SetWindowPos(HWND_TOP, pDlgNote->GetNoteRect(), SWP_SHOWWINDOW);
				else
				{
					::SetForegroundWindow(pDlgNote->m_hWnd);
					pDlgNote->ShowWindow(SW_SHOW);
				}

				// Initially all text is selected so fix it
				pDlgNote->UnselectText();
			}
			else
			{
				ATLTRACE(_T("Dialog object creation failed!\n"));
				return -1;
			}
		}
		else
			MessageBox(_T("This note was deleted!"), APP_NAME, MB_OK);
	}

	return 0;
}

// Creates a full path of the file where the application keeps saved notes.
string CHiddenWindow::GetFileName()
{
	string strFile = DEFAULT_FILE_NAME;
	HANDLE hToken = NULL;
	TCHAR szPath[_MAX_PATH];
	DWORD dwPathSize = sizeof(szPath)/sizeof(TCHAR);
	TCHAR szUserName[UNLEN + 1];
	DWORD dwUserNameSize = sizeof(szUserName)/sizeof(TCHAR);

	typedef BOOL (__stdcall *PFUNCOPENPROCESSTOKEN)(HANDLE, DWORD, HANDLE*); 
	PFUNCOPENPROCESSTOKEN pfOpenProcessToken;

	typedef BOOL (__stdcall *PFUNCGETUSERPROFILEDIR)(HANDLE, LPTSTR, DWORD*); 
	PFUNCGETUSERPROFILEDIR pfGetUserProfileDir;  

	// If Win95, 98 or Me is running the file will be created in the same 
	// directory where executable is located since only one user can use
	// the system.
	// If WinNT, 2000, XP or higher is running the file will be created
	// in the root directory of the specified user's profile, i.e.
	// C:\Documents and Settings\administrator on Win2000

	// Load the Advapi32.dll
	HMODULE hAdvapi = ::LoadLibrary("Advapi32.dll");
    if (hAdvapi == NULL) 
	{
		ATLTRACE(_T("LoadLibrary(Advapi32.dll) failed!\n"));
		return strFile;
	}

	// Try to get the OpenProcessToken function address.
	pfOpenProcessToken = 
		(PFUNCOPENPROCESSTOKEN)::GetProcAddress(hAdvapi, "OpenProcessToken"); 
	if (pfOpenProcessToken == NULL)
	{
		ATLTRACE(_T("GetProcAddress(hAdvapi, OpenProcessToken) failed!\n"));
		// Free the Advapi32.dll.
		::FreeLibrary(hAdvapi); 
		return strFile;
	}

	// Load the Userenv.dll
	HMODULE hUserenv = ::LoadLibrary("Userenv.dll");
    if (hUserenv == NULL) 
	{
		ATLTRACE(_T("LoadLibrary(Userenv.dll) failed!\n"));
		// Free the Advapi32.dll
		::FreeLibrary(hAdvapi); 
		return strFile;
	}

	// Try to get the GetUserProfileDirectory function address
#ifdef _UNICODE
	pfGetUserProfileDir = 
		(PFUNCGETUSERPROFILEDIR)::GetProcAddress(hUserenv, "GetUserProfileDirectoryW");
#else 
	pfGetUserProfileDir = 
		(PFUNCGETUSERPROFILEDIR)::GetProcAddress(hUserenv, "GetUserProfileDirectoryA");
#endif /* _UNICODE */

	if (pfGetUserProfileDir == NULL)
	{
		ATLTRACE(_T("GetProcAddress(hUserenv, GetUserProfileDirectory) failed!\n"));
		// Free the Advapi32.dll.
		::FreeLibrary(hAdvapi);
		// Free the Userenv.dll. 
		::FreeLibrary(hUserenv);
		return strFile;
	}

	// Open the access token associated with a process
	if (!(pfOpenProcessToken)(GetCurrentProcess(), TOKEN_QUERY, &hToken))
	{
		ATLTRACE(_T("OpenProcessToken() failed!\n"));
		// Free the Advapi32.dll.
		::FreeLibrary(hAdvapi); 
		// Free the Userenv.dll.
		::FreeLibrary(hUserenv); 
		return strFile;
	}

	// Retrieve the path to the root directory of the specified user's profile
	if (!(pfGetUserProfileDir)(hToken, szPath, &dwPathSize))
	{
		ATLTRACE(_T("GetUserProfileDirectory() failed!\n"));
		if (hToken)
			::CloseHandle(hToken);
		// Free the Advapi32.dll.
		::FreeLibrary(hAdvapi); 
		// Free the Userenv.dll.
		::FreeLibrary(hUserenv); 
		return strFile;
	}

	// Retrieve the user name of the current thread. 
	// This is the name of the user currently logged onto the system. 
	if (!::GetUserName(szUserName, &dwUserNameSize))
	{
		ATLTRACE(_T("GetUserName() failed!\n"));
		if (hToken)
			::CloseHandle(hToken);
		// Free the Advapi32.dll.
		::FreeLibrary(hAdvapi); 
		// Free the Userenv.dll.
		::FreeLibrary(hUserenv); 
		return strFile;
	}

	// Construct a fully qualified file name.
	// The file name is created by concatenating the user name and the default file name
	strFile = string(szPath) + string(_T("\\")) + string(szUserName) + 
			string(_T("_")) + string(DEFAULT_FILE_NAME);

	if (hToken)
		::CloseHandle(hToken);

	// Free the Advapi32.dll.
    ::FreeLibrary(hAdvapi); 
		
	// Free the Userenv.dll.
    ::FreeLibrary(hUserenv); 

	return strFile;
}

// Handler for WMU_DELETENOTE message
// Deletes a note from the collection
LRESULT CHiddenWindow::OnDeleteNote(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	vector<CNote>::iterator iter;	
	int nNoteID = (int)wParam;		// note's id

	// If the note is found remove it from the collection of notes
	for (iter = m_vecNotes.begin(); iter != m_vecNotes.end(); iter++)
	{
		if ((*iter).GetNoteID() == nNoteID)
		{
			m_vecNotes.erase(iter);

			// Remove it from the collection of recently accessed notes, if it's there
			m_RecNotes.RemoveItemFromCollection(nNoteID);

			// Remove it from the collection of open notes, if it's there
			RemoveFromListOfOpenNotes(nNoteID);

			return 1;	// success
		}
	}

	return 0;	// failure
}

// Handler for the COMMAND_RANGE_HANDLER message
// wID contains the identifier of the menu item, control, or accelerator. 
LRESULT CHiddenWindow::OnPopupRecentNotes(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	DWORD dwData;
	bool bRet;

	// Retrieve a value associated with the menu item - note's id
	bRet = m_RecNotes.GetItemData(wID, &dwData);
	if (bRet)
	{
		// Display a note
		return DisplayNote(dwData);
	}
	else
	{
		ATLTRACE(_T("GetItemData() failed!\n"));
		return -1;
	}
}

// Returns a note's text given a note's id.
// If the note is not found returns an empty string
string CHiddenWindow::FindNoteTextByID(DWORD dwID)
{
	vector<CNote> vecResult;		// vector to hold the search matches

	// Create the function object
	CFindNoteById findNotes(dwID, &vecResult);

	// Iterate over the contents of the vector.
	// Instance of CFindNoteById class is passed to the 'for_each()' algorithm as its
	// third argument and its operator() is called for each element in the vector.
	// Each element's m_nID value is searched for the specified integer.
	for_each(m_vecNotes.begin(), m_vecNotes.end(), findNotes);

	// Since I'm searching by unique id it can be only one match (I hope)
	if (vecResult.size() != 0)
	{
		return vecResult[0].GetNoteText();
	}
	else
		return EMPTY_STRING;
}

// Adds a note's window handle to a list of opened notes
// nID - note's id
// hwndNote - note's dialog window handle
void CHiddenWindow::AddToListOfOpenNotes(const DWORD dwID, const HWND hwndNote)
{
	m_mapOpenNotes.insert(pair<const int, HWND> (dwID, hwndNote));
}

// Removes a note's window handle from a list of opened notes
// nID - note's id
void CHiddenWindow::RemoveFromListOfOpenNotes(const DWORD dwID)
{
	// Reason behind the following code is that removing an item while iterating
	// invalidates the iterator. So if the application is being closed I'll need
	// to iterate through this collection to destroy all open notes and when
	// the note is destroyed it'll be removed from the collection and it is
	// causing an access violation.
	if (m_bAppClosing)
		return;

	// Remove from the collection
	if (!m_mapOpenNotes.empty())
		m_mapOpenNotes.erase(dwID);
}

// Checks if the note with the given id is already open. If it is returns its 
// window handle and NULL if not.
HWND CHiddenWindow::IsNoteOpen(int nID)
{
	// Try to find an element with a given key
	map<int, HWND>::iterator iter = m_mapOpenNotes.find(nID);

	// If it's there return its value or NULL otherwise
	if (iter != m_mapOpenNotes.end())
		return (*iter).second;
	return NULL;
}

// Handles selecting 'Bring All Notes To Front' item from the menu
LRESULT CHiddenWindow::OnBringNotesToFront(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	map<int, HWND>::iterator iter;	

	// Loop through the collection of open notes and activate them
	for (iter = m_mapOpenNotes.begin(); iter != m_mapOpenNotes.end(); iter++)
	{
		::SetForegroundWindow((*iter).second);
	}

	return 0;
}

// Handles WMU_ISAPPCLOSING message
LRESULT CHiddenWindow::OnIsAppClosing(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return m_bAppClosing ? TRUE : FALSE;
}

// Displays all notes that have been opened before the app closed
void CHiddenWindow::DisplayPreviouslyOpenNotes()
{
	vector<CNote>::iterator iter;	

	// Loop though all notes and check their status. Display a note if it has
	// been open before the app closed
	for (iter = m_vecNotes.begin(); iter != m_vecNotes.end(); iter++)
	{
		if ((*iter).GetNoteStatus() == (*iter).Status::Open)
		{
			DisplayNote((*iter).GetNoteID());
		}
	}
}