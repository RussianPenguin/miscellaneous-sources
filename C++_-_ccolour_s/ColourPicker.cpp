// ColourPicker.cpp : implementation file
//

#include "stdafx.h"
#include "ColourPicker.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColourPicker

ColourTable CColourPicker::m_crColours[] = 
{
	{ RGB(255,255,255),				_T("Default Colour")    },
    { RGB(0x00, 0x00, 0x00),		_T("Black")             },
    { RGB(0xA5, 0x2A, 0x00),    _T("Brown")             },
    { RGB(0x00, 0x40, 0x40),    _T("Dark Olive Green")  },
    { RGB(0x00, 0x55, 0x00),    _T("Dark Green")        },
    { RGB(0x00, 0x00, 0x5E),    _T("Dark Teal")         },
    { RGB(0x00, 0x00, 0x8B),    _T("Dark blue")         },
    { RGB(0x4B, 0x00, 0x82),    _T("Indigo")            },
    { RGB(0x28, 0x28, 0x28),    _T("Dark grey")         },

    { RGB(0x8B, 0x00, 0x00),    _T("Dark red")          },
    { RGB(0xFF, 0x68, 0x20),    _T("Orange")            },
    { RGB(0x8B, 0x8B, 0x00),    _T("Dark yellow")       },
    { RGB(0x00, 0x93, 0x00),    _T("Green")             },
    { RGB(0x38, 0x8E, 0x8E),    _T("Teal")              },
    { RGB(0x00, 0x00, 0xFF),    _T("Blue")              },
    { RGB(0x7B, 0x7B, 0xC0),    _T("Blue-grey")         },
    { RGB(0x66, 0x66, 0x66),    _T("Grey - 40")         },

    { RGB(0xFF, 0x00, 0x00),    _T("Red")               },
    { RGB(0xFF, 0xAD, 0x5B),    _T("Light orange")      },
    { RGB(0x32, 0xCD, 0x32),    _T("Lime")              }, 
    { RGB(0x3C, 0xB3, 0x71),    _T("Sea green")         },
    { RGB(0x7F, 0xFF, 0xD4),    _T("Aqua")              },
    { RGB(0x7D, 0x9E, 0xC0),    _T("Light blue")        },
    { RGB(0x80, 0x00, 0x80),    _T("Violet")            },
    { RGB(0x7F, 0x7F, 0x7F),    _T("Grey - 50")         },

    { RGB(0xFF, 0xC0, 0xCB),    _T("Pink")              },
    { RGB(0xFF, 0xD7, 0x00),    _T("Gold")              },
    { RGB(0xFF, 0xFF, 0x00),    _T("Yellow")            },    
    { RGB(0x00, 0xFF, 0x00),    _T("Bright green")      },
    { RGB(0x40, 0xE0, 0xD0),    _T("Turquoise")         },
    { RGB(0xC0, 0xFF, 0xFF),    _T("Skyblue")           },
    { RGB(0x48, 0x00, 0x48),    _T("Plum")              },
    { RGB(0xC0, 0xC0, 0xC0),    _T("Light grey")        },

    { RGB(0xFF, 0xE4, 0xE1),    _T("Rose")              },
    { RGB(0xD2, 0xB4, 0x8C),    _T("Tan")               },
    { RGB(0xFF, 0xFF, 0xE0),    _T("Light yellow")      },
    { RGB(0x98, 0xFB, 0x98),    _T("Pale green ")       },
    { RGB(0xAF, 0xEE, 0xEE),    _T("Pale turquoise")    },
    { RGB(0x68, 0x83, 0x8B),    _T("Pale blue")         },
    { RGB(0xE6, 0xE6, 0xFA),    _T("Lavender")          },
    { RGB(0xFF, 0xFF, 0xFF),    _T("White")             },
	{ RGB(0xFF, 0xFF, 0xFF),    _T("White")             },
	{ RGB(0xE6, 0xE6, 0xFA),    _T("Lavender")          }
};


