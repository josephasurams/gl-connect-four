#ifndef _GRAPHICS2D
#define _GRAPHICS2D
#include <string>
#include <iostream>
#include <fstream> 
#include <strstream> 
using namespace std; 
#include <windows.h> 
#include <assert.h> 
#include <math.h> 
#include <stdlib.h> 
#include <gl/Gl.h> 
#include <gl/Glu.h> 
#include <gl/glut.h>
 
class IntPoint{ 
// for 2D points with integer coordinates 
public:
	int x,y;
	void set(int dx, int dy){x = dx; y = dy;}
	void set(IntPoint& p){ x = p.x; y =p.y;}
	IntPoint(int xx, int yy){x = xx; y = yy;}
	IntPoint( ){x = y = 0;}
};



class Point2{ 
public:
	float x,y; 
	void set(float dx, float dy){x = dx; y = dy;}
	void set(Point2& p){ x = p.x; y = p.y;} 
	Point2(float xx, float yy){x = xx; y = yy;} 
	Point2(){x = y = 0;}
	float getX(void){return x;}
	float getY(void){return y;}
};



 class PolyLine
{// a polyline is a num plus an array of points 
 public: 
	 int num; 
	Point2 pt[80]; //may need larger arrays in some circumstanceS 
	PolyLine(){num = 0;}
};



  class IntRect
  {
  public: 
	  int left, top, right, bott; 
	  IntRect(){left = top = right = bott = 0;} 
	  IntRect(int l, int t, int r, int b){left = l; top = t; right = r; bott = b;} 
	  void set(int l, int t, int r, int b) {left = l; top = t; right = r; bott = b;} 
	  void set(IntRect& r) {left = r.left; top = r.top; right = r.right; bott= r.bott;}
  };






class Vector2
{
  public: 
	  float x,y; 
	  void set(float dx, float dy){ x = dx; y = dy; } 
	  void set(Vector2& v){ x = v.x; y = v.y;} 
	  void setDiff(Point2& a, Point2& b) {x = a.x - b.x; y = a.y - b.y;}


	  void normalize()	{
	double sizeSq = x * x + y * y;
	if(sizeSq < 0.0000001)
	{
		cerr << "\nnormalize() sees vector (0,0)!";
		return; // does nothing to zero vectors;
	}

	float scaleFactor = 1.0/(float)sqrt(sizeSq);
	x *= scaleFactor;
	y *= scaleFactor;
}

	  Vector2(float xx, float yy){x=xx; y=yy; }

	  Vector2(Vector2& v){x = v.x; y=v.y;}
	  Vector2(){x = y = 0;} //default constructor
	float dot(Vector2 b) // return this dotted with b
	{return x*b.x + y * b.y;}
	void perp()	// perp this vector
	{float tmp=x; x=-y; y=tmp;}
	float perpDot(Vector2& v)		
	{return x *v.x - y * v.y;}
};


//<<<<<<<<<<<<<<<<<<<< Canvas class >>>>>>>>>>>
//	a global Canvas object (described in Chapter 3) knows how
//to draw lines in world coordinates and to perform
//turtlegraphics
class Canvas 
{
	private:
		Point2 CP;	//current position in world
		float CD; // current direction in degrees
	public:
		float windowAspect;
		Canvas(int width, int height);
		void setWindow(float l, float r, float b, float t);
		void setViewport(int l, int r, int b, int t);
		float getWindowAspect(void) { return windowAspect;}
		void lineTo(float x, float y);
		void moveTo(float x, float y){CP.x = x; CP.y = y;}
		void turn(float ang) {CD += ang;}
		void turnTo(float ang) {CD = ang;}
		void forward(float dist, int vis);
		void initCT() // initialize the CT (model view matrix)
		{
			glMatrixMode(GL_MODELVIEW); glLoadIdentity();
		}
		void rotate2D(double angle)
		{
			glMatrixMode(GL_MODELVIEW); glRotated(angle, 0.0, 0.0, 1.0); 
		}
		void translate2D(double dx, double dy)
		{
			glMatrixMode(GL_MODELVIEW); glTranslated(dx, dy, 0.0); 
		}
		void scale2D(double sx, double sy)
		{
			glMatrixMode(GL_MODELVIEW); glScaled(sx, sy, 1.0);
		}
		void pushCT(void) 
		{
			glMatrixMode(GL_MODELVIEW); glPushMatrix();
		}
		void popCT(void)
		{
			glMatrixMode(GL_MODELVIEW); glPopMatrix(); 
		}
		void ngon(int n, float cx, float cy, float radius);

		void moveRel(float, float);
		void lineRel(float, float);

};

#endif
// end of graphics2d.h