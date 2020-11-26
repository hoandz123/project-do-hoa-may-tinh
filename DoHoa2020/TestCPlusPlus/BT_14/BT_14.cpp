#include <math.h>
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"


const int screenWidth = 640;
const int screenHeight = 480;
const double R = 150;
const double r = 75;
const double pi = 3.141592654;

struct GLdoublePoint
{
	GLdouble x;
	GLdouble y;
};

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glShadeModel(GL_FLAT);
}

//void drawRectangle(GLint x, GLint y, GLint width, GLint height)
//{
//	glBegin(GL_POLYGON);
//	glColor3f(1.0, 0.0, 1.0);
//	glVertex2i(x, y);
//	glColor3f(0.0, 1.0, 1.0);
//	glVertex2i(x + width, y);
//	glColor3f(1.0f, 1.0f, 0.0);
//	glVertex2i(x + width, y + height);
//	glColor3f(1.0f, 1.0f, 1.0f);
//	glVertex2i(x, y + height);
//	glEnd();
//
//}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(5.0);
	glColor3f(0.0f, 0.0f, 0.0f);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_POINTS);

	GLdoublePoint V1, V2, V3, V4, V5, V0, V6, V7, V8, V9, V10;
	V0.x = screenWidth / 2;
	V0.y = screenHeight / 2;
	V1.x = V0.x;
	V1.y = V0.y + R;
	V2.x = V0.x + R * sin(2 * pi / 5);
	V2.y = V0.y + R * cos(2 * pi / 5);
	V3.x = V0.x + R * sin(pi / 5);
	V3.y = V0.y - R * cos(pi / 5);
	V4.x = V0.x - R * sin(pi / 5);
	V4.y = V0.y - R * cos(pi / 5);
	V5.x = V0.x - R * sin(2 * pi / 5);
	V5.y = V0.y + R * cos(2 * pi / 5);
	//hình tròn 2 đối diện hình tròn 1
	V6.x = V0.x;
	V6.y = V0.y - r;
	V7.x = V0.x - r * sin(2 * pi / 5);
	V7.y = V0.y - r * cos(2 * pi / 5);
	V8.x = V0.x - r * sin(pi / 5);
	V8.y = V0.y + r * cos(pi / 5);
	V9.x = V0.x + r * sin(pi / 5);
	V9.y = V0.y + r * cos(pi / 5);
	V10.x = V0.x + r * sin(2 * pi / 5);
	V10.y = V0.y - r * cos(2 * pi / 5);

	glVertex2d(V1.x, V1.y);
	glVertex2d(V2.x, V2.y);
	glVertex2d(V3.x, V4.y);
	glVertex2d(V4.x, V4.y);
	glVertex2d(V5.x, V5.y);
	glVertex2d(V6.x, V6.y);
	glVertex2d(V7.x, V7.y);
	glVertex2d(V8.x, V8.y);
	glVertex2d(V8.x, V8.y);
	glVertex2d(V9.x, V9.y);
	glVertex2d(V10.x, V10.y);
	glEnd();

	glFlush();
}

void Reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(screenWidth, screenHeight); //optional
	glutInitWindowPosition(100, 100); //optional
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(Reshape);
	glutMainLoop();
	return 0;

}