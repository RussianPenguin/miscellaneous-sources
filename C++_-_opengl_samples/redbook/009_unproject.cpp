#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

//Изменение размеров окна
void reshape(int w, int h){
	glViewport(0,0,(GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0,(GLfloat) w/ (GLfloat) h,1.0,100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

//Отображение
void display(void){
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

//Реакция на мышь
void mouse(int button,int state,int x, int y){
	GLint viewport[4];
	GLdouble mvmatrix[16], projmatrix[16];
	//y – координата в OpenGL
	GLint realy;
	//Возвращаемые объектные x, y, z координаты
	GLdouble wx,wy,wz;
	switch(button){
		case GLUT_LEFT_BUTTON:
			if (state==GLUT_DOWN){
				glGetIntegerv(GL_VIEWPORT,viewport);
				glGetDoublev(GL_MODELVIEW_MATRIX,mvmatrix);
				glGetDoublev(GL_PROJECTION_MATRIX,projmatrix);
				//viewport[3] - высоте окна в пикселях
				realy=viewport[3]-(GLint)y-1;
				printf("Координаты в позиции курсора (%4d,%4d)\n",x,realy);
				gluUnProject((GLdouble)x,(GLdouble)realy,0.0,mvmatrix,projmatrix,viewport,&wx,&wy,&wz);
				printf("Объектные координаты при z=0 (%f,%f,%f)\n",wx,wy,wz);
				gluUnProject((GLdouble)x,(GLdouble)realy,1.0,mvmatrix,projmatrix,viewport,&wx,&wy,&wz);
				printf("Объектные координатыпри z=1 (%f,%f,%f)\n",wx,wy,wz);
			}
			break;
		case GLUT_RIGHT_BUTTON:
			if (state==GLUT_DOWN)
				exit(0);
			break;
	}
}

int main(int argc, char **argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Reversing the Geometric Processing Pipeline");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutMainLoop();
	return 0;
}
