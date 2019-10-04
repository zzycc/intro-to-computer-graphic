#include "glew.h"
#include "glut.h"
#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include "FreeImage.h"
#include "shader.h"

using namespace std;

struct VertexAttribute
{
	GLfloat position[3];
	GLfloat normal[3];
	GLfloat texcoord[2];
};


GLuint program;
GLuint vboName;
//Earth Spec
float Degree = 0.0f;
float Radius = 1.0f;
float Pi = 3.14159265358979323846f;
int Earth_Slice = 360;
int Earth_Stack = 180;
unsigned int textObj[3];
int width = 400, height = 400;
int image_width, image_height;

GLint mode[3] = {1,0,0};

void display();
void reshape(GLsizei w, GLsizei h);
void keyboard(unsigned char key, int x, int y);
void idle();
void init();
FIBITMAP* readFreeImage(const char* filename);
void init_texture();

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(width, height);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("0410835_HW3");
	glewInit();

	init();
	init_texture();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);
	glutMainLoop();

	return 0;
}

void init() {
	GLuint vert = createShader("Shaders/texture.vert", "vertex");
	GLuint geom = createShader("Shaders/texture.geom", "geometry");
	GLuint frag = createShader("Shaders/texture.frag", "fragment");
	program = createProgram(vert, geom, frag);
	int vertices_num = Earth_Stack * (Earth_Slice + 1);
	VertexAttribute vertices[180*361*2];
	for (int i = 0; i < Earth_Stack; i++) {
		for (int j = 0; j <= Earth_Slice; j++) {
			float f_i = (float)i, f_j = (float)j, f_stack = (float)Earth_Stack, f_slice = (float)Earth_Slice,R = Radius;
			vertices[2 * (i*(Earth_Slice+1) + j)].position[0] = R * sin(f_i / f_stack * Pi)*cos(f_j / f_slice * 2 * Pi);
			vertices[2 * (i*(Earth_Slice + 1) + j)].position[1] = R * sin(f_i / f_stack * Pi)*sin(f_j / f_slice * 2 * Pi);
			vertices[2 * (i*(Earth_Slice + 1) + j)].position[2] = R * cos((f_i / f_stack)*Pi);
			vertices[2 * (i*(Earth_Slice + 1) + j)].normal[0] = R * sin(f_i / f_stack * Pi)*cos(f_j / f_slice * 2 * Pi);
			vertices[2 * (i*(Earth_Slice + 1) + j)].normal[1] = R * sin(f_i / f_stack * Pi)*sin(f_j / f_slice * 2 * Pi);
			vertices[2 * (i*(Earth_Slice + 1) + j)].normal[2] = R * cos((f_i / f_stack)*Pi);
			vertices[2 * (i*(Earth_Slice + 1) + j)].texcoord[0] = f_j / f_slice;
			vertices[2 * (i*(Earth_Slice + 1) + j)].texcoord[1] = 1 - f_i / f_stack;

			vertices[2 * (i*(Earth_Slice + 1) + j) + 1].position[0] = R * sin((f_i + 1) / f_stack * Pi)*cos(f_j / f_slice * 2 * Pi);
			vertices[2 * (i*(Earth_Slice + 1) + j) + 1].position[1] = R * sin((f_i + 1) / f_stack * Pi)*sin(f_j / f_slice * 2 * Pi);
			vertices[2 * (i*(Earth_Slice + 1) + j) + 1].position[2] = R * cos(((f_i + 1) / f_stack)*Pi);
			vertices[2 * (i*(Earth_Slice + 1) + j) + 1].normal[0] = R * sin((f_i + 1) / f_stack * Pi)*cos(f_j / f_slice * 2 * Pi);
			vertices[2 * (i*(Earth_Slice + 1) + j) + 1].normal[1] = R * sin((f_i + 1) / f_stack * Pi)*sin(f_j / f_slice * 2 * Pi);
			vertices[2 * (i*(Earth_Slice + 1) + j) + 1].normal[2] = R * cos(((f_i + 1) / f_stack)*Pi);
			vertices[2 * (i*(Earth_Slice + 1) + j) + 1].texcoord[0] = f_j / f_slice;
			vertices[2 * (i*(Earth_Slice + 1) + j) + 1].texcoord[1] = 1 - (f_i + 1) / f_stack;
		}
	}


	glGenBuffers(1, &vboName);
	glBindBuffer(GL_ARRAY_BUFFER, vboName);

	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexAttribute) * vertices_num*2, vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttribute), (void*)(offsetof(VertexAttribute, position)));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttribute), (void*)(offsetof(VertexAttribute, normal)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexAttribute), (void*)(offsetof(VertexAttribute, texcoord)));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void display()
{
	//Clear the buffer
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// viewport transformation
	glViewport(0, 0, width, height);
	// projection transformation
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, (GLfloat)width / (GLfloat)height, 0.1, 1000);
	// viewing and modeling transformation
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	gluLookAt(0.0f, 0.0f, 3.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	glRotatef(Degree, -sin(23.5 / 180 * Pi), cos(23.5 / 180 * Pi), 0.0f);
	glRotatef(23.5f, 0.0f, 0.0f, 1.0f);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);

	GLfloat pmtx[16];
	GLfloat mmtx[16];
	glGetFloatv(GL_PROJECTION_MATRIX, pmtx);
	glGetFloatv(GL_MODELVIEW_MATRIX, mmtx);
	GLint pmatLoc = glGetUniformLocation(program, "Projection");
	GLint mmatLoc = glGetUniformLocation(program, "ModelView");
	GLint textLoc = glGetUniformLocation(program, "Texture");
	GLint normalLoc = glGetUniformLocation(program, "Normal_map");
	GLint specLoc = glGetUniformLocation(program, "Spec_map");
	GLint DegLoc = glGetUniformLocation(program, "Degree");
	GLint ModeLoc = glGetUniformLocation(program, "Mode");

	glUseProgram(program);

	glUniformMatrix4fv(pmatLoc, 1, GL_FALSE, pmtx);
	glUniformMatrix4fv(mmatLoc, 1, GL_FALSE, mmtx);
	glUniform3iv(ModeLoc,1,mode);
	glUniform1f(DegLoc, Degree);


	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textObj[0]);
	glUniform1i(textLoc, 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, textObj[1]);
	glUniform1i(normalLoc, 1);
	
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, textObj[2]);
	glUniform1i(specLoc, 2);
	for(int i = 0;i<Earth_Stack;i++)
		glDrawArrays(GL_TRIANGLE_STRIP, i*361*2, 361 * 2);
	glUseProgram(0);

	glPopMatrix();
	glutSwapBuffers();

}

void reshape(GLsizei w, GLsizei h)
{
	width = w;
	height = h;
}

void idle() {
	Sleep(100);
	Degree = (Degree +10);
	glutPostRedisplay();
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

	FIBITMAP* p32BitsImage = readFreeImage("./earth_texture_map.jpg");
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

	p32BitsImage = readFreeImage("./earth_normal_map.tif");
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

	p32BitsImage = readFreeImage("./earth_specular_map.tif");
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

}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'p':
	case 'P':
		system("pause");
		break;
	case '1':
		mode[0] = (mode[0] + 1) % 2;
		printf("1 %d\n", mode[0]);
		break;
	case '2':
		mode[1] = (mode[1] + 1) % 2;
		printf("2 %d\n", mode[1]);
		break;
	case '3':
		mode[2] = (mode[2] + 1) % 2;
		printf("3 %d\n", mode[2]);
		break;
	default:
		break;
	}
}