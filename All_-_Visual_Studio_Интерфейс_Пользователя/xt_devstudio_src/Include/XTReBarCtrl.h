// XTReBarCtrl.h interface for the CXTReBarCtrl class.
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

#if !defined(__XTREBARCTRL_H__)
#define __XTREBARCTRL_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// The CXTReBarCtrl class encapsulates the functionality of a rebar control, 
// which is a container for a child window. The application in which the rebar 
// control resides assigns the child window contained by the rebar control to the 
// rebar band. The child window is usually another common control.
/////////////////////////////////////////////////////////////////////////////
class _XT_EXT_CLASS CXTReBarCtrl : public CWnd
{
  DECLARE_DYNAMIC(CXTReBarCtrl)

public:
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Constructor - handles default initialization
	CXTReBarCtrl();

	// -> Parameters:		dwStyle		-	
	//						rect		-	
	//						pParentWnd	-	
	//						nID			-	
	// -> Return Value:		
	// -> Remarks:			
	BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	UINT GetBandCount() const;
	
	// -> Parameters:		uBand	-	
	//						prbbi	-
	// -> Return Value:		
	// -> Remarks:			
	BOOL GetBandInfo(UINT uBand, REBARBANDINFO* prbbi) const;
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	UINT GetBarHeight() const;
	
	// -> Parameters:		prbi	-	
	// -> Return Value:		
	// -> Remarks:			
	BOOL GetBarInfo(REBARINFO* prbi) const;
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	COLORREF GetBkColor() const;
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	IDropTarget* GetDropTarget() const;
	
	// -> Parameters:		uBand	-	
	//						prc		-	
	// -> Return Value:		
	// -> Remarks:			
	BOOL GetRect(UINT uBand, LPRECT prc) const;
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	UINT GetRowCount() const;
	
	// -> Parameters:		uRow	-	
	// -> Return Value:		
	// -> Remarks:			
	UINT GetRowHeight(UINT uRow) const;
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	COLORREF GetTextColor() const;
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	CToolTipCtrl* GetToolTips() const;
	
	// -> Parameters:		uBandID	-	
	// -> Return Value:		
	// -> Remarks:			
	int IDToIndex(UINT uBandID) const;
	
	// -> Parameters:		uBand	-	
	//						prbbi	-	
	// -> Return Value:		
	// -> Remarks:			
	BOOL SetBandInfo(UINT uBand, REBARBANDINFO* prbbi);
	
	// -> Parameters:		prbi	-	
	// -> Return Value:		
	// -> Remarks:			
	BOOL SetBarInfo(REBARINFO* prbi);
	
	// -> Parameters:		clr	-	
	// -> Return Value:		
	// -> Remarks:			
	COLORREF SetBkColor(COLORREF clr);
	
	// -> Parameters:		pWnd	-	
	// -> Return Value:		
	// -> Remarks:			
	CWnd* SetOwner(CWnd* pWnd);
	
	// -> Parameters:		clr	-	
	// -> Return Value:		
	// -> Remarks:			
	COLORREF SetTextColor(COLORREF clr);
	
	// -> Parameters:		pToolTip	-	
	// -> Return Value:		
	// -> Remarks:			
	void SetToolTips(CToolTipCtrl* pToolTip);
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	CImageList* GetImageList() const;
	
	// -> Parameters:		pImageList	-	
	// -> Return Value:		
	// -> Remarks:			
	BOOL SetImageList(CImageList* pImageList);
	
	// -> Parameters:		uBand	-	
	//						prc		-	
	// -> Return Value:		
	// -> Remarks:			
	void GetBandBorders(UINT uBand, LPRECT prc) const;
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	CPalette* GetPalette() const;
	
	// -> Parameters:		hPal	-	
	// -> Return Value:		
	// -> Remarks:			
	CPalette* SetPalette(HPALETTE hPal);
	
	// -> Parameters:		lpcs	-	
	// -> Return Value:		
	// -> Remarks:			
	BOOL GetColorScheme(COLORSCHEME* lpcs);
	
