{$N+}
{You can use this program for convert value in ieee's format}
program ieee;
uses
  crt;
const
  mask = 127;

type
  byte_array = array[0..9] of byte;

var
	x, y, m: Extended;
	b			 : byte_array;
	k      : Word;
  e      : Integer;
	s, u   : 0..1;

begin
	ClrScr;
	Write('Please enter real number: ');
	ReadLn(x);
	b := byte_array(x);

	WriteLn('Bytes of entered number:');
	Write('Position of byte: ');
	for k := 9 downto 0 do Write(k:5);
	WriteLn;
	Write('Meaning         : ');
	for k := 9 downto 0 do Write(b[k]:5);
  WriteLn;
  WriteLn;

  e := 256*(b[9] and mask) + b[8];
  s := b[9] shr 7;
  u := b[7] shr 7;
  m := 0.0;

  for k := 0 to 6 do m := m/256.0 + b[k];
  m := (m/256.0 + (b[7] and mask))/128.0;
  WriteLn('Exponent             e = ',e);
  WriteLn('Digit bit            s = ',s);
  WriteLn('Loss of moment bit   u = ',u);
  WriteLn('Coefficient          m = ',m);
  WriteLn;

  y := u + m;
  e := e - 16383;
  if e > 0 then
    for k := 1 to e do
      y := 2.0 * y
  else
    for k := 1 to -e do
      y := y / 2.0;

  if s = 1 then
    y := -y;

  WriteLn('Formula for reconstruction of value :');
  WriteLn('x = [(-1)*s]*[2^(e - 16383)]*[u.m]');
  WriteLn('Reconstruction   x = ',y:26);
  WriteLn('Original value   x = ',x:26);
  WriteLn('Press <Enter>');
  ReadLn;
end.