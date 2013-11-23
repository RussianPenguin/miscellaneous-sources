function pterm: string; forward;

function iscall(var lv: string): boolean;
begin
   iscall := lv[length(lv)] = ')';
end;


procedure make_pointer(var expr: string);
var
   sym:  symptr;
begin
   
   case(expr[1]) of
      '*':
      begin
         delete(expr,1,1);
         exit;
      end;
      
      'a'..'z','A'..'Z','_':
      begin 
         sym := locatesym(expr);
         if (sym <> nil) and ((sym^.symtype = s_string) or
                              (sym^.suptype = ss_array)) then
         begin

         end
         else
         
         if expr[length(expr)-1] = '(' then    {remove () from function calls}
            dec(expr[0],2)
            
         else
            expr := '&' + expr;
      end;
      
   end;

end;


function isnumber(var lv: string): boolean;
var
   i: integer;
begin
   for i := 1 to length(lv) do
      case lv[i] of
         '0'..'9','.': ;
         else
            isnumber := false;
            exit;
      end;
   isnumber := true;
end;


procedure subtract_base(var expr: string; base: integer);
begin
   if base <> 0 then
      if isnumber(expr) then
         expr := itoa(atoi(expr) - base)
      else
      if base > 0 then
         expr := expr + '-' + itoa(base)
      else
         expr := expr + '+' + itoa(-base);
end;


function exprtype: char;
var
   xt:      char;

begin
   case cexprtype of
      s_char:    xt := 'c';
      s_file:    xt := '@';
      s_double:  xt := 'f';
      s_string:  xt := 's';
      s_bool:    xt := 'b';
      s_int:     xt := 'd';
      s_long:    xt := 'D'; { calling routine should convert to "ld" }
      else       xt := '?';
   end;

   exprtype := xt;
end;


function strtype(ty: char): boolean;
begin
   case ty of
      's','c':  strtype := true;
      else      strtype := false;
   end;
end;



function psetof:  string;
var
   ex: string;

begin
   ex := 'setof(';
   if tok[1] <> ']' then
      ex := ex + pterm;

   while (tok = '..') or (tok[1] = ',') do
   begin
      if tok = '..' then       
         ex := ex + ',__,'
      else
         ex := ex + ',';

      gettok;
      ex := ex + pterm;
   end;

   if ex[length(ex)] <> '(' then
      ex := ex + ',';
   ex := ex + '_E)';
   psetof := ex;
end;


function pterm:   string;
var
   ex: string;
   builtin: boolean;

