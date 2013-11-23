//*************************************************************************
// CMenuEx.h : header file
// Version : 2.3
// Date : June 22, 1998
// Author : Brent Corkum
// 
// Portions of code supplied by:
// Ben Ashley,Girish Bharadwaj,Jean-Edouard Lachand-Robert,
// Robert Edward Caldecott,Kenny Goers,Leonardo Zide,
// Stefan Kuhr
//
// Bug Fixes:
// Stefan Kuhr,Martin Vladic,Kim Yoo Chul
//
// You are free to use/modify this code but leave this header intact.
//

#include <afxtempl.h>

#ifndef CMenuEx_H
#define CMenuEx_H

// CMenuExData class. Fill this class structure to define a single menu item:

#define MF_INVALIDFLAG	0x80000000 
#define MF_DRAWGRAYED	0x40000000
#define MF_LASTARROW	0x20000000
#define MF_USERMASK		0x0000ffff

class CMenuExData
{
public:
wchar_t *m_szMenuText;
CMenuExData () {menuIconNormal=-1;xoffset=-1;bitmap=NULL;
               nFlags=0;nID=0;syncflag=0;m_szMenuText=NULL;nFlagsEx=0;m_pExtraData=NULL;};
void SetAnsiString(LPCSTR szAnsiString);
void SetWideString(const wchar_t *szWideString);
const wchar_t *GetWideString(void) {return m_szMenuText;};
~CMenuExData ();
CString GetString(void);//returns the menu text in ANSI or UNICODE
int xoffset;
int menuIconNormal;
int nFlags,nID,syncflag,nFlagsEx;
void* m_pExtraData;
CImageList *bitmap;
};

//struct CMenuItemInfo : public MENUITEMINFO {
struct CMenuItemInfo : public 
//MENUITEMINFO 
#ifndef UNICODE   //SK: this fixes warning C4097: typedef-name 'MENUITEMINFO' used as synonym for class-name 'tagMENUITEMINFOA'
tagMENUITEMINFOA
#else
tagMENUITEMINFOW
#endif
    {
	CMenuItemInfo()
	{ memset(this, 0, sizeof(MENUITEMINFO));
	  cbSize = sizeof(MENUITEMINFO);
	}
};




typedef enum {Normal,TextOnly} HIGHLIGHTSTYLE;

#ifndef UNICODE
#define AppendODMenu AppendODMenuA
#define ModifyODMenu ModifyODMenuA
#else
#define AppendODMenu AppendODMenuW
#define ModifyODMenu ModifyODMenuW
#endif



class CMenuEx : public CMenu  // Derived from CMenu
{
	DECLARE_DYNAMIC(CMenuEx);
// Construction
public:
	CMenuEx(BOOL bDrawGrayed=FALSE,BOOL bShowLastArrow=FALSE); 
// Attributes
protected:
	CTypedPtrArray<CPtrArray, CMenuExData*> m_MenuList;  // Stores list of menu items 
// When loading an owner-drawn menu using a Resource, CMenuEx must keep track of
// the popup menu's that it creates. Warning, this list *MUST* be destroyed
// last item first :)

	CTypedPtrArray<CPtrArray, CMenuEx*>  m_SubMenus;  // Stores list of sub-menus 

