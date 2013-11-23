// NoteDlg.cpp : implementation of the CNoteDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "NoteDlg.h"
#include "HiddenWnd.h"
#include "FindNote.h"
#include "TitleDlg.h"

CNoteDlg::CNoteDlg(CHiddenWindow * pWnd) : m_pWndParent(pWnd), m_nHeight(0), m_nWidth(0)
{
	ATLTRACE(_T("CNoteDlg::CNoteDlg()\n"));
	ATLASSERT(pWnd);
	
	InitDefaultValues();
}

CNoteDlg::CNoteDlg(CHiddenWindow * pWnd, const CNote& objNote) : m_pWndParent(pWnd), 
										CNote(objNote), m_nHeight(0), m_nWidth(0)
{
	ATLTRACE(_T("CNoteDlg::CNoteDlg(const CNote& objNote)\n"));
	ATLASSERT(pWnd);
	
	InitDefaultValues();
}

CNoteDlg::~CNoteDlg() 
{
	ATLTRACE(_T("CNoteDlg::~CNoteDlg()\n")); 
	
	// Destroy the brush
	if (!m_brBkgnd.DeleteObject())
		ATLTRACE(_T("Note's brush was not destroyed!\n"));

	// Destroy the bitmaps
	if (!::DeleteObject(m_hBmpNote))
		ATLTRACE(_T("Note bitmap was not destroyed!\n"));
	if (!::DeleteObject(m_hBmpPinopen))
		ATLTRACE(_T("Pinopen bitmap was not destroyed!\n"));
	if (!::DeleteObject(m_hBmpPinclose))
		ATLTRACE(_T("Pinclose bitmap was not destroyed!\n"));
	if (!::DeleteObject(m_hBmpPinhoover))
		ATLTRACE(_T("Pinhoover bitmap was not destroyed!\n"));

	// Destroy the font
	if (!::DeleteObject(m_hFontClose))
		ATLTRACE(_T("Font for a close button was not destroyed!\n"));

	m_Printer.ClosePrinter();
	
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->RemoveMessageFilter(this);
	pLoop->RemoveIdleHandler(this);
}

void CNoteDlg::InitDefaultValues()
{
	m_bAutoDelete = TRUE;
	m_bClosing = false;
	m_hCursor = NULL;
	m_pfSetLayeredWindowAttributes = NULL;
	m_hFontClose = NULL;
	m_bDeleted = false;

	m_rcMargin = CRect(1000, 1000, 1000, 1000);
	m_Printer.OpenDefaultPrinter();
	m_DevMode.CopyFromPrinter(m_Printer);

	SetNoteStatus(Open);	// note is being open
}

// Override GetDialogProc to provide our own DialogProc
// See "Q202110 PRB: Deleting ATL Dialog Causes Assert in Atlwin.h, Line 2281" in MSDN
WNDPROC CNoteDlg::GetDialogProc()
{
	return NoteDialogProc;
}
	
// Our own dialog procedure that is mostly copied from
// CDialogImplBaseT<>::DialogProc() in Atlwin.h.
LRESULT CALLBACK CNoteDlg::NoteDialogProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CNoteDlg * pThis = (CNoteDlg*)hWnd;
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

