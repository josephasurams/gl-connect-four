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
void drawButtons();
void drawPlayerTurnBox();
char findWhosTurn();



float R; 
float radius = 20.0;
circle circleArray[7][7]; 
int gameArray[6][7]; 
bool highlightButton = false;
#define TWOPI 2*3.14159265
GLuint texture[1];

/*AUX_RGBImageRec *LoadBMP(char *Filename)					// Loads A Bitmap Image
{
	FILE *File=NULL;							// File Handle

	if (!Filename)								// Make Sure A Filename Was Given
	{
		return NULL;							// If Not Return NULL
	}
	File=fopen(Filename,"r");						// Check To See If The File Exists
	if (File)								// Does The File Exist?
	{
		fclose(File);							// Close The Handle
		return auxDIBImageLoad(Filename);				// Load The Bitmap And Return A Pointer
	}
	return NULL;								// If Load Failed Return NULL
}/*
int LoadGLTextures()								// Load Bitmaps And Convert To Textures
{
	int Status=FALSE;
	AUX_RGBImageRec *TextureImage[1];
	memset(TextureImage,0,sizeof(void *)*1);
	if (TextureImage[0]=LoadBMP("Data/NeHe.bmp"))
	{
		Status=TRUE;							// Set The Status To TRUE
		glGenTextures(1, &texture[0]);					// Create The Texture

		// Typical Texture Generation Using Data From The Bitmap
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		// Generate The Texture
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
	//PICKUP HERE !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!(http://nehe.gamedev.net/data/lessons/lesson.asp?lesson=06) halfway down*/
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
	glClearColor(0.0,1.0,0.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glLineWidth(2.0);
	setWindow(0,SCREENWIDTH,0,SCREENHEIGHT);
	setViewport(0,SCREENWIDTH,0,SCREENHEIGHT);
	
	newGame();
}



char findWhosTurn() {
	//loop unti who's turn it is, is found
	bool continueLooping = true;
	for(int i = 0; continueLooping; i++) {
		if((circleArray[0][i].color == 'r') || (circleArray[0][i].color == 'g'))
			return circleArray[0][i].color;
	}
}



void newGame(void)
{
	
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
			circleArray[m][z].color = 'g'; //black defaul
		}
	}
	circleArray[0][0].color = 'r'; //red

}

void drawButtons() {
	//draw button background
	highlightButton?glColor3f(1.0,0.0,0.0):glColor3f(1.0,1.0,0.0);
	glBegin(GL_QUADS);
	glVertex2i(SCREENWIDTH-200,60);
	glVertex2i(SCREENWIDTH-20,60);
	glVertex2i(SCREENWIDTH-20,20);
	glVertex2i(SCREENWIDTH-200,20);
	glEnd();
	//draw text ("Reset Game");
	glColor3f(0.0,0.0,0.0);
	glRasterPos2i(SCREENWIDTH-170,30);// yo you can use the writeText function to write text
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 82);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 101);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 115);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 101);// you just have to do is  
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 116);//writeText(location of x, location of y,"text"); 
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 32);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 71);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 97);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 109);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 101);
}

void drawGame(void)
{
	drawButtons();
	drawPlayerTurnBox();
	glPushMatrix();
	glColor3f(1.0,1.0,0.0);
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

void drawPlayerTurnBox() {
	//draw who's turn it is
	glColor3f(0.0,0.0,0.0);
	char c = findWhosTurn();
	if (findWhosTurn() == 'r') {
		//"Red"
		glColor3f(1.0,0.0,0.0);
		glRasterPos2i(20,30);
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 82);
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 101);
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 100);
	} else {
		//"black"
		glColor3f(0.0,0.0,0.0);
		writeText(20.0,30.0,"Black");
	}
	//" player's turn"
	glColor3f(1.0,1.0,0.0);
	glRasterPos2i((findWhosTurn()=='r')?63:80, 30);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 32);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 80);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 108);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 97);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 121);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 101);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 114);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 96);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 115);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 32);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 84);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 117);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 114);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 110);
}

void drawCircle(int i, int j)
{
	float x = circleArray[i][j].x;
	float y = circleArray[i][j].y;
	if(circleArray[i][j].color == 'g')//Green
		glColor3f(0.0,1.0,0.0); 
	if(circleArray[i][j].color == 'b')//black
		glColor3f(0.0,0.0,0.0); 
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
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(SCREENWIDTH, SCREENHEIGHT);
	glutInitWindowPosition(100,150);
	glutCreateWindow("GL Connect Four");
	glutDisplayFunc(myDisplay);
	glutReshapeFunc(myReshape);
	glutIdleFunc(myIdle);
	glutMouseFunc(myMouse);
	glutKeyboardFunc(keyboard);
	myInit();
	glutMainLoop();

	return 0; 
}

void myMouse(int button, int state, int x, int y)
{
	//invert y
	y = SCREENHEIGHT - y;

	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if((x >= SCREENWIDTH-200) && (x <= SCREENWIDTH-20)) {
			if ((y >= 20) && (y <= 60)) {
				highlightButton = true;
				newGame();
			}
		}
	} else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
			highlightButton = false;
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
				circleArray[0][z].color = 'g';
				circleArray[0][z+1].color = 'r';
				z= 7;//get out of the for loop
			}
			else if (circleArray[0][z].color == 'b')
			{
				circleArray[0][z].color = 'g';
				circleArray[0][z+1].color = 'b';
				z= 7;//get out of the for loop
			}
			else if(circleArray[0][6].color == 'r')
			{
				circleArray[0][6].color  = 'g';
				circleArray[0][0].color = 'r';
				z= 7;//get out of the for loop
			}
		    else if (circleArray[0][6].color == 'b')
			{
				circleArray[0][6].color = 'g';
				circleArray[0][0].color = 'b';
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
				circleArray[0][0].color = 'g';
				circleArray[0][6].color = 'r';
				z= 0;//get out of the for loop
			}
			else if (circleArray[0][0].color == 'b')
			{
				circleArray[0][0].color = 'g';
				circleArray[0][6].color = 'b';
				z= 0;//get out of the for loop
			
			}
			else if(circleArray[0][z].color == 'r')
			{
				circleArray[0][z].color = 'g';
				circleArray[0][z-1].color = 'r';
				z= 0;//get out of the for loop
			}
			else if (circleArray[0][z].color == 'b')
			{
				circleArray[0][z].color = 'g';
				circleArray[0][z-1].color = 'b';
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
					circleArray[z][m].color = 'g';
					circleArray[z+1][m].color = 'r';
					
					gameArray[z-1][m] = 0;
					gameArray[z][m]= 1;
					circleArray[0][0].color = 'b';//change turn
				
				}
				
			
				
				
			}
			else if (circleArray[z][m].color == 'b')
			{
				if(gameArray[z][m] == 0)
				{
					circleArray[z][m].color = 'g';
					circleArray[z+1][m].color = 'b';
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
