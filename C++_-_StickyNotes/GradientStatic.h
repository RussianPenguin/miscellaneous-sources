// GradientStatic.h : interface for the CGradientStatic class.
//
/////////////////////////////////////////////////////////////////////////////
//
// Original CGradientStatic Class written by Irek Zielinski (www.codeproject.com)
// Port to WTL by Igor Vigdorchik 
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRADIENTSTATIC_H__0709E3A1_C8B6_11D6_B74E_004033A0FB96__INCLUDED_)
#define AFX_GRADIENTSTATIC_H__0709E3A1_C8B6_11D6_B74E_004033A0FB96__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef UINT (CALLBACK * LPFNDLLFUNC1)(HDC, CONST PTRIVERTEX, DWORD, CONST PVOID, DWORD, DWORD);

class CGradientStatic : public CWindowImpl<CGradientStatic, CStatic>
{
protected:
	int m_nLeftSpacing;
	long m_lLeft;
	long m_lRight;
	long m_lText;
	int m_nAlign;
	HINSTANCE m_hinst_msimg32;
	BOOL m_bCanDoGradientFill;
	LPFNDLLFUNC1 m_dllfunc_GradientFill;	
	HFONT m_hFont;
	
	static void DrawGradRect(CDC * pDC, CRect rc, COLORREF clrLeft, COLORREF clrRight);

public:
	CGradientStatic();

	~CGradientStatic();

	BEGIN_MSG_MAP(CGradientStatic)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
		MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
	END_MSG_MAP()

	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	void SetWindowText(LPCSTR szpStr);

	void SetColor(long l) { m_lLeft = l; };

	void SetGradientColor(long l) { m_lRight = l; };

	void SetTextColor(long l) { m_lText = l; };

	void SetReverseGradient();

	void SetLeftSpacing(int nNoOfPixels) { m_nLeftSpacing = nNoOfPixels; };

	void SetTextAlign(int nAlign) { m_nAlign = nAlign; }; //0 - left, 1 - center, 2 -right

	void ChangeFont();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRADIENTSTATIC_H__0709E3A1_C8B6_11D6_B74E_004033A0FB96__INCLUDED_)
