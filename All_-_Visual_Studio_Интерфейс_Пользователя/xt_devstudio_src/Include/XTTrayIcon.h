// XTTrayIcon.h: interface for the CXTTrayIcon class.
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

#if !defined(__XTTRAYICON_H__)
#define __XTTRAYICON_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//////////////////////////////////////////////////////////////////////
// CXTTrayIcon is a NOTIFYICONDATA derived class which is used to diaplay
// a system tray icon with animation.
//////////////////////////////////////////////////////////////////////
class _XT_EXT_CLASS CXTTrayIcon : protected NOTIFYICONDATA
{
public:

	// Call this member function to construct a CXTTrayIcon object.
	// 
	CXTTrayIcon();

	// Destructor - handles clean up.
	//
	virtual ~CXTTrayIcon();

protected:

	UINT		m_nDefIconID;	// Resource ID for the default icon.
	CString		m_strDefTip;	// Tooltip for the default icon.
	UINT		m_nArrSize;		// If animated, the size of the resource and string arrays.
	UINT		m_nCounter;		// Index counter for displaying animated icons.
	UINT		m_nIDEvent;		// Timer event ID
	UINT*		m_pIconArr;		// Points to an array of icon resource ID's.
	CString*	m_pStrTipArr;	// Points to an array of tooltip strings.

public:

	static CXTTrayIcon* m_pXTTrayIcon;

	// This member function will create the system tray icon.
	//
	virtual bool Create(
		// Tooltip text to display for the icon.
		LPCTSTR lpszCaption,
		// Array of flags that indicate which of the other members contain 
		// valid data. This member can be a combination of the following:
		// NIF_ICON    - The hIcon member is valid.  
		// NIF_MESSAGE - The uCallbackMessage member is valid. 
		// NIF_TIP	   - The szTip member is valid. 
		DWORD dwStyle,
		// Points to the window that will receive notification messages
		// associated with an icon in the taskbar status area. 
		CWnd* pParent,
		// Resource id for the tray icon.
		UINT nIconID);

	// This member function will set the tooltip text to display for the icon.
	//
	virtual void SetTooltip(
		// Tooltip text to display for the icon.
		CString strToolTip);

	// This member function will set the icon and action to perform on the
	// tray icon.
	//
	virtual void SetXTTrayIcon(
		// Resource id for the tray icon.
		UINT nIcon,
		// Action to perform on the icon, can be one of the following:
		// NIM_ADD	  - Adds an icon to the taskbar status area. 
		// NIM_DELETE - Deletes an icon from the taskbar status area. 
		// NIM_MODIFY - Changes the icon, tooltip text, or notification
		//				message identifier for an icon in the taskbar status
		//				area. 
		DWORD dwMessage=NIM_ADD);

	// This member function will stop the animation timer. Used with animated
	// icons.
	//
	virtual void KillTimer();

	// This member funtion will set the animation timer.
	//
	virtual void SetTimer(
		// Specifies a nonzero timer identifier.
		UINT nIDEvent,
		// Specifies the time-out value, in milliseconds.
		UINT uElapse);

	// This member function will set the icons used for animated system tray
	// icons. To use, call SetAnimateIcons then SetTimer.
	//
	virtual void SetAnimateIcons(
		// An array of resource ids that represent the icons to display in
		// the caption area.
		UINT* pIconArr,
		// An array of tooltips that match the icons passed in as pIconArr.
		CString* pStrTipArr,
		// Size of the array pIconArr.
		UINT nArrSize);

	// This callback function is used during animation and is private to this
	// class.
	//
	friend void CALLBACK TimerProc(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime);
};

#define TIN_TRAYICON		(WM_USER+1000)

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // #if !defined(__TRAYICON_H__)
