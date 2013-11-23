
(*
 * This program demonstrates some weaknesses in TPC 1.4 and TPC 1.5.  Unless
 * otherwise noted, all failed translations are in 1.4 and corrected in 1.5.
 *
 *)

program Test;

var
   vector     : Integer absolute $0000:$03c4;
                        (* absolute variables not translated in tpc 1.5 *)

   Ch         : Char;
   IbmAt      : Boolean;
   Control    : Boolean;

type
  Longstring = string[255];

  Lookup = Array[1..7,0..1] of integer;
                        (* multi-dimension array declarations not translated
                           in tpc 1.5 *)

  NestedArray = Array[1..7] of array[0..1] of integer;
                        (* nested arrays not translated in tpc 1.5 *)

  mytype1 = char;
  mytype2 = byte;
  mytype3 = integer;
  mytype4 = string[80];

  myrec = record
     astr:  longstring;
     areal: real;
     aint:  integer;
     achar: char;
  end;
  
const
  tab  : Lookup = { this goes haywire here      }
                     ((10,824), (9,842), (9,858), (9,874),
                      (10,890), (9,908), (9,924));

procedure InvVid(m:  longstring);       {added}
begin
   writeln(m);
end;

procedure call_a;
var
   s1,s2: string;
begin
   s1 := 'filename';
   s2 := '#include "' + s1 + '"  ';
end;

procedure call_b(L     : Integer;
                 table : Lookup);
const
   seg_addr = $0040;                    {constants added}
   filter_ptr = $200;
   Vert = '|';
   Dbl = '==';

begin
  Write(Memw[seg_addr : Filter_Ptr] + 1); GotoXY(4,4);
  GotoXY(4,11);

{ put this next line in blows up in 1.4 -- }
          InvVid(Vert+' Retrieve '+Dbl+' Save '+Dbl+
                     ' Combine '+Dbl+' Xtract '+Dbl+' Erase '+
                     Dbl+' List '+Dbl+' Import '+Dbl+
                     ' Directory '+ Vert);
end;

procedure UsesUntyped( width: integer;
                       var base; {untyped}
                       size: integer );
var
   buf: array[1..1000] of byte absolute base;
                     (* absolutes not translated in 1.6 *)
   i: integer;
begin
   for i := 1 to size do 
      writeln(i,': ',buf[i]:width);
end;
                                            
   
procedure myprocmess(var v1, v2, v3);
         {untyped params not translated in tpc1.5}
var 
    xv1: mytype1 absolute v1;
    xv2: mytype2 absolute v2;
    xv3: mytype3 absolute v3;
    xv4: mytype4 absolute v3;  (* this is the dirtiest of the lot *)
                  {absolute variables not translated in tpc1.5}
    othvar1: integer;
    othvar2: char;
    
begin
    othvar1 := xv1;
    othvar2 := xv2;
    othvar1 := xv3;
    othvar2 := xv4;      
                  {implicit conversion of absolute variables to
                   pointer deref's produced by tptc1.6}
end;

procedure varparams(var i: integer;
                    var r: real;
                    var s: string);
begin
   i := 100;
   r := 100.1;
   s := 'some string';
   s[5] := '!';
end;

                    
procedure test_untyped;
var
   r: real;
   i: integer;
   s: string;
begin
   r := 1.2;
   i := 99;
   s := 'some string';
   myprocmess(r,i,s);

   UsesUntyped( 10, s, 2);
   UsesUntyped( 8, r, 3);
   UsesUntyped( 2, i, 3);

   varparams(i,r,s);

   str(r:3:1,s);  {should generate sbld call}
   val(s,r,i);    {should pass address of r and i}
end;

procedure testrec;
var
   rec1: myrec;
   rec2: myrec;
const
   limit = 1000;
begin
   rec1.astr := 'some string';
   rec1.astr[5] := '-';
   rec1.areal := 1.23;
   rec1.achar := 'x';
   rec1.aint := limit;
   writeln('str=',rec1.astr,' r=',rec1.areal,' i=',rec1.aint,' c=',rec1.achar);
   rec2 := rec1;
end;

procedure test_nesting(outerpar: integer);
const
   limit = 2000;  {clashes with testrec's limit?}
var
   outervar: integer;

   procedure inner;
      {outer version of inner}
   
      procedure inner;
         {name will clash with outer version of inner}
      begin
         outervar := 1;
         {inmost}
      end;
      
   var
      innervar: integer;
   begin
      inner; {outer version of inner}
      innervar := outerpar;
      outervar := innervar + limit;
   end;

begin
   inner;
   outervar := outerpar;
   write(^M^J'This wouldn''t translate in tpc1.5!');
   write(^M^J'This wouldn''t translate in tpc1.5!'^M^J);
   write('This wouldn''t translate in tpc1.5!'^M^J);
end;

procedure main_block;  
begin
   if Mem[$ffff:$0e] = $FC then
   begin
     IbmAt := True;
   end;

 Repeat
   if IbmAt then
     begin
       Control := True;
     end
   else

   case Ch of
      '1'..'8':     call_a;     { 1.4 fails to put in cases from 2 to 7 }
      'Z' :         call_a;
      'z' :         begin end;                { do nothing  }
       else
           { Do Nothing }
      end;

   Until (Ch = Chr(13))  OR  (Ch = 'Z');
end;



begin
   (* main block *)
   main_block;
end.

