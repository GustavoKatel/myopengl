#include "transformations.h"

#include <iostream>

#include <math.h>

void mygl_scale(Matrix *m, float sx, float sy, float sz)
{
	Matrix	s;
	s.load_identity();
	s.put(0,0,sx);
	s.put(1,1,sy);
	s.put(2,2,sz);
	s.put(3,3,1.0);
	*m = (*m)*s;
}   

void mygl_translate(Matrix *m, float dx, float dy, float dz)
{
	Matrix	s;
	s.load_identity();
	s.put(0,3,dx);
	s.put(1,3,dy);
	s.put(2,3,dz);
	s.put(3,3,1.0);
	*m = (*m)*s;
}

void mygl_rotate(Matrix *m, float ang, int x, int y, int z)
{
	Matrix s, t;
	s.load_identity();
	float rad_ang = (M_PI/180)*ang;
	if(x)
	{
		t.load_identity();
		t.put(1,1,cos(rad_ang));
		t.put(1,2,-sin(rad_ang));
		t.put(2,1,sin(rad_ang));
		t.put(2,2,cos(rad_ang));	
		s = s*(t);
	}
	if(y)
	{
		t.load_identity();
		t.put(0,0,cos(rad_ang));
		t.put(0,2,sin(rad_ang));
		t.put(2,0,-sin(rad_ang));
		t.put(2,2,cos(rad_ang));	
		s = s*(t);
	}
	if(z)
	{
		t.load_identity();
		t.put(0,0,cos(rad_ang));
		t.put(0,1,-sin(rad_ang));
		t.put(1,0,sin(rad_ang));
		t.put(1,1,cos(rad_ang));	
		s = s*(t);
	}
//	s.print();
	*m = (*m)*s;
}

void mygl_shear_x(Matrix *m, float a, float b)
{
	Matrix s;
	s.load_identity();
	s.put(1,0,a);
	s.put(2,0,b);
	*m = (*m)*s;
}

void mygl_shear_y(Matrix *m, float a, float b)
{
	Matrix s;
	s.load_identity();
	s.put(0,1,a);
	s.put(2,1,b);
	*m = (*m)*s;
}

void mygl_shear_z(Matrix *m, float a, float b)
{
	Matrix s;
	s.load_identity();
	s.put(0,2,a);
	s.put(1,2,b);
	*m = (*m)*s;
}
