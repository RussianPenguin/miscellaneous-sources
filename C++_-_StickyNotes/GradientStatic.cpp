// GradientStatic.cpp : implementation of the CGradientStatic class.
//

#include "stdafx.h"
#include "GradientStatic.h"

CGradientStatic::CGradientStatic()
{
	ATLTRACE(_T("CGradientStatic::CGradientStatic()\n"));

	m_nLeftSpacing = 10;
	m_lLeft = GetSysColor(COLOR_ACTIVECAPTION);
	m_lRight = GetSysColor(COLOR_BTNFACE);
	m_lText = GetSysColor(COLOR_CAPTIONTEXT);

	m_nAlign = 0;
	m_hFont = 0;

	m_hinst_msimg32 = LoadLibrary("msimg32.dll");
	m_bCanDoGradientFill = FALSE;

	if (m_hinst_msimg32)
	{
		m_bCanDoGradientFill = TRUE;		
		m_dllfunc_GradientFill = ((LPFNDLLFUNC1)GetProcAddress(m_hinst_msimg32, "GradientFill"));
	}
}

CGradientStatic::~CGradientStatic()
{
	ATLTRACE(_T("CGradientStatic::~CGradientStatic()\n"));

	FreeLibrary(m_hinst_msimg32);

	if (m_hFont)
	{
		if (!::DeleteObject(m_hFont))
			ATLTRACE(_T("Font was not destroyed!\n"));
	}
}

// This function will be used only if msimg32.dll library is not available
void CGradientStatic::DrawGradRect(CDC * pDC, CRect rc, COLORREF clrLeft, COLORREF clrRight)
{
	CRect rcStep;								// rectangle for color's band
	COLORREF clrColor;							// color for the bands
	float fStep = ((float)rc.Width())/255.0f;	// width of color's band

	for (int nOnBand = 0; nOnBand < 255; nOnBand++) 
	{
		// Set a current band
		SetRect(&rcStep,
				rc.left+(int)(nOnBand * fStep), 
				rc.top,
				rc.left+(int)((nOnBand+1)* fStep), 
				rc.bottom);	

		// Set a current color
		clrColor = RGB((GetRValue(clrRight) - GetRValue(clrLeft)) * ((float)nOnBand) / 255.0f + GetRValue(clrLeft),
			(GetGValue(clrRight) - GetGValue(clrLeft)) * ((float)nOnBand) / 255.0f + GetGValue(clrLeft),
			(GetBValue(clrRight) - GetBValue(clrLeft)) * ((float)nOnBand) / 255.0f + GetBValue(clrLeft));

		// Fill a current band
		pDC->FillSolidRect(rcStep, clrColor);
	}
}

LRESULT CGradientStatic::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) 
{
	CPaintDC dc(m_hWnd); // device context for painting

	CRect rect;
	GetClientRect(&rect);

	if (m_bCanDoGradientFill) //msimg32.dll library is loaded
	{

		TRIVERTEX rcVertex[2];
		rcVertex[0].x = rect.left;
		rcVertex[0].y = rect.top;
		rcVertex[0].Red = GetRValue(m_lLeft)<<8;	// color values from 0x0000 to 0xff00 !!!!
		rcVertex[0].Green = GetGValue(m_lLeft)<<8;
		rcVertex[0].Blue = GetBValue(m_lLeft)<<8;
		rcVertex[0].Alpha = 0x0000;
		rcVertex[1].x = rect.right; 
		rcVertex[1].y = rect.bottom;
		rcVertex[1].Red = GetRValue(m_lRight)<<8;
		rcVertex[1].Green = GetGValue(m_lRight)<<8;
		rcVertex[1].Blue = GetBValue(m_lRight)<<8;
		rcVertex[1].Alpha = 0;

		GRADIENT_RECT rect;
		rect.UpperLeft = 0;
		rect.LowerRight = 1;

		// Fill the area 
		m_dllfunc_GradientFill(dc, rcVertex, 2, &rect, 1, GRADIENT_FILL_RECT_H);		
	}
	else
	{
		// msimg32.dll is not available. Let's use our own code to display gradient background.
		// This code is very simple and produces worse gradient that function from the library - but works!
		DrawGradRect(&dc, rect, m_lLeft, m_lRight);
	}

	// Select a new font
	HFONT hOldFont = 0;
	if (m_hFont)
		hOldFont = (HFONT)::SelectObject(dc, m_hFont);

	// Let's set color defined by user
	::SetTextColor(dc, m_lText);

	TCHAR szTEXT[512];
	GetWindowText(szTEXT, sizeof(szTEXT)/sizeof(TCHAR));

	::SetBkMode(dc, TRANSPARENT);
	GetClientRect(&rect);

	rect.DeflateRect(0, -5);

	if (m_nAlign == 1) // center
		::DrawText(dc, szTEXT, -1, &rect, DT_SINGLELINE|DT_VCENTER|DT_CENTER);
	else if (m_nAlign == 0) // left
	{
		rect.left += m_nLeftSpacing;
		::DrawText(dc, szTEXT, -1, &rect, DT_SINGLELINE|DT_VCENTER|DT_LEFT);
	}
	else //right
	{
		rect.right -= m_nLeftSpacing;
		::DrawText(dc, szTEXT, -1, &rect, DT_SINGLELINE|DT_VCENTER|DT_RIGHT);
	}

	if (hOldFont)
		::SelectObject(dc, hOldFont);

	return 0;
}

LRESULT CGradientStatic::OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	// Eliminate the flicker during resizing
	return 1;
}

void CGradientStatic::SetReverseGradient()
{
	ATLASSERT(::IsWindow(m_hWnd));

	COLORREF clrTemp = m_lLeft;
	m_lLeft = m_lRight;
	m_lRight = clrTemp;
}

void CGradientStatic::SetWindowText(LPCSTR szpStr)
{
	ATLASSERT(::IsWindow(m_hWnd));

	CStatic::SetWindowText(szpStr);
	Invalidate();
}

void CGradientStatic::ChangeFont()
{
	ATLASSERT(::IsWindow(m_hWnd));

	LOGFONT lf;

	// Get the font that this control is currently using
	CFontHandle font = GetFont();
	ATLASSERT(font.m_hFont);

	if (font.m_hFont)
	{
		// Retrieve a copy of the LOGFONT structure for a currently selected font
		if (!font.GetLogFont(&lf))
		{
			ATLTRACE(_T("Retrieving a LOGFONT failed.\n"));
			return;
		}

		// Modify the LOGFONT members
		lf.lfHeight = 4;
		lf.lfWeight = FW_BOLD;

		// Create the new font
		m_hFont = ::CreateFontIndirect(&lf);
		ATLASSERT(m_hFont);
	}
}
