// BitmapButton.h: CButtonEx implementation.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BITMAPBUTTON_H__2412D479_780C_4EBD_9912_B7DF2298E628__INCLUDED_)
#define AFX_BITMAPBUTTON_H__2412D479_780C_4EBD_9912_B7DF2298E628__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
//
// Original CButtonEx Class written by Serge Kandakov (www.rsdn.ru)
// Very small modifications by Igor Vigdorchik 
//
/////////////////////////////////////////////////////////////////////////////

// Bitmap button extended styles
#define BTNEX_HCENTER		0x00000040
#define BTNEX_VCENTER		0x00000080
#define BTNEX_LEFTIMAGE		0x00000100
#define BTNEX_RIGHTIMAGE	0x00000200
#define BTNEX_TOPIMAGE		0x00000400
#define BTNEX_BOTTOMIMAGE	0x00000800
#define BTNEX_CHECKBUTTON	0x00001000

template <class T>
class ATL_NO_VTABLE CButtonExImpl : public CBitmapButtonImpl<T>
{
public:
	DECLARE_WND_SUPERCLASS(NULL, T::GetWndClassName())

	// Constructor/Destructor
	CButtonExImpl(DWORD dwExtendedStyle = BMPBTN_AUTOSIZE)
	: CBitmapButtonImpl<T>(dwExtendedStyle),
		m_hFont(NULL), m_crText(0), m_bChecked(false), m_dwBDownPos(-1)
	{}

	// Overridden to provide proper initialization
	BOOL SubclassWindow(HWND hWnd)
	{
		BOOL bRet = CBitmapButtonImpl<T>::SubclassWindow(hWnd);
		HWND parent = GetParent();
		if (parent)
			m_hFont = (HFONT)SendMessage(parent, WM_GETFONT, 0, 0);
		return bRet;
	}

	// Attributes
	DWORD GetExtendedStyle() const { return m_dwExtendedStyle; }

	DWORD SetExtendedStyle(DWORD dwExtendedStyle, DWORD dwMask = 0)
	{
		DWORD dwPrevStyle = m_dwExtendedStyle;
		if(dwMask == 0)
			m_dwExtendedStyle = dwExtendedStyle;
		else
			m_dwExtendedStyle = (m_dwExtendedStyle & ~dwMask) | (dwExtendedStyle & dwMask);
		return dwPrevStyle;
	}

	void SetFont(HFONT hFont) { m_hFont = hFont; }

	void SetTextColor(COLORREF crText) { m_crText = crText; }
	
	BOOL CreateImages(_U_STRINGorID bitmap, int cx, int nGrow, COLORREF crMask = CLR_NONE)
	{
		HBITMAP hbmp = ::LoadBitmap(_Module.GetResourceInstance(), bitmap.m_lpstr);
		if (hbmp == NULL)
			return false;
		BITMAP bmp;
		::GetObject(hbmp, sizeof(BITMAP), &bmp);
		BOOL bRes = 
		m_ImageList.Create(cx, bmp.bmHeight, bmp.bmBitsPixel | ILC_MASK, 0, nGrow);
		if (bRes)
			bRes = m_ImageList.Add(hbmp, crMask) != -1;
		::DeleteObject(hbmp);
		return bRes;
	}

	BOOL SizeToImage()
	{
		m_dwExtendedStyle |= BMPBTN_AUTOSIZE;
		return CBitmapButtonImpl< T >::SizeToImage();
	}
	
	BOOL IsChecked()
	{
		return (m_dwExtendedStyle & BTNEX_CHECKBUTTON) && m_bChecked;
	}

	void SetChecked(BOOL bCheck = true)
	{
		m_bChecked = bCheck;
	}

