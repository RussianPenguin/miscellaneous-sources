#include "stdafx.h"
#include "popmenu.h"
#include "calwnd.h"

CPopMenu::CPopMenu()
{
	CreatePopupMenu( );
	AppendMenu(MF_ENABLED|MF_STRING,IDM_POPUP_SELECTED, _T("Goto &Selected"));
	AppendMenu(MF_ENABLED|MF_STRING,IDM_POPUP_TODAY, _T("Goto &Today"));
	AppendMenu(MF_SEPARATOR);
	AppendMenu(MF_ENABLED|MF_STRING,IDM_POPUP_RESTORE, _T("&Restore Selected"));
}

CPopMenu::~CPopMenu()
{
	DestroyMenu();
}