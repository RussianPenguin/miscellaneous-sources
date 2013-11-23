// XTShell.h interface for the CXTShell class.
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
//////////////////////////////////////////////////////////////////////

#if !defined(__XTSHELL_H__)
#define __XTSHELL_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CXTShell class is used to perform shell file operations
/////////////////////////////////////////////////////////////////////////////
class _XT_EXT_CLASS CXTShell
{

public:
	
	// Default constructor
	//
	CXTShell(LPCTSTR lpszFileName=NULL);

	// Virtual destructor
	//
	virtual ~CXTShell();

public:

    int			m_iImageIndex;	// index into system image list
    CString		m_strPath;		// full file path used with BrowseForFolder(...)
    CString		m_strInitDir;	// start directory used with BrowseForFolder(...)
    CString		m_strSelDir;	// selected directory used with BrowseForFolder(...)
    CString		m_strTitle;		// dialog title used with BrowseForFolder(...)

protected:

	CString		m_strFileName;			// contains the full path to a file or folder
	char		m_szDrive[_MAX_DRIVE];	// contains the drive letter
	char		m_szDir[_MAX_DIR];		// contains the directory string
	char		m_szFname[_MAX_FNAME];	// contains the file name minus path and ext
	char		m_szExt[_MAX_EXT];		// contains the file extension

public:
	virtual void SplitPath(CString strFileName, char* szDrive, char* szDir, char* szFile, char* szExt);

	// this member function is used to retrieve a key from the registry
	//
	virtual LONG GetRegKey(HKEY key, LPCTSTR subkey, LPTSTR retdata);

	// this member funciont is used to perform execute command
	//
	virtual HINSTANCE ShellExec(LPCTSTR lpszExec, int nShow);

	// this member function returns the size of the file formatted in KB.
	//
	virtual CString GetFileSizeString(
		// a string containing the system file size
		LPCTSTR lpszFileSize);

	// this member function returns a formatted string for the last 
	// time file was written to.
	//
	virtual CString GetLastWriteTime(
		// points to a CTime object
		CTime* pTime);

	// retrieves the path only of the current filename. if the filename 
	// is "c:\incoming\hello.txt", this function returns "c:"
	//
	virtual CString GetFileDrive(
		// full path of file name to parse
		LPCTSTR lpszFileName=NULL);

	// this member function determines whether a file or directory exists.
	//
	virtual BOOL Exist(
		// full path of file or directory name
		LPCTSTR lpszFileName=NULL);

	// this member function returns the icon index of the file or folder
	//
	virtual int	GetIconIndex(
		// full path of file or directory name.
		LPCTSTR lpszFileName=NULL,
		// can be large or small icon
		UINT uFlags=SHGFI_SMALLICON);

	// this member function returns the system display name for the file.
	//
	virtual CString GetDisplayName(
		// full path of file or directory name.
		LPCTSTR lpszFileName=NULL);

	// this member function returns the system description for the file.
	//
	virtual CString GetFileType(
		// full path of file or directory name.
		LPCTSTR lpszFileName=NULL);

	// this member function retrieves the file extension. if the filename is 
	// "c:\incoming\hello.txt", this function returns "txt".
	//
	virtual CString GetFileExt(
		// full path of file or directory name.
		LPCTSTR lpszFileName=NULL);

	// this member function retrieves the title of the filename excluding 
	// the path and extension. if the filename is "c:\incoming\hello.txt",
	// this function returns "hello".
	//
	virtual CString GetFileTitle(
		// full path of file or directory name.
		LPCTSTR lpszFileName=NULL);

	// this member function retrieves the path only of the current filename. 
	// if the filename is "c:\incoming\hello.txt", this function returns "c:\incoming\".
	//
	virtual CString GetRoot(
		// full path of file or directory name.
		LPCTSTR lpszFileName=NULL);

	// this member function retrieves current filename minus the path if the 
	// filename is "c:\incoming\hello.txt", this function returns "hello.txt".
	//
	virtual CString GetFileName(
		// full path of file or directory name.
		LPCTSTR lpszFileName=NULL);

