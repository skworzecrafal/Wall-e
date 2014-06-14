#include "Obstacle.h"


Obstacle::Obstacle(Vector3f leftDown, int xSize, int zSize)
{
	this->leftDown = leftDown;
	this->xSize = xSize;
	this->zSize = zSize;
}

void Obstacle::Draw()
{
	leftUp.x = 0;
	leftUp.y = 0;
	leftUp.z = zSize;

	rightUp.x = xSize;
	rightUp.y = 0;
	rightUp.x = zSize;

	rightDown.x = xSize;
	rightDown.y = 0;
	rightDown.z = 0;

	glBegin(GL_QUAD_STRIP);
	glColor3f(1, 0, 0);

	glVertex3f(0.0f, 10, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(xSize, 10, 0.0f);
	glVertex3f(xSize, 0.0f, 0.0f);

	glVertex3f(xSize, 10, zSize);
	glVertex3f(xSize, 0.0f, zSize);

	glVertex3f(0.0f, 10, zSize);
	glVertex3f(0.0f, 0.0f, zSize);

	glVertex3f(0.0f, 10, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);

	glEnd();
}
bool Obstacle::Contain(Vector3f point)
{
	if ((point.x > leftDown.x && point.x < rightDown.x) && (point.z > leftDown.z && point.z < leftUp.z))
		return true;
	else
		return false;
}

Obstacle::~Obstacle()
{
}
