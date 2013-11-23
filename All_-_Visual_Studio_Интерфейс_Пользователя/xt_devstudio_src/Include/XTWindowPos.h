// XTWindowPos.h interface for the CXTWindowPos class.
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

#if !defined(__XTWINDOWPLACEMENT_H__)
#define __XTWINDOWPLACEMENT_H__

/////////////////////////////////////////////////////////////////////////////
// CXTWindowPos is used to save and restore window position.
/////////////////////////////////////////////////////////////////////////////
class _XT_EXT_CLASS CXTWindowPos : public WINDOWPLACEMENT
{
public:

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Constructor - handles default initialization
	CXTWindowPos();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Destructor - handles clean up.
	virtual ~CXTWindowPos();

	// -> Parameters:		pWnd -	Points to the CWnd* derived window to be restored to its
	//								previous state.
	// -> Return Value:		
	// -> Remarks:			This member function will load the window specified by pWnd to 
	//						its previous window position.
	BOOL LoadWindowPos(CWnd* pWnd);

	// -> Parameters:		pWnd -	Points to the CWnd* derived windows postition to be saved.
	// -> Return Value:		
	// -> Remarks:			This member function will save the window specified by pWnd by 
	//						its current window position.
	BOOL SaveWindowPos(CWnd* pWnd);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // #if !defined(__XTWINDOWPLACEMENT_H__)
