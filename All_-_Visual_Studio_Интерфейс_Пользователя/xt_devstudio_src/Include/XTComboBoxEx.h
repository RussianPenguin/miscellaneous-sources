// XTComboBoxEx.h : interface for the CXTComboBoxEx class.
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

#if !defined(__XTCOMBOBOXEX_H__)
#define __XTCOMBOBOXEX_H__

/////////////////////////////////////////////////////////////////////////////
// The CXTComboBoxEx class extends the combo box control by providing support 
// for image lists. By using CXTComboBoxEx to create combo box controls, you no 
// longer need to implement your own image drawing code. Instead, use CXTComboBoxEx 
// to access images from an image list.
/////////////////////////////////////////////////////////////////////////////
class _XT_EXT_CLASS CXTComboBoxEx : public CComboBox
{
	DECLARE_DYNAMIC(CXTComboBoxEx)

public:
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	CXTComboBoxEx();
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	virtual ~CXTComboBoxEx();
	
	// -> Parameters:		dwStyle		-	Specifies the combination of combo box
	//										styles applied to the combo box.
	//						rect		-	A reference to a CRect object orRECT structureis the
	//										position and size of the combo box
	//						pParentWnd	-	A pointer to a CWnd object that is the parent window
	//										of the combo box (usually a CDialog). It must not be NULL
	//						nID			-	Specifies
	//										the combo box’s control ID.
	// -> Return Value:		
	// -> Remarks:			Creates the combo box and attaches it to the CXTComboBoxEx
	//						object.
	BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);

	// -> Parameters:		iIndex	-	Zero-based index of the item to be removed. 
	// -> Return Value:		
	// -> Remarks:			Removes an item from a ComboBoxEx control.Returns the
	//						number of items remaining in the control. If iIndex is invalid,
	//						the function returns CB_ERR. 
	int DeleteItem(int iIndex);

	// -> Parameters:		pCBItem	-	A pointer to a COMBOBOXEXITEM structure
	//									that will receive the item information. 
	// -> Return Value:		
	// -> Remarks:			Retrieves item information for a given ComboBoxEx item
	//						Returns nonzero if the operation was successful; otherwise 0.
	BOOL GetItem(COMBOBOXEXITEM* pCBItem);

	// -> Parameters:		pCBItem	-	A pointer to aCOMBOBOXEXITEM structure that
	//									will receive the item information. This structure contains
	//									callback flag values for the item.
	// -> Return Value:		
	// -> Remarks:			Inserts a new item in a ComboBoxEx control. Returns
	//						the index at which the new item was inserted if successful; otherwise
	//						-1
	int InsertItem(const COMBOBOXEXITEM* pCBItem);

	// -> Parameters:		iItem			-	item index.
	//						nStringID		-	string resource.
	//						iIndent			-	ammount (in pixels) image is to be indented.
	//						iImage			-	image index.
	//						iSelectedImage	-	selected image index.
	//						mask			-	style mask.
	// -> Return Value:		
	// -> Remarks:			Inserts a new item in a ComboBoxEx control. Returns
	//						the index at which the new item was inserted if successful; otherwise
	//						-1
	int InsertItem(int iItem, UINT nStringID, int iIndent=0, int iImage=0, int iSelectedImage=0, UINT mask=CBEIF_TEXT|CBEIF_IMAGE|CBEIF_SELECTEDIMAGE|CBEIF_INDENT);

	// -> Parameters:		iItem			-	item index.
	//						lpszItem		-	item string.
	//						iIndent			-	ammount (in pixels) image is to be indented.
	//						iImage			-	image index.
	//						iSelectedImage	-	selected image index.
	//						mask			-	style mask.
	// -> Return Value:		
	// -> Remarks:			Inserts a new item in a ComboBoxEx control. Returns
	//						the index at which the new item was inserted if successful; otherwise
	//						-1
	int InsertItem(int iItem, LPCTSTR lpszItem, int iIndent=0, int iImage=0, int iSelectedImage=0, UINT mask=CBEIF_TEXT|CBEIF_IMAGE|CBEIF_SELECTEDIMAGE|CBEIF_INDENT);

	// -> Parameters:		pCBItem	-	A pointer to a COMBOBOXEXITEM structure
	//									that will receive the item information
	// -> Return Value:		
	// -> Remarks:			Sets the attributes for an item in a ComboBoxEx control.
	//						Returns nonzero if the operation was successful; otherwise 0.
	BOOL SetItem(const COMBOBOXEXITEM* pCBItem);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Retrieves the extended stylescontrol. Returns the DWORD
	//						value that contains the extended styles that are used for the
	//						combo box control.
	DWORD GetExtendedStyle() const;

	// -> Parameters:		dwExMask	-	A DWORD value that indicbe affected. Only
	//										the extended styles in dwExMask will be changed. All other
	//										styles will be maintained as is. If this parameter is zero,
	//										then all of the styles in dwExStyles will be affected
	//						dwExStyles	-	A DWORD to set for the control	
	// -> Return Value:		
	// -> Remarks:			Sets extended styles within a ComReturns a DWORD value
	//						that contains the extended styles previously used for the control.
	DWORD SetExtendedStyle(DWORD dwExMask, DWORD dwExStyles);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Deteredit control by typing.Returns nonzero if the user
	//						has typed in the control's edit box; otherwise 0. 
	BOOL HasEditChanged();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Retrieves the handlecontrol. Returns a pointer to a CEdit object.
	CEdit* GetEditCtrl();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Returns a pointer to a CComboBox object.
	CComboBox* GetComboBoxCtrl();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Retrieves a pointer to the image list assigned to a ComboBoxEx control. Returns a pointer to a CImageList object. If it fails, this member function returns NULL.
	CImageList* GetImageList() const;

	// -> Parameters:		pImageList	-	A pointer to a CImageList object containing
	//										the images to use with the CXTComboBoxEx control.
	// -> Return Value:		
	// -> Remarks:			Sets an image list for a ComboBoxEx control. Returns
	//						a pointer to a CImageList object containing the images previously
	//						used by the CXTComboBoxEx control. NULL if no image list as previously
	//						set.
	CImageList* SetImageList(CImageList* pImageList);
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Un-supported base class message.
	int Dir(UINT attr, LPCTSTR lpszWildCard);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Un-supported base class message.
	int FindString(int nIndexStart, LPCTSTR lpszFind) const;
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Un-supported base class message.
	int AddString(LPCTSTR lpszString);
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Un-supported base class message.
	BOOL SetEditSel(int nStartChar, int nEndChar);
	
	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Un-supported base class message.
	int InsertString(int nIndex, LPCTSTR lpszString);
};

