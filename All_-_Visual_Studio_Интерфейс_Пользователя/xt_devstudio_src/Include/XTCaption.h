// XTCaption.h : interface for the CXTCaption class.
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

#if !defined(__XTCAPTION_H__)
#define __XTCAPTION_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "XTButton.h"

/////////////////////////////////////////////////////////////////////////////
// CXTCaptionButton is a CXTButton derived class which is used by
// the CXTCaption class to activate a CXTCaptionPopupWnd window.
/////////////////////////////////////////////////////////////////////////////
class _XT_EXT_CLASS CXTCaptionButton : public CXTButton
{
	DECLARE_DYNAMIC(CXTCaptionButton)
public:
	
	// -> Parameters:		pFont			-	Points to a CFont object that represents the
	//											new font for the caption button.
	//						clrBackground	-	RGB value for the button background color.
	//						clrFont			-	RGB value for the font color.
	// -> Return Value:		TRUE if successful.
	// -> Remarks:			This member function will set the style for the caption button.
	virtual BOOL SetButtonStyle(CFont* pFont, COLORREF clrBackground, COLORREF clrFont);

	//{{AFX_VIRTUAL(CXTCaptionButton)
	virtual void DrawButtonText(CDC* pDC, UINT nState, CRect& rcItem);
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CXTCaptionButton)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

class CXTCaptionPopupWnd;

/////////////////////////////////////////////////////////////////////////////
// CXTCaption is a CStatic derived class which is simular to the
// caption or info bars that are seen in Microsoft Outlook
/////////////////////////////////////////////////////////////////////////////
class _XT_EXT_CLASS CXTCaption : public CStatic
{
	DECLARE_DYNAMIC(CXTCaption)

public:
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Constructor - handles default initialization.
	CXTCaption();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Destructor - handles cleanup and de-allocation.
	virtual ~CXTCaption();

protected:

	COLORREF			m_clrBorder;		// user defined border color
	COLORREF			m_clrBackgnd;		// user defined background color
	COLORREF			m_clrFont;			// user defined font color
	int					m_nBorder;			// size in pixels for the caption border
	HICON				m_hIcon;			// user defined icon handle, default value NULL
	CString				m_strWindText;		// text that will be displayed in caption.
	int					m_nOffset;			// 
	CWnd*				m_pChildWnd;		// 
	CWnd*				m_pNotifyWnd;		// 
	CXTCaptionButton	m_CaptionButton;	// 
	CXTCaptionPopupWnd* m_pWndPopDown;		// 
	CRect				m_rcChild;			// 
	DWORD				m_dwExStyle;		// 
	CRect				m_rcClient;			// 
	DWORD				m_dwTextStyle;		// 

public:
	
	// -> Parameters:		clrBorder	  -	A COLORREF value for the new border color.
	//						clrBackground -	A COLORREF value for the new background color.
	//						clrFont		  -	A COLORREF value for the new font color.
	// -> Return Value:		
	// -> Remarks:			This member function will set the caption bar border, 
	//						background and font colors.
	virtual void SetCaptionColors(COLORREF clrBorder, COLORREF clrBackground, COLORREF clrFont);
	
	// -> Parameters:		nBorderSize  -	Specifies size in pixels of the banner border.
	//						pFont		 -	Specifies the new caption font.
	//						lpszWindText -	Address of a null-terminated string specifying 
	//										the new caption text.
	//						hIcon		 -	Handle of the icon to be drawn in the caption.
	// -> Return Value:		
	// -> Remarks:			This function will modify the caption style. You can use this 
	//						member function to set the border size that is drawn around the 
	//						caption banner, the font that the caption will use, the caption text 
	//						and icon to be displayed.
	virtual void ModifyCaptionStyle(int nBorderSize, CFont* pFont=NULL, LPCTSTR lpszWindText=NULL, HICON hIcon=NULL);

	// -> Parameters:		pChild		-	
	//						pNotifyWnd	-	
	// -> Return Value:		
	// -> Remarks:			
	virtual void SetChildWindow(CWnd* pChild, CWnd* pNotifyWnd);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual void KillChildWindow();

	// -> Parameters:		pDC		-	
	//						rcItem	-	
	// -> Return Value:		
	// -> Remarks:			
	virtual void DrawCaptionBack(CDC* pDC, CRect& rcItem);

	// -> Parameters:		pDC		-	
	//						rcItem	-	
	// -> Return Value:		
	// -> Remarks:			
	virtual void DrawCaptionText(CDC* pDC, CRect& rcItem);

	// -> Parameters:		pDC		-	
	//						rcItem	-	
	// -> Return Value:		
	// -> Remarks:			
	virtual void DrawCaptionIcon(CDC* pDC, CRect& rcItem);

	// -> Parameters:		lpszWindowText	-	
	//						hIcon			-	
	// -> Return Value:		
	// -> Remarks:			
	virtual void UpdateCaption(LPCTSTR lpszWindowText, HICON hIcon);

	// -> Parameters:		pDC		-	
	//						rcItem	-	
	// -> Return Value:		
	// -> Remarks:			
	virtual void UpdateCaptionBack(CDC* pDC, CRect& rcItem);

	// -> Parameters:		pDC		-	
	//						rcItem	-	
	// -> Return Value:		
	// -> Remarks:			
	virtual void UpdateCaptionText(CDC* pDC, CRect& rcItem);

	// -> Parameters:		dwStyle	-	
	// -> Return Value:		
	// -> Remarks:			
	virtual void SetTextStyle(DWORD dwStyle); 

	//{{AFX_VIRTUAL(CXTCaption)
	virtual BOOL Create(CWnd* pParentWnd, LPCTSTR lpszWindowName, DWORD dwExStyle=CPWS_EX_FLATEDGE, DWORD dwStyle=WS_VISIBLE|SS_CENTER|SS_CENTERIMAGE, const CRect& rect=CRect(0,0,0,0), UINT nID = 0xffff);
	//}}AFX_VIRTUAL

protected:

	//{{AFX_MSG(CXTCaption)
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	afx_msg void OnCaptButton();
	afx_msg void OnPushPinButton(UINT lParam, LONG wParam);
	afx_msg void OnPushPinCancel(UINT lParam, LONG wParam);

	DECLARE_MESSAGE_MAP()
};

//---------------------------------------------------------------------------
inline void CXTCaption::SetTextStyle(DWORD dwStyle)
	{ m_dwTextStyle = dwStyle; }
//---------------------------------------------------------------------------
inline void CXTCaption::SetCaptionColors(COLORREF clrBorder, COLORREF clrBackground, COLORREF clrFont)
	{ ASSERT(::IsWindow(m_hWnd)); m_clrBorder = clrBorder; m_clrBackgnd = clrBackground; m_clrFont = clrFont; }
//---------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // #if !defined(__XTCAPTION_H__)

