//graphics2d.cpp - use #include " graphics2d.h
// Some methods for the classes defined in graphics2d.h


#include "graphics2d.h"

/*Canvas :: Canvas(int width, int height, char* title)
{
		char* list; 
		int numArgs = 1;
		glutInit(&numArgs, &list);
		glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
		glutInitWindowSize(width, height);
		glutInitWindowPosition(100, 100);
		glutCreateWindow(title);
	CP.x = CP.y	=0.0;
	windowAspect=1.0;
}*/

Canvas:: Canvas(int width, int height)
{
	char* argv[1]; 
	char dummyString[8];
	argv[0] = dummyString; 
	int argc = 1; 
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(200, 200);
//	glutCreateWindow(windowTitle); 
	setWindow(0, (float)width, 0, (float)height); 
	setViewport(0, width, 0, height); 
	CP.set(0.0f, 0.0f); 
}


void Canvas :: setWindow(float l, float r, float b, float t)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); 
	gluOrtho2D((GLdouble)l, (GLdouble)r, (GLdouble)b, (GLdouble)t);
	if(t == b) return; 
	windowAspect = (r - 1)/(t - b);
}

void Canvas :: setViewport(int l, int r, int b, int t) 
{
	glViewport((GLint)l, (GLint)b, (GLint)(r-l), (GLint)(t-b));
}

void Canvas :: lineTo(float x, float y)
{
	glBegin(GL_LINES);
		glVertex2f((GLfloat)CP.x, (GLfloat)CP.y);
		CP.x = x; CP.y = y;
		glVertex2f((GLfloat)CP.x, (GLfloat)CP.y);
	glEnd();
	glFlush();
}

void Canvas :: forward(float dist, int vis) 
{
    #define RadPerDeg 0.017453393 //radians per degree 
	float x = CP.x + dist * cos(RadPerDeg * CD);
	float y = CP.y + dist * sin(RadPerDeg * CD); 
	if(vis) lineTo(x, y);
	else moveTo(x, y);
	CP.x = x; CP.y = y;
}

void Canvas::ngon(int n,float cx, float cy, float radius)
{
	#define RadPerDeg 0.017453393 //radians per degree
	if(n < 3) 
		return; // bad number of sides
	double angle = 0, angleInc = 2 * 3.14159265 /n; //angle increment
	moveTo(cx + radius, cy);
	for(int k = 1; k <= n; k++)
	{
		angle += angleInc;
		lineTo(radius * cos(angle) + cx, radius*sin(angle) + cy);
	}
}



void Canvas::moveRel(float dx, float dy)
{
	CP.set(CP.x+dx, CP.y+dy);
}

void Canvas::lineRel(float dx, float dy)
{
	float x=CP.x+dx, y=CP.y+dy;
	lineTo(x,y);
	CP.set(x, y);
}

//end of graphics2d.cpp


