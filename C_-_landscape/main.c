/* MAIN.C - main file */

#include "main.h"

GLint windW, windH;

struct LandScapeTerrain *LandScape; /* HEIGHT data              */
struct ThePlayer CurrentPlayer;     /* "PLAYER"                 */
GLuint texobjs[NUM_TEXTURES];       /* textures                 */
AUX_RGBImageRec *texture_grass;     /* "grass" texture itself   */
GLfloat x_pos_frac, y_pos_frac;     /* fractional parts of move */

GLboolean LoadTerrain(char *fn)
{
	int LandScapeFile;
	LandScapeFile = _open(fn, _O_RDONLY | _O_BINARY);
	if (LandScapeFile == -1) return GL_FALSE;
    _read(LandScapeFile, LandScape->HEIGHTMAP, LANDSCAPESIZE2);
	_close(LandScapeFile);
	return GL_TRUE;
}

void SetupPlayer(void)
{
	CurrentPlayer.x_pos = (GLfloat)LANDSCAPESIZE / 2.0f;
	CurrentPlayer.y_pos = (GLfloat)LANDSCAPESIZE / 2.0f;
	CurrentPlayer.height = 1.2f * FLAT_SCALER;
	CurrentPlayer.alpha = 0;
}

GLboolean Init(void)
{
	GLfloat fogColor[] = {0.9f, 0.9f, 1.0f, 0.0f};
	
	LandScape = (struct LandScapeTerrain*)malloc(sizeof(struct LandScapeTerrain));
	if (LandScape == NULL) return GL_FALSE;
	if (LoadTerrain("data\\land.raw") == GL_FALSE) {
		free(LandScape);
		return GL_FALSE;
	}

    texture_grass = auxDIBImageLoad("data\\grass.bmp");
	if (texture_grass == NULL) return GL_FALSE;

    glGenTextures(NUM_TEXTURES, texobjs);
	glBindTexture(GL_TEXTURE_2D, texobjs[0]);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, texture_grass->sizeX, texture_grass->sizeY,
                      GL_RGB, GL_UNSIGNED_BYTE, texture_grass->data);

	glClearColor(fogColor[0], fogColor[1], fogColor[2], fogColor[3]);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_TEXTURE_2D);

	glEnable(GL_FOG);
	glFogi(GL_FOG_MODE, GL_EXP2);
	glFogf(GL_FOG_DENSITY, 0.04f);
	glFogfv(GL_FOG_COLOR, fogColor);

	SetupPlayer();
	
	return GL_TRUE;
}

void Done(void)
{
	free(LandScape);
}

static void CALLBACK Reshape(int width, int height)
{
	GLfloat aspect;
	if (!width) return;

	glFinish();
	
	windW = (GLint)width;
	windH = (GLint)height;

	aspect = (GLfloat)windW / (GLfloat)windH;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0f, aspect, 0.05f, 50.0f);

    glViewport (0, 0, windW, windH);
}

GLfloat ReturnHEIGHT(GLint _x_, GLint _y_)
{
//	_x_=_x_ << 1;
//	_y_=_y_ << 1;
	if (_x_ < 0) _x_+=LANDSCAPESIZE;
	if (_y_ < 0) _y_+=LANDSCAPESIZE;
	if (_x_ >= LANDSCAPESIZE) _x_-=LANDSCAPESIZE;
	if (_y_ >= LANDSCAPESIZE) _y_-=LANDSCAPESIZE;
	return (GLfloat)LandScape->HEIGHTMAP[_x_][_y_];
}

GLboolean PointInFrustum(GLint _x_, GLint _y_)
{
	if (sqrt(_x_ * _x_ + _y_ * _y_) >= VIEWDISTANCE >> 1) return GL_FALSE;
	return GL_TRUE;
}

void PreDrawLandScape(void)
{
	GLint ix, iy, oix, oiy;
	GLfloat fx, fy, xcf, ycf;
	GLfloat h1, h2, h3, h4, res_h;

	ix = (GLint)CurrentPlayer.x_pos;
	iy = (GLint)CurrentPlayer.y_pos;
	fx = (GLfloat)CurrentPlayer.x_pos;
	fy = (GLfloat)CurrentPlayer.y_pos;
	
	oix = ix; oiy = iy;
	h1 = ReturnHEIGHT(ix, iy);
	if (fx > ix) ix++; else ix--;
	h2 = ReturnHEIGHT(ix, iy);
	if (fy > iy) iy++; else iy--;
	h3 = ReturnHEIGHT(oix, iy);
	h4 = ReturnHEIGHT(ix, iy);
	xcf = 1.0f - fabs((GLfloat)oix - fx);
	ycf = 1.0f - fabs((GLfloat)oiy - fy);
	res_h = h1 * xcf * ycf +
		h2 * (1.0f - xcf) * ycf +
		h3 * (1.0f - ycf) * xcf +
		h4 * (1.0f - xcf) * (1.0f - ycf);

	CurrentPlayer.mounth = res_h;

	x_pos_frac = (CurrentPlayer.x_pos - ix) * FLAT_SCALER;
	y_pos_frac = (CurrentPlayer.y_pos - iy) * FLAT_SCALER;
}

