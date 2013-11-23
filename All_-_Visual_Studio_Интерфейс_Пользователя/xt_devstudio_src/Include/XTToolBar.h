// XTToolBar.h interface for the CXTToolBar class.
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

#if !defined(__XTTOOLBAR_H__)
#define __XTTOOLBAR_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "XTToolBarCtrl.h"
#include "XTControlBar.h"

/////////////////////////////////////////////////////////////////////////////
// CXTToolBar class
/////////////////////////////////////////////////////////////////////////////
class _XT_EXT_CLASS CXTToolBar : public CXTControlBar
{

	DECLARE_DYNAMIC(CXTToolBar)

public:
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Constructor - handles default initialization
	CXTToolBar();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Destructor - handles clean up.
	virtual ~CXTToolBar();

protected:

	BOOL				m_bDelayedButtonLayout;	// used to manage when button layout should be done
	CSize				m_sizeImage;			// current image size
	CSize				m_sizeButton;			// current button size
	HRSRC				m_hRsrcImageWell;		// handle to loaded resource for image well
	HINSTANCE			m_hInstImageWell;		// instance handle to load image well from
	HBITMAP				m_hbmImageWell;			// contains color mapped button images
	CMapStringToPtr*	m_pStringMap;			// used as CMapStringToUInt
	BOOL				m_bCustomBar;			// 
	BOOL				m_bNoEntry;				// 
	BOOL				m_bDisabledColor;		// 
	CRect				m_rcOldPos;				// 
	CString				m_strSubKey;			// 
	CString				m_strValueName;			// 

