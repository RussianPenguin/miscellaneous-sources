// XTShellTree.h interface for the CXTShellTree class.
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

#if !defined(__XTSHELLTREE_H__)
#define __XTSHELLTREE_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "XTShell.h"
#include "XTTreeCtrl.h"

// class forwards
class CXTShellList;

/////////////////////////////////////////////////////////////////////////////
// CXTShellTree is a CXTTreeCtrl derived class which is used to display
// system files and folders, typically associated with a CXTShellList object
/////////////////////////////////////////////////////////////////////////////
class _XT_EXT_CLASS CXTShellTree : public CXTTreeCtrl
{
	DECLARE_DYNAMIC(CXTShellTree)

public:
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Constructor - handles default initialization.
	CXTShellTree();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Destructor - handles cleanup and de-allocation.
	virtual ~CXTShellTree();

protected:

	CXTShell		m_shell;		// used for shell operations
	CXTShellList*	m_pListCtrl;	// CXTShellList that is associated with this control 
	CComboBox*		m_pComboBox;	// CComboBox that is associated with this control see AssociateCombo(...)
	bool			m_bRefresh;		// true when the control is to be refreshed
	bool			m_bOutaHere;	// true when the control is destroyed
	bool			m_bFoldersOnly;	// set to TRUE for 'real' folder display only.
	HTREEITEM		m_htiCurrent;	// currently selected tree item

	// Enumeration that holds the type of object folder or drive
	enum FindAttribs { type_drive, type_folder };

public:

	// -> Parameters:		bFoldersOnly	-	true to only display folders.
	// -> Return Value:		
	// -> Remarks:			This member function will set the explorer tree to display
	//						folders only, and not items such as control panel or printers.
	void ShowFoldersOnly(bool bFoldersOnly=true);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			This member function obtains a handle to the system image 
	//						list and attaches it to the tree control. DO NOT DELETE 
	//						the imagelist.
	virtual BOOL InitSystemImageLists();

	// -> Parameters:		lpsf	-	pointer to shell folder that we want to enumerate items
	//						lpifq	-	Fully qualified item id list to the item that we are 
	//									enumerating items for.  In other words, this is the 
	//									PIDL to the item identified by the lpsf parameter.
	//						hParent	-	parent node.
	// -> Return Value:		
	// -> Remarks:			This member function fills a branch of the TreeView control. 
	//						Given the shell folder, enumerate the subitems of this folder, 
	//						and add the appropriate items to the tree.
	//
	//						This function enumerates the items in the folder identifed by 
	//						lpsf. Note that since we are filling the left hand pane, we will 
	//						only add items that are folders and/or have sub-folders.  We *could* 
	//						put all items in here if we wanted, but that's not the intent.
	virtual void FillTreeView(LPSHELLFOLDER lpsf, LPITEMIDLIST lpifq, HTREEITEM hParent);

	// -> Parameters:		bRefresh	-	true when refreshing tree
	// -> Return Value:		
	// -> Remarks:			This member function processes the File.Fill/RefreshTree command
	virtual void OnFill(bool bRefresh=false);

	// -> Parameters:		lpszPath	-	path to populate
	// -> Return Value:		
	// -> Remarks:			This member function populates tree based upon path.
	virtual void PopulateTree(LPCTSTR lpszPath);

	// -> Parameters:		szFindPath	-	path to find
	// -> Return Value:		
	// -> Remarks:			This member function will "tunnel" the tree to find the 
	//						specified path. This will only work when the OnFill(...) method 
	//						is used to populate the tree.
	virtual void TunnelTree(CString szFindPath);

	// -> Parameters:		pComboBox	-	combo box to associate
	// -> Return Value:		
	// -> Remarks:			This member function is used to associate a CComboBox object 
	//						with the control. whenever the path changes, the combo is updated.
	virtual void AssociateCombo(CComboBox *pComboBox);

	// -> Parameters:		pListCtrl	-	list control to associate
	// -> Return Value:		
	// -> Remarks:			This member function is used to associate a CXTShellList object 
	//						with the control. whenever the path changes, the list is updated.
	virtual void AssociateList(CXTShellList *pListCtrl);

	// -> Parameters:		hItem			-	tree item to get path for
	//						strFolderPath	-	reference to a CString object to contain 
	//											folder path.
	// -> Return Value:		If the path is not in the filesystem(eg MyComputer) or none is 
	//						selected it returns FALSE.
	// -> Remarks:			This member function retrieves the path of a folder item, does 
	//						not have to be selected. Pass a CString object that will hold the 
	//						folder path.
	virtual BOOL GetFolderItemPath(HTREEITEM hItem, CString &strFolderPath);

	// -> Parameters:		strFolderPath	-	reference to a CString object to contain 
	//											folder path.
	// -> Return Value:		If the path is not in the filesystem(eg MyComputer) or none is 
	//						selected it returns FALSE. 
	// -> Remarks:			This member function retrieves the path of a folder item, does not 
	//						have to be selected. Pass a CString object that will hold the folder 
	//						path.
	virtual BOOL GetSelectedFolderPath(CString &strFolderPath);

	// -> Parameters:		treeNode		-	tree item to begin search from
	//						szSearchName	-	string to search for
	//						attr			-	looking for folder or drive
	// -> Return Value:		
	// -> Remarks:			This member function searchs the tree for a specified folder.
	virtual BOOL SearchTree(HTREEITEM treeNode, CString szSearchName, FindAttribs attr);

	// -> Parameters:		lParam1		-	
	//						lParam2		-	
	//						lparamSort	-	
	// -> Return Value:		
	// -> Remarks:			Callback routine for sorting tree.
	static int CALLBACK TreeViewCompareProc(LPARAM lparam1, LPARAM lparam2, LPARAM lparamSort);

	//{{AFX_VIRTUAL(CXTShellTree)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

protected:

	//{{AFX_MSG(CXTShellTree)
	afx_msg void OnRclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeleteitem(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemexpanding(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDestroy();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

//---------------------------------------------------------------------------
inline void CXTShellTree::ShowFoldersOnly(bool bFoldersOnly/*=true*/)
	{ m_bFoldersOnly = bFoldersOnly; }
//---------------------------------------------------------------------------
inline void CXTShellTree::AssociateList(CXTShellList *pListCtrl)
	{ ASSERT( pListCtrl != NULL ); m_pListCtrl = pListCtrl; }
//---------------------------------------------------------------------------
inline void CXTShellTree::AssociateCombo(CComboBox *pComboBox)
	{ ASSERT( pComboBox != NULL ); 	m_pComboBox = pComboBox; }
//---------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // #if !defined(__XTSHELLTREE_H__)
