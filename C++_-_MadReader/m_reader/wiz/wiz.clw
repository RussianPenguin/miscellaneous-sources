; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CWizDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "wiz.h"

ClassCount=14
Class1=CWizApp
Class2=CWizDlg

ResourceCount=18
Resource2=IDD_WIZ_DIALOG
Resource1=IDR_MAINFRAME (English (U.S.))
Class3=CReadWnd
Resource3=IDR_TEMPL
Resource4=IDR_ABOUT
Resource5=IDR_MENU3
Class4=CBookmText
Resource6=IDR_MENU1
Class5=CPropDlg
Resource7=IDD_DIALOGBAR (English (U.S.))
Class6=CFace
Resource8=IDD_DIALOGBAR5 (English (U.S.))
Class7=CPrint
Class8=CEdit2
Resource9=IDD_DIALOGBAR6 (English (U.S.))
Resource10=IDD_DIALOGBAR2 (English (U.S.))
Class9=CFind
Resource11=IDR_MENU2
Resource12=IDD_DIALOGBAR4 (English (U.S.))
Resource13=IDD_WIZ_DIALOG (English (U.S.))
Class10=CAbout
Class11=CGoto
Resource14=IDD_DIALOGBAR1 (English (U.S.))
Class12=CMySheet
Class13=CAdvProp
Resource15=IDD_DIALOG1
Resource16=IDD_DIALOGBAR3 (English (U.S.))
Resource17=IDD_GOTO (English (U.S.))
Class14=CEvalDlg
Resource18=IDD_REG (English (U.S.))

[CLS:CWizApp]
Type=0
HeaderFile=wiz.h
ImplementationFile=wiz.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC
LastObject=CWizApp

[CLS:CWizDlg]
Type=0
HeaderFile=wizDlg.h
ImplementationFile=wizDlg.cpp
Filter=W
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CWizDlg



[DLG:IDD_WIZ_DIALOG]
Type=1
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Class=CWizDlg

[DLG:IDD_WIZ_DIALOG (English (U.S.))]
Type=1
Class=CWizDlg
ControlCount=10
Control1=ID_COLOR,button,1342242944
Control2=IDC_BUTTON1,button,1342177536
Control3=IDC_hist2,button,1342177408
Control4=IDC_OPEN,button,1342242944
Control5=IDC_hist,button,1342177408
Control6=IDC_code,button,1342243072
Control7=IDC_EDIT1,edit,1342247040
Control8=ID_hide,button,1342177408
Control9=ID_close,button,1342177408
Control10=IDC_STATIC3,static,1342308352

