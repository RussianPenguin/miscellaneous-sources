program Simple;

uses
  windows,
  messages,
  sysutils;

var
  Instance: HWnd;
  WindowClass: TWndClass;
  Handle: HWnd;
  Msg: TMsg;

procedure DoExit;
begin
  Halt;
end;

function WindowProc(Hwn,msg,wpr,lpr: longint): longint; stdcall;
begin
  result := defwindowproc(hwn,msg,wpr,lpr);
  if msg = wm_destroy then
    DoExit;
  if msg = wm_KeyDown then
    if wpr = VK_ESCAPE then
      DoExit;
end;

begin
  instance := GetModuleHandle(nil);
  WindowClass.style := CS_HRedraw or CS_VRedraw;
  WindowClass.lpfnWndProc := @windowproc;
  WindowClass.hInstance := Instance;
  WindowClass.hbrBackground := color_btnface;
  WindowClass.lpszClassName := 'DX';
  WindowClass.hCursor := LoadCursor(0,IDC_ARROW);

  RegisterClass(WindowClass);

  Handle := CreateWindowExA(0,'DX','',WS_POPUP,1,1,200,200,0,0,Instance,nil);

  ShowWindow(Handle,SW_SHOW);
  UpdateWindow(Handle);

  while GetMessage(Msg,0,0,0) do
  begin
    TranslateMessage(Msg);
    DispatchMessage(Msg);
  end
end.
