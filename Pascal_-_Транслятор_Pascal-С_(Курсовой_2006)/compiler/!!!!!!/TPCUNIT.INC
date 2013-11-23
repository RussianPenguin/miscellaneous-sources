procedure psection;
begin
   if (tok = 'PROCEDURE') or (tok = 'FUNCTION') then
      punit
   else

   if tok = 'INTERFACE' then
      pinterface
   else
   
   if tok = 'IMPLEMENTATION' then
      pimplementation
   else
   
   if tok = 'USES' then
   begin
      puses;
      if tok[1] = ';' then 
         gettok;
   end
   else
   
   if tok = 'UNIT' then
      comment_statement
   else
   
   if tok = 'CONST' then
      pconst
   else

   if tok = 'TYPE' then
      ptype
   else

   if tok = 'VAR' then
      pvar
   else

   if tok = 'LABEL' then
      plabel
   else

   if tok[1] = '{' then
      pblock
   else

   if (tok[1] = '.') or (tok[1] = '}') then
   begin
      tok := '.';
      exit;
   end
   else
      syntax('Section header expected (psection)');
end;

const
   extern = true;
   
procedure punitheader(is_external: boolean);
var
   proc:    string40;
   proclit: string40;
   vars:    paramlist;
   types:   paramlist;
   bases:   array [1..maxparam] of integer;
   i:       integer;
   ii:      integer;
   rtype:   string40;
   varval:  integer;
   varon:   boolean;
   locvar:  integer;
   iptr:    integer;

begin
   gettok;                 {skip unit type}
   proclit := ltok;

   if (unitlevel > 1) and (not in_interface) then
   begin
      if cursym = nil then
         proc := proclit
      else
         proc := procnum + '_' + proclit;
         
      warning('Nested function');
      
      writeln(ofd[unitlevel-1],^M^J'   /* Nested function: ',proc,' */ ');
      inc(objtotal,2);
   end
   else
      proc := proclit;

   gettok;     

   vars.n := 0;
   varval := 0;   
   varon  := false;

   if tok[1] = '(' then
   begin
      gettok;

      while (tok[1] <> ')') and not recovery do
      begin

         ii := vars.n + 1;
         repeat
            if tok[1] = ',' then
               gettok;

            if tok = 'VAR' then
            begin
               gettok;
               varon := true;
            end;

            inc(vars.n);
            if vars.n > maxparam then
               fatal('Too many params (punitheader)');
            vars.id[vars.n] := ltok;
            gettok;

         until tok[1] <> ',';

         if tok[1] = ':' then       
         begin
            gettok; 

            rtype := psimpletype;
         end
         else

         begin  
            rtype := 'void';
            curtype := s_void;
            curbase := 0;
            cursuptype := ss_scalar;
         end;

         iptr := 0;
         if rtype[1] = '^' then
            rtype[1] := '*';

         if varon and (curtype <> s_string) and (cursuptype <> ss_array) then
            iptr := 1 shl (ii - 1);

         if curtype = s_string then
            rtype := 'char *'
         else
         if cursuptype = ss_array then
            rtype := typename[curtype] + ' *';

         for i := ii to vars.n do   
         begin
            types.id[i] := rtype;
            types.stype[i] := curtype;
            types.sstype[i] := cursuptype;
            bases[i] := curbase;
            varval := varval or iptr;
            iptr := iptr shl 1;
         end;

         if tok[1] = ';' then
         begin
            gettok;
            varon := false;
         end;

      end;   {) seen}

      gettok;   {consume the )}
   end;

   if tok[1] = ':' then
   begin
      gettok;            {consume the :}
      rtype := psimpletype;

      if curtype = s_string then
         rtype := 'char *'
      else
      if cursuptype = ss_array then
         rtype := typename[curtype] + ' *';
   end
   else

   begin
      rtype := 'void';
      curtype := s_void;
   end;

   putline;

   if is_external then
   begin
      putln(ljust('extern '+rtype,identlen)+proc+'();');
      addsym(globals,proc,curtype,ss_func,0,varval,0,9,false);
      exit;
   end;


   if tok = 'AS' then
   begin
      gettok;
      proc := usetok;
   end;

   if in_interface then
      rtype := 'extern '+rtype;
   puts(ljust(rtype,identlen)+proc+'(');

   if vars.n = 0 then
      puts('void');

   locvar := varval;
   for i := 1 to vars.n do
   begin
      iptr := -1;

      if (locvar and 1) = 1 then
      begin
         iptr := -2;
         types.id[i] := types.id[i] + ' *';
      end;

      puts(ljust(types.id[i],identlen)+vars.id[i]);
      addsym(locals,vars.id[i],types.stype[i],ss_scalar,iptr,0,0,bases[i],true);
      locvar := locvar shr 1;

      if i < vars.n then
      begin
         putln(','); 
         puts(ljust('',identlen+length(proc)+1));
      end;
   end;

   puts(')');
   nospace := false;

   addsym(globals,proclit,curtype,ss_func,vars.n,varval,0,0,false);
   cursym^.repid := proc;
