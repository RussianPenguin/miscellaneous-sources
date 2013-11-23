/****************************************************************
 
FILE : TUXIDOW.H
DETAILS : APPLICATION IS INITIALISED , CHECKS CURRENT WINDOWS VERSION
CONTACT : tuxidow@yahoo.com

*****************************************************************/

#ifndef __TUXIDOW_H
#define __TUXIDOW_H

#ifdef _WIN32
#include <windows.h>
#include <winnt.h>
#include <winioctl.h>
#include <windowsx.h>
#include <commctrl.h>
#endif

#include <direct.h>
#include <stdio.h>
#include <math.h>

#include "diskio.h"
//#include "partit.h"


#define MAX_LEN 1024

/*function prototype*/
void PrintError(char *msg);
BOOL FindCurrentOS() ;

HWND     hwndPB ; //The progress bar control handle .
				 
FILE *IMGPTR;
int present_partition;

#include "partit.h"
#include "gui.h"

#endif