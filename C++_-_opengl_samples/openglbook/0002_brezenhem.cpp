#include <math.h>
#include <GL/glut.h>

void setPixel(GLint xCoord, GLint yCoord){
	glBegin(GL_POINTS);
		glVertex2i(xCoord, yCoord);
	glEnd();
}

void swap(GLint &a, GLint &b){
	GLint t  = a;
	a = b;
	b = t;
}

void Line_Brezenhem(GLint x0, GLint y0, GLint xEnd, GLint yEnd){
	GLint dx = fabs(x0 - xEnd), dy = fabs(y0 - yEnd);
	GLint p, twoDy, twoDyMinusDx, x, y;
	bool dxldy = false;
	if(dy > dx){
		swap(dx, dy);
		swap(x0, y0);
		swap(xEnd, yEnd);
		dxldy = true;
	}
	p = 2* dy - dx;
	twoDy = 2 * dy;
	twoDyMinusDx = 2 * (dy -dx);
	if(x0 > xEnd){
		x = xEnd;
		y = yEnd;
		xEnd = x0;
	}else{
		x = x0;
		y = y0;
	}
	dxldy?setPixel(y,x):setPixel(x,y);
	while(x < xEnd){
		x++;
		if(p < 0)
			p += twoDy;
		else{
			y++;
			p += twoDyMinusDx;
		}
		dxldy?setPixel(y,x):setPixel(x,y);
	}
}

void Line_DDA(GLint x0, GLint y0, GLint xEnd, GLint yEnd){
	GLint dx = xEnd - x0, dy = yEnd - y0, steps, k;
	GLfloat xIncrement, yIncrement, x = x0, y = y0;
	if(fabs(dx) > fabs(dy))
		steps = fabs(dx);
	else
		steps = fabs(dy);
	xIncrement = float(dx) / float (steps);
	yIncrement = float(dy) / float (steps);
	setPixel(round(x), round(y));
	for(k = 0; k < steps; k++){
		x += xIncrement;
		y += yIncrement;
		setPixel(round(x), round(y));
	}
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

//Make circle's points
void circlePlotPoints(GLint xc, GLint yc, GLint x, GLint y){
	setPixel(xc + x, yc + y);
	setPixel(xc - x, yc + y);
	setPixel(xc + x, yc - y);
	setPixel(xc - x, yc - y);
	setPixel(xc + y, yc + x);
	setPixel(xc - y, yc + x);
	setPixel(xc + y, yc - x);
	setPixel(xc - y, yc - x);
}


//Special round function
inline GLint myround(const float a){
	return GLint(a + 0.5);
}

//Creating ellipse with middle-point alghorithm
void Ellipse_Brezenhem(GLint xCenter, GLint yCenter, GLint Rx, GLint Ry){
	GLint Rx2 = Rx * Rx;
	GLint Ry2 = Ry * Ry;
	GLint twoRx2 = Rx2 + Rx2;
	GLint twoRy2 = Ry2 + Ry2;
	GLint x = 0, y = Ry;
	GLint px = 0, py = twoRx2 * y;
	void ellipsePlotPoint(GLint,GLint,GLint,GLint);
	ellipsePlotPoint(xCenter,yCenter,x,y);
	
	GLint p = myround(Ry2 - (Rx2 * Ry) + (0.25 * Rx2));
	while(px < py){
		x++;
		px += twoRy2;
		if(p < 0)
			p += Ry2 + px;
		else{
			y--;
			py -= twoRx2;
			p += Ry2 + px - py;
		}
		ellipsePlotPoint(xCenter,yCenter,x,y);
	}
	
	p = myround(Ry2 * pow(x + 0.5,2) + Rx2*pow(y - 1, 2) - Rx2*Ry2);
	while(y > 0){
		y--;
		py -= twoRx2;
		if(p > 0)
			p += Rx2 - py;
		else{
			x++;
			px += twoRy2;
			p += Rx2 - py + px;
		}
		ellipsePlotPoint(xCenter,yCenter,x,y);
	}
}

void ellipsePlotPoint(GLint xCenter, GLint yCenter, GLint x, GLint y){
	setPixel(xCenter + x, yCenter + y);
	setPixel(xCenter - x, yCenter + y);
	setPixel(xCenter + x, yCenter - y);
	setPixel(xCenter - x, yCenter - y);
}

void init(void){
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 200.0, 0.0, 150.0);
}

void linesegment(void){
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	Circle_Brezenhem(100,75,40);
	Circle_Brezenhem(0,0,40);
	Circle_Brezenhem(199,0,40);
	Circle_Brezenhem(0,149,40);
	Circle_Brezenhem(199,149,40);
	Ellipse_Brezenhem(100,75,40,20);
	Ellipse_Brezenhem(0,0,40,20);
	Ellipse_Brezenhem(199,0,40,20);
	Ellipse_Brezenhem(0,149,40,20);
	Ellipse_Brezenhem(199,149,40,20);
	Line_Brezenhem(10,10,150,13);
	setPixel(0,149);
	Line_DDA(10,20,150,23);
	glFlush();
}

int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 100);
	glutInitWindowSize(400, 300);
	glutCreateWindow("Simple OpenGl Project");
	init();
	glutDisplayFunc(linesegment);
	glutMainLoop();
	return 0;
}
