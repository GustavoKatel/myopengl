#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
//­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­
void free_mem(void)
{
	std::clog << "Exiting...\n";
}
//­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­
void display(void)
{
	//MatrixMode(GL_MODELVIEW);
	glLoadIdentity();
//	glRotatef(180,1,0,0);
	
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, 512, 512);
	glOrtho(-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f);
	glColor3f(1.0f, 1.0f, 1.0);
	// Alterar o trecho abaixo para desenhar os pontos, linhas e triângulos 
	gluLookAt( 0.0f, 0.0f, 0.1f,  // posição da câmera
		   0.0f, 0.0f, 0.0f,  // ponto para o qual a camera está olhando
		  0.0f, 1.0f, 0.0f); // vetor "up"

	// a serem utilizados nas comparações.
	glBegin(GL_LINES);
	// linha 1
	glVertex3f(-0.5,-0.5, 0.0);
	glVertex3f( 0.5, 0.5, 0.0);
	//
	glEnd();
	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
}
//­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­­
int main(int argc, char **argv)
{
	std::clog << "Begin...\n";
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(512, 512);
	glutInitWindowPosition(100,100);
	glutCreateWindow("OpenGL: Line Drawing Reference");
	glutDisplayFunc(display);
	atexit(free_mem);
	glutMainLoop();
	return 0;
}
