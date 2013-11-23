program matrices;
type
  t_row=array[1..65520 div SizeOf(Real)] of Real;
  t_p_row=^t_row;
  t_p_max_row_arr = array[1..65520 div SizeOf(t_p_row)] of t_p_row;
  t_p_max_matr = ^t_p_max_row_arr;

procedure CreateMatr(var pa:t_p_max_matr; m,n:Word);
var
  sp,sr,i: Word;
begin
  sp:=m*SizeOf(pointer);
  sr:=n*SizeOf(pointer);
  if((sp+m*sr) <= MemAvail) and (sp <= MaxAvail) then
  begin
    GetMem(pa,sp);
    i:=1;
    While (i <= m) and (sr <= MaxAvail) do
    begin
      GetMem(pa^[i],sr);
      inc(i);
    end;
    if (i < m) then
    begin
      for i := i downto 1 do
        FreeMem(pa^[i],sr);
      FreeMem(pa,sp);
      pa := nil;
    end;
  end
  else
    pa := nil;
end;

procedure RemoveMatr(var pa:t_p_max_matr; m,n:Word);
var
  sp,sr,i: Word;
begin
  sp:=m*SizeOf(pointer);
  sr:=n*SizeOf(pointer);
  for i:=1 to m do
    FreeMem(pa^[i],sr);
  FreeMem(pa,sp);
  pa:=nil;
end;

var
  pm  : t_p_max_matr;
  r,c,i,j :Integer;
begin
  WriteLn('Введите количество строк и столбцов:');
  ReadLn(r,c);
  CreateMatr(pm,r,c);
  if(pm <> nil) then
  begin
    for i:=1 to c do
      for j:=1 to r do
        pm^[j]^[i]:=Random(1000);
    for i:=1 to c do
    begin
      for j:=1 to r do
        Write(pm^[j]^[i]:4:0,' ');
      WriteLn;
    end;
    RemoveMatr(pm,r,c);
    WriteLn('Операция прошла успешно');
  end
  else
  begin
    WriteLn('Э-э-э... Что-то пошло не так Ж(');
  end;
  ReadLn;
end.
