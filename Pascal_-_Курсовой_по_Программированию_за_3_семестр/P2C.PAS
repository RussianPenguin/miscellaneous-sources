
{$T+} 
{$R-} 
{$B-} 
{$S-} 
{$I+} 
{$N-} 
{$V-} 
{$M 65500,16384,655360}
uses crt;

const
   minstack =     4000;   
   outbufsiz =    10000;  
   inbufsiz =     2000;   
   maxparam =     16;     
   maxnest =      10;     
   maxincl =      2;      
   statrate =     5;      
   ticks_per_second = 18.2;
   identlen :integer = 13;
   

const
   nestfile =     'p$';   

type
   anystring =    string [127];
   string255 =    string [255];
   string80  =    string [80];
   string64  =    string [64];
   string40  =    string [40];
   string20  =    string [20];
   string10  =    string [10];

type
   toktypes =     (number,      identifier,
                   strng,       keyword,
                   chars,       comment,
                   unknown);

   symtypes =     (s_int,       s_long,
                   s_double,    s_string,
                   s_char,      s_struct,
                   s_file,      s_bool,
                   s_void                );

   supertypes =   (ss_scalar,   ss_const,
                   ss_func,     ss_struct,
                   ss_array,    ss_pointer,
                   ss_builtin,  ss_none  );

   symptr =      ^symrec;
   symrec =       record
                     symtype:  symtypes;      
                     suptype:  supertypes;    
                     id:       string40;      
                     repid:    string40;      

                     parcount: integer;       
                     pvar:     word;          
                     base:     integer;       
                     limit:    word;          

                     next:     symptr;        
                  end;

   paramlist =    record
                     n:      integer;
                     id:     array [1..maxparam] of string80;
                     stype:  array [1..maxparam] of symtypes;
                     sstype: array [1..maxparam] of supertypes;
                  end;

const
   typename:  array[symtypes] of string40 =
                  ('int',       'long',
                   'double',    'strptr',
                   'char',      'struct',
                   'file',      'boolean',
                   'void' );

   supertypename:  array[supertypes] of string40 =
                  ('scalar',    'constant',
                   'function',  'structure',
                   'array',     'pointer',
                   'builtin',   'none' );

   nkeywords = 14;
   keywords:  array[1..nkeywords] of string40 = (
      'PROGRAM',   'PROCEDURE', 'FUNCTION',
      'VAR',       'CONST',     'TYPE',
      'LABEL',     'OVERLAY',   'FORWARD',
      'MODULE',    'EXTERNAL',  'CASE',
      'INTERFACE', 'IMPLEMENTATION');

type
   byteptr =      ^byte;
   
var
   inbuf:         array [0..maxincl] of byteptr;
   srcfd:         array [0..maxincl] of text;
   srclines:      array [0..maxincl] of integer;
   srcfiles:      array [0..maxincl] of string64;
   
   outbuf:        array [0..maxnest] of byteptr;
   ofd:           array [0..maxnest] of text;
   
   inname:        string64;   
   outname:       string64;   
   unitname:      string64;   
   symdir:        string64;   
   ltok:          string80;   
   tok:           string80;   
   ptok:          string80;   
   spaces:        anystring;  
   decl_prefix:   anystring;  

const
   nextc:         char        = ' ';
   toktype:       toktypes    = unknown;
   ptoktype:      toktypes    = unknown;
   linestart:     boolean     = true;
   extradot:      boolean     = false;
   nospace:       boolean     = false;

   cursym:        symptr      = nil;
   curtype:       symtypes    = s_void;
   cexprtype:     symtypes    = s_void;
   cursuptype:    supertypes  = ss_scalar;
   curlimit:      integer     = 0;
   curbase:       integer     = 0;
   curpars:       integer     = 0;

   withlevel:     integer     = 0;
   unitlevel:     integer     = 0;
   srclevel:      integer     = 0;
   srctotal:      integer     = 1;
   objtotal:      integer     = 0;
   
   procnum:       string[2]   = 'AA';
   recovery:      boolean     = false;

   in_interface:  boolean     = false;
   top_interface: symptr      = nil;

   globals:       symptr      = nil;
   locals:        symptr      = nil;


{$I ljust.inc}    
{$I atoi.inc}     
{$I itoa.inc}     
{$I ftoa.inc}     
{$I stoupper.inc} 