void DrawLandScape(void)
{
	GLint i, j;
	GLint tx, ty;
	GLint ix, iy;
	GLfloat z1, z2, z3, z4;
	GLfloat x1, x2, y1, y2;
	ix = (GLint)CurrentPlayer.x_pos;
	iy = (GLint)CurrentPlayer.y_pos;

	glBegin(GL_TRIANGLES);
	for (i = - VIEWDISTANCE >> 1; i < VIEWDISTANCE >> 1; i++)
		for (j = - VIEWDISTANCE >> 1; j < VIEWDISTANCE >> 1; j++)
		{
			if (PointInFrustum(i, j) == GL_TRUE) {

				tx = ix + i;
				ty = iy + j;

				z1 = ReturnHEIGHT(tx    , ty    );
				z2 = ReturnHEIGHT(tx + 1, ty    );
				z3 = ReturnHEIGHT(tx + 1, ty + 1);
				z4 = ReturnHEIGHT(tx    , ty + 1);
	
				x1 = (GLfloat)(i) * FLAT_SCALER;
				x2 = (GLfloat)(i+1) * FLAT_SCALER;
				y1 = (GLfloat)(j) * FLAT_SCALER;
				y2 = (GLfloat)(j+1) * FLAT_SCALER;

				// --1--
				glTexCoord2f(0.0f, 0.0f);
				glVertex3f(x1, y1, z1);
				glTexCoord2f(1.0f, 0.0f);
				glVertex3f(x2, y1, z2);
				glTexCoord2f(1.0f, 1.0f);
				glVertex3f(x2, y2, z3);
				// --2--
				glTexCoord2f(1.0f, 1.0f);
				glVertex3f(x2, y2, z3);
				glTexCoord2f(0.0f, 1.0f);
				glVertex3f(x1, y2, z4);
				glTexCoord2f(0.0f, 0.0f);
				glVertex3f(x1, y1, z1);

			}

		}
	glEnd();
}

static void CALLBACK Draw(void)
{
	PreDrawLandScape();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
//	glTranslatef(0.0f, 0.0f, -p__-15.5);
//	glRotatef(t__*100, 0.0f, 0.0f, 1.0f);
//	glRotatef(rotX, 1.0f, 0.0f, 0.0f);
//	glRotatef(rotY, 0.0f, 1.0f, 0.0f);
//	glRotatef(rotZ, 0.0f, 0.0f, 1.0f);
//	glRotatef(-45.0f, 1.0f, 0.0f, 0.0f);
	gluLookAt( 0+x_pos_frac,
		       0+y_pos_frac,
		       CurrentPlayer.mounth + CurrentPlayer.height,
		       cos(CurrentPlayer.alpha)+x_pos_frac,
			   sin(CurrentPlayer.alpha)+y_pos_frac,
			   CurrentPlayer.mounth + CurrentPlayer.height,
			   0,
			   0,
			   1);
	// ...
	DrawLandScape();
	// ...
	glFlush();
	auxSwapBuffers();
}

static void CALLBACK IdleFunc(void)
{
	// ...
	CurrentPlayer.alpha -= 0.0005f;
	CurrentPlayer.x_pos += cos(CurrentPlayer.alpha) / 100.0f;
	CurrentPlayer.y_pos += sin(CurrentPlayer.alpha) / 100.0f;
	Draw();
}

void main(int argc, char **argv)
{
	windW = WND_WIDTH;
	windH = WND_HEIGHT;

	auxInitPosition(0, 0, windW, windH);
	auxInitDisplayMode(AUX_RGB | AUX_DOUBLE | AUX_DEPTH);

	if (auxInitWindow("LandScape") == GL_FALSE) auxQuit();
	if (Init() == GL_FALSE) auxQuit();

	auxReshapeFunc((AUXRESHAPEPROC)Reshape);
	auxIdleFunc((AUXIDLEPROC)IdleFunc);
	auxMainLoop(Draw);

	Done();
}
