// RecentNotes.cpp : implementation of the CRecentNotes class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "HiddenWnd.h"
#include "RecentNotes.h"

CRecentNotes::CRecentNotes()
{
	ATLTRACE(_T("CRecentNotes::CRecentNotes()\n"));

	memset(&m_dii, 0, sizeof(DYNITEMINFO));

	// Change it to false if you don't want to use the registry
	m_bUseRegistry = true;	

	if (m_bUseRegistry)
	{
		// Increase the deque size to NUM_NEW_ITEMS and set the new elements
		// to be DYNITEMINFO
		m_colItemInfo.resize(NUM_NEW_ITEMS, m_dii);

		// Set up default values in the registry
		m_regRecent1 = CRegStdWORD(_T("Software\\Local AppWizard-Generated Applications\\StickyNotes\\Recent\\F1"), 0, TRUE);
		m_regRecent2 = CRegStdWORD(_T("Software\\Local AppWizard-Generated Applications\\StickyNotes\\Recent\\F2"), 0, TRUE);
		m_regRecent3 = CRegStdWORD(_T("Software\\Local AppWizard-Generated Applications\\StickyNotes\\Recent\\F3"), 0, TRUE);
		m_regRecent4 = CRegStdWORD(_T("Software\\Local AppWizard-Generated Applications\\StickyNotes\\Recent\\F4"), 0, TRUE);
		m_regRecent5 = CRegStdWORD(_T("Software\\Local AppWizard-Generated Applications\\StickyNotes\\Recent\\F5"), 0, TRUE);
		m_regRecent6 = CRegStdWORD(_T("Software\\Local AppWizard-Generated Applications\\StickyNotes\\Recent\\F6"), 0, TRUE);
	}
}

CRecentNotes::~CRecentNotes()
{
	ATLTRACE(_T("CRecentNotes::~CRecentNotes()\n"));

	UpdateRegistry();
}

// Initializes collection of the recently accessed notes
void CRecentNotes::Initialize(CHiddenWindow * pWnd)
{
	int i = 0;
	m_pWndParent = pWnd;

	if (m_bUseRegistry)
	{
		// Initialize the collection of the recently accessed notes from the registry
		if (m_regRecent1 != 0)
		{
			m_colItemInfo[i].dwItemData = m_regRecent1;
			m_colItemInfo[i++].strItem = FixString(m_pWndParent->FindNoteTextByID(m_regRecent1));
		}
		if (m_regRecent2 != 0)
		{
			m_colItemInfo[i].dwItemData = m_regRecent2;
			m_colItemInfo[i++].strItem = FixString(m_pWndParent->FindNoteTextByID(m_regRecent2));
		}
		if (m_regRecent3 != 0)
		{
			m_colItemInfo[i].dwItemData = m_regRecent3;
			m_colItemInfo[i++].strItem = FixString(m_pWndParent->FindNoteTextByID(m_regRecent3));
		}
		if (m_regRecent4 != 0)
		{
			m_colItemInfo[i].dwItemData = m_regRecent4;
			m_colItemInfo[i++].strItem = FixString(m_pWndParent->FindNoteTextByID(m_regRecent4));
		}
		if (m_regRecent5 != 0)
		{
			m_colItemInfo[i].dwItemData = m_regRecent5;
			m_colItemInfo[i++].strItem = FixString(m_pWndParent->FindNoteTextByID(m_regRecent5));
		}
		if (m_regRecent6 != 0)
		{
			m_colItemInfo[i].dwItemData = m_regRecent6;
			m_colItemInfo[i++].strItem = FixString(m_pWndParent->FindNoteTextByID(m_regRecent6));
		}
	}
}

// Saves the ids of the recently accessed notes in the registry
void CRecentNotes::UpdateRegistry()
{
	if (m_bUseRegistry)
	{
		m_regRecent1 = m_colItemInfo[0].dwItemData;
		m_regRecent2 = m_colItemInfo[1].dwItemData;
		m_regRecent3 = m_colItemInfo[2].dwItemData;
		m_regRecent4 = m_colItemInfo[3].dwItemData;
		m_regRecent5 = m_colItemInfo[4].dwItemData;
		m_regRecent6 = m_colItemInfo[5].dwItemData;
	}
}

// Adds a DYNITEMINFO structure to the beginning of the collection
void CRecentNotes::AddItem(DYNITEMINFO& dii)
{
	// If an item is already in the collection remove it, since the first item
	// in the collection should be the most recently used
	RemoveItem(dii.dwItemData);

	// Delete the element at the end of the deque if number of elements is equal to
	// NUM_NEW_ITEMS (number of elements can not be greater than NUM_NEW_ITEMS)
	if (m_colItemInfo.size() == NUM_NEW_ITEMS)
		m_colItemInfo.pop_back();

	// Add the new element to the beginning of the deque
	m_colItemInfo.push_front(dii);

	UpdateRegistry();
}

