// 终点画线法.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//


#include <iostream>
//#include <windows.h>
#include <GL/glut.h>
#include <math.h>
using namespace std;

void renderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);	//清空颜色缓冲池
	glColor3f(1.0f, 0.0f, 0.0f);	//设置绘图颜色
	glRectf(-0.5f, -0.5f, 0.5f, 0.5f);	//绘制矩形 (x_1,y_1,x2,y2) 分别为矩形中左下角、右上角的坐标
	//glRectf(100.0f, 100.0f, 200.0f, 200.0f);
	glFlush();						//执行OpenGL指令列表中的指令
}
float x_0 = -1000;
float y_0 = -1000;
float x_1 = 1000; 
float y_1 = 1000;

void drawpixeil(double x, double y, int Color)
{
	glBegin(GL_POINTS);
	glColor3f(0, 255, 0);
	glVertex2f(x / 1000, y / 1000);
	glEnd();
}

//void DDALine5(void)
//{
//	int x_0, y_0, x_1, y_1, Color;
//	x_0 = 0; y_0 = 0; x_1 = 5; y_1 = 2; Color = 0;
//	glClear(GL_COLOR_BUFFER_BIT);
//	//x,y为计算得到的下一个点
//	int dx, dy, x;
//	float y, k;	//k为斜率
//	dx = x_1 - x_0;
//	dy = y_1 - y_0;
//	k = dy / dx;
//	//初始化至起点
//	y = y_0;
//	for (x = x_0; x <= x_1; x++)
//	{
//		drawpixeil(x, int(y + 0.5), Color);
//
//		y += k;
//	}
//}
void DDALine5(void)	//数值微分法DDA
{
	//窗口clear黑色
	glClear(GL_COLOR_BUFFER_BIT);
	//float x_0 = 0, y_0 = 0, x_1 = 1000, y_1 = 1000;	//float至少32位
	int n, j = 0;
	cout << "输入线段总数：";
	cin >> n;
	while (j < n)
	{
		cout << "输入第" << j + 1 << "条线段：";
		cin >> x_0 >> y_0 >> x_1 >> y_1;

		double dx, dy, ep, x, y;						//double至少48位

		dx = (double)x_1 - x_0;
		dy = (double)y_1 - y_0;
		//0<k<1 || k>1， 1 : k
		ep = (fabs(dx) > fabs(dy)) ? fabs(dx) : fabs(dy);
		dx = dx / ep;
		dy = dy / ep;
		x = x_0;
		y = y_0;
		for (int i = 0; i <= ep; i++)
		{
			//opengl中画点函数
			/*glBegin(GL_POINTS);
			glColor3f(0, 1, 0);
			glVertex2f(x / 1000, y / 1000);
			glEnd();*/
			drawpixeil(int(x + 0.5), int(y + 0.5), 0);
			x += dx;
			y += dy;
		}
		j++;
		glFlush();
	}
	//glFlush();
}

void Midpoint_Line(void)	//中点划线
{
	//float x_0 = -1000, y_0 = -1000, x_1 = 1000, y_1 = 1000;
	int n, j = 0;
	cout << "输入线段总数：";
	cin >> n;
	while (j < n)
	{
		cout << "输入第" << j + 1 << "条线段：";
		cin >> x_0 >> y_0 >> x_1 >> y_1;

		int a, b, d1, d2, d, x, y;
		glClear(GL_COLOR_BUFFER_BIT);
		a = y_0 - y_1; b = x_1 - x_0; d = 2 * a + b;
		d1 = 2 * a; d2 = 2 * (a + b);
		x = x_0; y = y_0;
		drawpixeil(x, y, 0);
		while (x < x_1)
		{
			if (d < 0)
			{
				x++; y++; d += d2;
			}
			else
			{
				x++; d += d1;
			}
			drawpixeil(x, y, 0);
		}

		j++;
		glFlush();
	}
	//glFlush();
}

void IntegerBresenhamline(void)	//Bresenhamline
{
	//float x_0 = -1000, y_0 = -1000, x_1 = 1000, y_1 = 1000;
	int n, j = 0;
	cout << "输入线段总数：";
	cin >> n;
	while (j < n)
	{
		cout << "输入第" << j+1 << "条线段：";
		cin >> x_0 >> y_0 >> x_1 >> y_1;
		int x, y, dx, dy, e;
		dx = x_1 - x_0, dy = y_1 - y_0;
		e = -dx;
		x = x_0, y = y_0;
		for (int i = 0; i <= dx; i++)
		{
			drawpixeil(x, y, 0);
			x++, e = e + 2 * dy;
			if (e > 0)
			{
				y++;
				e = e - 2 * dx;
			}
		}j++;
		glFlush();
	}
	//glFlush();
}


void main(int argc, char** argv)
{
	glutInit(&argc, argv); //初始化glut//////////////
	//glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);	//显示模式
	glutInitDisplayMode(GLUT_DEPTH | GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(1000, 1000);					//窗口大小
	glutInitWindowPosition(800, 0);					//窗口位置
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	glutCreateWindow("直线");						//创建 窗口并赋予title
	glOrtho(0.0f, 10.0f, 0.0f, 10.0f, 0, 0);	//设置新的相对坐标系(左,右,下,上,近,远)
	glutDisplayFunc(DDALine5);					//注册显示窗口时回调函数renderScene
	//glutDisplayFunc(Midpoint_Line);						//中点划线
	//glutDisplayFunc(IntegerBresenhamline);					//Bresenhamline

	//glClearColor(0.0f, 0.0f, 1.0f, 1.0f);			//蓝色
	//DDALine5(0, 0, 5, 2, 0);
	glutMainLoop();									//消息循环(处理操作系统等的消息，例如键盘、鼠标事件等)
}
