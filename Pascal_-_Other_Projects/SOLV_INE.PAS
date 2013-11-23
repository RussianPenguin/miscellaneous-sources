program solve_inequality;

function largest_power(a, b:LongInt):Word;
var
  n :Word;
  x :LongInt;
begin
  x := b;
  n := 0;
  while x <= a do
  begin
    x := b*x;
    Inc(n);
  end;
  largest_power := n;
end;

begin
  WriteLn('3^n <= 10000 < 3^(n+1)');
  WriteLn('n = ',largest_power(10000, 3));
  WriteLn('Press "Enter"');
  ReadLn;
end.