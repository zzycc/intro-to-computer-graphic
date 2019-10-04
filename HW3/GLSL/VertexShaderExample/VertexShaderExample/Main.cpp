#include "FreeImage.h"
#include "glew.h"
#include "glut.h"
#include "shader.h"
#include <iostream>

using namespace std;

struct VertexAttribute
{
	GLfloat position[3];
	GLfloat color[3];
};

int windowSize[2] = { 600, 500 };

GLuint program;
GLuint vboName;

bool start;

VertexAttribute *drawPlane();
void display();
void reshape(GLsizei w, GLsizei h);
void init();

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(windowSize[0], windowSize[1]);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutCreateWindow("ComputerGraphicsDemo");
	glewInit();

	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();

	return 0;
}

void init() {
	GLuint vert = createShader("Shaders/example.vert", "vertex");
	GLuint geom = createShader("Shaders/example.geom", "geometry");
	GLuint frag = createShader("Shaders/example.frag", "fragment");
	program = createProgram(vert, geom, frag);

	glGenBuffers(1, &vboName);
	glBindBuffer(GL_ARRAY_BUFFER, vboName);

	VertexAttribute *vertices;
	vertices = drawPlane();
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexAttribute) * 6, vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttribute), (void*)(offsetof(VertexAttribute, position)));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttribute), (void*)(offsetof(VertexAttribute, color)));
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &vboName);
	glBindBuffer(GL_ARRAY_BUFFER, vboName);

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
	glViewport(0, 0, windowSize[0], windowSize[1]);
	// projection transformation
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, (GLfloat)512 / (GLfloat)512, 1, 500);
	// viewing and modeling transformation
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//lights();
	gluLookAt(0.5f, 1.5f, -0.5f,// eye
		0.5f, 0.5f, 0.5f,// center
		0.0f, 1.0f, 0.0f);// up

	GLfloat pmtx[16];
	GLfloat mmtx[16];
	glGetFloatv(GL_PROJECTION_MATRIX, pmtx);
	glGetFloatv(GL_MODELVIEW_MATRIX, mmtx);
	GLint pmatLoc = glGetUniformLocation(program, "Projection");
	GLint mmatLoc = glGetUniformLocation(program, "ModelView");

	glUseProgram(program);

	glUniformMatrix4fv(pmatLoc, 1, GL_FALSE, pmtx);
	glUniformMatrix4fv(mmatLoc, 1, GL_FALSE, mmtx);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glUseProgram(0);
	
	glPopMatrix();
	glutSwapBuffers();

}

VertexAttribute *drawPlane() {
	VertexAttribute *vertices;
	vertices = new VertexAttribute[6];
	vertices[0].position[0] = 0.0f;	vertices[0].position[1] = 0.5f;	vertices[0].position[2] = 0.0f;
	vertices[1].position[0] = 1.0f;	vertices[1].position[1] = 0.5f;	vertices[1].position[2] = 0.0f;
	vertices[2].position[0] = 0.0f;	vertices[2].position[1] = 0.5f;	vertices[2].position[2] = 1.0f;
	vertices[3].position[0] = 1.0f;	vertices[3].position[1] = 0.5f;	vertices[3].position[2] = 0.0f;
	vertices[4].position[0] = 1.0f;	vertices[4].position[1] = 0.5f;	vertices[4].position[2] = 1.0f;
	vertices[5].position[0] = 0.0f;	vertices[5].position[1] = 0.5f;	vertices[5].position[2] = 1.0f;
	vertices[0].color[0] = 1.0f;	vertices[0].color[1] = 0.0f;	vertices[0].color[2] = 0.0f;
	vertices[1].color[0] = 0.0f;	vertices[1].color[1] = 1.0f;	vertices[1].color[2] = 0.0f;
	vertices[2].color[0] = 0.0f;	vertices[2].color[1] = 0.0f;	vertices[2].color[2] = 1.0f;
	vertices[3].color[0] = 0.0f;	vertices[3].color[1] = 1.0f;	vertices[3].color[2] = 0.0f;
	vertices[4].color[0] = 1.0f;	vertices[4].color[1] = 1.0f;	vertices[4].color[2] = 1.0f;
	vertices[5].color[0] = 0.0f;	vertices[5].color[1] = 0.0f;	vertices[5].color[2] = 1.0f;
	return vertices;
}

void reshape(GLsizei w, GLsizei h)
{
	windowSize[0] = w;
	windowSize[1] = h;
}