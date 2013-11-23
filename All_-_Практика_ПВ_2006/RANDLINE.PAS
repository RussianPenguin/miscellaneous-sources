uses
  Graph, Crt;
var
  Gd, Gm: Integer;
  Color : Word;
begin
  Gd := InstallUserDriver('svga256',nil);
  Gm := 6;
  InitGraph(Gd, Gm, '');
  if GraphResult <> grOk then
  begin
    WriteLn('Error');
    ReadKey;
    Halt(1);
  end;
  Randomize;
  repeat
    SetColor(Random(256));
    LineTo(Random(GetMaxX),Random(GetMaxY));
  until KeyPressed;
  ReadKey;
  CloseGraph;
  WriteLn('Current Resolution: ',GetMaxX+1,'x',GetMaxY+1);
  WriteLn('Press any key');
  ReadKey;
end.