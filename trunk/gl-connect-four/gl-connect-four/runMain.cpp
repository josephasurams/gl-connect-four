#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#include <gl\glut.h>

//used for glut init - Don't really do anything!
int argc = 1;
char *argv = "";

#define SCREENWIDTH 800
#define SCREENHEIGHT 600



typedef struct
{
	GLfloat x,y;
	char color; 

}circle;

void writeText(GLfloat x, GLfloat y, char *text);
void myMouse(int button, int state, int x, int y);
void keyboard(unsigned char key,int x, int y);
void newGame(void);
void delay(const int n);
void drawGame(void);
void drawCircle(int i, int j);

int tmp = 1; //kepts track which playes turn ( 1 = player 1, 2 = player 2)

float R; 
float radius = 20.0;
circle circleArray[7][7]; 
int gameArray[6][7]; 
#define TWOPI 2*3.14159265

void setWindow(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(left,right,bottom,top); 

	//reset aspect ratio
	R = fabs((right-left)/(top - bottom)); 
}

void setViewport(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top)
{
	glViewport((int)left,(int)right,(int)(right-left),(int)(bottom-top)); 
}
void myInit(void)
{
	glClearColor(0.0,0.0,0.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glLineWidth(2.0);
	setWindow(0,SCREENWIDTH,0,SCREENHEIGHT);
	setViewport(0,SCREENWIDTH,0,SCREENHEIGHT);
    
	
	newGame();

	
}
void newGame(void)
{
	//Set up the Game

	//All Black/Empty
	
	for(int m = 0; m < 6; m++)
	{
		for(int z = 0; z < 7;z++)
		{
			gameArray[m][z] = 0; 
		}
	}

	//Set up the color and places of the circles--------------------------------
	for(int m = 0; m < 7; m++)
	{
		for(int z = 0, w = 0; z < 7;z++,w +=20)
		{
			circleArray[m][z].x =60 + w;
			circleArray[m][z].y = 60 ;
			circleArray[m][z].color = 'b'; //black defaul
		}
	}
	circleArray[0][0].color = 'r'; //red

}

void drawButtons() {
	//draw button background
	glPushMatrix();
	glColor3f(1.0,1.0,0.0);
	glBegin(GL_QUADS);
	glVertex2i(SCREENWIDTH-200,60);
	glVertex2i(SCREENWIDTH-20,60);
	glVertex2i(SCREENWIDTH-20,20);
	glVertex2i(SCREENWIDTH-200,20);
	glEnd();
	//draw text ("Reset Game");
	glColor3f(0.0,0.0,0.0);
	glRasterPos2i(SCREENWIDTH-170,30);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 82);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 101);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 115);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 101);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 116);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 32);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 71);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 97);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 109);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 101);
	glPopMatrix();
}

void drawGame(void)
{
	drawButtons();
	glPushMatrix();
	glColor3f(0.0,0.0,1.0);
	glRecti(150,80,630,385);
	glTranslatef(70,350,0);
	for(int m = 0; m < 7; m++)
	{
		for(int z = 0,w = 0; z < 7; z++,w+=20)
		{
			glTranslatef(50,0,0);
			
			drawCircle(m,z);

		}
		glTranslatef(-350,-50,0);
	}
	glPopMatrix();
	
}
void drawCircle(int i, int j)
{
	float x = circleArray[i][j].x;
	float y = circleArray[i][j].y;
	if(circleArray[i][j].color == 'b')//Black
		glColor3f(0.0,0.0,0.0); 
	if(circleArray[i][j].color == 'g')//Green
		glColor3f(0.0,1.0,0.0); 
	if(circleArray[i][j].color == 'r')//Red
		glColor3f(1.0,0.0,0.0); 
	float angle = 0, angleInc = TWOPI/200; //angle increment
	
	glBegin(GL_POLYGON);
	for(int k = 1; k <= 200; k++)
	{
		angle += angleInc;
		glVertex3f(radius * cos(angle) + x, radius*sin(angle) +y,0);
		
	}
	glEnd();
	glFlush(); 

}
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<myDisplay>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT); //Clear the screen
	
	
    drawGame();
	
	glutSwapBuffers();
	
}

void myReshape(GLsizei W, GLsizei H)
{
	if(R > W/H) //use global window aspect ratio
		setViewport(0,W,0,W/R);
	else
		setViewport(0,H*R,0,H);
}

