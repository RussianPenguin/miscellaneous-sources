program diofantine_equation_1;
var
  x, y: Integer;
begin
  WriteLn('19x + 5y = 100');
  WriteLn('1 <= x <= 100, 1 <= y <= 100');
  for x := 1 to 100 do
    for y := 1 to 100 do
      if 19*x + 5*y = 100 then
        WriteLn('(x, y) = (',x,' ,',y,')');
  WriteLn('Press "Enter"');
  ReadLn;
end.