CColourPicker::CColourPicker()
{
//	Initialise();
	IsPopupWindow=TRUE;
	m_OldSel=m_CurSel=0;
}

CColourPicker::~CColourPicker()
{
	m_Font.DeleteObject();
    m_Palette.DeleteObject();
}


BEGIN_MESSAGE_MAP(CColourPicker, CWnd)
	//{{AFX_MSG_MAP(CColourPicker)
	ON_WM_KEYDOWN()
	ON_WM_KILLFOCUS()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_NCDESTROY()
	ON_WM_PAINT()
	ON_WM_ACTIVATEAPP()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CColourPicker message handlers

BOOL CColourPicker::Create(CPoint p, COLORREF crColour, CWnd* pParentWnd, 
                LPCTSTR szDefaultText)
{
	// TODO: Add your specialized code here and/or call the base class
		
    ASSERT(pParentWnd && ::IsWindow(pParentWnd->GetSafeHwnd()));
//    ASSERT(pParentWnd->IsKindOf(RUNTIME_CLASS(CColourPicker)));

    m_pParent  = pParentWnd;
    m_crInitialColour = crColour;
	m_DefString=szDefaultText;

    // Get the class name and create the window
    CString szClassName = AfxRegisterWndClass(CS_CLASSDC|CS_SAVEBITS|CS_HREDRAW|CS_VREDRAW,
                                              0,
                                              (HBRUSH) (COLOR_BTNFACE+1), 
                                              0);

    if (!CWnd::CreateEx(0, szClassName, _T(""), WS_VISIBLE|WS_POPUP, 
                        p.x, p.y, 100, 100, // size updated soon
                        pParentWnd->GetSafeHwnd(), 0, NULL))
        return FALSE;

	Initialise();
	CreateToolTips();

	SetStartPos(p);
	GetIndexFromColor(crColour);

  // Capture all mouse events for the life of this window
    SetCapture();
	m_CurSel=0;

    return TRUE;
}

int CColourPicker::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	
	return 0;
}

void CColourPicker::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	 int row = GetRow(m_CurSel);
	 int col = GetColumn(m_CurSel);
	 int m_Rows=m_nRows-1;
	 

	 CClientDC dc(this);
	 

	if(nChar==VK_DOWN)
	{
		if(m_CurSel==0)m_CurSel++;
		else
		{
			m_CurSel+=m_nColumns;
			if(m_CurSel>MAX_COLOURS-1)
			{
			   if(row==m_Rows-1)m_CurSel=MAX_COLOURS-1;
			   else m_CurSel=0;

			}
		}
	SetSelection(m_CurSel);
	}
	
	if(nChar==VK_UP)
	{
		if(m_CurSel==0)m_CurSel=MAX_COLOURS-1;
		else
		{
			m_CurSel-=m_nColumns;
			if(m_CurSel<0)m_CurSel=0;
		}
	SetSelection(m_CurSel);
	}

	if(nChar == VK_LEFT)
	{
		m_CurSel--;
		if(m_CurSel<0)m_CurSel=MAX_COLOURS-1;
	SetSelection(m_CurSel);
	}

	if(nChar == VK_RIGHT)
	{
		m_CurSel++;
		if(m_CurSel>MAX_COLOURS-1)m_CurSel=0;
	SetSelection(m_CurSel);
	}

	if(nChar==VK_RETURN || nChar == VK_SPACE)
	{
		m_Checked=m_CurSel;
		if(m_Checked==INVALID_COLOR)CloseWindow(ST_CANCEL);
		CloseWindow(ST_SELOK);
	}

	if(nChar==VK_ESCAPE)
	   CloseWindow(ST_CANCEL);
	
}

void CColourPicker::OnKillFocus(CWnd* pNewWnd) 
{
	CWnd::OnKillFocus(pNewWnd);

	ReleaseCapture();
	CloseWindow(ST_CANCEL);	
}

