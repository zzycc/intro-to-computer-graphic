
#include "glew.h"
#include "glut.h"
#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
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
void drawtail(float R, int slice, int stack);
void drawEx(float R, int slice, int stack, float r);

FIBITMAP* readFreeImage(const char* filename);
void init_texture();

int width = 1920, height = 1080;
int image_width, image_height;
float Degree = 0.0f;
float Radius = 2.0f;
float rate = 0.02f;
float Pi = 3.14159265358979323846f;
//Earth Spec
int Earth_Slice = 360;
int Earth_Stack = 180;
//Comet Spec
int Comet_Slice = 360;
int Comet_Stack = 180;

unsigned int textObj[10];

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA |GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("0410835_HW4");

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
	float red[4] = { 0.5f, 0.0f, 0.0f, 1.0f };
	float yellow[4] = { 1.0f, 1.0f, 0.0f, 1.0f };
	float white[4] = { 0.8f, 0.8f, 0.8f, 1.0f };
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
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);
	//Comet
	glBindTexture(GL_TEXTURE_2D, textObj[1]);
	glPushMatrix();
	glTranslatef(3.0f * Radius-Degree*0.1, 0.0f, 0.0f);
	drawSolidSphere(0.1f * Radius, Comet_Slice, Comet_Stack);
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);
	//Comet_tail
	if (3.0f * Radius - Degree * 0.1 != Radius) {
		glBindTexture(GL_TEXTURE_2D, textObj[2]);
		glPushMatrix();
		glTranslatef(3.0f * Radius - Degree * 0.1, 0.0f, 0.0f);
		drawtail(0.1f * Radius, Comet_Slice, Comet_Stack);
		glPopMatrix();
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	//Explosion_Effect
	if (3.0f * Radius - Degree * 0.1 == Radius) {
		glBindTexture(GL_TEXTURE_2D, textObj[3]);
		glPushMatrix();
		glTranslatef(3.0f * Radius - Degree * 0.1, 0.0f, 0.0f);
		drawEx(0.1f * Radius, Comet_Slice, Comet_Stack,rate);
		glPopMatrix();
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	glutSwapBuffers();
}

void reshape(int _width, int _height) {
	width = _width;
	height = _height;
}


void keyboard(unsigned char key, int x, int y) {
}

void mouse(int button, int state, int x, int y) {
}

void mouseMotion(int x, int y) {
}

void passiveMouseMotion(int x, int y) {
}

void idle() {
	Sleep(1);
	if(3.0f * Radius - Degree * 0.1 != Radius)
		Degree = (Degree + 1);
	if (3.0f * Radius - Degree * 0.1 == Radius && rate < 10.0f)
		rate += 0.3f;
		
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

void drawSolidSphere(float R, int slice, int stack) {//經度 緯度
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

void drawtail(float R, int slice, int stack) {//經度 緯度
	if (slice < 2 || stack < 2)
		return;
	srand(time(NULL));
	for (int i = 0; i < stack; i+=10) {
		glBegin(GL_TRIANGLE_STRIP);
		for (int j = 0; j <= slice; j+=19) {
			float f_i = (float)i, f_j = (float)j, f_stack = (float)stack, f_slice = (float)slice;
			if (R*sin(f_i / f_stack * Pi)*cos(f_j / f_slice * 2 * Pi) < 0)
				continue; 
			glNormal3f(R*sin(f_i / f_stack * Pi)*cos(f_j / f_slice * 2 * Pi), R*sin(f_i / f_stack * Pi)*sin(f_j / f_slice * 2 * Pi), R*cos((f_i / f_stack)*Pi));
			glTexCoord2f(((float)rand() / (float)(RAND_MAX)), ((float)rand() / (float)(RAND_MAX)));
			glVertex3f(R*sin(f_i / f_stack * Pi)*cos(f_j / f_slice * 2 * Pi), R*sin(f_i / f_stack * Pi)*sin(f_j / f_slice * 2 * Pi), R*cos((f_i / f_stack)*Pi));
			
			glNormal3f(R*sin((f_i + 1) / f_stack * Pi)*cos(f_j / f_slice * 2 * Pi), R*sin((f_i + 1) / f_stack * Pi)*sin(f_j / f_slice * 2 * Pi), R*cos(((f_i + 1) / f_stack)*Pi));
			glTexCoord2f(((float)rand() / (float)(RAND_MAX)), ((float)rand() / (float)(RAND_MAX)));
			glVertex3f(R*sin(f_i / f_stack * Pi)*cos(f_j / f_slice * 2 * Pi)+(float)(rand()%3), 0.2f*R*sin(f_i / f_stack * Pi)*sin(f_j / f_slice * 2 * Pi), 0.2f*R*cos((f_i / f_stack)*Pi));
		}
		glEnd();
	}
}
void drawEx(float R, int slice, int stack, float r) {//經度 緯度
	if (slice < 2 || stack < 2)
		return;
	srand(time(NULL));
	for (int i = 0; i < stack; i ++) {
		glBegin(GL_TRIANGLE_STRIP);
		for (int j = 0; j <= slice; j ++) {
			float f_i = (float)i, f_j = (float)j, f_stack = (float)stack, f_slice = (float)slice;
			if (R*sin(f_i / f_stack * Pi)*cos(f_j / f_slice * 2 * Pi) < 0)
				continue;
			glNormal3f(R*sin(f_i / f_stack * Pi)*cos(f_j / f_slice * 2 * Pi), R*sin(f_i / f_stack * Pi)*sin(f_j / f_slice * 2 * Pi), R*cos((f_i / f_stack)*Pi));
			glTexCoord2f(((float)rand() / (float)(RAND_MAX)), ((float)rand() / (float)(RAND_MAX)));
			glVertex3f(R*sin(f_i / f_stack * Pi)*cos(f_j / f_slice * 2 * Pi) - rate/10.0f, R*sin(f_i / f_stack * Pi)*sin(f_j / f_slice * 2 * Pi), R*cos((f_i / f_stack)*Pi));

			glNormal3f(R*sin((f_i + 1) / f_stack * Pi)*cos(f_j / f_slice * 2 * Pi), R*sin((f_i + 1) / f_stack * Pi)*sin(f_j / f_slice * 2 * Pi), R*cos(((f_i + 1) / f_stack)*Pi));
			glTexCoord2f(((float)rand() / (float)(RAND_MAX)), ((float)rand() / (float)(RAND_MAX)));
			glVertex3f(r/10*(R*sin(f_i / f_stack * Pi)*cos(f_j / f_slice * 2 * Pi) + 3.0f - rate / 10.0f), r*R*sin(f_i / f_stack * Pi)*sin(f_j / f_slice * 2 * Pi), r*R*cos((f_i / f_stack)*Pi));
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

	p32BitsImage = readFreeImage("./comet.jpg");
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

	p32BitsImage = readFreeImage("./cloud.jpg");
	glGenTextures(1, textObj + 2);
	glBindTexture(GL_TEXTURE_2D, textObj[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, image_width, image_height, 0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(p32BitsImage));
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	p32BitsImage = readFreeImage("./flame.jpg");
	glGenTextures(1, textObj + 3);
	glBindTexture(GL_TEXTURE_2D, textObj[3]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, image_width, image_height, 0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(p32BitsImage));
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
}