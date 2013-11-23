program twirl;
uses
  dos, crt;

procedure rot(j, k: Integer; color, speed: Word);
const
  line: array[0..3] of char = ('|','\','-','/');
var
  m :Integer;
begin
  textcolor(color);
  m := 0;
  repeat
    gotoxy(j,k);
    writeln(line[m]);
    gotoxy(1,1);
    delay(speed);
    m := (m + 1) mod 4;
  until keypressed;
  textcolor(LightGray);
end;

begin
  rot(40,13,Yellow,10000);
end.
