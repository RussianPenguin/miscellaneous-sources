// FindNote.h
//
//////////////////////////////////////////////////////////////////////

// This file contains function objects, which are used to search
// the saved notes.
// Function object is a class that overloads the operator().
// It can be used instead of function pointers in the STL algorithms.

#if !defined FINDNOTE_H
#define FINDNOTE_H

// CFindNotesByString is used to search notes by string
class CFindNotesByString
{
private:
	string m_strSearchFor;		// string to search for
	vector<CNote>* m_pvecRes;	// pointer to the vector which'll contain search matches, if any

	// Converts string to uppercase
	string& ToUpper(string& str)
	{
		string::iterator iter;
		for (iter = str.begin(); iter != str.end(); iter++)
			*iter = toupper(*iter);

		return str;
	}

public:
	// Constructor accepts string to search for and a pointer to the vector
	// which'll contain search matches as parameters
    CFindNotesByString(string str, vector<CNote>* pvec)
	{
		ATLTRACE(_T("CFindNotesByString::CFindNotesByString()\n"));

		m_strSearchFor = str;
		m_pvecRes = pvec;
	}

	// Overloads operator()
    void operator()(const CNote& note)
	{
		ATLTRACE(_T("CFindNotesByString::operator()()\n"));

		string strToSearch = note.GetNoteText();

		// Convert both strings to uppercase
		strToSearch = ToUpper(strToSearch);
		m_strSearchFor = ToUpper(m_strSearchFor);

		// Note: case sensitive algorithm.
		// I'm only searching note's text
		if (strToSearch.find(m_strSearchFor) != -1)
		{
			// If the match is found place
			// the class in the result container
			(*m_pvecRes).push_back(note);
		}
    }
};

// CFindNoteById is used to search notes by id
class CFindNoteById
{
private:
	DWORD m_dwSearchFor;			// id to search for
	vector<CNote>* m_pvecRes;	// pointer to the vector which'll contain search match, if any

public:
	// Constructor accepts id to search for and a pointer to the vector
	// which'll contain search matches as parameters
    CFindNoteById(DWORD dwID, vector<CNote>* pvec)
	{
		ATLTRACE(_T("CFindNoteById::CFindNoteById()\n"));

		m_dwSearchFor = dwID;
		m_pvecRes = pvec;
	}

	// Overloads operator()
    void operator()(const CNote& note)
	{
		ATLTRACE(_T("CFindNoteById::operator()()\n"));

		// I'm only searching note's text
		if (m_dwSearchFor == note.GetNoteID())
		{
			// If the match is found place
			// the class in the result container
			(*m_pvecRes).push_back(note);
		}
    }
};

#endif // !defined FINDNOTE_H
