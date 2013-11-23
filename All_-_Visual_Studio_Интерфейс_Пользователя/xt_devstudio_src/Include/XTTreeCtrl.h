// XTTreeCtrl.h interface for the CXTTreeCtrl class.
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

#if !defined(__XTTREECTRL_H__)
#define __XTTREECTRL_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CXTTreeCtrl is a CTreeCtrl derived class which extends the base class to add
// additional functionality and enhancements.
/////////////////////////////////////////////////////////////////////////////
class _XT_EXT_CLASS CXTTreeCtrl : public CTreeCtrl
{
	DECLARE_DYNAMIC(CXTTreeCtrl)

public:
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Constructor - handles default initialization.
	CXTTreeCtrl();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Destructor - handles cleanup and de-allocation.
	virtual ~CXTTreeCtrl();

protected:

	HTREEITEM	m_hItemFirstSel;	// First selected item in a multi selection tree control.
	DWORD		m_dwDragStart;		// The number of milliseconds that have elapsed since the system was started.
	BOOL		m_bMultiSelect;		// TRUE for a multiselection tree control.

	// Struct that contains the color and logfont for the tree item.
	CMap<void*,void*,XT_CLRFONT,XT_CLRFONT&> m_mapColorFont;

public:

	// -> Parameters:		hItem	-	Handle of a tree item.
	//						nCode	-	A flag indicating the type of relation to hItem. This 
	//									flag can be one of the following values:
	//									
	//									TVGN_CARET				Retrieves the currently selected item.
	//									TVGN_CHILD				Retrieves the first child item. The 
	//															hItem parameter must be NULL.
	//									TVGN_DROPHILITE			Retrieves the item that is the target
	//															of a drag-and-drop operation.
	//									TVGN_FIRSTVISIBLE		Retrieves the first visible item.
	//									TVGN_NEXT				Retrieves the next sibling item.
	//									TVGN_NEXTVISIBLE		Retrieves the next visible item that 
	//															follows the specified item.
	//									TVGN_PARENT				Retrieves the parent of the specified 
	//															item.
	//									TVGN_PREVIOUS			Retrieves the previous sibling item.
	//									TVGN_PREVIOUSVISIBLE	Retrieves the first visible item 
	//															that precedes the specified item.
	//									TVGN_ROOT				Retrieves the first child item of 
	//															the root item of which the specified 
	//															item is a part.
	//
	// -> Return Value:		Returns The handle of the next item if successful; otherwise NULL.
	// -> Remarks:			This member function will retrieve the tree view item that 
	//						has the specified relationship, indicated by the nCode parameter, 
	//						to hItem.
	virtual HTREEITEM GetNextItem(HTREEITEM hItem, UINT nCode);

	// -> Parameters:		hItem	-	The reference item.
	// -> Return Value:		Returns the item immediately below the reference item.
	// -> Remarks:			Get next item as if outline was completely expanded.
	virtual HTREEITEM GetNextItem(HTREEITEM hItem);

	// -> Parameters:		hItem	-	The reference item.
	// -> Return Value:		Returns the item immediately above the reference item.
	// -> Remarks:			Get previous item as if outline was completely expanded.
	virtual HTREEITEM GetPrevItem(HTREEITEM hItem);

	// -> Parameters:		hItem	-	Node identifying the branch. NULL will return the 
	//									last item in outine.
	// -> Return Value:		Returns returns the last item.
	// -> Remarks:			Gets last item in the branch.
	virtual HTREEITEM GetLastItem(HTREEITEM hItem);
	
	// -> Parameters:		hItem	-	The reference item.
	// -> Return Value:		Returns the previously selected tree item in a multi selection 
	//						tree control.
	// -> Remarks:			
	virtual HTREEITEM GetPrevSelectedItem(HTREEITEM hItem);

	// -> Parameters:		hItem	-	The reference item.
	// -> Return Value:		Returns the next selected item in a multi selection tree control.
	// -> Remarks:			
	virtual HTREEITEM GetNextSelectedItem(HTREEITEM hItem);
	
	// -> Parameters:		
	// -> Return Value:		Returns the first selected item in a multi selection tree control.
	// -> Remarks:			
	virtual HTREEITEM GetFirstSelectedItem();

