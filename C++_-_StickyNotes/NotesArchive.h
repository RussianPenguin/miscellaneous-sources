// NotesArchive.h: interface for the CNotesArchive class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NOTESARCHIVE_H__24F3DA54_F78F_4A0F_AECD_EF15C2C0AE5B__INCLUDED_)
#define AFX_SAVEDNOTES_H__24F3DA54_F78F_4A0F_AECD_EF15C2C0AE5B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "stdafx.h"

extern ostream& operator<<(ostream& os, CNote n);

class CNotesArchive
{
private:
	fstream m_File;			// file where all notes are saved
	string m_strFileName;	// file name
	ios::openmode m_Mode;	// open_mode flag
	bool m_bIsOpen;			// flag indicating if the file is open or not

public:
	CNotesArchive(const string& strFileName, ios::openmode Mode = ios::in | ios::out)
	{
		ATLTRACE(_T("CNotesArchive::CNotesArchive()\n"));
		ATLASSERT(!strFileName.empty());	// string should not be empty

		m_strFileName = strFileName;
		m_Mode = Mode;

		// Open the file
		m_File.open(m_strFileName.c_str(), m_Mode);
		// Set the flag 
		if (m_File.is_open())	// success
			m_bIsOpen = true;
		else					// failure
			m_bIsOpen = false;
	}

	~CNotesArchive()
	{
		ATLTRACE(_T("CNotesArchive::~CNotesArchive()\n"));

		// Close the file and free the operating system file handle
		if (m_bIsOpen)
			m_File.close();
	}

	bool IsOpen()
	{
		return m_bIsOpen;
	}

	/*
	Notes are saved as a key:value pair in the following format:
	[NOTE]
	[NOTETEXT]:my phone# 212-575-1212
	[NOTERTF]:{\rtf1\ansi\ansicpg1252\deff0\deflang1033{\fonttbl{\f0\fnil\fprq12\fcharset0 Arial;}}
	{\colortbl ;\red0\green0\blue0;}
	\viewkind4\uc1\pard\cf1\b\f0\fs20 my phone# 212-575-1212\par}
	[TITLE]:my phone
	[TIMESTAMP]:01/17/2002 11:19 AM
	[BKGNDCOLOR]:13434879
	[NOTEID]:4648
	[ALPHA]:255
	[POSITION]:200,300,400,500
	[STATUS]:1
	[ENDNOTE]
	*/
	void SaveNotesToFile(vector<CNote>& vec)
	{
		ATLASSERT(m_bIsOpen);

		// Iterator for template class vector of classes CNote
		vector<CNote>::iterator start, end, iter;

		// Location of the first note in the vector
		start = vec.begin(); 
		// One past the location of the last note in the vector
		end = vec.end(); 
		
		// Write all notes to the file
		for (iter = start; iter != end; iter++)
		{
			m_File << *iter;
		}
	}

	void LoadNotesFromFile(vector<CNote> * pvec)
	{
		ATLASSERT(m_bIsOpen);

		string strLine;		// string which'll hold characters read from the file
		CNote noteTemp;		// note to be created and put in the vector

		// As we know notes are saved as a key:value pair
		string strKey;		// string which'll hold the key
		string strValue;	// string which'll hold the value
		int nPos;			// starting position
		char * pszStop;		// pointer to character that stops scan

		bool bRTF;

		while (!m_File.eof())
		{
			// Read the file until the newline is found and store the
			// extracted characters in the strLine
			getline(m_File, strLine);
			
			if (strLine.length() == 0)
			{
				// Line is empty - do not do anything
				continue;
			}
			else if (strLine == "[ENDNOTE]")
			{
				// End of note - insert the note in the vector
				pvec->push_back(noteTemp);
			}
			else if (strLine == "[NOTE]")
			{
				// New note begins - do not do anything
				continue;
			}
			else if (strLine[0] != '[')
			{
				if (bRTF)
					// RTF formatting of the note continues
					noteTemp.SetNoteRTF(noteTemp.GetNoteRTF() + strLine);
				else
					// Text of the note continues
					noteTemp.SetNoteText(noteTemp.GetNoteText() + strLine);
			} 
			else
			{
				// This is a note attribute - parse it
				nPos = strLine.find(':');
				strKey = strLine.substr(0, nPos);
				strValue = strLine.substr(nPos + 1, strLine.length() - nPos);
				// Set up the note fields
				if (strKey == "[NOTETEXT]")
				{
					noteTemp.SetNoteText(strValue);
					bRTF = false;
				}
				if (strKey == "[NOTERTF]")
				{
					noteTemp.SetNoteRTF(strValue);
					bRTF = true;
				}
				else if (strKey == "[TITLE]")
					noteTemp.SetNoteTitle(strValue);
				else if (strKey == "[TIMESTAMP]")
					noteTemp.SetTimestamp(strValue);
				else if (strKey == "[BKGNDCOLOR]")
					noteTemp.SetNoteColor(_ttol(strValue.c_str()));
				else if (strKey == "[NOTEID]")
					noteTemp.SetNoteID(_tcstoul(strValue.c_str(), &pszStop, 10));
				else if (strKey == "[ALPHA]")
					noteTemp.SetNoteAlpha(_ttoi(strValue.c_str()));
				else if (strKey == "[POSITION]")
					noteTemp.SetNoteRect(strValue);
				else if (strKey == "[STATUS]")
					noteTemp.SetNoteStatus(_ttoi(strValue.c_str()));
			}
		}
	}
};

#endif // !defined(AFX_NOTESARCHIVE_H__24F3DA54_F78F_4A0F_AECD_EF15C2C0AE5B__INCLUDED_)
