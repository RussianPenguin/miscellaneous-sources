//Пример функции изменения формы и таблицы отображений
#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>

const double TWO_PI = 6.2831853;

GLsizei winWidth = 400, winHeight = 400;
GLuint regHex;

static void init(void){
	GLint xhexVertex = 0, yhexVertex = 0;
	GLint xcircCtr = 0, ycircCtr = 0;
	GLdouble theta;
	GLint k;

	xcircCtr = winWidth  /2;
	ycircCtr = winHeight /2;

	glClearColor(1.0, 1.0, 1.0, 0.0);
	regHex = glGenLists(1);

	glNewList(regHex, GL_COMPILE);
		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON);
			for(k = 0; k < 6; k++){
				theta = TWO_PI*k/6.0;
				xhexVertex = xcircCtr + 150 * cos(theta);
				yhexVertex = ycircCtr + 150 * sin(theta);
				glVertex2i(xhexVertex, yhexVertex);
			}
		glEnd();
	glEndList();
	//gluOrtho2D(0.0, (GLdouble) winWidth, 0.0, (GLdouble) winHeight);
}

void regHexagon(void){
	glClear(GL_COLOR_BUFFER_BIT);
	glCallList(regHex);
	glFlush();
}

void winReshapeFunc(GLint newWidth, GLint newHeight){
	glViewport(0, 0, (GLsizei) newWidth, (GLsizei) newHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, winWidth, 0.0, winHeight);
//	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char **argv){
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("0003");

	init();

	glutDisplayFunc(regHexagon);
	glutReshapeFunc(winReshapeFunc);

	glutMainLoop();
}