	// -> Parameters:		lpcs	-	
	// -> Return Value:		
	// -> Remarks:			
	void SetColorScheme(const COLORSCHEME* lpcs);

	// -> Parameters:		uBand	-	
	//						dwPos	-	
	// -> Return Value:		
	// -> Remarks:			
	void BeginDrag(UINT uBand, DWORD dwPos = (DWORD)-1);

	// -> Parameters:		uBand	-	
	// -> Return Value:		
	// -> Remarks:			
	BOOL DeleteBand(UINT uBand);

	// -> Parameters:		dwPos	-	
	// -> Return Value:		
	// -> Remarks:			
	void DragMove(DWORD dwPos = (DWORD)-1);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	void EndDrag();

	// -> Parameters:		prbht	-	
	// -> Return Value:		
	// -> Remarks:			
	int HitTest(RBHITTESTINFO* prbht);

	// -> Parameters:		uIndex	-	
	//						prbbi	-	
	// -> Return Value:		
	// -> Remarks:			
	BOOL InsertBand(UINT uIndex, REBARBANDINFO* prbbi);

	// -> Parameters:		uBand	-	
	// -> Return Value:		
	// -> Remarks:			
	void MaximizeBand(UINT uBand);

	// -> Parameters:		uBand	-	
	// -> Return Value:		
	// -> Remarks:			
	void MinimizeBand(UINT uBand);

	// -> Parameters:		uBand	-	
	//						fShow	-	
	// -> Return Value:		
	// -> Remarks:			
	BOOL ShowBand(UINT uBand, BOOL fShow = TRUE);

	// -> Parameters:		rect	-	
	// -> Return Value:		
	// -> Remarks:			
	BOOL SizeToRect(CRect& rect);

	// -> Parameters:		uFrom	-	
	//						uTo		-	
	// -> Return Value:		
	// -> Remarks:			
	BOOL MoveBand(UINT uFrom, UINT uTo);
};

//---------------------------------------------------------------------------
inline UINT CXTReBarCtrl::GetBandCount() const
	{ ASSERT(::IsWindow(m_hWnd)); return (UINT) ::SendMessage(m_hWnd, RB_GETBANDCOUNT, 0, 0L); }
//---------------------------------------------------------------------------
inline BOOL CXTReBarCtrl::GetBandInfo(UINT uBand, REBARBANDINFO* prbbi) const
	{ ASSERT(::IsWindow(m_hWnd)); return (BOOL) ::SendMessage(m_hWnd, RB_GETBANDINFO, uBand, (LPARAM)prbbi); }
//---------------------------------------------------------------------------
inline UINT CXTReBarCtrl::GetBarHeight() const
	{ ASSERT(::IsWindow(m_hWnd)); return (UINT) ::SendMessage(m_hWnd, RB_GETBARHEIGHT, 0, 0L); }
//---------------------------------------------------------------------------
inline BOOL CXTReBarCtrl::GetBarInfo(REBARINFO* prbi) const
	{ ASSERT(::IsWindow(m_hWnd)); return (BOOL) ::SendMessage(m_hWnd, RB_GETBARINFO, 0, (LPARAM)prbi); }
//---------------------------------------------------------------------------
inline COLORREF CXTReBarCtrl::GetBkColor() const
	{ ASSERT(::IsWindow(m_hWnd)); return (COLORREF) ::SendMessage(m_hWnd, RB_GETBKCOLOR, 0, 0L); }
//---------------------------------------------------------------------------
inline IDropTarget* CXTReBarCtrl::GetDropTarget() const
	{ ASSERT(::IsWindow(m_hWnd)); IDropTarget* pdt; ::SendMessage(m_hWnd, RB_GETDROPTARGET, 0, (LPARAM)&pdt); return pdt; }
