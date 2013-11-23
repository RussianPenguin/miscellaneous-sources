#if !defined(AFX_WINAPPEX_H__E07A7383_E1AE_11D2_B891_0048540133F7__INCLUDED_)
#define AFX_WINAPPEX_H__E07A7383_E1AE_11D2_B891_0048540133F7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WinAppEx.h : header file
//


////////////////////////////////////////////////////////////////////////////
// CWinAppEx thread

class CMenuEx;

class CWinAppEx : public CWinApp
{
	DECLARE_DYNCREATE(CWinAppEx)
protected:
	CWinAppEx();           // protected constructor used by dynamic creation
	BOOL m_bDrawGrayed;

// Attributes
public:
	LPCTSTR m_lpWndClass;

// Operations
public:
	CMenuEx* SetupMenu(CMenuEx * pTopMenu, const char * section);
	CMenuEx* SaveMenuChanges(CMenuEx * pTopMenu, const char * section);
	BOOL CheckForGrayedMenuPaint(){return m_bDrawGrayed;}
	void AdjustToolBars();
	void OnMenuSilent();
	int GetMenuParameter(){return m_iMenuParameter;};
	void SetMenuParameter(int i){m_iMenuParameter=i;};

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWinAppEx)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CWinAppEx();

	// Generated message map functions
	//{{AFX_MSG(CWinAppEx)
	afx_msg void OnMenuSetup();
	afx_msg void OnShowfull();
	afx_msg void OnUpdateRecentFileMenu(CCmdUI* pCmdUI);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	int m_iMenuParameter;
	void SetToolBar(CToolBar &ToolBar, UINT id , const char* section);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WINAPPEX_H__E07A7383_E1AE_11D2_B891_0048540133F7__INCLUDED_)
