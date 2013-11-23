// XTFlatHeaderCtrl.h interface for the CXTFlatHeaderCtrl class.
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

#if !defined(__XTFLATHEADERCTRL_H__)
#define __XTFLATHEADERCTRL_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "XTCoolMenu.h"

/////////////////////////////////////////////////////////////////////////////
// CXTFlatHeaderCtrl is a CHeaderCtrl derived class which is simular
// to the listbox flat header controls seen in Visual Studio and Outlook.
/////////////////////////////////////////////////////////////////////////////
class _XT_EXT_CLASS CXTFlatHeaderCtrl : public CHeaderCtrl
{
	DECLARE_DYNAMIC(CXTFlatHeaderCtrl)

public:

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Constructor - handles default initialization
	CXTFlatHeaderCtrl();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Destructor - handles clean up.
	virtual ~CXTFlatHeaderCtrl();

protected:

	UINT		m_popupMenuID;	// popup menu resource id
	int			m_nPos;			// index of the pop-up menu contained in the menu
	int			m_nOffset;		// ammount to offset the sort arrow.
	int			m_nSortCol;		// last column pressed during sort.
	CWnd*		m_pParentWnd;	// holds a pointer to the parent window.
	CRect		m_rcOldSize;	// 
	BOOL		m_bLBtnDown;	// true if left mouse button is pressed
	BOOL		m_bSortAsc;		// used when column is pressed to draw sort arrow.

public:

	// -> Parameters:		popupMenuID		-	
	//						nPos			-	
	// -> Return Value:		
	// -> Remarks:			This member function is called to associate a menu and toolbar 
	//						resource with the context menu.
	virtual void SetMenuID(UINT popupMenuID, int nPos=0);

	// -> Parameters:		bBoldFont	-	
	// -> Return Value:		
	// -> Remarks:			This member function must be called after creation to initialize 
	//						the font the header will use.
	virtual void InitializeHeader(bool bBoldFont);

	// -> Parameters:		bBoldFont	-	
	// -> Return Value:		
	// -> Remarks:			This member function can be used to toggle the font from bold to normal.
	virtual void SetFontBold(BOOL bBoldFont = TRUE);
	
	// -> Parameters:		nCol -	Zero-based index of the column to set the sort image for.
	//						bAsc -	TRUE if ascending, otherwise FALSE.
	// -> Return Value:		Zero-based index of the previously sorted column.
	// -> Remarks:			This member function will set the sort image for the
	//						specified column.
	virtual int SetSortImage( int nCol, BOOL bAsc );

protected:

	// -> Parameters:		pDC	 -	
	//						rect -	
	// -> Return Value:		
	// -> Remarks:			This member function is called by the header during paint operations.
	virtual void DrawBorders(CDC* pDC, CRect& rect);

#ifdef _VC_VERSION_5
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			This member function was added for vc5 support. It returns 
	//						the number of columns currently in the header.
	virtual int GetItemCount() const;

	// -> Parameters:		piArray	-	
	//						iCount	-	
	// -> Return Value:		
	// -> Remarks:			
	virtual BOOL GetOrderArray(LPINT piArray, int iCount=-1);
#endif

	//{{AFX_VIRTUAL(CXTFlatHeaderCtrl)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CXTFlatHeaderCtrl)
	afx_msg void OnPaint();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnWindowPosChanged(WINDOWPOS FAR* lpwndpos);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

//---------------------------------------------------------------------------
inline void CXTFlatHeaderCtrl::SetFontBold(BOOL bBoldFont)
	{ ASSERT(::IsWindow(m_hWnd)); SetFont(&xtAfxData.fontBold); }
//---------------------------------------------------------------------------
#ifdef _VC_VERSION_5
inline int CXTFlatHeaderCtrl::GetItemCount() const
	{ ASSERT(::IsWindow(m_hWnd)); return (int) ::SendMessage(m_hWnd, HDM_GETITEMCOUNT, 0, 0L); }
#endif
//---------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // #if !defined(__XTFLATHEADERCTRL_H__)