	CList<XT_DROPDOWNBUTTON*, XT_DROPDOWNBUTTON*> m_dropDownButtons;
	CList<TBBUTTON*, TBBUTTON*>	m_tbButtons;

public:

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	void SetSizes(SIZE sizeButton, SIZE sizeImage);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	void SetHeight(int cyHeight);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	BOOL LoadToolBar(LPCTSTR lpszResourceName);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	BOOL LoadBitmap(LPCTSTR lpszResourceName);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	BOOL SetBitmap(HBITMAP hbmImageWell);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	BOOL SetButtons(const UINT* lpIDArray, int nIDCount);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	int CommandToIndex(UINT nIDFind) const;

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	UINT GetItemID(int nIndex) const;

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	UINT GetButtonStyle(int nIndex) const;

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	void SetButtonStyle(int nIndex, UINT nStyle);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	void GetButtonInfo(int nIndex, UINT& nID, UINT& nStyle, int& iImage) const;

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	void SetButtonInfo(int nIndex, UINT nID, UINT nStyle, int iImage);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	BOOL SetButtonText(int nIndex, LPCTSTR lpszText);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	CString GetButtonText(int nIndex) const;

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	void GetButtonText(int nIndex, CString& rString) const;

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	BOOL AddReplaceBitmap(HBITMAP hbmImageWell);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	void GetButton(int nIndex, TBBUTTON* pButton) const;

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	void SetButton(int nIndex, TBBUTTON* pButton);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	CSize CalcLayout(DWORD nMode, int nLength = -1);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	CSize CalcSize(TBBUTTON* pData, int nCount);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	int WrapToolBar(TBBUTTON* pData, int nCount, int nWidth);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	void SizeToolBar(TBBUTTON* pData, int nCount, int nLength, BOOL bVert = FALSE);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	void Layout();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	BOOL AddDropDownButton(UINT nIDButton, UINT nIDMenu=0, BOOL bArrow=TRUE);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	XT_DROPDOWNBUTTON* FindDropDownButton(UINT nID);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	void SaveState();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	void RestoreState();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	void LoadButtonInfo();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual BOOL Create(CWnd* pParentWnd,
		DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_TOP,
		UINT nID = AFX_IDW_TOOLBAR);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual BOOL CreateEx(CWnd* pParentWnd, DWORD dwCtrlStyle = TBSTYLE_FLAT,
		DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP,
		CRect rcBorders = CRect(0, 0, 0, 0),
		UINT nID = AFX_IDW_TOOLBAR);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual void SetOwner(CWnd* pOwnerWnd);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual void GetItemRect(int nIndex, LPRECT lpRect) const;

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual void DrawSeparators(CDC* pDC);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual BOOL DrawItem(CDC* pDC, LPNMCUSTOMDRAW lpNMCD);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual void EraseWrappedSeparators(CDC* pDC);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual CSize CalcFixedLayout(BOOL bStretch, BOOL bHorz);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual CSize CalcDynamicLayout(int nLength, DWORD nMode);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual int OnToolHitTest(CPoint point, TOOLINFO* pTI) const;

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual void OnBarStyleChange(DWORD dwOldStyle, DWORD dwNewStyle);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual CSize GetButtonSize(TBBUTTON* pData, int iButton);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual void OnDropDownButton(NMTOOLBAR* pNMTB, UINT nID, CRect rect);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual BOOL InsertControl(CWnd* pWnd);

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	void SetCustomBar(BOOL bCustomBar=TRUE);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	BOOL GetCustomBar();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	void ColorizeDisabledItems(BOOL bDisabledColor=TRUE);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	BOOL LoadToolBar(UINT nIDResource);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	BOOL LoadBitmap(UINT nIDResource);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	CXTToolBarCtrl& GetToolBarCtrl() const;

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	BOOL EnableButton(int nID, BOOL bEnable);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	BOOL CheckButton(int nID, BOOL bCheck);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	BOOL PressButton(int nID, BOOL bPress);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	BOOL HideButton(int nID, BOOL bHide);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	BOOL Indeterminate(int nID, BOOL bIndeterminate);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	BOOL IsButtonEnabled(int nID) const;

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	BOOL IsButtonChecked(int nID) const;

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	BOOL IsButtonPressed(int nID) const;

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	BOOL IsButtonHidden(int nID) const;

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	BOOL IsButtonIndeterminate(int nID) const;

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	BOOL SetState(int nID, UINT nState);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	int GetState(int nID) const;

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	BOOL AddButtons(int nNumButtons, LPTBBUTTON lpButtons);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	BOOL InsertButton(int nIndex, LPTBBUTTON lpButton);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	BOOL DeleteButton(int nIndex);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	int GetButtonCount() const;

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	void Customize();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	int AddStrings(LPCTSTR lpszStrings);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	void SetButtonStructSize(int nSize);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	BOOL SetButtonSize(CSize size);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	BOOL SetBitmapSize(CSize size);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	void AutoSize();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	CToolTipCtrl* GetToolTips() const;

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	void SetToolTips(CToolTipCtrl* pTip);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	void SetRows(int nRows, BOOL bLarger, LPRECT lpRect);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	int GetRows() const;

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	BOOL SetCmdID(int nIndex, UINT nID);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	UINT GetBitmapFlags() const;

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	BOOL SetIndent(int indent);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	HIMAGELIST GetImageList() const;

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	HIMAGELIST SetImageList(HIMAGELIST hImgList);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	int GetBitmap(UINT nIdButton) const;

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	DWORD SetExtendedStyle(DWORD dwStyle);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	BOOL GetRect(UINT nIdButton, RECT& rc) const;

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	DWORD GetToolbarStyle() const;

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	void SetToolbarStyle(DWORD dwStyle);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	int HitTest(CPoint p) const;

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	int GetHotItem() const;

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	void SetHotItem(int iHot);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	BOOL MapAccelerator(TCHAR ch, UINT& nID) const;

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	CSize GetPadding() const;

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	CSize SetPadding(CSize size);

protected:
	//{{AFX_VIRTUAL(CXTToolBar)
	public:
	virtual void OnPaint();
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CXTToolBar)
	afx_msg UINT OnNcHitTest(CPoint point);
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp);
	afx_msg void OnWindowPosChanging(WINDOWPOS FAR* lpwndpos);
	afx_msg void OnSysColorChange();
	afx_msg BOOL OnNcCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	//}}AFX_MSG

	afx_msg LRESULT OnSetButtonSize(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSetBitmapSize(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnPreserveZeroBorderHelper(WPARAM wParam, LPARAM lParam);
	afx_msg void OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnToolBarBtnDropDown(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnToolBarBeginAdjust(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnToolBarBeginDrag(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnToolBarCustomHelp(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnToolBarEndAdjust(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnToolBarEndDrag(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnToolBarGetButtonInfo(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnToolBarQueryDelete(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnToolBarQueryInsert(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnToolBarReset(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnToolBarChange(NMHDR* pNMHDR, LRESULT* pResult);

	DECLARE_MESSAGE_MAP()

	LRESULT OnSetSizeHelper(CSize& size, LPARAM lParam);
};

//---------------------------------------------------------------------------
inline void CXTToolBar::SetCustomBar(BOOL bCustomBar)
	{ ASSERT(::IsWindow(m_hWnd)); m_bCustomBar = bCustomBar; }
//---------------------------------------------------------------------------
inline BOOL CXTToolBar::GetCustomBar()
	{ ASSERT(::IsWindow(m_hWnd)); return m_bCustomBar; }
//---------------------------------------------------------------------------
inline void CXTToolBar::ColorizeDisabledItems(BOOL bDisabledColor)
	{ ASSERT(::IsWindow(m_hWnd)); m_bDisabledColor = bDisabledColor; }
//---------------------------------------------------------------------------
inline BOOL CXTToolBar::LoadToolBar(UINT nIDResource)
	{ ASSERT(::IsWindow(m_hWnd)); return LoadToolBar(MAKEINTRESOURCE(nIDResource)); }
//---------------------------------------------------------------------------
inline BOOL CXTToolBar::LoadBitmap(UINT nIDResource)
	{ ASSERT(::IsWindow(m_hWnd)); return LoadBitmap(MAKEINTRESOURCE(nIDResource)); }
//---------------------------------------------------------------------------
inline CXTToolBarCtrl& CXTToolBar::GetToolBarCtrl() const
	{ ASSERT(::IsWindow(m_hWnd)); return *(CXTToolBarCtrl*)this; }
//---------------------------------------------------------------------------
inline BOOL CXTToolBar::EnableButton(int nID, BOOL bEnable)
	{ ASSERT(::IsWindow(m_hWnd)); return (BOOL) ::SendMessage(m_hWnd, TB_ENABLEBUTTON, nID, MAKELPARAM(bEnable, 0)); }
//---------------------------------------------------------------------------
inline BOOL CXTToolBar::CheckButton(int nID, BOOL bCheck)
	{ ASSERT(::IsWindow(m_hWnd)); return (BOOL) ::SendMessage(m_hWnd, TB_CHECKBUTTON, nID, MAKELPARAM(bCheck, 0)); }
//---------------------------------------------------------------------------
inline BOOL CXTToolBar::PressButton(int nID, BOOL bPress)
	{ ASSERT(::IsWindow(m_hWnd)); return (BOOL) ::SendMessage(m_hWnd, TB_PRESSBUTTON, nID, MAKELPARAM(bPress, 0)); }
//---------------------------------------------------------------------------
inline BOOL CXTToolBar::HideButton(int nID, BOOL bHide)
	{ ASSERT(::IsWindow(m_hWnd)); return (BOOL) ::SendMessage(m_hWnd, TB_HIDEBUTTON, nID, MAKELPARAM(bHide, 0)); }
//---------------------------------------------------------------------------
inline BOOL CXTToolBar::Indeterminate(int nID, BOOL bIndeterminate)
	{ ASSERT(::IsWindow(m_hWnd)); return (BOOL) ::SendMessage(m_hWnd, TB_INDETERMINATE, nID, MAKELPARAM(bIndeterminate, 0)); }
//---------------------------------------------------------------------------
inline BOOL CXTToolBar::IsButtonEnabled(int nID) const
	{ ASSERT(::IsWindow(m_hWnd)); return (BOOL) ::SendMessage(m_hWnd, TB_ISBUTTONENABLED, nID, 0); }
//---------------------------------------------------------------------------
inline BOOL CXTToolBar::IsButtonChecked(int nID) const
	{ ASSERT(::IsWindow(m_hWnd)); return (BOOL) ::SendMessage(m_hWnd, TB_ISBUTTONCHECKED, nID, 0); }
//---------------------------------------------------------------------------
inline BOOL CXTToolBar::IsButtonPressed(int nID) const
	{ ASSERT(::IsWindow(m_hWnd)); return (BOOL) ::SendMessage(m_hWnd, TB_ISBUTTONPRESSED, nID, 0); }
//---------------------------------------------------------------------------
inline BOOL CXTToolBar::IsButtonHidden(int nID) const
	{ ASSERT(::IsWindow(m_hWnd)); return (BOOL) ::SendMessage(m_hWnd, TB_ISBUTTONHIDDEN, nID, 0); }
//---------------------------------------------------------------------------
inline BOOL CXTToolBar::IsButtonIndeterminate(int nID) const
	{ ASSERT(::IsWindow(m_hWnd)); return (BOOL) ::SendMessage(m_hWnd, TB_ISBUTTONINDETERMINATE, nID, 0); }
//---------------------------------------------------------------------------
inline BOOL CXTToolBar::SetState(int nID, UINT nState)
	{ ASSERT(::IsWindow(m_hWnd)); return (BOOL) ::SendMessage(m_hWnd, TB_SETSTATE, nID, MAKELPARAM(nState, 0)); }
//---------------------------------------------------------------------------
inline int CXTToolBar::GetState(int nID) const
	{ ASSERT(::IsWindow(m_hWnd)); return (int) ::SendMessage(m_hWnd, TB_GETSTATE, nID, 0L); }
//---------------------------------------------------------------------------
inline BOOL CXTToolBar::AddButtons(int nNumButtons, LPTBBUTTON lpButtons)
	{ ASSERT(::IsWindow(m_hWnd)); return (BOOL) ::SendMessage(m_hWnd, TB_ADDBUTTONS, nNumButtons, (LPARAM)lpButtons); }
//---------------------------------------------------------------------------
inline BOOL CXTToolBar::InsertButton(int nIndex, LPTBBUTTON lpButton)
	{ ASSERT(::IsWindow(m_hWnd)); return (BOOL) ::SendMessage(m_hWnd, TB_INSERTBUTTON, nIndex, (LPARAM)lpButton); }
//---------------------------------------------------------------------------
inline BOOL CXTToolBar::DeleteButton(int nIndex)
	{ ASSERT(::IsWindow(m_hWnd)); return (BOOL) ::SendMessage(m_hWnd, TB_DELETEBUTTON, nIndex, 0); }
//---------------------------------------------------------------------------
inline int CXTToolBar::GetButtonCount() const
	{ ASSERT(::IsWindow(m_hWnd)); return (int) ::SendMessage(m_hWnd, TB_BUTTONCOUNT, 0, 0L); }
//---------------------------------------------------------------------------
inline void CXTToolBar::Customize()
	{ ASSERT(::IsWindow(m_hWnd)); ::SendMessage(m_hWnd, TB_CUSTOMIZE, 0, 0L); }
//---------------------------------------------------------------------------
inline int CXTToolBar::AddStrings(LPCTSTR lpszStrings)
	{ ASSERT(::IsWindow(m_hWnd)); return (int) ::SendMessage(m_hWnd, TB_ADDSTRING, 0, (LPARAM)lpszStrings); }
//---------------------------------------------------------------------------
inline void CXTToolBar::SetButtonStructSize(int nSize)
	{ ASSERT(::IsWindow(m_hWnd)); ::SendMessage(m_hWnd, TB_BUTTONSTRUCTSIZE, nSize, 0L); }
//---------------------------------------------------------------------------
inline BOOL CXTToolBar::SetButtonSize(CSize size)
	{ ASSERT(::IsWindow(m_hWnd)); return (BOOL) ::SendMessage(m_hWnd, TB_SETBUTTONSIZE, 0, MAKELPARAM(size.cx, size.cy)); }
//---------------------------------------------------------------------------
inline BOOL CXTToolBar::SetBitmapSize(CSize size)
	{ ASSERT(::IsWindow(m_hWnd)); return (BOOL) ::SendMessage(m_hWnd, TB_SETBITMAPSIZE, 0, MAKELPARAM(size.cx, size.cy)); }
//---------------------------------------------------------------------------
inline void CXTToolBar::AutoSize()
	{ ASSERT(::IsWindow(m_hWnd)); ::SendMessage(m_hWnd, TB_AUTOSIZE, 0, 0L); }
//---------------------------------------------------------------------------
inline CToolTipCtrl* CXTToolBar::GetToolTips() const
	{ ASSERT(::IsWindow(m_hWnd)); return (CToolTipCtrl*)CWnd::FromHandle((HWND)::SendMessage(m_hWnd, TB_GETTOOLTIPS, 0, 0L)); }
//---------------------------------------------------------------------------
inline void CXTToolBar::SetToolTips(CToolTipCtrl* pTip)
	{ ASSERT(::IsWindow(m_hWnd)); ::SendMessage(m_hWnd, TB_SETTOOLTIPS, (WPARAM)pTip->GetSafeHwnd(), 0L); }
//---------------------------------------------------------------------------
inline void CXTToolBar::SetRows(int nRows, BOOL bLarger, LPRECT lpRect)
	{ ASSERT(::IsWindow(m_hWnd)); ::SendMessage(m_hWnd, TB_SETROWS, MAKELPARAM(nRows, bLarger), (LPARAM)lpRect); }
//---------------------------------------------------------------------------
inline int CXTToolBar::GetRows() const
	{ ASSERT(::IsWindow(m_hWnd)); return (int) ::SendMessage(m_hWnd, TB_GETROWS, 0, 0L); }
//---------------------------------------------------------------------------
inline BOOL CXTToolBar::SetCmdID(int nIndex, UINT nID)
	{ ASSERT(::IsWindow(m_hWnd)); return (BOOL) ::SendMessage(m_hWnd, TB_SETCMDID, nIndex, nID); }
//---------------------------------------------------------------------------
inline UINT CXTToolBar::GetBitmapFlags() const
	{ ASSERT(::IsWindow(m_hWnd)); return (UINT) ::SendMessage(m_hWnd, TB_GETBITMAPFLAGS, 0, 0L); }
//---------------------------------------------------------------------------
inline BOOL CXTToolBar::SetIndent(int indent)
	{ ASSERT(::IsWindow(m_hWnd)); return (BOOL) ::SendMessage(m_hWnd, TB_SETINDENT, indent, 0L); }
//---------------------------------------------------------------------------
inline HIMAGELIST CXTToolBar::GetImageList() const
	{ ASSERT(::IsWindow(m_hWnd)); return (HIMAGELIST) ::SendMessage(m_hWnd, TB_GETIMAGELIST, 0, 0L); }
//---------------------------------------------------------------------------
inline HIMAGELIST CXTToolBar::SetImageList(HIMAGELIST hImgList)
	{ ASSERT(::IsWindow(m_hWnd)); return (HIMAGELIST) ::SendMessage(m_hWnd, TB_SETIMAGELIST, 0, (LPARAM)hImgList); }
//---------------------------------------------------------------------------
inline int CXTToolBar::GetBitmap(UINT nIdButton) const
	{ ASSERT(::IsWindow(m_hWnd)); return (int) ::SendMessage(m_hWnd, TB_GETBITMAP, nIdButton, 0L); }
//---------------------------------------------------------------------------
inline DWORD CXTToolBar::SetExtendedStyle(DWORD dwStyle)
	{ ASSERT(::IsWindow(m_hWnd)); return (DWORD) ::SendMessage(m_hWnd, TB_SETEXTENDEDSTYLE, 0, dwStyle); }
//---------------------------------------------------------------------------
inline BOOL CXTToolBar::GetRect(UINT nIdButton, RECT& rc) const
	{ ASSERT(::IsWindow(m_hWnd)); return (BOOL) ::SendMessage(m_hWnd, TB_GETRECT, nIdButton, (LPARAM)&rc); }
//---------------------------------------------------------------------------
inline DWORD CXTToolBar::GetToolbarStyle() const
	{ ASSERT(::IsWindow(m_hWnd)); return (DWORD) ::SendMessage(m_hWnd, TB_GETSTYLE, 0, 0L); }
//---------------------------------------------------------------------------
inline void CXTToolBar::SetToolbarStyle(DWORD dwStyle)
	{ ASSERT(::IsWindow(m_hWnd)); ::SendMessage(m_hWnd, TB_SETSTYLE, 0, dwStyle); }
//---------------------------------------------------------------------------
inline int CXTToolBar::HitTest(CPoint p) const
	{ ASSERT(::IsWindow(m_hWnd)); return (int) ::SendMessage(m_hWnd, TB_HITTEST, 0, (LPARAM)&p); }
//---------------------------------------------------------------------------
inline int CXTToolBar::GetHotItem() const
	{ ASSERT(::IsWindow(m_hWnd)); return (int) ::SendMessage(m_hWnd, TB_GETHOTITEM, 0, 0L); }
//---------------------------------------------------------------------------
inline void CXTToolBar::SetHotItem(int iHot)
	{ ASSERT(::IsWindow(m_hWnd)); ::SendMessage(m_hWnd, TB_SETHOTITEM, iHot, 0L); }
//---------------------------------------------------------------------------
inline BOOL CXTToolBar::MapAccelerator(TCHAR ch, UINT& nID) const
	{ ASSERT(::IsWindow(m_hWnd)); return (BOOL) ::SendMessage(m_hWnd, TB_MAPACCELERATOR, (WPARAM)ch, (LPARAM)&nID); }
//---------------------------------------------------------------------------
inline CSize CXTToolBar::GetPadding() const
	{ ASSERT(::IsWindow(m_hWnd)); return (CSize) ::SendMessage(m_hWnd, TB_GETPADDING, 0, 0L); }
//---------------------------------------------------------------------------
inline CSize CXTToolBar::SetPadding(CSize size) 
	{ ASSERT(::IsWindow(m_hWnd)); return (CSize) ::SendMessage(m_hWnd, TB_SETPADDING, 0, MAKELPARAM(size.cx,size.cy)); }
//---------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // #if !defined(__XTTOOLBAR_H__)

