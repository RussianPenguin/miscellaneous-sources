// XTMaskEdit.h interface for the CXTMaskEdit class.
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

#if !defined(__XTMASKEDIT_H__)
#define __XTMASKEDIT_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CXTMaskEdit is a CEdit derived class which allows text masking to be 
// applied to the control to format it for special editing restrictions.
/////////////////////////////////////////////////////////////////////////////
class _XT_EXT_CLASS CXTMaskEdit : public CEdit
{
	DECLARE_DYNAMIC(CXTMaskEdit)

public:

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Constructor - handles default initialization.
	CXTMaskEdit();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Destructor - handles cleanup and de-allocation.
	virtual ~CXTMaskEdit();

protected:

	bool		m_bUseMask;				// true to use edit mask.
	bool		m_bMaskKeyInProgress;	// true when 
	CString		m_strWindowText;		// buffer that holds the actual edit text.
	CString		m_strMask;				// buffer that holds the actual edit mask value.
	CString		m_strLiteral;			// 
	CString		m_strValid;				// 
	CString		m_strMaskLiteral;		// 

public:

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual void SetEditMask(LPCTSTR lpszMask, LPCTSTR lpszLiteral, LPCTSTR lpszWindowText);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual void SendChar(UINT nChar);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual bool CheckChar(UINT nChar);

	//{{AFX_VIRTUAL(CXTMaskEdit)
	//}}AFX_VIRTUAL

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual bool ProcessMask(UINT nChar, int nEndPos);

protected:
	//{{AFX_MSG(CXTMaskEdit)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CXTDateEdit is a CXTMaskEdit derived class which is specifically 
// geared toward editing date fields.
/////////////////////////////////////////////////////////////////////////////
class _XT_EXT_CLASS CXTDateEdit : public CXTMaskEdit
{
	DECLARE_DYNAMIC(CXTDateEdit)

public:

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Constructor - handles default initialization.
	CXTDateEdit();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual void SetDateTime(COleDateTime& dt);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual void SetDateTime(CString strDate);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual COleDateTime GetDateTime();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual CString GetWindowDateTime();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual COleDateTime ReadOleDateTime(LPCTSTR lpszData);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual bool ProcessMask(UINT nChar, int nEndPos);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual void FormatOleDateTime(CString& strData, COleDateTime dt);
};

/////////////////////////////////////////////////////////////////////////////
// CXTTimeEdit is a CXTDateEdit derived class which is specifically geared 
// toward editing time fields.
/////////////////////////////////////////////////////////////////////////////
class _XT_EXT_CLASS CXTTimeEdit : public CXTDateEdit
{
	DECLARE_DYNAMIC(CXTTimeEdit)

public:

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Constructor - handles default initialization.
	CXTTimeEdit();

protected:

	CString		m_strHours;	// 
	CString		m_strMins;	// 

public:

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual void SetHours(int nHours);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual void SetMins(int nMins);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual bool ProcessMask(UINT nChar, int nEndPos);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual void FormatOleDateTime(CString& strData, COleDateTime dt);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // #if !defined(__XTMASKEDIT_H__)

