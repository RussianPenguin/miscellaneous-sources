// SearchList.cpp: implementation of the CSearchList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "SearchList.h"
#include "HiddenWnd.h"

CSearchList::CSearchList()
{
	ATLTRACE(_T("CSearchList::CSearchList()\n"));
}

CSearchList::~CSearchList()
{
	ATLTRACE(_T("CSearchList::~CSearchList()\n"));
}

// This function is used to receive a pointer to the hidden window
void CSearchList::SetPointerToHiddenWindow(CHiddenWindow * pwndHidden)
{
	ATLASSERT(pwndHidden);

	m_pwndHidden = pwndHidden;
}

LRESULT CSearchList::OnLButtonDblClk(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = TRUE;
	DisplayNote();

	return 0;
}

LRESULT CSearchList::OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = FALSE;

	switch (wParam) 
	{
	case VK_RETURN:		// 'Enter' key pressed 
		DisplayNote();
		bHandled = TRUE;
		break;
	default: 
		break;
	}

	return 0;
}

// Tells the hidden window to display a note
void CSearchList::DisplayNote()
{
	// Retrieve the index of the currently selected item
	int nIndex = GetSelectedIndex();

	if (nIndex != LB_ERR)
	{
		// Retrieve the 32-bit value associated with the item, in our case it's the note's id
		int nNoteID = GetNoteId(nIndex);
		if (nNoteID != 0)
		{
			// Post a message to the hidden window to display a note
			::PostMessage(m_pwndHidden->m_hWnd, WMU_DISPLAYNOTE, (WPARAM)nNoteID, 0);
		}
	}
	else
		ATLTRACE(_T("No item is currently selected in the list control\n"));
}

// Creates a context menu
LRESULT CSearchList::OnContextMenu(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	// Retrieve the index of the currently selected item
	int nIndex = GetSelectedIndex();

	// Display the context menu
	if (nIndex != LB_ERR)
	{
		if (::IsMenu(m_menuSearch.m_hMenu))
		{
			ATLTRACE(_T("Menu is already displayed!\n"));
			return 0;
		}

		// Cursor's horizontal and vertical position
		CPoint pt(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));

		// Load the menu resource 
		if (!m_menuSearch.LoadMenu(IDR_DELETE_NOTE))
		{
			ATLTRACE(_T("Menu resource was not loaded successfully!\n"));
			return 0;
		}

		// TrackPopupMenu cannot display the menu bar so get 
		// a handle to the first shortcut menu. 
 		CMenuHandle menuPopup = m_menuSearch.GetSubMenu(0);
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
		m_menuSearch.DestroyMenu();
		m_menuSearch.m_hMenu = NULL;
	}

	return 0;
}

// Handles a menu item selection
LRESULT CSearchList::OnCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	switch (LOWORD(wParam))
	{
	case ID_POPUP_DELETE:
		OnDeleteNote();
		break;
	default:
		break;
	}

	return 0;
}

void CSearchList::OnDeleteNote()
{
	int nNoteID = 0;
	BOOL bRes = FALSE;

	// Retrieve the index of the currently selected item
	int nIndex = GetSelectedIndex();

	if (nIndex != LB_ERR)
	{
		// Retrieve the 32-bit value associated with the item, in our case it's the note's id
		nNoteID = GetNoteId(nIndex);
		if (nNoteID != 0)
		{
			// Delete a note from the collection
			if (::SendMessage(m_pwndHidden->m_hWnd, WMU_DELETENOTE, (WPARAM)nNoteID, 0))
			{
				// Delete the item from the list control
				bRes = DeleteItem(nIndex);
				if (bRes == FALSE)
					ATLTRACE(_T("Item has not been deleted from the list control!\n"));
			}
			else
				ATLTRACE(_T("Note has not been deleted!\n"));
		}
	}
	else
		ATLTRACE(_T("No item is currently selected in the list control\n"));
}

// Retrieves the application-supplied value associated with the specified list control item.
int CSearchList::GetNoteId(int nIndex)
{
	DWORD dwID = GetItemData(nIndex);
	if (dwID != LB_ERR && dwID != 0)
	{
		return (int)dwID;
	}
	else
	{
		ATLTRACE(_T("Getting the 32-bit value of the list control item failed\n"));
		return 0;
	}
}