	// -> Parameters:		hItem	-	The reference item.
	// -> Return Value:		Returns the RGB text value for the referenced tree item, or
	//						(COLORREF)-1 if color was not set.
	// -> Remarks:			
	virtual COLORREF GetItemColor(HTREEITEM hItem);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Clears all selections from multi selection tree control.
	virtual void ClearSelection();

	// -> Parameters:		hItem	-	The reference item
	//						logfont	-	New font for tree item.
	// -> Return Value:		
	// -> Remarks:			Sets the font for the reference tree item.
	virtual void SetItemFont(HTREEITEM hItem, LOGFONT& logfont);

	// -> Parameters:		hItem	-	The reference item
	//						bBold	-	TRUE for bold font.
	// -> Return Value:		
	// -> Remarks:			Sets the font to bold for the refernece tree item.
	virtual void SetItemBold(HTREEITEM hItem, BOOL bBold=TRUE);

	// -> Parameters:		hItem	-	The reference item
	//						color	-	RGB value for the tree items text.
	// -> Return Value:		
	// -> Remarks:			Sets the text color for the tree item.
	virtual void SetItemColor(HTREEITEM hItem, COLORREF color);

	// -> Parameters:		bMultiSelect	-	TRUE for multi selection tree control.
	// -> Return Value:		
	// -> Remarks:			Enables multi selection tree control.
	virtual void EnableMultiSelect(BOOL bMultiSelect=TRUE);

	// -> Parameters:		hItem		-	The reference item
	//						plogfont	-	Item's font.
	// -> Return Value:		
	// -> Remarks:			Returns the current font used by the tree item.
	virtual BOOL GetItemFont(HTREEITEM hItem, LOGFONT* plogfont);

	// -> Parameters:		hItem		-	The reference item
	// -> Return Value:		
	// -> Remarks:			Returns TRUE if the tree item has a bold font.
	virtual BOOL GetItemBold(HTREEITEM hItem);

	// -> Parameters:		hItemFrom	-	The item to start selecting from.
	//						hItemTo		-	The item to end selection at.
	// -> Return Value:		
	// -> Remarks:			Selects items from hItemFrom to hItemTo in a multi selection tree 
	//						control. Does not select child item if parent is collapsed. Removes 
	//						selection from all other items.
	virtual BOOL SelectItems(HTREEITEM hItemFrom, HTREEITEM hItemTo);

	// -> Parameters:		lpszSearch		-	String to search for.
	//						bCaseSensitive	-	Should the search be case sensitive.
	//						bDownDir		-	Search direction - TRUE for down.
	//						bWholeWord		-	True if search should match whole words.
	//						hItem			-	Item to start searching from. NULL for currently 
	//											selected item.
	// -> Return Value:		Returns the handle to the item or NULL.
	// -> Remarks:			Finds an item that contains the search string.
	virtual HTREEITEM FindItem(LPCTSTR lpszSearch, BOOL bCaseSensitive=FALSE, BOOL bDownDir=TRUE, BOOL bWholeWord=FALSE, HTREEITEM hItem=NULL);

protected:

	// -> Parameters:		hItem		-	The reference item
	// -> Return Value:		Returns TRUE if item matches the criteria.
	// -> Remarks:			Virtual function used by FindItem to allow this function to filter the 
	//						result of FindItem.
	virtual BOOL IsFindValid(HTREEITEM hti);

	//{{AFX_VIRTUAL(CXTTreeCtrl)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CXTTreeCtrl)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg UINT OnNcHitTest(CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

//---------------------------------------------------------------------------
inline HTREEITEM CXTTreeCtrl::GetNextItem( HTREEITEM hItem, UINT nCode )
	{ ASSERT(::IsWindow(m_hWnd)); return CTreeCtrl::GetNextItem( hItem, nCode ); }
//---------------------------------------------------------------------------
inline void CXTTreeCtrl::EnableMultiSelect(BOOL bMultiSelect)
	{ m_bMultiSelect = bMultiSelect; }
//---------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // #if !defined(__XTTREECTRL_H__)
