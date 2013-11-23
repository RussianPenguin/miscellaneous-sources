// XTShellList.h interface for the CXTShellList class.
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

#if !defined(__XTSHELLLIST_H__)
#define __XTSHELLLIST_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "XTShell.h"
#include "XTListCtrl.h"

// class forwards
class CXTShellTree;

/////////////////////////////////////////////////////////////////////////////
// CXTShellList is a CXTListCtrl derived class which is used to display
// system files and folders, typically associated with a CXTShellTree object
/////////////////////////////////////////////////////////////////////////////
class _XT_EXT_CLASS CXTShellList : public CXTListCtrl
{
	DECLARE_DYNAMIC(CXTShellList)

public:
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Constructor - handles default initialization.
	CXTShellList();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Destructor - handles cleanup and de-allocation.
	virtual ~CXTShellList();

protected:

	CXTShell		m_shell;			// used for shell operations
	CXTShellTree*	m_pTreeCtrl;		// points to a CXTShellTree that is associated with this control
	BOOL			m_bBuildingList;	// 
	BOOL			m_bShowHidden;		// 

public:

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual void BuildDefaultColumns();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			This member function rebuilds the current directory list.
	virtual void RefreshList();

	// -> Parameters:		pTreeCtrl	-	
	// -> Return Value:		
	// -> Remarks:			Call this member function to associate a CXTShellTree object 
	//						with this control
	virtual void AssociateTree(CXTShellTree *pTreeCtrl);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			This member function is called to initialize the system 
	//						image list used by the list control
	virtual BOOL InitSystemImageLists();

	// -> Parameters:		lptvid	-	Pointer to TreeView item data
	//						lpsf	-	Pointer to parent shell folder
	// -> Return Value:		
	// -> Remarks:			This member function is called to initialize the list control items.
	virtual BOOL InitListViewItems(LPXT_TVITEMDATA lptvid, LPSHELLFOLDER lpsf);

	// -> Parameters:		lptvid	-	Pointer to TreeView item data
	//						lpsf	-	Pointer to parent shell folder
	// -> Return Value:		
	// -> Remarks:			This member function is called to actually populate the 
	//						list control items
	virtual BOOL PopulateListView(LPXT_TVITEMDATA lptvid, LPSHELLFOLDER lpsf);

	// -> Parameters:		strFileName	-	
	//						bParse		-	
	// -> Return Value:		
	// -> Remarks:			This member function is called to insert a single item 
	//						into the list control
	virtual int InsertListItem(CString strFileName, BOOL bParse=TRUE);

	// -> Parameters:		lParam1		-	
	//						lParam2		-	
	//						lparamSort	-	
	// -> Return Value:		
	// -> Remarks:			Callback routine for sorting list
	static int CALLBACK ListViewCompareProc(LPARAM lParam1, LPARAM lParam2, LPARAM lparamSort);

	// -> Parameters:		nCol		-	passed in from control, index of column clicked.
	//						bAscending	-	passed in from control, true if sort order 
	//										should be ascending.
	// -> Return Value:		
	// -> Remarks:			Override this member function in your derived class to 
	//						peform custom sort routines.
	virtual bool SortList(int nCol, bool bAscending );

	//{{AFX_VIRTUAL(CXTShellList)
	//}}AFX_VIRTUAL

protected:

	//{{AFX_MSG(CXTShellList)
	afx_msg void OnRclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeleteitem(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnGetdispinfo(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	afx_msg long OnShellNotify(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
};

//---------------------------------------------------------------------------
inline void CXTShellList::AssociateTree(CXTShellTree *pTreeCtrl)
	{ ASSERT( pTreeCtrl ); m_pTreeCtrl = pTreeCtrl; }
//---------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // #if !defined(__XTSHELLLIST_H__)
