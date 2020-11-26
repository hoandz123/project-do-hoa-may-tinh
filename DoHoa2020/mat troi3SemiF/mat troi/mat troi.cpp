#include <iostream>
#include <windows.h>
#include "Dependencies/freeglut/glut.h"
#include <math.h>
#include <sys/timeb.h>
#include <sys/utime.h>



#define ktrang  0.05
#define kthuy  0.1
#define khoa  0.15
#define kkim  0.2
#define kdat 0.25
#define khv  0.3
#define ktv  0.35
#define ktho  0.4
#define kmoc  0.45


static int rotate = 1;
static GLfloat spin = 0.0;
static int der = 0;
static int d = 2;
static float g_x = 1, g_y = 5, g_z = 1;
static int year = 0, day = 0, moon = 0;
GLfloat  kim = 0.000 , thuy = 0.00, dat = 0.00, moc = 0.00, hoa = 0.00, tho = 0.00, tv = 0.00, hv = 0.00, mt = 0.00;
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
	glEnable(GL_DEPTH_TEST); // bật chức năng cho phép loại bỏ một phần của đối tượng bị che bởi đối tượng khác  

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);


	glShadeModel(GL_FLAT);



    GLfloat light_pos[] = { 0.0, 0.0, 1.0, 0.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

    GLfloat ambient[] = { 1.0, 0.0, 0.0, 1.0 };
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);

    GLfloat diff_use[] = { 0.0, 0.5, 0.0, 1.0 };
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff_use);

    GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);

    GLfloat shininess = 50.0f;
    glMateriali(GL_FRONT, GL_SHININESS, shininess);
}
void draw()
{
    
    glBegin(GL_LINES);
    glColor3f(1.0, 1.0, 0.0);
    glVertex3f(-50.0, 0.0, 0.0);
    glVertex3f(50.0, 0.0, 0.0);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(0.0, -50.0, 0.0);
    glVertex3f(0.0, 50.0, 0.0);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, 0.0, -50.0);
    glVertex3f(0.0, 0.0, 50.0);
    glEnd();
}

