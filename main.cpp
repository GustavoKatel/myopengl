#include "main.h"

//-----------------------------------------------------------------------------
void MyGlDraw(void)
{
	initMatrices();
//	mygl_rotate(_model,180,0,0,1);
	Vector *pos =  new Vector( 0.0, 0.0, 0.1),
		*dir = new Vector( 0.0, 0.0, 0.0),
		*up =  new Vector( 0.0, 1.0, 0.0);
	mygl_look_at(pos,
		     dir,
		     up);
	//*************************************************************************
	// Chame aqui as funções do mygl.h
	//*************************************************************************
	tCor *cor = new tCor();
	cor->r=255;
	cor->g=255;
	cor->b=0;
	cor->a=255;
	//
	Vector v1(-0.5,-0.5,0);
	Vector v2(0.5,0.5,0);
	//
	int x, y;
	getWindowCoord(&v2,&x,&y);
	std::cout<<"x: "<<x<<" y: "<< y << std::endl;
	exit(1);
	//
	DrawLine(&v1,&v2,cor);
	//
}

//-----------------------------------------------------------------------------
int main(int argc, char **argv)
{
	// Inicializações.
	InitOpenGL(&argc, argv);
	InitCallBacks();
	InitDataStructures();

	// Ajusta a função que chama as funções do mygl.h
	DrawFunc = MyGlDraw;	

	// Framebuffer scan loop.
	glutMainLoop();

	return 0;
}