end;

procedure punitbody;
begin
   gettok;

   if tok = 'FORWARD' then
   begin
      puts(';');
      gettok;
   end
   else

   begin
      puts('{ ');

      repeat
         if tok[1] = ';' then
         begin
            puttok;
            gettok;
         end;

         if tok[1] <> '{' then
            psection;
      until tok[1] = '{';

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

      puttok;
   end;
end;


(********************************************************************)
procedure enter_procdef;

var
   nam:  anystring;
begin
   inc(procnum[2]);
   if procnum[2] > 'Z' then
   begin
      inc(procnum[1]);
      procnum[2] := 'A';
   end;

   inc(unitlevel);
   if unitlevel > maxnest then
      fatal('Functions nested too deeply');

   str(unitlevel,nam);
   nam := nestfile + nam;

   assign(ofd[unitlevel],nam);
   {$i-} rewrite(ofd[unitlevel]); {$i+}

   if ioresult <> 0 then
   begin
      dec(unitlevel);
      ltok := nam;
      fatal('Can''t create tempfile');
   end;

   if maxavail-300 <= inbufsiz then
   begin
      ltok := nam;
      fatal('Out of memory');
   end;

   getmem(outbuf[unitlevel],inbufsiz);
   SetTextBuf(ofd[unitlevel],outbuf[unitlevel]^,inbufsiz);
end;


(********************************************************************)
procedure exit_procdef;

var
   line:  string;

begin
   if unitlevel < 1 then 
      exit;
   
   close(ofd[unitlevel]);
   reset(ofd[unitlevel]);
   SetTextBuf(ofd[unitlevel],outbuf[unitlevel]^,inbufsiz);

   while not eof(ofd[unitlevel]) do
   begin
      readln(ofd[unitlevel],line);
      writeln(ofd[0],line);
   end;

   close(ofd[unitlevel]);
   erase(ofd[unitlevel]);
   freemem(outbuf[unitlevel],inbufsiz);
   dec(unitlevel);
end;

procedure punit;
var
   top: symptr;
begin
   nospace := true;
   top := locals;

   if in_interface then
   begin
      nospace := false;
      punitheader(not extern);

      puts(';');
      if tok[1] = ';' then
         gettok;
      purgetable(locals,top);
   end
   else
   
   begin
      enter_procdef;

      punitheader(not extern);
      punitbody;
      gettok;
      if tok[1] = ';' then
         gettok;
      purgetable(locals,top);
      exit_procdef;
   end;
end;

procedure pprogram;
begin
   putline;
   putln('#include "types.h"');
   
   getchar;
   gettok;

   if (tok = 'PROGRAM') or (tok = 'UNIT') then
   begin
      comment_statement;
      gettok;
   end;

   repeat
      if tok[1] = ';' then
      begin
         puttok;
         gettok;
      end;

      if (tok[1] <> '{') then
         psection;
   until (tok[1] = '{') or (tok[1] = '.') or recovery;

   if tok[1] = '{' then
   begin
      putline;
      putln('void main(int argc,  char **argv)');
      
      puttok;
      gettok;
   
      while (tok[1] <> '}') and (tok[1] <> '.') do
      begin
         pstatement;
   
         if tok[1] = ';' then
         begin
            puttok;
            gettok; 
         end;
      end;

      putln('}');
   end;
   
   putline;
end;
