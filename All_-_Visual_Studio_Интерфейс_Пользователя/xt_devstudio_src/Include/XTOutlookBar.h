// XTContentItems.h interface for the CXTContentItems class.
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

#if !defined(__XTOUTLOOKBAR_H__)
#define __XTOUTLOOKBAR_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CXTContentItems is a utility class used as a Container for 
// XTOutlookBar menu items.
/////////////////////////////////////////////////////////////////////////////
class _XT_EXT_CLASS CXTContentItems
{
public:

	// -> Parameters:		nID -	
	//						str -	
	// -> Return Value:		
	// -> Remarks:			Constructor - handles default initialization.
	CXTContentItems(UINT nID, CString str);

protected:

	UINT	m_nImageID;	// index of menu item
	CString m_csText;	// text of menu item

public:

	// -> Parameters:		pItems -	
	// -> Return Value:		
	// -> Remarks:			Overloaded operator which copies a CContentItem object
	void operator = (CXTContentItems& pItems);

	// -> Parameters:		
	// -> Return Value:		Returns the index of a menu item
	// -> Remarks:			
	virtual UINT GetImageID();

	// -> Parameters:		
	// -> Return Value:		Returns the text of a menu item
	// -> Remarks:			
	virtual CString GetText();
};

/////////////////////////////////////////////////////////////////////////////
// XTOutlookBar is a CListBox derived class which simulates a control simular
// to the Outlook bar as seen in Outlook, can only be used with the
// LBS_OWNERDRAWVARIABLE style bit set. very generic 
/////////////////////////////////////////////////////////////////////////////
class _XT_EXT_CLASS CXTOutlookBar : public CListBox
{
	DECLARE_DYNAMIC(CXTOutlookBar)

public:

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Constructor - handles default initialization.
	CXTOutlookBar();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Destructor - handles cleanup and de-allocation.
	virtual ~CXTOutlookBar();

protected:

	CWnd*			 m_pOwner;			// points to the parent window for this control see SetOwner(...)
    CPoint           m_point;			// holds the cursor position
	CImageList*		 m_pImageListLarge;	// points to the small image list for this control see SetImageLists(...)
	CImageList*		 m_pImageListSmall;	// points to the large image list for this control see SetImageLists(...)
	CXTContentItems* m_pContents;		// points to a CContentItem array see SetItems(...)
    int              m_nNumItems;		// number of menu items in this control see SetItems(...)
	int              m_nIndex;			// currently selected menu index
    bool             m_bHilight;		// true when menu item is selected
    bool             m_bLBDown;			// true when left mouse button is pressed

public:

	// -> Parameters:		pImageListSmall -	
	//						pImageListLarge -	
	// -> Return Value:		
	// -> Remarks:			Sets the large and small image lists for the control. currently 
	//						only large image list is implemented
	virtual void SetImageLists(CImageList* pImageListSmall=NULL, CImageList* pImageListLarge=NULL);

	// -> Parameters:		pItems	  -	
	//						nNumItems -	
	// -> Return Value:		
	// -> Remarks:			Sets the CContentItem array and m_nNumItems member variables
	virtual void SetItems(CXTContentItems* pItems, int nNumItems);

	// -> Parameters:		pWnd	  -	
	// -> Return Value:		
	// -> Remarks:			Sets the window that will receive messages from this control
	virtual void SetOwner(CWnd* pWnd);

	//{{AFX_VIRTUAL(CXTOutlookBar)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	//}}AFX_VIRTUAL

protected:

	//{{AFX_MSG(CXTOutlookBar)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnPaint();
	afx_msg void OnWindowPosChanged(WINDOWPOS FAR* lpwndpos);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//---------------------------------------------------------------------------
inline CXTContentItems::CXTContentItems( UINT nID, CString str )
	{ m_nImageID = nID; m_csText = str; }
//---------------------------------------------------------------------------
inline CString CXTContentItems::GetText()
	{ return m_csText; }
//---------------------------------------------------------------------------
inline UINT CXTContentItems::GetImageID()
	{ return m_nImageID; }
//---------------------------------------------------------------------------
inline void CXTContentItems::operator = ( CXTContentItems& pItems )
	{ m_nImageID = pItems.m_nImageID; m_csText = pItems.m_csText; }
//---------------------------------------------------------------------------
inline void CXTOutlookBar::SetImageLists(CImageList* pImageListSmall, CImageList* pImageListLarge)
	{ m_pImageListLarge = pImageListLarge; m_pImageListSmall = pImageListSmall; }
//---------------------------------------------------------------------------
inline void CXTOutlookBar::SetItems(CXTContentItems * pItems, int nNumItems)
	{ m_pContents = pItems; m_nNumItems = nNumItems; ResetContent(); for (int i = 0; i < nNumItems; ++i) AddString(m_pContents[i].GetText()); }
//---------------------------------------------------------------------------
inline void CXTOutlookBar::SetOwner(CWnd* pWnd)
	{ m_pOwner = pWnd; }
//---------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // #if !defined(__XTOUTLOOKBAR_H__)

