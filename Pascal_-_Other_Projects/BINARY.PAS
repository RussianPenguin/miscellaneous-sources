program display_binary;
var
  r :LongInt;

procedure binary(var x:LongInt);
var
  hold       : array[0..7] of boolean;
  b          : Byte;
  size, j, k : Word;
  bits       : array[1..32] of Byte;

begin
  size := SizeOf(x);
  move(x, bits, size);

  for k := size downto 1 do
  begin
    b := bits[k];
    for j := 0 to 7 do
    begin
      hold[j] := odd(b);
			b := b shr 1;
    end;

  	for j := 7 downto 0 do
      if hold[j] then
        Write(1)
      else
        Write(0);
	end;
  WriteLn;
end;

begin
  Write('Enter integer number  :');
  ReadLn(r);
  Write('Binary view of number :');
  Binary(r);
  WriteLn('Press <Enter>');
  ReadLn;
end.