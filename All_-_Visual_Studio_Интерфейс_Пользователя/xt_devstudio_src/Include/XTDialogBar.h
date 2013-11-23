// XTDialogBar.h interface for the CXTDialogBar class.
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

#if !defined(__XTDIALOGBAR_H__)
#define __XTDIALOGBAR_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "XTControlBar.h"

/////////////////////////////////////////////////////////////////////////////
// CXTDialogBar control
// This is a control bar built from a dialog template. It is a modeless
// dialog that delegates all control notifications to the parent window
// of the control bar [the grandparent of the control]
/////////////////////////////////////////////////////////////////////////////
class _XT_EXT_CLASS CXTDialogBar : public CXTControlBar
{
	DECLARE_DYNAMIC(CXTDialogBar)

public:

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Constructor - handles default initialization.
	CXTDialogBar();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Destructor - handles cleanup and de-allocation.
	virtual ~CXTDialogBar();

protected:

	CSize	m_sizeDefault;	// 

public:

	// -> Parameters:		pParentWnd		 -	A pointer to the parent CWnd object.
	//						lpszTemplateName -	A pointer to the name of the CDialogBar 
	//											object’s dialog-box resource template.
	//						nStyle			 -	The alignment style of the dialog bar. The 
	//											following styles are supported:
	//
	//										CBRS_TOP		Control bar is at the top of the 
	//														frame window.
	//										BRS_BOTTOM		Control bar is at the bottom of 
	//														the frame window.
	//										CBRS_NOALIGN	Control bar is not repositioned 
	//														when the parent is resized.
	//										CBRS_LEFT		Control bar is at the left of the 
	//														frame window.
	//										CBRS_RIGHT		Control bar is at the right of the 
	//														frame window.
	//						nID				 -	The control ID of the dialog bar.
	// -> Return Value:		Nonzero if successful; otherwise 0.
	// -> Remarks:			Loads the dialog-box resource template specified by lpszTemplateName 
	//						or nIDTemplate, creates the dialog-bar window, sets its style, and 
	//						associates it with the CDialogBar object.
	//
	//						If you specify the CBRS_TOP or CBRS_BOTTOM alignment style, the 
	//						dialog bar’s width is that of the frame window and its height is 
	//						that of the resource specified by nIDTemplate. If you specify the 
	//						CBRS_LEFT or CBRS_RIGHT alignment style, the dialog bar’s height is 
	//						that of the frame window and its width is that of the resource 
	//						specified by nIDTemplate.
	virtual BOOL Create(CWnd* pParentWnd, LPCTSTR lpszTemplateName,
			UINT nStyle = CBRS_ALIGN_TOP, UINT nID = AFX_IDW_DIALOGBAR);

	// -> Parameters:		pParentWnd	-	A pointer to the parent CWnd object.
	//						nIDTemplate -	The resource ID of the CDialogBar object’s 
	//										dialog-box template.
	//						nStyle			 -	The alignment style of the dialog bar. The 
	//											following styles are supported:
	//
	//										CBRS_TOP		Control bar is at the top of the 
	//														frame window.
	//										BRS_BOTTOM		Control bar is at the bottom of 
	//														the frame window.
	//										CBRS_NOALIGN	Control bar is not repositioned 
	//														when the parent is resized.
	//										CBRS_LEFT		Control bar is at the left of the 
	//														frame window.
	//										CBRS_RIGHT		Control bar is at the right of the 
	//														frame window.
	//						nID				 -	The control ID of the dialog bar.
	// -> Return Value:		Nonzero if successful; otherwise 0.
	// -> Remarks:			Loads the dialog-box resource template specified by lpszTemplateName 
	//						or nIDTemplate, creates the dialog-bar window, sets its style, and 
	//						associates it with the CDialogBar object.
	//
	//						If you specify the CBRS_TOP or CBRS_BOTTOM alignment style, the 
	//						dialog bar’s width is that of the frame window and its height is 
	//						that of the resource specified by nIDTemplate. If you specify the 
	//						CBRS_LEFT or CBRS_RIGHT alignment style, the dialog bar’s height is 
	//						that of the frame window and its width is that of the resource 
	//						specified by nIDTemplate.
	virtual BOOL Create(CWnd* pParentWnd, UINT nIDTemplate,
			UINT nStyle = CBRS_ALIGN_TOP, UINT nID = AFX_IDW_DIALOGBAR);

protected:

	//{{AFX_VIRTUAL(CXTDialogBar)
	virtual CSize CalcFixedLayout(BOOL bStretch, BOOL bHorz);
	virtual void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);
	//}}AFX_VIRTUAL

#ifndef _AFX_NO_OCC_SUPPORT
	
	// Data and functions necessary for OLE control containment
	_AFX_OCC_DIALOG_INFO*	m_pOccDialogInfo;
	LPCTSTR					m_lpszTemplateName;

	// -> Parameters:		pOccDialogInfo	-	
	// -> Return Value:		
	// -> Remarks:			
	virtual BOOL SetOccDialogInfo(_AFX_OCC_DIALOG_INFO* pOccDialogInfo);

	//{{AFX_MSG(CXTDialogBar)
	afx_msg LRESULT HandleInitDialog(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
#endif
};

//---------------------------------------------------------------------------
inline BOOL CXTDialogBar::Create(CWnd* pParentWnd, UINT nIDTemplate, UINT nStyle, UINT nID)
	{ return Create(pParentWnd, MAKEINTRESOURCE(nIDTemplate), nStyle, nID); }
//---------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // #if !defined(__XTDIALOGBAR_H__)

