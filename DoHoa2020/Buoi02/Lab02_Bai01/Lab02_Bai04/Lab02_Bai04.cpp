#include "Dependencies/glew/glew.h"
#include "Dependencies/freeglut/freeglut.h"

void displayFunc(void)
{
	static float alpha = 0;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glTranslatef(0, 0, -10);
	//xoay theo trục x, x = 1
	glRotatef(30, 1, 0, 0);
	glRotatef(alpha, 0, 1, 0);
	glRotatef(alpha, 1, 0, 0);
	glBegin(GL_QUADS);

	glColor3f(0, 0, 0);
	glVertex3f(-1, -1, -1);
	glColor3f(0, 0, 1);
	glVertex3f(-1, -1, 1);
	glColor3f(0, 1, 1);
	glVertex3f(-1, 1, 1);
	glColor3f(0, 1, 0);
	glVertex3f(-1, 1, -1);

	glColor3f(1, 0, 0);
	glVertex3f(1, -1, -1);
	glColor3f(1, 0, 1);
	glVertex3f(1, -1, 1);
	glColor3f(1, 1, 1);
	glVertex3f(1, 1, 1);
	glColor3f(1, 1, 0);
	glVertex3f(1, 1, -1);

	glColor3f(0, 0, 0);
	glVertex3f(-1, -1, -1);
	glColor3f(0, 0, 1);
	glVertex3f(-1, -1, 1);
	glColor3f(1, 0, 1);
	glVertex3f(1, -1, 1);
	glColor3f(1, 0, 0);
	glVertex3f(1, -1, -1);

	glColor3f(0, 1, 0);
	glVertex3f(-1, 1, -1);
	glColor3f(0, 1, 1);
	glVertex3f(-1, 1, 1);
	glColor3f(1, 1, 1);
	glVertex3f(1, 1, 1);
	glColor3f(1, 1, 0);
	glVertex3f(1, 1, -1);

	glColor3f(0, 0, 0);
	glVertex3f(-1, -1, -1);
	glColor3f(0, 1, 0);
	glVertex3f(-1, 1, 1);
	glColor3f(1, 1, 0);
	glVertex3f(1, 1, -1);
	glColor3f(1, 0, 0);
	glVertex3f(1, -1, -1);

	glColor3f(0, 0, 1);
	glVertex3f(-1, -1, 1);
	glColor3f(0, 1, 1);
	glVertex3f(-1, 1, 1);
	glColor3f(1, 1, 1);
	glVertex3f(1, 1, 1);
	glColor3f(1, 0, 1);
	glVertex3f(1, -1, 1);

	glEnd();

	alpha = alpha + 0.1;

	glFlush();
	glutSwapBuffers();

	glutPostRedisplay();
}

void reshapeFunc(int width, int height)
{
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();
	gluPerspective(20, width / (float)height, 5, 15);
	glViewport(0, 0, width, height);

	glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();
}

void keyboardFunc(unsigned char key, int x, int y)
{
	int foo;

	foo = x + y;
	if ('q' == key || 'Q' == key || 27 == key)
		exit(0);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Spinning cube");

	glClearColor(0, 0, 0, 0);
	glEnable(GL_DEPTH_TEST);

	glutDisplayFunc(&displayFunc);
	glutReshapeFunc(&reshapeFunc);
	glutKeyboardFunc(&keyboardFunc);

	glutMainLoop();

	return 0;
}