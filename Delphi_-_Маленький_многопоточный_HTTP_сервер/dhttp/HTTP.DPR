program http;
{$apptype console}
{$i-}

{
  little multithread http server (support only GET)

  Copyright (C) 1999  Paul Toth

  tothpaul@multimania.com
  http://www.multimania.com/tothpaul

  just a little cosmetics for Delphi 5.0 and http v1.1
  by Valery Votintsev
  rswag<at>sources.ru
  http://pascal.sources.ru
}

{
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

uses
  CrtSock,Windows,Classes,SysUtils;

const
 e404='404 File not found';
 e504='504 Invalide request';
 e200='200 Ok';

Type
 TClient=class
  Socket  :integer;
  addr    :string;
  sin,sout:TextFile;
  Request :string;
  Thread  :Thandle;
  ThreadID:dword;
  Constructor Create(AAddr:string; ASocket:integer);
  Destructor Destroy; override;
  procedure GetRequest;
  procedure ExecRequest;
  procedure Error(color:word;Msg:string);
  Procedure GET;
  procedure ListDir(Path:string);
  procedure GetFile(FileName:string);
 end;

Const
 Root   =0;
 Default=1;

Var
 LockClients:TRTLCriticalSection; // to update Clients
 Clients:TList;

 LockConfig:TRTLCriticalSection;
 IniName:string;
 Config:array[0..1] of string; // Root, Default

 LockLog:TRTLCriticalSection; // for Log()
 Console:THandle;

Function ReadIniString(Section,Key,Default:string):string;
 Var
  s:ShortString;
 begin
  s[0]:=Chr(GetPrivateProfileString(pchar(Section),pchar(Key),pchar(Default),@s[1],255,pchar(IniName)));
  Result:=s;
 end;

Function GetConfig(index:integer):string;
 begin
  EnterCriticalSection(LockConfig);
  try
   Result:=Config[index];
  finally
   LeaveCriticalSection(LockConfig);
  end;
 end;

Procedure SetConfig(index:integer;value:string);
 begin
  EnterCriticalSection(LockConfig);
  try
   Config[index]:=Value;
  finally
   LeaveCriticalSection(LockConfig);
  end;
 end;

Procedure LoadConfig;
 var
  s:string;
 begin
  WriteLn(#16' Load config :');
 // Root = "c:\root"
  s:=ReadIniString('HTTP','Root',GetConfig(Root));
  SetConfig(Root,s);
  WriteLn(' root=',s);
 // Default = "index.htm"
  s:=ReadIniString('HTTP','Default',GetConfig(Default));
  SetConfig(Default,s);
  WriteLn(' default=',s);
 end;

Procedure RemoveClient(Client:TClient);
 begin
  EnterCriticalSection(LockClients);
  try
   Clients.Remove(Client);
  finally
   LeaveCriticalSection(Lockclients);
  end;
 end;

// This Thread reply to a connected client
// 1- read the HTTP request
// 2- send the requested file
Function ClientThread(Client:TClient):integer; stdcall; far;
 begin
  Client.GetRequest;
  Client.ExecRequest;
  Client.Free;
  Result:=0;
  ExitThread(Result);
 end;

Procedure Log(color:word; s:string);
 const
  r:TSmallRect=(Left:0; Top:1; Right:79; Bottom:23);
  xy:TCoord=(x:0;y:0);
  attr:TCharInfo=(AsciiChar:' ';Attributes:FOREGROUND_RED); // don't work ?
  wxy:tCOORD =(x:0;y:23);
 var
  size:dword;
 begin
  EnterCriticalSection(LockLog);
  try
   ScrollConsoleScreenBuffer(Console,r,nil,xy,attr);
   FillConsoleOutputAttribute(Console,color,80,wxy,size);
   WriteConsoleOutputCharacter(Console,pchar(s),length(s),wxy,size);
  finally
   LeaveCriticalSection(LockLog);
  end;
 end;

Constructor TClient.Create(AAddr:string; ASocket:integer);
 begin
  inherited Create;
  Addr:=AAddr;
  Socket:=ASocket;
  Request:='<wait>';
  EnterCriticalSection(LockClients);
  try
   Clients.Add(Self);
  finally
   LeaveCriticalSection(Lockclients);
  end;
  Thread:=CreateThread(nil,0,@ClientThread,Self,0,ThreadID);
 end;

Destructor TClient.Destroy;
 begin
  RemoveClient(Self);
  CloseHandle(Thread);
  inherited Destroy;
 end;

Procedure TClient.GetRequest;
 var
  s:string;
 begin
  AssignCrtSock(Socket,sin,sout);
  ReadLn(sin,s);
  Request:=Trim(s);
  while s<>'' do ReadLn(sin,s); // ignore other data
 end;

Procedure TClient.ExecRequest;
 begin
  if Request='' then Error($01,e504) else
  case Request[1] of
   'G': GET;
   else Error($01,e504);
  end;
  CloseFile(sout);
 end;

Procedure TClient.Error(Color:word; Msg:string);
 begin
  Log(Color,addr+' : '+Request+' '+Msg);
  WriteLn(sout,'HTTP/1.0 ',Msg);
  WriteLn(sout);
  WriteLn(sout,'<html><head><title>',Msg,'</title></head><body>');
  WriteLn(sout,'<h1>',Msg,'</h1>');
  WriteLn(sout,Request);
  Writeln(sout,'</body></html>');
 end;

procedure TClient.GET;
 var
  s:string;
  p:integer;
 begin
  if Copy(Request,1,4)<>'GET ' then begin
   Error($10,e504);
   exit;
  end;

  s:=Copy(Request,5,Length(Request));
  p:=Pos('HTTP/1.',s);
  if p>0 then SetLength(s,p-1); // "GET /Path/File HTTP/1.0"
  s:=Trim(s);
  if pos('..',s)<>0 then begin // do not allow /../
   Error($4F,e504);
   exit;
  end;
  if s='/' then s:=s+GetConfig(Default); // redirect to default, not that /./ is allowed
  if s[length(s)]='/' then ListDir(s) else GetFile(s);
 end;

Procedure TClient.ListDir(Path:string);
 var
  ff:TSearchRec;
 begin
  if FindFirst(GetConfig(Root)+Path+'*.*',faAnyFile,ff)<>0 then begin
   Error($04,e404);
  end else begin
   Log($0F,addr+' : '+Request+' '+e200);
   WriteLn(sout,'HTTP/1.0 '+e200);
   Writeln(sout,'Content-Type: text/html');
   Writeln(sout);
   WriteLn(sout,'<html><head><title>s</title></head><body>');
   repeat
    if ff.name[1]<>'.' then WriteLn(sout,'<a href="',Path,ff.name,'">',ff.name,'</a><br>');
   until FindNext(ff)<>0;
   FindClose(ff);
   WriteLn(sout,'</body></html>');
  end;
 end;

Procedure TClient.GetFile(FileName:string);
 const
  BlockSize=1024;
 var
  f:file;
  s:string;
  Size:integer;
 begin
  AssignFile(f,GetConfig(Root)+FileName);
  Reset(f,1);
  if IoResult<>0 then begin
   Error($04,e404);
  end else begin
   Log($01,addr+' : '+Request+' '+e200);
   WriteLn(sout,'HTTP/1.0 '+e200);
   Writeln(sout,'Content-Transfer-Encoding: 8bit');   // don't care of MIME format
   Writeln(sout);
   SetLength(s,BlockSize);
   BlockRead(f,s[1],BlockSize,Size);
   while Size>0 do begin
    Send(Socket,@s[1],Size,0);
    BlockRead(f,s[1],BlockSize,Size);
   end;
   CloseFile(f);
  end;
 end;

var
// Server
 Server:integer;
 Down  :boolean;

 ThreadWait:THandle;
 ThreadWaitID:dword;
 Command:string;

Function WaitThread(none:pointer):integer; stdcall; far;
 Var
  Socket:integer;
  Client:TClient;
  ip:string;
 begin
  repeat
   Socket:=WaitClientEx(Server,ip);
   if Socket>0 then Client:=TClient.Create(ip,Socket);
  until (Socket<0);
  Result:=0;
  ExitThread(Result);
 end;

procedure WaitClients;
var
 Client:TClient;
 done:boolean;
begin
 WriteLn(#16' waiting for end of clients request');
 done:=false;
 repeat
  EnterCriticalSection(LockClients);
  try
   done:=(Clients.Count=0);
  finally
   LeaveCriticalSection(LockClients);
  end;
 until done;
end;

procedure ExecCommand;

 procedure Help;
  begin
   WriteLn(#16' Help :');
   writeln(' h, ?  - this help message');
   writeln(' s     - server status');
   writeln(' l     - load config');
   writeln(' exit  - exit server');
  end;

 procedure Status;
  var
   i:integer;
   c:TClient;
  begin
   WriteLn(#16' Server status');
   WriteLn(' root=',GetConfig(Root));
   WritELn(' default=',GetConfig(Default));
   EnterCriticalSection(LockClients);
   try
    for i:=0 to Clients.Count-1 do begin
     c:=Clients[i];
     writeLn(i:3,' ',c.addr,' ',c.Request);
    end;
    Writeln(' ',Clients.Count,' client(s)');
   finally
    LeaveCriticalSection(LockClients);
   end;
  end;

 begin
  case Command[1] of
   'h','?' : Help;
   's'     : Status;
   'e'     :  if (Command='exit') then Down:=true else WriteLn('unknow command, try "help"');
   'l'     : LoadConfig;
   else      WriteLn('unknow command, try "help"');
  end;
 end;

function SetupServer:boolean;
 Var
  LastLine:TCoord;
 begin
 // some setups
  FileMode:=0;
  IniName:=ParamStr(0);
  IniName[Length(IniName)-2]:='I';
  IniName[Length(IniName)-1]:='N';
  IniName[Length(IniName)  ]:='I';
  Config[Root]:='Root';
  Config[Default]:='Index.htm';
 // Get console output handle
  Console:=GetStdHandle(STD_OUTPUT_HANDLE);
 // go to last line
  LastLine.x:=0;
  LastLine.y:=24;
  SetConsoleCursorPosition(Console,LastLine);
 // Start server
  WriteLn('HTTP Server v1.0 by Paul TOTH <tothpaul@multimania.com>');
  WriteLn('http://www.multimania.com/tothpaul');
  Server:=StartServer(80); // HTTP Server
  Result:=(Server<>-1);
 end;

begin

 if SetupServer then begin
  Clients:=TList.Create;
  InitializeCriticalSection(LockConfig);
  InitializeCriticalSection(LockClients);
  InitializeCriticalSection(LockLog);
  LoadConfig;
  ThreadWait:=CreateThread(nil,0,@WaitThread,nil,0,ThreadWaitID);
  Down:=false;
  repeat
   Write('>'); ReadLn(Command);
   if command<>'' then ExecCommand;
  until Down;
  TerminateThread(ThreadWait,0);
  WaitClients;
  DeleteCriticalSection(LockLog);
  DeleteCriticalSection(LockConfig);
  DeleteCriticalSection(LockClients);
  Clients.Free;
  Disconnect(Server);
 end;

 Writeln(#16,' Server is down.');
 writeln('---[enter]---');
 ReadLn;
end.
