// TabClassDoc.h : interface of the CTabClassDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TABCLASSDOC_H__1CA9DB25_2253_11D3_A634_00105A98E9A1__INCLUDED_)
#define AFX_TABCLASSDOC_H__1CA9DB25_2253_11D3_A634_00105A98E9A1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CTabClassDoc : public CDocument
{
protected: // create from serialization only
	DECLARE_DYNCREATE(CTabClassDoc)

// Attributes
public:
	CTabClassDoc();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTabClassDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	void UpdateTabView();
	virtual ~CTabClassDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTabClassDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABCLASSDOC_H__1CA9DB25_2253_11D3_A634_00105A98E9A1__INCLUDED_)
