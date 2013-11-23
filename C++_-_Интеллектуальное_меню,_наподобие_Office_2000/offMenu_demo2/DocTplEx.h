#if !defined(AFX_DOCTPLEX_H__34DBDA73_E0EB_11D2_B88F_0048540133F7__INCLUDED_)
#define AFX_DOCTPLEX_H__34DBDA73_E0EB_11D2_B88F_0048540133F7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DocTplEx.h : header file
//

#include "menuex.h"
#include "menubar.h"

/////////////////////////////////////////////////////////////////////////////
// CMultiDocTemplateEx document

class CMultiDocTemplateEx : public CMultiDocTemplate
{
public:
	CMultiDocTemplateEx( UINT nIDResource, 
						 CRuntimeClass* pDocClass, CRuntimeClass* pFrameClass, 
						 CRuntimeClass* pViewClass ,UINT *arID, int n);
	CMenuEx m_mnuDocMenu;

	DECLARE_DYNCREATE(CMultiDocTemplateEx)

// Implementation
public:
	void SetMenuToolbars(UINT* arID,int n);
	void LoadMenuToolBars();
	CMenuEx* GetMenu();
	virtual CFrameWnd* CreateNewFrame( CDocument* pDoc, CFrameWnd* pOther );
	virtual void LoadTemplate();
	virtual ~CMultiDocTemplateEx();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	UINT m_nIDResource;
private:
	CArray<UINT,UINT> m_arID;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DOCTPLEX_H__34DBDA73_E0EB_11D2_B88F_0048540133F7__INCLUDED_)
