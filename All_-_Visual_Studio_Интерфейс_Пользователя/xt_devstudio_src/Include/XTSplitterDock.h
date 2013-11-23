// XTSplitterRowDock.h interface for the CXTSplitterRowDock class.
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

#if !defined(__XTSPLITTERDOCK_H__)
#define __XTSPLITTERDOCK_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// class forwards.
class CXTDockBar;

/////////////////////////////////////////////////////////////////////////////
// CXTSplitterDock
/////////////////////////////////////////////////////////////////////////////
class CXTSplitterDock
{
public:

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	CXTSplitterDock(CXTDockBar *pBar, const CRect &rcCurrent,const int nType, const int nPos);
	
	// current size and position
	CRect		m_rcCurrent;
	CRect		m_rcTrack;
	CPoint		m_ptCurrent;
	
	// widths of the row
	int			m_nStartHeight;
	int			m_nCurrentHeight;
	int			m_nMaxHeight;
	int			m_nMinHeight;

	// vertical or horizontal
	int			m_nType;
	int			m_nControlBar;
	CXTDockBar*	m_pDockBar;

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual void Move(CPoint point);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual void StartTrack(CPoint point);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual void EndTrack(CPoint point);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	BOOL IsHorz();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	BOOL HitTest(const CPoint &point);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	void SetLength(int nLength);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	void OnInvertTracker();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	void Draw(CDC *pDC);
	
protected:

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual void SetNewHeight();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual void CalcMaxMinHeight();
};

/////////////////////////////////////////////////////////////////////////////
// CXTSplitterRowDock
/////////////////////////////////////////////////////////////////////////////
class _XT_EXT_CLASS CXTSplitterRowDock : public CXTSplitterDock  
{
public:

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	CXTSplitterRowDock(CXTDockBar *pBar, const CRect &rcCurrent,const int nType, const int nPos);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual void Move(CPoint point);

protected:

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual void SetNewHeight();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual void CalcMaxMinHeight();
};

//---------------------------------------------------------------------------
inline BOOL CXTSplitterDock::IsHorz()
	{ return (m_nType == XT_SPLITTER_HORZ); }
//---------------------------------------------------------------------------
inline BOOL CXTSplitterDock::HitTest(const CPoint &point)
	{ return m_rcCurrent.PtInRect(point); }
//---------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // #if !defined(__XTSPLITTERDOCK_H__)
