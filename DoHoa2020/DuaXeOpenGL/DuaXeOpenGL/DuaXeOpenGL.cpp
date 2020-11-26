#include <stdio.h>
#include<stdlib.h>
//#include<sdtbool.h>
#include<windows.h>
#include "Dependencies/freeglut/glut.h";
#include<limits.h>
//#include<unistd.h>
#include<time.h>
#include<math.h>
#include<cstring>
#include<iostream>
#include<vector>

//số lượng xe khác xuất hiện trên màn hình
#define MaxCars 3

int footY = 200;
int divY = 220;
int endY = 160;

int a = 0;
int speed = 1;
int steerSpeed = 1;
int temp = 0;
int seconds = 0;
int distance = 178;
int fuel = 178;

int gameState = 0;
int lane[MaxCars];
int pos[MaxCars];
int speeds[MaxCars];
int speedsTemp[MaxCars];

GLdouble width = 1200, height = 800;

bool carMoveLeft = false, carMoveRight = false, carMoveFast = false, carStopped = false, gameStopped = false, horn = false;
bool highLightStart = false, highLightExit = false;
bool reachEnd = false, gameComplete = false, fuelOver = false;

//khai bao car
int carX = 0;
int carY = -100;

int fuelX = 0;
int fuelY = -80;
void drawCar(void) {
	glPushMatrix();
	glTranslated(carX, carY, 0.0);
	//tô màu gì đó
	glColor3f(0.34, 1.0, 1.0);
	//vẽ hình gì đó???
	glRectd(2, 10, -2, -10);
	glRectd(-8, 12, 8, 13);
	glRectd(-10.0, 9.0, -8.0, 15.0);
	glRectd(8.0, 9.0, 10.0, 15.0);

	glBegin(GL_LINES);
		glVertex2f(8.0, 11.0);
		glVertex2f(6.0, 7.0);
		glVertex2f(6.0, 7.0);
		glVertex2f(6.0, -7.0);
		glVertex2f(6.0, -7.0);
		glVertex2f(10.0, -12.0);
		glVertex2f(-8.0, 11.0);
		glVertex2f(-6.0, 7.0);
		glVertex2f(-6.0, 7.0);
		glVertex2f(-6.0, -7.0);
		glVertex2f(-6.0, -7.0);
		glVertex2f(-10.0, -12.0);
		glVertex2f(10.0, -12.0);
		glVertex2f(-10.0, -12.0);
	glEnd();

	glRectd(-11.0, -16.0, -9.0, -8.0);
	glRectd(9.0, -16.0, 11.0, -8.0);
	glRectd(-7.0, -14.0, -5.0, -12.0);
	glRectd(5.0, -14.0, 7.0, -12.0);

	glBegin(GL_LINES);
		glVertex2f(-7, -15);
		glVertex2f(-5, -15);
		glVertex2f(-8, -16);
		glVertex2f(-4, -16);
		glVertex2f(-6, -16);
		glVertex2f(-6, -17);
	glEnd();

	glPopMatrix();
}
//vẽ mấy cái xe khác
void drawOtherCars(int i) {
	glPushMatrix();
	glTranslated((lane[i] - 1) * 37, pos[i], 0.0);
	switch (speeds[i]) {
		case 2: glColor3f(0.0, 1.0, 0.0);break;
		case 3: glColor3f(0.0, 0.0, 1.0);break;
		case 4:
		case 5:
		case 6:
		case 7:glColor3f(1.0, 0.0, 0.0);break;
		case 0:glColor3f(0.0, 0.0, 0.0);break;
	}
	glRectd(2, 10, -2, -10);
	glRectd(-8, 12, 8, 13);
	glRectd(-10.0, 9.0, -8.0, 15.0);
	glRectd(8.0, 9.0, 10.0, 15.0);

	glBegin(GL_LINES);
	glVertex2f(8.0, 11.0);
	glVertex2f(6.0, 7.0);
	glVertex2f(6.0, 7.0);
	glVertex2f(6.0, -7.0);
	glVertex2f(6.0, -7.0);
	glVertex2f(10.0, -12.0);
	glVertex2f(-8.0, 11.0);
	glVertex2f(-6.0, 7.0);
	glVertex2f(-6.0, 7.0);
	glVertex2f(-6.0, -7.0);
	glVertex2f(-6.0, -7.0);
	glVertex2f(-10.0, -12.0);
	glVertex2f(10.0, -12.0);
	glVertex2f(-10.0, -12.0);
	glEnd();

	glRectd(-11.0, -16.0, -9.0, -8.0);
	glRectd(9.0, -16.0, 11.0, -8.0);
	glRectd(-7.0, -14.0, -5.0, -12.0);
	glRectd(5.0, -14.0, 7.0, -12.0);

	glBegin(GL_LINES);
	glVertex2f(-7, -15);
	glVertex2f(-5, -15);
	glVertex2f(-8, -16);
	glVertex2f(-4, -16);
	glVertex2f(-6, -16);
	glVertex2f(-6, -17);
	glEnd();

	glPopMatrix();  
}
//vẽ đường
void drawFootPath()
{
	int i, int y;
	glPushMatrix();
	//ve phia ben tay phai con duong
	glTranslated(60, 0, 0);
	y = footY + 20;
	for (int i = 0; i < 20; i++) {
		if (a == 0) {
			if (i % 2 == 0) 
				glColor3f(1.0, 1.0, 1.0);
			else 
				glColor3f(1.0, 1.0, 0.0);
		}
		else {
			if (i % 2 == 1)
				glColor3f(1.0, 1.0, 1.0);
			else
				glColor3f(1.0, 1.0, 0.0);
		}

		y -= 20;
		glRectd(5, y, -5, -20);
	}
	glPopMatrix();
	glPushMatrix();
	//ve phia ben tay trai con duong
	glTranslated(-60, 0, 0);
	y = footY + 20;
	for (int i = 0; i < 20; i++) {
		if (a == 0) {
			if (i % 2 == 0)
				glColor3f(1.0, 1.0, 1.0);
			else
				glColor3f(1.0, 1.0, 0.0);
		}
		else {
			if (i % 2 == 1)
				glColor3f(1.0, 1.0, 1.0);
			else
				glColor3f(1.0, 1.0, 0.0);
		}

		y -= 20;
		glRectd(5, y, -5, -20);
	}
	glPopMatrix();
}
//ve xung quanh
void drawSurroundings() {
	glColor3f(0.0, 1.0, 0.0);
	glRectd(240, 160, 65, -160);
	glRectd(-240, 160, -65, -160);
}
//dung game
void stopGame() {
	speed = 0;
	steerSpeed = 0;
}
//tiep tuc game
void resumeGame() {
	speed = 2;
	steerSpeed = 1;
}
//ve nhieu chiec xe khac, gọi lại hàm vẽ drawOtherCars
void drawOther() {
	for (int i = 0; i < MaxCars; i++) {
		drawOtherCars(i);
	}
}
//set vi tri xuat hien cua xe tren duong
void setCars() {
	for (int i = 0; i < MaxCars; i++) {
		lane[i] = i;
		pos[i] = 110 + rand() % 100;
		speeds[i] = 1 + i + rand() % 4;
	}
}
//
void moveDriver() {
	divY -= speed;
	if (divY < 120 && distance > 0) {
		divY = 200;
		if (carMoveFast) {
			distance -= 1.5;
			fuel -= 4;
		}
		else {
			distance -= 0.5;
			fuel -= 2;
		}
		if (fuel < 0) 
			fuelOver = true;

		if (distance < 5)
			reachEnd = true;
	}
}
//khi xe di chuyen
void moveCar() {
	if (carMoveLeft)
		carX -= steerSpeed;
	else if (carMoveRight)
		carX += steerSpeed;
	if (carX > 45 || carX < -45) {
		gameState = 2;
		gameStopped = true;
	}
}
//lam cho con duong di chuyen khi xe di chuyen
void moveRoad() {
	footY -= speed;
	if (footY < 160) {
		footY = 180;
		if (a == 0)
			a = 1;
		else
			a = 0;
	}
}
//di chuyen cac xe khac
void moveOtherCars() {
	for (int i = 0; i < MaxCars; i++) {
		pos[i] += -speed + speeds[i];
		if (pos[i] < -200 || pos[i] > 200) {
			pos[i] = 200 + rand() % 100;
			speeds[i] = 2 + rand() % 4;
		}
	}
	if (horn) {
		speeds[(carX + 60) / 40]++;
		if (speeds[(carX + 60) / 40] > 7)
			speeds[(carX + 60) / 40] = 7;
		horn = false;
	}
}
//phát hiện ra sự va chạm
int detectCollision() {
	if (gameState != 1)
		return 0;
	int limit;
	for (int i = 0; i < MaxCars; i++) {
		if (pos[i] < -70 && pos[i] > -130) {
			limit = (i - 1) * 40;
			if (carX < limit + 22 && carX > limit - 22) {
				speeds[i] = 0;
				gameStopped = true;
				gameState = 2;
				return 1;
			}
		}
	}
	if ((fuelX > carX && fuelX - carX < 20) || (fuelX < carX && carX - fuelX < 20)) {
		if (fuelY < -80 && fuelY > -120) {
			fuel += 40;
			if (fuel > 178)
				fuel = 178;
			fuelY = 600 + rand() % 150;
			fuelX = (rand() % 3 - 1) * 37;
		}
	}
	return 0;
}
//ve doan chu
void drawString(std::string str) {
	for (unsigned int i = 0; i < str.length(); i++) {
		glutStrokeCharacter(GLUT_STROKE_ROMAN, *(str.begin()+i));
	}
}
//period
void periodicFunction() {
	if (gameStopped)
		stopGame();
	else
		resumeGame();
	if (speed != 0) {
		if (carMoveFast)
			speed = 6;
		else
			speed = 2;
	}
	if (fuelOver) {
		gameStopped = true;
		gameState = 2;
	}
	moveRoad();
	moveDriver();
	moveCar();
	moveOtherCars();
	moveEnd();
	moveFuel();

	if (!detectCollision() && !gameStopped && gameState == 1)
		temp += 15;
	if (temp > 1000) {
		temp = 0;
		seconds++;
	}
	glutPostRedisplay();
	glutTimerFunc(10, periodicFunction, v);
}
//ve menu
void drawMainMenu() {
	glClearColor(0.5, 0.5, 0.5, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	drawFootPath();
	drawSurroundings();
	drawDivider();
	drawCar();

	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
	glTranslated(0, 30, 0);
	glBegin(GL_LINE_LOOP);
		glVertex2f(30, 15);
		glVertex2f(30, -15);
		glVertex2f(-30, -15);
		glVertex2f(-30, 15);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-20, 30, 0);
	glScalef(0.1, 0.1, 0.1);
	glColor3f(1.0, 1.0, 1.0);
	drawString("START");
	glPopMatrix();
	//ve nut xoa
	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
	glTranslated(0, -30, 0);
	glBegin(GL_LINE_LOOP);
		glVertex2f(30, 15);
		glVertex2f(30, -15);
		glVertex2f(-30, -15);
		glVertex2f(-30, 15);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-15, -30, 0);
	glScalef(0.1, 0.1, 0.1);
	drawString("EXIT");
	glPopMatrix();

	if (highLightStart) {
		glColor3f(1.0, 0.0, 0.0);
		glPushMatrix();
		glTranslated(0, 30, 0);
		glBegin(GL_LINE_LOOP);
			glVertex2f(35, 20);
			glVertex2f(35, -20);
			glVertex2f(-35, -20);
			glVertex2f(-35, 20);
		glEnd();
		glPopMatrix();
	}
	if (highLightExit) {
		glColor3f(1.0, 0.0, 0.0);
		glPushMatrix();
		glTranslated(0, -30, 0);
		glBegin(GL_LINE_LOOP);
			glVertex2f(35, 20);
			glVertex2f(35, -20);
			glVertex2f(-35, -20);
			glVertex2f(-35, 20);
		glEnd();
		glPopMatrix();
	}
}
//ve exit menu
void drawMainMenu() {
	//ve nut start
	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
	glTranslated(0, 30, 0);
	glBegin(GL_LINE_LOOP);
		glVertex2f(30, 15);
		glVertex2f(30, -15);
		glVertex2f(-30, -15);
		glVertex2f(-30, 15);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-25, 30, 0);
	glScalef(0.1, 0.1, 0.1);
	glColor3f(1.0, 1.0, 1.0);
	drawString("RESTART");
	glPopMatrix();
	//ve nut exit
	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
	glTranslated(0, -30, 0);
	glBegin(GL_LINE_LOOP);
		glVertex2f(30, 15);
		glVertex2f(30, -15);
		glVertex2f(-30, -15);
		glVertex2f(-30, 15);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-15, -30, 0);
	glScalef(0.1, 0.1, 0.1);
	drawString("EXIT");
	glPopMatrix();

	if (highLightStart) {
		glColor3f(1.0, 0.0, 0.0);
		glPushMatrix();
		glTranslated(0, 30, 0);
		glBegin(GL_LINE_LOOP);
			glVertex2f(35, 20);
			glVertex2f(35, -20);
			glVertex2f(-35, -20);
			glVertex2f(-35, 20);
		glEnd();
		glPopMatrix();
	}
	if (highLightExit) {
		glColor3f(1.0, 0.0, 0.0);
		glPushMatrix();
		glTranslated(0, -30, 0);
		glBegin(GL_LINE_LOOP);
			glVertex2f(35, 20);
			glVertex2f(35, -20);
			glVertex2f(-35, -20);
			glVertex2f(-35, 20);
		glEnd();
		glPopMatrix();
	}
}
//ve diem
void drawScore(int score) {
	int temp = score;
	int str[20];
	int i = 0;
	while (temp > 0) {
		str[i++] = (temp % 10);
		temp /= 10;
	}
	i--;
	while (i >= 0) {
		glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i--]+'0');
	}
	if (score == 0)
		glutStrokeCharacter(GLUT_STROKE_ROMAN, '0');
}
//ve thoi gian
void drawTime() {
	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
	glTranslated(-200, 90, 0);
	glBegin(GL_LINE_LOOP);
		glVertex2f(50, 15);
		glVertex2f(50, -15);
		glVertex2f(-30, -15);
		glVertex2f(-30, 15);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-220, 85, 0);
	glScalef(0.1, 0.1, 0.1);
	glColor3f(1.0, 1.0, 1.0);
	drawString("Time: ");
	glPopMatrix();

	glPushMatrix();
	glTranslated(-180, 85, 0);
	glScalef(0.1, 0.1, 0.1);
	glColor3f(1.0, 0.0, 0.0);
	drawScore(seconds);
	glPopMatrix();
}
void mainDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	switch (gameState)
	{
	case 1: glClearColor(0.5, 0.5, 0.5, 0.0);
		drawFootPath();
		drawSurroundings();
		drawDivider();

		drawCar();
		drawOther();
		drawTime();
		drawDistanceBar();
		drawFuel();
		break;
	case 0: drawMainMenu();
		break;
	case 2: glClearColor(0.5, 0.5, 0.5, 0.0);
		drawFootPath();
		drawSurroundings();
		drawDivider();
		if (gameComplete)
			drawEnd();
		if (fuelOver)
			fuelMessage();

		drawCar();
		drawOther();
		drawDistanceBar();
		drawFuelBar();
		drawExitMenu();
		drawExitMenu();
		drawTime();
		break;
	}
	glFlush();
	glutSwapBuffers();
}

