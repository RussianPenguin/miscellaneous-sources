{Сортировка массива выборками}
{       по неубыванию        }
program viborkami;
const
  MAXC=13;
var
  a        : array[1..MAXC] of Integer;
  i,j,k,max: Integer;
begin
  WriteLn('Введите массив из ',MAXC,' чисел:');
  for i:= 1 to MAXC do
  begin
    a[i]:=Random(255);
    Write(a[i],' ');
  end;
  WriteLn;
  for i:=MAXC downto 2 do
  begin
    j:=1;
    max:=a[j];
    for k:=1 to i do
      if a[k]>=max then
      begin
        max:=a[k];
        j:=k;
      end;
    a[j]:=a[i];
    a[i]:=max;
  end;
  For i:=1 to MAXC do
    Write(a[i],' ');
  WriteLn;
  ReadLn;
end.
