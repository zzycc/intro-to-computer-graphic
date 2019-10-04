/*
#include<math.h>
#include<glut.h>

const int n = 100;

const GLfloat R = 0.5;

const GLfloat Pi = 3.14;

void Display()

{

	glClear(GL_COLOR_BUFFER_BIT); //清除顏色緩衝和深度緩衝

	glBegin(GL_LINE_LOOP); //繪製方式

	//glColor3f(1.0, .0, .0); //設置顏色，3f代表參數為三個浮點數

	for (int i = 0; i < n; i++)

		glVertex2f(R*cos(2 * Pi / n * i), R*sin(2 * Pi / n * i));//計算坐標

	glEnd();

	glFlush();//強制刷新緩衝，保證命令被執行

}

int main(int argc, char *argv[])

{

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE); //顯示方式

	glutInitWindowPosition(100, 100); //窗口位置

	glutInitWindowSize(500, 500);//窗口大小

	glutCreateWindow("Draw A Circle");// 窗口名字

	glutDisplayFunc(&Display);//調用顯示函數

	glutMainLoop();

	return 0;

}
*/