/* hàm vẽ */
void display(void) {

    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // xóa color buffer và  depth buffer
    glLoadIdentity();
    gluLookAt(g_x, g_y, g_z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glPushMatrix();  // lưu lại ma trận hiện hành
 
//-------------------------------------
     //printf_s("%f", thuy);
    //printf_s("\t");
       // printf_s("%f\n", kim);
    glColor3f (1.0, 0, 0);  // thiết lập màu vẽ là màu đỏ
    glutSolidSphere(1.0, 100, 100); //vẽ mặt trời tại tâm góc tòa độ 
    glRotatef(thuy, 0.0, 1.0, 0.0); // Sao Thủy quay quanh góc tọa độ
    glPushMatrix();// lưu góc tọa độ

    glTranslatef(2.0, 0.0, 0.0); // dời góc tọa độ đến vị trí mới để vẽ sao thuy từ vị trí tâm mặt trời
    glColor3f(1.0, 1.0, 1.0); // thiết lập màu trắng cho sao thuy 
    glutSolidSphere(kthuy, 50, 50); // vẽ sao thuy
    glPopMatrix();//quay về góc tọa độ củ là mặt trời
    glPushMatrix();// lưu góc tọa độ

    glRotatef(kim, 0.0, 1.0, 0.0); // Sao kim quay quanh mặt trời
    glTranslatef(3.0, 0.0, 0.0); // dời góc tọa độ đến vị trí mới để vẽ sao kim từ vị trí tâm mặt trời
    glColor3f(0, 1.0, 0); // thiết lập màu xanh lá cho sao kim
    glutSolidSphere(kkim, 50, 50); // vẽ sao kim

    glPopMatrix();//quay về góc tọa độ củ
    glRotatef(dat, 0.0, 1.0, 0.0); // trái đất quay quanh mặt trời
    glTranslatef(4.0, 0.0, 0.0);  // dời góc tọa độ đến vị trí mới để vẽ trái đất từ vị trí tâm mặt trời
    glColor3f(0, 0, 1.0); // thiết lập màu xanh cho trái đắt
    glutSolidSphere(kdat, 50, 50); // vẽ trái đất

    glRotatef(mt, 0.0, 1.0, 0.0); // mặt trăng quay quanh trái đất
    glColor3f(1.0, 1.0, 1.0); // thiết lập màu trắng cho mặt trăng
    glTranslatef(0.5, 0.0, 0.0);  // dời góc tọa độ đến vị trí mới để vẽ mặt trăng từ vị trái tâm trái đất
    glutSolidSphere(ktrang, 50, 50); // vẽ mặt trăng
    glPopMatrix();//quay về góc tọa độ củ là mặt trời
    glPushMatrix();// lưu góc tọa độ

    glRotatef(hoa, 0.0, 1.0, 0.0); // sao hỏa quay quanh mặt trời
    glTranslatef(5.0, 0.0, 0.0);  // dời góc tọa độ đến vị trí mới để vẽ sao hỏa từ vị trí tâm mặt trời
    glColor3f(1.0, 0, 0); // thiết lập màu đỏ cho sao hỏa
    glutSolidSphere(khoa, 50, 50); // vẽ sao hỏa
    glPopMatrix();//quay về góc tọa độ củ là mặt trời
    glPushMatrix();// lưu góc tọa độ

    glRotatef(moc, 0.0, 1.0, 0.0); // sao mộc quay quanh mặt trời
    glTranslatef(6.0, 0.0, 0.0);  // dời góc tọa độ đến vị trí mới để vẽ sao mộc từ vị trí tâm mặt trời
    glColor3f(1.0, 0, 1.0); // thiết lập màu vàng cho sao mộc
    glutSolidSphere(kmoc, 50, 50); // vẽ sao mộc
    glPopMatrix();//quay về góc tọa độ củ là mặt trời
    glPushMatrix();// lưu góc tọa độ

    glRotatef(tho, 0.0, 1.0, 0.0); // sao thổ quay quanh mặt trời
    glTranslatef(7.0, 0.0, 0.0);  // dời góc tọa độ đến vị trí mới để vẽ sao thổ từ vị trí tâm mặt trời
    glColor3f(1.0, 1.0, 0); // thiết lập màu vàng cho sao thổ
    glutSolidSphere(ktho, 50, 50); // vẽ sao thổ
    glPopMatrix();//quay về góc tọa độ củ là mặt trời
    glPushMatrix();// lưu góc tọa độ

    glRotatef(tv, 0.0, 1.0, 0.0); // sao thiên vương quay quanh mặt trời
    glTranslatef(8.0, 0.0, 0.0);  // dời góc tọa độ đến vị trí mới để vẽ sao thiên vương từ vị trí tâm mặt trời
    glColor3f(0, 1.0, 0); // thiết lập màu xanh lá cho sao thiên vương
    glutSolidSphere(ktv, 50, 50); // vẽ sao thiên vương
    glPopMatrix();//quay về góc tọa độ củ là mặt trời
    glPushMatrix();// lưu góc tọa độ

    glRotatef(hv, 0.0, 1.0, 0.0); // sao hải vương quay quanh mặt trời
    glTranslatef(9.0, 0.0, 0.0);  // dời góc tọa độ đến vị trí mới để vẽ sao hải vương từ vị trí tâm mặt trời
    glColor3f(0, 0, 1.0); // thiết lập màu xanh cho sao hải vương
    glutSolidSphere(khv, 50, 50); // vẽ sao hải vương


    glPopMatrix();  // phục hồi lại ma trận hiện hành cũ: tương ứng với quay lại vị trí ban đầu
    draw();
   
    glutSwapBuffers();
    
}
int maxy = 1;
void calSC(double dec)
{
    g_x = 5 * sin(dec);
    g_z = 5 * cos(dec);
    g_y = g_y + 0.1*maxy;
    if (g_y > 18 || g_y < -18)
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
   
    if (timeDiff < 100) // 25FPS = 40ms, 10FPS = 100ms
    {
        
       sleep(100 - timeDiff); 
    }
    //tính toán chu kì quay của các hành tinh
    kim = kim + 1.6;
    if (kim >= 360) kim = 0;
    thuy = thuy + 4.09;
    if (thuy >= 360) thuy = 0;
    dat = dat + 0.98;
    if (dat >= 360) dat = 0;
    hoa = hoa + 0.52;
    if (hoa >= 360) hoa = 0;
    moc = moc + 0.08;
    if (moc >= 360) moc = 0;
    tho = tho + 0.03;
    if (tho >= 360) tho = 0;
    tv = tv + 0.01;
    if (tv >= 360) tv = 0;
    hv = hv + 0.0059;
    if (hv >= 360) hv = 0;
    mt = mt + 13.3;
    if (mt >= 360) mt = 0;
    
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

