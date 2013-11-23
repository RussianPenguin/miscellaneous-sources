// wiz.h : main header file for the WIZ application
//

#if !defined(AFX_WIZ_H__0DEB6448_EF57_11D3_9AAA_81685D466B46__INCLUDED_)
#define AFX_WIZ_H__0DEB6448_EF57_11D3_9AAA_81685D466B46__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

#define  head_f 0;
#define  cont_f 1;
#define  footf_f 2;
#define  text_f 3;
#define  info_f 4;
#define  memo_f 5;
#define  bookm_f 6;
// 0-head, 1-cont, 2-foot, 3-text, 4-info, 5-memo, 6-bookm, 7-save, 8-wind 

/////////////////////////////////////////////////////

// CWizApp:
// See wiz.cpp for the implementation of this class
//

class CWizApp : public CWinApp
{
public:
	CWizApp();		

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWizApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CWizApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
class CBookm:public CObject
{
protected:
        CBookm();
        DECLARE_SERIAL(CBookm);
public:
        CBookm(CString pth, long ps, long pg);
        virtual void Serialize(CArchive& ar);
        virtual ~CBookm();		
        long pos,page;		
		CString name;        
};
typedef CTypedPtrList<CObList,CBookm*> CBookmark;

class CRecent:public CObject
{
	long charset;
	CString path;      
	CString Memo;  
	CRect viewPort;
	CBookmark bookmarks;

protected:
        CRecent();
        DECLARE_SERIAL(CRecent);
public:	
	bool add_memo(CString &s);
	void del_at(UINT pos);
	CRect& GetViewPort();
	long& GetCharset();
	CString& GetPath();
	CString& GetMemo();
	bool jmp_next();
	void jmp_to(UINT bm);
	void load_menu_bm(CStringList &bList);
	void change_top(CString &name, long pos, long page);
	int bookms_count();
	short is_page_bookmarked(long pos,long cnt);
	void add_bookm(CString &name,long pos,long page);

	void fill_curr_bookmark();	
	bool del_curr_bookm();	
	CRecent(CString pth);		
	virtual void Serialize(CArchive& ar);
	virtual ~CRecent();			

	CString cur_bname;
	long cur_pos,cur_page;		

	POSITION bookm_pos;
};
typedef CTypedPtrList<CObList,CRecent*> CRecnt;


bool SaveSettings( void* p, int size);
bool GetSettings(void* p, int size);
bool choose_font(LOGFONT *fnt, COLORREF &clr, HWND own);
bool choose_color(COLORREF &clr, HWND own);
char* decode_b64(char *ss);
void export_text(CString &s, CWnd* par = NULL);
void add_memo(CString &s);
void parse_templ(CString& s1, char* templ, CString& txt1 = CString(""), short nom = 0);
int hash(char *s );
//CWizDlg* maindlg3();

#include "MyWnd.h"
#include "wizDlg.h"


/////////////////////////////////////////////////////////////////////////////


//CWizDlg* maindlg2;
//CReadWnd* mainwnd2;  


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WIZ_H__0DEB6448_EF57_11D3_9AAA_81685D466B46__INCLUDED_)
