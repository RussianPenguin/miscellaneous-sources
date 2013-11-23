// XTDockContext.h interface for the CXTDockContext class.
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

#if !defined(__XTDOCKCONTEXT_H__)
#define __XTDOCKCONTEXT_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// class forwards
class CXTDockBar;
class CXTDockWindow;

/////////////////////////////////////////////////////////////////////////////
// CXTDockContext is a CDockContext derived class which is used by
// CXTDockWindow and CXTMiniDockFrameWnd for docking / sizing control bars.
/////////////////////////////////////////////////////////////////////////////
class _XT_EXT_CLASS CXTDockContext : public CDockContext
{
public:

	// -> Parameters:		pBar -	
	// -> Return Value:		
	// -> Remarks:			Constructor - handles default initialization.
	CXTDockContext(CControlBar* pBar);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Destructor - handles cleanup and de-allocation.
	virtual ~CXTDockContext();

protected:

    CPoint	m_ptOrig;	// 

public:

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			This member function is called by CXTDockContext 
	//						when a drag operation completes.
	void EndDrag();

	// -> Parameters:		pt -	
	// -> Return Value:		
	// -> Remarks:			This member function is called by CXTDockWindow 
	//						and CXTMiniDockFrameWnd whenever a drag operation 
	//						begins.
	virtual void StartDrag(CPoint pt);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			This member function is called by CXTDockContext to determine
	//						whether a control bar is dockable.
	DWORD CanDock();

	// -> Parameters:		rect		-	
	//						dwDockStyle	-	
	//						ppDockBar	-	
	// -> Return Value:		
	// -> Remarks:			This member function is called by CXTDockContext to determine 
	//						whether a control bar is dockable.
	DWORD CanDock(CRect rect, DWORD dwDockStyle, CDockBar** ppDockBar = NULL);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			This member function is called by CXTDockContext whenever a 
	//						drag operation begins.
	BOOL Track();

	// -> Parameters:		dwOverDockStyle -	
	// -> Return Value:		
	// -> Remarks:			This member function is called by CXTDockContext and returns 
	//						a CXTDock bar pointer.
	CXTDockBar* GetDockBar(DWORD dwOverDockStyle);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			This member function is used to toggle the docked state of 
	//						a control bar.
	virtual void ToggleDocking();

	// -> Parameters:		pt -	
	// -> Return Value:		
	// -> Remarks:			This member function is called to enable diagonal sizing for 
	//						the control bar.
	void Stretch(CPoint pt);

	// -> Parameters:		nHitTest -	
	//						pt		 -	
	// -> Return Value:		
	// -> Remarks:			
	virtual void StartResize(int nHitTest, CPoint pt);

	// -> Parameters:		pt -	
	// -> Return Value:		
	// -> Remarks:			
	void Move(CPoint pt);

	// -> Parameters:		bRemoveRect -	
	// -> Return Value:		
	// -> Remarks:			
	void DrawFocusRect(BOOL bRemoveRect = FALSE);

	// -> Parameters:		nChar -		
	//						bDown -		
	// -> Return Value:		
	// -> Remarks:			
	void OnKey(int nChar, BOOL bDown);

	// -> Parameters:		pFlag		-	
	//						bNewValue	-	
	// -> Return Value:		
	// -> Remarks:			
	void UpdateState(BOOL* pFlag, BOOL bNewValue);

private:

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	void AdjustRectangle(CRect& rect, CPoint pt);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // #if !defined(__XTDOCKCONTEXT_H__)
