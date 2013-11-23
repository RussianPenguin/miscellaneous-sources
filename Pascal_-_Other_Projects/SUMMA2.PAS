program sumation_2;
var
  i, n         : Word;
  t, add, summa: Real;
begin
  Write('Enter number of arguments n = ');
  ReadLn(n);
  summa := 0;
  for i := n downto 1 do
  begin
    t     := 1.0/i;
    add   := Sqr(t);
    summa := summa + add;
  end;
  WriteLn('Summ 1/i^2 from i = 1 to ',n);
  WriteLn('S = ',summa);
  WriteLn('Press "Enter"');
  ReadLn;
end.