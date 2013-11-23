// XTHyperLink.h interface for the CXTHyperLink class.
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

#if !defined(__XTHYPERLINK_H__)
#define __XTHYPERLINK_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CXTHyperLink window
/////////////////////////////////////////////////////////////////////////////
class _XT_EXT_CLASS CXTHyperLink : public CStatic
{
	DECLARE_DYNAMIC(CXTHyperLink)

public:

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Constructor - handles default initialization.
	CXTHyperLink();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Destructor - handles cleanup and de-allocation.
	virtual ~CXTHyperLink();

// Attributes
protected:

	bool			m_bUnderline;	// Set to true for underlined text.
	bool			m_bMouseOver;	// Set to true when the cursor is hovering over the control.
	bool			m_bVisited;		// Set to true when the hyperlink has been activated.
	CString			m_strLink;		// String object that represents the URL for this control.
	HCURSOR			m_hcurHand;		// Handle to the default cursor for this control. 
	COLORREF		m_clrLink;		// RGB color value for the hyperlink text color.
	COLORREF		m_clrHover;		// RGB color value for the hyperlink text color when the mouse is hovering.
	COLORREF		m_clrVisited;	// RGB color value for the hyperlink text color when the URL has been visited.
	CToolTipCtrl	m_toolTip;		// Tooltip to be displayted for the control.

// Operations
public:

	// -> Parameters:		lpszLink -	A NULL terminated character string that
	//									represents the URL for the hyperlink.
	// -> Return Value:		
	// -> Remarks:			This member function sets the URL for the hyperlink control.
    virtual void SetURL(LPCTSTR lpszLink);

	// -> Parameters:		
	// -> Return Value:		A CString object that represents the URL for the hyperlink
	//						control.
	// -> Remarks:			This member function returns the URL for the hyperlink.
	virtual CString GetURL() const;

	// -> Parameters:		clrLink    -	RGB color value for the hyperlink text color.
	//						clrVisited -	RGB color value for the hyperlink text color when 
	//										the mouse is hovering.
	//						clrHover   -	RGB color value for the hyperlink text color when
	//										the URL has been visited.
	// -> Return Value:		
	// -> Remarks:			This member function will set the RGB color values for the 
	//						hyperlink text.
    virtual void SetColors(COLORREF clrLink, COLORREF clrVisited, COLORREF clrHover);

	// -> Parameters:		
	// -> Return Value:		RGB color value that represents the current hyperlink text color.
	// -> Remarks:			This member function returns the current hyperlink text color.
	virtual COLORREF GetLinkColor() const;

	// -> Parameters:		
	// -> Return Value:		RGB color value that represents the current hyperlink text color
	//						when the link has been activated.
	// -> Remarks:			This member function returns the current hyperlink text color
	//						when the link has been activated.
    virtual COLORREF GetVisitedColor() const;

	// -> Parameters:		
	// -> Return Value:		RGB color value that represents the current hyperlink text color
	//						when the mouse hovers over the hyperlink.
	// -> Remarks:			This member function returns the current hyperlink text color
	//						when the mouse hovers over the hyperlink.
    virtual COLORREF GetHoverColor() const;

	// -> Parameters:		bVisited -	A boolean flag when set to true causes the control
	//									to display the hyperlink text color as visited.
	// -> Return Value:		
	// -> Remarks:			This member function will cause the contorl to display the
	//						hyperlink text color as visited.
    virtual void SetVisited(bool bVisited = true);

	// -> Parameters:		
	// -> Return Value:		true if the URL has been visited; otherwise false.
	// -> Remarks:			This member function returns true to indicate that the user has
	//						visited URL associated with the hyperlink.
    virtual bool GetVisited() const;

	// -> Parameters:		hCursor -	Handle of the cursor to be associated withthe 
	//									hyperlink control.
	// -> Return Value:		
	// -> Remarks:			This member function will set the cursor to be displayed when
	//						the mouse hovers over the hyperlink control.
	virtual void SetLinkCursor(HCURSOR hCursor);

