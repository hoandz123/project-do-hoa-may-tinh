#include "Dependencies/glew/glew.h"
#include "Dependencies/freeglut/freeglut.h"

const int screenWidth = 640;
const int screenHeight = 480;

GLfloat width = 500, height = 500;
GLfloat** material;
GLfloat light[3][3] = { {1,1,0}, {1,0.5,0}, {1,0,0} };


void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	//glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_VIEWPORT);
		glColor3f(1.0, 0.0, 0.0);
		glVertex2i(160, 80);
		glColor3f(0.0, 1.0, 0.0);
		glVertex2i(480, 80);
		glColor3f(0.0, 0.0, 1.0);
		glVertex2i(320, 400);
	glEnd();
	/*glBegin(GL_POINTS);
	glColor3f(1, 0, 0);
	glVertex2i(160, 80);
	glVertex3d(1, 2, 1);
	glVertex2i(480, 80);
	glVertex3d(2, 2, 1);
	glColor3f(1, 0, 1);
	glVertex2i(320, 400);
	glEnd();*/


	glutSolidTeapot(0.5);
	glFlush();
}

void reshape(int w, int h)
{
	int i = 0;
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_VIEWPORT);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(screenWidth, screenHeight);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}