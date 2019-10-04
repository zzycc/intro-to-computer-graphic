
#include "glew.h"
#include "glut.h"
#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include "FreeImage.h"

using namespace std;

void display();
void reshape(int _width, int _height);
void keyboard(unsigned char key, int x, int y);
void mouse(int button, int state, int x, int y);
void mouseMotion(int x, int y);
void passiveMouseMotion(int x, int y);
void idle();
void lighting();
void drawSolidSphere(float R, int slice, int stack);

FIBITMAP* readFreeImage(const char* filename);
void init_texture();

int width = 400, height = 400;
int image_width, image_height;
float Degree = 0.0f;
float Radius = 2.0f;
float Pi = 3.14159265358979323846f;
//Sun Spec
int Sun_Slice = 240;
int Sun_Stack = 60;
//Earth Spec
int Earth_Slice = 360;
int Earth_Stack = 180;
//Moon Spec
int Moon_Slice = 240;
int Moon_Stack = 60;

unsigned int textObj[2];

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA |GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("0410835_HW1");

	glewInit();

	init_texture();

	//set light
	lighting();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotion);
	glutPassiveMotionFunc(passiveMouseMotion);
	glutIdleFunc(idle);

	glutMainLoop();

	return 0;
}

void display()
{
	float red[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
	float yellow[4] = { 1.0f, 1.0f, 0.0f, 1.0f };
	float blue[4] = { 0.0f, 0.0f, 1.0f, 1.0f };
	//ModelView Matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0f, 5.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	//Projection Matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, width / (GLfloat)height, 0.1, 1000);
	//Viewport Matrix
	glViewport(0, 0, width, height);

	//
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//Earth
	glBindTexture(GL_TEXTURE_2D, textObj[0]);
	glPushMatrix();
	glRotatef(Degree, -sin(23.5/180*Pi), cos(23.5/180*Pi), 0.0f);
	glRotatef(23.5f, 0.0f, 0.0f, 1.0f);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	drawSolidSphere( Radius, Earth_Slice, Earth_Stack);
	//glutSolidSphere( Radius, Earth_Slice, Earth_Stack);
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);
	//Moon
	glBindTexture(GL_TEXTURE_2D, textObj[1]);
	glPushMatrix();
	glRotatef(23.5f, 0.0f, 0.0f, 1.0f);
	glRotatef(Degree / 28.0f, 0.0f, 1.0f, 0.0f);
	glTranslatef(3.0f * Radius, 0.0f, 0.0f);
	glRotatef(Degree / 28.0f, 0.0f, -1.0f, 0.0f);
	glRotatef(Degree / 28.0f, 0.0f, 1.0f, 0.0f);
	drawSolidSphere(0.5f * Radius, Moon_Slice, Moon_Stack);
	//glutSolidSphere(0.5f * Radius, Moon_Slice, Moon_Stack);
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);
	
	glutSwapBuffers();
}

void reshape(int _width, int _height) {
	width = _width;
	height = _height;
}


void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'p':
	case 'P':
		system("pause");
		break;
	case 'o':
	case 'O':
		if (Earth_Slice == 360) {
			Earth_Slice = 4;
			Earth_Stack = 2;
		}
		else {
			Earth_Slice = 360;
			Earth_Stack = 180;
		}
	default:
		break;
	}
}

void mouse(int button, int state, int x, int y) {
}

void mouseMotion(int x, int y) {
}

void passiveMouseMotion(int x, int y) {
}

void idle() {
	Sleep(100);
	Degree = (Degree + 10);
	glutPostRedisplay();
}

void lighting()
{
	// enable lighting
	glEnable(GL_LIGHTING);
	//Add directed light
	GLfloat diffuse_color[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat ambient_color[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat position[] = { 0.0f, 10.0f, 0.0f, 1.0f};
	glEnable(GL_LIGHT0);								//open light0
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_color);	//set diffuse color of light0
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_color);	//set ambient color of light0
	glLightfv(GL_LIGHT0, GL_POSITION, position);		//set position of light 0
}

void drawSolidSphere(float R, int slice, int stack) {//¸g«× ½n«×
	if (slice < 2 || stack < 2)
		return;
	for (int i = 0; i < stack; i++) {
		glBegin(GL_TRIANGLE_STRIP);
		for (int j = 0; j <= slice; j++) {
			float f_i = (float)i, f_j = (float)j, f_stack = (float)stack, f_slice = (float)slice;
			glNormal3f(R*sin(f_i / f_stack * Pi)*cos(f_j / f_slice * 2 * Pi), R*sin(f_i / f_stack * Pi)*sin(f_j / f_slice * 2 * Pi), R*cos((f_i / f_stack)*Pi));
			glTexCoord2f(f_j / f_slice, 1 - f_i / f_stack);
			glVertex3f(R*sin(f_i / f_stack * Pi)*cos(f_j / f_slice * 2 * Pi), R*sin(f_i / f_stack * Pi)*sin(f_j / f_slice * 2 * Pi), R*cos((f_i / f_stack)*Pi));
			glNormal3f(R*sin((f_i + 1) / f_stack * Pi)*cos(f_j / f_slice * 2 * Pi), R*sin((f_i + 1) / f_stack * Pi)*sin(f_j / f_slice * 2 * Pi), R*cos(((f_i + 1) / f_stack)*Pi));
			glTexCoord2f(f_j / f_slice, 1 - (f_i + 1) / f_stack);
			glVertex3f(R*sin((f_i + 1) / f_stack * Pi)*cos(f_j / f_slice * 2 * Pi), R*sin((f_i + 1) / f_stack * Pi)*sin(f_j / f_slice * 2 * Pi), R*cos(((f_i + 1) / f_stack)*Pi));
		}
		glEnd();
	}
}

FIBITMAP* readFreeImage(const char* filename) {
	FIBITMAP* pImage = FreeImage_Load(FreeImage_GetFileType(filename, 0), filename);
	FIBITMAP* p32BitsImage = FreeImage_ConvertTo32Bits(pImage);
	image_width = FreeImage_GetWidth(p32BitsImage);
	image_height = FreeImage_GetHeight(p32BitsImage);
	return p32BitsImage;
}

void init_texture() {
	glEnable(GL_TEXTURE_2D);

	FIBITMAP* p32BitsImage = readFreeImage("./earth.jpg");
	glGenTextures(1, textObj);
	glBindTexture(GL_TEXTURE_2D, textObj[0]);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, image_width, image_height, 0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(p32BitsImage));
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	p32BitsImage = readFreeImage("./moon.jpg");
	glGenTextures(1, textObj + 1);
	glBindTexture(GL_TEXTURE_2D, textObj[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, image_width, image_height, 0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(p32BitsImage));
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
}