#include "Obstacle.h"


Obstacle::Obstacle()
{
}

void Obstacle::Draw()
{
	leftUp.x = 0;
	leftUp.y = 0;
	leftUp.z = 20;

	leftDown.x = 0;
	leftDown.y = 0;
	leftDown.z = 0;

	rightUp.x = 20;
	rightUp.y = 0;
	rightUp.x = 20;

	rightDown.x = 20;
	rightDown.y = 0;
	rightDown.z = 20;

	float hight = 20.0f;
	glBegin(GL_QUAD_STRIP);
	glColor3f(1, 0, 0);

	glVertex3f(0.0f, hight, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(hight, hight, 0.0f);
	glVertex3f(hight, 0.0f, 0.0f);

	glVertex3f(hight, hight, hight);
	glVertex3f(hight, 0.0f, hight);

	glVertex3f(0.0f, hight, hight);
	glVertex3f(0.0f, 0.0f, hight);

	glVertex3f(0.0f, hight, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);

	glEnd();
}
bool Obstacle::Contain(Vector3f point)
{
	if ((point.x >= leftDown.x && point.x <= rightDown.x) && (point.z >= leftDown.z && point.z <= leftUp.z))
		return true;
	else
		return false;
}

Obstacle::~Obstacle()
{
}