LRESULT CNoteDlg::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	BOOL bRet;
	HWND hWnd;
	DWORD dwStyle;

	// Create the brush 
	m_brBkgnd.CreateSolidBrush(GetNoteColor());
	
	// Set the sizing border width/height
	m_nSizeFrame = GetSystemMetrics(SM_CXSIZEFRAME);
	
	// Center the dialog on the screen
	CenterWindow();
	
	// Retrieve the coordinates of a dialog's client area
	CRect rectDlg; 
	GetClientRect(&rectDlg);
	
	// Subclass the static control displaying current date and time and 
	// attach it to the CStaticDateTime object
	bRet = m_wndStaticDateTime.SubclassWindow(GetDlgItem(IDC_STATIC_TIME));
	ATLASSERT(bRet);
	// Set the size and position of the control
	m_wndStaticDateTime.MoveWindow(5, rectDlg.Height() - 14, rectDlg.Width() / 2, 14);
	// Set the current date and time
	m_wndStaticDateTime.SetCurrentDateTime(GetTimestamp());
	// Set the background color
	m_wndStaticDateTime.SetBkgndColor(GetNoteColor());
	
	// Subclass the bar static control and attach it to the CGradientStatic object
	bRet = m_wndStaticBar.SubclassWindow(GetDlgItem(IDC_STATIC_BAR));
	ATLASSERT(bRet);
	// Set the size and position of the control
	m_wndStaticBar.MoveWindow(42, 2, rectDlg.Width() - 66, 16);
	// Change the font
	m_wndStaticBar.ChangeFont();
	// Set the note's title
	m_wndStaticBar.SetWindowText(GetNoteTitle().c_str());

	// Subclass the edit control and attach it to the CNoteEdit object
	bRet = m_wndEdit.SubclassWindow(GetDlgItem(IDC_EDIT));
	ATLASSERT(bRet);
	// Set the ENM_LINK mask for a rich edit control to receive 
	// EN_LINK notifications
	m_wndEdit.SetEventMask(ENM_LINK);		
	// Enable automatic detection of URLs by a rich edit control
	m_wndEdit.SetAutoURLDetect();
	// Set the edit control's background color
	m_wndEdit.SetBackgroundColor(GetNoteColor());
	// Sets the initial character formatting attributes
	m_wndEdit.SetDefaultFont();
	// Set the edit control's text
	if (GetNoteRTF().length() != 0)
		m_wndEdit.SetRTF(GetNoteRTF().c_str());
	else
		m_wndEdit.SetWindowText(GetNoteText().c_str());
	// Set the size and position of the control
	m_wndEdit.MoveWindow(5, 20, rectDlg.Width() - 10, rectDlg.Height() - 40);
	
	// Create the static control holding the 'Note' bitmap
	CRect rectStatic(1, 2, 17, 18);
	hWnd = m_wndStaticNote.Create(m_hWnd, rectStatic, NULL,
		WS_CHILD|WS_VISIBLE|SS_BITMAP|SS_CENTERIMAGE|SS_NOTIFY);
	ATLASSERT(hWnd);
	
	// Create the button with the 'Close' bitmap
	rectStatic.SetRect(rectDlg.right - 21, 1, rectDlg.right - 1, 20);
	hWnd = m_wndBtnClose.Create(m_hWnd, rectStatic, NULL, 0, 0);
	ATLASSERT(hWnd);

	m_hFontClose = ::CreateFont(15, 0, 0, 0, FW_SEMIBOLD, 0, 0, 0, 1, 0, 0, 4, 
					FF_DONTCARE, _T("Marlett"));
	ATLASSERT(m_hFontClose);
	m_wndBtnClose.SetFont(m_hFontClose);
	m_wndBtnClose.SetTextColor(BLACK);
	m_wndBtnClose.SetColor(GetNoteColor());
	m_wndBtnClose.SetWindowText((TCHAR*)"\x72");		// 'x' sign
	m_wndBtnClose.SetToolTipText(_T("Close the note"));

	// Create the button with the 'Pin' bitmap
	rectStatic.SetRect(19, 1, 39, 21);
	hWnd = m_wndBtnPin.Create(m_hWnd, rectStatic, NULL, 0, 0);
	ATLASSERT(hWnd);
	// Change the button extended style
	dwStyle = BMPBTN_AUTOSIZE | BMPBTN_AUTO3D_SINGLE | BMPBTN_HOVER | BTNEX_CHECKBUTTON;
	m_wndBtnPin.SetBitmapButtonExtendedStyle(dwStyle);

	// Load the 'Pinopen' bitmap from the application's resources
	HBITMAP hBmpTemp2 = ::LoadBitmap(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDB_PINOPEN));
	ATLASSERT(hBmpTemp2);
	// Load the 'Pinclose' bitmap from the application's resources
	HBITMAP hBmpTemp3 = ::LoadBitmap(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDB_PINCLOSE));
	ATLASSERT(hBmpTemp3);
	// Load the 'Pinhoover' bitmap from the application's resources
	HBITMAP hBmpTemp4 = ::LoadBitmap(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDB_PINHOOVER));
	ATLASSERT(hBmpTemp4);
	
	// Replace the white background color with the saved or default (yellow) note's color
	m_hBmpPinopen = ReplaceColor(hBmpTemp2, WHITE, GetNoteColor());
	ATLASSERT(m_hBmpPinopen);
	// Replace the white background color with the saved or default (yellow) note's color
	m_hBmpPinclose = ReplaceColor(hBmpTemp3, WHITE, GetNoteColor());
	ATLASSERT(m_hBmpPinclose);
	// Replace the white background color with the saved or default (yellow) note's color
	m_hBmpPinhoover = ReplaceColor(hBmpTemp4, WHITE, GetNoteColor());
	ATLASSERT(m_hBmpPinhoover);
	
	// Create the pin button's imagelist
	m_wndBtnPin.m_ImageList.Create(20, 20, ILC_COLORDDB | ILC_MASK, 3, 1);
	// Add images to the image list.
	m_wndBtnPin.m_ImageList.Add(m_hBmpPinopen);
	m_wndBtnPin.m_ImageList.Add(m_hBmpPinclose);
	m_wndBtnPin.m_ImageList.Add(m_hBmpPinhoover);
	// Set normal, pressed and hover images
	m_wndBtnPin.SetImages(0, 1, 2);
	// ToolTip text
	m_wndBtnPin.SetToolTipText(_T("Keep the Note Visible"));

	// Load the 'Note' bitmap from the application's resources
	HBITMAP hBmpTemp1 = ::LoadBitmap(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDB_NOTE));
	ATLASSERT(hBmpTemp1);

	// Replace the white background color with the saved or default (yellow) note's color
	m_hBmpNote = ReplaceColor(hBmpTemp1, WHITE, GetNoteColor());
	ATLASSERT(m_hBmpNote);

	// Delete the original bitmaps
	DeleteObject(hBmpTemp1);
	DeleteObject(hBmpTemp2);
	DeleteObject(hBmpTemp3);
	DeleteObject(hBmpTemp4);

	// Draw the 'Note' bitmap in the static control
	m_wndStaticNote.SetBitmap(m_hBmpNote);
	
	// To support a transparency try to get a SetLayeredWindowAttributes function address
	// and set WS_EX_LAYERED style
	HMODULE hUser32 = GetModuleHandle(_T("User32.dll"));
	if (hUser32)
	{
		m_pfSetLayeredWindowAttributes = 
			(PFUNCSETLAYEREDWINDOWATTR)::GetProcAddress(hUser32, "SetLayeredWindowAttributes");
		if (m_pfSetLayeredWindowAttributes)
		{
			::SetWindowLong(m_hWnd, GWL_EXSTYLE, GetWindowLong(GWL_EXSTYLE)^WS_EX_LAYERED);
			// After the SetWindowLong call, the layered window will not become visible 
			// until the SetLayeredWindowAttributes function has been called for this window
			m_pfSetLayeredWindowAttributes(m_hWnd, 0, (BYTE)255, LWA_ALPHA);

			// Set the transparency of the note dialog
			MakeTransparent(GetNoteAlpha());
		}
	}

	// Register object for message filtering and idle updates
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->AddMessageFilter(this);
	pLoop->AddIdleHandler(this);

	return TRUE;
}

