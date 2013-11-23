// wizDlg.h : header file
//

#if !defined(AFX_WIZDLG_H__0DEB644A_EF57_11D3_9AAA_81685D466B46__INCLUDED_)
#define AFX_WIZDLG_H__0DEB644A_EF57_11D3_9AAA_81685D466B46__INCLUDED_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wiz.h"
//#include "MyWnd.h"


/////////////////////////////////////////////////////////////////////////////
// CWizDlg dialog

class CWizDlg : public CDialog
{
	friend class CReadWnd;
	friend class CPropDlg;
// Construction	
public:
	HCURSOR cursor1;
	bool ctrl;

    CString templ_str;
	CRect p_rect;
	bool is_runpointer_enable();
	void get_file_settings(POSITION pos=0);
	void set_file_settings();
	bool showing;
	void CloseAlldlg();
	CDialog* activedlg;
	bool context_h;
	void ShowTools(int sTpage=0);
	bool exprd;
	void load_menu_ch();
	bool marked_page;
	void from_readerwnd(short v,int v1,int v2, char* v3);
	//UINT timer_sec_run;
	//int open_pos_x;
	bool first_e;
	bool check_bookm();
	void load_menub(POSITION ps=NULL);
	POSITION del_pos;
	//POSITION top;
	//
	HBITMAP b[7];
	void add_recent(CString &path);
	void open_recent();
	void save_recent();
	CMenu popup,bookm;
	void Load_menu();
	CRecnt Recents;
	
	void repos_all();
	void start_hide();
	void start_show();

   CWizDlg(CWnd* pParent = NULL);  // standard constructor   
   
   POINT pnt;
   int  metY,metX;
   bool minim;
   	bool dlg_start;
   int timer,timer2,timer3;

   CReadWnd wnd; 
   CMenu code;
   char str1[300]; 
   //CCmdUI cm;

   struct f_s  
   {
	   LOGFONT fnt;	   
	   COLORREF clr,clr_bk;
	   char templ[500];	   
   };


   struct Parameters_struc  {
     CRect pos;         // размеры окна в координатах
     bool low_prior;    // 1 = приортет низкий
 
     bool systray;     //1=сувать в систрай     
	 short lines;
	 short decod;	 
  
	 int lastm;	 	 
	 bool askbookm;	   // show BookmtextDlg for bookm
	 bool run;         // Runner enable
	 int  runsec;      // next page period
	 bool lock_saver;  // don't allow screensaver
	 bool show_bm;     // show bookmark text on MyWnd when meet it
	 bool tips;        // show tips;
	 bool tip_day;     // show Tip of The day at Startup;
	 bool bigIcon;     // big iCons	 
	 bool openSUp;     // open at startup
	 bool jumpLast;    
	 bool AMpm;	       // AM PM time
	 f_s fonts[9];     // 0-head, 1-cont, 2-foot, 3-text, 4-info, 5-memo, 6-bookm, 7-save, 8-wind 
     short info_pos;   // InfoTip position
     //bool timer_st;
     //bool send_to;
     UINT run_kb;
     UINT run_wrd;
     int run_mode;   // 1-pg 2-byt 0- wrd 
     bool run_pointer; // Lead cursor
     int pos_panel;   
     char key[300];
     char owner[300];
     int date; // only 1 instance;
     int days;
	 //================
	 /*
	 char     fnt_name_head[50],fnt_name_cont[50],fnt_name_foot[50],fnt_name_info[50];
	 short    fnt_size_head,    fnt_size_cont,    fnt_size_foot,    fnt_size_info;
	 COLORREF fnt_clr_head,     fnt_clr_cont,     fnt_clr_foot,     fnt_clr_info;
	 int top,right,bott,left;

  */
	 //================

} Info;

	//	CStringArray Histor;


//	char  FILEMON_SETTINGS_KEY[]= ("Software\\MadReader");
//#define FILEMON_SETTINGS_KEY    TEXT("Software\\MadReader");
//#define FILEMON_SETTINGS_VALUE    TEXT("Settings");
//#define FILEMON_RECENT_CONNECT_VALUE  TEXT("Recent")




// Dialog Data
        //{{AFX_DATA(CWizDlg)
	enum { IDD = IDD_WIZ_DIALOG };
	CEdit	m_name;
	CStatic	m_prop;		
	//}}AFX_DATA

        // ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(CWizDlg)
	public:
	virtual BOOL DestroyWindow();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
        virtual void DoDataExchange(CDataExchange* pDX);        // DDX/DDV support
		virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	CToolTipCtrl m_tooltip;
	HICON m_hIcon;
		
        //mywnd2 wnd;


        // Generated message map functions
        //{{AFX_MSG(CWizDlg)
        virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void On_Options();
	afx_msg void OnButton3();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void Onhide();
	afx_msg void Onclose();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void Oncode();
	afx_msg void Onhist();
	afx_msg void OnUpdate1Dos(CCmdUI* pCmdUI);
	afx_msg void OnActivateApp(BOOL bActive, HTASK hTask);
	afx_msg void OnBookText();
	afx_msg void OnBookmm();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnEnterIdle(UINT nWhy, CWnd* pWho);
	//}}AFX_MSG
        DECLARE_MESSAGE_MAP()
private:
	short create_shorcut();	
	bool DafaultSettings();
	//DWORD ver;	
	bool showstat();
};

CWizDlg* maindlg3();

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WIZDLG_H__0DEB644A_EF57_11D3_9AAA_81685D466B46__INCLUDED_)
