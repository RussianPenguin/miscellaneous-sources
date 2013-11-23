/////////////////////////////////////////////////////////////////////////////
//
// Disclaimer Notice
// ------------------
// The Author cannot guarantee this software is error free.
// The author also disclaims all responsibility for damages or 
// loss of profits caused by the failure of this software
//. Your usage of these modifications indicates your willingness to 
// accept complete responsibility.
//
//
// Developed by: Norm Almond for www.codeproject.com 
//
// Please use this software freely, if you fix or make any modifications to
// the software you can let me know so I can improve future versions.
//
// Version 1.00 - First Release 24 Nov 2000
//
/////////////////////////////////////////////////////////////////////////////

// Btn.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCalBtn window

#ifndef __BTN__
#define __BTN__

class CCalBtn
{
// Construction
public:
	CCalBtn(CRect& rc, CWnd *pWnd);

// Attributes
public:
	void			Check(BOOL bCheck=TRUE);
	void			SetState(Styles type,COleDateTime tm);
	Styles			GetStyle() { return m_Style; }
	COleDateTime	GetDate() { return m_btnTime; }
	void			Reset();
	void			DrawItem(CDC* pDC);
	
	void			Unfocus();
	void			Focus();
	BOOL			HitTest(CPoint& point);
	void			Select();
	CString			GetTipText();
	void			SetHover(BOOL bHover);
	void			SetNote(const CString& strNote);
	CRect			GetRect() { return m_rcWnd; }


protected:
	CWnd*			m_pWnd;
	UINT			m_nDay;
	CString			m_strDay;
	CString			m_strNote;
	BOOL			m_bState;
	Styles			m_Style;
	BOOL			m_bFocus;
	COleDateTime	m_btnTime;
	CRect			m_rcWnd;
	BOOL			m_bHover;
	enum WindowsVersion { UnSupported, Win95, Win98, WinNT, Win2K};

// Operations
public:

// Implementation
public:
	virtual ~CCalBtn();

};

#endif // __BTN__
/////////////////////////////////////////////////////////////////////////////

