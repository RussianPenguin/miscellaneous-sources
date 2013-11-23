; -- Sample1.iss --
; Demonstrates copying 3 files, creating an icon, and some registry entries.

; Inno setup
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING SETUP SCRIPTS!

[Setup]
Bits=32
AppName=Dictionar  v2.1
AppVerName=Dictionar version 2.1
AppCopyright=Copyright © 2000,2001 Shilonosov Alex.
DefaultDirName={pf}\dict
DefaultGroupName=Dictionar
MinVersion=4,3.51

[Messages] 
WelcomeLabel=Welcome to the Dictionar setup program. This will install Dictionar v2.1 on your computer.%n%n%nDictionar ver. 2.1. Released on 03.17.2000%n23000 Romanian words%n25000 Russian words%n7000  English words%n%nAuthor: Alex Shilonosov.%n%n%n


[Files]
Source: "DICT.EXE"; DestDir: "{app}"
Source: "DICT.HLP"; DestDir: "{app}"
Source: "Base.dic"; DestDir: "{app}"
Source: "w-Base.dic"; DestDir: "{app}"

[Icons]
Name: "{group}\Dictionar"; Filename: "{app}\DICT.EXE"
Name: "{group}\Dictionar Help"; Filename: "{app}\DICT.HLP"

[UninstallDelete] 
Type: files; Name: "{app}\dict.opt"
Type: dirifempty;  Name: "{app}"