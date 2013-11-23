#if !defined(AFX_COLOURPICKER_H__739148C1_233F_11D4_8B13_FFD8518DD348__INCLUDED_)
#define AFX_COLOURPICKER_H__739148C1_233F_11D4_8B13_FFD8518DD348__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ColourPicker.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CColourPicker window
typedef struct {
    COLORREF crColour;
    TCHAR    *szName;
} ColourTable;

#define MAX_COLOURS 41

//DrawCell Options
#define DRC_OVER -3
#define DRC_NORMAL -2
#define DRC_INNER -1
#define ST_CANCEL		WM_USER+500
#define ST_SELOK		WM_USER+501
#define ST_SELCHANGE    WM_USER+502

#define INVALID_COLOR -1



class CColourPicker : public CWnd
{
// Construction
public:
	CColourPicker();

// Attributes
public:

	    BOOL Create(CPoint p, COLORREF crColour, CWnd* pParentWnd, 
                LPCTSTR szDefaultText);

	static ColourTable m_crColours[];
	COLORREF	   m_SelectedColour;

	CString GetColorName(COLORREF fColor);

protected: 
	CRect		   m_ColorRect[MAX_COLOURS];
	CRect		   m_CustomRect;
	CRect		   m_WindowRect;
    COLORREF       m_crInitialColour;
    CToolTipCtrl   m_ToolTip;
    CWnd*          m_pParent;
	int			   m_CurSel,m_OldSel,m_Checked;
	BOOL		   IsPopupWindow;
	CFont          m_Font;
    CPalette       m_Palette;
	int            m_nBoxSize, m_nMargin;
	int			   m_nColumns,m_nRows;
	int			   m_DefSel;
	CString		   m_DefString;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColourPicker)
	public:
		virtual void ShowWindow(int nCmdShow);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
COLORREF GetColor()							{return m_crColours[m_Checked].crColour;}

protected:
	LPCTSTR GetColourName(int nIndex)           { return m_crColours[nIndex].szName; }
	void CloseWindow(int nType);
	void GetIndexFromColor(COLORREF fnColor);
	void SetStartPos(CPoint point);
	void CreateToolTips();
	void Initialise();
	void DrawCell(int nType, CDC* pDC,int nIndex);
	void SetSelection(int nIndex);
	int GetCurrentIndex(CPoint point);
	void InitRect();
	COLORREF GetColour(int nIndex)              { return m_crColours[nIndex].crColour; }
	int GetColumn(int nIndex){return nIndex % m_nColumns; }
	int GetRow(int nIndex) { return nIndex / m_nColumns;}
	int GetIndex(int row,int col)				{return row*MAX_COLOURS + col;}

public:
	virtual ~CColourPicker();

	// Generated message map functions
protected:
	//{{AFX_MSG(CColourPicker)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnNcDestroy();
	afx_msg void OnPaint();
	afx_msg void OnActivateApp(BOOL bActive, HTASK hTask);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLOURPICKER_H__739148C1_233F_11D4_8B13_FFD8518DD348__INCLUDED_)
