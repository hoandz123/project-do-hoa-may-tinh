// Lab05_1711061181.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include  "Dependencies\glew\glew.h"
#include  "Dependencies\freeglut\freeglut.h" 
#include <stdio.h> 
#include <stdlib.h> 
#include "until.h"
#include "SHADER.h" 	

#ifdef _MSC_VER                           /* for MSVC */ 
#   pragma comment (lib, "opengl32.lib") 
#   pragma comment (lib, "glu32.lib") 
#   pragma comment (lib, "glew32.lib") 
#   pragma comment (lib, "freeglut.lib") 
#endif 

#define WND_WIDTH   640                     /* chieu rong cua so */ 
#define WND_HEIGHT  360                     /* chieu cao cua so */ 
#define WND_TITLE   "Lab05-Bai01"               /* tieu de */ 
#define VS_FILE     "VERTEX.glsl"           /* tap tin ma nguon vertex shader */
#define FS_FILE     "fragment.glsl"         /* tap tin ma nguon fragment shad  */

typedef enum objectMode { CUBE, SPHERE, TORUS, TEAPOT } OBJECT_MODE;

//Cac bien toan cuc
float xAngle = 0.0f;  //Cac goc xoay vat the
float yAngle = 0.0f;
float zAngle = 0.0f;
int xMotion = 0; //Theo doi chuyen dong chuot
int yMotion = 0;

GLSL_PROGRAM* prog = NULL;  //Chuong trinh shader 
OBJECT_MODE obj = TEAPOT;   //Vat the hien thi hien thoi

void resize(int width, int height) //Thay doi kich thuoc cua so
{ 
	if (height == 0) height = 1;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, width, height);
	gluPerspective(45.0f, (float)width / height, 1.0f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
}

void render() //Dung hinh 
{ 
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0.0f, 0.0f, 4.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	glRotatef(xAngle, 1.0f, 0.0f, 0.0f);
	glRotatef(yAngle, 0.0f, 1.0f, 0.0f);
	glRotatef(zAngle, 0.0f, 0.0f, 1.0f);

	switch (obj) 
	{
		case CUBE:      glutSolidCube(1.5f); break;
		case SPHERE:    glutSolidSphere(1.0f, 24, 24); break;
		case TORUS:     glutSolidTorus(0.5, 1.0f, 24, 24); break;
		case TEAPOT:    glutSolidTeapot(1.0f); break;
	}
	glutSwapBuffers();
}

void input(unsigned char key, int x, int y) //Xu ly su kien tu ban phim
{
	switch (key) 
	{
		case 27: exit(0);
		case '1':   obj = CUBE;   break;
		case '2':   obj = SPHERE; break;
		case '3':   obj = TORUS;  break;
		case '4':   obj = TEAPOT; break;
		default:    break;
	}
}
void mouse(int button, int state, int x, int y) 
{ 
	if (state == 0 && button == 0) //Phim trai nhan
	{ 
		xMotion = x;
		yMotion = y;
	}
}

void motion(int x, int y) //Ham xu ly chuyen dong chuot
{
	if (xMotion) {
		if (xMotion > x) yAngle -= 2.0f;
		if (xMotion < x) yAngle += 2.0f;
		xMotion = x;
	}
	if (yMotion) {
		if (yMotion > y) xAngle -= 1.0f;
		if (yMotion < y) xAngle += 1.0f;
		yMotion = y;
	}
}

void idle() //ham xu ly thoi gian choi
{ 
	glutPostRedisplay();
}

GLboolean init(int argc, char** argv) 
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(-1, -1);
	glutInitWindowSize(WND_WIDTH, WND_HEIGHT);
	glutCreateWindow(WND_TITLE);
	glutDisplayFunc(render);
	glutIdleFunc(idle);
	glutReshapeFunc(resize);
	glutKeyboardFunc(input);
	glutMotionFunc(motion);
	glutMouseFunc(mouse);

	if (GLEW_OK != glewInit()) return GL_FALSE;
	if (!(prog = glslCreate())) printf("No GLSL supported.\n");
	glslCompileFile(prog, VERTEX_SHADER, VS_FILE);
	glslCompileFile(prog, FRAGMENT_SHADER, FS_FILE);
	glslLink(prog);
	glslActivate(prog);
	glEnable(GL_DEPTH_TEST);
	return GL_TRUE;
}

void done() 
{
	glslDestroy(prog);
}

void run() 
{
	glutMainLoop();
}

int main(int argc, char** argv) 
{
	init(argc, argv);
	run();
	return 0;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
