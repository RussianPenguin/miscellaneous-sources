// XTMemFile.h interface for the CXTMemFile class.
//
// This file is a part of the Xtreme MFC Toolkit.
// ©2000 Codejock.com Software, All Rights Reserved.
//
// CODEJOCK.COM SOFTWARE GRANTS TO YOU (ONE SOFTWARE PROGRAMMER) THE
// LIMITED RIGHT TO USE THIS SOFTWARE ON A SINGLE COMPUTER FOR EVALUATION
// PURPOSES ONLY. THESE SOURCE FILE ARE CONSIDERED CONFIDENTIONAL AND ARE 
// THE PROPERTY OF CODEJOCK.COM SOFTWARE AND ARE NOT TO BE RE-DISTRIBUTED
// BY ANY MEANS WHATSOEVER WITHOUT THE EXPRESSED WRITTEN CONSENT OF 
// CODEJOCK.COM SOFTWARE.
//
// support@codejock.com
// http://www.codejock.com

//
// Used with permission Copyright © 1999 Maxallion
// mailto:XFile@maxallion.8m.com
// ICQ# 32304418
//
// CCJMemFile - Extended Memory File - Beta - w/o a lot of error checking
// - Is used like a normal CFile or CStdioFile or CMemFile object
// - String Functions : ReadString, WriteString
// - Loads physical files into memory on creation and saves them back to disk on destruction
// - Can duplicate itself to other CFile derived objects
// - Has a Search function
// - can be read-accessed like an array
//
// OVERLOADED OPERATORS:
// = Imports from another file or sets file Position
// += Appends another file
// [] reads a byte like an array
//
//////////////////////////////////////////////////////////////////////

#if !defined(__XTMEMFILE_H__)
#define __XTMEMFILE_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CXTMemFile
/////////////////////////////////////////////////////////////////////////////
class _XT_EXT_CLASS CXTMemFile : public CMemFile  
{

public:

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Constructor - handles default initialization.
	CXTMemFile( UINT nGrowBytes = 1024 );
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Constructor - handles default initialization.
	CXTMemFile( BYTE* lpBuffer, UINT nBufferSize, UINT nGrowBytes = 0 );

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Constructor - handles default initialization.
	CXTMemFile(LPCTSTR lpstFilename, UINT uiOpenFlags);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Destructor - handles cleanup and de-allocation.
	virtual ~CXTMemFile();

private:

	CFileException* m_pError;		// 
	CFile			m_File;			// 
	UINT			m_uiOpenFlags;	// 
	bool			m_bOpen;		// 

public:

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Flush() saves the memory to disk
	virtual void Flush();
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Open(...) opens and loads a physical File into memory
	virtual bool Open(CString strFilename, UINT uiOpenFlags, CFileException *pError = NULL);
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Close() saves the contents of the memory to the disk and closes it.
	virtual void Close();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			ReadString(...) reads a string
	virtual BOOL ReadString(CString& rString); 

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			WriteString(...) appends a string
	virtual void WriteString( LPCTSTR lpsz );

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Duplicate(...) Duplicates the CXTMemFile to a CFile derived class
	virtual bool Duplicate(CFile *fDuplicate);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Duplicate(...) Duplicates the CXTMemFile to a CFile derived class
	virtual bool Duplicate(CString strDup);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Discard() discards all changes to file since Open() or last Flush()
	virtual bool Discard();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Insert(...) inserts any File and returns the length of actual copied bytes
	virtual DWORD Insert(CFile* fSrc, DWORD dwSourcePos, DWORD dwDestPos, DWORD dwBytes);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Insert(...) inserts any File and returns the length of actual copied bytes
	virtual DWORD Insert(CString strSrc, DWORD dwSourcePos, DWORD dwDestPos, DWORD dwBytes);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Extract(...) Extracts bytes to a file and returns the length of actual copied bytes
	virtual DWORD Extract(CFile *fDest,DWORD dwStartPos, DWORD dwBytes);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Extract(...) Extracts bytes to a file and returns the length of actual copied bytes
	virtual DWORD Extract(CString strDest, DWORD dwStartPos, DWORD dwBytes);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Find(...) Finds data in the file
	LONG FindData(void* pData, DWORD dwDataLen, LONG lStartPos);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Importing operator
	void operator =( CFile *fDup);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Importing operator
	void operator =( CString strDup);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Positioning operator
	void operator =( DWORD dwFilePos);
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Appending operator
	void operator +=( CFile *fApp);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Appending operator
	void operator +=( CString strApp);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Indexing Operator
	BYTE operator [](DWORD dwFilePos);

protected:

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Load() loads the file into Memory
	virtual bool Load();  
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Save() saves the file to Disk
	virtual bool Save();
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Import() imports the data of a CFile derived object (operator = )
	virtual bool Import(CFile *fImp);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Appends a CFile derived object to the file (operator += )
	virtual bool Append(CFile *fApp);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // #if !defined(__XTMEMFILE_H__)
