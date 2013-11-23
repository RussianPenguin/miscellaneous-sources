unit UMySQL;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, DBXpress, StdCtrls, DB, SqlExpr;

type
  TForm1 = class(TForm)
    SQLConnection1: TSQLConnection;
    Button1: TButton;
    procedure Button1Click(Sender: TObject);
    procedure SQLConnection1BeforeConnect(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;

implementation

{$R *.dfm}

procedure TForm1.Button1Click(Sender: TObject);
begin
  
  SQLConnection1.Connected := true;
end;

procedure TForm1.SQLConnection1BeforeConnect(Sender: TObject);
begin
if SQLConnection1.LoginPrompt = false then
begin
  SQLConnection1.Params.Values['User_Name'] := 'root';
  SQLConnection1.Params.Values['Password'] := '';
end;
end;

end.
