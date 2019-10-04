
#include "glut.h"
#include <Windows.h>
#include <iostream>

using namespace std;

void display();
void reshape(int _width, int _height);
void keyboard(unsigned char key, int x, int y);
void idle();

void init();
void lighting(int mode);

int width = 400, height = 400;
int cutoff = 0, exponent = 0;
int lighting_mode = 0;	//0:point light, 1:direcitonal light, 2: spotlight

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("WindowName");
	
	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);

	glutMainLoop();

	return 0;
}

void display()
{
	//ModelView Matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	//Projection Matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, width / (GLfloat)height, 0.1, 1000);
	//Viewport Matrix
	glViewport(0, 0, width, height);

	//clear
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	lighting(lighting_mode);

	float red[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	float green[] = { 0.0f, 1.0f, 0.0f, 1.0f };
	float blue [] = { 0.0f, 0.0f, 1.0f, 1.0f };

	glPushMatrix();
	//glRotatef(degree, 0, 1, 0);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, red);
	glMaterialfv(GL_FRONT, GL_SPECULAR, green);
	glMaterialfv(GL_FRONT, GL_AMBIENT, blue);
	glMaterialf(GL_FRONT, GL_SHININESS, 10);
	glutSolidSphere(3.5, 72, 36);
	glPopMatrix();

	glutSwapBuffers();
}

void reshape(int _width, int _height) {
	width = _width;
	height = _height;
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case '1':
		lighting_mode = 0;
		break;
	case '2':
		lighting_mode = 1;
		break;
	case '3':
		lighting_mode = 2;
		break;
	case 'q':
		cutoff = cutoff <= 90 ? cutoff + 3 : 90;
		break;
	case 'w':
		cutoff = cutoff >= 0 ? cutoff - 3 : 0;
		break;
	case 'e':
		exponent = exponent <= 128 ? exponent + 4 : 128;
		break;
	case 'r':
		exponent = exponent >= 0 ? exponent - 4 : 0;
		break;
	default:
		break;
	}
}

void idle() {
	Sleep(20);	//about 50 fps
	glutPostRedisplay();
}

void init() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	//enable depth test
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClearDepth(1.0);

	//enable lighting
	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);
}

void lighting(int mode) {
	float position[] = { 0.0f, 10.0f, 0.0f, 1.0f };
	if (mode == 1) {	//directional light
		position[3] = 0.0f;
	}
	float specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float ambient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	float none[] = { 0.0f, 0.0f, 0.0f, 1.0f };

	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	
	if (mode == 2) {	//spotlight
		float direction[] = { 0.0f, -1.0f, 0.0f, 1.0f };
		glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, direction);
		glLighti(GL_LIGHT0, GL_SPOT_EXPONENT, exponent);
		glLighti(GL_LIGHT0, GL_SPOT_CUTOFF, cutoff);
	}
	else {
		glLighti(GL_LIGHT0, GL_SPOT_CUTOFF, 180);	//close spotlight
	}
}
