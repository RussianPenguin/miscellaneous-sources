#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>

using namespace std;

const GLdouble twoPi = 6.283185;
const GLint a = 150, b = 50;

GLint curveNum;

struct screenPt{
	GLint x, y;
};

typedef enum {limacon = 1, cardioid, threeLeaf, fourLeaf, spiral} curveName;

GLsizei winWidth = 600, winHeight = 500;

void init(void){
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, (GLdouble) winWidth, 0.0, (GLdouble) winHeight);
}

void lineSegment(screenPt pt1, screenPt pt2){
	glBegin(GL_LINES);
		glVertex2i(pt1.x, pt1.y);
		glVertex2i(pt2.x, pt2.y);
	glEnd();
}

void drawCurve(void){
	GLfloat r, theta, dtheta = 1.0 / (GLfloat) a;
	GLint x0 = winWidth/2, y0 = winHeight/2;
	screenPt curvePt[2];
	glColor3f(0.0, 0.0, 0.0);
	curvePt[0].x = x0;
	curvePt[0].y = y0;
	switch(curveNum){
		case limacon:
			curvePt[0].x += a + b;
			break;
		case cardioid:
			curvePt[0].x += a + a;
			break;
		case threeLeaf:
			curvePt[0].x += a;
			break;
		case fourLeaf:
			curvePt[0].x += a;
			break;
		case spiral:
			break;
		default:
			break;
	}
	
	theta = dtheta;
	
	while(theta < twoPi){
		switch(curveNum){
			case limacon:
				r = a * cos(theta) + b;
				break;
			case cardioid:
				r = a * (1 + cos(theta));
				break;
			case threeLeaf:
				r = a * cos(3 * theta);
				break;
			case fourLeaf:
				r = a * cos(2 * theta);
				break;
			case spiral:
				r = (a/4.0) * theta;
				break;
			default:
				break;
		}
		curvePt[1].x = x0 + r*cos(theta);
		curvePt[1].y = y0 + r*sin(theta);
		
		lineSegment(curvePt[0], curvePt[1]);
		
		curvePt[0] = curvePt[1];
		theta += dtheta;
	}
}

void displayFunc(void){
	glClear(GL_COLOR_BUFFER_BIT);
	drawCurve();
	glFlush();
}


void winReshapeFunc(GLint newWidth, GLint newHeight){
	glViewport(0, 0, (GLsizei) newWidth, (GLsizei) newHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble) winWidth, 0.0, (GLdouble) winHeight);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char **argv){
	cout << "1 - limacon\n2 - cardioid\n3 - threeLeaf\n4 - fourLeaf\n5 - spiral\n";
	cin >> curveNum;
	if(curveNum < 1 && curveNum > 5)
		exit(0);

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("pieChart");

	init();

	glutDisplayFunc(displayFunc);
	glutReshapeFunc(winReshapeFunc);

	glutMainLoop();
}
