#include "stdafx.h"
#include "PagerCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPagerCtrl

CPagerCtrl::CPagerCtrl()
{
    if (bInitialized==false) {
        INITCOMMONCONTROLSEX icex;
        icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
        icex.dwICC = ICC_PAGESCROLLER_CLASS|ICC_BAR_CLASSES;
        ::InitCommonControlsEx(&icex);
        bInitialized = true;
    }
}

CPagerCtrl::~CPagerCtrl()
{
}

BEGIN_MESSAGE_MAP(CPagerCtrl, CWnd)
	//{{AFX_MSG_MAP(CPagerCtrl)
	ON_NOTIFY_REFLECT_EX(PGN_SCROLL,	OnPagerScroll)
	ON_NOTIFY_REFLECT_EX(PGN_CALCSIZE,	OnPagerCalcSize)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

bool CPagerCtrl::bInitialized = false;

BOOL CPagerCtrl::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID) 
{
    return CWnd::Create(WC_PAGESCROLLER, _T(""),
		dwStyle, rect, pParentWnd, nID);
}

/////////////////////////////////////////////////////////////////////////////
// CPagerCtrl message handlers

BOOL CPagerCtrl::OnPagerCalcSize(NMPGCALCSIZE* pNMPGCalcSize, LRESULT* pResult)
{
    *pResult = 0;

	switch(pNMPGCalcSize->dwFlag)
    {
	case PGF_CALCWIDTH:
		pNMPGCalcSize->iWidth = m_nWidth;
		break;
		
	case PGF_CALCHEIGHT:
		pNMPGCalcSize->iHeight = m_nHeight;
        break;
	}
	
	return 0;
}

BOOL CPagerCtrl::OnPagerScroll(NMPGSCROLL* pNMPGScroll, LRESULT* pResult)
{
    *pResult = 0;
	
  	switch(pNMPGScroll->iDir)
	{
	case PGF_SCROLLLEFT:
	case PGF_SCROLLRIGHT:
	case PGF_SCROLLUP:
	case PGF_SCROLLDOWN:
        break;
	}
	return 0;
}
