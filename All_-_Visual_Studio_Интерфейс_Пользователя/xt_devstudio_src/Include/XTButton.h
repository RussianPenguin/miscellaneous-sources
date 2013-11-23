// XTButton.h : interface for the CXTButton class.
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

#if !defined(__XTBUTTON_H__)
#define __XTBUTTON_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CXTButton is a CButton derived class used to create flat buttons.
// this class can only be used with the BS_OWNERDRAW style bit set.
/////////////////////////////////////////////////////////////////////////////
class _XT_EXT_CLASS CXTButton : public CButton
{
	DECLARE_DYNAMIC(CXTButton)

public:
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Constructor - handles default initialization.
	CXTButton();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Destructor - handles cleanup and de-allocation.
	virtual ~CXTButton();

protected:

	HICON		m_hIcon;			// Handle to the icon associated with the button.
	HICON		m_hIconPushed;		// Handle to the icon associated with the button when it is pressed.
	HBITMAP		m_hBitmap;			// Bitmap associated with the button.
	HBITMAP		m_hBitmapMono;		// Disabled bitmap assosciated with the button.
	CSize		m_sizeImage;		// Initial size of the button.
	CPoint		m_ptImage;			// XY location of the button image.
	CPoint		m_ptText;			// XY location of the button text.
	int			m_nBorderGap;		// Gap between the button edge and the image.
	int			m_nImageGap;		// Gap between the button text and the image.
	DWORD		m_dwxStyle;			// The style of the button, see SetXButtonStyle().
	BOOL		m_bHilite;			// TRUE if the button is hilighted.
	BOOL		m_bForceHilight;	// TRUE to force the button to be hilighted 
	BOOL		m_bUserPosition;	// TRUE if the user has defined the XY coordinates for the image and text.
	BOOL		m_bMouseOver;		// TRUE if mouse is currently over the button.
	BOOL		m_bLBtnDown;		// true if left mouse button is pressed
	BOOL		m_bAltColor;		// TRUE if user defined colors are used.
	BOOL		m_bPainted;			// used during paint operations
	BOOL		m_bNoHilite;		// If TRUE the flat button will not be highlighted when mouse hovers and pressed.
	COLORREF	m_clrBtnText;		// RGB value that represents the button text color
	COLORREF	m_clr3DFace;		// RGB value that represents the button face color
	COLORREF	m_clr3DHilight;		// RGB value that represents the 3D border hilight color
	COLORREF	m_clr3DShadow;		// RGB value that represents the 3D border shadow color

public:

	// -> Parameters:		nGap -	Ammount in pixels of the gap between button edge and image.
	// -> Return Value:		Returns the prevous border gap value.
	// -> Remarks:			This member function will set the gap between the buttons 
	//						edge and the image.
	int SetBorderGap(int nGap);

	// -> Parameters:		nGap -	Ammount in pixels of the gap between button text and image.
	// -> Return Value:		Returns the prevous border gap value.
	// -> Remarks:			This member function will set the gap between the buttons 
	//						text and the image.
	int SetImageGap(int nGap);

	// -> Parameters:		clr3DFace		-	User defined face color for three-dimensional 
	//											display elements
	//						clr3DHilight	-	User defined highlight color for three-dimensional 
	//											display elements (for edges facing the light source.)
	//						clr3DShadow		-	User defined shadow color for three-dimensional 
	//											display elements (for edges facing away from the 
	//											light source). 
	//						clrBtnText		-	User defined text on push buttons. 
	// -> Return Value:		
	// -> Remarks:			This method will allow the user to define the default colors 
	//						for the background shadow and hilight colors for the button.
	virtual void SetAlternateColors(COLORREF clr3DFace, COLORREF clr3DHilight, COLORREF clr3DShadow, COLORREF clrBtnText);

	// -> Parameters:		size		-	CSize object that represents the size of the icon.
	//						hIcon		-	Handle to the normal icon.
	//						hIconPushed	-	Handle to the pressed icon.
	//						bRedraw		-	Specifies whether the button is to be redrawn. A 
	//										nonzero value redraws the button. A 0 value does not 
	//										redraw the button. The button is redrawn by default.
	// -> Return Value:		TRUE if successful, otherwise FALSE.
	// -> Remarks:			This member function will set the normal and pushed state icons
	//						for the push button.
	virtual BOOL SetIcon(CSize size, HICON hIcon, HICON hIconPushed=NULL, BOOL bRedraw=TRUE);

	// -> Parameters:		size		-	CSize object that represents the size of the icon.
	//						nID			-	Resource ID for the normal icon.
	//						nPushedID	-	Resource ID for the pressed icon.
	//						bRedraw		-	Specifies whether the button is to be redrawn. A 
	//										nonzero value redraws the button. A 0 value does not 
	//										redraw the button. The button is redrawn by default.
	// -> Return Value:		TRUE if successful, otherwise FALSE.
	// -> Remarks:			This member function will set the normal and pushed state icons
	//						for the push button.
	virtual BOOL SetIcon(CSize size, UINT nID, UINT nPushedID=0, BOOL bRedraw=TRUE);

	// -> Parameters:		size		-	CSize object that represents the size of the icon.
	//						lpszID		-	Resource string ID for the normal icon.
	//						lpszPushedID-	Resource string ID for the pressed icon.
	//						bRedraw		-	Specifies whether the button is to be redrawn. A 
	//										nonzero value redraws the button. A 0 value does not 
	//										redraw the button. The button is redrawn by default.
	// -> Return Value:		
	// -> Return Value:		TRUE if successful, otherwise FALSE.
	// -> Remarks:			This member function will set the normal and pushed state icons
	//						for the push button.
	virtual BOOL SetIcon(CSize size, LPCTSTR lpszID, LPCTSTR lpszPushedID=NULL, BOOL bRedraw=TRUE);

