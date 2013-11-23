// XTReBar.h interface for the CXTReBar class.
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

#if !defined(__XTREBAR_H__)
#define __XTREBAR_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "XTControlBar.h"

// class forwards
class CXTReBarCtrl;

/////////////////////////////////////////////////////////////////////////////
// A CXTReBar object is a control bar that provides layout, persistence, and state 
// information for rebar controls.
/////////////////////////////////////////////////////////////////////////////
class _XT_EXT_CLASS CXTReBar : public CXTControlBar
{
	DECLARE_DYNAMIC(CXTReBar)

public:

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Constructor - handles default initialization
	CXTReBar();

	// -> Parameters:		pParentWnd	-	
	//						dwCtrlStyle	-	
	//						dwStyle		-	
	//						nID			-	
	// -> Return Value:		
	// -> Remarks:			
	BOOL Create(CWnd* pParentWnd, DWORD dwCtrlStyle = RBS_BANDBORDERS,
		DWORD dwStyle = WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_TOP,
		UINT nID = AFX_IDW_REBAR);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			For direct access to the underlying common control.
	CXTReBarCtrl& GetReBarCtrl() const;

	// -> Parameters:		pBar	-	
	//						pszText	-	
	//						pbmp	-	
	//						dwStyle	-	
	// -> Return Value:		
	// -> Remarks:			
	BOOL AddBar(CWnd* pBar, LPCTSTR pszText = NULL, CBitmap* pbmp = NULL,
		DWORD dwStyle = RBBS_GRIPPERALWAYS | RBBS_FIXEDBMP, UINT wID=0);

	// -> Parameters:		pBar	-	
	//						clrFore	-	
	//						clrBack	-	
	//						pszText	-	
	//						dwStyle	-	
	// -> Return Value:		
	// -> Remarks:			
	BOOL AddBar(CWnd* pBar, COLORREF clrFore, COLORREF clrBack,
		LPCTSTR pszText = NULL, DWORD dwStyle = RBBS_GRIPPERALWAYS, UINT wID=0);

	// -> Parameters:		pBar	-	
	//						pRBBI	-	
	// -> Return Value:		
	// -> Remarks:			
	BOOL AddBar(CWnd* pBar, REBARBANDINFO* pRBBI);

	// -> Parameters:		pTarget				-	
	//						bDisableIfNoHndler	-	
	// -> Return Value:		
	// -> Remarks:			
	virtual void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);

	// -> Parameters:		point	-	
	//						pTI		-	
	// -> Return Value:		
	// -> Remarks:			
	virtual int OnToolHitTest(CPoint point, TOOLINFO* pTI) const;

	// -> Parameters:		bStretch	-	
	//						bHorz		-	
	// -> Return Value:		
	// -> Remarks:			
	virtual CSize CalcFixedLayout(BOOL bStretch, BOOL bHorz);

	// -> Parameters:		nLength	-	
	//						nMode	-	
	// -> Return Value:		
	// -> Remarks:			
	virtual CSize CalcDynamicLayout(int nLength, DWORD nMode);

	// -> Parameters:		lpszSection	-	
	// -> Return Value:		
	// -> Remarks:			
	void SaveState(LPCTSTR lpszSection);
	
	// -> Parameters:		lpszSection	-	
	// -> Return Value:		
	// -> Remarks:			
	void LoadState(LPCTSTR lpszSection);

protected:

	// -> Parameters:		message	-	
	//						wParam	-	
	//						lParam	-	
	// -> Return Value:		
	// -> Remarks:			
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);

	//{{AFX_MSG(CXTReBar)
	afx_msg BOOL OnNcCreate(LPCREATESTRUCT);
	afx_msg void OnPaint();
	afx_msg void OnHeightChange(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNcPaint();
	afx_msg void OnNcCalcSize(BOOL, NCCALCSIZE_PARAMS*);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg LRESULT OnShowBand(WPARAM wParam, LPARAM lParam);
	afx_msg void OnRecalcParent();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//---------------------------------------------------------------------------
inline CXTReBarCtrl& CXTReBar::GetReBarCtrl() const
	{ return *(CXTReBarCtrl*)this; }
//---------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // #if !defined(__XTREBAR_H__)
