unit crtsock;

{
  CrtSocket for Delphi 32
  Copyright (C) 1999  Paul Toth <tothpaul@free.fr>
  http://tothpaul.free.fr

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

}

interface

uses windows,sysutils;

// Server side :
//  - start a server
//  - wait for a client
function StartServer(Port:word):integer;
function WaitClient(Server:integer):integer;
function WaitClientEx(Server:integer; var ip:string):integer;

// Client side :
//  - call a server
function CallServer(Server:string;Port:word):integer;

// Both side :
//  - Assign CRT Sockets
//  - Disconnect server
procedure AssignCrtSock(Socket:integer; Var Input,Output:TextFile);
procedure Disconnect(Socket:integer);

// BlockRead
Function BlockReadsock(Var F:TextFile; var s:string):boolean;

Function send(socket:integer; data:pointer; datalen,flags:integer):integer; stdcall; far;
Function recv(socket:integer; data:pchar; datalen,flags:integer):integer; stdcall; far; 

// some usefull SOCKET apis
type
  PHost = ^THost;
  THost = packed record
    name     : PChar;
    aliases  : ^PChar;
    addrtype : Smallint;
    length   : Smallint;
    addr     : ^pointer;
  end;

  TSockAddr=packed record
   Family:word;
   Port:word;
   Addr:LongInt;
   Zeros:array[0..7] of byte;
  end;

Const
 fIoNbRead = $4004667F;

Function socket(Family,Kind,Protocol:integer):integer; stdcall;
Function gethostbyname(HostName:PChar):PHost; stdcall;
Function gethostname(name:pchar; size:integer):integer; stdcall;
Function bind(Socket:Integer; Var SockAddr:TSockAddr; AddrLen:integer):integer; stdcall;
Function WSAGetLastError:integer; stdcall;
Function ioctlsocket(socket:integer; cmd: Longint; var arg: longint): Integer; stdcall;

// Convert an IP Value to xxx.xxx.xxx.xxx string
Function LongToIp(Long:LongInt):string;
Function HostToLong(AHost:string):LongInt;

Var
 EofSock:boolean;

implementation

//------ winsock -------------------------------------------------------
Const
 WinSock='wsock32.dll'; { 32bits socket DLL }
 Internet=2; { Internat familly }
 Stream=1;   { Streamed socket }
// fIoNbRead = $4004667F;

Type
  TWSAData = packed record
    wVersion: Word;
    wHighVersion: Word;
    szDescription: array[0..256] of Char;
    szSystemStatus: array[0..128] of Char;
    iMaxSockets: Word;
    iMaxUdpDg: Word;
    lpVendorInfo: PChar;
  end;

{ Winsock }
Function WSAStartup(Version:word; Var Data:TwsaData):integer; stdcall; far; external winsock;
Function socket(Family,Kind,Protocol:integer):integer; stdcall; far; external winsock;
Function shutdown(Socket,How:Integer):integer; stdcall; far; external winsock;
Function closesocket(socket:Integer):integer; stdcall; far; external winsock;
Function WSACleanup:integer; stdcall; far; external winsock;
//Function WSAAsyncSelect(Socket:Integer; Handle:Hwnd; Msg:word; Level:Longint):longint; stdcall; far; external winsock;
Function bind(Socket:Integer; Var SockAddr:TSockAddr; AddrLen:integer):integer; stdcall; far; external winsock;
Function listen(socket,flags:Integer):integer; stdcall; far; external winsock;
Function connect(socket:Integer; Var SockAddr:TSockAddr; AddrLen:integer):integer; stdcall; far; external winsock;
Function accept(socket:Integer; Var SockAddr:TSockAddr; Var AddrLen:Integer):integer; stdcall; far; external winsock;
Function WSAGetLastError:integer; stdcall; far; external winsock;
Function recv(socket:integer; data:pchar; datalen,flags:integer):integer; stdcall; far; external winsock;
Function send(socket:integer; data:pointer; datalen,flags:integer):integer; stdcall; far; external winsock;
//Function getpeername(socket:integer; var SockAddr:TSockAddr; Var AddrLen:Integer):Integer; stdcall; far; external winsock;
Function gethostbyname(HostName:PChar):PHost; stdcall; far; external winsock;
//Function getsockname(socket:integer; var SockAddr:TSockAddr; Var AddrLen:Integer):integer; stdcall; far; external winsock;
//Function inet_ntoa(addr:longint):PChar; stdcall; far; external winsock;
Function WSAIsBlocking:boolean; stdcall; far; external winsock;
Function WSACancelBlockingCall:integer; stdcall; far; external winsock;
Function ioctlsocket(socket:integer; cmd: Longint; var arg: longint): Integer; stdcall; far; external winsock;
//Function gethostbyaddr(var addr:longint; size,atype:integer):PHost; stdcall; far; external winsock;
Function gethostname(name:pchar; size:integer):integer; stdcall; far; external winsock;

Function IpToLong(ip:string):LongInt;
 var
  x,i:byte;
  ipx:array[0..3] of byte;
  v:integer;
 begin
  Result:=0;
  longint(ipx):=0; i:=0;
  for x:=1 to length(ip) do
   if ip[x]='.' then begin
    inc(i);
    if i=4 then exit;
   end else begin
    if not (ip[x] in ['0'..'9']) then exit;
    v:=ipx[i]*10+ord(ip[x])-ord('0');
    if v>255 then exit;
    ipx[i]:=v;
   end;
  result:=longint(ipx);
 end;