begin
   
   if (toktype = identifier) and (cursym <> nil) then
      builtin := cursym^.suptype = ss_builtin
   else
      builtin := false;

   if builtin and (tok = 'POS') then
   begin
   
      gettok;
      if tok[1] <> '(' then
         syntax('"(" expected (pterm.pos)');
      
      gettok;
      ex := pexpr;
      if exprtype{(ex)} = 'c' then
         ex := 'cpos(' + ex
      else
         ex := 'spos(' + ex;

      gettok;  
      ex := ex + ',' + pexpr;
      gettok;  
      pterm := ex + ')';
      cexprtype := s_int;
   end
   else
   if builtin and (tok = 'CHR') then
   begin
   
      gettok; 
      if tok[1] <> '(' then
         syntax('"(" expected (pterm.chr)');
      
      gettok; 
      ex := pexpr;
      gettok; 

      if isnumber(ex) then
         ex := numlit(atoi(ex))
      else
         ex := 'chr('+ex+')';

      pterm := ex;
      cexprtype := s_char;
   end
   else
   
   if builtin and (tok = 'NOT') then
   begin
   
      gettok;
      pterm := '!' + pterm;
      cexprtype := s_bool;
   end
   else

   if (tok[1] = '?') or (tok[1] = '~') or (tok[1] = '\') then
   begin

      gettok;
      pterm := '!' + pterm; 
   end
   else

   if tok = '-' then
   begin

      gettok;
      pterm := '-' + pterm;
   end
   else
   if tok[1] = '@' then
   begin

      gettok; 
      ex := plvalue;
      make_pointer(ex);
      pterm := ex;
   end
   else
   if toktype = number then
   begin
      
      pterm := tok;
      gettok;
      cexprtype := s_int;
   end
   else
   if toktype = strng then
   begin
      
      pterm := tok;
      gettok;
      cexprtype := s_string;
   end
   else

   if toktype = chars then
   begin
      
      pterm := tok;
      gettok;
      cexprtype := s_char;
   end
   else

   if tok[1] = '(' then
   begin
      
      gettok;
      pterm := '(' + pexpr + ')';
      gettok;
   end
   else

   if tok[1] = '[' then
   begin
      
      gettok;
      pterm := psetof;
      gettok;
      cexprtype := s_struct;
   end

   else
      pterm := plvalue;
end;


function pexpr: string;
   
var
   ex:       string;
   ty:       char;
   ex2:      string;
   ty2:      char;

   procedure relop(newop: string40);
   begin
      
      gettok;   

      ex2 := pterm;
      ty2 := exprtype;
      if ty = 's' then
      begin
         if ty2 = 's' then
            ex := 'strcmp(' + ex + ',' + ex2 + ') ' + newop + ' 0'
         else
         if ex2[1] = '''' then
            ex := 'strcmp(' + ex + ',"' +
                     copy(ex2,2,length(ex2)-2) + '") ' + newop + ' 0'
         else
            ex := 'strcmp(' + ex + ',ctos(' + ex2 + ')) ' + newop + ' 0'
      end
      else

      if ty = 'c' then
      begin
         if ty2 = 's' then
            ex := 'strcmp(ctos(' + ex + '),' + ex2 + ') ' + newop + ' 0'
         else
            ex := ex + ' ' + newop + ' ' + ex2
      end

      else
         ex := ex + ' ' + newop + ' ' + ex2;

      cexprtype := s_bool;
   end;


   procedure addop;

      procedure add_scat;
      var
         p: integer;

      begin
         p := 7;  
         while (ex[p] <> '"') or
               ((ex[p] = '"') and (ex[p-1] = '\') and (ex[p-2] <> '\')) do
            p := succ(p);
         p := succ(p);
         if (ex2[1] = '''') or (ex2[1] = '"') then
            ex := copy(ex,1,p-2) + 
                  copy(ex2,2,length(ex2)-2) +
                  copy(ex,p-1,length(ex)-p+2)

         else
            ex := copy(ex,1,p-2) + '%' + ty2 +
                  copy(ex,p-1,length(ex)-p+1) + ',' + ex2 + ')';
      end;

   begin

      gettok;       

      ex2 := pterm; 
      ty2 := exprtype;
      
      if (ex[5] = '(') and (copy(ex,1,4) = 'scat') then
         add_scat
      else
      
      if strtype(ty) or strtype(ty2) then
      begin
         if (ex[1] = '''') or (ex[1] = '"') then
            ex := 'scat("' + copy(ex,2,length(ex)-2) + '")'
         else
            ex := 'scat("%' + ty + '",' + ex + ')';
         add_scat;
      end
      else
         ex := ex + ' + ' + ex2;

   end;

   procedure mulop(newop: string40);
   begin

      gettok;   

      ex2 := pterm; 
      ex := ex + ' ' + newop + ' ' + ex2;
   end;

   procedure andop(newop: char);
   begin

      gettok; 

      ex2 := pterm;  
      ty2 := exprtype;
      if (ty = 'b') or (ty2 = 'b') then
      begin
         ex := ex + ' ' + newop + newop + ' ' + ex2;
         cexprtype := s_bool;
      end
      else 
         ex := ex + ' ' + newop + ' ' + ex2;
   end;


begin

   ex := pterm;
   ty := exprtype;

   while true do
   begin
           if tok    = '>='  then relop(tok)
      else if tok    = '<='  then relop(tok)
      else if tok    = '<>'  then relop('!=')
      else if tok[1] = '>'   then relop(tok)
      else if tok[1] = '<'   then relop(tok)
      else if tok[1] = '='   then relop('==')
      else if tok[1] = '+'   then addop
      else if tok[1] = '-'   then mulop(tok)
      else if tok[1] = '*'   then mulop(tok)
      else if tok[1] = '/'   then mulop(tok)
      else if tok[1] = '&'   then mulop(tok)
      else if tok[1] = '!'   then mulop('|')
      else if tok[1] = '|'   then mulop('|')
      else if tok    = 'DIV' then mulop('/')
      else if tok    = 'MOD' then mulop('%')
      else if tok    = 'SHR' then mulop('>>')
      else if tok    = 'SHL' then mulop('<<')
      else if tok    = 'XOR' then mulop('^')
      else if tok    = 'AND' then andop('&')
      else if tok    = 'OR'  then andop('|')
      else

      if tok = 'IN'  then
      begin
         gettok;
         ex := 'inset('+ex+',' + pterm + ')';
      end
      else
      begin
         pexpr := ex;
         exit;
      end;
   end;

end;


function plvalue: string;
var
   lv:       string;
   expr:     string;
   funcid:   string40;
   pref:     string40;
   idok:     boolean;
   sym:      symptr;
   func:     symptr;
   btype:    symtypes;
   cstype:   supertypes;
   bstype:   supertypes;
   pvars:    integer;
   cbase:    integer;
   bbase:    integer;
      
begin

   plvalue := 'lvalue';


   if toktype <> identifier then
   begin
      syntax('Identifier expected (plvalue)');
      exit;
   end;


   idok := false;
   pref := '';
   lv := ltok;
   funcid := tok;
   bstype := ss_scalar;
   bbase := 0;
   cbase := 0;

   sym := cursym;
   if sym <> nil then
   begin
      cstype := sym^.suptype;
      cbase := sym^.base;
      cexprtype := sym^.symtype;
      lv := sym^.repid;


      if sym^.parcount = -2 then
         pref := '*';
      
      if (sym^.parcount < 0) and (sym^.pvar > 0) and (withlevel > 0) then
      begin
         pref := 'with'+itoa(withlevel)+'->';
      end;
      
   end;
   gettok;

   repeat
      if toktype = identifier then
      begin

         if cursym <> nil then        
         begin
            sym := cursym;
            cstype := sym^.suptype;
            cbase := sym^.base;
            cexprtype := sym^.symtype;
            ltok := sym^.repid;       
         end;
         
      end;
      if idok and (toktype = identifier) then
      begin

         lv := lv + ltok;
         gettok;
         idok := false;
      end
      else
      if tok = '^' then
      begin
         pref := '*' + pref;
         gettok;
      end
      else
      if tok = '^[' then
      begin

         lv := lv + '[';
         gettok;

         while tok <> ']' do
         begin
            lv := lv + pexpr;
            if tok = ',' then
            begin
               lv := lv + '][';
               gettok;
            end;
         end;

         lv := lv + ']';
         gettok;
      end
      else
      if tok = '^.' then
      begin

         lv := lv + '->';
         gettok;
         idok := true;
      end
      else
      if tok = '.' then
      begin

         if pref = '*' then  
         begin
            pref := '';
            lv := lv + '->';
         end
         else
            lv := lv + '.';
         idok := true;
         gettok;
      end
      else


      if tok[1] = '[' then
      begin

         btype := cexprtype;
         bstype := cstype;
         bbase := cbase;

         if copy(pref,1,1) = '*' then
            pref := '';

         lv := lv + '[';
         gettok;

         repeat
            expr := pexpr;

            if tok[1] = ',' then
            begin
               lv := lv + expr + '][';
               gettok;
               bstype := ss_scalar;
            end;
         until tok[1] = ']';

         subtract_base(expr,bbase);
         lv := lv + expr + ']';

         if (btype = s_string) and (bstype <> ss_array) then
         begin
            btype := s_char;
            ltok := lv;
            if expr = '-1' then
               warning('Dynamic length reference');
         end;

         cexprtype := btype;
         cstype := ss_scalar;
         cbase := 0;
         gettok;
      end
      else

      if tok[1] = '(' then
      begin

         func := locatesym(funcid);
         pvars := 0;
         if func <> nil then
         begin
            pvars := func^.pvar; 
            cexprtype := func^.symtype;
         end;
            
         btype := cexprtype;
         lv := lv + '(';
         gettok;

         while tok[1] <> ')' do
         begin
            expr := pexpr;
            if (pvars and 1) = 1 then
               make_pointer(expr);

            lv := lv + expr;
            pvars := pvars shr 1;

            if (tok[1] = ',') or (tok = ':') then
            begin
               lv := lv + ',';
               gettok;
            end;
         end;

         lv := lv + ')';
         gettok;
         cexprtype := btype;
      end
      else
      begin
         if sym <> nil then
         begin
            if (not iscall(lv)) and (sym^.parcount >= 0) then
               lv := lv + '()';
         end;

         plvalue := pref + lv;
         exit;
      end;
   until recovery;
   plvalue := pref + lv;
end;