void myIdle()
{
	glutPostRedisplay();
}

int main()
{
	glutInit(&argc, &argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(SCREENWIDTH, SCREENHEIGHT);
	glutInitWindowPosition(100,150);
	glutCreateWindow("Mouse Chase");
	glutDisplayFunc(myDisplay);
	glutReshapeFunc(myReshape);
	glutIdleFunc(myIdle);
	glutMouseFunc(myMouse);
	glutKeyboardFunc(keyboard);
	myInit();
	glutMainLoop();
	return 1; 

}

void myMouse(int button, int state, int x, int y)
{
//if left button clicked move the rat
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		
	}
}

void writeText(GLfloat x, GLfloat y, char *text)
{
    char *p;
    
    glPushMatrix();
	glColor3f(1.0,0.0,0.0); 
    glRasterPos2f(x,y); 
    for (p = text; *p; p++)
        glutBitmapCharacter (GLUT_BITMAP_TIMES_ROMAN_24, *p);
    glPopMatrix();
	
}
void keyboard(unsigned char key,int x, int y)
{

	//Moving Right------------------------------------------
	if(key == 'f'|| key == 'F')
	{
	 	 
		for(int z = 0; z < 7; z++)
		{
			
			if(circleArray[0][z].color == 'r')
			{
				circleArray[0][z].color = 'b';
				circleArray[0][z+1].color = 'r';
				z= 7;//get out of the for loop
			}
			else if (circleArray[0][z].color == 'g')
			{
				circleArray[0][z].color = 'b';
				circleArray[0][z+1].color = 'g';
				z= 7;//get out of the for loop
			}
			else if(circleArray[0][6].color == 'r')
			{
				circleArray[0][6].color  = 'b';
				circleArray[0][0].color = 'r';
				z= 7;//get out of the for loop
			}
		    else if (circleArray[0][6].color == 'g')
			{
				circleArray[0][6].color = 'b';
				circleArray[0][0].color = 'g';
				z= 7;//get out of the for loop

			}//end of if
		}//end of if
	}//end of if key

	  //Moving LEFT ------------------------------------------------
	if(key == 's'|| key == 'S')
	{
		
		for(int z = 6; z > 0; z--)
		{
			if(circleArray[0][0].color == 'r')
			{
				circleArray[0][0].color = 'b';
				circleArray[0][6].color = 'r';
				z= 0;//get out of the for loop
			}
			else if (circleArray[0][0].color == 'g')
			{
				circleArray[0][0].color = 'b';
				circleArray[0][6].color = 'g';
				z= 0;//get out of the for loop
			
			}
			else if(circleArray[0][z].color == 'r')
			{
				circleArray[0][z].color = 'b';
				circleArray[0][z-1].color = 'r';
				z= 0;//get out of the for loop
			}
			else if (circleArray[0][z].color == 'g')
			{
				circleArray[0][z].color = 'b';
				circleArray[0][z-1].color = 'g';
				z= 0;//get out of the for loop
			
		    
			}//end of else if
		}//end of the for loop
	}//end of if Key
	

			// Drop ------------------------------------------------------
	if(key == 'd'|| key == 'D')
	{
	  for(int m = 0; m < 7; m++)
	  {
		for(int z = 0; z < 6; z++)
		{
			
			
			if(circleArray[z][m].color == 'r')
			{
				if(gameArray[z][m] == 0) //check if there something on that spot
				{												//Check if it is able to drop
					circleArray[z][m].color = 'b';
					circleArray[z+1][m].color = 'r';
					
					gameArray[z-1][m] = 0;
					gameArray[z][m]= 1;
					circleArray[0][0].color = 'g';//change turn
				
				}
				
			
				
				
			}
			else if (circleArray[z][m].color == 'g')
			{
				if(gameArray[z][m] == 0)
				{
					circleArray[z][m].color = 'b';
					circleArray[z+1][m].color = 'g';
					gameArray[z-1][m] = 0;
					gameArray[z][m] = 2; 
					circleArray[0][0].color = 'r';//change turn
				}//end of the if
				
			}//end of if
		}//end of the for loop
	  }//end of the for loop


	  //Check for Winner ----------------------------------------------------
	   
   }//end of if drop Key
  
}
void delay(const int n)
{
 time_t start_time, cur_time;

         time(&start_time);
         do
         {
                 time(&cur_time);
         }
         while((cur_time - start_time) < n);
}