procedure fatal  (message:  string);      forward;
procedure warning  (message:  string);    forward;
procedure scan_tok;                       forward;
procedure gettok;                         forward;
procedure puttok;                         forward;
procedure putline;                        forward;
procedure puts(s: string);                forward;
procedure putln(s: string);               forward;
function  plvalue: string;                forward;
function  pexpr:   string;                forward;
procedure exit_procdef;                   forward;
procedure pblock;                         forward;
procedure pstatement;                     forward;
procedure pimplementation;                forward;
procedure punit;                          forward;
procedure pvar;                           forward;
procedure pident;                         forward;


{$I sym.inc}
{$I misc.inc}
{$I scan.inc}
{$I expr.inc}
{$I stmt.inc}
{$I decl.inc}
{$I unit.inc}

procedure initialize;

   procedure enter(name: anystring; etype: symtypes; elimit: integer);
   begin
      newsym(name, etype, ss_scalar, -1, 0, elimit, 0);
   end;

begin
   srclines[srclevel] := 1;
   srcfiles[srclevel] := inname;
   assign(srcfd[srclevel],inname);
   {$I-} reset(srcfd[srclevel]); {$I+}
   if ioresult <> 0 then
   begin
      writeln('Can''t open input file: ',inname);
      halt(88);
   end;

   getmem(inbuf[srclevel],inbufsiz);
   SetTextBuf(srcfd[srclevel],inbuf[srclevel]^,inbufsiz);

   assign(ofd[unitlevel],outname);
{$I-}
   rewrite(ofd[unitlevel]);
{$I+}
   if ioresult <> 0 then
   begin
      writeln('Can''t open output file: ',outname);
      halt(88);
   end;

   getmem(outbuf[unitlevel],outbufsiz);
   SetTextBuf(ofd[unitlevel],outbuf[unitlevel]^,outbufsiz);
         
   enter('boolean',    s_bool,1);
   enter('integer',    s_int,maxint);
   enter('word',       s_int,0);    
   enter('longint',    s_long,0);
   enter('real',       s_double,0);
   enter('char',       s_char,255);
   enter('byte',       s_int,255);
   enter('file',       s_file,0);
   enter('text',       s_file,0);
   enter('true',       s_bool,1);
   enter('false',      s_bool,1);
   newsym('string',    s_string, ss_scalar,    -1, 0, 0, 1);
   newsym('not',       s_int,    ss_builtin,    0, 0, 0, 0);

   newsym('chr',       s_char,   ss_builtin,    1, 0, 0, 0);
   newsym('pos',       s_int,    ss_builtin,    2, 0, 0, 0);
   newsym('str',       s_void,   ss_builtin,    2, 0, 0, 0);
   newsym('port',      s_int,    ss_builtin,    1, 0, 0, 0);
   newsym('portw',     s_int,    ss_builtin,    1, 0, 0, 0);
   newsym('mem',       s_int,    ss_builtin,    2, 0, 0, 0);
   newsym('memw',      s_int,    ss_builtin,    2, 0, 0, 0);
   newsym('exit',      s_void,   ss_builtin,    1, 0, 0, 0);
   
   load_unitfile('ALLSYS.UNS',globals);
   
   newsym('<predef>',  s_void,   ss_builtin,-1, 0, 0, 0);
end;


procedure process_option(par: anystring);
begin
  stoupper(par);

  if (par[1] = '-') or (par[1] = '/') then
    WriteLn('Unknow parametr - ',par)
  else
  
  if inname = '' then
    inname := par
  else
  
  if outname = '' then
    outname := par;
end;

procedure decode_options;
var
   i:        integer;
   options:  string;
   opt:      string;
      
begin
   inname := '';
   outname := '';
   unitname := '';
   symdir := '';
   ltok := '';
   tok := '';
   ptok := '';
   spaces := '';
   decl_prefix := '';

   options := '';
   for i := 1 to paramcount do
      options := options + ' ' + paramstr(i);         
   options := options + ' ';

   repeat
      i := pos(' ',options);
      opt := copy(options,1,i-1);
      options := copy(options,i+1,255);
      if length(opt) > 0 then
         process_option(opt);
   until length(options) = 0;

   if inname = '' then
      WriteLn('missing input name');

   if outname = '' then
   begin
      outname := inname;
      i := pos('.',outname);
      if i > 0 then
        outname := copy(outname,1,i-1);
   end;
   
   if pos('.',outname) = 0 then
      outname := outname + '.C';

   i := pos('.',outname);
   unitname := copy(outname,1,i-1);
   
   if pos('.',inname) = 0 then
      inname := inname + '.PAS';

   if inname = outname then
      WriteLn('duplicate input/output name');
end;

begin
   assign(output,'');
   rewrite(output);
   writeln;

   decode_options;
   initialize;

   pprogram;

   closing_statistics;
end.
