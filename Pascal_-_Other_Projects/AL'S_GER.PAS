{$N+}
program geron_sqrt;

function geron(x: Real): Extended;
const
  eps = 1.0E-100;
var
  y, z: Real;
begin
  y := 1.0;
  while Abs(z - y) >= eps do
  begin
    z := y;
    y := (y + x / y) / 2;
  end;
  geron := y;
end;

begin
  WriteLn('Algorithm''s Geron for computing square root from two');
  WriteLn('Geron(2.0) = ',geron(2.0));
  WriteLn('Sqrt(2.0)  = ',sqrt(2.0));
  WriteLn('Press "Enter"');
  ReadLn;
end.