Function HostToLong(AHost:string):LongInt;
 Var
  Host:PHost;
 begin
  Result:=IpToLong(AHost);
  if Result=0 then begin
   Host:=GetHostByName(PChar(AHost));
   if Host<>nil then Result:=longint(Host^.Addr^^);
  end; 
 end;

Function LongToIp(Long:LongInt):string;
 var
  ipx:array[0..3] of byte;
  i:byte;
 begin
  longint(ipx):=long;
  Result:='';
  for i:=0 to 3 do result:=result+IntToStr(ipx[i])+'.';
  SetLength(Result,Length(Result)-1);
 end;

//--- Server Side ------------------------------------------------------------------------
function StartServer(Port:word):integer;
 Var
  SockAddr:TSockAddr;
 begin
  Result:=socket(Internet,Stream,0);
  if Result=-1 then exit;
  FillChar(SockAddr,SizeOf(SockAddr),0);
  SockAddr.Family:=Internet;
  SockAddr.Port:=swap(Port);
  if (Bind(Result,SockAddr,SizeOf(SockAddr))<>0)
  or (Listen(Result,0)<>0) then begin
   CloseSocket(Result);
   Result:=-1;
  end;
 end;

function WaitClient(Server:integer):integer;
 var
  Client:TSockAddr;
  Size:integer;
 begin
  Size:=SizeOf(Client);
  Result:=Accept(Server,Client,Size);
 end;

function WaitClientEx(Server:integer; var ip:string):integer;
 var
  Client:TSockAddr;
  Size:integer;
 begin
  Size:=SizeOf(Client);
  Result:=Accept(Server,Client,Size);
  ip:=LongToIp(Client.Addr);
 end;

Function BlockReadSock(Var F:TextFile; var s:string):boolean;
 Var
  Handle:THandle;
  Size:longint;
 begin
  Result:=False;
  Handle:=TTextRec(F).Handle;
  Repeat
   if (IoctlSocket(Handle, fIoNbRead, Size)<0) then exit;
   if Size=0 then exit
  until (Size>0);
  SetLength(s,Size);
  Recv(Handle,pchar(s),Size,0);
  Result:=True;
 end;

// Client Side--------------------------------------------------------------------------
function CallServer(Server:string; Port:word):integer;
 var
  SockAddr:TSockAddr;
 begin
  Result:=socket(Internet,Stream,0);
  if Result=-1 then exit;
  FillChar(SockAddr,SizeOf(SockAddr),0);
  SockAddr.Family:=Internet;
  SockAddr.Port:=swap(Port);
  SockAddr.Addr:=HostToLong(Server);
  if Connect(Result,SockAddr,SizeOf(SockAddr))<>0 then begin
   Disconnect(Result);
   Result:=-1;
  end;
 end;

//------------ CrtSock -----------------
Var
 InitOk:boolean;

function OutputSock(Var F:TTextRec):integer; far;
 begin
  if F.BufPos<>0 then begin
   Send(F.Handle,F.BufPtr,F.BufPos,0);
   F.BufPos:=0;
  end;
  Result:=0;
 end;

function InputSock(var F: TTextRec): Integer; far;
 Var
  Size:longint;
 begin
  F.BufEnd:=0;
  F.BufPos:=0;
  Result:=0;
  Repeat
   if (IoctlSocket(F.Handle, fIoNbRead, Size)<0) then begin
    EofSock:=True;
    exit;
   end;
  until (Size>=0);
  //if Size>0 then
  F.BufEnd:=Recv(F.Handle,F.BufPtr,F.BufSize,0);
  EofSock:=(F.BufEnd=0);
 end;

procedure Disconnect(Socket:integer);
 begin
  ShutDown(Socket,1); //2);
  CloseSocket(Socket);
 end;

function CloseSock(var F:TTextRec):integer; far;
 begin
  Disconnect(F.Handle);
  F.Handle:=-1;
  Result:=0;
 end;

function OpenSock(var F: TTextRec): Integer; far;
begin
  if F.Mode = fmInput then begin // ReadLn
    EofSock:=False;
    F.BufPos:=0;
    F.BufEnd:=0;
    F.InOutFunc := @InputSock;
    F.FlushFunc := nil;
  end else begin                 // WriteLn
    F.Mode := fmOutput;
    F.InOutFunc := @OutputSock;
    F.FlushFunc := @OutputSock;
  end;
  F.CloseFunc := @CloseSock;
  Result:=0;
end;

Procedure AssignCrtSock(Socket:integer; Var Input,Output:TextFile);
 begin
  with TTextRec(Input) do begin
    Handle := Socket;
    Mode := fmClosed;
    BufSize := SizeOf(Buffer);
    BufPtr := @Buffer;
    OpenFunc := @OpenSock;
  end;
  with TTextRec(Output) do begin
    Handle := Socket;
    Mode := fmClosed;
    BufSize := SizeOf(Buffer);
    BufPtr := @Buffer;
    OpenFunc := @OpenSock;
  end;
  Reset(Input);
  Rewrite(Output);
 end;

//----- Initialization/Finalization--------------------------------------------------

Procedure InitCrtSock;
 var
  wsaData:TWSAData;
 begin
  InitOk:=wsaStartup($101,wsaData)=0;
 end;

Procedure DoneCrtSock;
 begin
  if not InitOk then exit;
  if wsaIsBlocking then wsaCancelBlockingCall;
  wsaCleanup;
 end;

Initialization InitCrtSock;

Finalization DoneCrtSock;

end.
