{$N+}
program JaponaCrosswords;
uses
  crt;
const
  MAX = 100;{Максимальный размер по вертикали или горизонтали}
  COLVO = 15;{Константа, ука зыващая на максимальное число элементов в строке или столбце}
  UNREAL = 254;{Константа, указывающая на ячейку, которая не может быть заполнена}
  THINK  = 255;{Константа, указывающая на подвопросную ячейку}
var
  SetkaH,SetkaV   :array[0..MAX,0..MAX] of Byte;
  {SetkaH - набор строк, SetkaV - набор столбцов}
  Matrix          :array[0..MAX,0..MAX] of Char;
  {Матрица, которая содержит решенный кроссворд}
  Hor,Vert        :array[0..MAX,0..COLVO] of Integer;
  {Описание горизонталей и вертикалей}
  HorR, VertR     :Byte;{Размер кроссворда по горизонтали и вертикали}
  St1,St2,St3,St4 :array[0..MAX] of Integer;
  {Части кроссворда, решаемые в данный момент}

procedure Error(number :Byte); {Вывод сообщения об ошибках}
begin
  case number of
    0 :
    begin
      WriteLn('I''m sorry. You have to many horizontales');
      Halt;
    end;
    1 :
    begin
      WriteLn('I''m sorry. You have to many downs');
      Halt;
    end;
  end;
end;

procedure Load; {Загрузка кроссворда}
var
  in_file     :Text;
  Porciya     :Integer;
  i,j         :Integer;
  path        :String[255];{Путь к файлу с кроссвордом}
begin
  Write('Please, enter path for file with crosswords: ');
  ReadLn(Path);{Читаем путь}
  Assign(in_file,path);
  ReadLn(in_file,HorR);{Считываем размер по горизонтали}
  if (HorR > MAX) or (HorR < 0) then Error(0);{Проверяем}
  ReadLn(in_file,VertR);{Считываем размер по вертикали}
  if (VertR > MAX) or (VertR < 0) then Error(1);{Проверяем}
  for i := 0 to HorR do {Считываем строки с описанием из файла}
  begin
    j := 0;
    do
    begin
      Hor[i,j] := Porciya;
      Read(in_file,Porciya);
      j := j + 1;
    While(Porciya <> 0);
    ReadLn(in_file,Porciya);
  end;
  for i := 0 to VertR do {Считываем столбцы с описанием из файла}
  begin
    j := 0;
    do
    begin
      Vert[i,j] := Porciya;
      Read(in_file,Porciya);
      j := j + 1;
    While(Porciya <> 0);
    ReadLn(in_file,Porciya);
  end;
end;

procedure Save;{Сохранение готовой матрицы}
var
  out_file :Text;
  i,j      :Integer;
  path     :String[255];
begin
  Write('Please, enter path for saving file: ');
  ReadLn(Path);
  Assign(out_file,path);
  for i := 0 to VertR do {Отсчитываем горизонтали и выводим вертикали}
  begin
    for j := 0 to HorR do
    begin
      Write(out_file,Matrix[i,j]);
      WriteLn(out_file);
    end;
  end;
end;

function Analise(): Byte;
{Эта функция анализирует текущую вертикаль или горизонталь}
{и выдает текущее состояние строки, относительно уже известных}
{типов}
var
  Lenght :Byte;
  i      :Byte;
begin
  if HOV then Length := HorR; else Length := VertR;
  for i := 0 to Lenght do
  begin

  end;
end:

procedure LoadMatrix(HOV :Boolean);
{Универсальная процедура заполнения горизонталей или вертикалей матрицы}
var
  i,j,k,l,p,s,tempsc,tempsc1,temp0,temp1 :Integer;
  problema                               :Boolean;