LRESULT CNoteDlg::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CloseDialog(0);

	return 0;
}

void CNoteDlg::CloseDialog(int nVal)
{
	m_bClosing = true;		// note is being closed

	// The app in not being closed so change the note's status to 'closed'
	if (!IsAppClosing())
		SetNoteStatus(Close);

	// Display a prompt dialog asking an user if a note should be saved
	// but only if the text has been modified in the edit control
	if (m_wndEdit.GetModify())
	{
		int nRet = MessageBox(_T("The text in the note has changed.\n\nDo you want to save the changes?"), 
								_T("StickyNotes"),
								MB_YESNOCANCEL|MB_ICONEXCLAMATION);

		if (nRet == IDCANCEL)	// 'Cancel' button - do not do anything 
			return;
		if (nRet == IDYES)		// 'Yes' button - save the note's text also
			OnSave(true);
		if (nRet == IDNO)		// 'No' button - only save the note's attributes
			OnSave(false);
	}
	else
		// Text has not been modified so save the note's attributes only
		OnSave(false);			

	// Add a note's text and a note's id to the collection of recently accessed notes
	if (GetNoteText().length() != 0)
	{
		(m_pWndParent->m_RecNotes).AddItemToCollection(GetNoteText(), GetNoteID());
	}

	// Remove it from the collection of the opened notes
	m_pWndParent->RemoveFromListOfOpenNotes(GetNoteID());

	// Destroy the Note dialog
	DestroyWindow();
}

LRESULT CNoteDlg::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	PAINTSTRUCT ps;
	HDC hDC = BeginPaint(&ps);
	ATLASSERT(hDC);
	
	CDC cDC;
	cDC.Attach(hDC);
	
	HPEN hOldPen, hPenLine;
	
	CRect rectDlg; 
	GetClientRect(&rectDlg);
	
	// Create a grey pen
	hPenLine = ::CreatePen(PS_SOLID, 1, GREY);
	ATLASSERT(hPenLine);	
	
	// Select the new pen into the device context
	hOldPen = (HPEN)::SelectObject(hDC, hPenLine);
	ATLASSERT(hOldPen);
	ATLASSERT(hOldPen != HGDI_ERROR);
	
	// Draw the gripper
	cDC.MoveTo(rectDlg.Width() - 15, rectDlg.Height());
	cDC.LineTo(rectDlg.Width(), rectDlg.Height() - 15);
	cDC.MoveTo(rectDlg.Width() - 11, rectDlg.Height());
	cDC.LineTo(rectDlg.Width(), rectDlg.Height() - 11);
	cDC.MoveTo(rectDlg.Width() - 7, rectDlg.Height());
	cDC.LineTo(rectDlg.Width(), rectDlg.Height() - 7);
	cDC.MoveTo(rectDlg.Width() - 3, rectDlg.Height());
	cDC.LineTo(rectDlg.Width(), rectDlg.Height() - 3);
	
	// Draw the horisontal line
	cDC.MoveTo(5, rectDlg.Height() - 15);
	cDC.LineTo(rectDlg.Width() - 5, rectDlg.Height() - 15);
	
	// Clean up
	::SelectObject(hDC, hOldPen);
	::DeleteObject(hPenLine);
	hPenLine = NULL;
	
	cDC.Detach();
	EndPaint(&ps);
	return 0;
}

LRESULT CNoteDlg::OnDlgColor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	ATLASSERT(m_brBkgnd.m_hBrush);
	
	// Change the dialog's background color
	return (LRESULT)m_brBkgnd.m_hBrush;
}

// Determine the location of the specified point relative to the client area
// of a dialog.
// point - contains the x- and y-coordinates of the cursor.
int CNoteDlg::HitTest(CPoint point)
{
	CRect rc;
	int nRes = HT_NOWHERE;
	
	GetClientRect(&rc);
	// Bar rectangle
	CRect rcBar(rc.left + 42, 0, rc.right - 22, 20);

	if (point.x <= m_nSizeFrame)
	{
		// Handle top left, bottom left and left sizing
		if (point.y <= m_nSizeFrame)
			nRes = HT_TOPLEFT;
		else if (point.y >= rc.Height() - m_nSizeFrame)
			nRes = HT_BOTTOMLEFT;
		else 
			nRes = HT_LEFT;
	}
	else if (point.x >= rc.Width() - m_nSizeFrame)
	{
		// Handle top right, bottom right and right sizing
		if (point.y <= m_nSizeFrame)
			nRes = HT_TOPRIGHT;
		else if (point.y <= rc.Height() - m_nSizeFrame)
			nRes = HT_RIGHT;
		else 
			nRes = HT_BOTTOMRIGHT;
	}
	else if (point.y <= m_nSizeFrame)
	{
		// Handle top sizing
		nRes = HT_TOP;
	}
	else if (point.y >= rc.Height() - m_nSizeFrame)
	{
		// Handle bottom sizing
		nRes = HT_BOTTOM;
	}
	else if (rcBar.PtInRect(point))
	{
		// Handle the dialog moving
		nRes = HT_BAR;
	}
	
	return nRes;
}

