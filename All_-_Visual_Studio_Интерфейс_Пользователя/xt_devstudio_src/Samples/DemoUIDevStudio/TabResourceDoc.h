// TabResourceDoc.h : interface of the CTabResourceDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TABRESOURCEDOC_H__1CA9DB51_2253_11D3_A634_00105A98E9A1__INCLUDED_)
#define AFX_TABRESOURCEDOC_H__1CA9DB51_2253_11D3_A634_00105A98E9A1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CTabResourceDoc : public CDocument
{
protected: // create from serialization only
	DECLARE_DYNCREATE(CTabResourceDoc)

// Attributes
public:
	CTabResourceDoc();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTabResourceDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	void UpdateTabView();
	virtual ~CTabResourceDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTabResourceDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABRESOURCEDOC_H__1CA9DB51_2253_11D3_A634_00105A98E9A1__INCLUDED_)
