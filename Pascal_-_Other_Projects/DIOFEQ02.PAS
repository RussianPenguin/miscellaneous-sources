program diofante_equation_2;
var
  x, y, z, w, n: LongInt;
begin
  n := MaxLongint - 63;
  n := Trunc(Sqrt(n));
  n := n - 8;
  WriteLn('x^3 = y^2 + 63,');
  WriteLn('for 1 <= y <= ',n,';');
  for y := 1 to n do
  begin
    z := y*y + 63;
    repeat
      Inc(x);
      w := x*x*x;
    until w >= z;
    if w = z then
      WriteLn('(x, y) = ','(',x,', ',y,')')
    else
      Dec(x);
  end;
  WriteLn('Press "Enter"');
  ReadLn;
end.