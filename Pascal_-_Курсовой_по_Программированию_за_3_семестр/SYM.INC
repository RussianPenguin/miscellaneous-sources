function findsym( table: symptr;
                  id:    string40): symptr;
var
   sym: symptr;
   
begin
   stoupper(id);
   
   sym := table;
   while sym <> nil do
   begin

      if sym^.id[1] = id[1] then             
      if length(sym^.id) = length(id) then   
      if sym^.id = id then                   
      begin
         findsym := sym;   
         exit;
      end;

      sym := sym^.next;
   end;

   findsym := nil; 
end;

function locatesym(id:    string40): symptr;
var
   sym: symptr;

begin
   if id[1] = '^' then
      delete(id,1,1);
      
   sym := findsym(locals,id);
   if sym = nil then
      sym := findsym(globals,id);

   locatesym := sym;
end;

procedure addsym( var table: symptr;
                  id:        string40;
                  symtype:   symtypes;
                  suptype:   supertypes;
                  parcount:  integer;
                  varmap:    integer;
                  lim:       integer;
                  base:      integer;
                  dup_ok:    boolean);
begin
   if maxavail-300 < sizeof(cursym^) then
   begin
      ltok := id;
      fatal('Out of memory');
   end;

   if (not dup_ok) and (not in_interface) then
   begin
      cursym := findsym(table,id);
      if cursym <> nil then
      begin
         ltok := id;
         if (cursym^.parcount <> parcount) or 
            (cursym^.symtype <> symtype) or (cursym^.limit <> lim) then
            warning('Redeclaration not identical');
         ltok := tok;
      end;
   end;
   
   new(cursym);
   cursym^.next := table;
   table := cursym;

   cursym^.repid := decl_prefix + id;
   stoupper(id);
   cursym^.id := id;
   cursym^.symtype := symtype;
   cursym^.suptype := suptype;
   cursym^.parcount := parcount;
   cursym^.limit := lim;
   cursym^.base := base;
   cursym^.pvar := varmap;
end;

procedure newsym( id:       string40;
                  symtype:  symtypes;
                  suptype:  supertypes;
                  parcount: integer;
                  varmap:   integer;
                  lim:      integer;
                  base:     integer);
begin
   if (unitlevel = 0) or (in_interface) then
      addsym(globals,id,symtype,suptype,parcount,varmap,lim,base,false)
   else
      addsym(locals,id,symtype,suptype,parcount,varmap,lim,base,true);
end;

procedure create_unitfile(name: string64; sym, top: symptr);
var
   fd:      text;
   outbuf:  array[1..inbufsiz] of byte;
   
begin
   assign(fd,name);
{$I-}
   rewrite(fd);
{$I+}
   if ioresult <> 0 then
   begin
      ltok := name;
      fatal('Can''t create unit symbol file');
   end;
   
   setTextBuf(fd,outbuf);

   while (sym <> nil) and (sym <> top) do
   begin
      writeln(fd,sym^.id);
      writeln(fd,sym^.repid);
      writeln(fd,ord(sym^.suptype),' ',
      ord(sym^.symtype),' ',
      sym^.base,' ',
      sym^.limit,' ',
      sym^.parcount,' ',
      sym^.pvar);
      
      inc(objtotal,3);
      sym := sym^.next;
   end;

   close(fd);
end;

procedure load_unitfile(name: string64; var table: symptr);
var
   fd:      text;
   sym:     symptr;
   sstype:  byte;
   stype:   byte;
   inbuf:   array[1..inbufsiz] of byte;
      
begin
   assign(fd,name);
   {$I-} reset(fd); {$I+}
   if ioresult <> 0 then
   begin
      name := symdir + name;
      assign(fd,name);
      {$I-} reset(fd); {$I+}
   end;
   
   if ioresult <> 0 then
   begin
      ltok := name;
      fatal('Can''t open unit symbol file');
   end;
   
   setTextBuf(fd,inbuf);
   
   while not eof(fd) do
   begin
      new(sym);
      sym^.next := table;
      table := sym;
      
      readln(fd,sym^.id);
      readln(fd,sym^.repid);
      readln(fd,sstype,stype,
                sym^.base,
                sym^.limit,
                sym^.parcount,
                sym^.pvar);

      sym^.suptype := supertypes(sstype);
      sym^.symtype := symtypes(stype);
   end;

   close(fd);
end;

procedure purgetable( var table: symptr; top: symptr);

var
   sym: symptr;

begin
   
   while (table <> nil) and (table <> top) do
   begin
      sym := table;
      table := table^.next;
      dispose(sym);
   end;
end;