LRESULT CNoteDlg::OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	// Get the coordinates of the cursor
	CPoint point((DWORD)lParam);
	
	int nHitCode = HitTest(point);
	
	// Load the appropriate cursor based on the cursor's location
	switch (nHitCode)
	{
	case HT_TOP:
	case HT_BOTTOM:
		m_hCursor = ::LoadCursor(NULL, IDC_SIZENS);
		break;
		
	case HT_LEFT:
	case HT_RIGHT:
		m_hCursor = ::LoadCursor(NULL, IDC_SIZEWE);
		break;
		
	case HT_TOPLEFT:
	case HT_BOTTOMRIGHT:
		m_hCursor = ::LoadCursor(NULL, IDC_SIZENWSE);
		break;
		
	case HT_TOPRIGHT:
	case HT_BOTTOMLEFT:
		m_hCursor = ::LoadCursor(NULL, IDC_SIZENESW);
		break;
		
	case HT_NOWHERE:
		m_hCursor = ::LoadCursor(NULL, IDC_ARROW);
		break;
	default:
		m_hCursor = ::LoadCursor(NULL, IDC_ARROW);
		break;
	}
	ATLASSERT(m_hCursor);
	
	// Set the cursor shape
	::SetCursor(m_hCursor);
	
	return 0;
}

LRESULT CNoteDlg::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	// Keep the current cursor shape
	if (m_hCursor)
		::SetCursor(m_hCursor);
	
	// Get the coordinates of the cursor
	CPoint point((DWORD)lParam);
	
	int nHitCode = HitTest(point);
	
	if (nHitCode != HT_NOWHERE)
	{
		// Resize the window
		SendMessage(WM_SYSCOMMAND, SC_SIZE|nHitCode);
	}
	else if (nHitCode == HT_BAR)
	{
		// Move the dialog
		SendMessage(WM_SYSCOMMAND, SC_MOVE|0x0002);
	}
	
	return 0;
}

LRESULT CNoteDlg::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	int xPos = (int)LOWORD(lParam);   // new width of the client area 
	int yPos = (int)HIWORD(lParam);   // new height of the client area 
	
	// Move the button that holds the 'Close' image
	CRect rectClose(xPos - 21, 1, xPos - 1 , 20);
	m_wndBtnClose.MoveWindow(&rectClose, false);

	// Move the static control that displays the date and time
	m_wndStaticDateTime.MoveWindow(5, yPos - 14, xPos / 2, 14, false);
	
	// Move the static bar control
	m_wndStaticBar.MoveWindow(42, 2, xPos - 66, 16, false);

	// Move the edit control
	m_wndEdit.MoveWindow(5, 20, xPos - 10, yPos - 40, false);
	
	// Invalidate the dialog's client area
	Invalidate();
	return 0;
}

LRESULT CNoteDlg::OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	LPMINMAXINFO lpMMI = (LPMINMAXINFO)lParam;

	// Limit the size of the dialog to some minimum to avoid being able to resize
	// the dialog to a line or a dot.
	CRect rectClose;
	m_wndBtnClose.GetWindowRect(&rectClose);

	lpMMI->ptMinTrackSize.x = rectClose.Width() * 4;
	lpMMI->ptMinTrackSize.y = rectClose.Width() * 2;
	return 0;
}

// Handles clicking on 'New Note' menu item.
void CNoteDlg::OnNewNote()
{
	// Send a message to the parent to create a new Note dialog
	::SendMessage(m_pWndParent->m_hWnd, WM_COMMAND, (WPARAM)ID_POPUP_NEWNOTE, 0);
}

void CNoteDlg::SetTopMost()
{
	// If the flag is set to true then place the dialog above all windows,
	// if it's not then do the opposite.
	// Reset the flag.
	if (GetAlwaysOnTop())
	{
		SetWindowPos(HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE);
		SetAlwaysOnTop(false);

		// Reset the button's internal state
		m_wndBtnPin.m_fPressed = 0;
	}
	else
	{
		SetWindowPos(HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE);
		SetAlwaysOnTop(true);

		// Reset the button's internal state
		m_wndBtnPin.m_fPressed = 1;
	}
}

// Handles WMU_SETTOPMOST message
LRESULT CNoteDlg::OnSetTopMost(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	SetTopMost();

	return 0;
}

// Handles clicking on different colors on the menu
void CNoteDlg::OnChangeBkgndColor(COLORREF clrColor)
{
	ATLASSERT(m_brBkgnd.m_hBrush);
	
	// Change the dialog's background color
	m_brBkgnd.DeleteObject();
	m_brBkgnd.CreateSolidBrush(clrColor);
	Invalidate();
	
	// Change the background color of the control displaying date and time
	m_wndStaticDateTime.ChangeBkgndColor(clrColor);
	
	// Change the background color of the edit control 
	m_wndEdit.ChangeBkgndColor(clrColor);

	// Change the background color of the 'Note' bitmap
	HBITMAP hBmpOldNote = m_wndStaticNote.GetBitmap();
	m_hBmpNote = NULL;
	m_hBmpNote = ReplaceColor(hBmpOldNote, GetNoteColor(), clrColor);

	// Change the background color of the 'Close' button
	m_wndBtnClose.SetColor(clrColor);

	// Change the background color of the 'Pin' bitmaps
	CImageList imageList = m_wndBtnPin.GetImageList();
	m_hBmpPinopen = ReplaceColor(m_hBmpPinopen, GetNoteColor(), clrColor);
	m_hBmpPinclose = ReplaceColor(m_hBmpPinclose, GetNoteColor(), clrColor);
	m_hBmpPinhoover = ReplaceColor(m_hBmpPinhoover, GetNoteColor(), clrColor);
	// Replace the images in the image list 
	imageList.Replace(0, m_hBmpPinopen, 0);
	imageList.Replace(1, m_hBmpPinclose, 0);
	imageList.Replace(2, m_hBmpPinhoover, 0);

	// Draw the new 'Note' bitmap in the static control
	m_wndStaticNote.SetBitmap(m_hBmpNote);

	// Delete the old bitmaps
	DeleteObject(hBmpOldNote);

	// Save the color
	SetNoteColor(clrColor);
}

