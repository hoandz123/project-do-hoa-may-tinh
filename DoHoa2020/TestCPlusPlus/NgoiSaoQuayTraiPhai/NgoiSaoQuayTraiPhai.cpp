#include "Dependencies/glew/glew.h"
#include "Dependencies/freeglut/freeglut.h"

#include<math.h>

#define PI 3.14159
#define Radius 200
#define width 500
#define height 500
static GLfloat quay = 0.0;
void display(void)
{
	//int R;
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	GLfloat step = 3.14 / 5.0;

	glRotatef((GLfloat)quay, 0.0, 0.0, 1.0);
	register int i;
	GLfloat angle, r;
	glBegin(GL_LINE_LOOP);
	for (i = 0; i < 10; ++i)
	{
		r = (i % 2 == 0 ? 5 : 15);
		angle = i * step;
		glVertex3f(r * cos(angle), r * sin(angle), 0.0);
	}
	glEnd();
	glFlush();
}

//void keyboard(unsigned char key, int x, int y)
//{
//	switch (key) {
//	case 'm':
//		quay = (quay + 100) % 360;
//
//		glutPostRedisplay();
//		break;
//
//
//	default:
//		break;
//	}
//}
void spinDisplay(void)
{
	quay = quay + 2.0;
	/*if (quay > 360.0)
	{
		quay = quay - 360.0;	
	}*/
	Sleep(100);
	glutPostRedisplay();
}
void Mouse(int button, int state, int x, int y)
{
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)
			glutIdleFunc(spinDisplay);
		break;
	case GLUT_MIDDLE_BUTTON:
		if (state == GLUT_DOWN)
			glutIdleFunc(NULL);
		break;
	default:
		break;
	}

}
//void Moue(int button, int state, int x, int y)
//{
//	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
//	{
//		quay = (quay + 5) % 360;
//		glutPostRedisplay();
//	}
//}
void init(void) {
	//glClearColor(0.0,0.0,0.0,0.0);
	///glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//glOrtho(0.0,1.0,0.0,1.0,-1.0,1.0);
	GLdouble hW, hH;
	glClearColor(0.0, 0.0, 0.0, 0.0);
	hW = (GLdouble)width / 20.0;
	hH = (GLdouble)height / 20.0;
	gluOrtho2D(-hW, hW, -hH, hH);

}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(width, height);
	//glutInitWindowPosition(100,200);
	glutCreateWindow("hello");
	init();
	glutDisplayFunc(display);
	//glutKeyboardFunc(keyboard);
	glutMouseFunc(Mouse);
	glutMainLoop();
	return 0;
}