void CColourPicker::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CWnd::OnLButtonUp(nFlags,point);
	CClientDC dc(this);
	int m_CustomSel=GetCurrentIndex(point);
	if(m_CustomSel==INVALID_COLOR)m_SelectedColour=m_crInitialColour;
	else
	{
		DrawCell(DRC_NORMAL,&dc,m_Checked);
		m_Checked=m_CurSel;
		DrawCell(DRC_INNER,&dc,m_Checked);

	}


	DWORD pos = GetMessagePos();
    point = CPoint(LOWORD(pos), HIWORD(pos));

    if (m_WindowRect.PtInRect(point))
        CloseWindow(ST_SELOK);
    else
        CloseWindow(ST_CANCEL);	
	
}

void CColourPicker::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	int m_CustomSel=GetCurrentIndex(point);
	if(m_CustomSel!=INVALID_COLOR)
	{
		m_CurSel=m_CustomSel;
		SetSelection(m_CurSel);
	}

	CWnd::OnMouseMove(nFlags, point);
}

void CColourPicker::OnNcDestroy() 
{
	CWnd::OnNcDestroy();
	delete this;	
}

void CColourPicker::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	CRect rect;
    GetClientRect(rect);
    dc.DrawEdge(rect, EDGE_RAISED, BF_RECT);
	for(int i=0;i<MAX_COLOURS;i++)
	DrawCell(DRC_NORMAL,&dc,i);	

	DrawCell(DRC_INNER,&dc,m_Checked);	
}
	// Do not call CWnd::OnPaint() for painting messages

void CColourPicker::InitRect()
{

	CRect rect;
    GetWindowRect(rect);
	//Set table sizes of picker
	m_nColumns=8;
	m_nRows = MAX_COLOURS/ m_nColumns;
    if (MAX_COLOURS-1 % m_nColumns) m_nRows++;
	
	//Set draw sizes of picker
    m_WindowRect.SetRect(rect.left, rect.top, 
                         rect.left + m_nColumns*m_nBoxSize + 2*m_nMargin,
                         rect.top  + (m_nRows-1)*m_nBoxSize + 2*m_nMargin+30);

	//Set buttons rect 
	m_ColorRect[0]=CRect(m_nMargin+1,m_nMargin+1,m_nMargin+m_nColumns*m_nBoxSize-1,m_nMargin+28);
	for(int i=0;i<MAX_COLOURS;i++)
	{
		m_ColorRect[i+1]=CRect(m_nMargin+GetColumn(i)*m_nBoxSize,
						  m_nMargin+30+GetRow(i)*m_nBoxSize,
						  m_nMargin+GetColumn(i)*m_nBoxSize+18,
						  m_nMargin+30+GetRow(i)*m_nBoxSize+18);
	}


}

int CColourPicker::GetCurrentIndex(CPoint point)
{

	//Search current Index from POINT
	for(int i=0;i<MAX_COLOURS;i++)
		if(m_ColorRect[i].PtInRect(point))return i;

		return INVALID_COLOR;
}

void CColourPicker::SetSelection(int nIndex)
{
//	if(nIndex<0 || nIndex>MAX_COLOURS)return;
	CString str;
	CClientDC dc(this);
	m_CurSel=nIndex;
	//IS it first change current button and if it not current and not first
	if(m_CurSel!=m_OldSel || IsPopupWindow)
	{

	 if(m_Checked==m_OldSel)DrawCell(DRC_INNER,&dc,m_Checked);
	else
	    DrawCell(DRC_NORMAL,&dc,m_OldSel);

	DrawCell(DRC_OVER,&dc,m_CurSel);

	m_OldSel=m_CurSel;
	}

	
	//Store current selection 
	m_pParent->SendMessage(ST_SELCHANGE,(WPARAM)m_crColours[m_CurSel].crColour,0); 
	
	//First start id false
	IsPopupWindow=FALSE;

}


