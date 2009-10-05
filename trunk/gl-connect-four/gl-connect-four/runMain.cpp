#include <windows.h> 
#include "graphics2d.cpp"


Canvas cvs(640,480);


const int screenWidth = 640; // width of screen window in pixels
const int screenHeight = 480; // height of screen window in pixels



void myInit(void)
{
	glClearColor(1.0,1.0,1.0,0.0); 
	glColor3f(0.0f, 0.0f, 0.0f); 
	glPointSize(2.0); 
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity();
}

void myDisplay(void)
{
	
	glClear(GL_COLOR_BUFFER_BIT);
	cvs.setWindow(-30.0, 30.0, -30.0, 30.0); 
	cvs.setViewport(0, 640, 0, 480); 
	GLdouble len=0.2;
	
	
	glColor3f(0,0,0);
	cvs.moveTo(-35,30);

	for(int x=0; x < 15; x++) {
	for(int j=0; j < 15; j++) {
		for(int i=0;i<200;i++)
		{
			cvs.forward(len,1);
			cvs.turn(2.0);
		}
		cvs.moveRel(5.75, 0);
	}
		cvs.moveRel(-86.25, -5);
	}
}



void main(int argc, char** argv)
{
	glutCreateWindow("Exercise 3, Figure 1"); 
	glutDisplayFunc(myDisplay);
	myInit();
	glutMainLoop(); 
}