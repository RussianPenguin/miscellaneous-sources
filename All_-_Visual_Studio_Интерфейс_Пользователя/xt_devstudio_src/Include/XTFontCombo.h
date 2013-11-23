// XTFontCombo.h interface for the CXTFontCombo class.
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

#if !defined(__XTFONTCOMBO_H__)
#define __XTFONTCOMBO_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "XTFlatComboBox.h"

/////////////////////////////////////////////////////////////////////////////
// CXTFontCombo window - Should only be used with CBS_OWNERDRAWVARIABLE
// |CBS_DROPDOWN|CBS_HASSTRINGS flags set.
/////////////////////////////////////////////////////////////////////////////
class _XT_EXT_CLASS CXTFontCombo : public CXTFlatComboBox
{
	DECLARE_DYNAMIC(CXTFontCombo)

public:
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Constructor - handles default initialization.
	CXTFontCombo();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Destructor - handles cleanup and de-allocation.
	virtual ~CXTFontCombo();

	// -> Parameters:		logFont -	
	// -> Return Value:		
	// -> Remarks:			
	virtual int GetSelFont(LOGFONT& logFont);
	
protected:
	
	CBitmap	m_bmFontType;	// True type font bitmap.

	// -> Parameters:		pDC	-	
	// -> Return Value:		
	// -> Remarks:			
	virtual void EnumFontFamiliesEx();

	// -> Parameters:		pelf		-	
	//						dwType		-	
	// -> Return Value:		
	// -> Remarks:			
	void AddFont(ENUMLOGFONT* pelf, DWORD dwType);

	static BOOL CALLBACK AFX_EXPORT EnumFamScreenCallBack(
		ENUMLOGFONT* pelf, NEWTEXTMETRICEX* /*lpntm*/, int FontType,
		LPVOID pThis);
	static BOOL CALLBACK AFX_EXPORT EnumFamPrinterCallBack(
		ENUMLOGFONT* pelf, NEWTEXTMETRICEX* /*lpntm*/, int FontType,
		LPVOID pThis);
	static BOOL CALLBACK AFX_EXPORT EnumFamScreenCallBackEx(
		ENUMLOGFONTEX* pelf, NEWTEXTMETRICEX* /*lpntm*/, int FontType,
		LPVOID pThis);
	static BOOL CALLBACK AFX_EXPORT EnumFamPrinterCallBackEx(
		ENUMLOGFONTEX* pelf, NEWTEXTMETRICEX* /*lpntm*/, int FontType,
		LPVOID pThis);

	//{{AFX_VIRTUAL(CXTFontCombo)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL
	
	//{{AFX_MSG(CXTFontCombo)
	afx_msg void OnDestroy();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

///////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // #if !defined(__XTFONTCOMBO_H__)
