// NoteDlg.h : interface of the CNoteDlg class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_NOTEDLG_H__85AE4B78_EF35_4D56_AB32_BB7986674ECF__INCLUDED_)
#define AFX_NOTEDLG_H__85AE4B78_EF35_4D56_AB32_BB7986674ECF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "StaticNote.h"
#include "NoteEdit.h"
#include "Note.h"
#include "NoteButton.h"

// The return value of the HitTest function is one of the following values,
// indicating the position of the cursor hot spot. 
#define	HT_NOWHERE		0	// On the screen background 
#define	HT_LEFT			1	// In the left border of a resizable dialog 
							// (the user can click the mouse to resize the dialog horizontally)
#define	HT_RIGHT		2	// In the right border of a resizable dialog 
							// (the user can click the mouse to resize the dialog horizontally)
#define	HT_TOP			3	// In the upper-horizontal border of a dialog
							// (the user can click the mouse to resize the dialog vertically)
#define	HT_TOPLEFT		4	// In the upper-left corner of a dialog border
							// (the user can click the mouse to resize the dialog diagonally)
#define	HT_TOPRIGHT		5	// In the upper-right corner of a dialog border
							// (the user can click the mouse to resize the dialog diagonally)
#define	HT_BOTTOM		6	// In the lower-horizontal border of a resizable dialog 
							// (the user can click the mouse to resize the dialog vertically)
#define	HT_BOTTOMLEFT	7	// In the lower-left corner of a border of a resizable dialog 
							// (the user can click the mouse to resize the dialog diagonally)
#define	HT_BOTTOMRIGHT	8	// In the lower-right corner of a border of a resizable dialog 
							// (the user can click the mouse to resize the dialog diagonally)
#define HT_BAR			9	// In the bar area
							// (the user can move the dialog)

// Constant value used to determine if we should delete ourselves later.
#define DEFERDELETE 2

class CHiddenWindow;

// CNoteDlg class represents the note window
class CNoteDlg : public CDialogImpl<CNoteDlg>,
				 public CMessageFilter, 
				 public CIdleHandler,
				 public CPrintJobInfo,
				 public CNote
{
private:
	CHiddenWindow * m_pWndParent;			// pointer to the parent hidden window

	BYTE m_bAutoDelete;						// it tells us if we want to auto-delete ourselves
	bool m_bClosing;						// indicates if a note is being closed
	bool m_bDeleted;						// indicates if a note has been deleted

	CStaticNote m_wndStaticNote;			// static control, it holds 'Note' image
	CStaticDateTime m_wndStaticDateTime;	// static control, it displays date and time
	CGradientStatic m_wndStaticBar;			// static control, I call it a bar, used to move the dialog
	CNoteEdit m_wndEdit;					// edit control

	CButtonExPin m_wndBtnPin;				// bitmap button, it keeps the note on top of other windows
	CButtonExClose m_wndBtnClose;			// bitmap button, it closes the note
	
	HCURSOR m_hCursor;
	HBITMAP m_hBmpNote;
	HBITMAP m_hBmpPinopen;
	HBITMAP m_hBmpPinclose;
	HBITMAP m_hBmpPinhoover;

	HFONT m_hFontClose;						// font for the 'Close' button

	int m_nSizeFrame;

	CBrush m_brBkgnd;						// brush for the dialog's background color

	int m_nHeight;							// dialog's full height
	int m_nWidth;							// dialog's full width

	typedef BOOL (__stdcall *PFUNCSETLAYEREDWINDOWATTR)(HWND, COLORREF, BYTE, DWORD);
	PFUNCSETLAYEREDWINDOWATTR m_pfSetLayeredWindowAttributes;

	CPrinter m_Printer;
	CDevMode m_DevMode;
	CRect m_rcMargin;
	CSimpleValArray<long> m_arrPages;

public:
	enum { IDD = IDD_NOTEDLG };

	CNoteDlg(CHiddenWindow * pWnd);

	CNoteDlg(CHiddenWindow * pWnd, const CNote& objNote);

	~CNoteDlg();

protected:

	virtual BOOL PreTranslateMessage(MSG* pMsg)
	{
		// Application is getting closed - save the note
		if (pMsg->message == WM_COMMAND && pMsg->wParam == 32903)
			OnSave(true);

		return FALSE;
	}

	virtual BOOL OnIdle()
	{
		return FALSE;
	}

	BEGIN_MSG_MAP(CNoteDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_CLOSE, OnClose)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
		MESSAGE_HANDLER(WM_CTLCOLORDLG, OnDlgColor)
		MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
		MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
		MESSAGE_HANDLER(WM_SIZE, OnSize)
		MESSAGE_HANDLER(WM_GETMINMAXINFO, OnGetMinMaxInfo)
		MESSAGE_HANDLER(WM_COMMAND, OnCommand)
		NOTIFY_CODE_HANDLER(EN_LINK, OnLink)
		MESSAGE_HANDLER(WM_LBUTTONDBLCLK, OnLButtonDblClk)
		MESSAGE_HANDLER(WMU_GETCOLOR, OnGetColor)
		MESSAGE_HANDLER(WMU_GETALPHA, OnGetAlpha)
		MESSAGE_HANDLER(WMU_SETTOPMOST, OnSetTopMost)
		MESSAGE_HANDLER(WM_ACTIVATE, OnActivateWindow)
		MESSAGE_HANDLER(WM_SETFOCUS, OnFocus)
		// When a control sends its parent a message, the parent can 
		// reflect the message back to the control
		REFLECT_NOTIFICATIONS()
	END_MSG_MAP()

	WNDPROC GetDialogProc();

	void InitDefaultValues();
	
	static LRESULT CALLBACK NoteDialogProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	void CloseDialog(int nVal);

	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnDlgColor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	int HitTest(CPoint point);

	LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnLButtonDblClk(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnLink(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnActivateWindow(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnGetColor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnGetAlpha(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnSetTopMost(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	void OnNewNote();

	void OnChangeBkgndColor(COLORREF clrColor);

	void OnSetFont();

	void OnSetTitle();

	void OnSave(bool bSaveAll);

	void OnDelete();

	void OnSaveToFile();

	void OnImportFromFile();

	void UnselectText();

	HBITMAP ReplaceColor (HBITMAP hBmp, COLORREF cOldColor, COLORREF cNewColor, HDC hBmpDC = NULL);

	bool IsDialogFullSize(CRect& rcNote, CRect& rcBar);

	void MakeTransparent(int nAlpha);

	bool LayoutPages();

	void OnPageSetup();

	void OnPrint();

	bool PrintPage(UINT nPage, HDC hDC);

	void SetTopMost();

	void SaveNoteText();

	void SaveNotePosition();

	bool IsAppClosing();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NOTEDLG_H__85AE4B78_EF35_4D56_AB32_BB7986674ECF__INCLUDED_)
