procedure pfor;
var
   up:       boolean;
   id:       string80;
   low,high: string80;

begin
   nospace := true;
   puts('for (');
   gettok; 

   id := plvalue;
   gettok; 

   low := pexpr;

   if tok = 'TO' then
      up := true
   else

   if tok = 'DOWNTO' then
      up := false;

   gettok;
   high := pexpr;

   if up then
      puts(id+' = '+low+'; '+id+' <= '+high+'; '+id+'++) ')
   else
      puts(id+' = '+low+'; '+id+' >= '+high+'; '+id+'--) ');

   nospace := false;
   gettok;   {consume the DO}
   pstatement;
end;

procedure pwhile;
begin
   gettok; 

   nospace := true;
   puts('while ('+pexpr+') ');
   nospace := false;

   gettok; 
   pstatement;
end;

procedure pwith;
var
   prefix: string;
   levels: integer;
   
begin
   gettok; 
   levels := 0;
   puts('{ ');
   nospace := true;
      
   repeat
      if tok[1] = ',' then 
      begin
         gettok;
         newline;
         puts('  ');
      end;
         
      prefix := plvalue;
      make_pointer(prefix);
      
      inc(levels);
      inc(withlevel);
      puts('void *with'+itoa(withlevel)+' = '+prefix+'; ');
      
   until tok[1] <> ',';
   
   nospace := false;
   gettok;  
   
   if tok[1] <> '{' then
      pstatement
   else

   begin
      gettok;
   
      while (tok[1] <> '}') and not recovery do
      begin
         pstatement; 
   
         if tok[1] = ';' then
         begin
            puttok;
            gettok;  
         end;
      end;
      
      gettok;        
   end;

   puts('   } ');
   newline;

   if tok[1] = ';' then
      gettok;

   dec(withlevel,levels);
end;

procedure prepeat;
begin
   puts('do { ');
   gettok;

   while (tok <> 'UNTIL') and not recovery do
   begin
      pstatement;

      if tok[1] = ';' then
      begin
         puttok;
         gettok;
      end;
   end;

   gettok;
   nospace := true;
   puts('}  while (!('+ pexpr+ '))');
   nospace := false;
end;

procedure pcase;
var
   ex:  string80;
   ex2: string80;   
   i:   integer;
   c:   char;

