#if !defined(CPAGERCTRL_H_INCLUDED)
#define CPAGERCTRL_H_INCLUDED

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#if _MSC_VER < 1200 // VC++ 5 support, not needed for VC++ 6
#include "comm_control.h"
#endif

/////////////////////////////////////////////////////////////////////////////
// CPagerCtrl window

class CPagerCtrl : public CWnd
{
// Construction
public:
	CPagerCtrl();
	virtual ~CPagerCtrl();

// Attributes
protected:
	static bool bInitialized;
	CWnd* m_pChild;
	int m_nWidth;
	int m_nHeight;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPagerCtrl)
	public:
	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetScrollArea (int nWidth, int nHeight) { m_nWidth = nWidth; m_nHeight = nHeight; }
	void SetChild(HWND hWnd){Pager_SetChild(m_hWnd, hWnd);}
	void RecalcSize(){Pager_RecalcSize(m_hWnd);}
	void ForwardMouse(bool bForward){Pager_ForwardMouse(m_hWnd,bForward);}
	COLORREF SetBkColor(COLORREF clr){return Pager_SetBkColor(m_hWnd,clr);}
	COLORREF GetBkColor(){return Pager_GetBkColor(m_hWnd);}
	int SetBorder(int iBorder){return Pager_SetBorder(m_hWnd,iBorder);}
	int GetBorder(){return Pager_GetBorder(m_hWnd);}
	int SetPos(int iPos){return Pager_SetPos(m_hWnd,iPos);}
	int GetPos(){return Pager_GetPos(m_hWnd);}
	int SetButtonSize(int iSize){return Pager_SetButtonSize(m_hWnd,iSize);}
	int GetButtonSize(){return Pager_GetButtonSize(m_hWnd);}
	DWORD GetButtonState(int iButton){return Pager_GetButtonState(m_hWnd,iButton);}


	// Generated message map functions
protected:
	//{{AFX_MSG(CPagerCtrl)
	virtual BOOL OnPagerScroll(NMPGSCROLL* pNMPGScroll, LRESULT * pResult);
	virtual BOOL OnPagerCalcSize(NMPGCALCSIZE * pNMPGCalcSize, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(CPAGERCTRL_H_INCLUDED)
