// XTStatusBarPaneControlInfo.h interface for the CXTStatusBarPaneControlInfo class.
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
// Used with permission Copyright © 1999 Pierre MELLINAND
//
//////////////////////////////////////////////////////////////////////

#if !defined(__XTSTATUSBAR_H__)
#define __XTSTATUSBAR_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CXTStatusBarPaneControlInfo class
/////////////////////////////////////////////////////////////////////////////
class _XT_EXT_CLASS CXTStatusBarPaneControlInfo : public CObject
{
	DECLARE_DYNCREATE(CXTStatusBarPaneControlInfo)

public:

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Constructor - handles default initialization
	CXTStatusBarPaneControlInfo();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Destructor - handles clean up.
	virtual ~CXTStatusBarPaneControlInfo();

public:

	CWnd*	m_pWnd;			// 
	int		m_nPaneID;		// 
	BOOL	m_bAutodelete;	// 
};

/////////////////////////////////////////////////////////////////////////////
// CXTStatusBarPane class
/////////////////////////////////////////////////////////////////////////////
class _XT_EXT_CLASS CXTStatusBarPane : public CObject
{

public:

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Constructor - handles default initialization
	CXTStatusBarPane();

	// -> Parameters:		rPane	-	
	// -> Return Value:		
	// -> Remarks:			Constructor - handles default initialization
	CXTStatusBarPane (CXTStatusBarPane& rPane);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Destructor - handles clean up.
	virtual ~CXTStatusBarPane();


public:

	UINT	m_nID;		// 
	int		m_cxText;	// 
	UINT	m_nStyle;	// 
	UINT	m_nFlags;	// 
	CString m_strText;	// 

public:

	// -> Parameters:		rPane	-	
	// -> Return Value:		
	// -> Remarks:			
	CXTStatusBarPane& operator=(CXTStatusBarPane& rPane);
};

/////////////////////////////////////////////////////////////////////////////
// CXTStatusBar class
/////////////////////////////////////////////////////////////////////////////
class _XT_EXT_CLASS CXTStatusBar : public CStatusBar
{
	DECLARE_DYNCREATE(CXTStatusBar)

public:

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Constructor - handles default initialization
	CXTStatusBar();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Destructor - handles clean up.
	virtual ~CXTStatusBar();

private:

	CArray<CXTStatusBarPaneControlInfo*, CXTStatusBarPaneControlInfo*>	m_aPans;

public:

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual void PositionControls();

	// -> Parameters:		nPaneID	-	
	// -> Return Value:		
	// -> Remarks:			
	virtual CXTStatusBarPaneControlInfo* GetPanControl(int nPaneID);

	// -> Parameters:		pWnd				-	
	//						nPaneID				-	
	//						bAutodeleteControl	-	
	// -> Return Value:		
	// -> Remarks:			
	virtual BOOL AddControl(CWnd * pWnd, int nPaneID, BOOL bAutodeleteControl = TRUE );

	// -> Parameters:		index	-	
	//						cxWidth	-	
	// -> Return Value:		
	// -> Remarks:			
	virtual void SetPaneWidth(int index, int cxWidth);

	// -> Parameters:		position	-	
	//						paneID		-	
	// -> Return Value:		
	// -> Remarks:			
	virtual BOOL AddIndicator( int position, UINT paneID);

	// -> Parameters:		nIndex	-	
	//						xfxpane	-	
	// -> Return Value:		
	// -> Remarks:			
	virtual BOOL GetStatusPane(int nIndex, CXTStatusBarPane & xfxpane);

	// -> Parameters:		nPaneID	-	
	// -> Return Value:		
	// -> Remarks:			
	virtual void RemovePane(int nPaneID);

	//{{AFX_VIRTUAL(CXTStatusBar)
	//}}AFX_VIRTUAL

protected:

	//{{AFX_MSG(CXTStatusBar)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // #if !defined(__XTSTATUSBAR_H__)

