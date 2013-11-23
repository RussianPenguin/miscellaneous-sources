; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMainFrame
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "demouidevstudio.h"
LastPage=0

ClassCount=15
Class1=CChildFrame
Class2=CDemoUIDevStudioApp
Class3=CAboutDlg
Class4=CDemoUIDevStudioDoc
Class5=CDemoUIDevStudioView
Class6=CMainFrame
Class7=COutputBar
Class8=CTabClassDoc
Class9=CTabClassView
Class10=CTabDoc
Class11=CTabFileDoc
Class12=CTabFileView
Class13=CTabResourceDoc
Class14=CTabResourceView
Class15=CTabView

ResourceCount=5
Resource1=IDR_MAINFRAME
Resource2=IDR_TOOLBAR1
Resource3=IDR_BUILDBAR
Resource4=IDD_ABOUTBOX
Resource5=IDR_DEMOUITYPE

[CLS:CChildFrame]
Type=0
BaseClass=CXTMDIChildWnd
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
Filter=M
VirtualFilter=mfWC
LastObject=ID_FIND_IN_FILES

[CLS:CDemoUIDevStudioApp]
Type=0
BaseClass=CWinApp
HeaderFile=DemoUIDevStudio.h
ImplementationFile=DemoUIDevStudio.cpp
LastObject=ID_BUTTON32774
Filter=N
VirtualFilter=AC

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=DemoUIDevStudio.cpp
ImplementationFile=DemoUIDevStudio.cpp
LastObject=IDC_COMBO1

[CLS:CDemoUIDevStudioDoc]
Type=0
BaseClass=CDocument
HeaderFile=DemoUIDevStudioDoc.h
ImplementationFile=DemoUIDevStudioDoc.cpp

[CLS:CDemoUIDevStudioView]
Type=0
BaseClass=CView
HeaderFile=DemoUIDevStudioView.h
ImplementationFile=DemoUIDevStudioView.cpp
Filter=C
VirtualFilter=VWC
LastObject=CDemoUIDevStudioView

[CLS:CMainFrame]
Type=0
BaseClass=CXTMDIFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
VirtualFilter=fWC
LastObject=ID_SEARCH

[CLS:COutputBar]
Type=0
BaseClass=CXTDockWindow
HeaderFile=OutputBar.h
ImplementationFile=OutputBar.cpp

[CLS:CTabClassDoc]
Type=0
BaseClass=CDocument
HeaderFile=TabClassDoc.h
ImplementationFile=TabClassDoc.cpp

[CLS:CTabClassView]
Type=0
BaseClass=CTreeView
HeaderFile=TabClassView.h
ImplementationFile=TabClassView.cpp
LastObject=CTabClassView
Filter=W
VirtualFilter=VWC

[CLS:CTabDoc]
Type=0
BaseClass=CDocument
HeaderFile=TabDoc.h
ImplementationFile=TabDoc.cpp

[CLS:CTabFileDoc]
Type=0
BaseClass=CDocument
HeaderFile=TabFileDoc.h
ImplementationFile=TabFileDoc.cpp

[CLS:CTabFileView]
Type=0
BaseClass=CTreeView
HeaderFile=TabFileView.h
ImplementationFile=TabFileView.cpp
Filter=W
VirtualFilter=VWC
LastObject=CTabFileView

[CLS:CTabResourceDoc]
Type=0
BaseClass=CDocument
HeaderFile=TabResourceDoc.h
ImplementationFile=TabResourceDoc.cpp

[CLS:CTabResourceView]
Type=0
BaseClass=CTreeView
HeaderFile=TabResourceView.h
ImplementationFile=TabResourceView.cpp
Filter=W
VirtualFilter=VWC
LastObject=CTabResourceView

[CLS:CTabView]
Type=0
BaseClass=CTreeView
HeaderFile=TabView.h
ImplementationFile=TabView.cpp
Filter=C
LastObject=CTabView

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=7
Control1=IDC_STATIC,static,1342177283
Control2=IDC_TXT_VERSION,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342177296
Control5=IDC_TXT_URL,static,1342308352
Control6=IDC_TXT_EMAIL,static,1342308352
Control7=IDOK,button,1342373889

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_SAVE_ALL
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_UNDO
Command9=ID_REDO
Command10=ID_WORKSPACE
Command11=ID_OUTPUT
Command12=ID_WINDOW_LIST
Command13=ID_FIND_IN_FILES
Command14=ID_FIND
Command15=ID_SEARCH
Command16=ID_APP_ABOUT
CommandCount=16

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
Command8=ID_APP_ABOUT
Command9=IDC_TIPOFTHEDAY
CommandCount=9

[MNU:IDR_DEMOUITYPE]
Type=1
Class=CDemoUIDevStudioApp
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_PREVIEW
Command8=ID_FILE_PRINT_SETUP
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_EDIT_UNDO
Command12=ID_EDIT_CUT
Command13=ID_EDIT_COPY
Command14=ID_EDIT_PASTE
Command15=ID_VIEW_TOOLBAR
Command16=ID_VIEW_STATUS_BAR
Command17=ID_WINDOW_NEW
Command18=ID_WINDOW_CASCADE
Command19=ID_WINDOW_TILE_HORZ
Command20=ID_WINDOW_ARRANGE
Command21=ID_APP_ABOUT
Command22=IDC_TIPOFTHEDAY
CommandCount=22

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[TB:IDR_TOOLBAR1]
Type=1
Class=CMainFrame
Command1=ID_ACTIVE_PROJECT
Command2=ID_ACTIVE_CONFIG
Command3=ID_COMPILE
Command4=ID_BUILD
Command5=ID_STOP_BUILD
Command6=ID_EXECUTE_PROG
Command7=ID_GO
Command8=ID_INSERT_BREAK
CommandCount=8

[TB:IDR_BUILDBAR]
Type=1
Class=?
Command1=ID_ACTIVE_PROJECT
Command2=ID_ACTIVE_CONFIG
Command3=ID_COMPILE
Command4=ID_BUILD
Command5=ID_STOP_BUILD
Command6=ID_EXECUTE_PROG
Command7=ID_GO
Command8=ID_INSERT_BREAK
CommandCount=8

