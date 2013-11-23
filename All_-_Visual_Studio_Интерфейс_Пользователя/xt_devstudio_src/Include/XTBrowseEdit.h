// XTBrowseEdit.h : interface for the CXTBrowseEdit class.
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

#if !defined(__XTBROWSEEDIT_H__)
#define __XTBROWSEEDIT_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "XTButton.h"

// forwards
class CXTBrowseEdit;

/////////////////////////////////////////////////////////////////////////////
// CXTBrowseButton is a CButton derived class which is used by
// the CXTBrowseEdit class.
/////////////////////////////////////////////////////////////////////////////
class _XT_EXT_CLASS CXTBrowseButton : public CXTButton
{
	DECLARE_DYNAMIC(CXTBrowseButton)

public:

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Constructor - handles default initialization
	CXTBrowseButton();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Destructor - handles clean up.
	virtual ~CXTBrowseButton();

protected:
	
	int				m_nGap;
	DWORD   		m_dwBStyle;		// search type
	UINT			m_nID;			// resource id for push button
	UINT			m_nMenu;		// popup menu id
	UINT			m_nSubMenuIndx;	// index of popup submenu.
	CXTBrowseEdit*	m_pEditWnd;		// Parent edit control.

public:

	// -> Parameters:		nGap	-	Ammount in pixels to offset the browse button.
	// -> Return Value:		
	// -> Remarks:			This member function will set the gap between the browse button
	//						and the edit control.
	inline void SetGap(int nGap);

	//{{AFX_VIRTUAL(CXTBrowseButton)
	public:
	virtual BOOL Create(CXTBrowseEdit* pEditWnd, const RECT& rect, DWORD dwStyle, UINT nID, UINT nMenu=-1, UINT nSubMenuIndx=-1);
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CXTBrowseButton)
	afx_msg void OnClicked();
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

//---------------------------------------------------------------------------
inline void CXTBrowseButton::SetGap(int nGap)
	{ m_nGap = nGap; }
//---------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////
// CXTBrowseEdit is a CEdit derived class which has a push button associated
// with it. It can be used to search for directories, files or activate a
// popup menu
/////////////////////////////////////////////////////////////////////////////
class _XT_EXT_CLASS CXTBrowseEdit : public CEdit
{
	DECLARE_DYNAMIC(CXTBrowseEdit)

public:

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Constructor - handles default initialization
	CXTBrowseEdit();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Destructor - handles clean up.
	virtual ~CXTBrowseEdit();

protected:

	BOOL			m_bOpenFileDialog;	// TRUE for open file dialog, FALSE for save as see SetDlgOpenFile(...)
	CFileDialog*	m_pFileDialog;
	DWORD			m_dwFlags;
	CString			m_strDefExt;
	CString			m_strFileName;
	CString	 		m_strFilter;
	CString	    	m_strTitle;
	CXTBrowseButton	m_btnBrowse;		// push button
	DWORD   		m_dwBStyle;			// search type
	UINT			m_nMenu;			// popup menu id
	UINT			m_nSubMenuIndx;		// index of popup submenu.
	CWnd*			m_pParentWnd;		// parent of edit control.

public:

	// -> Parameters:		pFileDialog -	Points to the CFileDialog object to replace
	//										the standard file open dialog with.
	// -> Return Value:		
	// -> Remarks:			This member function will set a CFileDialog derived class object
	//						to be the file-open dialog.
	virtual void SetFileDialog(CFileDialog *pFileDialog);

	// -> Parameters:		bOpenFileDialog -	Set to TRUE to construct a File Open dialog 
	//											box or FALSE to construct a File Save As dialog
	//											box.
	// -> Return Value:		
	// -> Remarks:			This member function will set file open dialog style.
	virtual void SetDlgOpenFile(BOOL bOpenFileDialog=TRUE);

	// -> Parameters:		strDefExt -		Points to a NULL terminated string that
	//										represents the default file extension to
	//										be used with the file open dialog.
	// -> Return Value:		
	// -> Remarks:			This member function sets the default extension for
	//						the file open dialog.
	virtual void SetDlgDefExt(LPCTSTR strDefExt=NULL);

	// -> Parameters:		strFileName -	Points to a NULL terminated string that
	//										represents the default file name to be
	//										used with the file open dialog.
	// -> Return Value:		
	// -> Remarks:			This member funciton sets the default file name for
	//						the file open dialog.
	virtual void SetDlgFileName(LPCTSTR strFileName=NULL);

	// -> Parameters:		dwFlags -	The desired OFN_ styles for the file open 
	//									dialog.
	// -> Return Value:		
	// -> Remarks:			This member function sets the style flags for the file
	//						open dialog.
	virtual void SetDlgStyle(DWORD dwFlags=OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT);

	// -> Parameters:		strFilter - Points to a NULL terminated string that
	//									represents the file filter used by the file
	//									open dialog.
	// -> Return Value:		
	// -> Remarks:			This member function sets the file filter for the file
	//						open dialog.
	virtual void SetDlgFilter(LPCTSTR strFilter=NULL);

