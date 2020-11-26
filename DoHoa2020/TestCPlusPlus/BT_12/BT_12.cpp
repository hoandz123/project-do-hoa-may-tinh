//bầu trời đầy sao chuyển trái phải
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include <math.h>
#include <gl\GL.h>
#define PI 3.14159265358979323846
#define STEPS 40
#define MAX_STARS 300

const int screenWidth = 640;
const int screenHeight = 480;

typedef struct star
{
	GLint x, y;
	GLint radius;
	GLint velocity;
	GLfloat intensity;
} STAR;

STAR sky[MAX_STARS];

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
}
void glCircle(GLint x, GLint y, GLint radius)
{
	GLfloat twicePi = (GLfloat)2.0f * PI;
	glBegin(GL_TRIANGLE_FAN);
	glVertex2i(x, y);
	for (int i = 0; i <= STEPS; i++) {
		glVertex2i((GLint)(x + (radius * cos(i * twicePi / STEPS)) + 0.5), (GLint)(y + (radius * sin(i * twicePi / STEPS)) + 0.5));
	}
	glEnd();
}

void skyInit()
{
	for (int i = 0; i < MAX_STARS; i++) {
		sky[i].x = rand() % screenWidth;
		sky[i].y = rand() % screenHeight;
		sky[i].radius = 1 + rand() % 3;
		sky[i].intensity = sky[i].radius / 3.0f;
		sky[i].velocity = sky[i].radius * 2 + rand() % 3;
	}
}

void skyDraw()
{
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	for (int i = 0; i < MAX_STARS; i++) {
		glColor3f(sky[i].intensity, sky[i].intensity, sky[i].intensity);
		glCircle(sky[i].x, sky[i].y, sky[i].radius);
	}
}
void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);

	glPushMatrix();
	skyDraw();
	glPopMatrix();
	glutSwapBuffers();
}
void update()
{
	for (int i = 0; i < MAX_STARS; i++)
	{
		//dòng này dùng để di chuyển từ phải sang trái.
		//nếu sửa thành dấu + và x > Max_STARS và sky[i].x = 0 thì sẽ đi từ trái sang phải
		sky[i].x -= sky[i].velocity;
		if (sky[i].x < 0) {
			sky[i].x = screenWidth;
			sky[i].y = rand() % screenHeight;
			sky[i].radius = 1 + rand() % 3;
			sky[i].intensity = sky[i].radius / 3.0f;
			sky[i].velocity = sky[i].radius * 2 + rand() % 3;

		}
	}
	Sleep(50);
	glutPostRedisplay();
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
	glutCreateWindow("Stary Night"); // tên của window là ‘rectangle’ 
	init(); // khởi tạo một số chế độ đồ họa 
	skyInit();
	glutDisplayFunc(display); // thiết lập hàm vẽ là hàm display() 
	glutReshapeFunc(reshape);
	glutIdleFunc(update);
	glutMainLoop(); // bắt đầu chu trình lặp thể hiện vẽ 
	return 0;
}