	// -> Parameters:		
	// -> Return Value:		A handle to the current cursor for the hyperlink control.
	// -> Remarks:			This member function will return a handle to the current
	//						cursor associated with the hyperlink control.
    virtual HCURSOR GetLinkCursor() const;

	// -> Parameters:		bUnderline -	true for underlined hyperlink text.
	// -> Return Value:		
	// -> Remarks:			This member function will cause the hyperlink to display the
	//						text as underlined, default equals true.
    virtual void SetUnderline(bool bUnderline = true);

	// -> Parameters:		
	// -> Return Value:		true if the hyperlink text is underlined; otherwise false.
	// -> Remarks:			This member function will true if the hyperlink text is 
	//						underlined.
    virtual bool GetUnderline() const;

	// -> Parameters:		lpszLink -	Points to a null terminated string that represents
	//									the URL to jump to, if NULL, the default URL is
	//									activated.
	//						nShowCmd -	Display state for shell command associated with the
	//									URL, default is SW_SHOW.
	// -> Return Value:		A value greater than 32 if successful, or an error value that is 
	//						less than or equal to 32 otherwise
	// -> Remarks:			This member function is called to execute the shell command 
	//						associated with the current URL.
    virtual HINSTANCE GotoURL(LPCTSTR lpszLink=NULL, int nShowCmd=SW_SHOW);

	// -> Parameters:		
	// -> Return Value:		true if the hyperlink control is a text control; otherwise false.
	// -> Remarks:			This member function returns true if the hyperlink control is
	//						a text control.
	virtual bool IsTextControl();

	//{{AFX_VIRTUAL(CXTHyperLink)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CXTHyperLink)
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg UINT OnNcHitTest(CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClicked();
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

//---------------------------------------------------------------------------
inline void CXTHyperLink::SetURL(LPCTSTR lpszLink)
	{ m_strLink = lpszLink; m_toolTip.UpdateTipText(lpszLink, this); }
//---------------------------------------------------------------------------
inline CString CXTHyperLink::GetURL() const
	{ return m_strLink; }
//---------------------------------------------------------------------------
inline void CXTHyperLink::SetColors(COLORREF clrLink, COLORREF clrVisited, COLORREF clrHover)
	{ m_clrLink = clrLink; m_clrVisited = clrVisited; m_clrHover = clrHover; }
//---------------------------------------------------------------------------
inline COLORREF CXTHyperLink::GetLinkColor() const
	{ return m_clrLink; }
//---------------------------------------------------------------------------
inline COLORREF CXTHyperLink::GetVisitedColor() const
	{ return m_clrVisited; }
//---------------------------------------------------------------------------
inline COLORREF CXTHyperLink::GetHoverColor() const
	{ return m_clrHover; }
//---------------------------------------------------------------------------
inline void CXTHyperLink::SetVisited(bool bVisited)
	{ m_bVisited = bVisited; }
//---------------------------------------------------------------------------
inline bool CXTHyperLink::GetVisited() const
	{ return m_bVisited; }
//---------------------------------------------------------------------------
inline void CXTHyperLink::SetLinkCursor(HCURSOR hCursor)
	{ m_hcurHand = hCursor; }
//---------------------------------------------------------------------------
inline HCURSOR CXTHyperLink::GetLinkCursor() const
	{ return m_hcurHand; }
//---------------------------------------------------------------------------
inline void CXTHyperLink::SetUnderline(bool bUnderline)
	{ m_bUnderline = bUnderline; }
//---------------------------------------------------------------------------
inline bool CXTHyperLink::GetUnderline() const
	{ return m_bUnderline; }
//---------------------------------------------------------------------------
inline bool CXTHyperLink::IsTextControl() 
	{ return ((GetStyle() & 0xFF) <= SS_RIGHT) ? true:false; }
//---------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // #if !defined(__XTHYPERLINK_H__)
