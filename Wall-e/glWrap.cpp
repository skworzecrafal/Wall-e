#include "glWrap.h"
#include <GL\glut.h>

glWrap::glWrap()
{
}


glWrap::~glWrap()
{
}
void glWrap::Axis()
{
	glBegin(GL_LINES);
	//x
	glColor3f(100, 0, 0);
	glVertex3f(-300, 0, 0);
	glVertex3f(300, 0, 0);
	//y
	glColor3f(0, 0, 100);
	glVertex3f(0,-300, 0);
	glVertex3f(0,300, 0);
	//z
	glColor3f(0, 100, 0);
	glVertex3f(0,0,-300);
	glVertex3f(0,0,300);
	glEnd();


}