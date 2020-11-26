//Hình tròn tự tăng kích thước khi di chuyển
#include <iostream>
#include "Dependencies/glew/glew.h"
#include "Dependencies/freeglut/freeglut.h"

#include <math.h>
#define PI 3.14159f

char title[] = "Bouncing Ball (2D)";
int windowWidth = 640;
int windowHeight = 480;
int windowPosX = 50;
int windowPosY = 50;
bool bigger = true;

GLfloat ballRadius = 0.5f;
GLfloat ballX = 0.0f;
GLfloat ballY = 0.0f;
GLfloat ballXMax, ballXMin, ballYMax, ballYMin;
GLfloat xSpeed = 0.02f;
GLfloat ySpeed = 0.007f;
int refreshMillis = 30;
GLfloat XMin = 0.0f;

GLdouble clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop;

void init() {
	glClearColor(0.0, 0.0, 0.0, 1.0);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);   //xóa các pixel
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();									//đưa các ma trận về ma trận đơn vị

	glTranslatef(ballX, ballY, 0.0f);

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(0.0f, 0.0f);
	int numSegments = 100;
	GLfloat angle;

	for (int i = 0; i <= numSegments; i++) {
		angle = i * 2.0f * PI / numSegments;
		glVertex2f(cos(angle) * ballRadius, sin(angle) * ballRadius);
	}
	glEnd();

	glutSwapBuffers();
	if (bigger)
	{
		ballRadius += 0.005f;

	}

	else
	{
		ballRadius -= 0.005f;
	}

	if (ballRadius > 1.0f)
	{
		bigger = false;
		ballXMin = ballXMin - 0.05f;
		ballXMax = ballXMax - 0.05f;
		ballYMin = ballYMin - 0.05f;
		ballYMax = ballYMax - 0.05f;
	}
	if (ballRadius < 0.05f)
	{
		bigger = true;
		ballXMin = ballXMin + 0.05f;
		ballXMax = ballXMax + 0.05f;
		ballYMin = ballYMin + 0.05f;
		ballYMax = ballYMax + 0.05f;
	}

	ballXMin = clipAreaXLeft + ballRadius;
	ballXMax = clipAreaXRight - ballRadius;
	ballYMin = clipAreaYBottom + ballRadius;
	ballYMax = clipAreaYTop - ballRadius;

	ballX += xSpeed;
	ballY += ySpeed;

	if (ballX > ballXMax) {
		ballX = ballXMax;
		xSpeed = -xSpeed;

	}
	else if (ballX < ballXMin) {
		ballX = ballXMin;
		xSpeed = -xSpeed;

	}if (ballY > ballYMax) {
		ballY = ballYMax;
		ySpeed = -ySpeed;

	}
	else if (ballY < ballYMin) {
		ballY = ballYMin;
		ySpeed = -ySpeed;

	}
}

void reshape(GLsizei  width, GLsizei height) {
	if (height == 0) height = 1;
	GLfloat aspect = (GLfloat)width / (GLfloat)height;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (width >= height) {
		clipAreaXLeft = -1.0 * aspect;
		clipAreaXRight = 1.0 * aspect;
		clipAreaYBottom = -1.0;
		clipAreaYTop = 1.0;

	}
	else {
		clipAreaXLeft = -1.0;
		clipAreaXRight = 1.0;
		clipAreaYBottom = -1.0 / aspect;
		clipAreaYTop = 1.0 / aspect;
	}
	gluOrtho2D(clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop);
	ballXMin = clipAreaXLeft + ballRadius;
	ballXMax = clipAreaXRight - ballRadius;
	ballYMin = clipAreaYBottom + ballRadius;
	ballYMax = clipAreaYTop - ballRadius;

}

void Timer(int value) {

	glutPostRedisplay();
	glutTimerFunc(refreshMillis, Timer, 0);
}

void update() {
	for (int i = 0; i < 100; i++) {
		if (ballX >= windowWidth) {
			ballRadius = ballRadius * ballRadius - ballRadius;
		}

	}

}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);    //khởi tạo chế độ vẽ single buffer và hệ màu RGB
	glutInitWindowSize(windowWidth, windowHeight);   //khởi tạo window kích thước rộng, cao
	glutInitWindowPosition(windowPosX, windowPosY);				 //khởi tạo window tại ví trí (100, 100) trên màn hình
	glutCreateWindow(title);
	glutDisplayFunc(display);					     //gọi lại hàm thực hiện các thao tác
	glutReshapeFunc(reshape);						 //gọi lại hàm xử lý các thao tác
	glutTimerFunc(0, Timer, 0);
	init();
	//(update);
	glutMainLoop();									 //vòng lặp xử lý sự kiện chính của glut 
	return 0;
}