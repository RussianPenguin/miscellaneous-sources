procedure abortcheck;
var
   c:  char;
begin
   if keypressed then
   begin
      c := readkey;
      if c = #27 then
         fatal('Aborted by <escape> key');
   end;
end;

procedure puttok;
begin
   write(ofd[unitlevel],ltok,' ');
   linestart := false;
end;

procedure putline;
begin
   writeln(ofd[unitlevel]);
   inc(objtotal);
   linestart := true;
end;

procedure closing_statistics;
var
   secs: real;
   rate: real;

begin
   if in_interface then
      pimplementation;
   purgetable(locals,nil);
   while unitlevel > 0 do
      exit_procdef;
   putline;
   putline;
   purgetable(globals,nil);
   close(ofd[unitlevel]);
end;

procedure error_message (message:       string);
   procedure report(var fd: text);
   begin
      writeln(fd,'/* Compiler: ',srcfiles[srclevel],'(',srclines[srclevel],'): ', 
           message,', tok=', ltok,' */');
   end;

begin
   write(^M);
   report(output);

   putline;
   report(ofd[unitlevel]);
   write(ofd[unitlevel],spaces);
   inc(objtotal);
end;

procedure comment_statement;
begin
   puts(' /* ');

   repeat
      puttok;
      gettok;
   until (tok[1] = ';');

   puts(' */ ');
end;

procedure warning (message:       string);
begin
  error_message('Warning: '+message);
end;

procedure syntax (message:       string);
begin
   if (not recovery)then
      error_message('Error: '+message);
   gettok;
   recovery := true;
end;

procedure fatal (message:       string);
begin
   error_message('Fatal: '+message);
   closing_statistics;
   halt(88);
end;

procedure puts(s: string);
begin
   write(ofd[unitlevel],s);
   if s[1] = ^J then
   begin
      inc(objtotal);
      linestart := true;
   end
   else
      linestart := false;
end;

procedure putln(s: string);
begin
   puts(s);
   putline;
end;

procedure newline;
begin
   putline;
   write(ofd[unitlevel],spaces);
end;



