
function numlit(n: integer): anystring;
var
   lit: string[6];
   

   function digit(n: integer): char;

   begin
      n := n and 15;
      if n > 9 then n := n + 7;
      digit := chr( n + ord('0') );
   end;

begin
   lit := '''\?''';

   case n of
     $07:   lit[3] := 'a';
     $08:   lit[3] := 'b';
     $09:   lit[3] := 't';
     $0a:   lit[3] := 'n';
     $0b:   lit[3] := 'v';
     $0c:   lit[3] := 'f';
     $0d:   lit[3] := 'r';

     32..126,128..254:
            lit := ''''+chr(n)+'''';

     else   begin
               lit := '''\x??''';
               lit[4] := digit(n shr 4);
               lit[5] := digit(n);
            end;
   end;

   numlit := lit;
   toktype := chars;
end;

procedure getchar;
var
   stack: char;
begin
   if ofs(stack) < minstack then
      fatal('Out of stack space');

   while (srclevel > 0) and eof(srcfd[srclevel]) do
   begin
      if not linestart then putline;
      putln('/* p2c: end of '+srcfiles[srclevel]+' */');
      
      writeln(^M,srcfiles[srclevel],'(',srclines[srclevel],')');
      
      close(srcfd[srclevel]);
      freemem(inbuf[srclevel],inbufsiz);

      dec(srclevel);
   end;
    
   if eof(srcfd[srclevel]) then
      nextc := '.'
   else
      read(srcfd[srclevel], nextc);

   if nextc = ^J then
   begin
      inc(srclines[srclevel]);
      inc(srctotal);
   end;
end;

function usec: char;
var
   c: char;
begin
   c := nextc;
   getchar;
   usec := c;
end;

function newc(n: string40): string40;
var
   c: char;
begin
   c := nextc;
   getchar;
   newc := n;
end;

procedure concat_tokens;
var
   cur: string;
begin
   cur := ltok;
   ltok := nextc;
   toktype := unknown;
   scan_tok;
   ltok := copy(cur,1,length(cur)-1) + copy(ltok,2,255);
   ltok[1] := '"';
   ltok[length(ltok)] := '"';
   toktype := strng;
end;

procedure scan_ident;
begin

   toktype := unknown;
   ltok := '';

   repeat
      case nextc of
         'A'..'Z':
            begin
               ltok := ltok + chr(ord(nextc)+ord('a')-ord('A'));
			   getchar;
            end;
         'a'..'z', '0'..'9', '_','@':
            ltok := ltok + usec;
         else
            toktype := identifier;
      end;
   until toktype = identifier;
end;

procedure scan_preproc;
begin
   puts('#');

   repeat
      puts(nextc);
      getchar;
   until nextc = ^M;

   getchar;
   putline;
   toktype := unknown;
end;

procedure scan_number;
var
   hasdot:  boolean;
   charlit:   boolean;
   islong:  boolean;