	// this member function returns the system image list for small and large icons.
	// if you use this method, you must call CImageList::Detach() for both
	// image lists
	//
	virtual void GetSystemImageList(
		// points to a CImageList object that contains small icons
		CImageList* pSmallList,
		// points to a CImageList object that contains large icons
		CImageList* pLargeList);

// FUNCTIONS THAT DEAL WITH PIDLs

	// this member function gets the next PIDL in the list
	//
	virtual LPITEMIDLIST Next(LPCITEMIDLIST pidl);

	// this member function gets the size of the PIDL
	//
	virtual UINT GetSize(LPCITEMIDLIST pidl);

	// this member function allocates a PIDL
	//
	virtual LPITEMIDLIST Create(UINT cbSize);

	// this member function concatenates two PIDLs
	//
	virtual LPITEMIDLIST ConcatPidls(LPCITEMIDLIST pidl1, LPCITEMIDLIST pidl2);

	// this member function copies the ITEMID
	//
	virtual LPITEMIDLIST CopyITEMID(LPMALLOC lpMalloc, LPITEMIDLIST lpi);

	// this member function gets the friendly name for the folder
	//
	virtual BOOL GetName(LPSHELLFOLDER lpsf, LPITEMIDLIST lpi, DWORD dwFlags, LPTSTR lpFriendlyName);

	// this member function gets the Fully qualified Pidls for the folder 
	//
	virtual LPITEMIDLIST GetFullyQualPidl(LPSHELLFOLDER lpsf, LPITEMIDLIST lpi);

	// this member function Displays a popup context menu, given a parent shell folder,
	// relative item id and screen location. returns TRUE on success, FALSE on failure
	//
	virtual BOOL DoTheMenuThing(
		// parent window handle
		HWND hwnd,
		// pointer to parent shell folder
		LPSHELLFOLDER lpsfParent,
		// pointer to item id that is relative to lpsfParent
		LPITEMIDLIST lpi,
		// screen location of where to popup the menu
		LPPOINT lppt);

	// this member function gets the index for the current icon. Index is 
	// index into system image list. returns icon index for current item.
	//
	virtual int	GetIcon(
		// fully qualified item id list for current item.
		LPITEMIDLIST lpi,
		// flags for SHGetFileInfo()
		UINT uFlags);

	// this member function gets the index for the normal and 
	// selected icons for the current item.
	//
	virtual void GetNormalAndSelectedIcons(
		// fully qualified item id list for current item.
		LPITEMIDLIST lpifq,
		// pointer to treeview item we are about to add to the tree.
		LPTV_ITEM lptvitem);

	// Makes a copy of the next item in an item ID list. Returns pointer to 
	// an ITEMIDLIST containing the copied item ID.
	//
	virtual LPITEMIDLIST DuplicateItem (
		// Pointer to an IMalloc interface.
		LPMALLOC pMalloc,
		// Pointer to an item ID list.
		LPITEMIDLIST pidl);

	// Finds the next item in an item ID list. Returns pointer to the next item.
	//
	virtual LPITEMIDLIST GetNextItem (
		// Pointer to an item ID list.
		LPITEMIDLIST pidl);

	// Computes the number of item IDs in an item ID list. Returns number 
	// of item IDs in the list.
	virtual UINT GetItemCount (
		// Pointer to an item ID list.
		LPITEMIDLIST pidl);

	// Given a path name to a file or folder object, displays the shell's context 
	// menu for that object and executes the menu command (if any) selected by the user.
	//
	virtual BOOL DoExplorerMenu (
		// Handle of the window in which the menu will be displayed.
		HWND hwnd,
		// Pointer to an ANSI or Unicode string specifying the path to the object.
		LPCTSTR pszPath,
		// x and y coordinates of the point where the menu's upper left corner should be 
		// located, in client coordinates relative to hwnd.
		POINT point);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // #if !defined(__XTSHELL_H__)

