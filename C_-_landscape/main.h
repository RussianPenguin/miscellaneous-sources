#ifndef __MAIN__
#define __MAIN__

#include <io.h>
#include <fcntl.h>
#include <math.h>
#include "glos.h"

#define WND_WIDTH  640
#define WND_HEIGHT 480

#define VIEWDISTANCE 40
#define LANDSCAPESIZE 1024
#define LANDSCAPESIZE2 LANDSCAPESIZE*LANDSCAPESIZE
#define NUM_TEXTURES 1

#define FLAT_SCALER 4.0f

extern GLint windW, windH;

#pragma pack(push)
#pragma pack(1)

struct LandScapeTerrain {
	GLubyte HEIGHTMAP[LANDSCAPESIZE][LANDSCAPESIZE];
	GLubyte LIGHTMAP[LANDSCAPESIZE][LANDSCAPESIZE];
};

struct ThePlayer {
	GLfloat x_pos;
	GLfloat y_pos;
	GLfloat height;
	GLfloat mounth;
	GLfloat alpha;
};

#pragma pack(pop)

extern struct LandScapeTerrain *LandScape;

#endif