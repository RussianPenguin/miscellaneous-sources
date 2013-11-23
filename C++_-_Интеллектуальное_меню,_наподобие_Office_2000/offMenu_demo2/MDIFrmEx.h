// MDIFrmEx.h : interface of the CMDIFrameEx class
//

// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1997 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

/////////////////////////////////////////////////////////////////////////////

#ifndef MDI_FRAME_EX
#define MDI_FRAME_EX

#include "MenuBar.h"
#include "MenuEx.h"	// Added by ClassView

#include "ToolbarEx.h"

class CMDIFrameEx : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMDIFrameEx)
public:
	CMDIFrameEx();
	CMenuEx* GetMainMenu(){return &m_MainMenu;};
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMDIFrameEx)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
public:
	void RefreshMenuBar(CMenuEx* pMenu,CMenuEx* pWindowMenu);
	CArray<CToolbarEx*,CToolbarEx*> m_ToolBarList;
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	void RemoveToolbar(CToolbarEx* pToolbar);
	void RegisterToolBar(CToolbarEx* pToolbar);
	void LoadMenuToolBars();
	void SetMenuToolBars(UINT* puArray,int n);
	void EnableMenuChange(BOOL bEnable);
	CMenuEx* GetWindowMenuPopup(CMenuEx* pMenu );
	UINT m_nIDResource;
 	virtual BOOL LoadFrame(UINT nIDResource,
				DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE,
				CWnd* pParentWnd = NULL,
				CCreateContext* pContext = NULL);
	HMENU GetWindowMenuPopup( HMENU hMenuBar );
	CMenuEx m_MainMenu;
	virtual ~CMDIFrameEx();
	CMenuBar* GetMenuBar();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CMenuBar	m_wndMenuBar;
private:
	CArray<UINT,UINT> m_MenuToolBars;
// Generated message map functions
protected:
	virtual int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//{{AFX_MSG(CMDIFrameEx)
	afx_msg void OnIntMode();
	afx_msg void OnUpdateIntMode(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
#endif
