// XTMemDC.h interface for the CXTMemDC class.
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

#if !defined(__XTMEMDC_H__)
#define __XTMEMDC_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CXTMemDC memory device context
/////////////////////////////////////////////////////////////////////////////
class _XT_EXT_CLASS CXTMemDC : public CDC  
{

public:
	
	// -> Parameters:		pWnd	-	window associated with the display device context
	//						pDC		-	
	//						rect	-	
	//						crFill	-	
	// -> Return Value:		
	// -> Remarks:			Constructor - handles default initialization.
	CXTMemDC(CWnd* pWnd, CDC* pDC, const CRect& rect, COLORREF crColor=xtAfxData.clr3DFace);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Destructor - handles cleanup and de-allocation.
	virtual ~CXTMemDC();

protected:

	CDC*	 m_pDC;			// Saves CDC passed in constructor
	CWnd*	 m_pWnd;		// Owner window.
	CRect	 m_rc;			// Rectangle of drawing area.
	CBitmap	 m_bitmap;		// Offscreen bitmap
	CBitmap* m_pOldBitmap;	// Original GDI object
	COLORREF m_crColor;		// Background fill color
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // #if !defined(__XTMEMDC_H__)
