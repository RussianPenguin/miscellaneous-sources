// XTBrowseDialog.h: interface for the CXTBrowseDialog class.
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

#if !defined(__XTBROWSEDIALOG_H__)
#define __XTBROWSEDIALOG_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//////////////////////////////////////////////////////////////////////
// CXTBrowseDialog is a BROWSEINFO derived class which is used to diaplay
// a directory chooser dialog using shell extensions.
//////////////////////////////////////////////////////////////////////
class CXTBrowseDialog : protected BROWSEINFO  
{
public:

	// Call this member function to construct a CXTBrowseDialog object.
	//
	CXTBrowseDialog(
		// Points to a CWnd object that represents the parent 
		// window for the browse dialog.
		CWnd* pParent=NULL);

	// Destructor - handles cleanup and de-allocation
	//
	virtual ~CXTBrowseDialog();

protected:

	TCHAR	m_szSelPath[MAX_PATH];	// NULL terminated string that represents the selected directory.

public:

	// Call this member function to invoke the browse dialog box and return 
	// the dialog-box result when done. Returns IDOK if the OK button was pressed,
	// otherwise IDCANCEL.
	//
	UINT DoModal();
	
	// Call this member function to set the owner window for the dialog box.
	//
	void SetOwner(
		// Handle to the owner window for the dialog box.
		HWND hWnd);
	
	// Retuns a HWND handle to the owner window for the dialog box.
	//
	HWND GetOwner();
	
	// Call this member function to set the address of an ITEMIDLIST structure
	// which specifies the location of the root folder from which to browse.
	//
	void SetPidlRoot(
		// Address of an ITEMIDLIST structure specifying the location
		// of the root folder from which to browse. Only the specified
		// folder and its subfolders appear in the dialog box. This member
		// can be NULL; in that case, the namespace root
		// (the desktop folder) is used
		LPCITEMIDLIST pidl);
	
	// Call this member function to return a the address of the ITEMIDLIST
	// structure that was specified for the location of the root folder.
	//
	LPCITEMIDLIST GetPidlRoot();
	
	// Call this member function to set the address for the display name
	// the dialog box will use.
	//
	void SetDisplayName(
		// Address of a buffer to receive the display name of the folder
		// selected by the user. The size of this buffer is assumed to be
		// MAX_PATH bytes. 
		TCHAR* szDisplayName);

	// Call this member function to return the display name that is used
	// by the browse dialog box.
	//
	LPCTSTR GetDisplayName();
	
	// Call this member function to set the title for the browse dialog box.
	//
	void SetTitle(
		// Address of a null-terminated string that is displayed above the
		// tree view control in the dialog box. This string can be used to
		// specify instructions to the user. 
		TCHAR* szTitle);
	
	// Call this member function to return a NULL terminated string that represents
	// that title that was set for the dialog box.
	//
	LPCTSTR GetTitle();
	
	// Call this member function to set the flags for specifying the options
	// for the browse dialog box.
	//
	void SetOptions(
		// Flags specifying the options for the dialog box. This member can
		// include zero or a combination of the following values:
		//
		// BIF_BROWSEFORCOMPUTER	Only return computers. If the user selects
		//							anything other than a computer, the OK 
		//							button is grayed.  
		// BIF_BROWSEFORPRINTER		Only return printers. If the user selects 
		//							anything other than a printer, the OK 
		//							button is grayed.  
		// BIF_BROWSEINCLUDEFILES	The browse dialog will display files as 
		//							well as folders.  
		// BIF_DONTGOBELOWDOMAIN	Do not include network folders below the 
		//							domain level in the tree view control.  
		// BIF_EDITBOX				Version 4.71. The browse dialog includes an 
		//							edit control in which the user can type the
		//							name of an item.  
		// BIF_RETURNFSANCESTORS	Only return file system ancestors. If the 
		//							user selects anything other than a file system
		//							ancestor, the OK button is grayed.  
		// BIF_RETURNONLYFSDIRS		Only return file system directories. If the user
		//							selects folders that are not part of the file 
		//							system, the OK button is grayed.  
		// BIF_STATUSTEXT			Include a status area in the dialog box. The 
		//							callback function can set the status text by 
		//							sending messages to the dialog box.  
		// BIF_VALIDATE				Version 4.71. If the user types an invalid name 
		//							into the edit box, the browse dialog will call 
		//							the application's BrowseCallbackProc with the 
		//							BFFM_VALIDATEFAILED message. This flag is ignored
		//							if BIF_EDITBOX is not specified.  
		UINT uf);
	
