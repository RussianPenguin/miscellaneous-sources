// SearchList.h: interface for the CSearchList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SEARCHLIST_H__B67350F3_101E_11D6_9A95_00A0C9D5029B__INCLUDED_)
#define AFX_SEARCHLIST_H__B67350F3_101E_11D6_9A95_00A0C9D5029B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CHiddenWindow;

class CSearchList : public CWindowImpl<CSearchList, CListViewCtrl>  
{
private:
	CHiddenWindow * m_pwndHidden;		// pointer to the hidden window
	CMenu m_menuSearch;					// context menu

public:
	CSearchList();
	~CSearchList();

	virtual BOOL PreTranslateMessage(MSG* pMsg)
	{
		return FALSE;
	}

	void SetPointerToHiddenWindow(CHiddenWindow * pwndHidden);

	BEGIN_MSG_MAP(CSearchList)
		MESSAGE_HANDLER(WM_LBUTTONDBLCLK, OnLButtonDblClk)
		MESSAGE_HANDLER(WM_KEYDOWN, OnKeyDown)
		MESSAGE_HANDLER(WM_CONTEXTMENU, OnContextMenu)
		MESSAGE_HANDLER(WM_COMMAND, OnCommand)
		// Take care of unhandled reflected messages
		DEFAULT_REFLECTION_HANDLER()
	END_MSG_MAP()

protected:
	LRESULT OnLButtonDblClk(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnContextMenu(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	int GetNoteId(int nIndex);

	void DisplayNote();

	void OnDeleteNote();
};

#endif // !defined(AFX_SEARCHLIST_H__B67350F3_101E_11D6_9A95_00A0C9D5029B__INCLUDED_)
