// dialogDlg.cpp : implementation file
// by Zarembo Maxim
// email: mzarembo@iba.com.by
// www: http://maxim.z.tripod.com/
// ICQ: 64569598

#include "stdafx.h"
#include "dialog.h"
#include "dialogDlg.h"

#include <stdio.h>
#include "iphlpapi.h"
#include <winsock.h>
//#include <winsock2.h>

char def[256]="\0";
char def2[512]="\0";

//////////////���������� ��� ������///////////////////////////////////
//����� ��� ����� ��� ����������� ������������� ���� ��� ����� ���������
//������������ ������ ��� �������,
//���� �� �� �� ������������ �����, �� �� ������ �������� ��� ����������
//��� ��� ��� ��������������� ������ ������� ��� ������� ������� access
//������ ����� ������� ����������, � ��������� ������� ����� ����������, ��������
//��� ������ �� �� �� ������ ����� ��������� �� ���������, � ��� �� ��������
//������ ������� ������� ��� ������������� �� ������ ������� 
HANDLE hThread;
DWORD dwCount, dwThreadId;
DWORD ThreadFunc(LPVOID lParam);
//////////////////////Client+Server////////////////////
#define DEF_HOSTADDR "127.0.0.1" //������� LOOPBACK-��� IP ������, �.�. ���������� ������ ���������� ��� ������� ���������

    int PORT=3182; //���� TCP, ������ ��� ����������� ����
	char S[256]="\0"; //����� ��� �������� � �� ������������ � ���������� ���������
	char Stemp[256]="\0";//��������� �����
	SOCKET ss, cc, r; //������ ��� ����������� ����
	sockaddr_in Addr; ////���������� ��������� ������ � ����� ��� �������� � ����� ������
	WSADATA Wsa; //���������� ��� ������������� winsock
    bool server; //���������� ��� ����������� ������ ������ ���������: ������ ��� ������
//////////////////////////////////////////////////////////
//��������� ��� ���������� � �������� ����������� ��� �������� ����� 
//IP ������� �� ����� �������, ����������� �������� �� NT4 ��� 
//�������� ��� ������������ ��������� IP ������, ���������������
//���������� ��� ����������� �������� �� NT4. Windows2000 ������������
//��� ������� ���������.
//����������� ��������� ���� ������� �� ������ ���������� � PDK �� Microsoft

    ULONG NTEContext=0;
    ULONG NTEInstance;
    IPAddr NewIP;
    IPAddr NewMask;
    DWORD Index;
    CHAR NewIPStr[64];
    CHAR NewMaskStr[64];

    PIP_ADAPTER_INFO pAdapterInfo, pAdapt;
    PIP_ADDR_STRING pAddrStr;
    DWORD AdapterInfoSize;
    DWORD Err;
    BOOL OptList = FALSE;
    BOOL OptAdd = FALSE;
    BOOL OptDel = FALSE;

DWORD Context = Index = (DWORD)-1;

/////////////////////////////////////////////////////////////////////////////
// CDialogDlg dialog

CDialogDlg::CDialogDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogDlg)
	m_Address = _T("");
	m_Mask = _T("");
	m_Interface = _T("");
	m_Ms = _T("");
	m_Mr = _T("");
	m_Port = 0;
	//}}AFX_DATA_INIT
}

void CDialogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogDlg)
	DDX_Text(pDX, IDC_EDIT1, m_Address);
	DDX_Text(pDX, IDC_EDIT2, m_Mask);
	DDX_Text(pDX, IDC_EDIT3, m_Interface);
	DDX_Text(pDX, IDC_MS, m_Ms);
	DDX_Text(pDX, IDC_MR, m_Mr);
	DDX_Text(pDX, IDC_EDIT4, m_Port);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDialogDlg, CDialog)
	//{{AFX_MSG_MAP(CDialogDlg)
	ON_BN_CLICKED(IDNEW, OnNew)
	ON_BN_CLICKED(IDDELETE, OnDelete)
	ON_BN_CLICKED(IDPING, OnPing)
	ON_BN_CLICKED(IDINFO, OnInfo)
	ON_BN_CLICKED(IDSEND, OnSend)
	ON_BN_CLICKED(IDC_SERVER, OnServer)
	ON_BN_CLICKED(IDC_CLIENT, OnClient)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDHELP, OnHelp)
	ON_EN_CHANGE(IDC_EDIT4, OnChangeEdit4)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogDlg message handlers

