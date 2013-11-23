// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__E40C032E_B6F1_450E_AE82_E001DF286256__INCLUDED_)
#define AFX_STDAFX_H__E40C032E_B6F1_450E_AE82_E001DF286256__INCLUDED_

// Change these values to use different versions
#define WINVER			0x0400
#define _WIN32_IE		0x0400
#define _RICHEDIT_VER	0x0300
#define _WIN32_WINNT	0x0400	// for WM_MOUSEWHEEL 

// For SetLayeredWindowAttributes, otherwise we need to #define _WIN32_WINNT 0x0500
// in stdafx.h and I do not want to do it
#define WS_EX_LAYERED           0x00080000
#define LWA_ALPHA               0x00000002

#include <atlbase.h>
#include <atlapp.h>

extern CAppModule _Module;

#include <atlwin.h>
#include <atlmisc.h>
#include <atlctrls.h>
#include <atlframe.h>
#include <atldlgs.h>
#include <atlprint.h>
#include <atlctrlx.h>
#include <TCHAR.h>

#include <vector>
#include <deque>
#include <map>
#include <algorithm>
#include <string>
#include <fstream>
using namespace std;

#define EMPTY_STRING		_T("")
	
#define MAX_STRING_LEN		24

// Colorref's used in the program
#define PINK			RGB(255,204,204)
#define GREEN			RGB(204,255,204)
#define BLUE			RGB(153,204,255)
#define YELLOW			RGB(255,255,204)
#define WHITE			RGB(255,255,255)
#define BLACK			RGB(  0,  0,  0)
#define GREY			RGB(125,125,125)

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__E40C032E_B6F1_450E_AE82_E001DF286256__INCLUDED_)