	BOOL m_bDrawGrayed;
	BOOL m_bShowLastArrow;
	BOOL m_bDrawOnlyGray;

// Operations
public: 
// Overrides
// ClassWizard generated virtual function overrides
//{{AFX_VIRTUAL(CCustomMenu)
//}}AFX_VIRTUAL 
// Implementation
public:
	virtual BOOL InsertMenu( UINT nPosition, UINT nFlags, UINT nIDNewItem = 0, LPCTSTR lpszNewItem = NULL, UINT nFlagsEx=0xFFFF);
	void*& GetExtraDataPtr(UINT nPos);
	void UpdateGrayedOnly(CMenuEx* pMenu, BOOL b);
	BOOL AppendLastArrow();
	void EnableArrows(BOOL b){m_bEnableArrows=b;}
	BOOL IsEnableArrows(){return m_bEnableArrows;}
	int SetFlagsEx(UINT nPos,int nFlagsEx);
	BOOL CheckIfGrayedDraw(){return m_bDrawGrayed;}
	int FindMenuPos(CMenuEx *pMenu,CMenuEx* &pFather);
	void InsertLastArrows(CMenuEx *pMenu);
	void RemoveLastArrows(CMenuEx* pMenu);
	void EnableGrayedDraw(BOOL bEnable,BOOL bForce=FALSE);
	LRESULT TrapWindowProc(UINT nMsg, WPARAM wParam, LPARAM lParam);
	BOOL ModifyFlagsEx(int nID,int nFlagsEx, BOOL byPos=FALSE);
	virtual BOOL CreatePopupMenu();
	virtual BOOL CreateMenu();
	void DrawLastArrow(CDC* pDC, int x, int y, COLORREF color);
	void PostBuiltMenu(CMenuEx* pMenu);
	int FindMenuPos(CMenuExData* pData,CMenuEx*& pFather);
	BOOL CheckIfGrayed(CMenuEx* pMenu);
	BOOL ModifyODSeparator(UINT nPos,int nFlagsEx);
	int GetFlagsEx(UINT nPos);
	int GetMenuItemID(UINT nPos);
	int GetFlags(UINT nPos);
	virtual BOOL AppendMenu(UINT nFlags, UINT nIDNewItem=0, LPCTSTR lpszNewItem=NULL, UINT nFlagsEx=0);
	CMenuEx* GetSubMenu(UINT iPos);
	UINT GetMenuItemCount(){return (UINT)m_MenuList.GetSize()-1;};
	virtual BOOL DeleteMenu( UINT nPosition, UINT nFlags );
	virtual BOOL PreLoadMenu(LPCTSTR lpszResourceName);
	virtual BOOL PostLoadMenu();
	virtual BOOL PreLoadMenu(int nResource);
  static BOOL IsNewShell(void);
  void SetBitmapBackground(COLORREF color);
  void SetDisableOldStyle(void);
  void UnSetDisableOldStyle(void);
  BOOL GetDisableOldStyle(void);
  void UnSetBitmapBackground(void);
  int AddBitmapToImageList(CImageList *list,UINT nResourceID);
  BOOL LoadFromToolBar(UINT nID,UINT nToolBar,int& xoffset);
  void InsertSpaces(void);
  static LRESULT FindKeyboardShortcut(UINT nChar,UINT nFlags,CMenu *pMenu);
  static void UpdateMenu(CMenu *pmenu);
  BOOL IsMenu(CMenu *submenu);
  void DrawCheckMark(CDC *pDC,int x,int y,COLORREF color);
  void DrawRadioDot(CDC *pDC,int x,int y,COLORREF color);
  CMenuEx *FindMenuOption(int nId,int& nLoc);
  CMenuExData *FindMenuOption(wchar_t *lpstrText);
  BOOL GetMenuText(UINT id,CString &string);
  CImageList *checkmaps;
  BOOL checkmapsshare;
  int m_selectcheck;
  int m_unselectcheck;
  void LoadCheckmarkBitmap(int unselect,int select);
  void DitherBlt(HDC hdcDest, int nXDest, int nYDest, int nWidth, 
                 int nHeight, HBITMAP hbm, int nXSrc, int nYSrc);
  void DitherBlt2(CDC *drawdc, int nXDest, int nYDest, int nWidth, 
                  int nHeight, CBitmap &bmp, int nXSrc, int nYSrc);
  HBITMAP LoadSysColorBitmap(int nResourceId);

virtual ~CMenuEx();  // Virtual Destructor 
// Drawing: 
virtual void DrawItem( LPDRAWITEMSTRUCT);  // Draw an item
virtual void MeasureItem( LPMEASUREITEMSTRUCT );  // Measure an item

// Customizing:

void SetIconSize (int, int);  // Set icon size

BOOL AppendODMenuA(LPCSTR lpstrText, UINT nFlags = MF_OWNERDRAW, UINT nID = 0, int nIconNormal = -1, int nFlagsEx=0); // Owner-Drawn Append 

BOOL AppendODMenuW(wchar_t *lpstrText, UINT nFlags = MF_OWNERDRAW, UINT nID = 0, int nIconNormal = -1, int nFlagsEx=0); // Owner-Drawn Append 

BOOL ModifyODMenuA(const char *lpstrText,UINT nID=0,int nIconNormal=-1,int nFlagsEx=-1);
BOOL ModifyODMenuA(const char *lpstrText,const char *OptionText,int nIconNormal,int nFlagsEx=-1);
BOOL ModifyODMenuW(wchar_t *lpstrText,UINT nID=0,int nIconNormal=-1,int nFlagsEx=-1);
BOOL ModifyODMenuW(wchar_t *lpstrText,wchar_t *OptionText,int nIconNormal,int nFlagsEx=-1);
CMenuExData *NewODMenu(UINT pos,UINT nFlags,UINT nID,CString string);
void SynchronizeMenu(void);
void CMenuEx::InitializeMenuList(int value);
void CMenuEx::DeleteMenuList(void);
CMenuExData *CMenuEx::FindMenuList(UINT nID);
virtual BOOL LoadMenu(LPCTSTR lpszResourceName);  // Load a menu
virtual BOOL LoadMenu(int nResource);  // ... 
void AddFromToolBar(CToolBar* pToolBar, int nResourceID);
BOOL Draw3DCheckmark(CDC *dc, const CRect& rc,BOOL bSelected,
                     HBITMAP hbmCheck);
BOOL Draw3DCheckmark2(CDC *dc, const CRect& rc,BOOL bSelected, CBrush* pBrush,
                     HBITMAP hbmCheck);
BOOL LoadToolbar(UINT nToolBar);
BOOL LoadToolbars(const UINT *arID,int n);

// Destoying:

virtual BOOL DestroyMenu();

// Generated message map functions
protected:
int m_iconX,m_iconY;
COLORREF m_bitmapBackground;
BOOL m_bitmapBackgroundFlag;
BOOL disable_old_style;
private:
	BOOL m_bEnableArrows;
	COLORREF m_clrHlt;
	HGLOBAL hGlobal;
}; 

#endif

//*************************************************************************
