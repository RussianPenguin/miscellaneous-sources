program forward_back_sum;
uses
  Crt;
var
  x, summa, assum: Real;
  k              : Word;
begin
  ClrScr;
  WriteLn('1/n^5, 1 to 1000');
  summa := 0.0;
  for k := 1 to 1000 do
  begin
    x := k;
    summa := summa + 1.0/(x*Sqr(Sqr(x)));
  end;
  assum := 0.0;
  for k := 1000 downto 1 do
  begin
    x := k;
    assum := assum + 1.0/(x*Sqr(Sqr(x)));
  end;
  WriteLn('Straight sum = ',summa);
  WriteLn('Loopback sum = ',assum);
  WriteLn('Difference = ',summa - assum);
  WriteLn;
  WriteLn('Press "Enter"');
  ReadLn;
end.