	// -> Parameters:		size		-	CSize object that represents the size of the bitmap.
	//						nID			-	Resource ID for the bitmap.
	//						bRedraw		-	Specifies whether the button is to be redrawn. A 
	//										nonzero value redraws the button. A 0 value does not 
	//										redraw the button. The button is redrawn by default.
	// -> Return Value:		TRUE if successful, otherwise FALSE.
	// -> Remarks:			This member function will set the bitmap associated with the button.
	virtual BOOL SetBitmap(CSize size, UINT nID, BOOL bRedraw=TRUE);

	// -> Parameters:		ptImage	-	XY location of the image displayed on the button.
	//						ptText	-	XY location of the text displayed on the button.
	//						bRedraw	-	Specifies whether the button is to be redrawn. A 
	//									nonzero value redraws the button. A 0 value does not 
	//									redraw the button. The button is redrawn by default.
	// -> Return Value:		TRUE if successful, otherwise FALSE.
	// -> Remarks:			This member function will set the XY location of the text and image
	//						that is displayed on the push button.
	virtual BOOL SetTextAndImagePos(CPoint ptImage, CPoint ptText, BOOL bRedraw=TRUE);

	// -> Parameters:		dwxStyle	-	Specifies the button style, can be one or more of 
	//										the following:
	//
	//										BS_XT_FLAT		-	The button is displayed flat with
	//															a raised edge whenever the mouse
	//															passes over the control.
	//										BS_XT_SEMIFLAT	-	The button is displayed with a thin
	//															3D raised edge.
	//										BS_XT_CENTER	-	The button text and image are centered
	//															within the control.
	//										BS_XT_SHOWFOCUS	-	A focus rect is drawn whenever the
	//															button has focus.
	//
	//						bRedraw		-	Specifies whether the button is to be redrawn. A 
	//										nonzero value redraws the button. A 0 value does not 
	//										redraw the button. The button is redrawn by default.
	// -> Return Value:		The previous style that was set.
	// -> Remarks:			This member function will set the display style for the button.
	DWORD SetXButtonStyle(DWORD dwxStyle, BOOL bRedraw=TRUE);

	// -> Parameters:		
	// -> Return Value:		Returns the button styles for this CXTButton object.
	// -> Remarks:			This function returns only the BS_XT_ style values, not any of the 
	//						other window styles.
	DWORD GetXButtonStyle();

protected:

	// -> Parameters:		point	-	XY location of the text and image that is displayed.
	//						size	-	Initial size of the image associated with the button.
	// -> Return Value:		
	// -> Remarks:			This member function will set the proper XY coordinates for the
	//						button text and image.
	void OffsetPoint(CPoint& point, CSize size);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			This member function is called to free all assocaited GDI resources
	//						that have been allocated.
	void CleanUpGDI();

	// -> Parameters:		pDC		-	A CDC pointer that represents the current device 
	//									context.
	//						nState	-	A UINT value that represents the current state 
	//									for the button.
	//						rcItem	-	A CRect reference that represents the current 
	//									size for the button.
	// -> Return Value:		
	// -> Remarks:			This member function draws the icon for the button, if any.
	virtual void DrawButtonIcon(CDC* pDC, UINT nState, CRect& rcItem);

	// -> Parameters:		pDC		-	A CDC pointer that represents the current device 
	//									context.
	//						nState	-	A UINT value that represents the current state 
	//									for the button.
	//						rcItem	-	A CRect reference that represents the current 
	//									size for the button.
	// -> Return Value:		
	// -> Remarks:			This member function will draw the text for the button, if any.
	virtual void DrawButtonText(CDC* pDC, UINT nState, CRect& rcItem);

	// -> Parameters:		pDC		-	A CDC pointer that represents the current device 
	//									context.
	//						nState	-	A UINT value that represents the current state 
	//									for the button.
	//						rcItem	-	A CRect reference that represents the current 
	//									size for the button.
	// -> Return Value:		
	// -> Remarks:			This member function will draw the bitmap for the button, if any.
	virtual void DrawButtonBitmap(CDC* pDC, UINT nState, CRect& rcItem);

	//{{AFX_VIRTUAL(CXTButton)
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CXTButton)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSysColorChange();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

//---------------------------------------------------------------------------
// NOTE: The following methods are obsolete, and are included here only for
// support to users who have upgraded from CJLibrary.
//---------------------------------------------------------------------------
public:
	inline void SetIcon(HICON hIcon, CSize size) {
		SetIcon(size, hIcon);
	}
	inline void SetIcon(HICON hIcon, HICON hIconPushed, CSize size) {
		SetIcon(size, hIcon, hIconPushed);
	}
};

//---------------------------------------------------------------------------
inline int CXTButton::SetImageGap(int nGap)
	{ int nOldGap = m_nImageGap; m_nImageGap = nGap; return nOldGap; }
//---------------------------------------------------------------------------
inline int CXTButton::SetBorderGap(int nGap)
	{ int nOldGap = m_nBorderGap; m_nBorderGap = nGap; return nOldGap; }
//---------------------------------------------------------------------------
inline DWORD CXTButton::GetXButtonStyle()
	{ ASSERT(::IsWindow(m_hWnd)); return m_dwxStyle; }
//---------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // #if !defined(__XTBUTTON_H__)