	// Message map and handlers
	BEGIN_MSG_MAP(thisClass)
		MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBackground)
		MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
		MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
		MESSAGE_HANDLER(WM_LBUTTONDBLCLK, OnLButtonDblClk)
		CHAIN_MSG_MAP(CBitmapButtonImpl<T>)
	END_MSG_MAP()	

	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		m_dwBDownPos = lParam;
		return CBitmapButtonImpl<T>::OnLButtonDown(uMsg, wParam, lParam, bHandled);
	}

	LRESULT OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		if (m_dwBDownPos != -1)
		{
			m_bChecked ^= true;
			m_dwBDownPos = -1;
		}
		return CBitmapButtonImpl<T>::OnLButtonUp(uMsg, wParam, lParam, bHandled);
	}

	LRESULT OnLButtonDblClk(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		m_dwBDownPos = lParam;
		return CBitmapButtonImpl<T>::OnLButtonDblClk(uMsg, wParam, lParam, bHandled);;
	}
	
	LRESULT OnEraseBackground(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
#ifndef _BTNEX_MEMPAINT_
		CDCHandle dc((HDC)wParam);
		CRect rc;
		GetClientRect(&rc);
		dc.FillSolidRect(&rc, ::GetSysColor(IsChecked() ? COLOR_3DHILIGHT : COLOR_3DFACE));
#endif
		return 1;	// no background needed
	}

	void DoPaint(CDCHandle wnddc)
	{
		CRect rc;
		GetClientRect(&rc);
		TCHAR text[256];
		GetWindowText(text, 256);

		BOOL bHover = IsHoverMode();
		BOOL bImage = ((m_ImageList.m_hImageList != NULL) && (m_nImage[0] != -1)) ? true : false;

		BOOL bText = lstrlen(text) != 0 && !(m_dwExtendedStyle & BMPBTN_AUTOSIZE) ? true : false;
		BOOL bDisabled = !IsWindowEnabled();
		CSize szImage(0);
		CSize szText(0);
		CSize szBoth(0);
		int x = 0, y = 0;
		CDCHandle dc;

#ifdef _BTNEX_MEMPAINT_
		dc.CreateCompatibleDC(wnddc);
		CBitmap bmpMem;
		bmpMem.CreateCompatibleBitmap(wnddc, rc.Width(), rc.Height());
		HBITMAP bmpOld = dc.SelectBitmap(bmpMem);
		dc.FillSolidRect(&rc, ::GetSysColor(IsChecked() ? COLOR_3DHILIGHT : COLOR_3DFACE));
#else
		dc = wnddc;
#endif

		HFONT fntOld = NULL;
		if (bText && m_hFont)
		{
			// Draw color
			dc.FillSolidRect(&rc, m_clrBkgnd);

			fntOld = dc.SelectFont(m_hFont);
			dc.GetTextExtent(text, lstrlen(text), &szText);
		}

		if (bImage)
			m_ImageList.GetIconSize(szImage);

		if (bText && bImage)
		{
			if (m_dwExtendedStyle & BTNEX_LEFTIMAGE || m_dwExtendedStyle & BTNEX_RIGHTIMAGE)
			{
				szBoth.cx = szText.cx + szImage.cx;
				szBoth.cy = szText.cy < szImage.cy ? szImage.cy : szText.cy;
			}
			else if (m_dwExtendedStyle & BTNEX_TOPIMAGE || m_dwExtendedStyle & BTNEX_BOTTOMIMAGE)
			{
				szBoth.cx = szText.cx < szImage.cx ? szImage.cx : szText.cx;
				szBoth.cy = szText.cy + szImage.cy;
			}
		}
		else if (bImage) szBoth = szImage;
		else if (bText) szBoth = szText;

		x = m_dwExtendedStyle & BTNEX_HCENTER ? (rc.Width() - szBoth.cx) / 2 : 0;
		y = m_dwExtendedStyle & BTNEX_VCENTER ? (rc.Height() - szBoth.cy) / 2 : 0;
		
		if (bImage)			
		{
			int nImage = -1;
			if(m_fPressed == 1 || IsChecked() && !bDisabled)
				nImage = m_nImage[_nImagePushed] != -1 ? m_nImage[_nImagePushed] : m_nImage[_nImageFocusOrHover];
			else if((!bHover && m_fFocus == 1) || (bHover && m_fMouseOver == 1))
				nImage = m_nImage[_nImageFocusOrHover];
			else if(bDisabled)
				nImage = IsChecked() && (m_nImage[_nImagePushed] != -1) ? 
						m_nImage[_nImagePushed] : m_nImage[_nImageDisabled];
			if(nImage == -1)	// not there, use default one
				nImage = m_nImage[_nImageNormal];

	
			// Draw the button image
			int xyPos = 0;
			if((m_fPressed == 1 || IsChecked()) && 
				((m_dwExtendedStyle & (BMPBTN_AUTO3D_SINGLE | BMPBTN_AUTO3D_DOUBLE)) != 0) 
				&& (m_nImage[_nImagePushed] == -1))
				xyPos = 1;
			
			int xi = x, yi = y;
			if (m_dwExtendedStyle & BTNEX_LEFTIMAGE)
				xi = x;
			else if (m_dwExtendedStyle & BTNEX_RIGHTIMAGE)
				xi = x + szText.cx;
			else if (m_dwExtendedStyle & BTNEX_TOPIMAGE)
				{xi += (szBoth.cx - szImage.cx) /2; yi = y;}
			else if (m_dwExtendedStyle & BTNEX_BOTTOMIMAGE)
				{xi += (szBoth.cx - szImage.cx) /2; yi += szText.cy;}

			HICON hIcon = m_ImageList.GetIcon(nImage);

			if (bDisabled && m_nImage[_nImageDisabled] == -1)
				dc.DrawState(CPoint(xi + xyPos, yi + xyPos), szImage, hIcon, DST_ICON | DSS_DISABLED);
			else
				dc.DrawState(CPoint(xi + xyPos, yi + xyPos), szImage, hIcon, DST_ICON);

			::DestroyIcon(hIcon);

			bImage = true;
		}


		if (!(m_dwExtendedStyle & BMPBTN_AUTOSIZE) && bText)
		{
			dc.SetBkMode(TRANSPARENT);
			dc.SetTextColor(m_crText);
			
			int xyPos = m_fPressed || IsChecked() ? 1 : 0;
			int xt = x, yt = y;

			if (m_dwExtendedStyle & BTNEX_LEFTIMAGE)
				{xt += szImage.cx; yt += (szBoth.cy - szText.cy) / 2;}
			else if ((m_dwExtendedStyle & BTNEX_RIGHTIMAGE) && bImage)
				{yt += (szBoth.cy - szText.cy) / 2;}
			else if (m_dwExtendedStyle & BTNEX_TOPIMAGE)
				{xt += (szBoth.cx - szText.cx) / 2; yt += szImage.cy;}
			else if (m_dwExtendedStyle & BTNEX_BOTTOMIMAGE)
				{xt += (szBoth.cx - szText.cx) / 2;}
				
				
			dc.DrawState(CPoint(xt + xyPos, yt + xyPos), szText, text, bDisabled ? DSS_DISABLED : 0);
		}
		
		// Draw 3D border if required
		if((m_dwExtendedStyle & (BMPBTN_AUTO3D_SINGLE | BMPBTN_AUTO3D_DOUBLE)) != 0)
		{
			RECT rect;
			GetClientRect(&rect);
			HBRUSH hbr = ::CreateSolidBrush(GetSysColor(COLOR_3DFACE));

			if(m_fPressed == 1 || IsChecked())
				dc.DrawEdge(&rect, ((m_dwExtendedStyle & BMPBTN_AUTO3D_SINGLE) != 0) ? BDR_SUNKENOUTER : EDGE_SUNKEN, BF_RECT);
			else if(!bHover || m_fMouseOver == 1)
				dc.DrawEdge(&rect, ((m_dwExtendedStyle & BMPBTN_AUTO3D_SINGLE) != 0) ? BDR_RAISEDINNER : EDGE_RAISED, BF_RECT);
			

			if(!bHover && m_fFocus == 1)
			{
				::InflateRect(&rect, -2 * ::GetSystemMetrics(SM_CXEDGE), -2 * ::GetSystemMetrics(SM_CYEDGE));
				dc.DrawFocusRect(&rect);
			}
			::DeleteObject(hbr);
		}

		dc.SelectFont(fntOld);

#ifdef _BTNEX_MEMPAINT_
		wnddc.BitBlt(0, 0, rc.Width(), rc.Height(), dc, 0, 0, SRCCOPY);
		dc.SelectBitmap(bmpOld);
		dc.DeleteDC();
#endif
	}

	// Set the current color
	void SetColor(const COLORREF clrNewColor)
	{
		m_clrBkgnd = clrNewColor;
		Invalidate(FALSE);
	}

	// Get the current color
	COLORREF GetColor() const
	{
		return m_clrBkgnd;
	}

private:
	HFONT m_hFont;
	COLORREF m_crText;
	BOOL m_bChecked;
	DWORD m_dwBDownPos;

	COLORREF m_clrBkgnd;	// background color
};

class CButtonEx : public CButtonExImpl<CButtonEx>
{
public:
	DECLARE_WND_SUPERCLASS(_T("WTL_ButtonEx"), GetWndClassName())

	CButtonEx(DWORD dwExtendedStyle = BMPBTN_AUTO3D_SINGLE | BMPBTN_HOVER | BTNEX_VCENTER | 
				BTNEX_HCENTER | BTNEX_LEFTIMAGE) : 
		CButtonExImpl<CButtonEx>(dwExtendedStyle)
	{}
};

#endif // !defined(AFX_BITMAPBUTTON_H__2412D479_780C_4EBD_9912_B7DF2298E628__INCLUDED_)
