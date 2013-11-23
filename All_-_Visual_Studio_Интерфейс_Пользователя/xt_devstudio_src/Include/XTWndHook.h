// XTWndHook.h interface for the CXTWndHook class.
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

#if !defined(__XTWNDHOOK_H__)
#define __XTWNDHOOK_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CXTWndHook class
/////////////////////////////////////////////////////////////////////////////
class _XT_EXT_CLASS CXTWndHook : public CObject
{
	DECLARE_DYNAMIC(CXTWndHook)

public:

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Constructor - handles default initialization.
	CXTWndHook();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Destructor - handles cleanup and de-allocation.
	virtual ~CXTWndHook();

protected:

	HWND			m_hWnd;				// The window hooked
	WNDPROC			m_pOldWndProc;		// The original window proc
	CXTWndHook*		m_pNextHook;		// Next in chain of hooks for this window

public:

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			This member function will return TRUE if the current
	//						window has been hooked.
	virtual inline BOOL IsWindowHooked();

	// -> Parameters:		pWnd	-	Points to a CWnd object that represents the
	//									window whose window proc is to be hooked, if
	//									set to NULL, the WNDPROC is removed.
	// -> Return Value:		
	// -> Remarks:			
	virtual inline BOOL HookWindow(CWnd* pWnd);

	// -> Parameters:		pWnd	-	A handle to a window that represents the
	//									window whose window proc is to be hooked, if
	//									set to NULL, the WNDPROC is removed.
	// -> Return Value:		
	// -> Remarks:			This member function will install a new window proc that 
	//						directs messages to the CXTWndHook.
	virtual BOOL HookWindow(HWND hWnd);

	// -> Parameters:		message	-	Specifies the Windows message to be processed.
	//						wParam	-	Provides additional information used in processing 
	//									the message. The parameter value depends on the message.
	//						lParam	-	Provides additional information used in processing the 
	//									message. The parameter value depends on the message.
	// -> Return Value:		The return value depends on the message.
	// -> Remarks:			Provides a Windows procedure (WindowProc) for a CXTWndHook object. It 
	//						dispatches messages through the window's message map.
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);

	// -> Parameters:		
	// -> Return Value:		The return value depends on the message.
	// -> Remarks:			Calls the default window procedure. The default window 
	//						procedure provides default processing for any window message 
	//						that an application does not process. This member function ensures 
	//						that every message is processed. 
	LRESULT Default();

	friend class CXTWindowMap;
};

// class forwards
class CXTMenuBar;

/////////////////////////////////////////////////////////////////////////////
// CXTMenuBar uses this private class to intercept messages on behalf
// of its owning frame, as well as the MDI client window. Conceptually,
// these should be two different hooks, but I want to save code.
/////////////////////////////////////////////////////////////////////////////
class _XT_EXT_CLASS CXTMBarWndHook : public CXTWndHook
{
	DECLARE_DYNAMIC(CXTMBarWndHook)

public:

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Constructor - handles default initialization.
	CXTMBarWndHook();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Destructor - handles cleanup and de-allocation.
   ~CXTMBarWndHook();

protected:

	CXTMenuBar* m_pMenuBar;

public:

	// -> Parameters:		pMenuBar	-	
	//						hWndToHook	-	
	// -> Return Value:		
	// -> Remarks:			
	virtual BOOL Install(CXTMenuBar* pMenuBar, HWND hWndToHook);

	// -> Parameters:		message	-	Specifies the Windows message to be processed.
	//						wParam	-	Provides additional information used in processing 
	//									the message. The parameter value depends on the message.
	//						lParam	-	Provides additional information used in processing the 
	//									message. The parameter value depends on the message.
	// -> Return Value:		The return value depends on the message.
	// -> Remarks:			Provides a Windows procedure (WindowProc) for a CXTWndHook object. It 
	//						dispatches messages through the window's message map.
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);

   friend class CXTMenuBar;
};
/////////////////////////////////////////////////////////////////////////////
// CXTWindowMap class.
/////////////////////////////////////////////////////////////////////////////
class _XT_EXT_CLASS CXTWindowMap : private CMapPtrToPtr
{
	DECLARE_DYNAMIC(CXTWindowMap)

public:

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Constructor - handles default initialization.
	CXTWindowMap();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Destructor - handles cleanup and de-allocation.
	~CXTWindowMap();

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Add hook to map; i.e., associate hook with window.
	void Add(HWND hWnd, CXTWndHook* pXTWndHook);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Remove hook from map.
	void Remove(CXTWndHook* pXTWndHook);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Remove all the hooks for a window
	void RemoveAll(HWND hWnd);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Subclassed window proc for message hooks. Replaces 
	//						AfxWndProc (or whatever else was there before).
	static LRESULT CALLBACK HookWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	// -> Parameters:		
	// -> Return Value:		
	// -> Remarks:			Find first hook associated with window.
	CXTWndHook* Lookup(HWND hWnd);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // #if !defined(__XTWNDHOOK_H__)
