#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

const GLdouble twoPi = 6.283185;

struct scrPt{
	GLint x, y;
};

GLsizei winWidth = 400, winHeight = 300;

void init(void){
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 200.0, 0.0, 150.0);
}

void setPixel(GLint xCoord, GLint yCoord){
	glBegin(GL_POINTS);
		glVertex2i(xCoord, yCoord);
	glEnd();
}

void Circle_Brezenhem(GLint xc, GLint yc, GLint radius){
	GLint p = 1 - radius;
	GLint x = 0, y = radius;
	void circlePlotPoints(GLint, GLint, GLint, GLint);
	circlePlotPoints(xc, yc, x, y);
	while(x < y){
		x++;
		if(p < 0)
			p += x + x + 1;
		else{
			y--;
			p += 2*(x - y) + 1;
		}
		circlePlotPoints(xc, yc, x, y);
	}
}

void circlePlotPoints(GLint xc, GLint yc, GLint x, GLint y){
	setPixel(xc + x - 1, yc + y - 1);
	setPixel(xc - x, yc + y - 1);
	setPixel(xc + x - 1, yc - y);
	setPixel(xc - x, yc - y);
	setPixel(xc + y - 1, yc + x - 1);
	setPixel(xc - y, yc + x - 1);
	setPixel(xc + y - 1, yc - x);
	setPixel(xc - y, yc - x);
}

void pieChart(void){
	scrPt circCtr, piePt;
	GLint radius = winWidth / 4;
	GLdouble sliceAngle, previousSliceAngle = 0.0;
	GLint k, nSlices = 12;
	GLfloat dataValues[12] = {
				10.0, 7.0, 13.0, 5.0, 13.0, 14.0,
				3.0, 16.0, 5.0, 3.0, 17.0, 8.0};
	GLfloat dataSym = 0.0;
	circCtr.x = winWidth /2;
	circCtr.y = winHeight /2;
	Circle_Brezenhem(circCtr.x, circCtr.y, radius);
	
	for(k = 0; k < nSlices; k++)
		dataSym += dataValues[k];

	for(k = 0; k < nSlices; k++){
		sliceAngle = twoPi * dataValues[k] / dataSym + previousSliceAngle;
		piePt.x = circCtr.x + radius * cos(sliceAngle);
		piePt.y = circCtr.y + radius * sin(sliceAngle);

		glBegin(GL_LINES);
			glVertex2i(circCtr.x, circCtr.y);
			glVertex2i(piePt.x, piePt.y);
		glEnd();
		
		previousSliceAngle = sliceAngle;
	}
}

void winDisplayFunc(void){
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 1.0);
	pieChart();
	glFlush();
}

void winReshapeFunc(GLint newWidth, GLint newHeight){
	glViewport(0, 0, (GLsizei) newWidth, (GLsizei) newHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble) newWidth, 0.0, (GLdouble) newHeight);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	winWidth = newWidth;
	winHeight = newHeight;
}

int main(int argc, char **argv){
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("pieChart");

	init();

	glutDisplayFunc(winDisplayFunc);
	glutReshapeFunc(winReshapeFunc);

	glutMainLoop();
}
