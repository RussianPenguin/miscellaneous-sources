program MySQL;

uses
  Forms,
  UMySQL in 'UMySQL.pas' {Form1};

{$R *.res}

begin
  Application.Initialize;
  Application.CreateForm(TForm1, Form1);
  Application.Run;
end.
