// Note.cpp: implementation of the CNote class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Note.h"
#include "CryptRandom.h"

CNote::CNote() 
{
	ATLTRACE(_T("CNote::CNote()\n"));
	
	// Set up default values
	m_strNoteText = EMPTY_STRING;
	m_strNoteRTF = EMPTY_STRING;
	m_strTitle = EMPTY_STRING;
	m_clrBkgnd = YELLOW;
	m_dwID = GenerateID();
	if (m_dwID == 0)
		ATLTRACE(_T("Note's id has not been generated!\n"));
	m_strTimestamp = GenerateTimestamp();
	m_nAlpha = 255;
	m_bAlwaysOnTop = false;
	m_rcNote.SetRectEmpty();
	m_nStatus = Status::Close;
}

CNote::CNote(const CNote& rhs)
{
	ATLTRACE(_T("CNote::CNote(const CNote& rhs)\n"));
	
	m_strNoteText = rhs.m_strNoteText;	
	m_strNoteRTF = rhs.m_strNoteRTF;	
	m_strTimestamp = rhs.m_strTimestamp;
	m_strTitle = rhs.m_strTitle;
	m_clrBkgnd = rhs.m_clrBkgnd;
	m_dwID = rhs.m_dwID;
	m_nAlpha = rhs.m_nAlpha;
	m_bAlwaysOnTop = rhs.m_bAlwaysOnTop;
	m_rcNote = rhs.m_rcNote;
	m_nStatus = rhs.m_nStatus;
}

CNote::~CNote() 
{
	ATLTRACE(_T("CNote::~CNote()\n"));
}

bool CNote::operator==(const CNote& rhs)
{
	ATLTRACE(_T("CNote::operator==()\n"));
	
	if ((m_strNoteText == rhs.m_strNoteText) &&
		(m_strNoteRTF == rhs.m_strNoteRTF) &&
		(m_strTimestamp == rhs.m_strTimestamp) &&
		(m_strTitle == rhs.m_strTitle) &&
		(m_clrBkgnd == rhs.m_clrBkgnd) &&
		(m_dwID == rhs.m_dwID) &&
		(m_nAlpha == rhs.m_nAlpha) &&
		(m_bAlwaysOnTop == rhs.m_bAlwaysOnTop) &&
		m_rcNote == rhs.m_rcNote &&
		m_nStatus == rhs.m_nStatus)
		return true;
	else
		return false;
}

CNote& CNote::operator=(const CNote& rhs)
{
	ATLTRACE(_T("CNote::operator=()\n"));
	
	if (this == &rhs)
		return *this;
	
	m_strNoteText = rhs.m_strNoteText;	
	m_strNoteRTF = rhs.m_strNoteRTF;	
	m_strTimestamp = rhs.m_strTimestamp;
	m_strTitle = rhs.m_strTitle;
	m_clrBkgnd = rhs.m_clrBkgnd;
	m_dwID = rhs.m_dwID;
	m_nAlpha = rhs.m_nAlpha;
	m_bAlwaysOnTop = rhs.m_bAlwaysOnTop;
	m_rcNote = rhs.m_rcNote;
	m_nStatus = rhs.m_nStatus;
	
	return *this;
}

// Generates a timestamp
string CNote::GenerateTimestamp()
{
	SYSTEMTIME csSysTime;
	TCHAR szDate[32];
	TCHAR szTime[32];
	TCHAR szTemp[4];
	lstrcpy(szTemp, _T("AM"));
	TCHAR szDateFormat[4];
	TCHAR szTimeFormat[4];

	// Get the local date and time
	::GetLocalTime(&csSysTime);
	
	// Retrieve information about a locale

	// Short date format
	int nLen = ::GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_IDATE, szDateFormat, 4);
	if (nLen == 0)	// error
		lstrcpy(szDateFormat, _T("0"));

	// Format date and store it in a buffer
	switch (_ttoi(szDateFormat))
	{
	case 0:		// Month-Day-Year
		::wsprintf(szDate, _T("%02d/%02d/%04d "), csSysTime.wMonth, csSysTime.wDay, csSysTime.wYear);
		break;
	case 1:		// Day-Month-Year
		::wsprintf(szDate, _T("%02d/%02d/%04d "), csSysTime.wDay, csSysTime.wMonth, csSysTime.wYear);
		break;
	case 2:		// Year-Month-Day
		::wsprintf(szDate, _T("%04d/%02d/%02d "), csSysTime.wYear, csSysTime.wMonth, csSysTime.wDay);
		break;
	default:	
		break;
	}

	// Time format
	nLen = ::GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_ITIME, szTimeFormat, 4);
	if (nLen == 0)	// error
		lstrcpy(szTimeFormat, _T("0"));

	// Format time and store it in a buffer
	switch (_ttoi(szTimeFormat))
	{
	case 0:		// AM/PM 12-hour format
		// AM or PM?
		if (csSysTime.wHour > 12)
		{
			csSysTime.wHour = csSysTime.wHour - 12;
			lstrcpy(szTemp, _T("PM"));
		}

		::wsprintf(szTime, _T("%02d:%02d %s"), csSysTime.wHour, csSysTime.wMinute, szTemp);
		break;
	case 1:		// 24-hour format
		::wsprintf(szTime, _T("%02d:%02d"), csSysTime.wHour, csSysTime.wMinute);
		break;
	default:	
		break;
	}

	return (string(szDate) + string(szTime));
}

// Generates a unique note's id
DWORD CNote::GenerateID()
{
    CCryptRandom cr;

    DWORD d;
    if (cr.GenRand(&d, sizeof(DWORD)))
        return d;
	else 
		return 0;
}

// It takes a string looking like this "200,300,400,500" (where
// the numbers represent CRect data members in the following order - left, 
// top, right, bottom), parses it and populates a CRect object 
void CNote::SetNoteRect(string strRectValues)
{
	ATLASSERT(!strRectValues.empty());		// should not be empty

	TCHAR seps[]   = ",";
	TCHAR * token;
	CSimpleArray<TCHAR*> arPos;

	// Parse the string
	token = _tcstok(const_cast<TCHAR*>(strRectValues.c_str()), seps);
	while(token != NULL)
	{
		// While there are tokens in the string
		arPos.Add(token);

		// Get next token
		token = _tcstok(NULL, seps);
	}

	// Populate the CRect object that represents note's size
	m_rcNote.left = _ttol(arPos[0]);
	m_rcNote.top = _ttol(arPos[1]);
	m_rcNote.right = _ttol(arPos[2]);
	m_rcNote.bottom = _ttol(arPos[3]);
}
