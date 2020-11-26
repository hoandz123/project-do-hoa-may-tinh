#include "Dependencies/glew/glew.h"
#include "Dependencies/freeglut/freeglut.h" 

#include <Math.h>
#define PI 3.14159265f

char title[] = "Bouncing Ball 2d";
int windowWidth = 640;
int windowHeight = 480;
int windowPosX = 50;
int windowPosY = 50;
bool bigger = true;

GLfloat ballRadius = 0.2f;
GLfloat ballX = 0.0f; //tọa độ tâm trái bóng
GLfloat ballY = 0.0f;

//tọa độ của quả bóng lớn nhất - nhỏ nhất khi chạm vào khung
GLfloat ballXMax, ballXMin, ballYMax, ballYMin;
//tốc độ di chuyển trái bóng
GLfloat xSpeed = 0.02f;
GLfloat ySpeed = 0.007f;

//số lần quét mỗi mili giây
int refreshMillis = 30;

GLdouble clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop;

void initGL()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT); //xóa các pixel
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(ballX, ballY, 0.0f);
	//dòng này chỉ để giảm hình tròn nhỏ dần
	//ballRadius = -(ballRadius * ballRadius - ballRadius);

	//đoạn này vẽ hình tròn từ những hình tam giác
	glBegin(GL_TRIANGLE_FAN); 
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex2f(0.0f, 0.0f);
		int numSegments = 100; //100 phần; 100 hình tam giác quạt quay vòng vòng
		GLfloat angle;
	
		for (int i = 0; i <= numSegments; i++) {
				angle = i * 2.0f * PI / numSegments;
				glVertex2f(cos(angle) * ballRadius, sin(angle) * ballRadius);
			
		}
	glEnd();

	//đoạn này xử lý hình tròn tự động tăng giảm
	glutSwapBuffers();
	if (bigger) {
		ballRadius += 0.005f;
	}
	else {
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
	//------------------------------------------------------

	ballX += xSpeed;
	ballY += ySpeed;

	if (ballX > ballXMax)
	{
		ballX = ballXMax;
		xSpeed = -xSpeed;	
	}
	else if (ballX < ballXMin)
	{
		ballX = ballXMin;
		xSpeed = -xSpeed;
	}
	if (ballY > ballYMax)
	{
		ballY = ballYMax;
		ySpeed = -ySpeed;
	}
	if (ballY < ballYMin)
	{
		ballY = ballYMin;
		ySpeed = -ySpeed;
	}
}

void reshape(GLsizei width, GLsizei height)
{
	if (height == 0) height = 1;
	//tỷ lệ màn hình
	GLfloat aspect = (GLfloat)width / (GLfloat)height;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (width >= height)
	{
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
	//dựa vào kích thước bóng để tinh lại min max
	ballXMin = clipAreaXLeft + ballRadius;
	ballXMax = clipAreaXRight - ballRadius;
	ballYMin = clipAreaYBottom + ballRadius;
	ballXMax = clipAreaYTop - ballRadius;
	
}

void Timer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(refreshMillis, Timer, 0);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition(windowPosX, windowPosY);
	glutCreateWindow(title);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutTimerFunc(0, Timer, 0);
	initGL();
	glutMainLoop();
	return 0;
}
