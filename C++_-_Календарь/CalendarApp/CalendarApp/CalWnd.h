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
/////////////////////////////////////////////////////////////////////////////


// CalWnd.h : header file
//


/////////////////////////////////////////////////////////////////////////////
// CCalWnd window


#ifndef __CALWND__
#define __CALWND__

static const UINT glbBtns=42;			// Number of buttons on calendar

enum Styles { Normal, Dimmed, Recessed };	// Button States

// Child -> Parent Event Messages
#define WM_DATE_NOTIFY	WM_APP + 0x00000001

// Control Ids
#define ID_SPIN_CAL		0x1000
#define ID_COMBO_MONTH	0x1002
#define ID_EDITYEAR		0x1003
#define ID_SPINYEAR		0x1004

// Popup Menu Ids
#define IDM_POPUP_SELECTED		0x1000
#define IDM_POPUP_TODAY			0x1001
#define IDM_POPUP_RESTORE		0x1002

#include "CalBtn.h"
#include "NoEdit.h"
#include "PopMenu.h"

#include <afxdisp.h>
#include <afxtempl.h>


enum WindowsVersion { UnSupported, Win95, Win98, WinNT, Win2K};

typedef CList<CCalBtn*, CCalBtn*> BtnList;
typedef CMap<COleDateTime, COleDateTime, CString, CString&> NoteList;

class CCalWnd : public CWnd
{
//////////////////////////////////////////////
// Public Interfaces
//////////////////////////////////////////////
public:
	// Public Interface
	CCalWnd();

	// Returns selected date
	COleDateTime	GetDate();

	// Toggle month spinner
	void			ShowSpinner(BOOL bShow);

	// Set selected date
	BOOL			SetDate(COleDateTime  tm);

	// Add a note behind a date
	BOOL			AddNote(COleDateTime& date, CString strNote, BOOL bReplace);

	// Remoe a note from behind a date
	void			DeleteNote(COleDateTime& date);

	// ClearAllNotes
	void			ClearAllNotes();

	// Spinner visibility test
	BOOL			IsSpinnerVisible();

	
protected:	

	virtual int  OnToolHitTest(CPoint point, TOOLINFO* pTI) const;
	CCalBtn*	 HitTest(CPoint& point);
	COleDateTime MakeDate(COleDateTime date = COleDateTime::GetCurrentTime());
	WindowsVersion GetOSVersion();


	NoteList			m_listNotes;
	BOOL				m_bTipInit;
	CPopMenu			m_PopMenu;
	BtnList				m_btnList;
	CRect				m_rc;
	BOOL				m_bSpinner;
	BOOL				m_bCapture;
	BOOL				m_bTrackLeave;
	int					m_nYear;
	int					m_nMonth;
	int					m_nCharWidth;
	int					m_nCharHeight;
	int					m_nEdge;
	
	COleDateTime m_cTime;
	COleDateTime m_rTime;
	COleDateTime m_sTime;
	COleDateTime m_timeMax;
	COleDateTime m_timeMin;

	CSpinButtonCtrl		m_btnCalendar;
	CSpinButtonCtrl		m_btnYear;
	CNoEdit				m_YearEdit;
	CComboBox			m_cboMonth;
	CFont				m_Font;
	CCalBtn*			m_pbtnSelected;
	CCalBtn*			m_pbtnHiLite;
	CCalBtn*			m_pbtnCurrent;


protected:
	BOOL			ValidateLimits(COleDateTime& tm);
	CRect			CreateCombo();
	COleDateTime	SyncDate(COleDateTime& cTime);
	void			UpdateControlCaptions(int nYear,int nMonth);
	void			SelectMonth(COleDateTime  tm,int nOffSet = 1 /*Default*/);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCalWnd)
	public:
	virtual afx_msg BOOL OnToolTipText(UINT nID, NMHDR* pNMHDR, LRESULT* pResult );
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCalWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CCalWnd)
	afx_msg void OnPaint();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSpinYear(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSpinCalendar(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeComboMonth();
	afx_msg void OnPopupToday();
	afx_msg void OnPopupSelected();
	afx_msg void OnPopupRestore();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	afx_msg LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

#endif // __CALWND__
/////////////////////////////////////////////////////////////////////////////
