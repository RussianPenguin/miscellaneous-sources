// XTPreviewView.h interface for the CXTPreviewView class.
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

#if !defined(__XTPREVIEWVIEW_H__)
#define __XTPREVIEWVIEW_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "XTButton.h"

/////////////////////////////////////////////////////////////////////////////
// CXTPreviewView view - Alternate print preview dialog. to use, override
// CView::OnFilePrintPreview in your view class, and add the following code:
//
//	// In derived classes, implement special window handling here
//	// Be sure to Unhook Frame Window close if hooked.
//
//	// must not create this on the frame.  Must outlive this function
//	CPrintPreviewState* pState = new CPrintPreviewState;
//
//	// DoPrintPreview's return value does not necessarily indicate that
//	// Print preview succeeded or failed, but rather what actions are necessary
//	// at this point.  If DoPrintPreview returns TRUE, it means that
//	// OnEndPrintPreview will be (or has already been) called and the
//	// pState structure will be/has been deleted.
//	// If DoPrintPreview returns FALSE, it means that OnEndPrintPreview
//	// WILL NOT be called and that cleanup, including deleting pState
//	// must be done here.
//
//	if (!DoPrintPreview(XT_IDD_PREVIEW_TOOLBAR, this,
//							RUNTIME_CLASS(CXTPreviewView), pState))
//	{
//		// In derived classes, reverse special window handling here for
//		// Preview failure case
//		TRACE0("Error: DoPrintPreview failed.\n");
//		AfxMessageBox(AFX_IDP_COMMAND_FAILURE);
//		delete pState;      // preview failed to initialize, delete State now
//	}
//
/////////////////////////////////////////////////////////////////////////////
class _XT_EXT_CLASS CXTPreviewView : public CPreviewView
{
	DECLARE_DYNCREATE(CXTPreviewView)

protected:
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Constructor - protected constructor used by dynamic creation.
	CXTPreviewView();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Destructor - handles cleanup and de-allocation.
	virtual ~CXTPreviewView();

	CXTButton  m_btnPrint;		// Print button.
	CXTButton  m_btnNext;		// Next button.
	CXTButton  m_btnPrevious;	// Previous button.
	CXTButton  m_btnNumPage;	// One / two page toggle button.
	CXTButton  m_btnZoomIn;		// Zoom-in button.
	CXTButton  m_btnZoomOut;	// Zoom-out button.
	CXTButton  m_btnClose;		// Close button.
	CImageList m_ImageList;		// Image list for preview buttons.

	// -> Parameters:		nID		-	Resource id of the print preview button to subclass.
	//						nImage	-	Index into the button imagelist.
	//						button	-	A reference to the CXTButton object to subclass.
	// -> Return Value:		
	// -> Remarks:			This member function will subclass a print preview button.
	void SubclassPreviewButton(UINT nID, int nImage, CXTButton& button);

	//{{AFX_VIRTUAL(CXTPreviewView)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CXTPreviewView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnUpdateNumPageChange(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // #if !defined(__XTPREVIEWVIEW_H__)