// Handles clicking on 'Set font' menu item
void CNoteDlg::OnSetFont()
{
	// Change font in the edit control
	m_wndEdit.ChangeFont();
}

// Saves note's text
void CNoteDlg::SaveNoteText()
{
	// Obtain the length of the text within the edit control
	int nLen = m_wndEdit.GetTextLengthEx();
	if (nLen == 0)
		return;
	
	// Create the buffer that will receive the text 
	TCHAR * pszText = new TCHAR[(nLen + 1) * sizeof(TCHAR)];
	if (!pszText)
		ATLTRACE(_T("Not enough memory to allocate for the buffer.\n"));
	
	pszText[nLen * sizeof(TCHAR)] = '\0';
	
	// Copy the text of the edit control into the buffer
	if (!m_wndEdit.GetTextEx(pszText, nLen + 1))
		ATLTRACE(_T("GetTextEx() failed.\n"));
	
	// Set the note's test
	SetNoteText(pszText);
	delete[] pszText;
	
	// Set the note's RTF formatting code
	SetNoteRTF(m_wndEdit.GetRTF());
}

// Saves note's rectangle (position)
void CNoteDlg::SaveNotePosition()
{
	CRect rcNote;

	// Retrieve the dimensions of the bounding rectangle
	GetWindowRect(&rcNote);

	// Set it
	SetNoteRect(rcNote);
}

// Handles clicking on 'Save' menu item.
// If bSaveAll is true means save note's attributes and a text,
// if bSaveAll is false means save only note's attributes
void CNoteDlg::OnSave(bool bSaveAll)
{
	vector<CNote>::iterator iter;
	bool bFound = false;

	// Let's see if this note was saved already
	for (iter = (m_pWndParent->m_vecNotes).begin(); iter != (m_pWndParent->m_vecNotes).end(); iter++)
	{
		if ((*iter).GetNoteID() == GetNoteID())	// note is in the collection
		{
			bFound = true;
			break;
		}
	}

	// Save note's text but only if the user said so
	if (bSaveAll)
		SaveNoteText();

	// Save note's size and position
	SaveNotePosition();

	// Get a note object
	CNote * pNote = this;

	// Save the note but only if the note is not empty
	if (GetNoteText().length() != 0)
	{
		if (bFound)			// note already exists
		{
			*iter = *pNote;
		}
		else				// it's a new note
		{
			// Insert a CNote object at the end of the vector
			(m_pWndParent->m_vecNotes).push_back(*pNote);
		}

		// Post a message to the parent to persist all notes
		::PostMessage(m_pWndParent->m_hWnd, WMU_PERSISTNOTES, 0, 0);
	}

	if (bSaveAll)
	{
		// Clear the modified flag for an edit control
		m_wndEdit.SetModify(FALSE);
	}
}

// Handles clicking on 'Delete' menu item
void CNoteDlg::OnDelete()
{
	// ID of the note being deleted
	if (GetNoteID() != 0)
	{
		// Delete a note from the collection
		if (::SendMessage(m_pWndParent->m_hWnd, WMU_DELETENOTE, (WPARAM)GetNoteID(), 0))
		{
			// Note was deleted successfully
			m_bDeleted = true;
			// Destroy the Note dialog
			DestroyWindow();
		}
		else
			ATLTRACE(_T("Note has not been deleted!\n"));
	}
}

// Handles clicking on 'Save To File' menu item
void CNoteDlg::OnSaveToFile()
{
	m_wndEdit.SaveToFile();
}

// Handles clicking on 'Import From File' menu item
void CNoteDlg::OnImportFromFile()
{
	m_wndEdit.ImportFromFile();
}

// Handles a menu item selection
LRESULT CNoteDlg::OnCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	switch (LOWORD(wParam))
	{
	case IDR_MENU_NEWNOTE:
		OnNewNote();
		break;
	case IDR_MENU_SAVE:
		OnSave(true);
		break;
	case IDR_MENU_SAVETOFILE:
		OnSaveToFile();
		break;
	case IDR_MENU_IMPORTFROMFILE:
		OnImportFromFile();
		break;
	case IDR_MENU_DELETE:
		OnDelete();
		break;
	case IDR_MENU_SETFONT:
		OnSetFont();
		break;
	case ID_EDIT_SETTITLE:
		OnSetTitle();
		break;
	case IDR_MENU_CLOSE:
		CloseDialog(0);
		break;
	case IDR_MENU_BLUE:
		OnChangeBkgndColor(BLUE);
		break;
	case IDR_MENU_GREEN:
		OnChangeBkgndColor(GREEN);
		break;
	case IDR_MENU_PINK:
		OnChangeBkgndColor(PINK);
		break;
	case IDR_MENU_YELLOW:
		OnChangeBkgndColor(YELLOW);
		break;
	case IDR_MENU_WHITE:
		OnChangeBkgndColor(WHITE);
		break;
	case IDR_MENU_0:
		MakeTransparent(255);
		break;
	case IDR_MENU_10:
		MakeTransparent(225);
		break;
	case IDR_MENU_20:
		MakeTransparent(200);
		break;
	case IDR_MENU_30:
		MakeTransparent(175);
		break;
	case IDR_MENU_40:
		MakeTransparent(150);
		break;
	case IDR_MENU_50:
		MakeTransparent(125);
		break;
	case IDR_MENU_60:
		MakeTransparent(100);
		break;
	case IDR_MENU_70:
		MakeTransparent(75);
		break;
	case IDR_MENU_80:
		MakeTransparent(50);
		break;
	case IDR_MENU_90:
		MakeTransparent(25);
		break;
	case ID_FILE_PAGE_SETUP:
		OnPageSetup();
		break;
	case ID_FILE_PRINT:
		OnPrint();
		break;
	default:
		break;
	}

	return 0;
}

