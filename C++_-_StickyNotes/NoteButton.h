// NoteButton.h: interface for the button classes used by the note.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NOTEBUTTON_H__F69829D5_73B6_4F46_86D4_02ED8D41CEEA__INCLUDED_)
#define AFX_NOTEBUTTON_H__F69829D5_73B6_4F46_86D4_02ED8D41CEEA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BitmapButton.h"

// Message to make a note the top most window
#define WMU_SETTOPMOST		WM_APP + 8

class CButtonExPin : public CButtonEx
{
public:
	CButtonExPin() 
	{
		ATLTRACE(_T("CButtonExPin::CButtonExPin()\n"));
	}

	~CButtonExPin() 
	{
		ATLTRACE(_T("CButtonExPin::~CButtonExPin()\n"));
	}

	BEGIN_MSG_MAP(CButtonExPin)
		MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
		CHAIN_MSG_MAP(CButtonEx/*CBmpButtonEx*/)
		DEFAULT_REFLECTION_HANDLER()
	END_MSG_MAP()

	// Handles clicking on 'Pin' button
	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		// Make a note the top most window
		::SendMessage(GetParent(), WMU_SETTOPMOST, 0, 0);

		return CButtonEx::OnLButtonDown(uMsg, wParam, lParam, bHandled);
	}
};

class CButtonExClose : public CButtonEx
{
public:
	CButtonExClose() 
	{
		ATLTRACE(_T("CButtonExClose::CButtonExClose()\n"));
	}

	~CButtonExClose() 
	{
		ATLTRACE(_T("CButtonExClose::~CButtonExClose()\n"));
	}

	BEGIN_MSG_MAP(CButtonExClose)
		MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
		CHAIN_MSG_MAP(CButtonEx/*CBmpButtonEx*/)
		DEFAULT_REFLECTION_HANDLER()
	END_MSG_MAP()

	// Handles clicking on 'Close' button
	LRESULT OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		// Close the Note dialog
		// Can't use SendMessage(), because by the time SendMessage() returns
		// object's gone
		::PostMessage(GetParent(), WM_CLOSE, 0, 0);

		return CButtonEx::OnLButtonUp(uMsg, wParam, lParam, bHandled);
	}
};

#endif // !defined(AFX_NOTEBUTTON_H__F69829D5_73B6_4F46_86D4_02ED8D41CEEA__INCLUDED_)
