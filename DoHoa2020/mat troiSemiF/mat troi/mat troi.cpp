//#include "Dependencies\glew\glew.h"
//#include "Dependencies\freeglut\freeglut.h"
#include "Dependencies\freeglut\glut.h"

#include <math.h>
#include <sys/timeb.h>
#include <sys/utime.h>
static int rotate = 1;
static GLfloat spin = 0.0;
static int der = 0;
static int d = 2;
static float g_x = 1, g_y = 5, g_z = 1;
static int year = 0, day = 0, moon = 0; 
int getMilliCount() {
    timeb tb;
    ftime(&tb);
    int nCount = tb.millitm + (tb.time & 0xfffff) * 1000;
    return nCount;
}

void sleep(int sleeptime)
{
    int count = 0;
    int beginsleep = getMilliCount();
    while (getMilliCount() - beginsleep < sleeptime)
    {
        count++;
    }
}
void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_FLAT);
}
void draw()
{
    
    glBegin(GL_LINES);
    glColor3f(1.0, 1.0, 0.0);
    glVertex3f(-10.0, 0.0, 0.0);
    glVertex3f(10.0, 0.0, 0.0);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(0.0, -10.0, 0.0);
    glVertex3f(0.0, 10.0, 0.0);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, 0.0, -10.0);
    glVertex3f(0.0, 0.0, 10.0);
    glEnd();
}
void display(void) {
  
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(g_x, g_y, g_z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glPushMatrix(); 
    
    glColor3f (1.0, 0, 0); 
    //glutWireSphere(1.0, 20, 16);

    glutSolidSphere(1.0, 100, 100);
   
    glRotatef((GLfloat)year, 0.0, 1.0, 0.0); 
    glTranslatef (2.0, 0.0, 0.0);


    glRotatef ((GLfloat) day, 0.0, 1.0, 0.0); 
    glColor3f (0, 0, 1.0); 
    //glutWireSphere(0.2, 10, 8);
    glutSolidSphere(0.2, 50, 100);
   


    glRotatef((GLfloat)moon, 0.0, 12.0, 0.0);
    glTranslatef(0.5, 0.0, 0.0);

    glColor3f(1.0, 1.0, 1.0);
  
    glutSolidSphere(0.08, 10, 100);
    
    glPopMatrix();  
    draw();
   
    glutSwapBuffers();
    
}
int maxy = 1;
void calSC(double dec)
{
    g_x = 5 * sin(dec);
    g_z = 5 * cos(dec);
    g_y = g_y + 0.1*maxy;
    if (g_y > 7 || g_y < -7)
    {
        maxy *= -1;
    }
}
void spinDisplay(void)
{
    der += 10;
    calSC((double)der / 360);
    year = (year - rotate * d) % 360;
    day = (day - rotate * d) % 360;
    moon = (moon - rotate * d*12) % 360;
    int beginFrame = getMilliCount();

    glutPostRedisplay(); /* thông báo cho chương trình rằng: cần phải thực
   hiện việc vẽ lại */
    int timeDiff = getMilliCount() - beginFrame;
    if (timeDiff < 40) // 25FPS
    {
       sleep(40 - timeDiff);
    }
}


void reshape(int w, int h) {

    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();    
   // gluLookAt(2.0, 5.0, 5.0, 0.0, 0.0, 0.0, 1.0, 1.0, 0.0);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case '1':
            rotate = 1;
            spin = spin + 0.5;
            d = d + 0.2;
            glutIdleFunc(spinDisplay);
            break;       
        case '2':
            rotate = -1;
            spin = spin + 0.5;
            d = d + 0.2;
            glutIdleFunc(spinDisplay);
            break;
    default:          break;
    }
}

void keyStartEnd(unsigned char key, int x, int y)
{
    switch (key)
    {
      
    default:
        break;
    }
}; 

int main(int argc, char** argv)
{ 
    glutInit(&argc, argv);    
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);    
    
    glutInitWindowPosition(100, 100); 
    glutCreateWindow(argv[0]);   
    init();   
    glutDisplayFunc(display);  
    glutReshapeFunc(reshape);   
    glutKeyboardFunc(keyboard); 
    glutMainLoop();   
    return 0; 
}


