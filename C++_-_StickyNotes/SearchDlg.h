// SearchDlg.h : interface of the CSearchDlg class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SEARCHDLG_H__475DFB95_8F0C_4F6C_8EE4_34DC495F448A__INCLUDED_)
#define AFX_SEARCHDLG_H__475DFB95_8F0C_4F6C_8EE4_34DC495F448A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Message to search for notes
#define WMU_FINDNOTE		WM_APP + 3

// Message to create a new note
#define WMU_NEWNOTE			WM_APP + 4

#include "HiddenWnd.h"
#include "SearchList.h"
#include "SearchButton.h"
#include "ATLLabel.h"

class CSearchDlg : public CDialogImpl<CSearchDlg>,
					public CMessageFilter, 
					public CIdleHandler,
					public CDialogResize<CSearchDlg>
{
private:
	CHiddenWindow * m_pWndParent;	// pointer to the parent hidden window
	CEditEx m_wndSearchEdit;		// edit control
	CSearchList m_wndSearchList;	// list control
	vector<CNote> m_vecResult;		// vector to hold the search matches

	CButtonExCancel m_wndBtnCancel;	// 'Cancel' button
	CButtonExFind m_wndBtnFind;		// 'Find Now' button
	CButtonExNew m_wndBtnNew;		// 'New Note' button

	CLabel m_wndLblFind;			// 'Find Note' label control
	CLabel m_wndLblLookFor;			// 'Look for' label control
	BYTE m_bAutoDelete;				// it tells us if we want to auto-delete ourselves

public:
	enum { IDD = IDD_SEARCHDLG };

	CSearchDlg(CHiddenWindow * pWnd);

	~CSearchDlg();

	virtual BOOL PreTranslateMessage(MSG* pMsg)
	{
		// If it's a 'Tab' key then the dialog should handle it
		if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_TAB)
			return IsDialogMessage(pMsg);

		// If an edit control has a focus and an 'Enter' key is pressed then
		// edit control button should handle the message
		if (pMsg->hwnd == m_wndSearchEdit.m_hWnd && pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
			return m_wndSearchEdit.PreTranslateMessage(pMsg);

		// If any of the buttons have a focus and an 'Enter' key is pressed then
		// buttons should handle the message
		if (pMsg->hwnd == m_wndBtnCancel.m_hWnd && pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
			return m_wndBtnCancel.PreTranslateMessage(pMsg);
		if (pMsg->hwnd == m_wndBtnFind.m_hWnd && pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
			return m_wndBtnFind.PreTranslateMessage(pMsg);
		if (pMsg->hwnd == m_wndBtnNew.m_hWnd && pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
			return m_wndBtnNew.PreTranslateMessage(pMsg);

		// If any of the buttons have a focus and any other key is pressed then
		// do not handle the message
		if (pMsg->hwnd == m_wndBtnCancel.m_hWnd && pMsg->message == WM_KEYDOWN)
			return TRUE;
		if (pMsg->hwnd == m_wndBtnFind.m_hWnd && pMsg->message == WM_KEYDOWN)
			return TRUE;
		if (pMsg->hwnd == m_wndBtnNew.m_hWnd && pMsg->message == WM_KEYDOWN)
			return TRUE;

		// If the list  control has a focus then it should handle all messages
		if (m_wndSearchList.m_hWnd == ::GetFocus())
			return m_wndSearchList.PreTranslateMessage(pMsg);
		else
			return IsDialogMessage(pMsg);
	}

	virtual BOOL OnIdle()
	{
		return FALSE;
	}

	BEGIN_MSG_MAP(CSearchDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_CLOSE, OnClose)
		MESSAGE_HANDLER(WMU_FINDNOTE, OnFind)
		MESSAGE_HANDLER(WMU_NEWNOTE, OnNewNote)
		CHAIN_MSG_MAP(CDialogResize<CSearchDlg>)
		// When a control sends its parent a message, the parent can 
		// reflect the message back to the control  
		REFLECT_NOTIFICATIONS()
	END_MSG_MAP()

    BEGIN_DLGRESIZE_MAP(CSearchDlg)
		DLGRESIZE_CONTROL(IDCANCEL, DLSZ_MOVE_X)
		DLGRESIZE_CONTROL(IDC_FIND, DLSZ_MOVE_X)
		DLGRESIZE_CONTROL(IDC_NEW, DLSZ_MOVE_X)
		DLGRESIZE_CONTROL(IDC_STATIC_FIND, DLSZ_SIZE_X)
		DLGRESIZE_CONTROL(IDC_SEARCH_EDIT, DLSZ_SIZE_X)
		DLGRESIZE_CONTROL(IDC_SEARCH_LIST, DLSZ_SIZE_X)
		DLGRESIZE_CONTROL(IDC_SEARCH_LIST, DLSZ_SIZE_Y)
    END_DLGRESIZE_MAP()

	WNDPROC GetDialogProc();

	static LRESULT CALLBACK SearchDialogProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	void CloseDialog(int nVal);

	LRESULT OnFind(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnNewNote(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEARCHDLG_H__475DFB95_8F0C_4F6C_8EE4_34DC495F448A__INCLUDED_)
