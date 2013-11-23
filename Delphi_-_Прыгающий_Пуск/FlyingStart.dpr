program FlyingStart;

uses
  Forms,Windows,
  Main in 'Main.pas' {Form1};

{$R *.res}
var
  EStyle :Integer;
begin
  Application.Initialize;
  EStyle := GetWindowLong(Application.Handle,GWL_EXSTYLE);
  SetWindowLong(Application.Handle,GWL_EXSTYLE,EStyle or WS_EX_TOOLWINDOW);
  Application.CreateForm(TForm1, Form1);
  Application.Run;
end.