//---------------------------------------------------------------------------
inline CXTComboBoxEx::CXTComboBoxEx()
	{ }
//---------------------------------------------------------------------------
inline DWORD CXTComboBoxEx::GetExtendedStyle() const
	{ ASSERT(::IsWindow(m_hWnd)); return (BOOL) ::SendMessage(m_hWnd, CBEM_GETEXTENDEDSTYLE, 0, 0); }
//---------------------------------------------------------------------------
inline DWORD CXTComboBoxEx::SetExtendedStyle(DWORD dwExMask, DWORD dwExStyles)
	{ ASSERT(::IsWindow(m_hWnd)); return (DWORD) ::SendMessage(m_hWnd, CBEM_SETEXTENDEDSTYLE, (DWORD) dwExMask, (LPARAM) dwExStyles); }
//---------------------------------------------------------------------------
inline BOOL CXTComboBoxEx::HasEditChanged()
	{ ASSERT(::IsWindow(m_hWnd)); return (BOOL) ::SendMessage(m_hWnd, CBEM_HASEDITCHANGED, 0, 0); }
//---------------------------------------------------------------------------
inline CEdit* CXTComboBoxEx::GetEditCtrl()
	{ ASSERT(::IsWindow(m_hWnd)); return (CEdit*) CEdit::FromHandle((HWND) ::SendMessage(m_hWnd, CBEM_GETEDITCONTROL, 0, 0)); }
//---------------------------------------------------------------------------
inline CComboBox* CXTComboBoxEx::GetComboBoxCtrl()
	{ ASSERT(::IsWindow(m_hWnd)); return (CComboBox*) CComboBox::FromHandle((HWND) ::SendMessage(m_hWnd, CBEM_GETCOMBOCONTROL, 0, 0)); }
//---------------------------------------------------------------------------
inline CImageList* CXTComboBoxEx::SetImageList(CImageList* pImageList)
	{ ASSERT(::IsWindow(m_hWnd)); return CImageList::FromHandle((HIMAGELIST) ::SendMessage(m_hWnd, CBEM_SETIMAGELIST, 0, (LPARAM)pImageList->GetSafeHandle())); }
//---------------------------------------------------------------------------
inline CImageList* CXTComboBoxEx::GetImageList() const
	{ ASSERT(::IsWindow(m_hWnd)); return CImageList::FromHandle((HIMAGELIST) ::SendMessage(m_hWnd, CBEM_GETIMAGELIST, 0, 0)); }
//---------------------------------------------------------------------------
// While CXTComboBoxEx derives from CComboBox, there are some
// CB_messages the underlying ComboBoxEx control doesn't support.
//---------------------------------------------------------------------------
inline int CXTComboBoxEx::Dir(UINT attr, LPCTSTR lpszWildCard)
	{ UNUSED_ALWAYS(attr); UNUSED_ALWAYS(lpszWildCard); ASSERT(FALSE); return CB_ERR; }
//---------------------------------------------------------------------------
inline int CXTComboBoxEx::FindString(int nIndexStart, LPCTSTR lpszFind) const
	{ UNUSED_ALWAYS(nIndexStart); UNUSED_ALWAYS(lpszFind); ASSERT(FALSE); return CB_ERR; }
//---------------------------------------------------------------------------
inline int CXTComboBoxEx::AddString(LPCTSTR lpszString)
	{ UNUSED_ALWAYS(lpszString); ASSERT(FALSE); return CB_ERR; }
//---------------------------------------------------------------------------
inline BOOL CXTComboBoxEx::SetEditSel(int nStartChar, int nEndChar)
	{ UNUSED_ALWAYS(nStartChar); UNUSED_ALWAYS(nEndChar); ASSERT(FALSE); return FALSE; }
//---------------------------------------------------------------------------
inline int CXTComboBoxEx::InsertString(int nIndex, LPCTSTR lpszString)
	{ UNUSED_ALWAYS(nIndex); UNUSED_ALWAYS(lpszString); ASSERT(FALSE); return CB_ERR; }
//---------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // #if !defined(__XTCOMBOBOXEX_H__)