//---------------------------------------------------------------------------
inline BOOL CXTReBarCtrl::GetRect(UINT uBand, LPRECT prc) const
	{ ASSERT(::IsWindow(m_hWnd)); return (BOOL) ::SendMessage(m_hWnd, RB_GETRECT, uBand, (LPARAM)prc); }
//---------------------------------------------------------------------------
inline UINT CXTReBarCtrl::GetRowCount() const
	{ ASSERT(::IsWindow(m_hWnd)); return (UINT) ::SendMessage(m_hWnd, RB_GETROWCOUNT, 0, 0L); }
//---------------------------------------------------------------------------
inline UINT CXTReBarCtrl::GetRowHeight(UINT uRow) const
	{ ASSERT(::IsWindow(m_hWnd)); return (UINT) ::SendMessage(m_hWnd, RB_GETROWHEIGHT, uRow, 0L); }
//---------------------------------------------------------------------------
inline COLORREF CXTReBarCtrl::GetTextColor() const
	{ ASSERT(::IsWindow(m_hWnd)); return (COLORREF) ::SendMessage(m_hWnd, RB_GETTEXTCOLOR, 0, 0L); }
//---------------------------------------------------------------------------
inline CToolTipCtrl* CXTReBarCtrl::GetToolTips() const
	{ ASSERT(::IsWindow(m_hWnd)); return (CToolTipCtrl*)CWnd::FromHandle((HWND)::SendMessage(m_hWnd, RB_GETTOOLTIPS, 0, 0L)); }
//---------------------------------------------------------------------------
inline int CXTReBarCtrl::IDToIndex(UINT uBandID) const
	{ ASSERT(::IsWindow(m_hWnd)); return (int) ::SendMessage(m_hWnd, RB_IDTOINDEX, uBandID, 0L); }
//---------------------------------------------------------------------------
inline BOOL CXTReBarCtrl::SetBandInfo(UINT uBand, REBARBANDINFO* prbbi)
	{ ASSERT(::IsWindow(m_hWnd)); return (BOOL) ::SendMessage(m_hWnd, RB_SETBANDINFO, uBand, (LPARAM)prbbi); }
//---------------------------------------------------------------------------
inline BOOL CXTReBarCtrl::SetBarInfo(REBARINFO* prbi)
	{ ASSERT(::IsWindow(m_hWnd)); return (BOOL) ::SendMessage(m_hWnd, RB_SETBARINFO, 0, (LPARAM)prbi); }
//---------------------------------------------------------------------------
inline COLORREF CXTReBarCtrl::SetBkColor(COLORREF clr)
	{ ASSERT(::IsWindow(m_hWnd)); return (COLORREF) ::SendMessage(m_hWnd, RB_SETBKCOLOR, 0, (LPARAM)clr); }
//---------------------------------------------------------------------------
inline CWnd* CXTReBarCtrl::SetOwner(CWnd* pWnd)
	{ ASSERT(::IsWindow(m_hWnd)); return CWnd::FromHandle((HWND)::SendMessage(m_hWnd, RB_SETPARENT, (WPARAM)pWnd->m_hWnd, 0L)); }
//---------------------------------------------------------------------------
inline COLORREF CXTReBarCtrl::SetTextColor(COLORREF clr)
	{ ASSERT(::IsWindow(m_hWnd)); return (COLORREF) ::SendMessage(m_hWnd, RB_SETTEXTCOLOR, 0, (LPARAM)clr); }
//---------------------------------------------------------------------------
inline void CXTReBarCtrl::SetToolTips(CToolTipCtrl* pToolTip)
	{ ASSERT(::IsWindow(m_hWnd)); ::SendMessage(m_hWnd, RB_SETTOOLTIPS, (WPARAM)pToolTip->m_hWnd, 0L); }
//---------------------------------------------------------------------------
inline void CXTReBarCtrl::GetBandBorders(UINT uBand, LPRECT prc) const
	{ ASSERT(::IsWindow(m_hWnd)); ::SendMessage(m_hWnd, RB_GETBANDBORDERS, uBand, (LPARAM)prc); }
