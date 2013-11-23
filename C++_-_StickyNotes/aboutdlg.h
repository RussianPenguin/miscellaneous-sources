// aboutdlg.h : interface of the CAboutDlg class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ABOUTDLG_H__E0325F50_A0EF_4726_820C_F22EC5E0C149__INCLUDED_)
#define AFX_ABOUTDLG_H__E0325F50_A0EF_4726_820C_F22EC5E0C149__INCLUDED_

class CAboutDlg : public CDialogImpl<CAboutDlg>
{
private:
	CHyperLink m_LinkMailto;

public:
	enum { IDD = IDD_ABOUTBOX };

	BEGIN_MSG_MAP(CAboutDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_CLOSE, OnClose)
		COMMAND_ID_HANDLER(IDOK, OnOK)
	END_MSG_MAP()

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		// Attach the hyper link object to the static control
		BOOL bRet = m_LinkMailto.SubclassWindow(GetDlgItem(IDC_ABOUT_MAILTO));
		ATLASSERT(bRet);
		// Initialize the hyper link
		m_LinkMailto.SetHyperLink(_T("mailto:stickysoft@yahoo.com"));
		m_LinkMailto.SetLabel(_T("Feedback"));

		CenterWindow(GetParent());
		return TRUE;
	}

	LRESULT OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		EndDialog(IDOK);
		return 0;
	}

	LRESULT OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		EndDialog(wID);
		return 0;
	}
};

#endif // !defined(AFX_ABOUTDLG_H__E0325F50_A0EF_4726_820C_F22EC5E0C149__INCLUDED_)
