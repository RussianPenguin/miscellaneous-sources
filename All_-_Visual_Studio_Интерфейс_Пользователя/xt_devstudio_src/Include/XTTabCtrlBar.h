// XTTabCtrlBar.h interface for the CXTTabCtrlBar class.
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

#if !defined(__XTTABCTRLBAR_H__)
#define __XTTABCTRLBAR_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "XTDockWindow.h"
#include "XTTabCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CXTTabCtrlBar is a CXTControl bar derived class which implements a
// tabbed window simular to VisualStudio's workspace window.
/////////////////////////////////////////////////////////////////////////////
class _XT_EXT_CLASS CXTTabCtrlBar : public CXTDockWindow
{
	DECLARE_DYNAMIC(CXTTabCtrlBar)

public:
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Constructor - handles default initialization.
	CXTTabCtrlBar();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Destructor - handles cleanup and de-allocation.
	virtual ~CXTTabCtrlBar();

protected:

	int				m_nPointTab;				// tab index set from GetTabFromPoint(...)
	int				m_nActiveTab;				// currently selected tab
    int             m_nNextToolTipId;			// tooltip resource id
	CView*			m_pActiveView;				// this points to the active view
	CXTTabCtrl		m_TabCtrl;					// tab control
	CMapStringToPtr	m_ClassNameToImageIndexMap;	// Map class name to the image index
	BOOL			m_bToolTipsEnabled;			// TRUE if tooltips are enabled.

	// template list containing tab information
	CList <XT_TCB_ITEM *,XT_TCB_ITEM *>	m_viewList;

public:

	// -> Parameters:		lpszLabel	-	tab text
	//						pViewClass	-	CView object associated with tab
	//						pDoc		-	CDocument associated with view
	//						nIndex		-	index of tab to add
	//						pContext	-	create context for view
	// -> Return Value:		
	// -> Remarks:			This member function is called to add a view to the tab control
	virtual BOOL AddView(LPCTSTR lpszLabel, CRuntimeClass *pViewClass, CDocument* pDoc = NULL, UINT nIndex=-1,  CCreateContext *pContext = NULL);

	// -> Parameters:		nView	-	
	// -> Return Value:		
	// -> Remarks:			This member function will remove a view based on its index
	virtual void RemoveView(int nView);

	// -> Parameters:		nView	-	
	// -> Return Value:		
	// -> Remarks:			This member function will set a view active based on index
	virtual void SetActiveView(int nView);

	// -> Parameters:		pViewClass	-	
	// -> Return Value:		
	// -> Remarks:			This member function will set a view active based on a CView object
	virtual void SetActiveView(CRuntimeClass *pViewClass);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			This member function returns a pointer to the active view in the 
	//						tab control
	virtual CView* GetActiveView();

	// -> Parameters:		nView	-	
	// -> Return Value:		
	// -> Remarks:			This member function returns a pointer to a view based on its index
	virtual CView* GetView(int nView);

	// -> Parameters:		pViewClass	-	
	// -> Return Value:		
	// -> Remarks:			This member function returns a pointer to a view based on a CView object
	virtual CView* GetView(CRuntimeClass *pViewClass);

	// -> Parameters:		pImageList	-	
	// -> Return Value:		
	// -> Remarks:			This member function initializes the image list for the tab control
	virtual CImageList* SetTabImageList(CImageList *pImageList);

	// -> Parameters:		dwRemove	-	
	//						dwAdd		-	
	//						nFlags		-	
	// -> Return Value:		
	// -> Remarks:			This member function will modify the style for the tab control 
	//						associated with this control.
	virtual BOOL ModifyTabStyle(DWORD dwRemove, DWORD dwAdd, UINT nFlags=0);

	// -> Parameters:		nView	-	
	// -> Return Value:		
	// -> Remarks:			This member function will return the name for a view based on index
    virtual LPCTSTR GetViewName(int nView);

	// -> Parameters:		pViewClass	-	
	// -> Return Value:		
	// -> Remarks:			This member function will return the name for a view based upon a 
	//						CView object
    virtual LPCTSTR GetViewName(CRuntimeClass *pViewClass);

	// -> Parameters:		nView	-	
	// -> Return Value:		
	// -> Remarks:			This member function will delete a view based upon its index
    virtual void DeleteView(int nView);

	// -> Parameters:		pViewClass	-	
	// -> Return Value:		
	// -> Remarks:			This member function will delete a view based upon a CView object
    virtual void DeleteView(CRuntimeClass *pViewClass);

	// -> Parameters:		nView		-	
	//						lpszLabel	-	
	// -> Return Value:		
	// -> Remarks:			This member function will set the tooltip for a particular view in 
	//						the tab control based on its index
    virtual void SetViewToolTip(int nView, LPCTSTR lpszLabel);

	// -> Parameters:		pViewClass	-	
	//						lpszLabel	-	
	// -> Return Value:		
	// -> Remarks:			This member function will set the tooltip for a particular view in 
	//						the tab control based on a CView object
    virtual void SetViewToolTip(CRuntimeClass *pViewClass, LPCTSTR lpszLabel);

	// -> Parameters:		rect	-	reference to a CRect object which contains the size of 
	//									the child window associated with the control bar.
	// -> Return Value:		
	// -> Remarks:			This member function is called by the control bar, and can be 
	//						overloaded in derived classes to return the rect for the child window 
	//						associated with the control bar.
	virtual void GetInsideRect(CRect &rect);

