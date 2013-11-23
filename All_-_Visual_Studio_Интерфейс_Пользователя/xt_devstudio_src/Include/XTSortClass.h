// XTSortClass .h interface for the CXTSortClass  class.
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

#if !defined(__XTSORTCLASS_H__)
#define __XTSORTCLASS_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// This class will sort a List control by a column of text, integer, float or
// date/time type. It could be easily extended for other data types.
/////////////////////////////////////////////////////////////////////////////
class _XT_EXT_CLASS CXTSortClass
{

public:
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Constructor - handles default initialization.
	CXTSortClass(CListCtrl* pListCtrl, const int nCol);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Destructor - handles cleanup and de-allocation.
	virtual ~CXTSortClass();

protected:

	CListCtrl* m_pListCtrl;	// pointer to the CListCtrl object to peform sort on

public:

	// -> Parameters:		bAsc	-	
	//						eType	-	
	// -> Return Value:		
	// -> Remarks:			This member function is call to peform the actual sort proceedure.
	virtual void Sort(bool bAsc, XT_DATA_TYPE eType);

protected:

	// -> Parameters:		lParam1		-	
	//						lParam2		-	
	//						lParamSort	-	
	// -> Return Value:		
	// -> Remarks:			This callback member function is called to compare to data items 
	//						during sorting operations
	static int CALLBACK Compare(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // #if !defined(__XTSORTCLASS_H__)
