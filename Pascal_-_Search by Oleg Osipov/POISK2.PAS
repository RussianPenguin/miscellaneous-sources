Uses DOS;
var fw:text;
    zai:string;
function NalichieSlova(sl,str:string):boolean;
var i,j,k:byte;
    f:boolean;
begin
  f:=false;
  for i:=1 to ord(str[0])-ord(sl[0])+1 do
  begin
    j:=1;
    k:=i;
    while sl[j] = str[k] do begin
                              inc(j);
                              inc(k);
                            end;
    if j-1=ord(sl[0]) then f:=true;
  end;
  NalichieSlova:=f;
end;

procedure PoiskFaila(f_name,Path:string);
var S:SearchRec;
    tek,tekp:string;
    f:text;
    i:byte;
begin
  Assign(f,f_name);
  {$I-}
  Reset(f);
  {$I+}
  if IOresult <> 0 then
  begin
    FindFirst('*.',Anyfile,S);
    FindNext(S);
    FindNext(S);
    while (S.size > 0) and (DosError = 0) do FindNext(S);
    while DosError = 0 do
      begin
        GETDIR(4,tek);
        if tek = 'D:\' then tekp:=tek+S.name
                       else tekp:=tek+'\'+S.name;
        writeln(tekp,' ',ord(s.name[0]));
        writeln(fw,tekp,' ',ord(s.name[0]));
        CHDIR(S.name);
        PoiskFaila('Поиск.bak',Path);
        CHDIR('..');
        FindNext(S);
        while (S.size > 0) and (DosError = 0) do FindNext(S);
      end;
  end;
end;


var str,sl,f_name,Path:string;
    f,fr:text;
begin
  getdir(4,sl);
  chdir('d:\');
  f_name:='fack.img';
  asm
  lea si,f_name
  inc si
  xor cx,cx
  mov bx,2
  mov dx,10h
  mov ah,6ch
  int 21h
  end;

  Assign(fw,'d:\result.bak');rewrite(fw);
  Assign(f,'Поиск.bak');
  {$I-}
  Reset(f);
  {$I+}
  if IOresult <> 0 then PoiskFaila('Поиск.bak',Path) else
  begin
    readln(f,f_name);
    readln(f,sl);
    Close(f);
  end;
  write(sl);
  readln;
  chdir(sl);
  readln;
end.