	// Call this member function to return the flags specifying the options 
	// that have been set for the dialog box
	//
	UINT GetOptions();
	
	// Call this member function to define the address for the BrowseCallbackProc function
	// to be called when an event occrus.
	//
	void SetCallback(
		// Address of an application-defined function that the dialog box calls when 
		// an event occurs. For more information, see the BrowseCallbackProc function.
		// This member can be NULL. 
		BFFCALLBACK pf);

	// Call this member function to return the address for the BrowseCallbackProc function
	// that is called when an event occurs.
	//
	BFFCALLBACK GetCallback();
	
	// Call this member function to set the application data that is passed to
	// the callback function.
	//
	void SetData(
		// Application-defined value that the dialog box passes to the callback 
		// function, if one is specified.
		LPARAM lp);
	
	// This member function will return the application data that was set to be
	// passed to the callback function, if one is specified.
	//
	LPARAM GetData();
	
	// Call this member function to set the initial path to select when the 
	// browse dialog is first opened.
	//
	void SetSelPath(
		// A NULL terminated string that represents the directory that is selected
		// when the dialog is initially opened. If not set, GetCurrentDirectory
		// is called to set the directory.
		TCHAR* szSelPath);

	// Returns a NULL termiated string that represents the currently 
	// selected directory.
	//
	LPCTSTR GetSelPath();

	// Returns the index to the system image list of the image associated with the 
	// selected folder.
	//
	int GetImage();

private:

	// Application-defined callback function used with the SHBrowseForFolder function. 
	// The browse dialog box calls this function to notify it about events. You can 
	// define your own callback function by using the SetCallback method.
	static int CALLBACK BrowseCtrlCallback(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData);
};

//--------------------------------------------------------------------
inline void CXTBrowseDialog::SetOwner(HWND hWnd)
	{ hwndOwner = hWnd; }
//--------------------------------------------------------------------
inline HWND CXTBrowseDialog::GetOwner()
	{ return hwndOwner; }
//--------------------------------------------------------------------
inline void CXTBrowseDialog::SetPidlRoot(LPCITEMIDLIST pidl)
	{ pidlRoot = pidl; }
//--------------------------------------------------------------------
inline LPCITEMIDLIST CXTBrowseDialog::GetPidlRoot()
	{ return pidlRoot; }
//--------------------------------------------------------------------
inline void CXTBrowseDialog::SetDisplayName(TCHAR* szDisplayName)
	{ pszDisplayName = szDisplayName; }
//--------------------------------------------------------------------
inline LPCTSTR CXTBrowseDialog::GetDisplayName()
	{ return pszDisplayName; }
//--------------------------------------------------------------------
inline void CXTBrowseDialog::SetTitle(TCHAR* szTitle)
	{ lpszTitle = szTitle; }
//--------------------------------------------------------------------
inline LPCTSTR CXTBrowseDialog::GetTitle()
	{ return lpszTitle; }
//--------------------------------------------------------------------
inline void CXTBrowseDialog::SetOptions(UINT uf)
	{ ulFlags = uf; }
//--------------------------------------------------------------------
inline UINT CXTBrowseDialog::GetOptions()
	{ return ulFlags; }
//--------------------------------------------------------------------
inline void CXTBrowseDialog::SetCallback(BFFCALLBACK pf)
	{ lpfn = pf; }
//--------------------------------------------------------------------
inline BFFCALLBACK CXTBrowseDialog::GetCallback()
	{ return lpfn; }
//--------------------------------------------------------------------
inline void CXTBrowseDialog::SetData(LPARAM lp)
	{ lParam = lp; }
//--------------------------------------------------------------------
inline LPARAM CXTBrowseDialog::GetData()
	{ return lParam; }
//--------------------------------------------------------------------
inline void CXTBrowseDialog::SetSelPath(TCHAR* szSelPath)
	{ _tcscpy(m_szSelPath, szSelPath); }
//--------------------------------------------------------------------
inline LPCTSTR CXTBrowseDialog::GetSelPath()
	{ return m_szSelPath; }
//--------------------------------------------------------------------
inline int CXTBrowseDialog::GetImage()
	{ return iImage; }
//--------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(__XTBROWSEDIALOG_H__)