// When the previously saved note is displayed the whole text inside the
// richedit control is initially selected. So this function fixes it.
void CNoteDlg::UnselectText()
{
	m_wndEdit.SetSelNone();
}

//-----------------------------------------------------------------------------------
// ReplaceColor
//
// Author	:	Dimitri Rochette drochette@ltezone.net
// Article  :	"How to replace a color in a HBITMAP" (www.codeproject.com)
//
// hBmp		:	Source Bitmap
// cOldColor:	Color to replace in hBmp
// cNewColor:	Color used for replacement
// hBmpDC   :	DC of hBmp ( default NULL ) could be NULL if hBmp is not selected
//
// Retcode	:	HBITMAP of the modified bitmap or NULL for errors
//
//-----------------------------------------------------------------------------------

#define COLORREF2RGB(Color) (Color & 0xff00) | ((Color >> 16) & 0xff) | ((Color << 16) & 0xff0000)

HBITMAP CNoteDlg::ReplaceColor(HBITMAP hBmp, COLORREF cOldColor, COLORREF cNewColor, HDC hBmpDC)
{
    HBITMAP RetBmp = NULL;
    if (hBmp)
    {	
        HDC BufferDC = CreateCompatibleDC(NULL);	// DC for Source Bitmap
		if (BufferDC)
		{
			HBITMAP hTmpBitmap = (HBITMAP) NULL;
			if (hBmpDC)
				if (hBmp == (HBITMAP)GetCurrentObject(hBmpDC, OBJ_BITMAP))
				{
					hTmpBitmap = CreateBitmap(1, 1, 1, 1, NULL);
					SelectObject(hBmpDC, hTmpBitmap);
				}
				
				HGDIOBJ PreviousBufferObject = SelectObject(BufferDC,hBmp);
				// Here BufferDC contains the bitmap
				
				HDC DirectDC = CreateCompatibleDC(NULL); // DC for working		
				if (DirectDC)
				{
					// Get bitmap size
					BITMAP bm;
					GetObject(hBmp, sizeof(bm), &bm);
					
					// Create a BITMAPINFO with minimal initilisation 
					// for the CreateDIBSection
					BITMAPINFO RGB32BitsBITMAPINFO; 
					ZeroMemory(&RGB32BitsBITMAPINFO,sizeof(BITMAPINFO));
					RGB32BitsBITMAPINFO.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
					RGB32BitsBITMAPINFO.bmiHeader.biWidth = bm.bmWidth;
					RGB32BitsBITMAPINFO.bmiHeader.biHeight = bm.bmHeight;
					RGB32BitsBITMAPINFO.bmiHeader.biPlanes = 1;
					RGB32BitsBITMAPINFO.bmiHeader.biBitCount = 32;
					
					// Pointer used for direct Bitmap pixels access
					UINT * ptPixels;	
					
					HBITMAP DirectBitmap = CreateDIBSection(DirectDC, 
						(BITMAPINFO *)&RGB32BitsBITMAPINFO, 
						DIB_RGB_COLORS,
						(void **)&ptPixels, 
						NULL, 0);
					if (DirectBitmap)
					{
						// Here DirectBitmap!=NULL so ptPixels!=NULL no need to test
						HGDIOBJ PreviousObject = SelectObject(DirectDC, DirectBitmap);
						BitBlt(DirectDC,0,0,
							bm.bmWidth,bm.bmHeight,
							BufferDC,0,0,SRCCOPY);					
						// Here the DirectDC contains the bitmap
						
						// Convert COLORREF to RGB (Invert RED and BLUE)
						cOldColor = COLORREF2RGB(cOldColor);
						cNewColor = COLORREF2RGB(cNewColor);
						
						// After all the inits we can do the job : Replace Color
						for (int i=((bm.bmWidth*bm.bmHeight)-1); i>=0; i--)
						{
							if (ptPixels[i] == cOldColor) ptPixels[i] = cNewColor;
						}
						// Little clean up
						// Don't delete the result of SelectObject because it's 
						// our modified bitmap (DirectBitmap)
						SelectObject(DirectDC,PreviousObject);
						
						// Finish
						RetBmp = DirectBitmap;
					}
					// Clean up
					DeleteDC(DirectDC);
				}			
				if (hTmpBitmap)
				{
					SelectObject(hBmpDC, hBmp);
					DeleteObject(hTmpBitmap);
				}
				SelectObject(BufferDC,PreviousBufferObject);
				// BufferDC is now useless
				DeleteDC(BufferDC);
		}
    }
    return RetBmp;
}