begin
  if HOV then{Если заполняем вертикали, то temp0 равен числу горизонталей, а temp1 - горизонталей}
  begin
    temp0 := HorR;
    temp1 := VertR;
  end
  else{Иначе - наоборот}
  begin
    temp0 := VertR;
    temp1 := HorR;
  end;
  for i := 0 to temp0 do{Цикл заполнения выбранного из матрицы фрагмента}
  begin
    if HOV then j := Hor[i,0] else j := Vert[i,0];{Если заполняем вертикали,}
                                                  {то j - число фрагментов в}
                                                  {данное вертикали,}
                                                  {иначе - в данной горизонтали}
    if j = 0 then
    begin
      for k := 0 to temp1 do{Заполняем фрагмент кроссворда константами UNREAL}
      begin
         if HOV then SetkaH[i,k] := UNREAL; else SetkaV[i,k] := UNREAL;
      end;
      continue;{Переходим к следующей горизонтали (вертикали)}
    end;
    for k := 0 to temp1 do
    begin
      if HOV then St3[k] := SetkaH[i,k] else St3[k] := SetkaV[i,k];
    end;
    p := 0;
    for k := 1 to j do{Цикл заполнения St1 от начала до конца}
    begin
      if HOV then l := Hor[i,k] else l := Vert[i,k];
      tempsc := 1;
      for s := p to l do{Проверка на свободные клетки}
      begin
        if St3[p] <> UNREAL then Inc(tempsc)
        else Break;
      end;
      if tempsc < l then{Ежели места не хватает}
                        {реходим к следующи свободным полям}
      begin
        p := p + tempsc;
        k := k - 1;
        Continue;
      end;
      for s := p to l do{Вставляем линию}
      begin
        St1[p] := k;
        p := p + 1;
      end;
      p := p + 1;
    end;{Конец цикл заполнения St1 от начала до конца}
    if HOV then p := HorR else p := VertR;
    for k := j downto 1 do{Цикл заполнения St2 от конца до начала}
    begin
      if HOV then l := Hor[i,k] else l := Vert[i,k];
      tempsc := 1;
      for s := p downto 0 do
      begin
        if (St3[p] <> UNREAL) then Inc(tempsc)
        else Break;
      end;
      if tempsc < l then{Ежели места не хватает,}
                        {переходим к следующи свободным полям}
      begin
        p := p - tempsc;
        k := k + 1;
        Continue;
      end;
      for s := p downto 0 do{Вставляем линию}
      begin
        St2[p] := k;
        p := p - 1;
      end;
    end;{Конец цикла заполнения St2 от конца до начала}
    if HOV then p := HorR else p := VertR;
    for l := 0 to p do
    begin
      if St1[l] = St2[p] then St4[p] := St1[p];
      {Если в St1 и St2 есть одинаковые символы, то вносим их в St4}
      if (St3[l] = THINK) then problema := true;
    end;
    if problema then{Если имеется проблема в виде THINK,}
                    {то используем функцию интелектуальной вставки ячеек}
      Insert(Analise);
  end;{Конец цикла заполнения}
end;

procedure Solving; {Решение кроссворда}
begin
  While(TestMatrix = false){Пока функция тестирования}
                           {матрицы выдает false "прогоняем" заполнение матрицы}
  begin
    LoadMatrix(true);{Прогонка горизонталей}
    LoadMatrix(false);{Прогонка вертикалей}
    Unite;{Объединение вертикалей с горизонталями}
  end:
  ToChar;{Перевод решенного кроссворда к подобающему виду}
  Print;{Вывод на экран}
end;

{int main()}
var
  i :Char;
begin{Main функция: собирает данны и вызывает нужные функции}
  ClrScr;
  WriteLn('*--------------------------------------------*');
  WriteLn('|  Program for solving Japenese crosswords   |');
  WriteLn('|     This program was create by Stalker     |');
  WriteLn('|          All rights reserved ;-P           |');
  WriteLn('*--------------------------------------------*');
  WriteLn;
  WriteLn;
  Load;
  Solving;
  Write('Save results Yes[Y] or No[N]: ');
  ReadLn(i);
  if (i = 'y') or (i = 'Y') then Save;
  WriteLn('!Program is complete!');
  WriteLn('Press <Enter>');
end.
