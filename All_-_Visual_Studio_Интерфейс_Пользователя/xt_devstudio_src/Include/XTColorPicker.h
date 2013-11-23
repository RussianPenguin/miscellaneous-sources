// XTColorPicker.h : interface for the CXTColorPicker class.
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

#if !defined(__XTCOLORPICKER_H__)
#define __XTCOLORPICKER_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// class forwards
class CXTColorPopup;

/////////////////////////////////////////////////////////////////////////////
// CXTColorPicker window
/////////////////////////////////////////////////////////////////////////////
class _XT_EXT_CLASS CXTColorPicker : public CButton
{
	DECLARE_DYNAMIC(CXTColorPicker)

public:
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Constructor - handles default initialization.
	CXTColorPicker();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Destructor - handles cleanup and de-allocation.
	virtual ~CXTColorPicker();

protected:

	DWORD			m_dwPopup;			// Represents the style for the color picker.
	CXTColorPopup*	m_pColorPopup;		// Points to the color popup window that is created.
	COLORREF		m_clrDisp;			// RGB color value for the display color.
	COLORREF		m_clrText;			// RGB color value for the display text.
	COLORREF		m_clrDefault;		// RGB color value for the default color.
	BOOL			m_bDefault;			// TRUE to display a colored rect, FALSE to display colored text.

public:

	// -> Parameters:		clr -	New RGB color value for the control.
	// -> Return Value:		
	// -> Remarks:			This member function will set the color value for the
	//						color picker.
	virtual void SetColor(COLORREF clr);

	// -> Parameters:		
	// -> Return Value:		A RGB color value that represents the currently 
	//						selected color.
	// -> Remarks:			This member function will return the currently selected color.
	virtual COLORREF GetColor();

	// -> Parameters:		bDefault -	If TRUE the color picker will display a box
	//									filled with the currently selected color; otherwise
	//									the color will be dislayed as text.
	// -> Return Value:		
	// -> Remarks:			This member function will set the display style for the color
	//						picker. The color picker can either display a filled rect or
	//						text to represent the currently selected color.
    virtual void SetSelectionMode(BOOL bDefault);

	// -> Parameters:		
	// -> Return Value:		TRUE if the color picker displays a filled rect, otherwise FALSE;
	// -> Remarks:			This member function will return TRUE or FALSE depending on the
	//						display settings.
    virtual BOOL GetSelectionMode();

	// -> Parameters:		clrDefault -	RGB default color value for the color picker.
	// -> Return Value:		
	// -> Remarks:			This member function will set the default RGB color value for the
	//						color picker.
	virtual void SetDefaultColor(COLORREF clrDefault);

	// -> Parameters:		
	// -> Return Value:		The default color value for the color picker.
	// -> Remarks:			This member function will return the default RGB color value for 
	//						the color picker.
	virtual COLORREF GetDefaultColor();

	// -> Parameters:		dwRemove -	Specifies window styles to be removed during style 
	//									modification.
	//						dwAdd	 -	Specifies window styles to be added during style 
	//									modification.
	// -> Return Value:		
	// -> Remarks:			Call this member function to modify the color picker style. Styles 
	//						to be added or removed can be combined by using the bitwise OR (|) 
	//						operator. Can be one or more of the following:
	//
	//							CPS_NOFILL		-	The color picker will display a No Fill button
	//												rather than the default Automatic Color button.
	//							CPS_EXTENDED	-	The color picker will display 40 extended
	//												colors rather than the default 16 colors.
	//							CPS_MORECOLORS	-	The color picker will display a More Colors
	//												button which will display a CColorDialog. 
	virtual void ModifyCPStyle(DWORD dwRemove, DWORD dwAdd);

protected:

	// -> Parameters:		clr -	RGB color value which represents the default color rect color.
	// -> Return Value:		
	// -> Remarks:			This member function will set the color of the filled rect that
	//						is displayed on the control.
	virtual void SetDispColor(COLORREF clr);

	// -> Parameters:		
	// -> Return Value:		RGB color value that represents the currently selected color.
	// -> Remarks:			This member function will return the currently selected color if
	//						the display mode is set to TRUE.
	virtual COLORREF GetDispColor();

	// -> Parameters:		clr -	RGB color value which represents the default color text color.
	// -> Return Value:		
	// -> Remarks:			This member function will set the color of the filled text that
	//						is displayed on the control.
	virtual void SetTextColor(COLORREF clr);

	// -> Parameters:		
	// -> Return Value:		RGB color value that represents the currently selected color.
	// -> Remarks:			This member function will return the currently selected color if
	//						the display mode is set to FALSE.
	virtual COLORREF GetTextColor();

	// -> Parameters:		clr -	RGB color value to check against the text display.
	// -> Return Value:		
	// -> Remarks:			If the display mode is set to TRUE, this member function will
	//						check the currently selected color, and adjust the text display
	//						accordingly.
	virtual void CheckColor(COLORREF clr);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXTColorPicker)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

	// Generated message map functions
protected:
	//{{AFX_MSG(CXTColorPicker)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg LRESULT OnSelChange(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnDropDown(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnCloseUp(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnSelEndOK(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnSelEndCancel(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnSelNoFill(WPARAM wParam, LPARAM lParam);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	//}}AFX_MSG

	afx_msg void OnClicked();

	DECLARE_MESSAGE_MAP()
};

//---------------------------------------------------------------------------
inline COLORREF CXTColorPicker::GetColor()
	{ return (m_bDefault ? GetDispColor() : GetTextColor()); }
//---------------------------------------------------------------------------
inline void CXTColorPicker::SetDispColor(COLORREF clr)
	{ m_clrDisp = clr; }
//---------------------------------------------------------------------------
inline COLORREF CXTColorPicker::GetDispColor()
	{ return (m_clrDisp==-1) ? afxData.clrBtnFace : m_clrDisp; }
//---------------------------------------------------------------------------
inline void CXTColorPicker::SetTextColor(COLORREF clr)
	{ m_clrText = clr; }
//---------------------------------------------------------------------------
inline COLORREF CXTColorPicker::GetTextColor()
	{ return (m_clrText==-1) ? afxData.clrBtnFace : m_clrText; }
//---------------------------------------------------------------------------
inline void CXTColorPicker::SetSelectionMode(BOOL bDefault)
	{ m_bDefault = bDefault; }
//---------------------------------------------------------------------------
inline BOOL CXTColorPicker::GetSelectionMode()
	{ return m_bDefault; }
//---------------------------------------------------------------------------
inline void CXTColorPicker::SetDefaultColor(COLORREF clrDefault)
	{ m_clrDefault = clrDefault; }
//---------------------------------------------------------------------------
inline COLORREF CXTColorPicker::GetDefaultColor()
	{ return m_clrDefault; }
//---------------------------------------------------------------------------
inline void CXTColorPicker::ModifyCPStyle(DWORD dwRemove, DWORD dwAdd)
	{ m_dwPopup &= ~dwRemove; m_dwPopup |= dwAdd; }
//---------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // #if !defined(__XTCOLORPICKER_H__)
