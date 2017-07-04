#include "cube.h"

GLfloat AngleX;
GLfloat AngleY;

void ShowCube()
{
	GLfloat aspect = (GLfloat)600 / (GLfloat)600;
	GLfloat nRange = 100.0f;

	glViewport(0, 0, 600, 600);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-nRange, nRange, -nRange * aspect, nRange * aspect, -nRange, nRange);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();
	{
		glRotatef(AngleX, 1.0f, 0.0f, 0.0f);
		glRotatef(AngleY, 0.0f, 1.0f, 0.0f);


		glBegin(GL_POLYGON); //后表面  
		glColor3ub(136u, 176u, 75u);
		glVertex3f(50.0f, 50.0f, -50.0f);
		glVertex3f(50.0f, -50.0f, -50.0f);
		glVertex3f(-50.0f, -50.0f, -50.0f);
		glVertex3f(-50.0f, 50.0f, -50.0f);
		glEnd();

		glBegin(GL_POLYGON); //下表面  
		glColor3f(1.0, 1.0, 0.0);
		glVertex3f(50.0f, -50.0f, -50.0f);
		glVertex3f(50.0f, -50.0f, 50.0f);
		glVertex3f(-50.0f, -50.0f, 50.0f);
		glVertex3f(-50.0f, -50.0f, -50.0f);
		glEnd();

		glBegin(GL_POLYGON); //左表面  
		
		glColor3ub(255u, 235u, 205u);
		glVertex3f(50.0f, 50.0f, 50.0f);
		glVertex3f(50.0f, 50.0f, -50.0f);
		glVertex3f(50.0f, -50.0f, -50.0f);
		glVertex3f(50.0f, -50.0f, 50.0f);
		glEnd();

		glBegin(GL_POLYGON); //右表面  
		glColor3f(0.0f, 1.0f, 1.0f);
		glVertex3f(-50.0f, 50.0f, 50.0f);
		glVertex3f(-50.0f, 50.0f, -50.0f);
		glVertex3f(-50.0f, -50.0f, -50.0f);
		glVertex3f(-50.0f, -50.0f, 50.0f);
		glEnd();

		glBegin(GL_POLYGON); //前表面  
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(50.0f, 50.0f, 50.0f);
		glVertex3f(50.0f, -50.0f, 50.0f);
		glVertex3f(-50.0f, -50.0f, 50.0f);
		glVertex3f(-50.0f, 50.0f, 50.0f);
		glEnd();

		glBegin(GL_POLYGON); //上表面  
		glColor3ub(185u, 205u, 246u);
		glVertex3f(50.0f, 50.0f, -50.0f);
		glVertex3f(50.0f, 50.0f, 50.0f);
		glVertex3f(-50.0f, 50.0f, 50.0f);
		glVertex3f(-50.0f, 50.0f, -50.0f);
		glEnd();
	}
	glPopMatrix();
}



void CubeInit()
{
	AngleX = 45.0f;
	AngleY = 315.0f;
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DITHER);
	glShadeModel(GL_SMOOTH);
}