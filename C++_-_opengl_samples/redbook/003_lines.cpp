#include <GL/glut.h>
#define drawOneLine(x1,y1,x2,y2) glBegin(GL_LINES);glVertex2f((x1),(y1));glVertex2f((x2),(y2));glEnd();

void init(void){
	glClearColor(1.0,1.0,1.0,0.0);
	glShadeModel(GL_FLAT);
}

void display(void){
	int i;
	glClear(GL_COLOR_BUFFER_BIT);
	
	//Черный цвет для всех линий
	glColor3f(0.0,0.0,0.0);
	glEnable(GL_LINE_STIPPLE);
	//В первом ряду три линии с разными шаблонами
	glLineWidth(1.0);
	glLineStipple(1,0x0101); //Пунктирная
	drawOneLine(50.0,125.0,150.0,125.0);
	glLineStipple(1,0x00FF); //Штриховая
	drawOneLine(150.0,125.0,250.0,125.0);
	glLineStipple(1,0x1C47); //Штрих-пунктирная
	drawOneLine(250.0,125.0,350.0,125.0);
	
	//Во втором ряду три толстые линии с аналогичными шаблонами
	glLineWidth(5.0);
	glLineStipple(1,0x0101); //Пунктирная
	drawOneLine(50.0,100.0,150.0,100.0);
	glLineStipple(1,0x00FF); //Штриховая
	drawOneLine(150.0,100.0,250.0,100.0);
	glLineStipple(1,0x1C47); //Штрих-пунктирная
	drawOneLine(250.0,100.0,350.0,100.0);
	
	//В третьем ряду шесть штрих-пунктирных линий, объединенных в ломаную
	glLineWidth(1.0);
	glLineStipple(1,0x1C47); //Штрих-пунктирная
	glBegin(GL_LINE_STRIP);
		for (i=0;i<7;i++)
			glVertex2f(50.0+((GLfloat)i*50.0),75.0);
	glEnd();
	
	//В четвертом ряду шесть независимых линий того же шаблона
	for (i=0;i<6;i++){
		drawOneLine(50.0+((GLfloat)i*50.0),50.0,50.0+((GLfloat)(i+1)*50.0),50.0);
	}
	
	//В пятом ряду 1 штрих-пунктирная линия с фактором повторения=5
	glLineStipple(5,0x1c47);
	drawOneLine(50.0,25.0,350.0,25.0);
	glDisable(GL_LINE_STIPPLE);
	
	glFlush();
}

void reshape(int w,int h){
	glViewport(0,0,(GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,400.0,0.0,150.0);
}

int main(int argc, char **argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(400,150);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Line Stipple Patterns");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}
