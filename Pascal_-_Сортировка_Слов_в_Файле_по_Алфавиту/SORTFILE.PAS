type
  t_rec = ^t_word;
  t_word = record
    wrd  :String;
    next :t_rec;
    prev :t_rec;
  end;

function GetRec(var f:Text; var a:t_rec):Boolean;
var
  ch_c:Char;
  st_s:String;
begin
  st_s:='';
  Read(f,ch_c);
  while ((ch_c<=' ') and (not EOF(f))) do
    Read(f,ch_c);
  while ((ch_c > ' ') and (not EOF(f))) do
  begin
    st_s := st_s + ch_c;
    Read(f,ch_c);
  end;
  if(ch_c > ' ') then
  begin
    st_s := st_s + ch_c;
  end;
  if(EOF(f)) then
  begin
    Read(f,ch_c);
    if(ch_c > ' ') then
      st_s := st_s + ch_c;
  end;
  if (st_s = '') then
  begin
    a := nil;
    GetRec:=false;
  end
  else
  begin
    GetMem(a,sizeof(t_word));
    a^.wrd := st_s;
    a^.next := nil;
    GetRec:=true;
  end;
end;

procedure Sort(var t1,t2:t_rec);
var
  a,b:t_rec;
  t_s:String;
begin
  a:=t1;
  if((a<>nil) and (a^.next <> nil)) then
  begin
    while(a^.next <> nil) do
    begin
      b:=t2;
      while(b^.prev <> a^.prev) do
      begin
        if(b^.wrd < b^.prev^.wrd) then
        begin
          t_s:=b^.prev^.wrd;
          b^.prev^.wrd:=b^.wrd;
          b^.wrd:=t_s;
        end;
        b:=b^.prev;
      end;
      a:=a^.next;
    end;
  end;
end;

procedure SaveRec(var f:Text;var a:t_rec);
begin
  while(a^.next <> nil) do
  begin
    Write(f,a^.wrd,' ');
    a:=a^.next;
    FreeMem(a^.prev,SizeOf(t_word));
  end;
  Write(f,a^.wrd);
  FreeMem(a,SizeOf(t_word))
end;

var
  first :t_rec;
  temp  :t_rec;
  f1,f2 :Text;
begin
  Assign(f1,'src.txt');
  Reset(f1);
  Assign(f2,'dest.txt');
  Rewrite(f2);
  first := nil;
  if(GetRec(f1,first)) then
  begin
    temp:=first;
    first^.next:=nil;
    first^.prev:=nil;
    while(GetRec(f1,temp^.next)) do
    begin
      temp^.next^.prev:=temp;
      temp:=temp^.next;
    end;
  end;
  if(first = nil) then
    WriteLn('Nifiga ne majdenno! :(')
  else
  begin
    Sort(first,temp);
    SaveRec(f2,first);
  end;
  Close(f1);
  Close(f2);
  WriteLn('Press <Enter>');
  ReadLn;
end.