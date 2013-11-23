{Сортировка методом пузырька}
{      по неубыванию        }
program puser;
const
  MAX=13;
var
  mas  : array[1..MAX] of Integer;
  i,j,k: Integer;
begin
  WriteLn('Введите массив из ',MAX,' чисел: ');
  for i:= 1 to MAX do
  begin
    mas[i]:=Random(255);
    Write(mas[i],' ');
  end;
  WriteLn;
  for j:=MAX downto 2 do
  begin
    for i:=1 to MAX-1 do
    begin
      if mas[i]>=mas[i+1] then
      begin
        k:=mas[i];
        mas[i]:=mas[i+1];
        mas[i+1]:=k;
      end
    end;
  end;
  for i:=1 to MAX do
    Write(mas[i],' ');
  ReadLn;
end.