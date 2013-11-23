// XTCoolMenu.h : interface for the CXTCoolMenu class.
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

#if !defined(__XTCOOLMENU_H__)
#define __XTCOOLMENU_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "XTWndHook.h"

/////////////////////////////////////////////////////////////////////////////
// CXTCoolMenu class
/////////////////////////////////////////////////////////////////////////////
class _XT_EXT_CLASS CXTCoolMenu : public CXTWndHook
{
	DECLARE_DYNAMIC(CXTCoolMenu)

public:
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Constructor - handles default initialization.
	CXTCoolMenu();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Destructor - handles cleanup and de-allocation.
	virtual ~CXTCoolMenu();

protected:

	CImageList		m_imageList;	// image list for all buttons
	CMapWordToPtr	m_imageMap;		// maps command ID -> image list index
	BOOL			m_bHasButtons;	// use to control whether buttons are shown
	CFrameWnd*		m_pFrame;		// frame window I belong to
	CUIntArray		m_arToolbarID;	// array of toolbar IDs loaded
	CPtrList		m_menuList;		// list of HMENU's initialized
	CSize			m_sizeBmp;		// size of button bitmap
	CSize			m_sizeBtn;		// size of button (including shadow)

public:

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	CImageList& GetImageList();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	CMapWordToPtr& GetImageMap();

	// -> Parameters:		nID	-	
	// -> Return Value:		
	// -> Remarks:			Get button index for given command ID, or -1 if not found
	int GetButtonIndex(WORD nID);

	// -> Parameters:		pFrame -	CFrameWnd object that represents the applications
	//									main window, if NULL this will uninstall the cool
	//									menus.
	// -> Return Value:		
	// -> Remarks:			This member function is called to install cool
	//						menus for application.
	virtual void Install(CFrameWnd* pFrame);

	// -> Parameters:		nToolbarID -	The resource ID of a toolbar to extract images
	//										from to be displayed in cool menus.
	//										
	// -> Return Value:		
	// -> Remarks:			This member function will load a toolbar resource and extract
	//						each button image to be used with its associated menu command.
	virtual BOOL LoadToolbar(UINT nToolbarID);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Load multiple toolbars
	virtual BOOL LoadToolbars(const UINT* nToolbarIDs, int nSize);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual BOOL AddSingleBitmap(UINT nBitmapID, UINT* nCmdIDs, int nSize);

protected:

	// -> Parameters:		dc		-	
	//						rc		-	
	//						text	-	
	//						color	-	
	// -> Return Value:		
	// -> Remarks:			
	virtual void DrawMenuText(CDC* pDC, CRect rect, CString strText, COLORREF clrColor);

	// -> Parameters:		dc			-	
	//						rc			-	
	//						bSelected	-	
	//						hbmCheck	-	
	// -> Return Value:		
	// -> Remarks:			
	virtual BOOL Draw3DCheckmark(CDC* pDC, const CRect& rect, BOOL bSelected, HBITMAP hbmCheck);

	// -> Parameters:		pMenu			-	
	//						nIndex			-	
	//						bSysMenu		-	
	//						bHasButtons	-	
	// -> Return Value:		
	// -> Remarks:			
	virtual void ConvertMenu(CMenu* pMenu, UINT nIndex, BOOL bSysMenu, BOOL bHasButtons);

	// -> Parameters:		pDC			-	Current device context.
	//						rcItem		-	Initial size for chevron.
	//						bSelected	-	Selected state, TRUE if mouse hovering.
	// -> Return Value:		
	// -> Remarks:			This member function is called to draw a chevron for Office
	//						2000 style menus.
	virtual void DrawChevron(CDC* pDC, CRect rcItem, BOOL bSelected);

	//{{AFX_VIRTUAL(CXTCoolMenu)
	virtual void Destroy();
	virtual void Refresh();
	virtual void OnInitMenuPopup(CMenu* pMenu, UINT nIndex, BOOL bSysMenu);
	virtual BOOL OnMeasureItem(LPMEASUREITEMSTRUCT lpms);
	virtual BOOL OnDrawItem(LPDRAWITEMSTRUCT lpds);
	virtual LONG OnMenuChar(UINT nChar, UINT nFlags, CMenu* pMenu);
	virtual void OnMenuSelect(UINT nItemID, UINT nFlags, HMENU hSysMenu);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL
};

//---------------------------------------------------------------------------
inline CImageList& CXTCoolMenu::GetImageList()
	{ ASSERT(::IsWindow(m_hWnd)); return m_imageList; }
//---------------------------------------------------------------------------
inline CMapWordToPtr& CXTCoolMenu::GetImageMap()
	{ ASSERT(::IsWindow(m_hWnd)); return m_imageMap; }
//---------------------------------------------------------------------------
inline int CXTCoolMenu::GetButtonIndex(WORD nID)
	{ void* val; return m_imageMap.Lookup(nID, val) ? (int)val : -1; }
//---------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // #if !defined(__XTCOOLMENU_H__)

