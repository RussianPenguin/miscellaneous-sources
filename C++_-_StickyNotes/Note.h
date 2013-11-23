// Note.h: interface for the CNote class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NOTE_H__8BFEB8A3_FA1F_11D5_9A92_00A0C9D5029B__INCLUDED_)
#define AFX_NOTE_H__8BFEB8A3_FA1F_11D5_9A92_00A0C9D5029B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "stdafx.h"
#include <time.h>

// CNote class represents the sticky note
class CNote  
{
private:
	
	// These data members will be used to set up the default attributes of the new note
	// and they will be persisted into the file to have the note saved.
	string m_strNoteRTF;	// note's text including the RTF formatting code
	string m_strNoteText;	// note's text not including the RTF formatting code
	string m_strTimestamp;	// when the note was created
	string m_strTitle;		// note's title
	COLORREF m_clrBkgnd;	// background color
	DWORD m_dwID;			// unique note's id, used to identify the note in the collection
	int m_nAlpha;			// note's opacity (transparency)
	bool m_bAlwaysOnTop;	// indicates if a note should be the top most window
	CRect m_rcNote;			// note's size
	int m_nStatus;			// flag indicating if a note is displayed or not (open or close)
							// this flag will be used to determine what notes have been
							// open when we closed the application

protected:

	string GenerateTimestamp();

	DWORD GenerateID();

public:

	enum Status { Close, Open };	

public:

	CNote(); 

	CNote(const CNote& rhs);

	~CNote(); 

	bool operator==(const CNote& rhs);

	CNote& operator=(const CNote& rhs);

	DWORD GetNoteColor() const { return m_clrBkgnd; }

	int GetNoteAlpha() const { return m_nAlpha; }

	DWORD GetNoteID() const { return m_dwID; }

	string GetTimestamp() const { return m_strTimestamp; }

	string GetNoteText() const { return m_strNoteText; }

	string GetNoteRTF() const { return m_strNoteRTF; }

	string GetNoteTitle() const { return m_strTitle; }

	bool GetAlwaysOnTop() const { return m_bAlwaysOnTop; }

	CRect& GetNoteRect() { return m_rcNote; }

	int GetNoteStatus() const { return m_nStatus; }

	void SetNoteID(DWORD dwID) { m_dwID = dwID; }

	void SetNoteAlpha(int nAlpha) { m_nAlpha = nAlpha; }

	void SetNoteColor(DWORD dwColor) { m_clrBkgnd = dwColor; }

	void SetTimestamp(string strTime) { m_strTimestamp = strTime; }

	void SetNoteText(string strText) { m_strNoteText = strText; }

	void SetNoteRTF(string strRTF) { m_strNoteRTF = strRTF; }

	void SetNoteTitle(string strTitle) { m_strTitle = strTitle; }

	void SetAlwaysOnTop(bool bAlwaysOnTop) { m_bAlwaysOnTop = bAlwaysOnTop; }

	void SetNoteRect(CRect rcNote) { m_rcNote = rcNote; }

	void SetNoteRect(string strPos);

	void SetNoteStatus(int nStatus) { ATLASSERT(nStatus != Status::Open || nStatus != Status::Close); m_nStatus = nStatus; }
};

#endif // !defined(AFX_NOTE_H__8BFEB8A3_FA1F_11D5_9A92_00A0C9D5029B__INCLUDED_)
