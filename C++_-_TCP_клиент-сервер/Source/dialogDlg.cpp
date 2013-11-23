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

//////////////переменные для потока///////////////////////////////////
//поток нам нужен для организации прослушивания сети для приёма сообщений
//используется только для сервера,
//если бы мы не использовали поток, мы бы теряли контроль над программой
//так как при активизировании работы сервера при запуске функции access
//сервер будет ожидать соединения, а остальные функции будут недоступны, например
//без потока мы бы не смогли выйти нормально из программы, а так же отменить
//работу функции сервера или переключиться на другие функции 
HANDLE hThread;
DWORD dwCount, dwThreadId;
DWORD ThreadFunc(LPVOID lParam);
//////////////////////Client+Server////////////////////
#define DEF_HOSTADDR "127.0.0.1" //задание LOOPBACK-ого IP адреса, т.е. локального адреса изначально при запуске программы

    int PORT=3182; //порт TCP, служит для организации сети
	char S[256]="\0"; //буфер для хранения в нём отправляемых и получаемых сообщений
	char Stemp[256]="\0";//временный буфер
	SOCKET ss, cc, r; //сокеты для организации сети
	sockaddr_in Addr; ////обьявление структуры адреса и порта для передачи и приёма данных
	WSADATA Wsa; //переменная для инициализации winsock
    bool server; //переменная для определения режима работы программы: сервер или клиент
//////////////////////////////////////////////////////////
//параметры для добавления и удаления интерфейсов для создания новых 
//IP адресов на одной станции, применяется частично на NT4 для 
//создания без перезагрузки програмно IP адреса, предназначалось
//изначально для организации кластера на NT4. Windows2000 поддерживает
//эти функции полностью.
//Изначальные исходники этих функций вы можете посмотреть в PDK от Microsoft

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

    if(WSAStartup(0x0101,&Wsa)) AfxMessageBox("Cannot init WinSock"); //Инициализация Winsock. Без этой функции сеть работать не будет. Ошибка возможна из-за неправильной настройки сети или случайного удаления файла winsock.dll

    SetTimer(1,1000,NULL); //задание величины таймера, через это время программа будет проверять приход сообщений, время равно 1 секунде

	//инициализация структуры типа сообщений, адреса и порта для передачи и приёма данных
	Addr.sin_family=AF_INET;
	Addr.sin_addr.s_addr=INADDR_ANY;
	Addr.sin_port=htons(PORT);

	m_Port=PORT;
    m_Address=DEF_HOSTADDR; //в графе IP ADRESS прописывается адрес LOOPBACK по умолчанию 127.0.0.1, т.е.локальный адрес
    m_Mask="255.255.255.0"; //в графе MASK задаётся маска сети
	m_Interface="2"; //в графе № Interface задаётся интерфейс, изначально 2, применяется для создания дополнительного нового IP адреса интерфейс вы можете посмотреть, нажав клавишу INFO
	UpdateData(false); 

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDialogDlg::OnNew() //создание нового интерфейса с новым IP адресом
{
	UpdateData(true);
	NewIP = inet_addr(m_Address);//задание нового дополнительного IP адреса, адрес берётся из поля IP ADRESS
    NewMask = inet_addr(m_Mask);//задание маски сети
	Index=atoi(m_Interface);//задание интерфейса
    if (AddIPAddress(NewIP, NewMask, Index, &NTEContext, &NTEInstance)) AfxMessageBox("Error add interface\nNot corect number interface or You use Windows 9X.\nThis function don't work in Windows 9X.");
    else {
		  sprintf(def,"Добавлен адрес %s",m_Address);
	      AfxMessageBox(def);
		 }  	
}

void CDialogDlg::OnDelete() //удаление созданного интерфейса
{
	UpdateData(true);	
	Index=atoi(m_Interface);//для удаления уже созданного интерфейса нужна переменная в поле № Interface, если вы создавали 1-ый интерфейс, то чтобы его удалить в стандартной ситуации надо задать 3
    if (DeleteIPAddress(Index)) AfxMessageBox("Error delete interface\nNot corect number context or You use Windows 9X.\nThis function don't work in Windows 9X.");
    else {
		  sprintf(def,"Удалён интерфейс №%d",Index);
		  AfxMessageBox(def);
		 }
}

void CDialogDlg::OnPing() //запуск утилиты PING для проверки активности адреса
{
    UpdateData(true);
	NewIP = inet_addr(m_Address);
	sprintf(def,"ping %s -t",m_Address);
    WinExec(def,SW_NORMAL);	//запуск стандартной утилиты ping от Microsoft
}

