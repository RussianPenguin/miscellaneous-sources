// SearchDlg.cpp : implementation of the CSearchDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "SearchDlg.h"
#include "FindNote.h"

CSearchDlg::CSearchDlg(CHiddenWindow * pWnd) : m_pWndParent(pWnd)
{
	ATLTRACE(_T("CSearchDlg::CSearchDlg()\n"));
	ATLASSERT(pWnd);

	m_bAutoDelete = TRUE;
}

CSearchDlg::~CSearchDlg()
{
	ATLTRACE(_T("CSearchDlg::~CSearchDlg()\n"));

	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->RemoveMessageFilter(this);
	pLoop->RemoveIdleHandler(this);
}

// Override GetDialogProc to provide our own DialogProc
// See "Q202110 PRB: Deleting ATL Dialog Causes Assert in Atlwin.h, Line 2281" in MSDN
WNDPROC CSearchDlg::GetDialogProc()
{
	return SearchDialogProc;
}

// Our own dialog procedure that is mostly copied from
// CDialogImplBaseT<>::DialogProc() in Atlwin.h.
LRESULT CALLBACK CSearchDlg::SearchDialogProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CSearchDlg * pThis = (CSearchDlg*)hWnd;
	// Set a ptr to this message and save the old value.
	MSG msg = { pThis->m_hWnd, uMsg, wParam, lParam, 0, { 0, 0 } };
	const MSG* pOldMsg = pThis->m_pCurrentMsg;
	pThis->m_pCurrentMsg = &msg;
	// Pass to the message map to process.
	LRESULT lRes;
	BOOL bRet = pThis->ProcessWindowMessage(pThis->m_hWnd, uMsg, wParam,
		lParam, lRes, 0);
	// If window has been destroyed and this is the last message,
	// then delete ourselves.
	if (DEFERDELETE == pThis->m_bAutoDelete && pOldMsg == NULL)
	{
		delete pThis;
		return FALSE;
	}
	// Restore saved value for the current message.
	ATLASSERT(pThis->m_pCurrentMsg == &msg);
	pThis->m_pCurrentMsg = pOldMsg;
	// Set result if message was handled.
	if(bRet)
	{
		switch (uMsg)
		{
		case WM_COMPAREITEM:
		case WM_VKEYTOITEM:
		case WM_CHARTOITEM:
		case WM_INITDIALOG:
		case WM_QUERYDRAGICON:
		case WM_CTLCOLORMSGBOX:
		case WM_CTLCOLOREDIT:
		case WM_CTLCOLORLISTBOX:
		case WM_CTLCOLORBTN:
		case WM_CTLCOLORDLG:
		case WM_CTLCOLORSCROLLBAR:
		case WM_CTLCOLORSTATIC:
			return lRes;
			break;
		}
		::SetWindowLong(pThis->m_hWnd, DWL_MSGRESULT, lRes);
		return TRUE;
	}
	if(uMsg == WM_NCDESTROY)
	{
		// Clear out window handle.
		HWND hWnd = pThis->m_hWnd;
		pThis->m_hWnd = NULL;
		// Clean up after dialog box is destroyed.
		pThis->OnFinalMessage(hWnd);
		// If we want to automatically delete ourselves...
		if (pThis->m_bAutoDelete)
		{
			// If no outstanding messages to process in call stack,
			// m_pCurrentMsg will be NULL so we can delete ourselves.
			if (pThis->m_pCurrentMsg == NULL)
				delete pThis;
			// Else set a flag so we can delete ourselves later.
			else
				pThis->m_bAutoDelete = DEFERDELETE;
		}
	}
	return FALSE;
}

