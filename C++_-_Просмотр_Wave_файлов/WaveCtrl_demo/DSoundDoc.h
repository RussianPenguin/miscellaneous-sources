// DSoundDoc.h : interface of the CDSoundDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DSOUNDDOC_H__BC88D1EA_9A2F_11D3_8740_0080ADC92595__INCLUDED_)
#define AFX_DSOUNDDOC_H__BC88D1EA_9A2F_11D3_8740_0080ADC92595__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include ".\WaveFile\CWaveFile.h"
class CDSoundDoc : public CDocument
{
protected: // create from serialization only
	CDSoundDoc();
	DECLARE_DYNCREATE(CDSoundDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDSoundDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void DeleteContents();
	//}}AFX_VIRTUAL
	CWaveViewCtrl *m_wave;

// Implementation
public:
	virtual ~CDSoundDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDSoundDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DSOUNDDOC_H__BC88D1EA_9A2F_11D3_8740_0080ADC92595__INCLUDED_)
