// XTHtmlView.h interface for the CXTHtmlView class.
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

#if !defined(__XTHTMLVIEW_H__)
#define __XTHTMLVIEW_H__

#include <docobj.h>
#include <shlobj.h>
#include <exdisp.h>
#include <afxconv.h>

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// The CXTHtmlView class provides the functionality of the WebBrowser control 
// within the context of MFC's document/view architecture. The WebBrowser control 
// is a window in which the user can browse sites on the World Wide Web, as well 
// as folders in the local file system and on a network. The WebBrowser control 
// supports hyperlinking, Uniform Resource Locator (URL) navigation, and maintains 
// a history list.
/////////////////////////////////////////////////////////////////////////////
class _XT_EXT_CLASS CXTHtmlView : public CFormView
{
	DECLARE_DYNCREATE(CXTHtmlView)
	DECLARE_EVENTSINK_MAP()

protected:

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Constructor - handles default initialization.
	CXTHtmlView();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Destructor - handles cleanup and de-allocation.
	virtual ~CXTHtmlView();

	IWebBrowser2* m_pBrowserApp;	//	

public:

	CWnd m_wndBrowser;				//	

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	CString GetType() const;

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	long GetLeft() const;

	// -> Parameters:		nNewValue -	
	// -> Return Value:		
	// -> Remarks:			
	void SetLeft(long nNewValue);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	long GetTop() const;

	// -> Parameters:		nNewValue -	
	// -> Return Value:		
	// -> Remarks:			
	void SetTop(long nNewValue);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	long GetHeight() const;

	// -> Parameters:		nNewValue -	
	// -> Return Value:		
	// -> Remarks:			
	void SetHeight(long nNewValue);

	// -> Parameters:		bNewValue -	
	// -> Return Value:		
	// -> Remarks:			
	void SetVisible(BOOL bNewValue);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	BOOL GetVisible() const;

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	CString GetLocationName() const;

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	READYSTATE GetReadyState() const;

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	BOOL GetOffline() const;

	// -> Parameters:		bNewValue -	
	// -> Return Value:		
	// -> Remarks:			
	void SetOffline(BOOL bNewValue);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	BOOL GetSilent() const;

	// -> Parameters:		bNewValue -	
	// -> Return Value:		
	// -> Remarks:			
	void SetSilent(BOOL bNewValue);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	BOOL GetTopLevelContainer() const;

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	CString GetLocationURL() const;

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	BOOL GetBusy() const;

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	LPDISPATCH GetApplication() const;

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	LPDISPATCH GetParentBrowser() const;

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	LPDISPATCH GetContainer() const;

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	LPDISPATCH GetHtmlDocument() const;

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	CString GetFullName() const;

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	int GetToolBar() const;

	// -> Parameters:		nNewValue -	
	// -> Return Value:		
	// -> Remarks:			
	void SetToolBar(int nNewValue);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	BOOL GetMenuBar() const;

	// -> Parameters:		bNewValue -	
	// -> Return Value:		
	// -> Remarks:			
	void SetMenuBar(BOOL bNewValue);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	BOOL GetFullScreen() const;

	// -> Parameters:		bNewValue -	
	// -> Return Value:		
	// -> Remarks:			
	void SetFullScreen(BOOL bNewValue);

	// -> Parameters:		cmdID	-	
	// -> Return Value:		
	// -> Remarks:			
	OLECMDF QueryStatusWB(OLECMDID cmdID) const;

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	BOOL GetRegisterAsBrowser() const;

	// -> Parameters:		bNewValue -	
	// -> Return Value:		
	// -> Remarks:			
	void SetRegisterAsBrowser(BOOL bNewValue);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	BOOL GetRegisterAsDropTarget() const;

	// -> Parameters:		bNewValue -	
	// -> Return Value:		
	// -> Remarks:			
	void SetRegisterAsDropTarget(BOOL bNewValue);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	BOOL GetTheaterMode() const;

	// -> Parameters:		bNewValue -	
	// -> Return Value:		
	// -> Remarks:			
	void SetTheaterMode(BOOL bNewValue);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	BOOL GetAddressBar() const;

	// -> Parameters:		bNewValue -	
	// -> Return Value:		
	// -> Remarks:			
	void SetAddressBar(BOOL bNewValue);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	BOOL GetStatusBar() const;