void keyBoardInput(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_LEFT: carMoveLeft = true; carMoveRight = false; break;
	case GLUT_KEY_RIGHT: carMoveRight = true; carMoveLeft = false; break;
	case GLUT_KEY_UP: carMoveFast = true; break;
	}
}

void keyBoardUpFunc(int k, int x, int y) {
	switch (k) {
	case GLUT_KEY_LEFT: carMoveLeft = false;break;
	case GLUT_KEY_RIGHT: carMoveRight = false; break;
	case GLUT_KEY_UP: carMoveFast = false; break;
	case GLUT_KEY_DOWN: carStopped = false; break;
	}
}

void normalKeyBoardFunc(unsigned char key, int x, int y) {
	if (gameState == 1) {
		switch (key) {
		case 'H':
		case 'h': horn = true; break;
		}
	}
	else if (gameState == 0) {
		if (key == 13) {
			setCars();
			gameState = 1;
		}
	}
}

void mouseFunc(int button, int state, int x, int y) {
	switch (gameState) {
	case 0: if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		if (x >= 630 && x <= 810 && y >= 320 && y <= 405) {
			//gameStopped = false;
			setCars();
			gameState = 1;
		}
		else if (x >= 630 && x <= 810 && y >= 490 && y <= 575)
			exit(0);
	}
		  break;
	case 2: if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		if (x >= 630 && x <= 810 && y >= 320 && y <= 405) {
			gameStopped = false;
			gameComplete = false;
			reachEnd = false;
			seconds = 0;
			distance = 178;
			fuel = 178;
			fuelOver = false;
			endY = 160;
			setCars();
			gameState = 1;
			carX = 0;
		}
		else if (x >= 630 && x <= 810 && y >= 490 && y <= 575)
			exit(0);
	}
		  break;
	}
}

void mouseHover(int x, int y) {
	if (x >= 630 && x <= 810 && y >= 320 && y <= 405) {
		highLightStart = true;
		highLightExit = false;
	}
	else if (x >= 630 && x <= 810 && y >= 490 && y <= 575) {
		highLightStart = false;
		highLightExit = true;
	}
	else {
		highLightStart = false;
		highLightExit = false;
	}
}
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize((int)width, (int)height);
	glutCreateWindow("Game Đua Xe Tien-Nguyen");
	glutFullScreen();

	gluOrtho2D(-240.0, 240.0, -160.0, 160.0);

	glutDisplayFunc(mainDisplay);
	glutTimerFunc(100, periodicFunction, 0);

	glutSpecialFunc(keyBoardInput);
	glutSpecialFunc(keyBoardUpFunc);
	glutSpecialFunc(normalKeyBoardFunc);
	glutMouseFunc(mouseFunc);
	glutPassiveMotionFunc(mouseHover);

	glutMainLoop();
	return 0;
}
