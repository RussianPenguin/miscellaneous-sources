#if !defined(AFX_MENUSETUP_H__5FAABAA4_5868_11D2_94E5_0020AF2A4474__INCLUDED_)
#define AFX_MENUSETUP_H__5FAABAA4_5868_11D2_94E5_0020AF2A4474__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MenuSetup.h : header file
//

#include "PagerCtrl.h"
#include "MenuBar.h"
#include "resource.h"

class CResStr
{
public:
	UINT m_nIDResource;
	CString m_MenuName;
	BOOL m_bModified;
	BOOL m_Loaded;
	CResStr(){m_nIDResource=0;m_bModified=FALSE;m_Loaded=FALSE;};
	CArray<DWORD,DWORD> m_IDs;
};

/////////////////////////////////////////////////////////////////////////////
// CMenuSetup dialog

class CMenuSetup : public CDialog
{
// Construction
public:
	void UpdateToolbar();
	void SaveCurToolbar();
	CArray<CResStr,CResStr&> m_MenuList;
	CArray<CResStr,CResStr&> m_ToolBarList;
	BOOL m_bSaved;
	void ChangeMode(int iMode, int iSel);
	void UpdateMenu();
	void SaveToolbar(CToolBar & Toolbar, const char * section);
	void LoadToolbarState(CToolBar &Toolbar, const char* section);
	void SaveCurMenu();
	int SaveMenu(FILE* f, int n, CMenuEx* pTopMenu);
	BOOL m_IsModified;
	CMenuSetup(CWnd* pParent = NULL);   // standard constructor
	~CMenuSetup(){if(m_pMenuBar) delete m_pMenuBar; if (m_pToolBar) delete m_pToolBar;}
	
// Dialog Data
	//{{AFX_DATA(CMenuSetup)
	enum { IDD = IDD_MENU_SETUP };
	CTabCtrl	m_Tab;
	CComboBox	m_Combo;
	//}}AFX_DATA

	CPagerCtrl m_Pager1;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMenuSetup)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMenuSetup)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnComboSelChange();
	afx_msg void OnTabSelChange(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CMenuEx m_Menu;
	CMenuBar* m_pMenuBar;
	int m_CurComboSel;
	int m_CurMode;
	CMenuEx* SaveMenu(CMenuEx* pTopMenu, const char* section);
	CMenuEx* LoadMenuState(CMenuEx * pTopMenu, const char* section);
	CToolBar* m_pToolBar;
	CMenuEx* ChangeMenuState(CMenuEx* pTopMenu, UINT com);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MENUSETUP_H__5FAABAA4_5868_11D2_94E5_0020AF2A4474__INCLUDED_)
