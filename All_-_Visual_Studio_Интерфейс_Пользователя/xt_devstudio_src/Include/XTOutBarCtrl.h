// XTOutBarCtrl.h interface for the CXTOutBarCtrl class.
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

#if !defined(__XTOUTBARCTRL_H__)
#define __XTOUTBARCTRL_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "XTCoolMenu.h"

/////////////////////////////////////////////////////////////////////////////
// CXTOutBarCtrl window
/////////////////////////////////////////////////////////////////////////////
class _XT_EXT_CLASS CXTOutBarCtrl : public CWnd
{
	DECLARE_DYNCREATE(CXTOutBarCtrl)

public:

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Constructor - handles default initialization.
	CXTOutBarCtrl();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Destructor - handles cleanup and de-allocation.
	virtual ~CXTOutBarCtrl();

protected:

	int			m_nFolderHeight;
	int			m_nSelFolder;
	int			m_nFolderHilighted;
	int			m_nItemHilighted;
	int			m_nLastFolderSelected;
	int			m_nLastItemSelected;
	int			m_nFirstItem;
	int			m_nIconSpacingLarge;
	int			m_nIconSpacingSmall;
	int			m_nHitInternal1;
	int			m_nHitInternal2;
	int			m_nLastDragItemDraw;
	int			m_nLastDragItemDrawType;
	int			m_nSelAnimCount;
	int			m_nSelAnimTiming;
	int			m_nAnimationTickCount;
	BOOL		m_bUpArrow;
	BOOL		m_bDownArrow;
	BOOL		m_bUpPressed;
	BOOL		m_bDownPressed;
	BOOL		m_bLooping;
	BOOL		m_bPressedHighlight;
	CPen		m_penBlack;
	CImageList*	m_pLargeImageList;
	CImageList*	m_pSmallImageList;
	DWORD		m_dwFlags;
	CRect		m_rcUpArrow;
	CRect		m_rcDownArrow;
	CSize		m_sizeOffset;
	CSize		m_sizeMargin;
	CPtrArray	m_arFolder;
	CXTCoolMenu	m_coolMenu;		// 

public:

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual void DrawAnimItem(const int xoffset, const int yoffset, const int index);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual void SetAnimSelHighlight(const int iTime);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual DWORD GetFolderData(int iFolder = -1);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual CWnd * GetFolderChild(int iFolder = -1);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual int AddFolderBar(LPCTSTR pFolder, CWnd * pSon, const DWORD exData = 0);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual CString GetItemText(const int index);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual void SetAnimationTickCount(const long value) { m_nAnimationTickCount = value; };

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual int GetAnimationTickCount() { return m_nAnimationTickCount; };

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual void AnimateFolderScroll(const int iFrom, const int iTo);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual int GetDragItemRect(const int index, CRect &rect);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual void DrawDragArrow(CDC * pDC, const int iFrom, const int iTo);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual void SetItemImage(const int index, const int iImage);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual void SetItemData(const int index, const DWORD dwData);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual int  GetItemImage(const int index) const;

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual DWORD GetItemData(const int index) const;

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual BOOL IsValidItem(const int index) const;

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual void RemoveItem(const int index);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual void SetItemText(const int index, LPCTSTR text);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual void StartItemEdit(const int index);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual void SetFolderText(const int index, LPCTSTR text);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual void StartGroupEdit(const int index);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual void GetLabelRect(const int iFolder, const int iIndex, CRect &rect);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual void GetIconRect(const int iFolder, const int iIndex, CRect &rect);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual void HighlightItem(const int index, const BOOL bPressed = false);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual void GetVisibleRange(const int iFolder, int &first, int &last);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual void DrawItem(CDC * pDC, const int iFolder, CRect rc, const int index, const BOOL bOnlyImage = false);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual CImageList * GetFolderImageList(const int index, const BOOL bSmall) const;

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual CSize GetItemSize(const int iFolder, const int index, const int type);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual void PaintItems(CDC * pDC, const int iFolder, CRect rc);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual CImageList * GetImageList(CImageList * pImageList, DWORD dwImageList);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual CImageList * SetFolderImageList(const int folder, CImageList * pImageList, DWORD dwImageList);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual CImageList * SetImageList(CImageList * pImageList, DWORD dwImageList);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual int GetCountPerPage() const;

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual void RemoveFolder(const int index);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual int GetSelFolder() const;

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual int GetFolderCount() const;

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual void SetSelFolder(const int index);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual int GetItemCount() const;

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual int InsertItem(const int folder, const int index, LPCTSTR text, const int image = -1, const DWORD exData = 0);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual void HighlightFolder(const int index);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual int HitTestEx(const CPoint &point, int &index);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual void GetInsideRect(CRect &rect) const;

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual int AddFolder(LPCTSTR cFolderName, const DWORD exData);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual void GetItemRect(const int iFolder, const int iIndex, CRect &rect);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual BOOL GetFolderRect(const int iIndex, CRect &rect) const;

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual void ModifyFlag(const DWORD &dwRemove, const DWORD &dwAdd, const UINT redraw = 0);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual DWORD GetFlag() const;

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual void SetSmallIconView(const BOOL bSet);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual BOOL IsSmallIconView() const;

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd * pParentWnd, UINT nID, const DWORD dwFlag = OBS_XT_DEFAULT);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual BOOL CreateEx(DWORD dwExStyle, DWORD dwStyle, const RECT& rect, CWnd * pParentWnd, UINT nID, const DWORD dwFlag = OBS_XT_DEFAULT);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual void DrawFolder(CDC * pDC, const int iIdx, CRect rect, const BOOL bSelected);

protected:

	//{{AFX_VIRTUAL(CXTOutBarCtrl)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CXTOutBarCtrl)
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLargeicon();
	afx_msg void OnUpdateLargeicon(CCmdUI* pCmdUI);
	afx_msg void OnSmallicon();
	afx_msg void OnUpdateSmallicon(CCmdUI* pCmdUI);
	afx_msg void OnRemoveitem();
	afx_msg void OnUpdateRemoveitem(CCmdUI* pCmdUI);
	afx_msg void OnRenameitem();
	afx_msg void OnUpdateRenameitem(CCmdUI* pCmdUI);
	//}}AFX_MSG
	
	afx_msg long OnEndLabelEdit(WPARAM wParam, LPARAM lParam);
	
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CXTEditItem helper class
/////////////////////////////////////////////////////////////////////////////
class _XT_EXT_CLASS CXTEditItem : public CEdit
{
	DECLARE_DYNAMIC(CXTEditItem)

public:
	CXTEditItem();
	virtual ~CXTEditItem();

	int		m_nIndex;
	BOOL	m_bEscapeKey;
	CString m_strText;
	WPARAM	m_wParam;
	BOOL	m_bNoDown;

	//{{AFX_VIRTUAL(CXTEditItem)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

protected:

	//{{AFX_MSG(CXTEditItem)
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // #if !defined(__XTOUTBARCTRL_H__)
