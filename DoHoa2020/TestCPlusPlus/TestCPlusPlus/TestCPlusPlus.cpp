//vẽ 4 chấm vuông
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"


const int screenWidth = 640;
const int screenHeight = 480;

void init(void)
{
	//màu background là màu đen
	glClearColor(0.0, 0.0, 0.0, 0.0);
	//Flat là tô màu đều 1 màu, k có đậm nhạt sáng tối
	glShadeModel(GL_FLAT);
}
void display()
{
	//lấy cây cọ chấm vô
	glClear(GL_COLOR_BUFFER_BIT);
	//màu trắng
	glColor3f(1.0, 1.0, 1.0);
	//kích thước của cái chấm đó
	glPointSize(5.0);

	glBegin(GL_POINTS);//3f là kiểu float
		glVertex3f(200.0, 120.0, 0.0);
		glVertex3f(440.0, 120.0, 0.0);
		glVertex3f(440.0, 360.0, 0.0);
		glVertex3f(200.0, 360.0, 0.0);
	glEnd();
	//vẽ lên màn hình
	glFlush();
}

//hàm để vẽ lại hình khi có chạy lại
void reshape(int w, int h)
{
	//0, 0 là vẽ lại toàn bộ cái khung cảnh
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);
}
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(screenWidth, screenHeight);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Point");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}


