// XTToolBarCtrl.h interface for the CXTToolBarCtrl class.
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

#if !defined(__XTTOOLBARCTRL_H__)
#define __XTTOOLBARCTRL_H__

/////////////////////////////////////////////////////////////////////////////
// The CXTToolBarCtrl class provides the functionality of the Windows toolbar 
// common control. This control (and therefore the CXTToolBarCtrl class) is available 
// only to programs running under Windows 95 and Windows NT version 3.51 and later.
/////////////////////////////////////////////////////////////////////////////
class _XT_EXT_CLASS CXTToolBarCtrl : public CToolBarCtrl
{
	DECLARE_DYNAMIC(CXTToolBarCtrl)

public:
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	CXTToolBarCtrl();
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual ~CXTToolBarCtrl();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	DWORD GetButtonSize() const;

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	CImageList* GetDisabledImageList() const;

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	CImageList* GetHotImageList() const;

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	CImageList* GetImageList() const;

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	DWORD GetStyle() const;

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	int GetMaxTextRows() const;

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	BOOL IsButtonHighlighted(int nID) const;

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	BOOL SetButtonWidth(int cxMin, int cxMax);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	CImageList* SetDisabledImageList(CImageList* pImageList);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	CImageList* SetHotImageList(CImageList* pImageList);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	CImageList* SetImageList(CImageList* pImageList);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	HRESULT GetDropTarget(IDropTarget** ppDropTarget) const;;

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	BOOL SetIndent(int iIndent);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	BOOL SetMaxTextRows(int iMaxRows);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	void SetStyle(DWORD dwStyle);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	BOOL GetButtonInfo(int nID, TBBUTTONINFO* ptbbi) const;

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	BOOL SetButtonInfo(int nID, TBBUTTONINFO* ptbbi);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	DWORD SetDrawTextFlags(DWORD dwMask, DWORD dwDTFlags);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	BOOL GetAnchorHighlight() const;

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	BOOL SetAnchorHighlight(BOOL fAnchor = TRUE);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	int GetHotItem() const;

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	int SetHotItem(int nHot);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	void GetInsertMark(TBINSERTMARK* ptbim) const;

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	void SetInsertMark(TBINSERTMARK* ptbim);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	BOOL GetMaxSize(LPSIZE pSize) const;

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	BOOL InsertMarkHitTest(LPPOINT ppt, LPTBINSERTMARK ptbim) const;

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	DWORD GetExtendedStyle() const;

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	DWORD SetExtendedStyle(DWORD dwExStyle);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	COLORREF GetInsertMarkColor() const;

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	COLORREF SetInsertMarkColor(COLORREF clrNew);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	BOOL MapAccelerator(TCHAR chAccel, UINT* pIDBtn);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	BOOL MarkButton(int nID, BOOL bHighlight = TRUE);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	BOOL MoveButton(UINT nOldPos, UINT nNewPos);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	int HitTest(LPPOINT ppt) const;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXTToolBarCtrl)
	//}}AFX_VIRTUAL

protected:
	// Generated message map functions
	//{{AFX_MSG(CXTToolBarCtrl)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

//---------------------------------------------------------------------------
inline DWORD CXTToolBarCtrl::GetButtonSize() const
	{ ASSERT(::IsWindow(m_hWnd)); return (DWORD) ::SendMessage(m_hWnd, TB_GETBUTTONSIZE, 0, 0L); }
//---------------------------------------------------------------------------
inline CImageList* CXTToolBarCtrl::GetDisabledImageList() const
	{ ASSERT(::IsWindow(m_hWnd)); return CImageList::FromHandle((HIMAGELIST) ::SendMessage(m_hWnd, TB_GETDISABLEDIMAGELIST, 0, 0)); }
//---------------------------------------------------------------------------
inline CImageList* CXTToolBarCtrl::GetHotImageList() const
	{ ASSERT(::IsWindow(m_hWnd)); return CImageList::FromHandle((HIMAGELIST) ::SendMessage(m_hWnd, TB_GETHOTIMAGELIST, 0, 0)); }
//---------------------------------------------------------------------------
inline CImageList* CXTToolBarCtrl::GetImageList() const
	{ ASSERT(::IsWindow(m_hWnd)); return CImageList::FromHandle((HIMAGELIST) ::SendMessage(m_hWnd, TB_GETIMAGELIST, 0, 0)); }
//---------------------------------------------------------------------------
inline DWORD CXTToolBarCtrl::GetStyle() const
	{ ASSERT(::IsWindow(m_hWnd)); return (DWORD) ::SendMessage(m_hWnd, TB_GETSTYLE, 0, 0L); }
