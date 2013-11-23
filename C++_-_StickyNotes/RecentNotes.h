// RecentNotes.h : interface of the CRecentNotes class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include "stdafx.h"
#include "Registry.h"

// Identifier of the first new menu item, used during the creation of the new menu items 
// and for message handler defined in the CHiddenWindow class.
#define NEW_MENU_ID_FIRST	10000

// Max number of the new menu items.
#define NUM_NEW_ITEMS		6

// CRecentNotes class keeps track of recently accessed notes and adds them 
// to the popup menu.
// Also keeps recently accessed notes id in the registry
class CRecentNotes
{
private:
	// Structure associated with menu item - contains info about menu item to be created,
	struct DYNITEMINFO{
		string strItem;			// menu item string - partial note's text
		UINT uID;				// menu item identifier
		DWORD dwItemData;		// unique note's id, it'll be associated with the menu item
	} m_dii;
	
	deque<DYNITEMINFO> m_colItemInfo;	// deque of DYNITEMINFO structures, it will 
										// contain recently accessed notes
	bool m_bUseRegistry;				// use of registry 
	CHiddenWindow * m_pWndParent;		// pointer to the parent hidden window

	CRegStdWORD m_regRecent1;
	CRegStdWORD m_regRecent2;
	CRegStdWORD m_regRecent3;
	CRegStdWORD m_regRecent4;
	CRegStdWORD m_regRecent5;
	CRegStdWORD m_regRecent6;

	void AddItem(DYNITEMINFO& dii);

	void RemoveItem(DWORD dwData);

	UINT GetNextItemID();

	string FixString(string strIn);

	void UpdateRegistry();

public:
	CRecentNotes();

	~CRecentNotes();

	void Initialize(CHiddenWindow * pWnd);

	void InsertMenuItems(CMenuHandle& menuTrackPopup);

	void AddItemToCollection(string strItemText, DWORD dwData);

	void RemoveItemFromCollection(DWORD dwData);

	bool GetItemData(/*in*/WORD wID, /*out*/DWORD * pdwData);
};
