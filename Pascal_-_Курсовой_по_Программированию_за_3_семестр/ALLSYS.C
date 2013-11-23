
#include "types.h"

/*
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
 */ 

 /* unit tptc_system_unit  */ 



   /* 
    * Standard functions provided in Borland's system unit 
    *
    */ 

   
#define extern /* globals defined here */
#include "ALLSYS.UNH"
#undef extern





