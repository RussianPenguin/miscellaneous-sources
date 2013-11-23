// XTListView.h interface for the CXTListView class.
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

#if !defined(__XTLISTVIEW_H__)
#define __XTLISTVIEW_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "XTFlatHeaderCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CXTListView is a CListView derived class which implements a
// flat header and generic sorting routines.
/////////////////////////////////////////////////////////////////////////////
class _XT_EXT_CLASS CXTListView : public CListView
{
	DECLARE_DYNCREATE(CXTListView)

public:
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Constructor - handles default initialization.
	CXTListView();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Destructor - handles cleanup and de-allocation.
	virtual ~CXTListView();

protected:

	int					m_nMinColWidth;		// minimum width for columns
	int					m_nMaxColWidth;		// maximum width for columns
	int					m_nSortedCol;		// index of currently selected column
	CXTFlatHeaderCtrl*	m_pHeaderCtrl;		// points to subclassed flat header control.
	CString				m_strSection;		// registry section name.
	CString				m_strEntry;			// registry entry name.
	CString				m_strDefault;		// registry default value.
	CListCtrl*			m_pListCtrl;		// points to the list control associated with this view.
	COLORREF			m_clrText;			// RGB value for row text color.
	COLORREF			m_clrTextBk;		// RGB value for row text background color.
	bool				m_bNoColSizing;		// if true, column sizing is disabled.
	int					m_nMinSize;			// if set, columns will have a minimum size requirement.
	bool				m_bAscending;		// flag to determine sorting order
	bool				m_bAutoSave;		// true if saving column widths.

public:
	
	// -> Parameters:		nCol -	Zero-based index of the column to set the sort image for.
	//						bAsc -	TRUE if ascending, otherwise FALSE.
	// -> Return Value:		Zero-based index of the previously sorted column.
	// -> Remarks:			This member function will set the sort image for the
	//						specified column.
	virtual int SetSortImage(int nCol, BOOL bAsc);

	// -> Parameters:		nCol -	
	// -> Return Value:		
	// -> Remarks:			This member function will return the column width stored
	//						in the registry.
	virtual int GetStoredWidth(int nCol);

	// -> Parameters:		nCol -	
	// -> Return Value:		
	// -> Remarks:			This member function will automatically size a given column.
	virtual void AutoSizeColumn(int nCol=-1);

	// -> Parameters:		nCol -	
	// -> Return Value:		
	// -> Remarks:			This member function will set the column width from the 
	//						registry settings.
	virtual void SetColumnWidth(int nCol);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			This member function loads column widths from the registry.
	virtual void LoadColumnWidths();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			This member function saves column widths to the registry.
	virtual void SaveColumnWidths();

	// -> Parameters:		lpszSection	-	Registry section name, if NULL the default is "Settings".
	//						lpszEntry	-	Registry entry name, if NULL the default is "Column Info".
	//						lpszDefault	-	Registry default value, if NULL the default id.
	// -> Return Value:		
	// -> Remarks:			This member function will initialize the autosave feature. If 
	//						called column widths will be saved to system registry when the 
	//						list control window is destroyed.
	virtual void AutoSaveColumns(LPCTSTR lpszSection=NULL, LPCTSTR lpszEntry=NULL, LPCTSTR lpszDefault=NULL);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Call this member function to subclass the the flat header control.
	virtual bool SubclassHeader(bool bBoldFont=false);

	// -> Parameters:		nCol		-	passed in from control, index of column clicked.
	//						bAscending	-	passed in from control, true if sort order should 
	//										be ascending.
	// -> Return Value:		
	// -> Remarks:			Override this member function in your derived class to peform 
	//						custom sort routines.
	virtual bool SortList(int nCol, bool bAscending );

	// -> Parameters:		dwExStyle	-	
	// -> Return Value:		
	// -> Remarks:			This member function is called to set extended styles for the 
	//						list control ie: LVS_EX_FULLROWSELECT, LVS_EX_GRIDLINES, 
	//						LVS_EX_HEADERDRAGDROP.
	virtual void SetExtendedStyle( DWORD dwExStyle );

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			This member function is called to return the list control 
	//						extended style.
	virtual DWORD GetExtendedStyle();

