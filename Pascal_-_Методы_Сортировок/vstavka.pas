{‘®àâ¨à®¢ª  ¬ áá¨¢  ¢áâ ¢ª ¬¨}
{       ¯® ­¥ã¡ë¢ ­¨î        }
program vstavkami;
const
  MAXC=13;
var
  a    : array[1..MAXC] of Integer;
  i,j,t: Integer;
begin
  WriteLn('‚¢¥¤¨â¥ ¬ áá¨¢ ¨§ ',MAXC,' ç¨á¥«:');
  for i:= 1 to MAXC do
  begin
    a[i]:=Random(255);
    Write(a[i],' ');
  end;
  WriteLn;
  for i:=1 to MAXC-1 do
  begin
    t:=a[i+1];
    j:=i;
    while ((j>0) and (t<a[j])) do
    begin
      a[j+1]:=a[j];
      dec(j);
    end;
    a[j+1]:=t;
  end;
  For i:=1 to MAXC do
    Write(a[i],' ');
  WriteLn;
  ReadLn;
end.
