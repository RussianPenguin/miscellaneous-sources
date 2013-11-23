program factorial;

function factor(arg :LongInt) :LongInt;
var
  All, i :LongInt;
begin
  All := 1;
  for i := 1 to arg do
  begin
    All := All*i;
  end;
  factor := All;
end;

var
  y :LongInt;
begin
  Write('Enter value:');
  ReadLn(y);
  y := factor(y);
  WriteLn('Value = ',y);
  WriteLn('Press "Enter"');
  ReadLn;
end.