void CDialogDlg::OnInfo() //информация об интерфейсах на данном компьютере, работает в ОС Win9X и Nt5.0, для Nt4.0 запускается стандартная утила route
{
    AdapterInfoSize = 0;
    if ((Err = GetAdaptersInfo(NULL, &AdapterInfoSize)) != 0)
    {
        if (Err != ERROR_BUFFER_OVERFLOW)
        {
            AfxMessageBox("Work's in Windows 2000 & Windows 9X");
			WinExec("cmd /k route print",SW_NORMAL);	//запуск стандартной утилиты route от Microsoft, которая выводит инфу об сетевых адаптерах, а для нас об интерфейсах
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

void CDialogDlg::OnSend() //функция для отправки сообщений
{
	if (!server) 
	{
	 UpdateData(true); m_Mr="Send"; UpdateData(false);
	 if (send(cc, m_Ms, 256, 0)==SOCKET_ERROR) AfxMessageBox("Server not respond.");//передача данных
	 else recv(cc, Stemp, 256, 0);
    }
	else {m_Ms="Server not send"; UpdateData(false);}
}

void CDialogDlg::OnServer() //функция для инициализации и работы сервера
{
    if (cc) closesocket(cc);
	server=TRUE;

	//создание соединения для приёма данных
	ss=socket(PF_INET, SOCK_STREAM, IPPROTO_TCP); 
    	  
	//привязывание созданного соединения к порту и к IP адресу
   if (bind(ss, (sockaddr*)&Addr, sizeof(Addr))==SOCKET_ERROR)
   {
      closesocket(ss);
	  ss=0;
      AfxMessageBox("Cannot bind socket");
   }  
	
	//инициализация для приёма данных  
   if (listen(ss, SOMAXCONN)==SOCKET_ERROR) 
   {
     closesocket(ss);
	 ss=0;
     AfxMessageBox("Cannot listen socket");
   }

   //открытие потока для ожидания соединения клиента
   if (ss) hThread=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)ThreadFunc,&dwCount,0,&dwThreadId);
 
}

void CDialogDlg::OnClient() //функция для инициализации и работы клиента
{
	if (hThread) TerminateThread(hThread,0);
	if (ss) closesocket(ss);
	if (r) closesocket(r);
	if (cc) closesocket(cc);

	//создание соединения для передачи данных
    cc=socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    
    if (cc==SOCKET_ERROR) 
    {
     closesocket(cc);
	 cc=0;
     AfxMessageBox("Cannot create socket");
    }

	//соединение с портом сервера
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
//таймер для обновления принятых данных от клиента
void CDialogDlg::OnTimer(UINT nIDEvent) 
{
	UpdateData(true);
	if (server) m_Mr=S;
	else m_Mr=Stemp;
	UpdateData(false);
}

///////////////////////////////////////////////
//поток для открытия соединения с клиентом
DWORD ThreadFunc(LPVOID lParam) 
{
   LPDWORD lpdwCount=(LPDWORD)lParam;
   *lpdwCount=0;

   //функция ожидает соединение клиента, используется для сервера
   if(!r) r=accept(ss,(sockaddr*)&Addr, NULL);
   
   if (r==INVALID_SOCKET) AfxMessageBox("Cannot accept socket");
   
   if ((r!=0)&&server)
   {
	Stemp[0]='\0';
	if (recv(r, Stemp, 256, 0)==SOCKET_ERROR) //функция приёма сообщений
    {
     closesocket(r); //при разъединении клиента с сервером, сервер заново переинициализирует функцию соединения, для ожидания следующего конекта
     r=0;
    }    
    else {
		  if (Stemp[0]=='\0') {
			                   closesocket(r); //при разъединении клиента с сервером, сервер заново переинициализирует функцию соединения, для ожидания следующего конекта
                               r=0;
							  }
	      strcpy(S,Stemp); 
		  send(r, "Server recieved", 256, 0);//посылка подтверждения приёма   
		  }
   }

   //создание нового потока, старый закрывается
   if (r!=INVALID_SOCKET) hThread=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)ThreadFunc,&dwCount,0,&dwThreadId);
   return *lpdwCount;
}
////////////////////////////////////////////////
//для связи с создателем программы
void CDialogDlg::OnHelp() 
{    
	 CDialog *about = new CDialog(IDD_HELP);
     about->DoModal();
}
///////////////////////////////////////////////

void CDialogDlg::OnChangeEdit4() //для опроса изменений номера порта
{
    UpdateData(true);
	PORT=m_Port;	
	Addr.sin_port=htons(PORT);
}

void CDialogDlg::OnClose() //закрытие активных соединений
{
	CDialog::OnClose();
	if (ss) closesocket(ss);
	if (cc) closesocket(cc);
	if (r) closesocket(r);
}
