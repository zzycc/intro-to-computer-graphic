/*
#include<math.h>
#include<glut.h>

const int n = 100;

const GLfloat R = 0.5;

const GLfloat Pi = 3.14;

void Display()

{

	glClear(GL_COLOR_BUFFER_BIT); //�M���C��w�ĩM�`�׽w��

	glBegin(GL_LINE_LOOP); //ø�s�覡

	//glColor3f(1.0, .0, .0); //�]�m�C��A3f�N��ѼƬ��T�ӯB�I��

	for (int i = 0; i < n; i++)

		glVertex2f(R*cos(2 * Pi / n * i), R*sin(2 * Pi / n * i));//�p�⧤��

	glEnd();

	glFlush();//�j���s�w�ġA�O�ҩR�O�Q����

}

int main(int argc, char *argv[])

{

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE); //��ܤ覡

	glutInitWindowPosition(100, 100); //���f��m

	glutInitWindowSize(500, 500);//���f�j�p

	glutCreateWindow("Draw A Circle");// ���f�W�r

	glutDisplayFunc(&Display);//�ե���ܨ��

	glutMainLoop();

	return 0;

}
*/