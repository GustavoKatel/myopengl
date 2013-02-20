#include "main.h"
#include "objLoader.h"

// Ponteiro para o objeto que carregará o modelo 3D (formato OBJ).
objLoader *objData;

float angle = 1.0;

//-----------------------------------------------------------------------------
void MyGlDraw(void)
{
	for(int i=0;i<IMAGE_WIDTH*IMAGE_HEIGHT;i++)
	{
		FBptr[i*4]   = 0;
		FBptr[i*4+1] = 0;
		FBptr[i*4+2] = 0;
		FBptr[i*4+3] = 255;
	}
	initMatrices();
	//	mygl_rotate(_model,180,0,0,1);
	Vector *pos =  new Vector( 0.0, 0.0, 1.0),
	       *dir = new Vector( 0.0, 0.0,-1.0),
	       *up =  new Vector( 0.0, 1.0, 0.0);
	mygl_look_at(pos,
			dir,
			up);
	mygl_perspective(55.0, 1.0, 50.0f);
	mygl_rotate(_model, angle,0,1,0);
	mygl_rotate(_model,-angle,1,0,0);
	mygl_rotate(_model,angle/2,0,0,1);
//	angle+=1.0;
	//	mygl_rotate(_model, 45,1,0,0);
	//*************************************************************************
	// Chame aqui as funções do mygl.h
	//*************************************************************************
	//
	tCor cx(255, 0, 0);	// eixo X
	Vector vx1(0.0f, 0.0f, 0.0f);
	Vector vx2(2.0f, 0.0f, 0.0f);
	DrawLine(&vx1, &vx2, &cx);

	tCor cy(0, 255, 0);	// eixo Y
	Vector vy1(0.0f, 0.0f, 0.0f);
	Vector vy2(0.0f, 2.0f, 0.0f);
	DrawLine(&vy1, &vy2, &cy);

	tCor cz(0, 0, 255);	// eixo Z
	Vector vz1(0.0f, 0.0f, 0.0f);
	Vector vz2(0.0f, 0.0f, 2.0f);
	DrawLine(&vz1, &vz2, &cz);
	//
	tCor cor(255,255,255);
	for(int i=0;i<objData->faceCount;i++)
	{
		obj_face *o = objData->faceList[i];
		Vector vm1(	objData->vertexList[o->vertex_index[0]]->e[0], // primeira linha
				objData->vertexList[o->vertex_index[0]]->e[1],
				objData->vertexList[o->vertex_index[0]]->e[2]);
		Vector vm2(	objData->vertexList[o->vertex_index[1]]->e[0],
				objData->vertexList[o->vertex_index[1]]->e[1],
				objData->vertexList[o->vertex_index[1]]->e[2]);

		DrawLine(&vm1, &vm2, &cor);

		Vector vm3(	objData->vertexList[o->vertex_index[1]]->e[0],	// segunda linha
				objData->vertexList[o->vertex_index[1]]->e[1],
				objData->vertexList[o->vertex_index[1]]->e[2]);
		Vector vm4(	objData->vertexList[o->vertex_index[2]]->e[0],
				objData->vertexList[o->vertex_index[2]]->e[1],
				objData->vertexList[o->vertex_index[2]]->e[2]);

		DrawLine(&vm3, &vm4, &cor);

		Vector vm5(	objData->vertexList[o->vertex_index[2]]->e[0],	// terceira linha
				objData->vertexList[o->vertex_index[2]]->e[1],
				objData->vertexList[o->vertex_index[2]]->e[2]);
		Vector vm6(	objData->vertexList[o->vertex_index[0]]->e[0],
				objData->vertexList[o->vertex_index[0]]->e[1],
				objData->vertexList[o->vertex_index[0]]->e[2]);
		
		DrawLine(&vm5, &vm6, &cor);

	}
}

//-----------------------------------------------------------------------------
int main(int argc, char **argv)
{
	objData = new objLoader();			// cria o objeto que carrega o modelo
	objData->load("monkey_head2.obj");	// a carga do modelo é indicada atraves do nome do arquivo. 
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