//---------------------------------------------------------------------------
inline int CXTToolBarCtrl::GetMaxTextRows() const
	{ ASSERT(::IsWindow(m_hWnd)); return (INT) ::SendMessage(m_hWnd, TB_GETTEXTROWS, 0, 0L); }
//---------------------------------------------------------------------------
inline BOOL CXTToolBarCtrl::IsButtonHighlighted(int nID) const
	{ ASSERT(::IsWindow(m_hWnd)); return (BOOL) ::SendMessage(m_hWnd, TB_ISBUTTONHIGHLIGHTED, nID, 0); }
//---------------------------------------------------------------------------
inline BOOL CXTToolBarCtrl::SetButtonWidth(int cxMin, int cxMax)
	{ ASSERT(::IsWindow(m_hWnd)); return (BOOL) ::SendMessage(m_hWnd, TB_SETBUTTONWIDTH, 0, MAKELPARAM(cxMin, cxMax)); }
//---------------------------------------------------------------------------
inline CImageList* CXTToolBarCtrl::SetDisabledImageList(CImageList* pImageList)
	{ ASSERT(::IsWindow(m_hWnd)); return CImageList::FromHandle((HIMAGELIST) ::SendMessage(m_hWnd, TB_SETDISABLEDIMAGELIST, 0, (LPARAM)pImageList->GetSafeHandle())); }
//---------------------------------------------------------------------------
inline CImageList* CXTToolBarCtrl::SetHotImageList(CImageList* pImageList)
	{ ASSERT(::IsWindow(m_hWnd)); return CImageList::FromHandle((HIMAGELIST) ::SendMessage(m_hWnd, TB_SETHOTIMAGELIST, 0, (LPARAM)pImageList->GetSafeHandle())); }
//---------------------------------------------------------------------------
inline CImageList* CXTToolBarCtrl::SetImageList(CImageList* pImageList)
	{ ASSERT(::IsWindow(m_hWnd)); return CImageList::FromHandle((HIMAGELIST) ::SendMessage(m_hWnd, TB_SETIMAGELIST, 0, (LPARAM)pImageList->GetSafeHandle())); }
//---------------------------------------------------------------------------
inline BOOL CXTToolBarCtrl::SetIndent(int iIndent)
	{ ASSERT(::IsWindow(m_hWnd)); return (BOOL) ::SendMessage(m_hWnd, TB_SETINDENT, iIndent, 0L); }
//---------------------------------------------------------------------------
inline BOOL CXTToolBarCtrl::SetMaxTextRows(int iMaxRows)
	{ ASSERT(::IsWindow(m_hWnd)); return (BOOL) ::SendMessage(m_hWnd, TB_SETMAXTEXTROWS, iMaxRows, 0L); }
//---------------------------------------------------------------------------
inline void CXTToolBarCtrl::SetStyle(DWORD dwStyle)
	{ ASSERT(::IsWindow(m_hWnd)); ::SendMessage(m_hWnd, TB_SETSTYLE, 0, dwStyle); }
//---------------------------------------------------------------------------
inline BOOL CXTToolBarCtrl::GetButtonInfo(int nID, TBBUTTONINFO* ptbbi) const
	{ ASSERT(::IsWindow(m_hWnd)); return (BOOL) ::SendMessage(m_hWnd, TB_GETBUTTONINFO, nID, (LPARAM)ptbbi); }
//---------------------------------------------------------------------------
inline BOOL CXTToolBarCtrl::SetButtonInfo(int nID, TBBUTTONINFO* ptbbi)
	{ ASSERT(::IsWindow(m_hWnd)); return (BOOL) ::SendMessage(m_hWnd, TB_SETBUTTONINFO, nID, (LPARAM)ptbbi); }
//---------------------------------------------------------------------------
inline DWORD CXTToolBarCtrl::SetDrawTextFlags(DWORD dwMask, DWORD dwDTFlags)
	{ ASSERT(::IsWindow(m_hWnd)); return (DWORD) ::SendMessage(m_hWnd, TB_SETDRAWTEXTFLAGS, dwMask, dwDTFlags); }
//---------------------------------------------------------------------------
inline BOOL CXTToolBarCtrl::GetAnchorHighlight() const
	{ ASSERT(::IsWindow(m_hWnd)); return (BOOL) ::SendMessage(m_hWnd, TB_GETANCHORHIGHLIGHT, 0, 0); }
//---------------------------------------------------------------------------
inline BOOL CXTToolBarCtrl::SetAnchorHighlight(BOOL fAnchor)
	{ ASSERT(::IsWindow(m_hWnd)); return (BOOL) ::SendMessage(m_hWnd, TB_SETANCHORHIGHLIGHT, fAnchor, 0); }
