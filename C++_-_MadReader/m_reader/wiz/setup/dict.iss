; -- Sample1.iss --
; Demonstrates copying 3 files, creating an icon, and some registry entries.

; SEE THE DOCUMENTATION FOR DETAILS ON CREATING SETUP SCRIPTS!

[Setup]
Bits=32
AppName=MadReader v2.1(ru)
AppVerName=MadReader version 2.1
AppCopyright=Copyright © forever, Shilonosov Alex.
DefaultDirName={pf}\madreader
DefaultGroupName=MadReader
MinVersion=4,4.0
WizardImageFile=books.bmp 
WizardImageBackColor  = clSilver
LicenseFile=license.txt 

[Messages]
WelcomeLabel=Welcome to the MadReader setup program. This will install MadReader v2.1 on your computer.%n%n%nMadReader ver. 2.1. Released on 1.09.2000%nVery powerfull TXT reader Utility%n%nAuthor: Alex Shilonosov.
FinishedLabel=Setup has finished installing MadReader on your computer. The application may be launched by selecting the installed icons%n%nUse "Send To" from explorer for opening files .


[Files]
Source: "MReader.EXE"; DestDir: "{app}"
Source: "MReader.HLP"; DestDir: "{app}"

[Icons]
Name: "{group}\MadReader"; Filename: "{app}\MReader.EXE"
Name: "{sendto}\MadReader"; Filename: "{app}\MReader.EXE"
Name: "{group}\MadReader Help"; Filename: "{app}\MReader.HLP"

[Registry] 
Root: HKCU; Subkey: "Software\shilonosov\madreader"; Flags: uninsdeletekey

[UninstallDelete]
Type: files; Name: "{app}\Reader.dat"
Type: dirifempty;  Name: "{app}"