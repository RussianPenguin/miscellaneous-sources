#include <GL/glut.h>

//Инициализация
void init(void){
	glClearColor(0.0,0.0,0.0,0.0);
	glShadeModel(GL_SMOOTH);
}

//Изменение размеров окна
void reshape(int w, int h){
	glViewport(0,0,(GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w<=h)
		gluOrtho2D(0.0,30.0,0.0,30.0*(GLfloat)h/(GLfloat)w);
	else
		gluOrtho2D(0.0,30.0*(GLfloat)w/(GLfloat)h,0.0,30.0);
	glMatrixMode(GL_MODELVIEW);
}

//Рисуем треугольник
void triangle(void){
	glBegin(GL_TRIANGLES);
		glColor3f(1.0,0.0,0.0);
		glVertex2f(5.0,5.0);
		glColor3f(0.0,1.0,0.0);
		glVertex2f(25.0,5.0);
		glColor3f(0.0,0.0,1.0);
		glVertex2f(5.0,25.0);
	glEnd();
}

//Отображение
void display(void){
	glClear(GL_COLOR_BUFFER_BIT);
	triangle();
	glFlush();
}

int main(int argc, char** argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Drawing a Smooth-Shaded Triangle");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}
