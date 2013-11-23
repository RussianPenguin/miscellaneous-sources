unit Main;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, ExtCtrls;

type
  TForm1 = class(TForm)
    Timer1: TTimer;
    Image1: TImage;
    procedure FormShow(Sender: TObject);
    procedure Timer1Timer(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;

implementation

{$R *.dfm}

procedure TForm1.FormShow(Sender: TObject);
begin
  Width := 55;
  Height := 26;
  Left := -100;
end;

procedure TForm1.Timer1Timer(Sender: TObject);
var
  i:integer;
  h:THandle;
begin
  visible := true;

  Top := Screen.Height - Height;
  Left := 1;

  h := CreateEvent(nil,true,false,'et');

  for i := 1 to 80 do
  begin
    Top := Screen.Height-Height-i*5;
    Repaint;
    WaitForSingleObject(h,15);
  end;

  for i := 80 downto 1 do
  begin
    Top := Screen.Height-Height-i*5;
    Repaint;
    WaitForSingleObject(h,15);
  end;

  CloseHandle(h);
  Visible := false;
end;

end.
