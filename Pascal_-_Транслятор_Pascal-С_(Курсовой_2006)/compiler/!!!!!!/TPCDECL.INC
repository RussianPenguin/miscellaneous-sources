function psimpletype: string80;
var
   sym: symptr;

begin
   sym := locatesym(ltok);
   if sym <> nil then
   begin
      curtype := sym^.symtype;
      if cursuptype = ss_none then
         cursuptype := sym^.suptype;
      curlimit := sym^.limit;
      curbase := sym^.base;
      curpars := sym^.parcount;
   end;

   psimpletype := usetok;
end;

procedure pdatatype(stoclass: anystring;
                    var vars: paramlist;
                    prefix:   anystring;
                    suffix:   anystring;
                    addsemi:  boolean);

const
   forward_typedef: anystring = '';
   forward_undef:   anystring = '';

var
   i:      integer;
   ts:     anystring;
   ex:     anystring;
   sym:    symptr;
   nbase:  integer;
   bbase:  integer;
   nsuper: supertypes;
   
   procedure pvarlist;
   var
      i:    integer;
      pcnt: integer;

   begin
      ts := '';
      pcnt := -1;
            
      if tok = 'ABSOLUTE' then
      begin
         gettok; 
         ts := pexpr;

         if tok[1] = ':' then
         begin
            gettok;
            ts := ' = MK_FP('+ts+','+pexpr+')';
         end
         
         else
         begin
            if ts[1] = '*' then
               ts := ' = ' + copy(ts,2,255)
            else
               ts := ' = &(' + ts + ')';
         end;
         if length(prefix) = 0 then
            prefix := '*';
         pcnt := -2;
      end;

      if cursuptype = ss_none then
         cursuptype := ss_scalar;
                          
      for i := 1 to vars.n do
      begin
         newsym(vars.id[i],curtype,cursuptype,pcnt,withlevel,curlimit,nbase);
         puts(prefix+vars.id[i]+suffix+ts);
         if i < vars.n then
            puts(', ');
      end;
   end;


   procedure parray;
   begin

      gettok; 

      repeat
         gettok; 

         ts := pexpr; 
         if isnumber(ts) then
            nbase := atoi(ts)
         else
            nbase := curbase;

         if tok = '..' then
         begin
            gettok;
            ts := pexpr;

            subtract_base(ts,nbase-1);
         end
         else

         begin 
            sym := locatesym(ts);
            if sym <> nil then
            begin
               nbase := sym^.base;
               if (sym^.limit > 0) and (sym^.suptype <> ss_const) then
                  ts := ' /* ' + ts + ' */ ' + itoa(sym^.limit-nbase+1);
            end;
         end;
   
         suffix := suffix + '[' + ts + ']'; 

      until tok[1] <> ',';
      
      gettok;  
      gettok;  

      cursuptype := ss_array;
   end;


   procedure pstring;
   begin

      gettok;  

      if tok[1] = '[' then
      begin
         gettok;   

         nsuper := cursuptype;
         ts := pexpr;
         cursuptype := nsuper;
         subtract_base(ts,-1);
         suffix := suffix + '[' + ts + ']'; 
         
         gettok;   
      end
      else
         suffix := suffix + '[STRSIZ]';

      puts(ljust(stoclass+'char',identlen));
      curtype := s_string;
      nbase := 1;
      pvarlist;
   end;


   procedure ptext;
   begin

      gettok; 

      if tok[1] = '[' then
      begin
         gettok;
         nsuper := cursuptype;
         ts := pexpr;
         cursuptype := nsuper;
         gettok;
      end;

      puts(ljust(stoclass+'text',identlen));
      curtype := s_file;
      pvarlist;
   end;


   procedure pfile;
   begin

      gettok;   

      if tok = 'OF' then
      begin
         gettok;
         ts := tok;
         gettok;
         ts := '/* file of '+ts+' */ ';
      end
      else
         ts := '/* untyped file */ ';

      puts(ljust(stoclass+'int',identlen)+ts);
      curtype := s_file;
      pvarlist;
   end;


   procedure pset;
   begin
      gettok; 
      gettok; 

      ts := '/* ';
      if toktype = identifier then
         ts := ts + usetok
      else

      if tok = '(' then
      begin
         repeat
            ts := ts + usetok
         until (tok[1] = ')') or recovery;
         ts := ts + usetok;
      end

      else
         ts := ts + psetof;

      puts(ljust(stoclass+'setrec',identlen)+ts+' */ ');
      curtype := s_struct;
      pvarlist;
   end;


   procedure pvariant;
   begin

      gettok; 

      ts := ltok;
      gettok; 

      if tok[1] = ':' then
      begin
         gettok;
         puts(ltok+' '+ts+ ';  /* Selector */');
         gettok;
      end
      else
         puts(' /* Selector is '+ts+' */');

      gettok;
      puts('union { ');
      newline;

      while (tok <> '}') and not recovery do
      begin
         ts := pexpr;  
         while tok[1] = ',' do
         begin
            gettok;
            ts := pexpr;
         end;

         gettok; 

         puts(' struct {  ');

         ts := 's' + ts;
         decl_prefix := 'v.'+ts+'.';
         pvar;
         decl_prefix := '';
         
         gettok; 

         puts(' } '+ts+';');
         newsym(ts,s_void,ss_struct,-1,0,0,0);
         cursym^.repid := ts;

         if tok[1] = ';' then
            gettok;
      end;

      puts(' } v;');
      newline;
   end;


   procedure precord;
   begin
      puts(stoclass+'struct '+vars.id[1]+' { ');

      inc(withlevel);
      pvar;

      if tok = 'CASE' then
         pvariant;
      dec(withlevel);

      puttok;   {output the closing brace}
      gettok;   {and consume it}

      curtype := s_struct;
      cursuptype := ss_struct;
      pvarlist; {output any variables of this record type}

      {convert a #define into a typedef in case of a forward pointer decl}
      if length(forward_typedef) > 0 then
      begin
         puts(';'); 
         newline;
         puts(forward_undef); 
         newline;
         puts(forward_typedef);
         forward_typedef := '';
      end;
   end;


   procedure penum;
   var
      members: integer;

   begin
      puts(stoclass+'enum {  ');

      gettok;
      members := 0;
      repeat
         puts(ltok);
         if toktype = identifier then
            inc(members);
         gettok;
      until (tok[1] = ')') or recovery;

      puts(' } ');
      gettok; 

      curtype := s_int;
      curlimit := members-1;
      nbase := 0;
      pvarlist;
   end;


   procedure pintrange;
   begin

      ex := pexpr; 
      nbase := atoi(ex);
      
      if tok <> '..' then
      begin
         syntax('".." expected');
         exit;
      end;
      
      gettok; 
      ts := pexpr;

      sym := locatesym(ts);
      if sym <> nil then
         if sym^.limit > 0 then
            ts := itoa(sym^.limit);

      curtype := s_int;
      curlimit := atoi(ts);
      puts(ljust(stoclass+'int',identlen)+'/* '+ex+'..'+ts+' */ ');
      pvarlist;
   end;

   procedure pcharrange;
   begin

      ex := pexpr;
      nbase := ord(ex[2]);

      if tok <> '..' then
      begin
         syntax('".." expected');
         exit;
      end;

      gettok;     
      ts := pexpr;

      sym := locatesym(ts);
      if sym <> nil then
         if sym^.limit > 0 then
            ts := itoa(sym^.limit);

      curtype := s_char;
      curlimit := ord(ts[2]);
      puts(ljust(stoclass+'char',identlen)+'/* '+ex+'..'+ts+' */ ');
      pvarlist;
   end;

   procedure psimple;
   begin
      ex := psimpletype;
      if cursuptype <> ss_array then
         nbase := curbase;
      
      if tok =  '..' then
      begin
         
         gettok;
         ts := pexpr;
   
         sym := locatesym(ts);
         if sym <> nil then
            if sym^.limit > 0 then
               ts := itoa(sym^.limit);
   
         curtype := s_int;
         curlimit := curbase;
         puts(ljust(stoclass+'int',identlen)+'/* '+ex+'..'+ex+' */ ');
         pvarlist;
         exit;
      end;
      i := pos('^',ex);
      if i <> 0 then
      begin
      
         delete(ex,i,1);
         prefix := '*';
         cursuptype := ss_pointer;
      end;
   
      sym := locatesym(ex);
      if (stoclass = 'typedef ') and (vars.n = 1) and 
         (prefix = '*') and (sym = nil) then
      begin
      
         newsym(vars.id[1],curtype,cursuptype,-1,0,curlimit,0);
         puts(ljust('#define '+vars.id[1],identlen)+'struct '+ex+' *');
         forward_undef := '#undef '+vars.id[1];
         forward_typedef := 'typedef struct '+ex+' *'+vars.id[1];
         addsemi := false;
      end
      else
      begin
      
         puts(ljust(stoclass+ex,identlen));
         pvarlist;
      end;
   end;

begin
   cursuptype := ss_none;
   curlimit := 0;
   nbase := 0;

   if tok = 'EXTERNAL' then
   begin
      gettok;
      stoclass := 'extern '+stoclass;
   end;
   
   if tok = 'PACKED' then
      gettok;
   while tok = 'ARRAY' do
      parray;
   if tok = 'PACKED' then
      gettok;

   if tok = 'STRING'        then pstring
   else if tok = 'TEXT'     then ptext
   else if tok = 'FILE'     then pfile
   else if tok = 'SET'      then pset
   else if tok = '('        then penum
   else if tok = 'RECORD'   then precord
   else if toktype = number then pintrange
   else if toktype = chars  then pcharrange
   else psimple;

   if addsemi then
      puts(';');
   puts(' ');

   if tok[1] = ';' then
      gettok;
end;

procedure pconst;

var
   vars:    paramlist;
   parlev:  integer;
   exp:     string;
   dup:     boolean;

begin

   gettok;

   while (toktype <> keyword) and not recovery do
   begin
      nospace := false;
      vars.n := 1;
      vars.id[1] := ltok;

      gettok;  

      if tok[1] = '=' then 
      begin
         

         {$b-}
         dup := (unitlevel > 0) and (cursym <> nil) and 
                (cursym^.suptype = ss_const);
                     
         gettok;

         exp := pexpr;
         curtype := cexprtype;
         if isnumber(exp) then
            curlimit := atoi(exp);
         newsym(vars.id[1],curtype,ss_const,-1,0,curlimit,0);
         if dup then
         begin
            vars.id[1] := procnum + '_' + vars.id[1];
            cursym^.repid := vars.id[1];
         end;
         
         puts(ljust('#define '+vars.id[1],identlen));
         puts(exp);
         puts('  ');

         gettok;
      end
      else

      begin     
         

         gettok;

         pdatatype('',vars,'','',false);

         if tok[1] <> '=' then
         begin
            syntax('"=" expected');
            exit;
         end;
            
         gettok;   {consume the =}

         puts(' = ');
         parlev := 0;

         repeat
            if tok[1] = '[' then
            begin
               gettok;
               exp := psetof;
               gettok;
               puts(exp);
            end
            else
            
            if tok[1] = '(' then
            begin
               inc(parlev);
               puts('{');
               gettok;
            end
            else

            if tok[1] = ')' then
            begin
               dec(parlev);
               puts('}');
               gettok;
            end
            else

            if tok[1] = ',' then
            begin
               puttok;
               gettok;
            end
            else

            if (parlev > 0) and (tok[1] = ';') then
            begin
               puts(',');
               gettok;
            end
            else

            if tok[1] <> ';' then
            begin
               exp := pexpr;
               if tok[1] = ':' then
                  gettok   {discard 'member-identifier :'}
               else
                  puts(exp);
            end;

         until ((parlev = 0) and (tok[1] = ';')) or recovery;

         puttok;
         gettok;
      end;
   end;
end;
procedure ptype;

var
   vars: paramlist;

begin

   gettok;

   while (toktype <> keyword) do
   begin
      vars.n := 1;
      vars.id[1] := usetok;

      if tok = '=' then
         gettok
      else
      begin
         syntax('"=" expected');
         exit;
      end;
      
      nospace := false;
      pdatatype('typedef ',vars,'','',true);
   end;

end;
procedure pvar;
var
   vars:  paramlist;
   sto:   string20;
begin

   if in_interface and (withlevel = 0) then
      sto := 'extern '
   else
      sto := '';

   vars.n := 0;
   gettok;

   while (toktype <> keyword) and (tok[1] <> '}') and (tok[1] <> ')') do
   begin
      nospace := true;

      repeat
         if tok[1] = ',' then
            gettok;

         inc(vars.n);
         if vars.n > maxparam then
            fatal('Too many identifiers (pvar)');
         vars.id[vars.n] := ltok;
         gettok;
      until tok[1] <> ',';

      if tok[1] <> ':' then       
      begin
         syntax('":" expected');
         exit;
      end;
         
      gettok;
      nospace := false;
      pdatatype(sto,vars,'','',true);
      vars.n := 0;
   end;
end;