begin
   hasdot := false;
   islong := false;
   charlit := false;
   toktype := number;
   if nextc = '#' then
   begin
      ltok := '';
      charlit := true;
   end;

   getchar;
   if charlit and (nextc >= 'a') and (nextc <= 'z') then
      scan_preproc
   else

   repeat
      case nextc of
         '$','0'..'9','a'..'f','A'..'F':
            ltok := ltok + usec;

         '.':
            if hasdot then
            begin
               if ltok[length(ltok)] = '.' then
               begin
                  ltok[0] := pred(ltok[0]);  {remove trailing ., part of ..}
                  if charlit then
                     ltok := numlit(atoi(ltok));
                  extradot := true;
               end;
               exit;
            end
            else

            begin
               hasdot := true;
               ltok := ltok + usec;
            end;

         else
            begin
               if charlit then
               begin
                  ltok := numlit(atoi(ltok));
                  if (nextc = '''') or (nextc = '^') or (nextc = '#') then
                     concat_tokens;
                  exit;
               end;
               
               if ltok[1] = '$' then
                  ltok := '0x' + copy(ltok,2,99);
               if islong then
                  ltok := ltok + 'L';
               exit;
            end;
      end;

   until true=false;
end;

procedure scan_hat;
var
   c: char;

begin
   getchar;

   if ((nextc = '.') or (nextc = '[')) and 
      ((ptoktype = identifier) or (ptok = ']')) then
   begin
      ltok := '^' + usec;     {^. or ^[}
      exit;
   end;

   case nextc of
      '@','['..'`':
         ltok := usec;
         
      'A'..'Z','a'..'z':
         begin
            ltok := nextc;
            scan_ident;
         end;
       else
         exit;
   end;

   if length(ltok) = 1 then      {^c = control char}
   begin
      ltok := numlit( ord(upcase(ltok[1])) - ord('@') );
      if (nextc = '''') or (nextc = '^') or (nextc = '#') then
         concat_tokens;
   end
   else
      ltok := '^' + ltok;        {^ident = pointer to ident}

end;

procedure scan_dot;
begin
   getchar;

   if (nextc = '.') or extradot then
   begin
      ltok := '..';
      extradot := false;
   end;

   if nextc = '.' then
      getchar;
end;

procedure scan_string;
begin
   toktype := unknown;
   ltok := '"';
   getchar;

   repeat
      case nextc of
         ^J,^M:
            begin
               error_message('Closing quote expected (scan_string)');
               toktype := strng;
            end;
      
         '''':
            begin
               getchar;     {consume the quote}
      
               if nextc = '''' then
                  ltok := ltok + usec
                  {double quotes are coded as a single quote}
               else
      
               begin        {end of string}
                  ltok := ltok + '"';
                  toktype := strng;
               end;
            end;
      
         '"':  ltok := ltok + newc('\"');
         '\':  ltok := ltok + newc('\\');

         else  ltok := ltok + usec;
      end;

   until toktype = strng;

   if length(ltok) = 3 then
   begin
      ltok[1] := '''';
      ltok[3] := '''';
      toktype := chars;
   end;

   if ltok = '"\""' then
   begin
      ltok := '''"''';
      toktype := chars;
   end
   else

   if (ltok = '"''"') or (ltok = '''''''') then
      ltok := '''\'''''
   else

   if (ltok = '"\\"') then
   begin
      ltok := '''\\''';
      toktype := chars;
   end;

   if (nextc = '^') or (nextc = '#') then
      concat_tokens;
end;

procedure scan_pragma(var isinclude: anystring);
var
   code: anystring;
   prag: anystring;
   arg:  anystring;

   procedure scanword(var dest: anystring);
   begin
      dest := '       ';
      dest := '';
      while true do
      case nextc of
         ' ', '*', '}', ',':
            exit;
         else
         begin
            dest := dest + upcase(nextc);
            getchar;
         end;
      end;
   end;
   
begin
   isinclude := '';
   
   repeat
      if nextc = ',' then
         newline;

      getchar; 
      scanword(code);
      
      if nextc = ' ' then
      begin
         getchar;
         scanword(arg);
      end
      else
         arg := '';
      
      if code[2] = '+' then
         arg := 'ON'
      else
      if code[2] = '-' then
         arg := 'OFF';

      prag := '/* '+code[1]+'(' + arg + ')' + ' */';
      
      case code[1] of

         'D':  if code[2] = 'E' then
                  prag := '#define '+arg;
               
         'E':  if code[2] = 'N' then
                  prag := '#endif'
               else
               if code[2] = 'L' then
                  prag := '#else';
               
         'I':  if code[2] = ' ' then
               begin
                  if pos('.',arg) = 0 then
                     arg := arg + '.PAS';
                  prag := '#include "' + arg + '"   ';
                       
                  prag := '';
                  isinclude := arg;
               end
               else
               
               if code[2] = 'F' then
               begin
                  if code[3] = 'N' then
                     prag := '#ifndef '+arg
                  else
                     prag := '#ifdef '+arg;
               end;

         'U':  if code[2] = 'N' then
                  prag := '#undef '+arg;
               
      end;

      puts(prag);
      puts('   ');

      while nextc = ' ' do
         getchar;

   until nextc <> ',';

end;

procedure open_include(name: anystring);
begin
   if length(name) = 0 then exit;
   
   inc(srctotal);
   inc(objtotal);

   inc(srclevel);
   if srclevel > maxincl then
      fatal('Includes nested too deeply');
      
   srcfiles[srclevel] := name;
   srclines[srclevel] := 1;
   
   assign(srcfd[srclevel],name);
   {$I-} reset(srcfd[srclevel]); {$I+}
   if ioresult <> 0 then
   begin
      dec(srclevel);
      ltok := name;
      warning('Missing include file');
   end
   else

   begin
      if not linestart then putline;
      if maxavail-300 <= inbufsiz then
      begin
         ltok := name;
         fatal('Out of memory');
      end;
         
      getmem(inbuf[srclevel],inbufsiz);
      SetTextBuf(srcfd[srclevel],inbuf[srclevel]^,inbufsiz);
   end;
   
   write(^M,'':40,^M);
   writeln;
end;

procedure scan_curlycomment;
var
   isinclude: anystring;
   
begin
   toktype := comment;
   getchar;
   isinclude := '';
   if nextc = '$' then
      scan_pragma(isinclude);

   if nextc = '}' then
   begin
      getchar;
      open_include(isinclude);
      exit;
   end;

   puts('  /* ');

   while nextc <> '}' do
   begin
      puts(nextc);
      getchar;
   end;

   puts(' */ ');
   if nospace then newline;
   

   getchar; 
   open_include(isinclude);
end;

procedure scan_parencomment;
var
   isinclude: anystring;
   
begin
   toktype := comment;
   getchar;   {consume the *}

   isinclude := '';
   if nextc = '$' then
      scan_pragma(isinclude);

   puts('/*');

   repeat
      puts(nextc);

      if nextc = '*' then
      begin
         getchar;

         if nextc = ')' then
         begin
            getchar;
            puts('/ ');
            if nospace then putline;
            open_include(isinclude);
            exit;
         end;
      end
      else
         getchar;

   until true=false;
end;

procedure scan_blanks;
var
   indent:        anystring;
   valid:         boolean;

begin
   linestart := false;
   indent := '';
   valid := false;

   repeat

      case nextc of
         ^J,^M:  begin
                    if (nospace = false) and (nextc = ^J) then 
                       putline;
                    
                    indent := '';
                    linestart := true;
                    getchar;
                 end;

         ' ',^I,^@,^L:
                 indent := indent + usec;

         '#':    if linestart then
                 begin
                    puts(indent);   
                    indent := '';   

                    repeat
                       puts(nextc);
                       getchar;
                    until nextc = ^M;

                    getchar;
                    putline;
                 end
                 else
                    valid := true;

         else
                 valid := true;
      end;

   until valid;

   if linestart then
   begin
      spaces := indent;
      if nospace=false then
         puts(spaces);

      linestart := true;
   end;
end;

procedure scan_tok;
begin
   scan_blanks;

   toktype := unknown;
   ltok := nextc;

   case nextc of
      'a'..'z', 
      '_', 'A'..'Z': scan_ident;

      '$':           scan_number;
      '0'..'9':      scan_number;

      '''':          scan_string;

      '^':           scan_hat;

      '#':           begin
                        scan_number;
                        if toktype = unknown then
                           scan_tok; 
                     end;


      '<':           begin
                        getchar;
                        if (nextc = '>') or (nextc = '=') then
                           ltok := '<' + usec;
                     end;

      '>':           begin
                        getchar;
                        if nextc = '=' then
                           ltok := '>' + usec;
                     end;

      ':':           begin
                        getchar;
                        if nextc = '=' then
                           ltok := ':' + usec;
                     end;

      '.':           scan_dot;

      '{':           scan_curlycomment;

      '(':           begin
                        getchar;
                        if nextc = '*' then
                           scan_parencomment;
                     end;

      else           getchar; 
   end;
end;
procedure gettok;
var
   i:             integer;

begin
   ptoktype := toktype;
   ptok := tok;
   cursym := nil;
   
   repeat
      scan_tok;
   until toktype <> comment;
   tok := ltok;

   if toktype = identifier then
   begin
      stoupper(tok);

      if tok = 'BEGIN' then
      begin
         tok := '{';
         ltok := tok;
         toktype := keyword;
      end
      else

      if tok = 'END' then
      begin
         tok := '}';
         ltok := tok;
         toktype := keyword;
      end;
      i := 0;
      repeat
         inc(i);
         if tok[1] = keywords[i][1] then              {hack for speed}
         if length(tok) = length(keywords[i]) then
         if tok = keywords[i] then
            toktype := keyword;
      until (i = nkeywords) or (toktype = keyword);
      cursym := locatesym(tok);
   end;
end;

function usetok: string80;
var
   tv: string80;
begin
   tv := ltok;
   gettok;
   usetok := tv;
end;
