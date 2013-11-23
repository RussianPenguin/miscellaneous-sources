// HiddenWnd.h : interface of the CHiddenWindow class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_HIDDENWND_H__65DA3445_4922_4EFF_8008_15CDDC626CDC__INCLUDED_)
#define AFX_HIDDENWND_H__65DA3445_4922_4EFF_8008_15CDDC626CDC__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "aboutdlg.h"
#include "NoteDlg.h"
#include "NotesArchive.h"
#include "SearchDlg.h"
#include <Userenv.h>
#include <Lmcons.h>
#include "TrayIcon.h"
#include "RecentNotes.h"

#define APP_NAME				_T("Sticky Notes")
#define DEFAULT_FILE_NAME		_T("notes.dat")

// Message to display a note
#define WMU_DISPLAYNOTE		WM_APP + 2

// Message to delete a note
#define WMU_DELETENOTE		WM_APP + 5

// Message to persist the notes
#define WMU_PERSISTNOTES	WM_APP + 9

// Message to see if the application is being closed
#define WMU_ISAPPCLOSING		WM_APP + 10

class CSearchDlg;

// This is a hidden window which is used to send a message to the taskbar's status 
// area (add and remove an icon to the taskbar status area) and handle all
// other application tasks like creating a new note, searching and so on.
class CHiddenWindow : public CWindowImpl<CHiddenWindow> 
{
private:
	CMenu m_menuPopup;				// top-level popup menu
	string m_strFileName;			// name of the file to store notes
	CSearchDlg * m_pSearchDlg;		// pointer to the search dialog
	CTrayIcon m_TrayIcon;
	HICON m_hIconNotes;
	map<int, HWND> m_mapOpenNotes;	// map containing IDs and HWNDs of all open notes
									// map's key - note's id, map's value - HWND
	bool m_bAppClosing;				// indicates if the application is being closed

public:	
	vector<CNote> m_vecNotes;		// vector containing all saved notes
	CRecentNotes m_RecNotes;

	CHiddenWindow();

	~CHiddenWindow();

	BEGIN_MSG_MAP(CHiddenWindow)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		MESSAGE_HANDLER(WMU_NOTIFYICON, OnNotifyIcon)
		MESSAGE_HANDLER(WMU_DISPLAYNOTE, OnDisplayNote)
		MESSAGE_HANDLER(WMU_DELETENOTE, OnDeleteNote)
		MESSAGE_HANDLER(WMU_PERSISTNOTES, OnPersistNotes)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_QUERYENDSESSION, OnEndSession)
		MESSAGE_HANDLER(WMU_ISAPPCLOSING, OnIsAppClosing)
		COMMAND_HANDLER(ID_POPUP_NEWNOTE, 0, OnNewNote)
		COMMAND_HANDLER(ID_POPUP_SEARCH, 0, OnSearch)
		COMMAND_HANDLER(ID_POPUP_ABOUT, 0, OnAbout)
		COMMAND_HANDLER(ID_POPUP_EXIT, 0, OnExit)
		COMMAND_HANDLER(ID_POPUP_TOP, 0, OnBringNotesToFront)
		COMMAND_RANGE_HANDLER(NEW_MENU_ID_FIRST, (NEW_MENU_ID_FIRST + NUM_NEW_ITEMS - 1), OnPopupRecentNotes)
	END_MSG_MAP()

	string FindNoteTextByID(DWORD dwID);
 
	void AddToListOfOpenNotes(const DWORD nID, const HWND hwndNote);

	void RemoveFromListOfOpenNotes(const DWORD nID);

protected:
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	
	LRESULT OnEndSession(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnNotifyIcon(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnDisplayNote(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnDeleteNote(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnPersistNotes(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnIsAppClosing(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT DisplayShortcutMenu();

	LRESULT OnNewNote(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	LRESULT OnSearch(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	LRESULT OnAbout(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	
	LRESULT OnExit(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	LRESULT OnPopupRecentNotes(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	LRESULT OnBringNotesToFront(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	LRESULT CreateNewNote();

	LRESULT DisplayNote(DWORD dwID);

	bool LoadNotes();

	bool SaveNotes();

	string GetFileName();

	HWND IsNoteOpen(int nID);

	void DestroyOpenNotes();

	void DisplayPreviouslyOpenNotes();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HIDDENWND_H__65DA3445_4922_4EFF_8008_15CDDC626CDC__INCLUDED_)
