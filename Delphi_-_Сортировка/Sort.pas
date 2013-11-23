unit Sort;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls;

const
  n = 13;

type
  TFSort = class(TForm)
    EArray: TEdit;
    LSorted: TLabel;
    BSort: TButton;
    procedure BSortClick(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;
  Arr = array[1..n] of Integer;

var
  FSort: TFSort;

implementation

{$R *.dfm}

procedure QuickSort(var a:Arr);
Procedure Sort(l, r: Integer);
var
  x, w :Integer;
  i, j :Integer;
begin
  i:=l;
  j:=r;
  x:=a[ (l+r) div 2];
  while i <= j do
  begin
    while a[i] < x do Inc(i);
    while a[j] > x do Dec(j);
    if i <= j then
    begin
      w := a[i];
      a[i] := a[j];
      a[j] := w;
      Inc(i);
      Dec(j);
    end;
  end;
  if l < j then Sort(l,j);
  if i < r then Sort(i,r);
end;
begin
  Sort(1,n)
end;

procedure TFSort.BSortClick(Sender: TObject);
var
  i:Integer;
  b:Arr;
begin
  for i:=1 to n do
    b[i]:=Random(1024);
  FSort.EArray.Text := '';
  for i := 1 to n do
  begin
    FSort.EArray.Text := FSort.EArray.Text + IntToStr(b[i]);
    FSort.EArray.Text := FSort.EArray.Text + ';';
  end;
  QuickSort(b);
  LSorted.Caption := '';
  for i := 1 to n do
  begin
    LSorted.Caption := LSorted.Caption + IntToStr(b[i]);
    LSorted.Caption := LSorted.Caption + ';';
  end
end;

end.
