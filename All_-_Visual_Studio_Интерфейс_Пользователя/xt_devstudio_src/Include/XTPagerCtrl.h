// XTPagerCtrl.h interface for the CXTPagerCtrl class.
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

#if !defined(__XTPAGERCTRL_H__)
#define __XTPAGERCTRL_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CXTPagerCtrl is a CWnd derived class which wraps the windows
// Pager common control.
/////////////////////////////////////////////////////////////////////////////
class _XT_EXT_CLASS CXTPagerCtrl : public CWnd
{
	DECLARE_DYNAMIC(CXTPagerCtrl)

public:
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Constructor - handles default initialization
	CXTPagerCtrl();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Destructor - handles clean up.
	virtual ~CXTPagerCtrl();

protected:

	int m_nWidth;	// user defined scroll width see SetScrollArea(...)
	int m_nHeight;	// user defined scroll height see SetScrollArea(...)

public:

	// -> Parameters:		nWidth	-	
	//						nHeight	-	
	// -> Return Value:		
	// -> Remarks:			This member function sets the scroll area for the pager
	void SetScrollArea (int nWidth, int nHeight);

	// -> Parameters:		hwndChild	-	Handle to the window to be contained.
	// -> Return Value:		
	// -> Remarks:			Sets the contained window for the pager control
	void SetChild(HWND hwndChild);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Forces the pager control to recalculate the size of 
	//						the contained window
	void RecalcSize();

	// -> Parameters:		bForward	-	BOOL value that determines if mouse forwarding 
	//										is enabled or disabled. If this value is nonzero, 
	//										mouse forwarding is enabled. If this value is zero, 
	//										mouse forwarding is disabled.
	// -> Return Value:		
	// -> Remarks:			Enables or disables mouse forwarding for the pager control
	void ForwardMouse(BOOL bForward);

	// -> Parameters:		clr	-	COLORREF value that contains the new background color 
	//								of the pager control.
	// -> Return Value:		
	// -> Remarks:			Sets the current background color for the pager control
	COLORREF SetBkColor(COLORREF clr);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Retrieves the current background color for the pager control
	COLORREF GetBkColor();

	// -> Parameters:		iBorder	-	INT value that contains the new size of the 
	//									border, in pixels.
	// -> Return Value:		
	// -> Remarks:			Sets the current border size for the pager control
	int SetBorder(int iBorder);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Retrieves the current border size for the pager control
	int GetBorder();

	// -> Parameters:		iPos	-	INT value that contains the new scroll 
	//									position, in pixels.
	// -> Return Value:		
	// -> Remarks:			Sets the scroll position for the pager control
	int SetPos(int iPos);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Retrieves the current scroll position of the pager control.
	int GetPos();

	// -> Parameters:		iSize	-	INT value that contains the new button size, in pixels
	// -> Return Value:		
	// -> Remarks:			Sets the current button size for the pager control.
	int SetButtonSize(int iSize);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Retrieves the current button size for the pager control.
	int GetButtonSize();

	// -> Parameters:		iButton	-	Indicates which button to retrieve the state for
	// -> Return Value:		
	// -> Remarks:			Retrieves the state of the specified button in a pager control
	DWORD GetButtonState(int iButton);

	// -> Parameters:		ppdt -	Address of an IDropTarget pointer that receives the 
	//								interface pointer
	// -> Return Value:		
	// -> Remarks:			Retrieves a pager control's IDropTarget interface pointer
	void GetDropTarget(IDropTarget **ppdt);

	//{{AFX_VIRTUAL(CXTPagerCtrl)
	public:
	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
	//}}AFX_VIRTUAL

protected:

	//{{AFX_MSG(CXTPagerCtrl)
	virtual BOOL OnPagerScroll(NMPGSCROLL* pNMPGScroll, LRESULT * pResult);
	virtual BOOL OnPagerCalcSize(NMPGCALCSIZE * pNMPGCalcSize, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//---------------------------------------------------------------------------
inline void CXTPagerCtrl::SetScrollArea (int nWidth, int nHeight)
	{ ASSERT(::IsWindow(m_hWnd)); m_nWidth  = nWidth; m_nHeight = nHeight; }
//---------------------------------------------------------------------------
inline void CXTPagerCtrl::SetChild(HWND hwndChild)
	{ ASSERT(::IsWindow(m_hWnd)); Pager_SetChild(m_hWnd, hwndChild); }
//---------------------------------------------------------------------------
inline void CXTPagerCtrl::RecalcSize()
	{ ASSERT(::IsWindow(m_hWnd)); Pager_RecalcSize(m_hWnd); }
//---------------------------------------------------------------------------
inline void CXTPagerCtrl::ForwardMouse(BOOL bForward)
	{ ASSERT(::IsWindow(m_hWnd)); Pager_ForwardMouse(m_hWnd, bForward); }
//---------------------------------------------------------------------------
inline COLORREF CXTPagerCtrl::SetBkColor(COLORREF clr)
	{ ASSERT(::IsWindow(m_hWnd)); return Pager_SetBkColor(m_hWnd, clr); }
//---------------------------------------------------------------------------
inline COLORREF CXTPagerCtrl::GetBkColor()
	{ ASSERT(::IsWindow(m_hWnd)); return Pager_GetBkColor(m_hWnd); }
//---------------------------------------------------------------------------
inline int CXTPagerCtrl::SetBorder(int iBorder)
	{ ASSERT(::IsWindow(m_hWnd)); return Pager_SetBorder(m_hWnd, iBorder); }
//---------------------------------------------------------------------------
inline int CXTPagerCtrl::GetBorder()
	{ ASSERT(::IsWindow(m_hWnd)); return Pager_GetBorder(m_hWnd); }
//---------------------------------------------------------------------------
inline int CXTPagerCtrl::SetPos(int iPos)
	{ ASSERT(::IsWindow(m_hWnd)); return Pager_SetPos(m_hWnd, iPos); }
//---------------------------------------------------------------------------
inline int CXTPagerCtrl::GetPos()
	{ ASSERT(::IsWindow(m_hWnd)); return Pager_GetPos(m_hWnd); }
//---------------------------------------------------------------------------
inline int CXTPagerCtrl::SetButtonSize(int iSize)
	{ ASSERT(::IsWindow(m_hWnd)); return Pager_SetButtonSize(m_hWnd, iSize); }
//---------------------------------------------------------------------------
inline int CXTPagerCtrl::GetButtonSize()
	{ ASSERT(::IsWindow(m_hWnd)); return Pager_GetButtonSize(m_hWnd); }
//---------------------------------------------------------------------------
inline DWORD CXTPagerCtrl::GetButtonState(int iButton)
	{ ASSERT(::IsWindow(m_hWnd)); return Pager_GetButtonState(m_hWnd, iButton); }
//---------------------------------------------------------------------------
inline void CXTPagerCtrl::GetDropTarget(IDropTarget **ppdt)
	{ ASSERT(::IsWindow(m_hWnd)); Pager_GetDropTarget(m_hWnd, ppdt); }
//---------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // #if !defined(__XTPAGERCTRL_H__)
