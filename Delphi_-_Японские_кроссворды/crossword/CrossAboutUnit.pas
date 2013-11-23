unit CrossAboutUnit;

interface

uses Windows, SysUtils, Classes, Graphics, Forms, Controls, StdCtrls,
  Buttons, ExtCtrls, RXCtrls;

type
  TAboutBox = class(TForm)
    Panel1: TPanel;
    ProgramIcon: TImage;
    ProductName: TLabel;
    Version: TLabel;
    Copyright: TLabel;
    Comments: TLabel;
    OKButton: TButton;
    EMailLabel: TRxLabel;
    RxLabel2: TRxLabel;
    RxLabel3: TRxLabel;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    procedure RxLabel3MouseEnter(Sender: TObject);
    procedure RxLabel3MouseLeave(Sender: TObject);
    procedure EMailLabelClick(Sender: TObject);
    procedure RxLabel3Click(Sender: TObject);
    procedure RxLabel2Click(Sender: TObject);
    procedure FormCreate(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  AboutBox: TAboutBox;

implementation
uses ShellAPI, RxVerInf;

{$R *.DFM}

procedure TAboutBox.RxLabel3MouseEnter(Sender: TObject);
begin
  (Sender as TRxLabel).Font.Style:=Font.Style+[fsUnderline];
  (Sender as TRxLabel).Font.Color:=clBlue;
end;

procedure TAboutBox.RxLabel3MouseLeave(Sender: TObject);
begin
  (Sender as TRxLabel).Font.Style:=Font.Style-[fsUnderline];
  (Sender as TRxLabel).Font.Color:=clNavy;
end;

procedure TAboutBox.EMailLabelClick(Sender: TObject);
begin
  ShellExecute(Application.Handle, 'open', 'mailto:alexs@n10.ft.stavropol.ru',nil,nil,0);
end;

procedure TAboutBox.RxLabel3Click(Sender: TObject);
begin
  ShellExecute(Application.Handle, 'open', 'http://ls10/',nil,nil,0);
end;

procedure TAboutBox.RxLabel2Click(Sender: TObject);
begin
  ShellExecute(Application.Handle, 'open', 'ftp://ls10/games/jcrosword',nil,nil,0);
end;

procedure TAboutBox.FormCreate(Sender: TObject);
var V:TVersionInfo;
begin
  V:=TVersionInfo.Create(Application.ExeName);
  Label4.Caption:='—борка '+V.FileVersion;
end;

end.

