// XTMiniDockFrameWnd.h interface for the CXTMiniDockFrameWnd class.
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

#if !defined(__XTMINIDOCKFRAMEWND_H__)
#define __XTMINIDOCKFRAMEWND_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CXTMiniDockFrameWnd is a CMiniDockFrameWnd class which is used to
// handle docking for the CXTDockWindow class.
/////////////////////////////////////////////////////////////////////////////
class _XT_EXT_CLASS CXTMiniDockFrameWnd : public CMiniDockFrameWnd
{
	DECLARE_DYNCREATE(CXTMiniDockFrameWnd)

public:

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Constructor - handles default initialization
	CXTMiniDockFrameWnd();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Destructor - handles clean up.
	virtual ~CXTMiniDockFrameWnd();

protected:

	//{{AFX_VIRTUAL(CXTMiniDockFrameWnd)
	public:
	virtual BOOL Create(CWnd* pParent, DWORD dwBarStyle);
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CXTMiniDockFrameWnd)
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	afx_msg void OnNcLButtonDblClk(UINT nHitTest, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	friend class CDockBar;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // #if !defined(__XTMINIDOCKFRAMEWND_H__)

