/* Clinton Rogers */



#include <windows.h> // use proper includes for your system
#include <math.h>
#include <gl/Gl.h>
#include <gl/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/***************************Begin struct declarations***********************************************/
typedef struct
{
	float x;
	float y;
	float z;
}Vertex3f;

typedef struct
{
	short r;
	short g;
	short b;
}Color3ub;

typedef struct
{
	short totalVertexPoints;
	short *vertexIndex;	/*array (size of vertexPoints)of index positions pointing to vertex points*/
}Facet;

typedef struct
{
	float u;
	float v;
}UVMap;

typedef struct
{
	/*PLY model format, more info see http://local.wasp.uwa.edu.au/~pbourke/dataformats/ply/*/
	
	Vertex3f *vertex;	/*
						an array of vertex points that make up the model, size determined at
						at file-load time.
						*/
	Color3ub *color;	/*
						an array of colors, each one matching up 1:1 for each vertex point above
						*/
	Vertex3f *normal;	/*
						an array of normals, each one matching up 1:1 with each vertex point
						*/
	Facet *faces;		/*
						an array of facets that make up the model, these point to which vertex
						point to use from *vertex;
						*/
	UVMap *map;			/*
						an array of u/v coordinates to map an image to the model as specific
						vertex points
						*/
	short totalVertexPoints;
	short totalFacets;
	bool hasColor;
	bool hasNormals;
	bool hasUVMap;
}PLYModel;
/***************************End struct declarations*************************************************/

/***************************Begin procedure declarations********************************************/
void drawPLYModel(PLYModel *model);
void drawPLYModelCircle(PLYModel *model);
void display(void);
void reshape (int w, int h);
void keyboard (unsigned char key, int x, int y);
void camera(void); 
void mouseMovement(int x, int y);
PLYModel *loadPLYModel(char *filename);
/***************************End procedure declarations**********************************************/

/***************************Global variable declarations********************************************/
PLYModel *monkey;
PLYModel *circle; 
float rotate = 0;
float xpos = 0, ypos = 0, zpos = 0, xrot = 0, yrot = 0, angle=0.0;

float lastx, lasty;
float positionz;
float positionx;
float cRadius = 10.0f;
bool turn = false;
bool turn2 = false; 
bool drop = false; 
float xPosCircle = -3.0;
float yPosCircle = 3.0; 
/***********************End Global variable declarations********************************************/

int main(int argc, char* argv[])
{
	int width = 1000;
	int height =700;
	monkey = loadPLYModel("cube6.ply");
	circle = loadPLYModel("circle.ply"); 

	glutInit(&argc,argv);
	glutInitDisplayMode (GLUT_DOUBLE );
	glutInitWindowSize (width, height);
	glutInitWindowPosition (100, 100);
	glutCreateWindow("Connect Four Game"); 

	glutDisplayFunc(display);
	glutIdleFunc (display);
	//glViewport(0, 0, width, height);

	glutReshapeFunc (reshape);
	glutKeyboardFunc (keyboard);
	glutMainLoop();
	/*
    glMatrixMode(GL_PROJECTION);
    //glLoadIdentity();
    gluPerspective(90.0f, (GLfloat)width/(GLfloat)height, 1.0f, 1000.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	*/

	
	 //reshape the window accordingly
//glutPassiveMotionFunc(mouseMovement); 
     //check the keyboard
	

	return 0;
}


