#ifndef _MYGL_H_
#define _MYGL_H_

#include "definitions.h"
#include <math.h>

#include "transformations.h"
#include "matrix.h"

/* ------------------- PIPELINE MATRIX ----------------------*/
Matrix *_window;
Matrix *_canonical;
Matrix *_projection;
Matrix *_view;
Matrix *_model;

void initMatrices()
{
	if(_window)
		delete _window;
	_window = new Matrix();
	_window->load_identity();
	//
	mygl_scale(_window,IMAGE_WIDTH/2,IMAGE_HEIGHT/2,1);
	//
	mygl_translate(_window,1.0,1.0,1.0);
	//
	mygl_scale(_window,1.0,-1.0,1.0);
	//
	//
	if(_model)
		delete _model;
	_model = new Matrix();
	_model->load_identity();
	//
	if(_view)
		delete _view;
	_view = new Matrix();
	_view->load_identity();
	//
	if(_projection)
		delete _projection;
	_projection = new Matrix();
	_projection->load_identity();
	//
	if(_canonical)
		delete _canonical;
	_canonical = new Matrix();
	_canonical->load_identity();
}

void mygl_look_at(Vector *pos, Vector *dir, Vector *up)
{
	Vector temp(dir->get(0) - pos->get(0), dir->get(1) - pos->get(1), dir->get(2) - pos->get(2) );
	temp.normalize();
	Vector zc = -(temp);
	//
	//
	temp = (*up)*zc;
	temp.normalize();
	Vector xc = temp;
	//
	temp =  zc * xc; 
	temp.normalize();
	Vector yc = temp;

	Matrix bT;
	bT.load_identity();
	bT.put(0,0,xc.get(0));
	bT.put(0,1,xc.get(1));
	bT.put(0,2,xc.get(2));
	//
	bT.put(1,0,yc.get(0));
	bT.put(1,1,yc.get(1));
	bT.put(1,2,yc.get(2));
	//
	bT.put(2,0,zc.get(0));
	bT.put(2,1,zc.get(1));
	bT.put(2,2,zc.get(2));
	//
	Matrix t;
	t.load_identity();
	t.put(0,3,-pos->get(0));
	t.put(1,3,-pos->get(1));
	t.put(2,3,-pos->get(2));
	//
	_view->load_identity();
	*_view = (*_view)*bT;
	*_view = (*_view)*t;
}

void mygl_perspective(float angle,float near, float far)
{
	_projection->load_identity();
	_projection->put(2,2, -(near+far)/near );
	_projection->put(2,3,far);
	_projection->put(3,2,-(1/near));
	//
	//
	float r = tan( (M_PI/180)*angle )*near;
	_canonical->load_identity();
	_canonical->put(0,0,1/(r));
	_canonical->put(1,1,1/(r));
	_canonical->put(2,2,2/(near-far));
	//
	_canonical->put(2,3, -(near+far)/(near-far) );

} 

void getWindowCoord(Vector *v, int *x, int *y)
{
	Vector c = *v;
	/* --- model to world space --- */
	c = (*_model)*c;
	/* --- world space to camera space -- */
	c = (*_view)*c;
	/* ---  camera to projection space --- */
	c = (*_projection)*c;
	//
	//
	/* --- projection to caninical space  --- */
	// homogeneous
	if(c.get(3))
	{
		c.put(0,c.get(0)/c.get(3));
		c.put(1,c.get(1)/c.get(3));
		c.put(2,c.get(2)/c.get(3));
	}
	c.put(3,1.0);
	//
	c = (*_canonical)*c;
	/* --- canonical to window space --- */
	c = (*_window)*c;
	*x = round(c.get(0));
	*y = round(c.get(1));
	//
}
/* ---------------- END PIPELINE MATRIX ----------------------*/

void invertPoint(int &xi, int &yi, int &xf, int &yf)
{
	int aux = xi;
	xi = xf;
	xf = aux;
	//
	aux = yi;
	yi = yf;
	yf = aux;
}
//
//*****************************************************************************
// Defina aqui as suas funções gráficas
//*****************************************************************************
class tCor
{
public:
	tCor(unsigned char r=0,unsigned char g=0, unsigned char b=0, unsigned char a=255)
	{
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}
	//
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
};
class tPixel : public tCor
{
public:
	unsigned int x;
	unsigned int y;
	tPixel()
	{
		r=0;
		g=0;
		b=0;
		a=255;
	}
};

