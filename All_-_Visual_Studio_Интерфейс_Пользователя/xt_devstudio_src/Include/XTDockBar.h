// XTDockBar.h interface for the CXTDockBar class.
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

#if !defined(__XTDOCKBAR_H__)
#define __XTDOCKBAR_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "XTSplitterDock.h"

// class forwards.
class CXTDockWindow;

/////////////////////////////////////////////////////////////////////////////
// CXTDockBar is a CDockBar derived class used by CXTFrameWnd and CXTMDIFrameWnd
// to offset CXTToolBars to allow 3D borders.
/////////////////////////////////////////////////////////////////////////////
class _XT_EXT_CLASS CXTDockBar : public CDockBar
{
	DECLARE_DYNAMIC(CXTDockBar)

public:

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Constructor - handles default initialization.
	CXTDockBar();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Destructor - handles cleanup and de-allocation.
	virtual ~CXTDockBar();

protected:
	
	int			m_nTrackSplitter;		// Splitter used to drag
	BOOL		m_bTracking;			// TRUE when tracking.
	HWND		m_hWndFocus;			// Previous focus window when tracking
	DWORD		m_dwXTStyle;			// FLAT styles
	BOOL		m_bTopBorder;			// AFX_IDW_DOCKBAR_TOP won't draw a top border line If FALSE, set by CXTSplitterWnd.

	// Array of CXTSplitterDock objects.
	CArray <CXTSplitterDock *, CXTSplitterDock *>	m_arrSplitters;	

public:

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	CXTDockWindow * IsRowMaximized(int nBar);
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	void DockControlBar(CControlBar* pBar, LPCRECT lpRect);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	void Maximize(CXTDockWindow* pMaxBar, BOOL bRecalcLayout = TRUE);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	void Normalize(CXTDockWindow* pMaxBar, BOOL bRecalcLayout = TRUE);

	// -> Parameters:	
	// -> Return Value:		The current CBRS_XT_ (Control bar) settings for the control bar. 
	//						See ModifyXTBarStyle for the complete list of available styles.
	// -> Remarks:			Call this function to determine which CBRS_XT_ (control bar) 
	//						settings are currently set for the control bar. Does not 
	//						handle WS_ (window style) or CBRS_ (control bar style).
	DWORD GetXTBarStyle();

	// -> Parameters:		dwNewStyle	-	New CBRS_XT_ style for the control bar, see 
	//										SetXTBarStyle() for availiable styles.
	// -> Return Value:		
	// -> Remarks:			This member function will set style for the control bar. Does not 
	//						handle WS_ (window style) or CBRS_ (control bar style).
	void SetXTBarStyle(DWORD dwNewStyle);

	//{{AFX_VIRTUAL(CXTDockBar)
	public:
	virtual CSize CalcFixedLayout(BOOL bStretch, BOOL bHorz);
	virtual void HitTest(const CPoint& point);
	virtual void DoPaint(CDC* pDC);
	//}}AFX_VIRTUAL

// Generated message map functions
protected:

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	void DrawBorders(CDC* pDC, CRect& rect);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	void RemoveRowBorders(int nInitPos, DWORD dwBarStyle = CBRS_BORDER_ANY, BOOL bOnlySized = FALSE);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	int SetRowHeight(int nInitPos, int nNewHeight);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	int StretchRowLeft(int nInitPos, int nIncWidth);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	int StretchRowRight(int nInitPos, int nIncWidth);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	int GetRowSizeBars(int nInitPos, CControlBar *pNewBar = NULL);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	int GetRowFixedWidth(int nInitPos, CControlBar *pNewBar = NULL);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	int GetRowMinSizedWidth(int nInitPos, CControlBar *pNewBar = NULL);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	int GetRowSizedWidth(int nInitPos, CControlBar *pNewBar = NULL);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	int GetRowMaxHeight(int nInitPos, CControlBar *pNewBar = NULL);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	int GetRowMinHeight(int nInitPos, CControlBar *pNewBar = NULL);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	int GetAvailableHeight();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	int GetFirstBarInRow(CControlBar *pBar);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	void AdjustRowSizes(int nInitPos);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	void DrawSplitters(CDC *dc);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	void SetSplittersLength(int nStart, int nType, int nLength);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	void DeleteSplitters();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	void AddSplitter(CRect rcSplitter, int nType, BOOL bInterRow, int nPos);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	CControlBar *FindNewBar(int nInitPos);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	void OnCancel();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	//{{AFX_MSG(CXTDockBar)
	afx_msg UINT OnNcHitTest(CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	friend class CXTSplitterWnd;
	friend class CXTSplitterDock;
	friend class CXTSplitterRowDock;
	friend class CXTMiniDockFrameWnd;
};

//---------------------------------------------------------------------------
inline void CXTDockBar::SetXTBarStyle(DWORD dwNewStyle)
	{ m_dwXTStyle = dwNewStyle; }
//---------------------------------------------------------------------------
inline DWORD CXTDockBar::GetXTBarStyle()
{	ASSERT(::IsWindow(m_hWnd));	return m_dwXTStyle;}
//---------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // #if !defined(__XTDOCKBAR_H__)

