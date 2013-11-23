{$N+}
program product;
const
  m = 400;
var
  p, x: Extended;
  n   : Word;
begin
  p := 1.0;
  for n := 2 to m do
  begin
    x := Sqrt(1.0/n);
    if Odd(n) then
      p := p * (1.0 - x)
    else
      p := p * (1.0 + x);
  end;
  WriteLn('Product for 2 <= n <= ',m,':');
  WriteLn;
  WriteLn('P (1 + (-1)^n / n^2) = ',p);
  WriteLn;
  WriteLn('Press "Enter"');
  ReadLn;
end.