void drawPLYModel(PLYModel *model)
{
	int x,y, index;

	glPushMatrix();
	
	
	glTranslatef(0.0, -5.0, -20.0);
	if (turn== true)
		glRotatef(angle,0.0,1.0,0.0);
	if (turn2 == true)
		glRotatef(-angle,0.0,1.0,0.0);

	
	glColor3f(0.0,0.0,1.0); 
	
	for(x=0; x<model->totalFacets;x++)
	{
		glBegin(GL_POLYGON);
		for(y=0;y<model->faces[x].totalVertexPoints;y++)
		{
			index = model->faces[x].vertexIndex[y];
			//if(model->hasColor)
				//glColor3ub(model->color[index].r,model->color[index].g,model->color[index].b);
			if(model->hasNormals)
				glNormal3f(model->normal[index].x,model->normal[index].y,model->normal[index].z);
			glVertex3f(model->vertex[index].x,model->vertex[index].y,model->vertex[index].z);

		}
		glEnd();
	}

	glPopMatrix();
 glutSwapBuffers();
}
void drawPLYModelCircle(PLYModel *model)
{
	int x,y, index;
	/*glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();*/
	//glRotatef(180.0,0.0,1.0,0.0);
	glPushMatrix();
	
	//glRotatef(angle,0.0,1.0,0.0);
	
	glTranslatef(xPosCircle, yPosCircle, -120.0);
	//glRotatef(angle,0.0,1.0,0.0);
	
	glColor3f(1.0,0.0,0.0); 
	
	for(x=0; x<model->totalFacets;x++)
	{
		glBegin(GL_POLYGON);
		for(y=0;y<model->faces[x].totalVertexPoints;y++)
		{
			index = model->faces[x].vertexIndex[y];
			//if(model->hasColor)
				//glColor3ub(model->color[index].r,model->color[index].g,model->color[index].b);
			if(model->hasNormals)
				glNormal3f(model->normal[index].x,model->normal[index].y,model->normal[index].z);
			glVertex3f(model->vertex[index].x,model->vertex[index].y,model->vertex[index].z);

		}
		glEnd();
	}

	glPopMatrix();
	glutSwapBuffers();
}
void display(void)
{
	glClearColor(0.0,0.0,0.0,1.0); 
	glClear(GL_COLOR_BUFFER_BIT); 
	glLoadIdentity();
	gluLookAt(0.0,0.0,5.0,0.0,0.0,0.0,0.0,1.0,0.0); 
	camera();

	
	drawPLYModel(monkey);
	drawPLYModelCircle(circle); 
	glutSwapBuffers();
	 
	
	/* flush GL buffers */
	//glFlush();
	 if (angle < 180 && turn == true)
		angle+=0.2; 
	 if(angle >0 && turn2 == true)
		 angle-=0.2; 
}
PLYModel *loadPLYModel(char *filename)
{
	FILE *modelFile;
	PLYModel *temp;
	char tempString[100];
	int tempInt, x, y;
	float tempFloat;

	modelFile = fopen (filename,"r");
	if(modelFile==NULL)
	{
		printf("Error: can't open file in loadPLYModel %s\n",filename);
		return NULL;
	}

	/*Allocate space for a new model, if at any point loading the model fails, free this*/
	temp = (PLYModel *)malloc(sizeof(PLYModel));

	/*Identify this is inface a ply model file*/
	fscanf(modelFile,"%s",tempString);
	if(strcmp(tempString,"ply")!=0)
	{
		printf("Error: not valid ply file in loadPLYModel %s\n",filename);
		free(temp);
		return NULL;
	}

	/*read strings until we get "element"*/
	while(strcmp(tempString,"element")!=0)
		fscanf(modelFile,"%s",tempString);

	/*make sure the next string is vertex*/
	fscanf(modelFile,"%s",tempString);
	if(strcmp(tempString,"vertex")!=0)
	{
		printf("Error:loadPLYModel %s expected vertex, got %s\n",filename,tempString);
		free(temp);
		return NULL;
	}

	/*Get number of vertex points.*/
	fscanf(modelFile,"%d",&tempInt);
	temp->totalVertexPoints = tempInt;

	/*Allocate space for vertex points to be read later*/
	temp->vertex = (Vertex3f *)malloc(sizeof(Vertex3f)* tempInt);

	/*Allocate space for normals to be read later*/
	temp->normal = (Vertex3f *)malloc(sizeof(Vertex3f)* tempInt);

	/*Allocate space for colors to be read later*/
	//temp->color = (Color3ub *)malloc(sizeof(Color3ub)* tempInt);

	/*Get property type*/
	fscanf(modelFile,"%s",tempString);
	while(strcmp(tempString,"property")==0)
	{
		/*read data type and ignore*/
		fscanf(modelFile,"%s",tempString);

		/*read point type*/
		fscanf(modelFile,"%s",tempString);

		if(strcmp(tempString,"nx"))
			temp->hasNormals;
		else
		if(strcmp(tempString,"red"))
			temp->hasNormals;
		/*else
		if(strcmp(tempString,""))
			temp->hasUVMap;
		you must add in code to read for UVMaps if desired.
		*/
		fscanf(modelFile,"%s",tempString);
	}

	/*At this point we have a string that SHOULD be element*/
	if(strcmp(tempString,"element")!=0)
	{
		printf("Error:loadPLYModel %s expected element, got %s\n",filename,tempString);
		free(temp);
		return NULL;
	}

	/*At this point we have a string that SHOULD be face*/
	fscanf(modelFile,"%s",tempString);
	if(strcmp(tempString,"face")!=0)
	{
		printf("Error:loadPLYModel %s expected face, got %s\n",filename,tempString);
		free(temp);
		return NULL;
	}

	/*read in the face count*/
	fscanf(modelFile,"%d",&tempInt);
	temp->totalFacets = tempInt;
	temp->faces = (Facet *)malloc(sizeof(Facet)* tempInt);

	/*read until we read the end of the header*/
	while(strcmp(tempString,"end_header")!=0)
		fscanf(modelFile,"%s",tempString);

	/*Now read all the vertex points and their corresponding data*/
	for(x=0;x<temp->totalVertexPoints;x++)
	{
		fscanf(modelFile,"%f",&tempFloat);
		temp->vertex[x].x = tempFloat;
		fscanf(modelFile,"%f",&tempFloat);
		temp->vertex[x].y = tempFloat;
		fscanf(modelFile,"%f",&tempFloat);
		temp->vertex[x].z = tempFloat;

		if(temp->hasNormals)
		{
			fscanf(modelFile,"%f",&tempFloat);
			temp->normal[x].x = tempFloat;
			fscanf(modelFile,"%f",&tempFloat);
			temp->normal[x].y = tempFloat;
			fscanf(modelFile,"%f",&tempFloat);
			temp->normal[x].z = tempFloat;
		}

		/*if(temp->hasColor)
		{
			fscanf(modelFile,"%d",&tempInt);
			temp->color[x].r = tempInt;
			fscanf(modelFile,"%d",&tempInt);
			temp->color[x].g = tempInt;
			fscanf(modelFile,"%d",&tempInt);
			temp->color[x].b = tempInt;
		}*/
	}

	/*Now read all face data*/
	for(x=0;x<temp->totalFacets;x++)
	{
		/*Read total points*/
		fscanf(modelFile,"%d",&tempInt);
		temp->faces[x].totalVertexPoints = tempInt;

		/*Allocate the space*/
		temp->faces[x].vertexIndex = (short *)malloc(sizeof(short)*tempInt);

		/*Read the index points of the face*/
		for(y=0; y<temp->faces[x].totalVertexPoints;y++)
		{
			fscanf(modelFile,"%d",&tempInt);
			temp->faces[x].vertexIndex[y] = tempInt;
		}

	}

	/*Fin*/
	return(temp);
}
void keyboard (unsigned char key, int x, int y) {
    if (key=='q')
    {

	  angle = 0; 
	  turn = true; 
    if (xrot >360) xrot -= 360;
    }

    if (key=='z')
    {
		//angle = 0; 
		turn = false; 
	   turn2 = true; 
    if (xrot < -360) xrot += 360;
    }

    if (key=='l')
    {
     xPosCircle +=2; 
	 if(xPosCircle == 7)
		 xPosCircle -=10; 
    }

    if (key=='k')
    {
	  xPosCircle -=2;
	  if(xPosCircle == -3)
		  xPosCircle += 6; 
    }

    if (key=='d')
    {
	
	 yPosCircle -= 5;  

	
	
	 
    if (yrot >360) yrot -= 360;
    }

    if (key=='a')
    {
    yrot -= 1;
    if (yrot < -360)yrot += 360;
    }
    if (key==27)
    {
    exit(0);
    }
}
void reshape (int w, int h) {
    glViewport (0, 0, (GLsizei)w, (GLsizei)h); //set the viewportto the current window specifications
    glMatrixMode (GL_PROJECTION); //set the matrix to projection

    glLoadIdentity ();
    gluPerspective (60, (GLfloat)w / (GLfloat)h, 1.0, 100.0); //set the perspective (angle of sight, width, height, , depth)
    glMatrixMode (GL_MODELVIEW); //set the matrix back to model

}
void camera (void) {
    glRotatef(xrot,1.0,0.0,0.0);  //rotate our camera on teh x-axis (left and right)
    glRotatef(yrot,0.0,1.0,0.0);  //rotate our camera on the y-axis (up and down)
    glTranslated(-xpos,-ypos,-zpos); //translate the screento the position of our camera
	
}

void mouseMovement(int x, int y) {
    int diffx=x-lastx; //check the difference between the current x and the last x position
    int diffy=y-lasty; //check the difference between the current y and the last y position
    lastx=x; //set lastx to the current x position
    lasty=y; //set lasty to the current y position
    xrot -= (float) diffy; //set the xrot to xrot with the additionof the difference in the y position
    yrot -= (float) diffx;    //set the xrot to yrot with the additionof the difference in the x position
}