	// -> Parameters:		pParentWnd -	Points to a CWnd object that represents the
	//										owner window for this control.
	// -> Return Value:		
	// -> Remarks:			This member function sets the owner for the file open dialog
	virtual void SetDlgOwner(CWnd* pParentWnd=NULL);

	// -> Parameters:		strTitle -	Points to a NULL terminated string the represents
	//									the title for the browse for directory dialog.
	// -> Return Value:		
	// -> Remarks:			This member function sets the title for the directory dialog.
	virtual void SetDlgTitle(LPCTSTR strTitle=NULL);

	// -> Parameters:		nType			-	Type of search to perform - BES_CHOOSEDIR,
	//											BES_CHOOSEFILE, BES_POPUPMENU.
	//						nMenu			-	If nType is a popup menu, resource id of menu.
	//						nSubMenuIndx	-	Index of submenu to display.
	// -> Return Value:		
	// -> Remarks:			This member function sets the current search type for the control
	virtual void SetBrowseStyle(DWORD dwBStyle, UINT nMenu=-1, int nSubMenuIndx=-1);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			This member fuction is called whenever the browse button is pressed
	//						and can be overridden to perform custom browse functions.
	virtual void OnBrowse();

	//{{AFX_VIRTUAL(CXTBrowseEdit)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CXTBrowseEdit)
	afx_msg void OnEnable(BOOL bEnable);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

//---------------------------------------------------------------------------
// NOTE: The following methods are obsolete, and are included here only for
// support to users who have upgraded from CJLibrary.
//---------------------------------------------------------------------------
public:
	virtual void SetSearchType(DWORD dwType, UINT nMenu = 0, int nSubMenuIndx = 0) {
		SetBrowseStyle(dwType, nMenu, nSubMenuIndx);
	}
};

//---------------------------------------------------------------------------
inline void CXTBrowseEdit::SetFileDialog(CFileDialog *pFileDialog/*=NULL*/)
	{ m_pFileDialog = pFileDialog; }
//---------------------------------------------------------------------------
inline void CXTBrowseEdit::SetDlgOpenFile(BOOL bOpenFileDialog/*=TRUE*/)
	{ m_bOpenFileDialog = bOpenFileDialog; }
//---------------------------------------------------------------------------
inline void CXTBrowseEdit::SetDlgDefExt(LPCTSTR strDefExt/*=NULL*/)
	{ m_strDefExt = strDefExt; }
//---------------------------------------------------------------------------
inline void CXTBrowseEdit::SetDlgFileName(LPCTSTR strFileName/*=NULL*/)
	{ m_strFileName = strFileName; }
//---------------------------------------------------------------------------
inline void CXTBrowseEdit::SetDlgStyle(DWORD dwFlags/*=OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT*/)
	{ m_dwFlags = dwFlags; }
//---------------------------------------------------------------------------
inline void CXTBrowseEdit::SetDlgFilter(LPCTSTR strFilter/*=NULL*/)
	{ m_strFilter = strFilter; }
//---------------------------------------------------------------------------
inline void CXTBrowseEdit::SetDlgOwner(CWnd* pParentWnd/*=NULL*/)
	{ m_pParentWnd = pParentWnd; }
//---------------------------------------------------------------------------
inline void CXTBrowseEdit::SetDlgTitle(LPCTSTR strTitle/*=NULL*/)
	{ m_strTitle = strTitle; }
//---------------------------------------------------------------------------
inline void CXTBrowseEdit::SetBrowseStyle(DWORD dwBStyle, UINT nMenu, int nSubMenuIndx)
	{ m_dwBStyle = dwBStyle; m_nMenu = nMenu; m_nSubMenuIndx = nSubMenuIndx; }
//---------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////
// CXTItemEdit window
/////////////////////////////////////////////////////////////////////////////
class _XT_EXT_CLASS CXTItemEdit : public CXTBrowseEdit
{
	DECLARE_DYNAMIC(CXTItemEdit)

public:

	// -> Parameters:		pParent			-	Points to the parent window.
	//						rect			-	Size of the edit item.
	//						strWindowText	-	Text to be initially displayed in the edit field.
	// -> Return Value:		
	// -> Remarks:			Constructor - handles default initialization. This will construct
	//						an "in-place" edit field that can be used to edit text in controls
	//						such as a listbox.
	CXTItemEdit(CWnd* pParent, const CRect& rect, CString& strWindowText, DWORD dwBStyle=BES_XT_CHOOSEDIR, bool bAutoDelete=true);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Destructor - handles clean up.
	virtual ~CXTItemEdit();

public:

	bool			m_bAutoDelete;		// true if self deleting.
	BOOL			m_bEscapeKey;		// TRUE if the edit window was closed with the escape key.
	CString&		m_strWindowText;	// The edit controls text.

public:

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			This member function is called whenever the control looses focus. 
	//						This will destroy the window, and notify the parent via WM_COMMAND
	//						that the editing has been completed. The two possible commands are:
	//						ON_BEN_XT_LABELEDITEND and ON_BEN_XT_LABELEDITCANCEL;
	virtual void EndLabelEdit();

	//{{AFX_VIRTUAL(CXTItemEdit)
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void PostNcDestroy();
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CXTItemEdit)
	protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // #if !defined(__XTBROWSEEDIT_H__)
