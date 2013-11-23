// SearchButton.h: interface for the buttons and edit classes used by the search dialog.
//
//////////////////////////////////////////////////////////////////////

#ifndef __ATLBTN_H__
#define __ATLBTN_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CEditEx : public CWindowImpl<CEditEx, CEdit>
{
public:
	CEditEx() 
	{
		ATLTRACE(_T("CEditEx::CEditEx()\n"));
	}

	~CEditEx() 
	{
		ATLTRACE(_T("CEditEx::~CEditEx()\n"));
	}

	BEGIN_MSG_MAP(CEditEx)
		MESSAGE_HANDLER(WM_KEYDOWN, OnKeyDown)
		DEFAULT_REFLECTION_HANDLER()
	END_MSG_MAP()

	BOOL PreTranslateMessage(MSG* pMsg)
	{
		return FALSE;
	}

	LRESULT OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		// If an 'Enter' key was pressed
		if (wParam == VK_RETURN)		
		{
			// Do a search
			::SendMessage(GetParent(), WMU_FINDNOTE, 0, 0);	
			return 0;
		}

		// If any other key do not handle the message
		bHandled = FALSE;
		return 0;
	}
};

class CButtonExCancel : public CWindowImpl<CButtonExCancel, CButton>
{
public:
	CButtonExCancel() 
	{
		ATLTRACE(_T("CButtonExCancel::CButtonExCancel()\n"));
	}

	~CButtonExCancel() 
	{
		ATLTRACE(_T("CButtonExCancel::~CButtonExCancel()\n"));
	}

	BEGIN_MSG_MAP(CButtonExCancel)
		MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
		MESSAGE_HANDLER(WM_KEYDOWN, OnKeyDown)
		DEFAULT_REFLECTION_HANDLER()
	END_MSG_MAP()

	BOOL PreTranslateMessage(MSG* pMsg)
	{
		return FALSE;
	}

	// Handles clicking on 'Cancel' button
	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		// Close the search dialog
		// Can't use SendMessage(), because by the time SendMessage() returns
		// object's gone
		::PostMessage(GetParent(), WM_CLOSE, 0, 0);
		return 0;
	}

	// Handles pressing the 'Enter' key when 'Cancel' button has a focus
	LRESULT OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		// Close the search dialog
		// Can't use SendMessage(), because by the time SendMessage() returns
		// object's gone
		::PostMessage(GetParent(), WM_CLOSE, 0, 0);
		return 0;
	}
};

class CButtonExFind : public CWindowImpl<CButtonExFind, CButton>
{
public:
	CButtonExFind() 
	{
		ATLTRACE(_T("CButtonExFind::CButtonExFind()\n"));
	}

	~CButtonExFind() 
	{
		ATLTRACE(_T("CButtonExFind::~CButtonExFind()\n"));
	}

	BEGIN_MSG_MAP(CButtonExFind)
		MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
		MESSAGE_HANDLER(WM_KEYDOWN, OnKeyDown)
		DEFAULT_REFLECTION_HANDLER()
	END_MSG_MAP()

	BOOL PreTranslateMessage(MSG* pMsg)
	{
		return FALSE;
	}

	// Handles clicking on 'Find' button
	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		// Do a search
		::SendMessage(GetParent(), WMU_FINDNOTE, 0, 0);
		return 0;
	}

	// Handles pressing the 'Enter' key when 'Find' button has a focus
	LRESULT OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		// Do a search
		::SendMessage(GetParent(), WMU_FINDNOTE, 0, 0);
		return 0;
	}
};

class CButtonExNew : public CWindowImpl<CButtonExNew, CButton>
{
public:
	BEGIN_MSG_MAP(CButtonExNew)
		MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
		MESSAGE_HANDLER(WM_KEYDOWN, OnKeyDown)
		DEFAULT_REFLECTION_HANDLER()
	END_MSG_MAP()

	BOOL PreTranslateMessage(MSG* pMsg)
	{
		return FALSE;
	}

	// Handles clicking on 'New note' button
	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		// Send a message to create a new Note dialog
		::SendMessage(GetParent(), WMU_NEWNOTE, 0, 0);
		return 0;
	}

	// Handles pressing the 'Enter' key when 'New Note' button has a focus
	LRESULT OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		// Send a message to create a new Note dialog
		::SendMessage(GetParent(), WMU_NEWNOTE, 0, 0);
		return 0;
	}
};

/************************************************************************/
#endif // __ATLBTN_H__