//---------------------------------------------------------------------------
inline int CXTToolBarCtrl::GetHotItem() const
	{ ASSERT(::IsWindow(m_hWnd)); return (int) ::SendMessage(m_hWnd, TB_GETHOTITEM, 0, 0); }
//---------------------------------------------------------------------------
inline int CXTToolBarCtrl::SetHotItem(int nHot)
	{ ASSERT(::IsWindow(m_hWnd)); return (int) ::SendMessage(m_hWnd, TB_SETHOTITEM, nHot, 0); }
//---------------------------------------------------------------------------
inline void CXTToolBarCtrl::GetInsertMark(TBINSERTMARK* ptbim) const
	{ ASSERT(::IsWindow(m_hWnd)); ::SendMessage(m_hWnd, TB_GETINSERTMARK, 0, (LPARAM)ptbim); }
//---------------------------------------------------------------------------
inline void CXTToolBarCtrl::SetInsertMark(TBINSERTMARK* ptbim)
	{ ASSERT(::IsWindow(m_hWnd)); ::SendMessage(m_hWnd, TB_SETINSERTMARK, 0, (LPARAM)ptbim); }
//---------------------------------------------------------------------------
inline BOOL CXTToolBarCtrl::GetMaxSize(LPSIZE pSize) const
	{ ASSERT(::IsWindow(m_hWnd)); return (BOOL) ::SendMessage(m_hWnd, TB_GETMAXSIZE, 0, (LPARAM)pSize); }
//---------------------------------------------------------------------------
inline BOOL CXTToolBarCtrl::InsertMarkHitTest(LPPOINT ppt, LPTBINSERTMARK ptbim) const
	{ ASSERT(::IsWindow(m_hWnd)); return (BOOL) ::SendMessage(m_hWnd, TB_INSERTMARKHITTEST, (WPARAM)ppt, (LPARAM)ptbim); }
//---------------------------------------------------------------------------
inline DWORD CXTToolBarCtrl::GetExtendedStyle() const
	{ ASSERT(::IsWindow(m_hWnd)); return (DWORD) ::SendMessage(m_hWnd, TB_GETEXTENDEDSTYLE, 0, 0L); }
//---------------------------------------------------------------------------
inline DWORD CXTToolBarCtrl::SetExtendedStyle(DWORD dwExStyle)
	{ ASSERT(::IsWindow(m_hWnd)); return (DWORD) ::SendMessage(m_hWnd, TB_SETEXTENDEDSTYLE, 0, dwExStyle); }
//---------------------------------------------------------------------------
inline COLORREF CXTToolBarCtrl::GetInsertMarkColor() const
	{ ASSERT(::IsWindow(m_hWnd)); return (COLORREF) ::SendMessage(m_hWnd, TB_GETINSERTMARKCOLOR, 0, 0); }
//---------------------------------------------------------------------------
inline COLORREF CXTToolBarCtrl::SetInsertMarkColor(COLORREF clrNew)
	{ ASSERT(::IsWindow(m_hWnd)); return (COLORREF) ::SendMessage(m_hWnd, TB_SETINSERTMARKCOLOR, 0, (LPARAM) clrNew); }
//---------------------------------------------------------------------------
inline BOOL CXTToolBarCtrl::MapAccelerator(TCHAR chAccel, UINT* pIDBtn)
	{ ASSERT(::IsWindow(m_hWnd)); return (BOOL) ::SendMessage(m_hWnd, TB_MAPACCELERATOR, (WPARAM)chAccel, (LPARAM)pIDBtn); }
//---------------------------------------------------------------------------
inline BOOL CXTToolBarCtrl::MarkButton(int nID, BOOL bHighlight)
	{ ASSERT(::IsWindow(m_hWnd)); return (BOOL) ::SendMessage(m_hWnd, TB_MARKBUTTON, nID, MAKELPARAM(bHighlight, 0)); }
//---------------------------------------------------------------------------
inline BOOL CXTToolBarCtrl::MoveButton(UINT nOldPos, UINT nNewPos)
	{ ASSERT(::IsWindow(m_hWnd)); return (BOOL) ::SendMessage(m_hWnd, TB_MOVEBUTTON, nOldPos, nNewPos); }
//---------------------------------------------------------------------------
inline int CXTToolBarCtrl::HitTest(LPPOINT ppt) const
	{ ASSERT(::IsWindow(m_hWnd)); return (int) ::SendMessage(m_hWnd, TB_HITTEST, 0, (LPARAM)ppt); }
//---------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // #if !defined(__XTTOOLBARCTRL_H__)
