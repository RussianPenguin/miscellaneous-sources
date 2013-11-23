{Программа получает координаты n точек }
{и затем находит окружность проходящую }
{через три точки и заключающую в себе  }
{наибольшее количество точек           }
uses
  crt;
const
  num=4;
type
  pnt = object
    x,y  : real;
  end;
  crcl = object(pnt)
    rad  : real;
    kolvo: integer;
    procedure verify(var pntr: array of pnt);
    function init(var a,b,c:pnt):Boolean;
  end;

{*********************************************}
procedure crcl.verify(var pntr:array of pnt);
var
  i,res:integer;
  dl   :real;
begin
  kolvo:=0;
  for i:=0 to High(pntr) do
  begin
    dl:=sqrt(sqr(pntr[i].x-x)+sqr(pntr[i].y-y));
    if dl<=rad then
      Inc(kolvo);
  end;
end;
{*********************************************}
function crcl.init(var a,b,c:pnt):Boolean;
var
  a1,b1,c1 :Real;
  a2,b2,c2 :Real;
  x0,y0    :Real;
begin
  x0:=(a.x+b.x)/2;
  y0:=(a.y+b.y)/2;

  a1:=(a.x-b.x);
  b1:=(a.y-b.y);
  c1:=(-x0*a1-y0*b1);

  x0:=(c.x+b.x)/2;
  y0:=(c.y+b.y)/2;

  a2:=(c.x-b.x);
  b2:=(c.y-b.y);
  c2:=(-x0*a2-y0*b2);
  if(a1*b2=a2*b1) or (a1=0) then
  begin
    init:=false;
    Exit;
  end
  else
  begin
    y:=(a2*c1-c2*a1)/(a1*b2-a2*b1);
    init:=true;
  end;
  x:=(-(b1*y+c1)/a1);
  rad:=sqrt(sqr(a.x-x)+sqr(a.y-y));
end;
{*********************************************}
var
  plosk :array[1..num] of pnt;
  okr   :array[1..720] of crcl;
  i,j,k,ncrc:integer;
  max:crcl;
begin
  ncrc:=1;
  ClrScr;
  for i:=1 to num do
  begin
    writeln('Vvedite koordinati ',i,'-j tochku');
    readln(plosk[i].x,plosk[i].y);
  end;
  for i:=1 to num do
    for j:=1 to num do
    begin
      if j=i then
        continue;
      for k:=1 to num do
      begin
        if (k=j) or (k=i) then
          continue;
        if(okr[ncrc].init(plosk[i],plosk[j],plosk[k])) then
          Inc(ncrc);
      end;
    end;
  okr[1].verify(plosk);
  max := okr[1];
  for i:=2 to ncrc do
  begin
    okr[i].verify(plosk);
    if max.kolvo < okr[i].kolvo then
      max:=okr[i];
  end;
  WriteLn('********************************');
  WriteLn('O(x;y) = O(',max.x:3:2,';',max.y:3:2,')');
  WriteLn('Radius = ', max.rad:3:2);
  WriteLn('Okruznost'' soderzit tochek: ',max.kolvo-3);
  ReadLn;
end.