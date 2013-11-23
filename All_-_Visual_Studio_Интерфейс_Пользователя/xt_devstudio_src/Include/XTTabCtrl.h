// XTTabCtrl.h interface for the CXTTabCtrl class.
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

#if !defined(__XTTABCTRL_H__)
#define __XTTABCTRL_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CXTTabCtrl is a CTabCtrl derived class which is used by CXTTabCtrl
// to help fix problems with repainting in the tab control
/////////////////////////////////////////////////////////////////////////////
class _XT_EXT_CLASS CXTTabCtrl : public CTabCtrl
{
	DECLARE_DYNAMIC(CXTTabCtrl)

public:
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Constructor - handles default initialization.
	CXTTabCtrl();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Destructor - handles cleanup and de-allocation.
	virtual ~CXTTabCtrl();

protected:

	UINT	m_popupMenuID;	// popup menu resource id
	int		m_nPos;			// index of the pop-up menu contained in the menu

public:

	// -> Parameters:		popupMenuID		-	
	//						nPos			-	
	// -> Return Value:		
	// -> Remarks:			This member function is called to associate a menu and toolbar 
	//						resource with the context menu.
	virtual void SetMenuID(UINT popupMenuID, int nPos=0);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			This member function returns the menu resource associated with 
	//						the tab control.
	virtual UINT GetMenuID();

	//{{AFX_VIRTUAL(CXTTabCtrl)
	public:
	virtual BOOL Create(CWnd* pParentWnd, UINT nID=AFX_IDC_TAB_CONTROL, DWORD dwStyle=WS_VISIBLE|WS_CHILD|TCS_BOTTOM|TCS_TOOLTIPS|WS_CLIPSIBLINGS|WS_CLIPCHILDREN, const CRect& rect=CRect(0,0,0,0));
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CXTTabCtrl)
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//---------------------------------------------------------------------------
inline UINT CXTTabCtrl::GetMenuID()
	{ ASSERT(::IsWindow(m_hWnd)); return m_popupMenuID; }
//---------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // #if !defined(__XTTABCTRL_H__)