void mygl_clear_color(tCor *cor)
{
	for(int i=0;i<IMAGE_WIDTH*IMAGE_HEIGHT;i++)
	{
		FBptr[i*4]   = cor->r;
		FBptr[i*4+1] = cor->g;
		FBptr[i*4+2] = cor->b;
		FBptr[i*4+3] = cor->a;
	}
}

void PutPixel(tPixel *pixel)
{
	if(pixel->x>IMAGE_WIDTH || pixel->x<0 || pixel->y>IMAGE_HEIGHT || pixel->y<0)
		return;
	//offset = x*4 + y*w*4
	unsigned int byte = pixel->x*4 + pixel->y*IMAGE_WIDTH*4;
	FBptr[byte]= pixel->r;
	FBptr[byte+1]=pixel->g;
	FBptr[byte+2]=pixel->b;
	FBptr[byte+3]=pixel->a;
	//
}

void DrawLine(Vector *v1, Vector *v2, tCor *cor)
{
	//
	int xi, yi;
	getWindowCoord(v1,&xi,&yi);

	int xf, yf;
	getWindowCoord(v2,&xf,&yf);
	//
	int dx=xf-xi;
	int dy=yf-yi;
	bool trans = false;
	if(abs(dy)>abs(dx))
	{	
		invertPoint(xi, xf, yi, yf);
		dx = xf-xi;
		dy = yf-yi;
		trans=true;
	}
	if(xi>xf)
	{
		invertPoint(xi, yi, xf, yf);
		dx = xf-xi;
		dy = yf-yi;
	}
	//
	//termo independente
	int c = -xi*yf + xf*yi;
	//coeficiente angular
	float cAng = (float)dy/dx;
	//ponto médio
	float mx = xi+1.0;
	float my = yi+( cAng>=0 ? 0.5 : -0.5 );
	//decisão
	float d = -dx*my + dy*mx + c;
	//define pixel
	tPixel *pixel = new tPixel;
	//define cor
	pixel->r = cor->r;
	pixel->g = cor->g;
	pixel->b = cor->b;
	pixel->a = cor->a;
	//
	int x,y=yi;
	for(x=xi;x<=xf;x++)
	{
		//define posição
		pixel->x = ( trans==true ? y : x );
		pixel->y = ( trans==true ? x : y );
		PutPixel(pixel);
		if(d>0)
		{//SE escolhido se cAng>=0, E escolhido se cAng<0
			if(cAng>=0)
			{
				y++;
				d-=dx;
			}
		}
		else
		{//E escolhido se cAng>=0, NE escolhido se cAng<0
			if(cAng<0)
			{
				y--;
				d+=dx;
			}
		}
		d+=dy;
	}
	delete pixel;
}

void DrawLineNoBresenham(Vector *v1, Vector *v2, tCor *cor)
{
	//
	int xi, yi;
	getWindowCoord(v1,&xi,&yi);

	int xf, yf;
	getWindowCoord(v2,&xf,&yf);
	//
	int dx=xf-xi;
	int dy=yf-yi;
	bool trans = false;
	if(abs(dy)>abs(dx))
	{	
		invertPoint(xi, xf, yi, yf);
		dx = xf-xi;
		dy = yf-yi;
		trans=true;
	}
	if(xi>xf)
	{
		invertPoint(xi, yi, xf, yf);
		dx = xf-xi;
		dy = yf-yi;
	}
	//termo independente
	int c = -xi*yf + xf*yi;
	//
	tPixel *pixel = new tPixel;
	pixel->r=cor->r;
	pixel->g=cor->g;
	pixel->b=cor->b;
	pixel->a=cor->a;
	for(int x=xi; x<xf; x++)
	{
		float y = (dy*x + c)/dx;
		if(trans)
		{
			pixel->x = y;
			pixel->y = x;
		}
		else
		{
			pixel->x=x;
			pixel->y=y;
		}
		PutPixel(pixel);
	}

}

void DrawTriangle(Vector *v1, Vector *v2, Vector *v3, tCor *cor)
{
	DrawLine(v1, v2, cor);
	DrawLine(v2, v3, cor);
	DrawLine(v3, v1, cor);
}


#endif // _MYGL_H_