[DLG:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
ControlCount=3
Control1=IDC_STATIC,static,1342308352
Control2=IDC_BUTTON1,button,1342242816
Control3=IDC_STATIC,button,1342177287

[MNU:IDR_MENU2]
Type=1
Class=?
Command1=ID_1_DOS
Command2=ID_1_WIN1251
Command3=ID_1_ISO
CommandCount=3

[MNU:IDR_MENU1]
Type=1
Class=?
CommandCount=0

[DLG:IDD_DIALOGBAR (English (U.S.))]
Type=1
Class=CPropDlg
ControlCount=35
Control1=IDC_CHECK1,button,1342242819
Control2=IDC_CHECK2,button,1342242819
Control3=IDC_CHECK3,button,1342242819
Control4=IDC_CHECK7,button,1342242819
Control5=IDC_CHECK5,button,1342242819
Control6=IDC_CHECK9,button,1342242819
Control7=IDC_CHECK10,button,1342242819
Control8=IDC_CHECK11,button,1342242819
Control9=IDC_EDIT1,edit,1082208384
Control10=IDC_SPIN2,msctls_updown32,1073742134
Control11=IDC_EDIT3,edit,1350643840
Control12=IDC_SPIN3,msctls_updown32,1342177590
Control13=IDC_STATIC0,static,1073872896
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,button,1342177287
Control16=IDC_STATICH,static,1073872896
Control17=IDC_STATIC,button,1342177287
Control18=IDC_CHECK15,button,1073807363
Control19=IDC_CHECK16,button,1342242819
Control20=IDC_COMBO5,combobox,1344339971
Control21=IDC_STATIC5,static,1342308352
Control22=IDC_RADIO4,button,1342177289
Control23=IDC_RADIO5,button,1073741833
Control24=IDC_RADIO6,button,1342177289
Control25=IDC_CHECK4,button,1342242819
Control26=IDC_EDIT23,edit,1082208384
Control27=IDC_SPIN11,msctls_updown32,1073742134
Control28=IDC_EDIT24,edit,1350643840
Control29=IDC_SPIN12,msctls_updown32,1342177590
Control30=IDC_STATIC,static,1073872896
Control31=IDC_STATIC,static,1342308352
Control32=IDC_COMBO6,combobox,1344339971
Control33=IDC_STATIC6,static,1342308352
Control34=IDC_STATIC7,static,1342308352
Control35=IDC_CHECK18,button,1073807363

[DLG:IDD_DIALOGBAR1 (English (U.S.))]
Type=1
Class=CBookmText
ControlCount=2
Control1=IDC_EDIT2,edit,1342247040
Control2=IDOK,button,1342242816

[CLS:CBookmText]
Type=0
HeaderFile=BookmText.h
ImplementationFile=BookmText.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC

[CLS:CReadWnd]
Type=0
HeaderFile=mywnd.h
ImplementationFile=mywnd.cpp
BaseClass=CWnd
LastObject=CReadWnd
Filter=W
VirtualFilter=WC

[CLS:CPropDlg]
Type=0
HeaderFile=PropDlg.h
ImplementationFile=PropDlg.cpp
BaseClass=CPropertyPage
Filter=W
LastObject=CPropDlg
VirtualFilter=idWC

[DLG:IDD_DIALOG1]
Type=1
Class=CFace
ControlCount=6
Control1=IDC_BUTTON21,button,1342242816
Control2=IDC_EDIT8,edit,1345392836
Control3=IDC_BUTTON22,button,1342242816
Control4=IDC_BUTTON23,button,1208025088
Control5=IDC_STATIC1,static,1342308354
Control6=IDC_STATIC,static,1342308352

[CLS:CFace]
Type=0
HeaderFile=Face.h
ImplementationFile=Face.cpp
BaseClass=CPropertyPage
Filter=D
LastObject=IDC_EDIT8
VirtualFilter=idWC

[DLG:IDD_DIALOGBAR2 (English (U.S.))]
Type=1
Class=CPrint
ControlCount=18
Control1=IDC_COMBO3,combobox,1344339971
Control2=IDC_BUTTON2,button,1342242816
Control3=IDC_EDIT7,edit,1342242944
Control4=IDC_BUTTON1,button,1342242816
Control5=IDC_STATIC,button,1207959559
Control6=IDC_STATIC,static,1208090624
Control7=IDC_EDIT2,edit,1208033408
Control8=IDC_STATIC,static,1208090624
Control9=IDC_EDIT6,edit,1208033408
Control10=IDC_STATIC,static,1208090624
Control11=IDC_EDIT9,edit,1208033408
Control12=IDC_STATIC,static,1208090624
Control13=IDC_EDIT8,edit,1208033408
Control14=IDC_STATIC,button,1342177287
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC1,static,1342308864
Control17=IDC_STATIC2,static,1342308352
Control18=IDC_STATICH,static,1073872896

[CLS:CPrint]
Type=0
HeaderFile=Print.h
ImplementationFile=Print.cpp
BaseClass=CPropertyPage
Filter=W
LastObject=CPrint
VirtualFilter=idWC

[CLS:CEdit2]
Type=0
HeaderFile=Edit2.h
ImplementationFile=Edit2.cpp
BaseClass=CEdit
Filter=W
VirtualFilter=WC

[MNU:IDR_TEMPL]
Type=1
Class=?
Command1=ID_1_PAGE
Command2=ID_1_PERS
Command3=ID_1_DATEMMDD
Command4=ID_1_TIME
Command5=ID_1_DAYOFWEEK
Command6=ID_1_PATH
Command7=ID_1_FILENAME
Command8=ID_1_KB
Command9=ID_1
Command10=ID_1_TEXT
Command11=ID_1_USER
Command12=ID_1_BOOKMARKTEXT
Command13=ID_1_SPEED
Command14=ID_1_AVERAGESPEED
Command15=ID_1_AVERAGESPEED2
Command16=ID_1_AVERAGESPEED3
Command17=ID_1_WORDSINPAGE
Command18=ID_1_READPAGES
CommandCount=18

[DLG:IDD_DIALOGBAR3 (English (U.S.))]
Type=1
Class=CFind
ControlCount=16
Control1=IDC_EDIT20,edit,1342242944
Control2=IDC_BUTTON9,button,1476460544
Control3=IDC_BUTTON4,button,1476460544
Control4=IDC_RADIO1,button,1342177289
Control5=IDC_RADIO2,button,1342177289
Control6=IDC_LIST2,SysListView32,1073940489
Control7=IDC_BUTTON8,button,1476460544
Control8=IDC_BUTTON1,button,1208025088
Control9=IDC_STATIC,button,1342177287
Control10=IDC_STATIC,static,1342308352
Control11=IDC_BUTTON6,button,1208025088
Control12=IDC_EDIT2,edit,1342244992
Control13=IDC_STATIC,static,1342177296
Control14=IDC_PROGRESS1,msctls_progress32,1073741824
Control15=IDC_STATICH,static,1073872896
Control16=IDC_CHECK17,button,1342242819

[CLS:CFind]
Type=0
HeaderFile=Find.h
ImplementationFile=Find.cpp
BaseClass=CPropertyPage
Filter=D
LastObject=IDC_RADIO4
VirtualFilter=idWC

[MNU:IDR_MENU3]
Type=1
Class=?
Command1=ID_1_COPY
Command2=ID_1_BOOKMARK
Command3=ID_1_SAVETEXT
Command4=ID_1_MEMO
Command5=ID_1_JUMP
Command6=ID_1_SELECTALL
Command7=ID_1_DELETE
CommandCount=7

[DLG:IDD_DIALOGBAR4 (English (U.S.))]
Type=1
Class=?
ControlCount=9
Control1=IDC_CHECK1,button,1342242819
Control2=IDC_CHECK2,button,1342242819
Control3=IDC_STATIC,static,1342177296
Control4=IDC_STATIC,static,1342177297
Control5=IDC_STATIC,static,1342308354
Control6=IDC_STATIC,static,1342308354
Control7=IDC_STATIC,static,1342308354
Control8=IDC_STATIC,static,1342308354
Control9=IDC_STATICH,static,1342308352

[DLG:IDD_DIALOGBAR5 (English (U.S.))]
Type=1
Class=CAbout
ControlCount=13
Control1=IDC_BUTTON25,button,1342251008
Control2=IDC_EDIT1,edit,1342244998
Control3=IDC_EDIT21,edit,1344342212
Control4=IDC_STATIC,static,1342177296
Control5=IDC_STATIC,static,1342177296
Control6=IDC_STATIC1,static,1342308354
Control7=IDC_STATIC,static,1342308354
Control8=IDC_STATIC5,static,1342177294
Control9=IDC_EDIT4,edit,1082196096
Control10=IDC_EDIT5,edit,1082196096
Control11=IDC_STATIC2,static,1073872896
Control12=IDC_STATIC3,static,1073872896
Control13=IDC_BUTTON1,button,1073807360

[CLS:CAbout]
Type=0
HeaderFile=About.h
ImplementationFile=About.cpp
BaseClass=CPropertyPage
Filter=D
LastObject=IDC_EDIT4
VirtualFilter=idWC

[DLG:IDD_DIALOGBAR6 (English (U.S.))]
Type=1
Class=CAdvProp
ControlCount=13
Control1=IDC_COMBO4,combobox,1344339971
Control2=IDC_BUTTON2,button,1342242816
Control3=IDC_BUTTON14,button,1342242827
Control4=IDC_BUTTON13,button,1342242827
Control5=IDC_COMBO3,combobox,1344339971
Control6=IDC_EDIT7,edit,1344344260
Control7=IDC_BUTTON1,button,1342242816
Control8=IDC_STATIC1,static,1342308864
Control9=IDC_STATIC,button,1342177287
Control10=IDC_STATIC,button,1342177287
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATICH,static,1073872896

[CLS:CMySheet]
Type=0
HeaderFile=MySheet.h
ImplementationFile=MySheet.cpp
BaseClass=CPropertySheet
Filter=W
VirtualFilter=hWC
LastObject=CMySheet

[CLS:CAdvProp]
Type=0
HeaderFile=AdvProp.h
ImplementationFile=AdvProp.cpp
BaseClass=CPropertyPage
Filter=W
LastObject=IDC_BUTTON13
VirtualFilter=idWC

[DLG:IDD_GOTO (English (U.S.))]
Type=1
Class=CGoto
ControlCount=10
Control1=IDC_EDIT2,edit,1342255232
Control2=IDC_SPIN1,msctls_updown32,1342177590
Control3=IDOK,button,1342242816
Control4=IDC_BUTTON23,button,1342242816
Control5=IDC_RADIO1,button,1342177289
Control6=IDC_RADIO2,button,1342177289
Control7=IDC_RADIO3,button,1342177289
Control8=IDC_BUTTON21,button,1342242817
Control9=IDC_STATIC,button,1342177287
Control10=IDC_STATIC20,static,1342308352

[CLS:CGoto]
Type=0
HeaderFile=Goto.h
ImplementationFile=Goto.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_SPIN1

[MNU:IDR_ABOUT]
Type=1
Class=?
Command1=ID_1_HOWTOREGISTER
Command2=ID_1_PRICES
Command3=ID_1_ENTERREGISTRATIONCODE
Command4=ID_1_WEBBOOKSSTORAGE_WWWMOSHKOV
Command5=ID_1_WEBBOOKSSTORAGE_WWWINKWEELRU
Command6=ID_1_WEBBOOKSSTORAGES_SYMPAD
Command7=ID_1_WWW
Command8=ID_1_FEEDBAK_BAGREPORT
CommandCount=8

[DLG:IDD_REG (English (U.S.))]
Type=1
Class=CEvalDlg
ControlCount=5
Control1=IDOK,button,1342242816
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC1,static,1342308353
Control4=IDC_STATIC,static,1342177283
Control5=IDC_STATIC2,static,1342308352

[CLS:CEvalDlg]
Type=0
HeaderFile=EvalDlg.h
ImplementationFile=EvalDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC

