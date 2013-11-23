// XTCaptionPopupWnd.h : interface for the CXTCaptionPopupWnd class.
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

#if !defined(__XTCAPTIONPOPUPWND_H__)
#define __XTCAPTIONPOPUPWND_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "XTCaption.h"
#include "XTButton.h"

/////////////////////////////////////////////////////////////////////////////
// CXTCaptionPopupWnd is a CWnd derived class which is used by
// the CXTCaption class to display a popup child window simular to Outlook
/////////////////////////////////////////////////////////////////////////////
class _XT_EXT_CLASS CXTCaptionPopupWnd : public CWnd
{
	DECLARE_DYNAMIC(CXTCaptionPopupWnd)

public:
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Constructor - handles default initialization.
	CXTCaptionPopupWnd();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Destructor - handles cleanup and de-allocation.
	virtual ~CXTCaptionPopupWnd();

protected:

	CWnd*			m_pParentWnd;	 // 
	CWnd*			m_pChildWnd;	 // 
	CWnd*			m_pChildParent;	 // 
	CXTCaption		m_Caption;		 // 
	CXTButton		m_CaptionButton; // 
	HICON			m_hIconOn;		 // handle to normal button icon.
	HICON			m_hIconOff;		 // handle to pressed button icon.

	//{{AFX_VIRTUAL(CXTCaptionPopupWnd)
	public:
	virtual BOOL Create(const CRect& rect, CWnd* pParentWnd, CWnd* pChildWnd);
	//}}AFX_VIRTUAL
	
protected:

	//{{AFX_MSG(CXTCaptionPopupWnd)
	afx_msg void OnDestroy();
	afx_msg void OnCaptButton();
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // #if !defined(__XTCAPTIONPOPUPWND_H__)
