// NoteEdit.h: interface for the CNoteEdit class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NOTEEDIT_H__5FE9A853_AFE7_4DB9_8AE9_074DB729D6AF__INCLUDED_)
#define AFX_NOTEEDIT_H__5FE9A853_AFE7_4DB9_8AE9_074DB729D6AF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define APP_NAME		_T("Sticky Notes")
#define OPEN			_T("open")

class CNoteEdit : public CWindowImpl<CNoteEdit, CRichEditCtrl>,
					public CRichEditCommands<CNoteEdit>
{
private:
	COLORREF m_clrBkgnd;	// background color
	CMenu m_menuEdit;		// context menu
	HCURSOR m_hCursor;

	// Callback function to write file's contents into the rich edit control
	static DWORD CALLBACK CBStreamInFile(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG FAR *pcb)
	{
		ATLASSERT(dwCookie != 0);
		ATLASSERT(pcb != NULL);

		// We insert the rich text here.
		ifstream * pFile = (ifstream*)dwCookie;

		pFile->read((char*)pbBuff, cb);

		// Return the number of characters extracted by the last unformatted input function
		int nReadSize = pFile->gcount();

		*pcb = nReadSize;
		return 0;
	}

	// Callback function to write the rich edit control contents into a file
	static DWORD CALLBACK CBStreamOutFile(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG FAR *pcb)
	{
		ATLASSERT(dwCookie != 0);
		ATLASSERT(pcb != NULL);

		// Write it
		ofstream * pFile = (ofstream*)dwCookie;

		pFile->write((char*)pbBuff, cb);

		*pcb = 2048;
		return 0;
	}

	// Callback function to stream an RTF string into the rich edit control.
	static DWORD CALLBACK CBStreamInRTF(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb)
	{
		ATLASSERT(dwCookie != 0);
		ATLASSERT(pcb != NULL);

		// We insert the rich text here.
		string * pstr = (string*)dwCookie;

		if (pstr->length() < cb)
		{
			*pcb = pstr->length();
			memcpy(pbBuff, (pstr->c_str()), *pcb);
			pstr->resize(0);
		}
		else
		{
			*pcb = cb;
			memcpy(pbBuff, (pstr->c_str()), *pcb);
			*pstr = pstr->substr(pstr->length() - cb, pstr->length());
		}

		return 0;
	}

	// Callback function to stream the RTF string out of the rich edit control.
	static DWORD CALLBACK CBStreamOutRTF(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb)
	{
		ATLASSERT(dwCookie != 0);
		ATLASSERT(pcb != NULL);

		// Address of our string var is in psEntry
		string * pstrEntry = (string*)dwCookie;
		
		string tmpEntry((LPCSTR)pbBuff);

		// Write it
		*pstrEntry += tmpEntry.substr(0, cb);

		return 0;
	}

	// Handles clicking 'Set Font' menu item
	LRESULT OnSetFont(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		ChangeFont();
		return 0;
	}

public:
	DECLARE_WND_SUPERCLASS(NULL, CRichEditCtrl::GetWndClassName())

	BOOL PreTranslateMessage(MSG* pMsg)
	{
		pMsg;
		return FALSE;
	}

	CNoteEdit()
	{
		ATLTRACE(_T("CNoteEdit::CNoteEdit()\n"));
		m_hCursor = NULL;
	}

	~CNoteEdit() 
	{
		ATLTRACE(_T("CNoteEdit::~CNoteEdit()\n"));

		if (m_menuEdit.m_hMenu != NULL)
			m_menuEdit.DestroyMenu();
	}

	BEGIN_MSG_MAP(CNoteEdit)
		// Take care of unhandled reflected messages
		DEFAULT_REFLECTION_HANDLER()
		MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
		MESSAGE_HANDLER(WM_INITMENUPOPUP, OnInitMenuPopup)
		MESSAGE_HANDLER(WM_RBUTTONUP, OnRButtonUp)
		MESSAGE_HANDLER(WM_MOUSEWHEEL, OnMouseWheel)
		CHAIN_MSG_MAP_ALT(CRichEditCommands<CNoteEdit>, 1)
		COMMAND_ID_HANDLER(ID_EDIT_SETFONT, OnSetFont)
	END_MSG_MAP()

	// Changes the control's background color
	void ChangeBkgndColor(COLORREF clrColor)
	{
		m_clrBkgnd = clrColor;
		SetBackgroundColor(m_clrBkgnd);
	}

	// Sets the initial character formatting attributes
	void SetDefaultFont()
	{
		CHARFORMAT cf;
		cf.cbSize = sizeof(CHARFORMAT);

		cf.dwMask = CFM_BOLD|CFM_FACE|CFM_SIZE|CFM_COLOR;
//		cf.dwEffects = CFE_BOLD;
		cf.yHeight = 160;
		cf.crTextColor = BLACK;
		lstrcpyn(cf.szFaceName, _T("Tahoma"), LF_FACESIZE);

		// Set the character formatting attributes for new text
		if (!SetDefaultCharFormat(cf))
			ATLTRACE(_T("Default character formatting was not set successfully!\n"));
	}

	// Changes font
	void ChangeFont()
	{
		CHARFORMAT cf;
		GetSelectionCharFormat(cf);		

		// Display the 'Font' dialog, when user clicks OK, DoModal() returns IDOK.
		CRichEditFontDialog dlg(cf, CF_SCREENFONTS | CF_EFFECTS, 0, m_hWnd);
		
		if (dlg.DoModal() == IDOK)
		{
			ATLASSERT(dlg.m_cf.lpLogFont);

			dlg.GetCharFormat(cf);

			// Set the character formatting attributes for the text in the current
			// selection 
			SetSelectionCharFormat(cf);	
			// De-select the text
			SetSelNone();
		}
		else
			ATLTRACE(_T("Font dialog creation failed!\n"));
	}

	// Saves note's content into a file
	void SaveToFile()
	{
		const TCHAR * szFilters = _T("Text Files (*.txt)\0*.txt\0")
								_T("RTF Files (*.rtf)\0*.rtf\0")
								_T("All Files (*.*)\0*.*\0");

		// Construct a 'File Save As' dialog box
		CFileDialog dlg(FALSE, "txt", "*.txt", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_EXPLORER, szFilters);	

		// Display the file dialog, when user clicks OK, DoModal() returns IDOK.	   
		if (dlg.DoModal() == IDOK)
		{
			ATLASSERT(dlg.m_ofn.lpstrFile);

			// Create a file (truncate an existing file or create a new file for writing). 
			ofstream file;
			file.open(dlg.m_ofn.lpstrFile);
			if (!file.is_open())	
			{
				MessageBox(_T("Could not create a file!"), _T("Sticky Notes - Error"), MB_OK|MB_ICONEXCLAMATION);
				return;
			}
			
			// Create a structure that contains information that an application passes to a rich edit 
			// control. The rich edit control uses the information to transfer a stream of data into 
			// or out of the control. 
			EDITSTREAM es;
			es.dwCookie = (DWORD)&file;
			es.dwError = 0;
			es.pfnCallback = CBStreamOutFile;

			// Call CRichEditCtrl::StreamOut to write out the contents
			StreamOut(SF_TEXT, es);

			file.close();
		}
	}

	// Imports file's content into a note
	void ImportFromFile()
	{
		const TCHAR * szFilters = _T("Text Files (*.txt)\0*.txt\0")
								_T("RTF Files (*.rtf)\0*.rtf\0")
								_T("All Files (*.*)\0*.*\0");

		// Construct a 'File Open' dialog box
		CFileDialog dlg(TRUE, "txt", "*.txt", OFN_HIDEREADONLY | OFN_EXPLORER, szFilters);
		
		// Display the file dialog, when user clicks OK, DoModal() returns IDOK.
		if (dlg.DoModal() == IDOK)
		{
			ATLASSERT(dlg.m_ofn.lpstrFile);

			// Open the selected file. 
			ifstream file;
			file.open(dlg.m_ofn.lpstrFile);
			if (!file.is_open())	
			{
				MessageBox(_T("Could not open a file!"), _T("Sticky Notes - Error"), MB_OK|MB_ICONEXCLAMATION);
				return;
			}
			
			// Create a structure that contains information that an application passes to a rich edit 
			// control. The rich edit control uses the information to transfer a stream of data into 
			// or out of the control. 
			EDITSTREAM es;
			es.dwCookie = (DWORD)&file;
			es.dwError = 0;
			es.pfnCallback = CBStreamInFile;

			// Call CRichEditCtrl::StreamIn to write the file's contents into the control
			StreamIn(SF_TEXT, es);

			file.close();
		}
	}

	LRESULT OnEraseBkgnd(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		// Eliminate the flicker during resizing
		return 1;
	}

	// Modifies the menu before it is displayed
	LRESULT OnInitMenuPopup(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		HMENU hMenuPopup = (HMENU)wParam;
		int nPos;
		UINT uId;

		// Set the cursor shape to an arrow
		m_hCursor = ::LoadCursor(NULL, IDC_ARROW);
		ATLASSERT(m_hCursor);
		::SetCursor(m_hCursor);

		int  nMenuItems = GetMenuItemCount(hMenuPopup); 

		for (nPos = 0; nPos < nMenuItems; nPos++) 
		{ 
			uId = GetMenuItemID(hMenuPopup, nPos); 

			switch (uId) 
			{ 
			case ID_EDIT_UNDO:
				EnableMenuItem(hMenuPopup, uId, CanUndo() ?
											MF_BYCOMMAND | MF_ENABLED : 
											MF_BYCOMMAND | MF_GRAYED);
				break;
			case ID_EDIT_SELECT_ALL:
				EnableMenuItem(hMenuPopup, uId, (GetWindowTextLength() > 0) ?
											MF_BYCOMMAND | MF_ENABLED : 
											MF_BYCOMMAND | MF_GRAYED);
				break;
			case ID_EDIT_CUT: 
			case ID_EDIT_COPY: 
			case ID_EDIT_CLEAR: 
				EnableMenuItem(hMenuPopup, uId, HasSelection() ?
											MF_BYCOMMAND | MF_ENABLED : 
											MF_BYCOMMAND | MF_GRAYED);
				break; 
			case ID_EDIT_PASTE: 
				EnableMenuItem(hMenuPopup, uId, IsClipboardFormatAvailable(CF_TEXT) ? 
											MF_BYCOMMAND | MF_ENABLED : 
											MF_BYCOMMAND | MF_GRAYED);
				break;
			default:
				break;
			}
		} 

		return 0;
	}

	LRESULT OnRButtonUp(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
	{
		if (m_menuEdit.m_hMenu != NULL)
			return 0;

		// Cursor's horizontal and vertical position
		CPoint pt(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)); 

		// Convert client coordinates to screen coordinates 
		ClientToScreen(&pt);

		// Load the menu resource 
		if (!m_menuEdit.LoadMenu(IDR_CONTEXTMENU))
		{
			ATLTRACE(_T("Menu resource was not loaded successfully!\n"));
			return 0;
		}

		// TrackPopupMenu cannot display the menu bar so get 
		// a handle to the first shortcut menu. 
 		CMenuHandle menuPopup = m_menuEdit.GetSubMenu(0);
		if (menuPopup.m_hMenu == NULL)
		{
			ATLTRACE(_T("Submenu was not retrieved successfully!\n"));
			return 0;
		}

		// Display the shortcut menu
 		if (!menuPopup.TrackPopupMenu(TPM_LEFTALIGN|TPM_TOPALIGN|TPM_LEFTBUTTON,
								pt.x, pt.y, m_hWnd))
		{
			ATLTRACE(_T("Context menu was not displayed successfully!\n"));
			return 0;
		}		

		// Destroy the menu and free any memory that the menu occupies
		menuPopup.DestroyMenu();
		m_menuEdit.DestroyMenu();
		m_menuEdit.m_hMenu = NULL;
		return 0;
	}

	// Handles clicking on a hyper link
	void OnLinkClick(ENLINK * pLink)
	{
		// Left button click only
		if (pLink->msg == WM_LBUTTONDOWN)
		{
			// Get a number of consecutive characters in the rich edit control 
			// that have the CFE_LINK effect.
			LONG lMax = pLink->chrg.cpMax;
			LONG lMin = pLink->chrg.cpMin;
			if (lMin == lMax) return;
			
			LONG lNumChar = lMax - lMin;

			// Create the buffer that will receive the text
			TCHAR * pszURL = new TCHAR[(lNumChar + 1) * sizeof(TCHAR)];
			if (!pszURL)
				ATLTRACE(_T("Not enough memory to allocate for the buffer\n"));

			pszURL[lNumChar * sizeof(TCHAR)] = '\0';

			// Retrieve an URL string
			GetTextRange(lMin, lMax, pszURL);

			// Navigate			
			if (!OpenURL(pszURL))
				MessageBox(_T("Could not open an URL!"), APP_NAME, MB_OK | MB_ICONERROR);
			
			delete[] pszURL;
		}
	}

	BOOL OpenURL(TCHAR * pszLink)
	{
		SHELLEXECUTEINFO sei; 
		memset(&sei, 0, sizeof(SHELLEXECUTEINFO));
		sei.cbSize = sizeof(SHELLEXECUTEINFO);
		sei.fMask = SEE_MASK_FLAG_NO_UI;
		sei.hwnd = m_hWnd;
		sei.lpVerb = OPEN;
		sei.lpFile = pszLink;
		sei.nShow = SW_SHOW;

		return ShellExecuteEx(&sei);
	}

	// Return the RTF string of the text in the control.
	string GetRTF()
	{
		// Stream out here.
		EDITSTREAM es;
		es.dwError = 0;
		es.pfnCallback = CBStreamOutRTF;	// set the callback

		string strRTF = EMPTY_STRING;

		es.dwCookie = (DWORD)&strRTF;		// so sRTF receives the string
		
		// Call CRichEditCtrl::StreamOut to get the string.
		StreamOut(SF_RTF, es);			

		return strRTF;
	}

	// Put the RTF string strRTF into the rich edit control.
	void SetRTF(string strRTF)
	{
		// Read the text in
		EDITSTREAM es;
		es.dwError = 0;
		es.pfnCallback = CBStreamInRTF;
		es.dwCookie = (DWORD)&strRTF;

		// Call CRichEditCtrl::StreamIn to put the string.
		StreamIn(SF_RTF, es);
		
		// Clear the modified flag for an edit control
		SetModify(FALSE);
	}

	// Handles WM_MOUSEWHELL message
	LRESULT OnMouseWheel(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		// Determine if a mouse with a wheel is connected
		if (GetSystemMetrics(SM_MOUSEWHEELPRESENT) == FALSE)
		{
			ATLTRACE(_T("Mouse with a wheel is not connected\n"));
			return 0;
		}

		UINT nScrollLines = 0;
		int nZoom = 0;

		// Retrieve the number of lines a note scrolls for each scroll operation (wheel notch)
		SystemParametersInfo(SPI_GETWHEELSCROLLLINES, 0, &nScrollLines, 0);

		// Wheel rotation
		short sDelta = GET_WHEEL_DELTA_WPARAM(wParam);

		// Positive value indicates that the wheel was rotated forward, away from
		// the user; a negative value indicates that the wheel was rotated backward, 
		// toward the user
		(sDelta > 0) ? nZoom-- : nZoom++;

		// Scroll the text
		LineScroll(nZoom * nScrollLines);

		return 0;
	}
};

#endif // !defined(AFX_NOTEEDIT_H__5FE9A853_AFE7_4DB9_8AE9_074DB729D6AF__INCLUDED_)