LRESULT CSearchDlg::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	BOOL bRet;

    // Initialize the CDialogResize
    DlgResize_Init(/*bAddGripper*/ true, /*bUseMinTrackSize*/ false);
        
	// center the dialog on the screen
	CenterWindow();

	// Subclass the 'Cancel' button and attach it to the CButtonExCancel object
	bRet = m_wndBtnCancel.SubclassWindow(GetDlgItem(IDCANCEL));
	ATLASSERT(bRet);

	// Subclass the 'Find' button and attach it to the CButtonExFind object
	bRet = m_wndBtnFind.SubclassWindow(GetDlgItem(IDC_FIND));
	ATLASSERT(bRet);

	// Subclass the 'New Note' button and attach it to the CButtonExNew object
	bRet = m_wndBtnNew.SubclassWindow(GetDlgItem(IDC_NEW));
	ATLASSERT(bRet);

	// Subclass the edit control and attach it to the CEditEx object
	bRet = m_wndSearchEdit.SubclassWindow(GetDlgItem(IDC_SEARCH_EDIT));
	ATLASSERT(bRet);

	// Subclass the list control and attach it to the CSearchList object
	bRet = m_wndSearchList.SubclassWindow(GetDlgItem(IDC_SEARCH_LIST));
	ATLASSERT(bRet);
	// Pass the pointer to the hidden window to the list control
	m_wndSearchList.SetPointerToHiddenWindow(m_pWndParent);
	
	// Subclass the 'Find Note' static control and attach it to the CLabel object
    bRet = m_wndLblFind.SubclassWindow(GetDlgItem(IDC_STATIC_FIND));
	ATLASSERT(bRet);
	m_wndLblFind.SetFont3D(TRUE,CLabel::Raised)
			.SetText3DHiliteColor(RGB(0, 0, 255))
			.SetFontName("Times New Roman")
			.SetFontSize(16)
			.SetFontBold(TRUE);
						
	// Subclass the 'Look for' static control and attach it to the CLabel object
    bRet = m_wndLblLookFor.SubclassWindow(GetDlgItem(IDC_STATIC_LOOK));
	ATLASSERT(bRet);
	m_wndLblLookFor.SetFontSize(10);
	m_wndLblLookFor.SetFontBold(TRUE);

	// Register object for message filtering and idle updates
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->AddMessageFilter(this);
	pLoop->AddIdleHandler(this);

	return TRUE;
}

LRESULT CSearchDlg::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CloseDialog(0);
	return 0;
}

void CSearchDlg::CloseDialog(int nVal)
{
	// Destroy the search dialog
	DestroyWindow();
}

// Searches for saved note/notes based on a search criteria specified in the search edit control  
LRESULT CSearchDlg::OnFind(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	// Vector to hold the search matches
	vector<CNote> vecResult;

	// Delete all items from the list control, if any
	if (m_wndSearchList.GetItemCount() != 0)
		m_wndSearchList.DeleteAllItems();
	ATLASSERT(m_wndSearchList.GetItemCount() == 0);

	// Retrieve the string to search for
	// (As of now we can only search the notes by text)

	// Obtain the length of the text within the edit control
	// It's OK if the window has no text, in this case search will
	// return all notes
	int nLen = m_wndSearchEdit.GetWindowTextLength();

	// Create the buffer that will receive the text 
	TCHAR * pszToLookFor = new TCHAR[(nLen + 1) * sizeof(TCHAR)];
	if (!pszToLookFor)
		ATLTRACE(_T("Not enough memory to allocate for the buffer\n"));

	pszToLookFor[nLen * sizeof(TCHAR)] = '\0';

	// Copy the text of the edit control into the buffer
	nLen = m_wndSearchEdit.GetWindowText(pszToLookFor, nLen + 1);
	if (nLen == FALSE)
		ATLTRACE(_T("GetWindowText() failed\n"));
  
	// Create the function object
	CFindNotesByString findNotes(pszToLookFor, &vecResult);

	// Iterate over the contents of the vector.
	// Instance of CFindNotesByString class is passed to the 'for_each()' algorithm as its
	// third argument and its operator() is called for each element in the vector.
	// Each element's m_strNoteText value is searched for the specified string.
	for_each(m_pWndParent->m_vecNotes.begin(), m_pWndParent->m_vecNotes.end(), findNotes);

	// Display search results in the list control
	// only if there are matches
	int nIndex;						// zero-based index to the string in the list control
	if (vecResult.size() != 0)		
	{
		vector<CNote>::iterator iter;

		for (iter = vecResult.begin(); iter != vecResult.end(); iter++)
		{
			string strTemp = (*iter).GetNoteText();
			replace(strTemp.begin(), strTemp.end(), '\r', ' ');
			replace(strTemp.begin(), strTemp.end(), '\n', ' ');

			// Add note's text to the list control
			nIndex = m_wndSearchList.InsertItem(0, strTemp.c_str());
			if (nIndex == -1)
				ATLTRACE(_T("Adding the string to the list control failed\n"));

			// Associate the note's id with this item in the list control
			nIndex = m_wndSearchList.SetItemData(nIndex, (*iter).GetNoteID());
			if (nIndex == 0)
				ATLTRACE(_T("Setting the 32-bit value in the list control failed\n"));
		}
	}
	else
	{
		nIndex = m_wndSearchList.InsertItem(0, _T("No matches were found"));
		if (nIndex == -1)
			ATLTRACE(_T("Adding the string to the list control failed\n"));
	}

	delete[] pszToLookFor;
	return 0;
}

LRESULT CSearchDlg::OnNewNote(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	::SendMessage(m_pWndParent->m_hWnd, WM_COMMAND, (WPARAM)ID_POPUP_NEWNOTE, 0);
	return 0;
}