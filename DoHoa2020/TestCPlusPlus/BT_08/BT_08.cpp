#include "Dependencies\glew/glew.h"
#include "Dependencies/freeglut/freeglut.h"
/* hàm thực hiện các thao tác vẽ theo yêu cầu của chương trình */
const int screenWidth = 640;
const int screenHeight = 480;
void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glShadeModel(GL_FLAT);
	//glShadeModel(GL_SMOOTH);
}

void display()
{
	/* xóa mọi pixel */
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	// vẽ hình vuông có tọa độ x - y

	glBegin(GL_TRIANGLES);
	glVertex2i(50, 50);
	glVertex2i(200, 50);
	glVertex2i(100, 150);

	glVertex2i(300, 100);
	glVertex2i(450, 150);
	glVertex2i(350, 250);

	glEnd();

	// thực hiện quá trình đẩy ra buffer
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
	glutCreateWindow(argv[0]); // tên của window là ‘rectangle’ 
	init(); // khởi tạo một số chế độ đồ họa 
	glutDisplayFunc(display); // thiết lập hàm vẽ là hàm display() 
	glutReshapeFunc(reshape);
	glutMainLoop(); // bắt đầu chu trình lặp thể hiện vẽ 
	return 0;
}