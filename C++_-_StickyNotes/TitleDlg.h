// TitleDlg.h: interface for the CTitleDlg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TITLEDLG_H__94049C2C_1F4F_41EB_BA36_B1FFD32EF146__INCLUDED_)
#define AFX_TITLEDLG_H__94049C2C_1F4F_41EB_BA36_B1FFD32EF146__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTitleDlg : public CDialogImpl<CTitleDlg> 
{
public:
	enum { IDD = IDD_TITLEDLG };

	TCHAR m_szTitle[(MAX_STRING_LEN + 1) * sizeof(TCHAR)];	// buffer that will receive the text

	CTitleDlg()
	{
		ATLTRACE(_T("CTitleDlg::CTitleDlg()\n"));
	}

	~CTitleDlg()
	{
		ATLTRACE(_T("CTitleDlg::~CTitleDlg()\n"));
	}

	BEGIN_MSG_MAP(CTitleDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_CLOSE, OnClose)
		COMMAND_ID_HANDLER(IDOK, OnOK)
		COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
	END_MSG_MAP()

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		CenterWindow(GetParent());
		return TRUE;
	}

	LRESULT OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		EndDialog(IDCANCEL);
		return 0;
	}

	LRESULT OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		int nLen;
		
		// Retrieve the text from the edit control
		nLen = GetDlgItemText(IDC_TITLE_EDIT, m_szTitle, (MAX_STRING_LEN) * sizeof(TCHAR));
		if (nLen == FALSE)
			ATLTRACE(_T("GetWindowText() failed\n"));

		EndDialog(wID);
		return 0;
	}

	LRESULT OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		EndDialog(wID);
		return 0;
	}
};

#endif // !defined(AFX_TITLEDLG_H__94049C2C_1F4F_41EB_BA36_B1FFD32EF146__INCLUDED_)