BOOL CDialogDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

    if(WSAStartup(0x0101,&Wsa)) AfxMessageBox("Cannot init WinSock"); //������������� Winsock. ��� ���� ������� ���� �������� �� �����. ������ �������� ��-�� ������������ ��������� ���� ��� ���������� �������� ����� winsock.dll

    SetTimer(1,1000,NULL); //������� �������� �������, ����� ��� ����� ��������� ����� ��������� ������ ���������, ����� ����� 1 �������

	//������������� ��������� ���� ���������, ������ � ����� ��� �������� � ����� ������
	Addr.sin_family=AF_INET;
	Addr.sin_addr.s_addr=INADDR_ANY;
	Addr.sin_port=htons(PORT);

	m_Port=PORT;
    m_Address=DEF_HOSTADDR; //� ����� IP ADRESS ������������� ����� LOOPBACK �� ��������� 127.0.0.1, �.�.��������� �����
    m_Mask="255.255.255.0"; //� ����� MASK ������� ����� ����
	m_Interface="2"; //� ����� � Interface ������� ���������, ���������� 2, ����������� ��� �������� ��������������� ������ IP ������ ��������� �� ������ ����������, ����� ������� INFO
	UpdateData(false); 

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDialogDlg::OnNew() //�������� ������ ���������� � ����� IP �������
{
	UpdateData(true);
	NewIP = inet_addr(m_Address);//������� ������ ��������������� IP ������, ����� ������ �� ���� IP ADRESS
    NewMask = inet_addr(m_Mask);//������� ����� ����
	Index=atoi(m_Interface);//������� ����������
    if (AddIPAddress(NewIP, NewMask, Index, &NTEContext, &NTEInstance)) AfxMessageBox("Error add interface\nNot corect number interface or You use Windows 9X.\nThis function don't work in Windows 9X.");
    else {
		  sprintf(def,"�������� ����� %s",m_Address);
	      AfxMessageBox(def);
		 }  	
}

void CDialogDlg::OnDelete() //�������� ���������� ����������
{
	UpdateData(true);	
	Index=atoi(m_Interface);//��� �������� ��� ���������� ���������� ����� ���������� � ���� � Interface, ���� �� ��������� 1-�� ���������, �� ����� ��� ������� � ����������� �������� ���� ������ 3
    if (DeleteIPAddress(Index)) AfxMessageBox("Error delete interface\nNot corect number context or You use Windows 9X.\nThis function don't work in Windows 9X.");
    else {
		  sprintf(def,"����� ��������� �%d",Index);
		  AfxMessageBox(def);
		 }
}

void CDialogDlg::OnPing() //������ ������� PING ��� �������� ���������� ������
{
    UpdateData(true);
	NewIP = inet_addr(m_Address);
	sprintf(def,"ping %s -t",m_Address);
    WinExec(def,SW_NORMAL);	//������ ����������� ������� ping �� Microsoft
}

void CDialogDlg::OnInfo() //���������� �� ����������� �� ������ ����������, �������� � �� Win9X � Nt5.0, ��� Nt4.0 ����������� ����������� ����� route
{
    AdapterInfoSize = 0;
    if ((Err = GetAdaptersInfo(NULL, &AdapterInfoSize)) != 0)
    {
        if (Err != ERROR_BUFFER_OVERFLOW)
        {
            AfxMessageBox("Work's in Windows 2000 & Windows 9X");
			WinExec("cmd /k route print",SW_NORMAL);	//������ ����������� ������� route �� Microsoft, ������� ������� ���� �� ������� ���������, � ��� ��� �� �����������
            return;
        }
    }

    // Allocate memory from sizing information
    if ((pAdapterInfo = (PIP_ADAPTER_INFO) GlobalAlloc(GPTR, AdapterInfoSize)) == NULL)
    {
        AfxMessageBox("Memory allocation error");
        return;
    }

    // Get actual adapter information
    if ((Err = GetAdaptersInfo(pAdapterInfo, &AdapterInfoSize)) != 0)
    {
        AfxMessageBox("GetAdaptersInfo failed with error");
        return;
    }
	
    pAdapt = pAdapterInfo;

	  sprintf(def2,"MAC Address - Adapter\n"
            "Index     Context   Ip Address          Subnet Mask\n"
            "--------------------------------------------------------------\n");

    while (pAdapt)
	{
		   for (UINT i=0; i<pAdapt->AddressLength; i++)
            {
                if (i == (pAdapt->AddressLength - 1))
				{
                    sprintf(def,"%.2X - ",(int)pAdapt->Address[i]);
					strcat(def2,def);
				}    
                else
				{
                    sprintf(def,"%.2X-",(int)pAdapt->Address[i]);
					strcat(def2,def);
				}
            }

            sprintf(def,"%s", pAdapt->Description);
            strcat(def2,def);
            pAddrStr = &(pAdapt->IpAddressList);

            while(pAddrStr)
            {
				sprintf(def,"\n%-10.d%-10.d%-20.20s%s\n",pAdapt->Index,pAddrStr->Context,pAddrStr->IpAddress.String,pAddrStr->IpMask.String);//
				strcat(def2,def);                
                pAddrStr = pAddrStr->Next;
            }

            pAdapt = pAdapt->Next;
	}
	AfxMessageBox(def2);
}

