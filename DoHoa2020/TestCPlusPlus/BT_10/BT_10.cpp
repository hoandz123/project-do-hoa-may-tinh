//bai 9 + 10 + 11 + 15(kích thước của hình tròn mỗi lần random khác nhau)
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include <math.h>
#define PI 3.14159265358979323846
#define STEPS 40

const int screenWidth = 640;
const int screenHeight = 480;
const double R = 150;
//const double pi = 3.14;

struct GLdoublePoint {
	GLdouble x;
	GLdouble y;
};

void glCircle(GLint x, GLint y, GLint radius) {
	GLfloat twicePi = (GLfloat)2.0f * PI;
	glBegin(GL_TRIANGLE_FAN);
	glVertex2i(x, y);
	for (int i = 0; i <= STEPS; i++) {
		glVertex2i((GLint)(x + (radius * cos(i * twicePi / STEPS)) + 0.5), (GLint)(y + (radius * sin(i * twicePi / STEPS)) + 0.5));
	}
	glEnd();
}

void init(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
};

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	GLfloat red = 1.0f;
	GLfloat green = 1.0f;
	GLfloat blue = 1.0f;

	//kích thước của mỗi vòng sẽ bị thay đổi ==> random
	for (int r = 250; r > 0; r -= (rand() % 60 + 1)) {
		glColor3f(red, green, blue);
		glCircle(320, 240, r);
		red -= 0.1f;
		green -= 0.2f;
		blue -= 0.3f;	
	}
	glFlush();
}

void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(screenWidth, screenHeight); // khởi tạo window kích thước 250 x 250 
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Tien Nguyen"); // tên của window là ‘rectangle’ 
	init(); // khởi tạo một số chế độ đồ họa 
	glutDisplayFunc(display); // thiết lập hàm vẽ là hàm display() 
	glutReshapeFunc(reshape);
	glutMainLoop(); // bắt đầu chu trình lặp thể hiện vẽ 
	return 0;
}