void CColourPicker::DrawCell(int nType, CDC *pDC,int nIndex)
{
	//Save the current rect in tempory 
	if(nIndex<0 || nIndex>MAX_COLOURS)return;

	m_CustomRect=m_ColorRect[nIndex];
	
	switch(nType)
	{
		//Draw over button
		case DRC_OVER:
		pDC->DrawEdge(m_ColorRect[nIndex],BDR_RAISEDINNER,BF_RECT);
		m_CustomRect.DeflateRect(1,1,1,1);
		pDC->FillSolidRect(m_CustomRect,::GetSysColor(COLOR_3DFACE));
		break;

		//Draw normal, usualy button
		case DRC_NORMAL:
		pDC->FillSolidRect(m_ColorRect[nIndex],::GetSysColor(COLOR_3DFACE));
		break;

		//Draw inner button
		case DRC_INNER:
			pDC->DrawEdge(m_ColorRect[nIndex],BDR_SUNKENOUTER,BF_RECT);
			m_CustomRect.DeflateRect(1,1,1,1);
			pDC->FillSolidRect(m_CustomRect,::GetSysColor(COLOR_3DHILIGHT));

		break;

		default:
		break;
	}

	m_CustomRect=m_ColorRect[nIndex];

    CPalette* pOldPalette = NULL;
    if (pDC->GetDeviceCaps(RASTERCAPS) & RC_PALETTE)
    {
        pOldPalette = pDC->SelectPalette(&m_Palette, FALSE);
        pDC->RealizePalette();
    }

    if(nIndex!=0)
	{
	//Draw Color Bar
	CBrush brush(PALETTERGB(GetRValue(GetColour(nIndex)), 
                            GetGValue(GetColour(nIndex)), 
                            GetBValue(GetColour(nIndex)) ));
	
    CPen   pen;
    pen.CreatePen(PS_SOLID, 1, ::GetSysColor(COLOR_3DSHADOW));

    CBrush* pOldBrush = (CBrush*) pDC->SelectObject(&brush);
    CPen*   pOldPen   = (CPen*)   pDC->SelectObject(&pen);

    // Draw the cell colour
    m_CustomRect.DeflateRect(m_nMargin+1, m_nMargin+1);
    pDC->Rectangle(m_CustomRect);

    // restore DC and cleanup
    pDC->SelectObject(pOldBrush);
    pDC->SelectObject(pOldPen);
    brush.DeleteObject();
    pen.DeleteObject();

    if (pOldPalette && pDC->GetDeviceCaps(RASTERCAPS) & RC_PALETTE)
        pDC->SelectPalette(pOldPalette, FALSE);


	}
	else if(nIndex==0)
	{
		//Draw Text In Default Button
		CFont *pOldFont = (CFont*) pDC->SelectObject(&m_Font);
        pDC->SetBkMode(TRANSPARENT);
		pDC->DrawText(m_DefString,m_ColorRect[0],DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        pDC->SelectObject(pOldFont);
		
		//Draw line around text
		CRect SquareRect = m_ColorRect[0];
        SquareRect.DeflateRect(2*m_nMargin,2*m_nMargin);
        CPen pen(PS_SOLID, 1, ::GetSysColor(COLOR_3DSHADOW));
        CPen* pOldPen = pDC->SelectObject(&pen);
        pDC->SelectStockObject(NULL_BRUSH);
        pDC->Rectangle(SquareRect);
        pDC->SelectObject(pOldPen);
	}

}

void CColourPicker::ShowWindow(int nCmdShow)
{

		//IsPopupWindow=TRUE;
		//Make current selection in start position
		//m_CurSel=0;
		CWnd::ShowWindow(nCmdShow);
}

void CColourPicker::Initialise()
{
	
    m_nBoxSize          = 18;//Image button size
    m_nMargin           = ::GetSystemMetrics(SM_CXEDGE);

	//Create font
	NONCLIENTMETRICS ncm;
    ncm.cbSize = sizeof(NONCLIENTMETRICS);
    VERIFY(SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(NONCLIENTMETRICS), &ncm, 0));
    m_Font.CreateFontIndirect(&(ncm.lfMessageFont));

    // Create the palette
    struct
	{
        LOGPALETTE    LogPalette;
        PALETTEENTRY  PalEntry[MAX_COLOURS];
    } pal;

    LOGPALETTE* pLogPalette = (LOGPALETTE*) &pal;
    pLogPalette->palVersion    = 0x300;
    pLogPalette->palNumEntries = (WORD) MAX_COLOURS; 

    for (int i = 0; i < MAX_COLOURS; i++)
    {
        pLogPalette->palPalEntry[i].peRed   = GetRValue(m_crColours[i].crColour);
        pLogPalette->palPalEntry[i].peGreen = GetGValue(m_crColours[i].crColour);
        pLogPalette->palPalEntry[i].peBlue  = GetBValue(m_crColours[i].crColour);
        pLogPalette->palPalEntry[i].peFlags = 0;
    }

    m_Palette.CreatePalette(pLogPalette);

	InitRect(); //Init button and window rect
}