	// -> Parameters:		bNewValue -	
	// -> Return Value:		
	// -> Remarks:			
	void SetStatusBar(BOOL bNewValue);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	void GoBack();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	void GoForward();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	void GoHome();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	void GoSearch();

	// -> Parameters:		URL					-	
	//						dwFlags				-	
	//						lpszTargetFrameName	-	
	//						lpszHeaders			-	
	//						lpvPostData			-	
	//						dwPostDataLen		-	
	// -> Return Value:		
	// -> Remarks:			
	void Navigate(LPCTSTR URL, DWORD dwFlags = 0, LPCTSTR lpszTargetFrameName = NULL, LPCTSTR lpszHeaders = NULL, LPVOID lpvPostData = NULL, DWORD dwPostDataLen = 0);

	// -> Parameters:		pIDL				-	
	//						dwFlags				-	
	//						lpszTargetFrameName	-	
	// -> Return Value:		
	// -> Remarks:			
	void Navigate2(LPITEMIDLIST pIDL, DWORD dwFlags = 0, LPCTSTR lpszTargetFrameName = NULL);

	// -> Parameters:		lpszURL				-	
	//						dwFlags				-	
	//						lpszTargetFrameName	-	
	//						lpszHeaders			-	
	//						lpvPostData			-	
	//						dwPostDataLen		-	
	// -> Return Value:		
	// -> Remarks:			
	void Navigate2(LPCTSTR lpszURL, DWORD dwFlags = 0, LPCTSTR lpszTargetFrameName = NULL, LPCTSTR lpszHeaders = NULL, LPVOID lpvPostData = NULL, DWORD dwPostDataLen = 0);

	// -> Parameters:		lpszURL				-	
	//						dwFlags				-	
	//						baPostedData		-	
	//						lpszTargetFrameName	-	
	//						lpszHeader			-	
	// -> Return Value:		
	// -> Remarks:			
	void Navigate2(LPCTSTR lpszURL, DWORD dwFlags, CByteArray& baPostedData, LPCTSTR lpszTargetFrameName = NULL, LPCTSTR lpszHeader = NULL);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	void Refresh();

	// -> Parameters:		nLevel	-	
	// -> Return Value:		
	// -> Remarks:			
	void Refresh2(int nLevel);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			
	void Stop();

	// -> Parameters:		lpszProperty	-	
	//						vtValue			-	
	// -> Return Value:		
	// -> Remarks:			
	void PutProperty(LPCTSTR lpszProperty, const VARIANT& vtValue);

	// -> Parameters:		lpszPropertyName	-	
	//						dValue				-	
	// -> Return Value:		
	// -> Remarks:			
	void PutProperty(LPCTSTR lpszPropertyName, double dValue);

	// -> Parameters:		lpszPropertyName	-	
	//						lpszValue			-	
	// -> Return Value:		
	// -> Remarks:			
	void PutProperty(LPCTSTR lpszPropertyName, LPCTSTR lpszValue);

	// -> Parameters:		lpszPropertyName	-	
	//						lValue  			-	
	// -> Return Value:		
	// -> Remarks:			
	void PutProperty(LPCTSTR lpszPropertyName, long lValue);

	// -> Parameters:		lpszPropertyName	-	
	//						nValue  			-	
	// -> Return Value:		
	// -> Remarks:			
	void PutProperty(LPCTSTR lpszPropertyName, short nValue);

	// -> Parameters:		lpszPropertyName	-	
	//						strValue  			-	
	// -> Return Value:		
	// -> Remarks:			
	BOOL GetProperty(LPCTSTR lpszProperty, CString& strValue);

	// -> Parameters:		lpszPropertyName	-	
	// -> Return Value:		
	// -> Remarks:			
	COleVariant GetProperty(LPCTSTR lpszProperty);

	// -> Parameters:		cmdID		-	
	//						cmdexecopt	-	
	//						pvaIn		-	
	//						pvaOut		-	
	// -> Return Value:		
	// -> Remarks:			
	void ExecWB(OLECMDID cmdID, OLECMDEXECOPT cmdexecopt, VARIANT* pvaIn, VARIANT* pvaOut);

	// -> Parameters:		lpszResource	-	
	// -> Return Value:		
	// -> Remarks:			
	BOOL LoadFromResource(LPCTSTR lpszResource);