void CDialogDlg::OnSend() //������� ��� �������� ���������
{
	if (!server) 
	{
	 UpdateData(true); m_Mr="Send"; UpdateData(false);
	 if (send(cc, m_Ms, 256, 0)==SOCKET_ERROR) AfxMessageBox("Server not respond.");//�������� ������
	 else recv(cc, Stemp, 256, 0);
    }
	else {m_Ms="Server not send"; UpdateData(false);}
}

void CDialogDlg::OnServer() //������� ��� ������������� � ������ �������
{
    if (cc) closesocket(cc);
	server=TRUE;

	//�������� ���������� ��� ����� ������
	ss=socket(PF_INET, SOCK_STREAM, IPPROTO_TCP); 
    	  
	//������������ ���������� ���������� � ����� � � IP ������
   if (bind(ss, (sockaddr*)&Addr, sizeof(Addr))==SOCKET_ERROR)
   {
      closesocket(ss);
	  ss=0;
      AfxMessageBox("Cannot bind socket");
   }  
	
	//������������� ��� ����� ������  
   if (listen(ss, SOMAXCONN)==SOCKET_ERROR) 
   {
     closesocket(ss);
	 ss=0;
     AfxMessageBox("Cannot listen socket");
   }

   //�������� ������ ��� �������� ���������� �������
   if (ss) hThread=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)ThreadFunc,&dwCount,0,&dwThreadId);
 
}

void CDialogDlg::OnClient() //������� ��� ������������� � ������ �������
{
	if (hThread) TerminateThread(hThread,0);
	if (ss) closesocket(ss);
	if (r) closesocket(r);
	if (cc) closesocket(cc);

	//�������� ���������� ��� �������� ������
    cc=socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    
    if (cc==SOCKET_ERROR) 
    {
     closesocket(cc);
	 cc=0;
     AfxMessageBox("Cannot create socket");
    }

	//���������� � ������ �������
	SOCKADDR_IN servsin = {AF_INET};
	servsin.sin_port = htons(u_short(PORT));
	servsin.sin_addr.S_un.S_addr = inet_addr(m_Address);
	if (connect(cc, (LPSOCKADDR)&servsin, sizeof(servsin))==SOCKET_ERROR) 
    {
     closesocket(cc);
	 cc=0;
     AfxMessageBox("Cannot connect socket");
    }
   
	server=FALSE;
}

////////////////////////////////////////
//������ ��� ���������� �������� ������ �� �������
void CDialogDlg::OnTimer(UINT nIDEvent) 
{
	UpdateData(true);
	if (server) m_Mr=S;
	else m_Mr=Stemp;
	UpdateData(false);
}

///////////////////////////////////////////////
//����� ��� �������� ���������� � ��������
DWORD ThreadFunc(LPVOID lParam) 
{
   LPDWORD lpdwCount=(LPDWORD)lParam;
   *lpdwCount=0;

   //������� ������� ���������� �������, ������������ ��� �������
   if(!r) r=accept(ss,(sockaddr*)&Addr, NULL);
   
   if (r==INVALID_SOCKET) AfxMessageBox("Cannot accept socket");
   
   if ((r!=0)&&server)
   {
	Stemp[0]='\0';
	if (recv(r, Stemp, 256, 0)==SOCKET_ERROR) //������� ����� ���������
    {
     closesocket(r); //��� ������������ ������� � ��������, ������ ������ ������������������ ������� ����������, ��� �������� ���������� �������
     r=0;
    }    
    else {
		  if (Stemp[0]=='\0') {
			                   closesocket(r); //��� ������������ ������� � ��������, ������ ������ ������������������ ������� ����������, ��� �������� ���������� �������
                               r=0;
							  }
	      strcpy(S,Stemp); 
		  send(r, "Server recieved", 256, 0);//������� ������������� �����   
		  }
   }

   //�������� ������ ������, ������ �����������
   if (r!=INVALID_SOCKET) hThread=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)ThreadFunc,&dwCount,0,&dwThreadId);
   return *lpdwCount;
}
////////////////////////////////////////////////
//��� ����� � ���������� ���������
void CDialogDlg::OnHelp() 
{    
	 CDialog *about = new CDialog(IDD_HELP);
     about->DoModal();
}
///////////////////////////////////////////////

void CDialogDlg::OnChangeEdit4() //��� ������ ��������� ������ �����
{
    UpdateData(true);
	PORT=m_Port;	
	Addr.sin_port=htons(PORT);
}

void CDialogDlg::OnClose() //�������� �������� ����������
{
	CDialog::OnClose();
	if (ss) closesocket(ss);
	if (cc) closesocket(cc);
	if (r) closesocket(r);
}