	// -> Parameters:		popupMenuID  -	id for the tab control popup menu
	//						nPos		 -	index position in menu resource
	// -> Return Value:		
	// -> Remarks:			This member function is used to set the resource id for the popup 
	//						menu used by the tab control.
	virtual void SetTabMenuID(UINT popupMenuID, int nPos=0);

	// -> Parameters:		pViewClass	-	
	// -> Return Value:		
	// -> Remarks:			Use this member function to set the active view to the specified 
	//						view this provides more user control than the other SetActiveView()'s
	virtual void SetActiveView(CView* pUserView);

	// -> Parameters:		nIndex			-	
	//						pRuntimeClass	-	
	// -> Return Value:		
	// -> Remarks:			Use this member function to map the image index to the class name, 
	//						and allows the image to be set based on the view's runtime class type
	virtual void AssociateImageIndexWithRuntimeClass(int nIndex, CRuntimeClass* pRuntimeClass);
	
	// -> Parameters:		nIndex					-	
	//						lpszRuntimeClassName	-	
	// -> Return Value:		
	// -> Remarks:			Use this member function to map the image index to the class name, 
	//						and allows the image to be set based on the name of the view's runtime 
	//						class name
	void AssociateImageIndexWithRuntimeClass(int nIndex, LPCTSTR lpszRuntimeClassName);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Use this member function to clear out all the tabs, but the user 
	//						MUST take care of the views themselves
	virtual BOOL RemoveAllTabs();

	// -> Parameters:		point	-	Pointer to a CPoint object that contains the cursor screen 
	//									coordinates. Use default for current cursor position.
	// -> Return Value:		
	// -> Remarks:			Call this member function to retrieve the tab index from current 
	//						cursor position.
	virtual int GetTabFromPoint(CPoint point = CPoint(0,0));

protected:

	// -> Parameters:		nActiveTab -	Index of the tab to set active.
	//						pActiveWnd -	Points to the CView object to set active.
	// -> Return Value:		TRUE if successful.
	// -> Remarks:			This member function will set the parent frames active view based
	//						on the tab index and CView object passed in.
	virtual BOOL SetActiveTab(int nActiveTab, CWnd* pActiveWnd);

	// -> Parameters:		pRuntimeClass	-	
	// -> Return Value:		
	// -> Remarks:			This member function returns the image associated with a runtime 
	//						class, and indicates which image will be displayed with the 
	//						associated view class
	virtual short GetImageIndexFromRuntimeClass(CRuntimeClass* pRuntimeClass);
	
	// -> Parameters:		pos	-	
	// -> Return Value:		
	// -> Remarks:			This member function is used by the tab control bar to remove an 
	//						item from the view list.
	virtual void RemoveListItem(POSITION pos);

	// -> Parameters:		pWnd	-	
	// -> Return Value:		
	// -> Remarks:			This member function is called by the tab control bar to resize the 
	//						tab control window.
	virtual void SizeTabView(CWnd* pWnd);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			This member function is used by the tab control bar to return a 
	//						pointer to the tooltip control associated with this control.
	virtual CToolTipCtrl* GetToolTip();

	// -> Parameters:		pMember		-	
	//						lpszLabel	-	
	// -> Return Value:		
	// -> Remarks:			This member function is used by the tab control bar to add a 
	//						tooltip to a tab.
	virtual void AddToolTip(XT_TCB_ITEM* pMember, LPCTSTR lpszLabel);

	// -> Parameters:		pToolTip	-	
	// -> Return Value:		
	// -> Remarks:			This member function is used by the tab control bar to reset the 
	//						tooltip control.
	virtual void ResetToolTips(CToolTipCtrl* pToolTip);

	// -> Parameters:		lpszLabel	-	
	// -> Return Value:		
	// -> Remarks:			This member function is used by the control bar to create a tab item.
	virtual XT_TCB_ITEM* CreateTabListItem(LPCTSTR lpszLabel);

	// -> Parameters:		pViewClass	-	
	//						pDocument	-	
	//						pContext	-	
	// -> Return Value:		
	// -> Remarks:			This member function is used by the control bar to create a view to 
	//						be associated with a tab control item.
	virtual BOOL CreateTabView(CRuntimeClass *pViewClass, CDocument *pDocument, CCreateContext *pContext);

	// -> Parameters:		bEnable	-	
	// -> Return Value:		
	// -> Remarks:			This member function enables / disables tooltips
	virtual BOOL EnableToolTips(BOOL bEnable);

	//{{AFX_VIRTUAL(CXTTabCtrlBar)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CXTTabCtrlBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnWindowPosChanged(WINDOWPOS FAR* lpwndpos);
	afx_msg void OnTabSelChange(NMHDR* pNMHDR, LRESULT* pResult) ;
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

//---------------------------------------------------------------------------
inline void CXTTabCtrlBar::SetTabMenuID(UINT popupMenuID, int nPos)
	{ m_TabCtrl.SetMenuID(popupMenuID, nPos); }
//---------------------------------------------------------------------------
inline CView* CXTTabCtrlBar::GetActiveView()
	{ return m_pActiveView; }
//---------------------------------------------------------------------------
inline CImageList* CXTTabCtrlBar::SetTabImageList(CImageList *pImageList)
	{ return m_TabCtrl.SetImageList (pImageList); }
//---------------------------------------------------------------------------
inline BOOL CXTTabCtrlBar::ModifyTabStyle(DWORD dwRemove, DWORD dwAdd, UINT nFlags)
	{ return m_TabCtrl.ModifyStyle(dwRemove, dwAdd, nFlags); }
//---------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // #if !defined(__XTTABCTRLBAR_H__)
