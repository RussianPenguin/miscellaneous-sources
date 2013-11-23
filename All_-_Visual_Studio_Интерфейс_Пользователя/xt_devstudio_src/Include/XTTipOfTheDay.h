// XTTipOfTheDay.h interface for the CXTTipOfTheDay class.
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

#if !defined(__XTTIPOFTHEDAY_H__)
#define __XTTIPOFTHEDAY_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CXTTipOfTheDay dialog
/////////////////////////////////////////////////////////////////////////////
class _XT_EXT_CLASS CXTTipOfTheDay : public CDialog
{
	DECLARE_DYNAMIC(CXTTipOfTheDay)

public:

	// -> Parameters:		lpszTipFile -	A NULL terminated string that represents the path
	//										and file name of where the tips text file is located,
	//										by default the file name is set to "tips.txt".
	//               		pParent		-	Points to the parent window for the
	//										Tip Of The Day Dialog.
	// -> Return Value:		
	// -> Remarks:			Constructor - handles default initialization
	CXTTipOfTheDay(LPCTSTR lpszTipFile=NULL, CWnd* pParent = NULL);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Destructor - handles clean up.
	virtual ~CXTTipOfTheDay();

protected:

	CFont		m_fontTitle;	// Default font used for "Did you know..." text.
	CFont		m_fontTip;		// Default font used for tips.
	CFont*		m_pFontTitle;	// User defined font for "Did you know..." text.
	CFont*		m_pFontTip;		// User defined font for tips.
	CString		m_strTipTitle;	// Represents the "Did you know" text.
	CString		m_strTipText;	// Represents the Tip Of The Day text.
	CString		m_strTipFile;	// Represents the file name and path for the tips file.
	FILE*		m_pStream;		// A pointer to the open file stream.
	CRect		m_rcBorder;		// Size of the total display area.
	CRect		m_rcShadow;		// Size of the shadowed rect displayed to the left of the tip.
	CRect		m_rcHilite;		// Size of the background area the tips are displayed on.
	CRect		m_rcTipText;	// Size of the display area for tip text.

public:

	// -> Parameters:		pFontTitle	-	Points to a CFont object that represents the new
	//										font to be used for "Did you know..." text.
	//						pFontTip	-	Points to a CFont object that represents the new
	//										font to be used for Tip Of The Day text.
	// -> Return Value:		
	// -> Remarks:			This member function will set the fonts to be used by the
	//						"Did you know..." and the Tip Of The Day text.
	virtual void SetDefaultFonts(CFont* pFontTitle, CFont* pFontTip);

	// -> Parameters:		strNext -	A CString reference that represents the next
	//									Tip Of The Day text that is to be displayed.
	// -> Return Value:		
	// -> Remarks:			This member function will retreive the next string to be
	//						displayed as the Tip Of The Day.
	virtual void GetNextTipString(CString& strNext);

	// -> Parameters:		lpszTitle	-	Represents a NULL terminated string that is
	//										the string to be displayed in place of the
	//										"Did you know..." text.
	// -> Return Value:		
	// -> Remarks:			This member function will set the text that is to be displayed
	//						in place of the "Did you know..." string.
	virtual void SetDefaultTitle(LPCTSTR lpszTitle) { m_strTipTitle = lpszTitle; }

	// -> Parameters:		lpszTipFile	-	A NULL terminated string that represents the full
	//										path to whrer the tips text file is located.
	// -> Return Value:		
	// -> Remarks:			This member function will set the path to where the tips file is
	//						located.
	virtual void SetTipsFilePath(LPCTSTR lpszTipFile);

// Dialog Data
	//{{AFX_DATA(CXTTipOfTheDay)
	enum { IDD = XT_IDD_TIPOFTHEDAY };
	CButton	m_ok;
	CButton	m_showTips;
	CButton	m_btnNextTip;
	CStatic	m_staticBorder;
	BOOL	m_bStartup;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXTTipOfTheDay)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CXTTipOfTheDay)
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnDaytipNext();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // #if !defined(__XTTIPOFTHEDAY_H__)