	// -> Parameters:		nRes	-	
	// -> Return Value:		
	// -> Remarks:			
	BOOL LoadFromResource(UINT nRes);

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	//{{AFX_VIRTUAL(CXTHtmlView)
	virtual void OnDraw(CDC* pDC);
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	virtual void OnNavigateComplete2(LPCTSTR strURL);
	virtual void OnBeforeNavigate2(LPCTSTR lpszURL, DWORD nFlags, LPCTSTR lpszTargetFrameName, CByteArray& baPostedData, LPCTSTR lpszHeaders, BOOL* pbCancel);
	virtual void OnStatusTextChange(LPCTSTR lpszText);
	virtual void OnProgressChange(long nProgress, long nProgressMax);
	virtual void OnCommandStateChange(long nCommand, BOOL bEnable);
	virtual void OnDownloadBegin();
	virtual void OnDownloadComplete();
	virtual void OnTitleChange(LPCTSTR lpszText);
	virtual void OnPropertyChange(LPCTSTR lpszProperty);
	virtual void OnNewWindow2(LPDISPATCH* ppDisp, BOOL* Cancel);
	virtual void OnDocumentComplete(LPCTSTR lpszURL);
	virtual void OnQuit();
	virtual void OnVisible(BOOL bVisible);
	virtual void OnToolBar(BOOL bToolBar);
	virtual void OnMenuBar(BOOL bMenuBar);
	virtual void OnStatusBar(BOOL bStatusBar);
	virtual void OnFullScreen(BOOL bFullScreen);
	virtual void OnTheaterMode(BOOL bTheaterMode);
	protected:
	virtual void NavigateComplete2(LPDISPATCH pDisp, VARIANT* URL);
	virtual void BeforeNavigate2(LPDISPATCH pDisp, VARIANT* URL, VARIANT* Flags, VARIANT* TargetFrameName, VARIANT* PostData, VARIANT* Headers,   BOOL* Cancel);
	virtual void DocumentComplete(LPDISPATCH pDisp, VARIANT* URL);
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CXTHtmlView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	afx_msg void OnFilePrint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//---------------------------------------------------------------------------
inline void CXTHtmlView::SetRegisterAsBrowser(BOOL bNewValue)
	{ ASSERT(m_pBrowserApp != NULL); m_pBrowserApp->put_RegisterAsBrowser((short) (bNewValue ? AFX_OLE_TRUE : AFX_OLE_FALSE)); }
//---------------------------------------------------------------------------
inline void CXTHtmlView::SetRegisterAsDropTarget(BOOL bNewValue)
	{ ASSERT(m_pBrowserApp != NULL); m_pBrowserApp->put_RegisterAsDropTarget((short) (bNewValue ? AFX_OLE_TRUE : AFX_OLE_FALSE)); }
//---------------------------------------------------------------------------
inline void CXTHtmlView::SetTheaterMode(BOOL bNewValue)
	{ ASSERT(m_pBrowserApp != NULL); m_pBrowserApp->put_TheaterMode((short) (bNewValue ? AFX_OLE_TRUE : AFX_OLE_FALSE)); }
//---------------------------------------------------------------------------
inline void CXTHtmlView::SetVisible(BOOL bNewValue)
	{ ASSERT(m_pBrowserApp != NULL); m_pBrowserApp->put_Visible((short) (bNewValue ? AFX_OLE_TRUE : AFX_OLE_FALSE)); }
//---------------------------------------------------------------------------
inline void CXTHtmlView::SetMenuBar(BOOL bNewValue)
	{ ASSERT(m_pBrowserApp != NULL); m_pBrowserApp->put_MenuBar((short) (bNewValue ? AFX_OLE_TRUE : AFX_OLE_FALSE)); }
//---------------------------------------------------------------------------
inline void CXTHtmlView::SetToolBar(int nNewValue)
	{ ASSERT(m_pBrowserApp != NULL); m_pBrowserApp->put_ToolBar(nNewValue); }
//---------------------------------------------------------------------------
inline void CXTHtmlView::SetOffline(BOOL bNewValue)
	{ ASSERT(m_pBrowserApp != NULL); m_pBrowserApp->put_Offline((short) (bNewValue ? AFX_OLE_TRUE : AFX_OLE_FALSE)); }
//---------------------------------------------------------------------------
inline void CXTHtmlView::SetSilent(BOOL bNewValue)
	{ ASSERT(m_pBrowserApp != NULL); m_pBrowserApp->put_Silent((short) (bNewValue ? AFX_OLE_TRUE : AFX_OLE_FALSE)); }
//---------------------------------------------------------------------------
inline void CXTHtmlView::GoBack()
	{ ASSERT(m_pBrowserApp != NULL); m_pBrowserApp->GoBack(); }
//---------------------------------------------------------------------------
inline void CXTHtmlView::GoForward()
	{ ASSERT(m_pBrowserApp != NULL); m_pBrowserApp->GoForward(); }
//---------------------------------------------------------------------------
inline void CXTHtmlView::GoHome()
	{ ASSERT(m_pBrowserApp != NULL); m_pBrowserApp->GoHome(); }
//---------------------------------------------------------------------------
inline void CXTHtmlView::GoSearch()
	{ ASSERT(m_pBrowserApp != NULL); m_pBrowserApp->GoSearch(); }
//---------------------------------------------------------------------------
inline void CXTHtmlView::Refresh()
	{ ASSERT(m_pBrowserApp != NULL); m_pBrowserApp->Refresh(); }
//---------------------------------------------------------------------------
inline void CXTHtmlView::Refresh2(int nLevel)
	{ ASSERT(m_pBrowserApp != NULL); m_pBrowserApp->Refresh2(COleVariant((long) nLevel, VT_I4)); }
//---------------------------------------------------------------------------
inline void CXTHtmlView::Stop()
	{ ASSERT(m_pBrowserApp != NULL); m_pBrowserApp->Stop(); }
//---------------------------------------------------------------------------
inline void CXTHtmlView::SetFullScreen(BOOL bNewValue)
	{ ASSERT(m_pBrowserApp != NULL); m_pBrowserApp->put_FullScreen((short) (bNewValue ? AFX_OLE_TRUE : AFX_OLE_FALSE)); }
//---------------------------------------------------------------------------
inline void CXTHtmlView::SetAddressBar(BOOL bNewValue)
	{ ASSERT(m_pBrowserApp != NULL); m_pBrowserApp->put_AddressBar((short) (bNewValue ? AFX_OLE_TRUE : AFX_OLE_FALSE)); }
//---------------------------------------------------------------------------
inline void CXTHtmlView::SetHeight(long nNewValue)
	{ ASSERT(m_pBrowserApp != NULL); m_pBrowserApp->put_Height(nNewValue); }
//---------------------------------------------------------------------------
inline void CXTHtmlView::PutProperty(LPCTSTR lpszPropertyName, long lValue)
	{ ASSERT(m_pBrowserApp != NULL); ASSERT(m_pBrowserApp != NULL); PutProperty(lpszPropertyName, COleVariant(lValue, VT_UI4)); }
//---------------------------------------------------------------------------
inline void CXTHtmlView::PutProperty(LPCTSTR lpszPropertyName, short nValue)
	{ ASSERT(m_pBrowserApp != NULL); ASSERT(m_pBrowserApp != NULL); PutProperty(lpszPropertyName, COleVariant(nValue, VT_UI2)); }
//---------------------------------------------------------------------------
inline void CXTHtmlView::PutProperty(LPCTSTR lpszPropertyName, LPCTSTR lpszValue)
	{ ASSERT(m_pBrowserApp != NULL); ASSERT(m_pBrowserApp != NULL); PutProperty(lpszPropertyName, COleVariant(lpszValue, VT_BSTR)); }
//---------------------------------------------------------------------------
inline void CXTHtmlView::PutProperty(LPCTSTR lpszPropertyName, double dValue)
	{ ASSERT(m_pBrowserApp != NULL); ASSERT(m_pBrowserApp != NULL); PutProperty(lpszPropertyName, COleVariant(dValue)); }
//---------------------------------------------------------------------------
inline void CXTHtmlView::SetTop(long nNewValue)
	{ ASSERT(m_pBrowserApp != NULL); m_pBrowserApp->put_Top(nNewValue); }
//---------------------------------------------------------------------------
inline void CXTHtmlView::SetLeft(long nNewValue)
	{ ASSERT(m_pBrowserApp != NULL); m_pBrowserApp->put_Left(nNewValue); }
//---------------------------------------------------------------------------
inline void CXTHtmlView::SetStatusBar(BOOL bNewValue)
	{ ASSERT(m_pBrowserApp != NULL); m_pBrowserApp->put_StatusBar((short) (bNewValue ? AFX_OLE_TRUE : AFX_OLE_FALSE)); }
//---------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // #if !defined(__XTHTMLVIEW_H__)

