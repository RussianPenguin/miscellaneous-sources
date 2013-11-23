// XTTipWindow.h interface for the CXTTipWindow class.
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

#if !defined(__XTTIPWINDOW_H__)
#define __XTTIPWINDOW_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CXTTipWindow window
/////////////////////////////////////////////////////////////////////////////
class _XT_EXT_CLASS CXTTipWindow : public CWnd
{

public:
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Constructor - handles default initialization
	CXTTipWindow();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Destructor - handles clean up.
	virtual ~CXTTipWindow();

protected:

	CRect		m_rcTip;		// Initial size of the tip window.
	CRect		m_rcShadow;		// Initial size of the tip window shadow.
	CWnd*		m_pParentWnd;	// Parent window.
	COLORREF	m_crBackColor;	// Background color for tip window.
	COLORREF	m_crTextColor;	// Text color for the tip window.
	CString		m_strTitle;		// Title text for the tip window.
	CString		m_strDescrip;	// Description text for the tip window.
	UINT		m_nElapse;		// Time out value.
	UINT		m_nEventID;		// Timer event ID.
	DWORD		m_dwTipStyle;	// Initial style for the tip window, see ShowTipWindow(..).
	int			m_nLineSpace;	// Ammount in pixels to space the title and description text.
	CSize		m_sizeOffset;	// Ammount in pixels to offset the shadow rect form the tip window.
	CSize		m_sizeMargin;	// Ammount in pixels of the tip and side margins to where the tip text is displayed.

public:

	// -> Parameters:		nElapse -	Specifies the time-out value, in milliseconds to when the
	//									tip window should close.
	// -> Return Value:		
	// -> Remarks:			This member function will set the initial time-out value for when
	//						to close the tip window.
	void SetTimeout(UINT nElapse);

	// -> Parameters:		lpszTitle	-	A NULL terminated string that is to be displayed as
	//										the title for the tip window.
	//						lpszDescrip	-	A NULL terminated string that is to be displayed as
	//										the description text for the tip window.
	//						bRedraw		-	If true the tip window will be redrawn.
	// -> Return Value:		
	// -> Remarks:			This member function will set the text for the title and description
	//						values that are displayed in the tip window.
	void SetTipText(LPCTSTR lpszTitle, LPCTSTR lpszDescrip, BOOL bRedraw=FALSE);

	// -> Parameters:		crBackColor	-	The color value for the background of the tip window.
	//						crTextColor	-	The color value for the text of the tip window.
	//						bRedraw		-	If true the tip window will be redrawn.
	// -> Return Value:		
	// -> Remarks:			This member function will set the text and background colors for
	//						the tip window display.
	void SetTipColors(COLORREF crBackColor, COLORREF crTextColor, BOOL bRedraw=FALSE);

	// -> Parameters:		point		-	The initial xy coordinates where the tip window is
	//										to be displayed.
	//						pParentWnd	-	Points the the parent window of the tip window.
	//						dwTipStyle	-	Initial style for the tip window. The desired styles 
	//										for the tip widnow can be one or more of the
	//										following:
	//
	//										TWS_XT_THICKBORDER	-	This style will cause the tip
	//																window to display a thick
	//																border around it's edges.
	//										TWS_XT_DROPSHADOW	-	This style will cause the tip
	//																window to cast a shadow on the
	//																parent window.
	//
	//               		nElapse		-	Specifies the time-out value, in milliseconds to when
	//										the tip window should close.
	// -> Return Value:		TRUE if the tip window was successfully created; otherwise FALSE.
	// -> Remarks:			This member function will display a tip window to display a title
	//						and description text.
	virtual BOOL ShowTipWindow(const CPoint& point, CWnd* pParentWnd, DWORD dwTipStyle=TWS_XT_THICKBORDER|TWS_XT_DROPSHADOW, UINT nElapse=5000);

	// -> Parameters:		size	-	Initial size for the horizontal and vertical text margins.
	// -> Return Value:		
	// -> Remarks:			This member function will set the text margins for the tip window.
	void SetMargins(CSize size);

	// -> Parameters:		nLineSpace	-	Initial size for text line spacing.
	// -> Return Value:		
	// -> Remarks:			This member function will set the line spacing for the tip window.
	void SetLineSpace(int nLineSpace);

	// -> Parameters:		size	-	Initial size to offset the shadow from the tip window.
	// -> Return Value:		
	// -> Remarks:			This member function will set the shadow offset for the tip window.
	void SetShadowOffset(CSize size);

protected:

	// -> Parameters:		pDC		-	Device context of the window to cast the shadow on.
	//						rect	-	Initial size of the shadow.
	// -> Return Value:		
	// -> Remarks:			This member function will draw a shadow rect to the device context
	//						specified by pDC.
	void DrawShadowRect(CDC *pDC, const CRect& rect);

	// -> Parameters:		point	-	The xy coordinates of where the tip window is to be
	//									displayed.
	// -> Return Value:		
	// -> Remarks:			This member function will set the sizes for the tip window.
	void InitializeSize(const CPoint& point);

	//{{AFX_VIRTUAL(CXTTipWindow)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CXTTipWindow)
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

//---------------------------------------------------------------------------
inline void CXTTipWindow::SetTimeout(UINT nElapse)
	{ m_nElapse = nElapse; }
//---------------------------------------------------------------------------
inline void CXTTipWindow::SetTipText(LPCTSTR lpszTitle, LPCTSTR lpszDescrip, BOOL bRedraw)
	{ m_strTitle = lpszTitle; m_strDescrip = lpszDescrip; if (bRedraw) { InvalidateRect(NULL); }}
//---------------------------------------------------------------------------
inline void CXTTipWindow::SetTipColors(COLORREF crBackColor, COLORREF crTextColor, BOOL bRedraw)
	{ m_crBackColor = crBackColor; m_crTextColor = crTextColor; if (bRedraw) { InvalidateRect(NULL); }}
//---------------------------------------------------------------------------
inline void CXTTipWindow::SetMargins(CSize size)
	{ m_sizeMargin.cx = max(3, size.cx); m_sizeMargin.cy = max(3, size.cy); }
//---------------------------------------------------------------------------
inline void CXTTipWindow::SetLineSpace(int nLineSpace)
	{ m_nLineSpace = max(2, nLineSpace); }
//---------------------------------------------------------------------------
inline void CXTTipWindow::SetShadowOffset(CSize size)
	{ m_sizeOffset = size; }
//---------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // #if !defined(__XTTIPWINDOW_H__)
