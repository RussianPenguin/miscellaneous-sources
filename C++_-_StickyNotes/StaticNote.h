// StaticNote.h: interface for the CStaticNote class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STATICNOTE_H__7457B84E_63B8_41DB_9804_71830DCC1EFD__INCLUDED_)
#define AFX_STATICNOTE_H__7457B84E_63B8_41DB_9804_71830DCC1EFD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GradientStatic.h"

// Message to retrieve a note's color
#define WMU_GETCOLOR		WM_APP + 6

// Message to retrieve a note's opacity
#define WMU_GETALPHA		WM_APP + 7

class CStaticNote : public CWindowImpl<CStaticNote, CStatic>  
{
private:
	CMenu m_menuNotes;		// menu displayed when the user clicks on 'Note' icon

public:
	CStaticNote() 
	{
		ATLTRACE(_T("CStaticNote::CStaticNote()\n"));
	}

	~CStaticNote() 
	{
		ATLTRACE(_T("CStaticNote::~CStaticNote()\n"));

		// Destroy the menu
		if (m_menuNotes.m_hMenu != NULL)
			m_menuNotes.DestroyMenu();
	}

	BEGIN_MSG_MAP(CStaticNote)
		MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
		MESSAGE_HANDLER(WM_LBUTTONDBLCLK, OnLButtonDblClk)
	END_MSG_MAP()

	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		// Always display the menu relative to the left bottom corner
		CPoint pt(0, 16);

		// Convert client coordinates to screen coordinates 
		ClientToScreen(&pt);

		// Load the menu resource 
		if (!m_menuNotes.LoadMenu(IDR_MENU_NOTES))
		{
			ATLTRACE(_T("Menu resource was not loaded successfully!\n"));
			return 0;
		}

		// Retrieve a note's color
		DWORD lColor = (DWORD)::SendMessage(GetParent(), WMU_GETCOLOR, 0, 0);

		// Put a check mark next to a corresponding color menu item 
		switch (lColor)
		{
		case PINK:
			m_menuNotes.CheckMenuItem(IDR_MENU_PINK, MF_BYCOMMAND|MF_CHECKED);
			break;
		case GREEN:
			m_menuNotes.CheckMenuItem(IDR_MENU_GREEN, MF_BYCOMMAND|MF_CHECKED);
			break;
		case BLUE:
			m_menuNotes.CheckMenuItem(IDR_MENU_BLUE, MF_BYCOMMAND|MF_CHECKED);
			break;
		case YELLOW:
			m_menuNotes.CheckMenuItem(IDR_MENU_YELLOW, MF_BYCOMMAND|MF_CHECKED);
			break;
		case WHITE:
			m_menuNotes.CheckMenuItem(IDR_MENU_WHITE, MF_BYCOMMAND|MF_CHECKED);
			break;
		default:
			break;
		}

		// TrackPopupMenu cannot display the menu bar so get 
		// a handle to the first shortcut menu. 
 		CMenuHandle menuPopup = m_menuNotes.GetSubMenu(0);
		if (menuPopup.m_hMenu == NULL)
		{
			ATLTRACE(_T("Submenu was not retrieved successfully!\n"));
			return 0;
		}

		// Retrieve a note's opacity
		long lAlpha = ::SendMessage(GetParent(), WMU_GETALPHA, 0, 0);

