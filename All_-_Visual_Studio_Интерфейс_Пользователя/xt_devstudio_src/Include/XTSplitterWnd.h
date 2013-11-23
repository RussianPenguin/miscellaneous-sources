// XTSplitterWnd.h interface for the CXTSplitterWnd class.
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

#if !defined(__XTSPLITTERWND_H__)
#define __XTSPLITTERWND_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CXTSplitterWnd is a CSplitterWnd derived class which adds the ability
// to hide and show splitter panes, based upon its index, and 
// to draw flat splitter windows simular to Oultook.
/////////////////////////////////////////////////////////////////////////////
class _XT_EXT_CLASS CXTSplitterWnd : public CSplitterWnd
{
	DECLARE_DYNAMIC(CXTSplitterWnd)

public:
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Constructor - handles default initialization.
	CXTSplitterWnd();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Destructor - handles cleanup and de-allocation.
	virtual ~CXTSplitterWnd();

protected:

	int		m_nHiddenCol;		// Index of the hidden column.
	int		m_nHiddenRow;		// Index of the hidden row.
	int		m_cyBorderGap;		// Ammount in pixels to offset the splitter from the top edge.
	BOOL	m_bFlatSplitter;	// TRUE if the SPLS_FLATEDGE style was used during creation.
	BOOL	m_bTopBorder;		// TRUE	if the splitter is the top level splitter.
	BOOL	m_bDrawEdge;		// TRUE to draw a white edge along the top border.

public:

	// -> Parameters:		bDrawEdge	-	If TRUE a white edge will be drawn along the top.
	//						cyBorderGap -	Amount in pixels to offset splitter edge.
	// -> Return Value:		
	// -> Remarks:			Call this member function to show a top border for the splitter
	//						window, simular to Outlook. Note that children should have the
	//						WS_EX_STATICEDGE style set, and m_bFlatSplitter should be set to
	//						TRUE for best results.
	void ShowTopBorder(BOOL bDrawEdge=TRUE, int cyBorderGap=5);

	// -> Parameters:		bDisable	-	
	// -> Return Value:		
	// -> Remarks:			Call this member function to enable or disable flat splitters.
	virtual void EnableFlatLook(BOOL bDisable=TRUE);

	// -> Parameters:		nRow		-	
	//						nCol		-	
	//						pNewView	-	
	// -> Return Value:		
	// -> Remarks:			This member function is called to switch, or swap a splitter 
	//						view with another.
	virtual BOOL SwitchView(int nRow, int nCol, CView *pNewView);

	// -> Parameters:		nRow		-	
	//						nCol		-	
	//						pViewClass	-	
	// -> Return Value:		
	// -> Remarks:			This member function is called to replace an existing splitter
	//						view with another.
	virtual BOOL ReplaceView(int nRow, int nCol, CRuntimeClass *pViewClass);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			This member function is called to show the column that was 
	//						previously hidden.
	virtual void ShowColumn();

	// -> Parameters:		nColHide	-	
	// -> Return Value:		
	// -> Remarks:			This member function will hide a column based upon its index.
	virtual void HideColumn(int nColHide);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			This member function is called to show the row that was 
	//						previously hidden.
	virtual void ShowRow();

	// -> Parameters:		nRowHide	-	
	// -> Return Value:		
	// -> Remarks:			This member function will hide a row based upon its index.
	virtual void HideRow(int nRowHide);

	//{{AFX_VIRTUAL(CXTSplitterWnd)
	public:
	virtual void OnDrawSplitter(CDC* pDC, ESplitType nType, const CRect& rect);
	virtual void RecalcLayout();
	virtual void GetInsideRect(CRect& rect) const;
	virtual void OnInvertTracker(const CRect& rect);
	//}}AFX_VIRTUAL

protected:

	//{{AFX_MSG(CXTSplitterWnd)
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// -> Parameters:		pInfoArray	  -	
	//						nMax		  -	
	//						nSize		  -	
	//						nSizeSplitter -	
	// -> Return Value:		
	// -> Remarks:			
	void LayoutRowCol(CRowColInfo* pInfoArray, int nMax, int nSize, int nSizeSplitter);

	// -> Parameters:		lpLayout   -	
	//						pWnd	   -	
	//						x 		   -	
	//						y 		   -	
	//						cx		   -	
	//						cy		   -	
	//						bScrollBar -	
	//						bTopBorder -	
	// -> Return Value:		
	// -> Remarks:			
	void DeferClientPos(AFX_SIZEPARENTPARAMS* lpLayout, CWnd* pWnd, int x, int y, int cx, int cy, BOOL bScrollBar, BOOL bTopBorder);
};

//---------------------------------------------------------------------------
inline void CXTSplitterWnd::EnableFlatLook(BOOL bEnable)
	{ m_bFlatSplitter = bEnable; }
//---------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // #if !defined(__XTSPLITTERWND_H__)