	// -> Parameters:		bDisable	-	
	// -> Return Value:		
	// -> Remarks:			Call this member function to enable/disable column sizing
	virtual void DisableColumnSizing(bool bDisable);

	// -> Parameters:		nSize	-	
	// -> Return Value:		
	// -> Remarks:			Call this member function to set a minimum column size
	virtual void SetMinimumColSize(int nSize);

	// -> Parameters:		point	-	point to be tested.
	//						col		-	to hold the column index
	// -> Return Value:		the row index or -1 if point is not over a row
	// -> Remarks:			Call this member function to determine the row index and 
	//						column index for a point. returns the row index or -1 if 
	//						point is not over a row.
	virtual int HitTestEx(CPoint &point, int *col) const;

	// -> Parameters:		lpszColHeading	-	the column's heading
	//						nWidth			-	Width of the column, in pixels. If this 
	//											parameter is -1, the column width is the 
	//											same as previous column
	//						nFormat			-	the alignment of the column. Can be LVCFMT_LEFT,
	//											LVCFMT_RIGHT, or LVCFMT_CENTER.
	// -> Return Value:		the index of the new column if successful or -1 otherwise.
	// -> Remarks:			Adds column after the right most column.
	virtual int AddColumn(LPCTSTR lpszColHeading, int nWidth = -1, int nFormat=LVCFMT_LEFT);
	
	// -> Parameters:		nCols			-	number of columns the list control contains
	//						nWidth			-	int array containing the column widths
	//						strColString	-	CString array containing the string for each column
	// -> Return Value:		Returns false if an error occured.
	// -> Remarks:			This member function will build the columns for the list control. 
	virtual bool BuildColumns(int nCols, int* nWidth, CString* strColString );
	
	// -> Parameters:		nCols		-	number of columns the list control contains
	//						nWidth		-	int array containing the column widths
	//						nColString	-	int array containing the  string resource id 
	//										for each column
	// -> Return Value:		Returns false if an error occured.
	// -> Remarks:			This member function will build the columns for the list control.
	virtual bool BuildColumns(int nCols, int* nWidth, int* nColString );

	// -> Parameters:		clrText		-	
	//						clrTextBk	-	
	// -> Return Value:		
	// -> Remarks:			Sets the row text and background colors.
	virtual void SetRowColors(COLORREF clrText, COLORREF clrTextBk);
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Returns the number of columns in the list.
	virtual int GetColumnCount() const;

	// -> Parameters:		nFrom	-	
	//						nTo		-	
	// -> Return Value:		
	// -> Remarks:			Copies a row to a new location.
	virtual bool CopyRow(int nFrom, int nTo);

	// -> Parameters:		nFrom	-	
	//						nTo		-	
	// -> Return Value:		
	// -> Remarks:			Moves a row to a new location.
	virtual bool MoveRow(int nFrom, int nTo);

	//{{AFX_VIRTUAL(CXTListView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	//{{AFX_MSG(CXTListView)
	afx_msg void OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//---------------------------------------------------------------------------
inline int CXTListView::SetSortImage( int nCol, BOOL bAsc )
	{ ASSERT(::IsWindow(m_hWnd)); return m_pHeaderCtrl->SetSortImage(nCol, bAsc); } 
//---------------------------------------------------------------------------
inline DWORD CXTListView::GetExtendedStyle()
	{ ASSERT(::IsWindow(m_hWnd)); return SendMessage(LVM_GETEXTENDEDLISTVIEWSTYLE, 0, 0); }
//---------------------------------------------------------------------------
inline void CXTListView::SetExtendedStyle(DWORD dwExStyle)
	{ ASSERT(::IsWindow(m_hWnd)); SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, GetExtendedStyle()|dwExStyle); }
//---------------------------------------------------------------------------
inline void CXTListView::SetRowColors(COLORREF clrText, COLORREF clrTextBk)
	{ m_clrText = clrText; m_clrTextBk = clrTextBk; }
//---------------------------------------------------------------------------
inline void CXTListView::SetMinimumColSize(int nSize)
	{ m_nMinSize = nSize; }
//---------------------------------------------------------------------------
inline void CXTListView::DisableColumnSizing(bool bDisable)
	{ m_bNoColSizing = bDisable; }
//---------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // #if !defined(__XTLISTVIEW_H__)
