// XTHexEdit.h interface for the CXTHexEdit class.
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

#if !defined(__XTHEXEDIT_H__)
#define __XTHEXEDIT_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CXTHexEdit is a CEdit derived class which allows editing in hex
// display format.
/////////////////////////////////////////////////////////////////////////////
class _XT_EXT_CLASS CXTHexEdit : public CEdit
{
	DECLARE_DYNAMIC(CXTHexEdit)

public:

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Constructor - handles default initialization
	CXTHexEdit();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Destructor - handles clean up.
	virtual ~CXTHexEdit();

protected:

	enum EDITMODE{ EDIT_NONE, EDIT_ASCII, EDIT_HIGH, EDIT_LOW } ;

	int			m_nLength;			// length of data
	int			m_nTopIndex;		// offset of first visible byte on screen
	int			m_nCurrentAddress;	// address under cursor
	int			m_nSelStart;		// start address of selection
	int			m_nSelEnd;			// end address of selection
	int			m_nBytePerRow;		// byte per row 
	int			m_nLinesPerPage;	// lines per page
	int			m_nLineHeight;		// 
	int			m_nNullWidth;		// 
	int			m_nOffHex;			// 
	int			m_nOffAscii;		// 
	int			m_nOffAddress;		// 
	BOOL		m_bShowAddress;		// 
	BOOL		m_bShowAscii;		// 
	BOOL		m_bShowHex;			// 
	BOOL		m_bAddressIsWide;	// 4/8 byte address
	BOOL		m_bNoAddressChange;	// internally used
	BOOL		m_bHalfPage;		// 
	BOOL		m_bUpdate;			// update font info
	CFont		m_Font;
	CPoint		m_ptEditPos;		// 
	EDITMODE	m_eEditMode;		// current editing mode: address/hex/ascii

public:

	LPBYTE		m_pData;			// pointer to data

	// -> Parameters:		pData	-	
	//						nLength	-	
	// -> Return Value:		
	// -> Remarks:			
	virtual int GetData(LPBYTE pData, int nLength);

	// -> Parameters:		pData	-	
	//						nLength	-	
	// -> Return Value:		
	// -> Remarks:			
	virtual void SetData(LPBYTE pData, int nLength);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual CSize GetSel();

	// -> Parameters:		nSelStart -	
	//						nSelEnd	  -	
	// -> Return Value:		
	// -> Remarks:			
	virtual void SetSel(int nSelStart, int nSelEnd);

	// -> Parameters:		nBytePerRow	-	
	// -> Return Value:		
	// -> Remarks:			
	virtual void SetBPR(int nBytePerRow);

	// -> Parameters:		bShowAddress	-	
	//						bShowHex		-	
	//						bShowAscii		-	
	//						AddressIsWide	-	
	// -> Return Value:		
	// -> Remarks:			
	virtual void SetOptions(BOOL bShowAddress, BOOL bShowHex, BOOL bShowAscii, BOOL AddressIsWide);

protected:

	// -> Parameters:		pData	-	
	// -> Return Value:		
	// -> Remarks:			
	virtual void ScrollIntoView(int pData);

	// -> Parameters:		pData	-	
	// -> Return Value:		
	// -> Remarks:			
	virtual void RepositionCaret(int pData);

	// -> Parameters:		x	-	
	//						y	-	
	// -> Return Value:		
	// -> Remarks:			
	virtual void Move(int x, int y);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual BOOL IsSelected();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual void UpdateScrollbars();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual void CreateEditCaret();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual void CreateAddressCaret();

	// -> Parameters:		x	-	
	//						y	-	
	// -> Return Value:		
	// -> Remarks:			
	virtual CPoint CalcPos(int x, int y);

	// -> Parameters:		nSelStart	-		
	//						nLength		-	
	// -> Return Value:		
	// -> Remarks:			
	virtual void SelInsert(int nSelStart, int nLength);

	// -> Parameters:		nSelStart	-		
	//						nSelEnd		-	
	// -> Return Value:		
	// -> Remarks:			
	virtual void SelDelete(int nSelStart, int nSelEnd);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual void NormalizeSel();

	//{{AFX_VIRTUAL(CXTHexEdit)
	public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CXTHexEdit)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg UINT OnGetDlgCode();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnEditClear();
	afx_msg void OnEditCopy();
	afx_msg void OnEditCut();
	afx_msg void OnEditPaste();
	afx_msg void OnEditSelectAll();
	afx_msg void OnEditUndo();
	afx_msg void OnContextMenu(CWnd*, CPoint point);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//---------------------------------------------------------------------------
inline UINT CXTHexEdit::OnGetDlgCode() 
	{ return DLGC_WANTALLKEYS; }
//---------------------------------------------------------------------------
inline void CXTHexEdit::SetOptions(BOOL bShowAddress, BOOL bShowHex, BOOL bShowAscii, BOOL AddressIsWide)
	{ m_bShowHex = bShowHex; m_bShowAscii = bShowAscii; m_bShowAddress = bShowAddress; m_bAddressIsWide = AddressIsWide; m_bUpdate = TRUE; }
//---------------------------------------------------------------------------
inline void CXTHexEdit::SetBPR(int nBytePerRow)
	{ m_nBytePerRow = nBytePerRow; m_bUpdate = TRUE; }
//---------------------------------------------------------------------------
inline BOOL CXTHexEdit::IsSelected()
	{ return m_nSelStart != 0xffffffff; }
//---------------------------------------------------------------------------
inline CSize CXTHexEdit::GetSel()
	{ return CSize(m_nSelStart, m_nSelEnd); }
//---------------------------------------------------------------------------
inline int CXTHexEdit::GetData(LPBYTE pData, int nLength)
	{ memcpy(pData, m_pData, min(nLength, m_nLength)); return m_nLength; }
//---------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // #if !defined(__XTHEXEDIT_H__)

