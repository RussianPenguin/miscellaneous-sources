Program convert;

function char2num(c: char):byte;
begin
  if c in ['0'..'9'] then char2num := byte(c) - byte('0')
   else char2num := byte(Upcase(c)) - byte('A') + 10;
end;

function num2char(b: byte): char;
begin
  if b in [0..9] then num2char := chr(b + byte('0'))
   else num2char := chr(b + byte('A') - 10);
end;

var s1, s2: string;
    d1, d2, i: byte;
    n: longint;

begin
  writeln('** Перевод чисел из одной системы счисления в другую **');
  write('Введите число (используя символы 0..9,A..Z): '); readln(s1);
  write('Основание системы счисления введенного числа: '); readln(d1);
  i := 1;
  while (i <= length(s1)) and (char2num(s1[i]) < d1) do
    i := i + 1;
  if i <= length(s1) then writeln('Неверно введенное число!')
   else begin
     write('Основание системы счисления результата: '); readln(d2);
     n := 0;
     for i := 1 to length(s1) do
       n := n * d1 + char2num(s1[i]);
     s2 := '';
     repeat
       s2 := num2char(n mod d2) + s2;
       n := n div d2;
     until n = 0;
     writeln('Результат: ', s1, '(', d1, ') = ', s2, '(', d2, ')')
   end;
   ReadLn;
end.