		// Put a check mark next to a corresponding opacity menu item
		switch (lAlpha)
		{
		case -1:
			// Transparency is not supported, disable the menu
			menuPopup.EnableMenuItem(9, MF_BYPOSITION|MF_GRAYED);
			break;
		case 25:
			m_menuNotes.CheckMenuItem(IDR_MENU_90, MF_BYCOMMAND|MF_CHECKED);
			break;
		case 50:
			m_menuNotes.CheckMenuItem(IDR_MENU_80, MF_BYCOMMAND|MF_CHECKED);
			break;
		case 75:
			m_menuNotes.CheckMenuItem(IDR_MENU_70, MF_BYCOMMAND|MF_CHECKED);
			break;
		case 100:
			m_menuNotes.CheckMenuItem(IDR_MENU_60, MF_BYCOMMAND|MF_CHECKED);
			break;
		case 125:
			m_menuNotes.CheckMenuItem(IDR_MENU_50, MF_BYCOMMAND|MF_CHECKED);
			break;
		case 150:
			m_menuNotes.CheckMenuItem(IDR_MENU_40, MF_BYCOMMAND|MF_CHECKED);
			break;
		case 175:
			m_menuNotes.CheckMenuItem(IDR_MENU_30, MF_BYCOMMAND|MF_CHECKED);
			break;
		case 200:
			m_menuNotes.CheckMenuItem(IDR_MENU_20, MF_BYCOMMAND|MF_CHECKED);
			break;
		case 225:
			m_menuNotes.CheckMenuItem(IDR_MENU_10, MF_BYCOMMAND|MF_CHECKED);
			break;
		case 255:
			m_menuNotes.CheckMenuItem(IDR_MENU_0, MF_BYCOMMAND|MF_CHECKED);
			break;
		default:
			break;
		}

		// Display the shortcut menu, track the left mouse button,
		// and I want the Note dialog to receive all messages from the menu
 		if (!menuPopup.TrackPopupMenu(TPM_LEFTALIGN|TPM_TOPALIGN|TPM_LEFTBUTTON,
								pt.x, pt.y, GetParent()))
		{
			ATLTRACE(_T("Shortcut menu was not displayed successfully!\n"));
			return 0;
		}		

		// Destroy the menu and free any memory that the menu occupies
		menuPopup.DestroyMenu();
		m_menuNotes.DestroyMenu();

		return 0;
	}

	LRESULT OnLButtonDblClk(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		// Close the Note dialog
		// Can't use SendMessage(), because by the time SendMessage() returns
		// object's gone
		::PostMessage(GetParent(), WM_CLOSE, 0, 0);
		return 0;
	}
};

class CStaticDateTime : public CWindowImpl<CStaticDateTime, CStatic>  
{
private:
	COLORREF m_clrBkgnd;	// background color
	CBrush m_brBkgnd;		// brush for painting the background 

public:
	CStaticDateTime() 
	{
		ATLTRACE(_T("CStaticDateTime::CStaticDateTime()\n"));
	}

	~CStaticDateTime() 
	{
		ATLTRACE(_T("CStaticDateTime::~CStaticDateTime()\n"));

		if (m_brBkgnd.m_hBrush)
			m_brBkgnd.DeleteObject();
	}

	BEGIN_MSG_MAP(CStaticDateTime)
		// Uses message reflection: WM_* comes back as OCM_*
		MESSAGE_HANDLER(OCM_CTLCOLORSTATIC, OnCtlColor)
		// Take care of unhandled reflected messages
		DEFAULT_REFLECTION_HANDLER()
	END_MSG_MAP()

	// Sets the control's background color
	void SetBkgndColor(COLORREF clrColor)
	{
		m_clrBkgnd = clrColor;
		m_brBkgnd.CreateSolidBrush(m_clrBkgnd);
		ATLASSERT(m_brBkgnd.m_hBrush);
	}

	LRESULT OnCtlColor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		ATLASSERT(m_brBkgnd.m_hBrush);

		HDC hDC = (HDC)wParam;

		// Set the text current background color to the specified color value
        SetBkColor(hDC, m_clrBkgnd);

		return (LRESULT)m_brBkgnd.m_hBrush;
	}

	// Changes the control's background color
	void ChangeBkgndColor(COLORREF clrColor)
	{
		ATLASSERT(m_brBkgnd.m_hBrush);

		m_clrBkgnd = clrColor;
		m_brBkgnd.DeleteObject();
		m_brBkgnd.CreateSolidBrush(m_clrBkgnd);
		ATLASSERT(m_brBkgnd.m_hBrush);
	}

	// Displays the current date and time in the static control
	void SetCurrentDateTime(string strTimeStamp)
	{
		// Set the new text of the static control
		SetWindowText(strTimeStamp.c_str());
	}
};

#endif // !defined(AFX_STATICNOTE_H__7457B84E_63B8_41DB_9804_71830DCC1EFD__INCLUDED_)