BOOL CColourPicker::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	m_ToolTip.RelayEvent(pMsg);

    // Sometimes if the picker loses focus it is never destroyed
    if (GetCapture()->GetSafeHwnd() != m_hWnd)
        SetCapture(); 

	return CWnd::PreTranslateMessage(pMsg);
}

void CColourPicker::CreateToolTips()
{

	if (!m_ToolTip.Create(this)) return;
	m_ToolTip.EnableToolTips();

	//m_ToolTip.SetDelayTime(500); Change time for draw tooltips

	//Add tooltips
	for(int i=0;i<MAX_COLOURS;i++)
	   m_ToolTip.AddTool(this, GetColourName(i), m_ColorRect[i], 1);
}

void CColourPicker::SetStartPos(CPoint point)
{
	//Get Width and Height of Screen
	CSize ScreenSize(::GetSystemMetrics(SM_CXSCREEN), ::GetSystemMetrics(SM_CYSCREEN));
	int cx=m_WindowRect.Width();
	int cy=m_WindowRect.Height();

	m_WindowRect.SetRect(point,CPoint(point.x+cx,point.y+cy));
	//Far right?
	if (m_WindowRect.right > ScreenSize.cx)
        m_WindowRect.OffsetRect(-(m_WindowRect.right - ScreenSize.cx), 0);

    // Too far left?
    if (m_WindowRect.left < 0)
        m_WindowRect.OffsetRect( -m_WindowRect.left, 0);

    // Bottom falling out of screen?
    if (m_WindowRect.bottom+30 > ScreenSize.cy)
    {
        /*CRect ParentRect;
        m_pParent->GetWindowRect(ParentRect)*/
        m_WindowRect.OffsetRect(0, -(m_WindowRect.Height()));
    }
	//Compare points
	MoveWindow(m_WindowRect.left,m_WindowRect.top,m_WindowRect.Width(),m_WindowRect.Height(),TRUE);

}

void CColourPicker::GetIndexFromColor(COLORREF fnColor)
{
	for(int i=0;i<MAX_COLOURS;i++)
	{
		//Return Index from Inital Color
		if(GetColour(i)==fnColor)
		{

			m_DefSel=m_Checked=i;
			return;
		}
	}

	m_Checked=0;
}

void CColourPicker::CloseWindow(int nType)
{

	if(nType==ST_CANCEL)m_Checked=m_DefSel;
		
	
	if(nType==ST_SELOK)
			m_SelectedColour=m_crColours[m_Checked].crColour;


	m_pParent->SendMessage(ST_SELOK,(WPARAM)m_SelectedColour,0); 

	DestroyWindow();
}

void CColourPicker::OnActivateApp(BOOL bActive, HTASK hTask) 
{
	CWnd::OnActivateApp(bActive, hTask);
	
	// TODO: Add your message handler code here
	if (!bActive)CloseWindow(ST_CANCEL);	
}

CString CColourPicker::GetColorName(COLORREF fColor)
{
		
	for(int i=0;i<MAX_COLOURS;i++)
	{
		//Return Index from Inital Color
		if(GetColour(i)==fColor)
				return 	(CString)m_crColours[i].szName;
		
	}

	return "Black";
}

