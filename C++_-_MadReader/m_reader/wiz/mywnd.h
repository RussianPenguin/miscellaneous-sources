#if !defined(AFX_MYWND_H__0DEB6452_EF57_11D3_9AAA_81685D466B46__INCLUDED_)
#define AFX_MYWND_H__0DEB6452_EF57_11D3_9AAA_81685D466B46__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyWnd.h : header file
//
//#include "wiz.h"
//#include "wizDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CReadWnd window

class CReadWnd : public CWnd
{
// Construction
public:
	CReadWnd();

// Attributes
public:
//	CStatic *m_stat;	
	

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReadWnd)
	public:
	virtual BOOL DestroyWindow();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
    DWORD f_pos;
    CRect RECT_arrow;
    CPen *pPenOld;
    CFont fnt2;
    CBrush pBrs;
    CPen pPen;
    CRect lead;

    int ms2 , line_back ;
    double milisec2;
    short line[200];
	bool afterHLP;
    //bool 
    CRect r;
	bool hidecursor;
	void timer_1sec(int mode, int sum, bool run);

	//bool speed_start;
	int page_sec;
    int pages_read;
    int aver_page_sec;
	int words_in_page;

    int aver_speed2,aver_speed3;

	int GetWordsCnt(char* s);
	HCURSOR m_sizecur;
	CRect info;
	void draw_info();
	void show_curr_page(int i, int i2);
	DWORD read_hide(int i, CString& s1);
	void from_edit2(WPARAM param);
	void draw_bm_lable(UINT i);
	int page_kb;
	char filename[MAX_PATH];
	//SYSTEMTIME time;
	CString stat;
	CString& GetStatName(short ch);
	void draw_arrow();
    void draw_runner_lead(CPoint pnt);
	bool tip;
	int timer,timer2;
	void Seek_to(UINT page);
    void Seek_toPage(UINT page);
	int get_pagenum();
	CRectTracker tr;
	bool track;
	void prepare_tracker();
	DWORD get_dim();
	int line_y;
	void sizes(int &x, UINT &y);
	bool change_font();
	bool change_color();
	short get_decode();
	bool update_viewPort(UINT x);
	bool isOpened();
	CWnd* par;
	bool res;
	bool SetDimens(int pg);
	bool readnext(short n);
	int RedFile(LPTSTR name,UINT charset);
	CFile f;
	
	bool BringUP();
	POINT p;	
	COLORREF clr_fnt,clr_bc;
    HBRUSH bc,bc2;
	CFont fnt;
	int metX,metY;

	char buff1[15002];
	char buff[8502];
	//LONG  pos,pos2;
	UINT pages,cnt;
	CDWordArray cash;
	bool eof;

	CEdit *m_edit;
	virtual ~CReadWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CReadWnd)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnClose();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
    afx_msg BOOL OnSetCursor( CWnd* pWnd, UINT nHitTest, UINT message );
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	bool read_page(bool show = true);
	bool decode(char *s);
	UINT decod;
};
CReadWnd* mainwnd3();

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYWND_H__0DEB6452_EF57_11D3_9AAA_81685D466B46__INCLUDED_)