// Handles double clicking on a title bar
LRESULT CNoteDlg::OnLButtonDblClk(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect rcNote;	// note rectangle	
	CRect rcBar;	// bar rectangle
	
	// Retrieve the dimensions of the bounding rectangles
	GetWindowRect(&rcNote);
	m_wndStaticBar.GetWindowRect(&rcBar);

	ScreenToClient(&rcBar);

	// Get the coordinates of the cursor
	CPoint point(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
	
	// See if the cursor is within the bar rectangle
	if (rcBar.PtInRect(point))
	{
		if (IsDialogFullSize(rcNote, rcBar))
		{
			// Save the dialog's full size
			m_nHeight = rcNote.Height();
			m_nWidth = rcNote.Width();

			// Shrink the dialog's size
			SetWindowPos(HWND_TOP, 0, 0, m_nWidth, rcBar.Height() + 25, SWP_NOMOVE);
		}
		else
		{
			// Maximize the dialog's size
			SetWindowPos(HWND_TOP, 0, 0, m_nWidth, m_nHeight, SWP_NOMOVE);
		}
	}

	return TRUE;
}

// Checks if the dialog in in full size
bool CNoteDlg::IsDialogFullSize(CRect& rcNote, CRect& rcBar)
{
	return (rcNote.Height() > (rcBar.Height() + 25));
}

// Sets the transparency of the note dialog
void CNoteDlg::MakeTransparent(int nAlpha)
{
	// Save the opacity
	SetNoteAlpha(nAlpha);

	if (m_pfSetLayeredWindowAttributes)
		m_pfSetLayeredWindowAttributes(m_hWnd, 0, (BYTE)nAlpha, LWA_ALPHA);
	else
		MessageBox(_T("Your OS does not support this feature"), APP_NAME, MB_ICONEXCLAMATION);
}

bool CNoteDlg::LayoutPages()
{
	CDC dc = m_Printer.CreatePrinterDC(m_DevMode);
	if(dc.IsNull())
		return false;
	
	RECT rcPage;
	rcPage.left = rcPage.top = 0;
	rcPage.bottom = GetDeviceCaps(dc, PHYSICALHEIGHT);
	rcPage.right = GetDeviceCaps(dc, PHYSICALWIDTH);
	// We have to adjust the origin because 0,0 is not at the corner of the paper
	// but is at the corner of the printable region
	int nOffsetX = dc.GetDeviceCaps(PHYSICALOFFSETX);
	int nOffsetY = dc.GetDeviceCaps(PHYSICALOFFSETY);
	dc.SetViewportOrg(-nOffsetX, -nOffsetY);
	rcPage.right = MulDiv(rcPage.right, 1440, GetDeviceCaps(dc, LOGPIXELSX));
	rcPage.bottom = MulDiv(rcPage.bottom, 1440, GetDeviceCaps(dc, LOGPIXELSY));
	
	RECT rcOutput = rcPage;
	// Convert from 1/1000" to twips
	rcOutput.left += MulDiv(m_rcMargin.left, 1440, 1000);
	rcOutput.right -= MulDiv(m_rcMargin.right, 1440, 1000);
	rcOutput.top += MulDiv(m_rcMargin.top, 1440, 1000);
	rcOutput.bottom -= MulDiv(m_rcMargin.bottom, 1440, 1000);
	
	FORMATRANGE fr;
	fr.hdc = dc.m_hDC;
	fr.hdcTarget = dc.m_hDC;
	fr.rc = rcOutput;
	fr.rcPage = rcPage;
	fr.chrg.cpMin = 0;
	fr.chrg.cpMax = -1;
	
	LONG n = (LONG)m_wndEdit.GetTextLength();
	m_arrPages.RemoveAll();
	LONG lRet;
	while (1)
	{
		m_arrPages.Add(fr.chrg.cpMin);
		lRet = m_wndEdit.FormatRange(fr, FALSE);

		if ((lRet - fr.chrg.cpMin) == -1)
		{
			m_arrPages.RemoveAt(m_arrPages.GetSize() - 1);
			break;
		}
		else
			fr.chrg.cpMin = lRet;

		if (fr.chrg.cpMin >= n)
			break;
	}

	// Tell the control to release cached information
	m_wndEdit.FormatRange(NULL, FALSE);

	return true;
}

// Handles clicking on 'Page Setup' menu item
void CNoteDlg::OnPageSetup()
{
	CPageSetupDialog dlg;
	dlg.m_psd.hDevMode = m_DevMode.CopyToHDEVMODE();
	dlg.m_psd.hDevNames = m_Printer.CopyToHDEVNAMES();
	dlg.m_psd.rtMargin = m_rcMargin;
	
	if (dlg.DoModal() == IDOK)
	{
		m_DevMode.CopyFromHDEVMODE(dlg.m_psd.hDevMode);
		m_Printer.ClosePrinter();
		m_Printer.OpenPrinter(dlg.m_psd.hDevNames, m_DevMode.m_pDevMode);
		m_rcMargin = dlg.m_psd.rtMargin;
	}
	
	GlobalFree(dlg.m_psd.hDevMode);
	GlobalFree(dlg.m_psd.hDevNames);
}

bool CNoteDlg::PrintPage(UINT nPage, HDC hDC)
{
	if (nPage >= (UINT)m_arrPages.GetSize())
		return false;
	
	RECT rcPage;
	rcPage.left = rcPage.top = 0;
	rcPage.bottom = GetDeviceCaps(hDC, PHYSICALHEIGHT);
	rcPage.right = GetDeviceCaps(hDC, PHYSICALWIDTH);
	
	rcPage.right = MulDiv(rcPage.right, 1440, GetDeviceCaps(hDC, LOGPIXELSX));
	rcPage.bottom = MulDiv(rcPage.bottom, 1440, GetDeviceCaps(hDC, LOGPIXELSY));
	
	RECT rcOutput = rcPage;
	// Convert from 1/1000" to twips
	rcOutput.left += MulDiv(m_rcMargin.left, 1440, 1000);
	rcOutput.right -= MulDiv(m_rcMargin.right, 1440, 1000);
	rcOutput.top += MulDiv(m_rcMargin.top, 1440, 1000);
	rcOutput.bottom -= MulDiv(m_rcMargin.bottom, 1440, 1000);
	
	
	FORMATRANGE fr;
	fr.hdc = hDC;
	fr.hdcTarget = hDC;
	fr.rc = rcOutput;
	fr.rcPage = rcPage;
	fr.chrg.cpMin = 0;
	fr.chrg.cpMax = -1;
	fr.chrg.cpMin = m_arrPages[nPage];
	
	// We have to adjust the origin because 0,0 is not at the corner of the paper
	// but is at the corner of the printable region
	int nOffsetX = GetDeviceCaps(hDC, PHYSICALOFFSETX);
	int nOffsetY = GetDeviceCaps(hDC, PHYSICALOFFSETY);
	SetViewportOrgEx(hDC, -nOffsetX, -nOffsetY, NULL);
	m_wndEdit.FormatRange(fr, TRUE);
	m_wndEdit.DisplayBand(&rcOutput);
	
	// Tell the control to release cached information
	m_wndEdit.FormatRange(NULL, FALSE);
	return true;
}

// Handles clicking on 'Print' menu item
void CNoteDlg::OnPrint()
{
	if(!LayoutPages())
	{
		MessageBox(_T("Print operation failed"), APP_NAME, MB_ICONERROR | MB_OK);
		return;
	}
	
	CPrintDialog dlg(FALSE);
	dlg.m_pd.hDevMode = m_DevMode.CopyToHDEVMODE();
	dlg.m_pd.hDevNames = m_Printer.CopyToHDEVNAMES();
	dlg.m_pd.nMinPage = 1;
	dlg.m_pd.nMaxPage = (WORD)m_arrPages.GetSize();
	dlg.m_pd.nFromPage = 1;
	dlg.m_pd.nToPage = (WORD)m_arrPages.GetSize();
	dlg.m_pd.Flags &= ~PD_NOPAGENUMS;
	
	if (dlg.DoModal() == IDOK)
	{
		m_DevMode.CopyFromHDEVMODE(dlg.m_pd.hDevMode);
		m_Printer.ClosePrinter();
		m_Printer.OpenPrinter(dlg.m_pd.hDevNames, m_DevMode.m_pDevMode);
		
		CPrintJob job;
		int nMin = 0;
		int nMax = m_arrPages.GetSize() - 1;
		if(dlg.PrintRange() != FALSE)
		{
			nMin = dlg.m_pd.nFromPage - 1;
			nMax = dlg.m_pd.nToPage - 1;
		}
		
		job.StartPrintJob(false, m_Printer, m_DevMode.m_pDevMode, this, 
			APP_NAME, nMin, nMax, (dlg.PrintToFile() != FALSE));
	}
	
	::GlobalFree(dlg.m_pd.hDevMode);
	::GlobalFree(dlg.m_pd.hDevNames);
}

// Handler for EN_LINK message which is sent by a rich edit control when 
// it receives various messages, for example, when the user clicks the mouse 
// or when the mouse pointer is over text that has the CFE_LINK effect.
LRESULT CNoteDlg::OnLink(int idCtrl, LPNMHDR pnmh, BOOL& bHandled)
{
	m_wndEdit.OnLinkClick((ENLINK*)pnmh);
	return 0;
}

// Handles WMU_GETCOLOR message
LRESULT CNoteDlg::OnGetColor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return (long)GetNoteColor();
}

