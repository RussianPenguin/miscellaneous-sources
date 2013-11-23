
(*
 * TPTCSYS.PAS - System unit for use with Turbo Pascal --> C Translator
 *
 * (C) 1988 S.H.Smith (rev. 23-Mar-88)
 *
 * This unit is compiled to create 'TPTCSYS.UNS', which is automatically
 * loaded on each TPTC run.   It defines the predefined environment from
 * which programs are translated.
 *
 * Compile with:
 *    tptc tptcsys -lower
 *
 * Create an empty tptcsys.uns if the file does not already exist.
 *
 * Note the special 'as replacement_name' clause used in some cases.
 * When present, this clause causes the replacement_name to be used in
 * place of the original name in the translated output.
 *
 *)

unit tptc_system_unit;

interface

   (* 
    * Standard functions provided in Borland's system unit 
    *
    *)
   
   function Sin(n: real): real;
   function Cos(n: real): real;
   function Tan(n: real): real;
   function Sqr(n: real): real;
   function Sqrt(n: real): real;
   function Trunc(r: real): longint;
   function Round(r: real): real;
   function Int(r: real): real;

   function Pred(b: integer): integer;
   function Succ(b: integer): integer;
   function Ord(c: char): integer;
   function Hi(w: word): word;
   function Lo(w: word): word;

   function MemAvail: longint;
   function MaxAvail: longint;
   procedure Dispose(var ptr);
   procedure Mark(var ptr);
   procedure Release(var ptr);
      
   procedure Assign(fd: text; name: string);
   procedure Reset(var fd: text);
   procedure ReWrite(var fd: text);
   procedure Append(var fd: text);
   procedure SetTextBuf(fd: text; var buffer; size: word);
   procedure Seek(fd: text; rec: word);
   function SeekEof(fd: text): boolean;
      
   var ParamCount: integer;
   function ParamStr(n: integer): string;
   
   procedure Delete(s: string; posit,number: integer);
   function Copy(s: string; from,len: integer): string;
   procedure Val(s: string; var res: real; var code: integer);
   procedure Move(var tomem; var fmmem; bytes: word);
   procedure FillChar(var dest; size: integer; value: char);

   
   (*
    * Standard procedures with replacement names or modified
    * parameter types
    *
    *)
    
   function Eof(fd: text): boolean        as feof;
   procedure Flush(fd: text)              as fflush;
   procedure Close(fd: text)              as fclose;
   function UpCase(c: char): char         as toupper;
   function Length(s: string): integer    as strlen;

   procedure Inc(b: byte);          {tptcmac.h macros}
   procedure Dec(b: byte);
   
   type 
      setrec = set of char;
      
   function setof(element: byte {...}): setrec;
   function inset(theset: setrec; item: byte): boolean;

   function scat(control: string {...}): string;
       
   function ctos(c: char): string;
      
   procedure sbld(dest: string; control: string {...});
       
   function spos(key: string; str: string): integer;
      
   function cpos(key: char; str: string): integer;
      
   function fscanv(var fd: text; control: string {...}): integer;
    
   procedure MsDos(var reg);
   procedure Intr(fun: integer; var reg);

   var
      Lst:     text;
      Con:     text;
      Output:  text;
      Input:   text;
      

implementation