// Removes a DYNITEMINFO structure from the collection
void CRecentNotes::RemoveItem(DWORD dwData)
{
	deque<DYNITEMINFO>::iterator iter;

	// Loop thru the collection of DYNITEMINFO structures
	for (iter = m_colItemInfo.begin(); iter != m_colItemInfo.end(); iter++)
	{
		// If the note's id is found set this element to an empty structure
		if ((*iter).dwItemData == dwData)
		{
			DYNITEMINFO dii;
			memset(&dii, 0, sizeof(DYNITEMINFO));
			*iter = dii;
			break;
		}
	}

	UpdateRegistry();
}

// Returns the next available identifier. If the last used value is equal 
// to the max allowed value reset it to the first allowed value.
// Result is that NUM_NEW_ITEMS identifiers will be reused over and over.
UINT CRecentNotes::GetNextItemID()
{
	// Last used menu item identifier
	static UINT uLastUsedID = NEW_MENU_ID_FIRST - 1;

	if (uLastUsedID < (NEW_MENU_ID_FIRST + NUM_NEW_ITEMS - 1))
		uLastUsedID++;
	else
		uLastUsedID = NEW_MENU_ID_FIRST;

	return uLastUsedID;
}

// Inserts new menu items at the specified position in a menu
void CRecentNotes::InsertMenuItems(CMenuHandle& menuTrackPopup)
{
	ATLASSERT(::IsMenu(menuTrackPopup.m_hMenu));

	if (m_colItemInfo.size() == 0)
		return;

	UINT nInsertPoint = 0;	// position of the menu item before which to insert the new item
	bool bEmptyDeleted = false;

	// Initialize MENUITEMINFO structure
	MENUITEMINFO mii;
	mii.cbSize = sizeof(MENUITEMINFO);
	mii.fMask = MIIM_DATA | MIIM_TYPE | MIIM_ID;
	mii.fType = MFT_STRING;

	deque<DYNITEMINFO>::iterator iter;

	// Loop thru the collection of DYNITEMINFO structures
	for (iter = m_colItemInfo.begin(); iter != m_colItemInfo.end(); iter++)
	{
		if ((*iter).dwItemData != 0)
		{
			// Delete "Empty" menu item - do not need it any more
			if (!bEmptyDeleted)
			{
				menuTrackPopup.DeleteMenu(ID_POPUP_EMPTY, MF_BYCOMMAND);
				bEmptyDeleted = true;
			}

			// Initialize the menu item identifier of DYNITEMINFO structure
			(*iter).uID = GetNextItemID();

			// Initialize the rest of MENUITEMINFO structure with the information
			// containing in DYNITEMINFO
			mii.wID = (*iter).uID;
			mii.dwItemData = (*iter).dwItemData;
			mii.dwTypeData = (char*)(*iter).strItem.c_str();

			// Insert a new menu item
			if (!menuTrackPopup.InsertMenuItem(nInsertPoint, MF_BYPOSITION | MF_POPUP, &mii))
				ATLTRACE(_T("Menu item was not inserted!\n"));

			nInsertPoint++;
		}
	}
}

// Creates a DYNITEMINFO structure and adds it to the collection
// of recently accessed notes
void CRecentNotes::AddItemToCollection(string strItemText, DWORD dwData)
{
	DYNITEMINFO dii;
	memset(&dii, 0, sizeof(DYNITEMINFO));

	// Populate some of the DYNITEMINFO structure
	dii.strItem = FixString(strItemText);	// menu item text
	dii.dwItemData = dwData;				// note's id

	// Add it to the collection
	AddItem(dii);
}

// Removes a DYNITEMINFO structure from the collection
// of recently accessed notes
void CRecentNotes::RemoveItemFromCollection(DWORD dwData)
{
	RemoveItem(dwData);
}

// Retrieves a value associated with the menu item
// wID - the identifier of the menu item
// pdwData - the value associated with the menu item (note's id)
bool CRecentNotes::GetItemData(/*in*/WORD wID, /*out*/DWORD * pdwData)
{
	deque<DYNITEMINFO>::iterator iter;
	*pdwData = 0;

	// Loop thru the collection of DYNITEMINFO structures
	for (iter = m_colItemInfo.begin(); iter != m_colItemInfo.end(); iter++)
	{
		// If the identifier of the menu item is found
		if ((*iter).uID == wID)
		{
			*pdwData =  (*iter).dwItemData;
			return true;
		}
	}

	return false;
}

// Replaces invalid characters in the string and returns a substring
// having a specified length
string CRecentNotes::FixString(string strIn)
{
	ATLASSERT(strIn.length() != 0);

	// Replace invalid characters
	replace(strIn.begin(), strIn.end(), '\r', ' ');
	replace(strIn.begin(), strIn.end(), '\n', ' ');

	return strIn.substr(0, MAX_STRING_LEN);
}