// Handles WMU_GETALPHA message
LRESULT CNoteDlg::OnGetAlpha(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (m_pfSetLayeredWindowAttributes)
		return (long)GetNoteAlpha();
	else
		return -1;
}

// Handles WM_ACTIVATE message
LRESULT CNoteDlg::OnActivateWindow(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (LOWORD(wParam) == WA_INACTIVE)	// the window gets deactivated
	{
		// Change title bar's color to an inactive window caption color
		m_wndStaticBar.SetColor(GetSysColor(COLOR_INACTIVECAPTION));

		// Change 'Close' button color to an inactive
		m_wndBtnClose.SetTextColor(GREY);

		// Note should be saved whenever it loses the focus.
		// The m_bClosing flag is used to avoid saving a note twice when we close it since
		// this function is also called.
		// The m_bDeleted flag is used to avoid saving a note again after it has
		// been deleted.
		if (!m_bClosing)
		{
			if (!m_bDeleted)
				OnSave(true);
		}
	}
	else								// the window gets activated
	{
		// Change title bar's color to an active window caption color
		m_wndStaticBar.SetColor(GetSysColor(COLOR_ACTIVECAPTION));
		m_wndEdit.SetFocus();

		// Change 'Close' button color to an active
		m_wndBtnClose.SetTextColor(BLACK);
	}
	
	m_wndStaticBar.Invalidate(FALSE);
	m_wndBtnClose.Invalidate(FALSE);
	return 0;
}

// Handles WM_SETFOCUS message
LRESULT CNoteDlg::OnFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	// Note's text gets selected, so fix it
	UnselectText();

	return 0;
}

// Handles clicking on 'Set title' menu item - sets note's title and saves it
void CNoteDlg::OnSetTitle()
{
	int nRet = -1;
	
	// Create and show the dialog to set a note's title
	CTitleDlg dlgTitle;
	
	nRet = dlgTitle.DoModal();
	
	// Handle the return value from DoModal
	switch (nRet)
	{
	case -1: 
	case IDABORT:
		ATLTRACE(_T("Title dialog box could not be created!\n"));
		break;
	case IDOK:
		// Set the note's title
		m_wndStaticBar.SetWindowText(dlgTitle.m_szTitle);
		break;
	case IDCANCEL:
	default:
		break;
	};	

	// Save it
	SetNoteTitle(dlgTitle.m_szTitle);
}

// Returns true if the application is being closed, false otherwise
bool CNoteDlg::IsAppClosing()
{
	return ::SendMessage(m_pWndParent->m_hWnd, WMU_ISAPPCLOSING, 0, 0) ? true : false;
}