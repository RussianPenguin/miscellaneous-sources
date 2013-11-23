program summation;
var
  i, summa: Word;
begin
  summa := 0;
  for i := 1 to 20 do summa := summa + i;
  WriteLn('1 + 2 + ... + 20 = ',summa);
  Write('Press "Enter"');
  ReadLn;
end.