begin
   
   gettok;
   ex := pexpr;
   puts('switch ('+ex+') {');

   gettok;

   while (tok[1] <> '}') and (tok <> 'ELSE') and not recovery do
   begin

      repeat
         if tok[1] = ',' then
            gettok;

         if tok = '..' then
         begin
            gettok;
            ex2 := pexpr;
            
            if (ex2[1] = '''') or (ex2[1] = '"') then
               for c := succ(ex[2]) to ex2[2] do
               begin
                  newline;
                  puts('case '''+c+''':   ');
               end
            else
            
            if atoi(ex2) - atoi(ex) > 128 then
            begin
               ltok := ex+'..'+ex2;
               warning('Gigantic case range');
            end 
            else
            
            for i := succ(atoi(ex)) to atoi(ex2) do
            begin
               newline;
               write(ofd[unitlevel],'case ',i,':   ');
            end;
         end
         else
         
         begin
            ex := pexpr;
            newline;
            puts('case '+ex+':   ');
         end;

      until (tok[1] = ':') or recovery;
      gettok;

      if (tok[1] <> '}') and (tok <> 'ELSE') then
         pstatement;
      puts('break; ');
      newline;

      if tok[1] = ';' then
         gettok;
   end;

   if tok = 'ELSE' then
   begin
      newline;
      puts('default: ');
      gettok; 

      while (tok[1] <> '}') and not recovery do
      begin
         if (tok[1] <> '}') and (tok <> 'ELSE') then
            pstatement;
         if tok[1] = ';' then
            gettok;
      end;
   end;

   puttok;
   gettok;

   if tok[1] = ';' then
      gettok;
end;

procedure pif;
var
   pspace: integer;
begin
   
   gettok; 

   pspace := length(spaces);
   nospace := true;
   puts('if ('+ pexpr+ ') ');
   nospace := false;
   
   gettok; 

   if (tok[1] <> '}') and (tok <> 'ELSE') then
      pstatement;

   if tok = 'ELSE' then
   begin
      spaces := copy(spaces,1,pspace);
      if not linestart then
         newline;
      puts('else ');

      gettok;
      if tok[1] <> '}' then
         pstatement;
   end;

end;

procedure pexit;
begin

   puts('return;');

   gettok;
   if tok[1] = ';' then
      gettok;
end;

procedure phalt;
var
   ex: anystring;

begin

   gettok;

   if tok[1] = '(' then
   begin
      gettok;
      ex := pexpr;
      gettok;
   end
   else
      ex := '0';

   puts('exit('+ex+');');

   if tok[1] = ';' then
      gettok;
end;

procedure pread;
var
   ctl:  string;
   func: anystring;
   ex:   paramlist;
   p:    string;
   ln:   boolean;
   ty:   string[2];
   i:    integer;

begin
 
   nospace := true;  

   ln := tok = 'READLN';
   nospace := true;
   func := 'scanv(';

   gettok; 

   if tok[1] = '(' then
   begin
      gettok;

      if ltok[1] = '[' then  
      begin
         gettok; 

         if tok[1] = ']' then
            func := 'scanf('
         else

         begin
            gettok; 
            gettok; 
            func := 'fiscanf(' + usetok + ',';
            gettok;   {consume the ')'}
         end;

         gettok;
         if tok[1] = ',' then
            gettok;
      end;

      ctl := '';
      ex.n := 0;

      while (tok[1] <> ')') and not recovery do
      begin
         p := pexpr;
         ty := exprtype;

         if (ex.n = 0) and (ty = '@') then
            func := 'fscanv(' + p + ','
         else

         begin
            if ty <> 's' then
               if p[1] = '*' then
                  delete(p,1,1)
               else
                  p := '&' + p;
            inc(ex.n);
            if ex.n > maxparam then
               fatal('Too many params (pread)');
            ex.id[ex.n] := p;
            ctl := ctl + '%'+ty;
         end;

         if tok[1] = ',' then
            gettok;
      end;

      gettok; 

      if ctl = '%s' then
         ctl := '#';
      if ln then
         ctl := ctl + '\n';

      if func[1] <> 'f' then
         func := 'f' + func + 'stdin,';

      puts(func+'"'+ctl+'"');
      for i := 1 to ex.n do
         puts(','+ex.id[i]);

      puts(')');
   end

   else
      if ln then
         puts('scanf("\n")');

   nospace := false;

   if tok[1] = ';' then
   begin
      puttok;
      gettok;
   end
   else

   begin
      puts('; ');
      newline;
   end;

end;

type
   write_modes = (m_write, m_writeln, m_str);

procedure pwrite(mode: write_modes);
var
   ctl:  string;
   func: anystring;
   ex:   paramlist;
   p:    string;
   ty:   string[2];
   i:    integer;

   procedure addform(f: anystring);
   begin
      if isnumber(f) then
         ctl := ctl + f   
      else
      begin               
         ctl := ctl + '*';
         inc(ex.n);
         if ex.n > maxparam then
            fatal('Too many params (pwrite.form)');
         ex.id[ex.n] := ex.id[ex.n-1];
         ex.id[ex.n-1] := f;
      end;
   end;
   
begin
   nospace := true; 

   if mode = m_str then
      func := 'sbld('
   else
      func := 'printf(';
      
   gettok;  
   
   if tok[1] = '(' then
   begin
      gettok;

      if ltok[1] = '[' then
      begin
         gettok; 

         if tok[1] <> ']' then
         begin
            gettok;
            gettok;
            func := 'iprintf(' + usetok + ',';
            gettok;   {consume the ')'}
         end;

         gettok;   
         if tok[1] = ',' then
            gettok;
      end;

      ctl := '';
      ex.n := 0;

      while (tok[1] <> ')') and not recovery do
      begin
         p := pexpr;
         ty := exprtype;

         if (ex.n = 0) and (ty = '@') then
            func := 'fprintf(' + p + ','
         else

         begin
            inc(ex.n);
            if ex.n > maxparam then
               fatal('Too many params (pwrite)');
            ex.id[ex.n] := p;

            if ty = 'D' then
               ty := 'ld';
            if ty = 'b' then
               ty := 'd';

            if tok[1] = ':' then
            begin
               ctl := ctl + '%';
               gettok;
               addform(pexpr);               
               
               if tok[1] = ':' then
               begin
                  ctl := ctl + '.';
                  gettok;
                  addform(pexpr);
                  ty := 'f';
               end;
               
               ctl := ctl + ty;
            end
            else

            begin
               if (p[1] = '"') or (p[1] = '''') then
               begin
                  ctl := ctl + copy(p,2,length(p)-2);
                  dec(ex.n);
               end

               else
                  ctl := ctl + '%'+ty;
            end;
         end;

         if tok[1] = ',' then
            gettok;
      end;

      gettok; 

      if mode = m_writeln then
         ctl := ctl + '\n';

      if mode = m_str then
      begin
         func := func + ex.id[ex.n] + ',';
         dec(ex.n);
         delete(ctl,length(ctl)-1,2);
      end;
      puts(func+'"'+ctl+'"');
      for i := 1 to ex.n do
         puts(','+ex.id[i]);

      puts(')');
   end

   else
      if mode = m_writeln then
         puts('printf("\n")');

   nospace := false;

   if tok[1] = ';' then
   begin
      puttok;
      gettok;
   end
   else

   begin
      puts('; ');
      newline;
   end;

end;

procedure pnew;
var
   lv: string;
begin


   gettok;  
   gettok;  

   lv := plvalue;
   puts(lv+' = malloc(sizeof(*'+lv+'));');

   gettok;  
   if tok[1] = ';' then
      gettok;
end;

procedure pident;

var
   ex: string;
   lv: string;
   lvt,ext: char;

begin


   nospace := true; 
   lv := plvalue;   
   lvt := exprtype; 

   if tok = ':=' then
   begin
      gettok;
      ex := pexpr;
      ext := exprtype;

      if iscall(lv) then
         puts('return '+ex)
      else

      begin
         if copy(ex,1,5) = 'scat(' then
            puts('sbld('+lv+',' + copy(ex,6,255))
         else

         if lvt = 's' then
            if ext = 's' then
               puts('strcpy('+lv+','+ex+')')
            else
               puts('sbld('+lv+',"%'+ext+'",'+ex+')')
         else

         if lvt = 'c' then
            if ext = 's' then
               puts(lv+' = first('+ex+')')
            else
               puts(lv+' = '+ex)
         else
            puts(lv+' = '+ex);
      end;
   end
   else

   if tok[1] = ':' then
   begin

      
      putline;
      puts(lv+': ');

      gettok;

      if tok[1] = ';' then
         gettok;

      exit;
   end
   else

   begin   

      if iscall(lv) then
         puts(lv)
      else
         puts(lv+'()');
   end;
   
   nospace := false;

   if tok[1] = ';' then
   begin
      puttok;
      gettok;
   end
   else

   begin
      puts('; ');
   end;

end;

procedure pstatement;
var
   builtin: boolean;
   
begin

   if (toktype = identifier) and (cursym <> nil) then
      builtin := cursym^.suptype = ss_builtin
   else
      builtin := false;

   case tok[1] of
   '.':
      exit;

   ';':
      begin
         puts('; ');
         gettok;
      end;
      
   '{':
      pblock;

   'C':
      if tok = 'CASE' then
         pcase
      else
         pident;

   'E':
      if builtin and (tok = 'EXIT') then
         pexit
      else
         pident;

   'F':
      if tok = 'FOR' then
         pfor
      else
         pident;
        
   'H':
      if tok = 'HALT' then
         phalt
      else
         pident;
         
   'I':
      if tok = 'IF' then
         pif
      else
         pident;
   'N':
      if tok = 'NEW' then
         pnew
      else
         pident;
   'R':
      if tok = 'REPEAT' then
         prepeat
      else
      if tok = 'READ' then
         pread
      else
      if tok = 'READLN' then
         pread
      else
         pident;
   'S':
      if builtin and (tok = 'STR') then
         pwrite(m_str)
      else
         pident;
                  
   'W':
      if tok = 'WHILE' then
         pwhile
      else
      if tok = 'WITH' then
         pwith
      else
      if tok = 'WRITE' then
         pwrite(m_write)
      else
      if tok = 'WRITELN' then
         pwrite(m_writeln)
      else
         pident;
   else
      pident;
   end;
end;

procedure pblock;
begin

   puts('{ ');
   gettok; 

   while (tok[1] <> '}') and not recovery do
   begin
      pstatement;

      if tok[1] = ';' then
      begin
         puttok;
         gettok;   
      end;
   end;

   if not linestart then
      newline;
      
   puttok; 

   gettok;
   if tok[1] = ';' then
      gettok;
end;

procedure puses;
begin
   gettok; 
   
   repeat

      puts('#include "'+ltok+'.UNH"');
      newline;                      
      
      load_unitfile(ltok+'.UNS',globals);

      top_interface := globals;     
      
      gettok;
      if tok[1] = ',' then
         gettok;
   until (tok[1] = ';') or recovery;
   
end;
procedure pinterface;
begin
   gettok;
   if tok = 'USES' then
      puses;
      
   in_interface := true;
   top_interface := globals;

   putline;
   putln('#define extern /* globals defined here */');
   putln('#include "'+unitname+'.UNH"');
   putln('#undef extern');
   
   inc(unitlevel);
   assign(ofd[unitlevel],unitname+'.UNH');
   rewrite(ofd[unitlevel]);
   getmem(outbuf[unitlevel],inbufsiz);
   SetTextBuf(ofd[unitlevel],outbuf[unitlevel]^,inbufsiz);

   putline;

   if tok[1] = ';' then
      gettok;
end;

procedure pimplementation;
begin

   if not in_interface then
      exit;
   in_interface := false;

   close(ofd[unitlevel]);
   freemem(outbuf[unitlevel],inbufsiz);
   dec(unitlevel);
   
   create_unitfile(unitname+'.UNS',globals,top_interface);

   gettok;
end;