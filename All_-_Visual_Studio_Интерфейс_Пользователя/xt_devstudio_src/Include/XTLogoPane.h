// XTLogoPane.h interface for the CXTLogoPane class.
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

#if !defined(__XTLOGOPANE_H__)
#define __XTLOGOPANE_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CXTLogoPane class
/////////////////////////////////////////////////////////////////////////////
class _XT_EXT_CLASS CXTLogoPane : public CWnd
{
	DECLARE_DYNCREATE(CXTLogoPane)

public:
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Constructor - handles default initialization.
	CXTLogoPane();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Destructor - handles cleanup and de-allocation.
	virtual ~CXTLogoPane();

protected:

	CString m_strLogoText;	// 
	CFont 	m_Font;			// 
	CSize	m_sizeText;		//

public:

	// -> Parameters:		lpszLogoText	-	
	// -> Return Value:		
	// -> Remarks:			
	virtual void SetLogoText(LPCTSTR lpszLogoText);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual CString GetLogoText();

	// -> Parameters:		lpszFontName	-	
	//						nHeight			-	
	//						nWeight			-	
	//						bItalic			-	
	//						bUnderline		-	
	// -> Return Value:		
	// -> Remarks:			
	virtual void SetLogoFont(LPCTSTR lpszFontName, int nHeight=24, int nWeight=FW_BOLD, BOOL bItalic=TRUE, BOOL bUnderline=FALSE);
	
	// -> Parameters:		logFont	-	
	// -> Return Value:		
	// -> Remarks:			
	virtual void SetLogoFont(LOGFONT& logFont);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	CSize GetTextSize();
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	void SetTextSize();

	//{{AFX_VIRTUAL(CXTLogoPane)
	public:
	virtual BOOL Create(LPCTSTR lpszWindowName, CWnd* pParentWnd, DWORD dwStyle=WS_CHILD|WS_VISIBLE, UINT nID=0xffff);
	//}}AFX_VIRTUAL

protected:

	//{{AFX_MSG(CXTLogoPane)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//---------------------------------------------------------------------------
inline CSize CXTLogoPane::GetTextSize()
	{ SetTextSize(); return m_sizeText; }
//---------------------------------------------------------------------------
inline void CXTLogoPane::SetLogoText(LPCTSTR lpszLogoText)
	{ m_strLogoText = lpszLogoText; }
//---------------------------------------------------------------------------
inline CString CXTLogoPane::GetLogoText()
	{ return m_strLogoText; }
//---------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // #if !defined(__XTLOGOPANE_H__)