//---------------------------------------------------------------------------
inline CPalette* CXTReBarCtrl::GetPalette() const
	{ ASSERT(::IsWindow(m_hWnd)); return CPalette::FromHandle((HPALETTE)::SendMessage(m_hWnd, RB_GETPALETTE, 0, 0L)); }
//---------------------------------------------------------------------------
inline CPalette* CXTReBarCtrl::SetPalette(HPALETTE hPal)
	{ ASSERT(::IsWindow(m_hWnd)); return CPalette::FromHandle((HPALETTE)::SendMessage(m_hWnd, RB_SETPALETTE, 0, (LPARAM)hPal)); }
//---------------------------------------------------------------------------
inline void CXTReBarCtrl::BeginDrag(UINT uBand, DWORD dwPos)
	{ ASSERT(::IsWindow(m_hWnd)); ::SendMessage(m_hWnd, RB_BEGINDRAG, uBand, dwPos); }
//---------------------------------------------------------------------------
inline BOOL CXTReBarCtrl::DeleteBand(UINT uBand)
	{ ASSERT(::IsWindow(m_hWnd)); return (BOOL) ::SendMessage(m_hWnd, RB_DELETEBAND, uBand, 0L); }
//---------------------------------------------------------------------------
inline void CXTReBarCtrl::DragMove(DWORD dwPos)
	{ ASSERT(::IsWindow(m_hWnd)); ::SendMessage(m_hWnd, RB_DRAGMOVE, 0, dwPos); }
//---------------------------------------------------------------------------
inline void CXTReBarCtrl::EndDrag()
	{ ASSERT(::IsWindow(m_hWnd)); ::SendMessage(m_hWnd, RB_ENDDRAG, 0, 0L); }
//---------------------------------------------------------------------------
inline int CXTReBarCtrl::HitTest(RBHITTESTINFO* prbht)
	{ ASSERT(::IsWindow(m_hWnd)); return (int) ::SendMessage(m_hWnd, RB_HITTEST, 0, (LPARAM)prbht); }
//---------------------------------------------------------------------------
inline BOOL CXTReBarCtrl::InsertBand(UINT uIndex, REBARBANDINFO* prbbi)
	{ ASSERT(::IsWindow(m_hWnd)); return (BOOL) ::SendMessage(m_hWnd, RB_INSERTBAND, uIndex, (LPARAM)prbbi); }
//---------------------------------------------------------------------------
inline void CXTReBarCtrl::MaximizeBand(UINT uBand)
	{ ASSERT(::IsWindow(m_hWnd)); ::SendMessage(m_hWnd, RB_MAXIMIZEBAND, uBand, 0L); }
//---------------------------------------------------------------------------
inline void CXTReBarCtrl::MinimizeBand(UINT uBand)
	{ ASSERT(::IsWindow(m_hWnd)); ::SendMessage(m_hWnd, RB_MINIMIZEBAND, uBand, 0L); }
//---------------------------------------------------------------------------
inline BOOL CXTReBarCtrl::ShowBand(UINT uBand, BOOL fShow)
	{ ASSERT(::IsWindow(m_hWnd)); return (BOOL) ::SendMessage(m_hWnd, RB_SHOWBAND, uBand, fShow); }
//---------------------------------------------------------------------------
inline BOOL CXTReBarCtrl::SizeToRect(CRect& rect)
	{ ASSERT(::IsWindow(m_hWnd)); return (BOOL) ::SendMessage(m_hWnd, RB_SIZETORECT, 0, (LPARAM)&rect); }
//---------------------------------------------------------------------------
inline BOOL CXTReBarCtrl::MoveBand(UINT uFrom, UINT uTo)
	{ ASSERT(::IsWindow(m_hWnd)); return (BOOL) ::SendMessage(m_hWnd, RB_MOVEBAND, uFrom, uTo); }
//---------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // #if !defined(__XTREBARCTRL_H__)
