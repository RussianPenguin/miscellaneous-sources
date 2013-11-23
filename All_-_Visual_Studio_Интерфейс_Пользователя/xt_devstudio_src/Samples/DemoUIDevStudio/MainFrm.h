// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__1D0FB12C_4A25_11D4_82DA_D868EA325637__INCLUDED_)
#define AFX_MAINFRM_H__1D0FB12C_4A25_11D4_82DA_D868EA325637__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "OutputBar.h"

class CMainFrame : public CXTMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes

public:
	CXTWindowPos	m_wndPos;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CXTStatusBar	m_wndStatusBar;
	CXTToolBar		m_wndToolBar;
	CXTToolBar		m_wndBuildBar;
	COutputBar		m_wndOutputBar;
	CXTTabCtrlBar	m_wndWrkspBar;
	CImageList		m_TabImages;
	CComboBox		m_wndComboFind;
	CComboBox		m_wndComboProj;
	CComboBox		m_wndComboConf;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg void OnClose();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDoNothing();
	afx_msg void OnWorkspace();
	afx_msg void OnOutput();
	afx_msg void OnUpdateWorkspace(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOutput(CCmdUI* pCmdUI);
	afx_msg void OnSearch();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__1D0FB12C_4A25_11D4_82DA_D868EA325637__INCLUDED_)
