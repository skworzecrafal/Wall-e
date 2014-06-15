#include "Obstacle.h"


Obstacle::Obstacle(Vector3f leftDown, int xSize, int zSize)
{
	this->leftDown = leftDown;
	this->xSize = xSize;
	this->zSize = zSize;
}

void Obstacle::Draw()
{
	leftUp.x = leftDown.x;
	leftUp.y = 0;
	leftUp.z = zSize+leftDown.z;

	rightUp.x = xSize+leftDown.x;
	rightUp.y = 0;
	rightUp.x = zSize + leftDown.z;

	rightDown.x = xSize + leftDown.x;
	rightDown.y = 0;
	rightDown.z = 0 + leftDown.z;
	int height = 40;
	glBegin(GL_QUAD_STRIP);
	glColor3f(1, 0, 0);

	glVertex3f(leftDown.x, leftDown.y + height, leftDown.z);
	glVertex3f(leftDown.x, leftDown.y, leftDown.z);
	glVertex3f(leftDown.x + xSize, leftDown.y + height, leftDown.z);
	glVertex3f(leftDown.x + xSize, leftDown.y, leftDown.z);

	glVertex3f(leftDown.x + xSize, leftDown.y + height, leftDown.z+ zSize);
	glVertex3f(leftDown.x + xSize, leftDown.y, leftDown.z+zSize);

	glVertex3f(leftDown.x, leftDown.y + height, leftDown.z+ zSize);
	glVertex3f(leftDown.x, leftDown.y, leftDown.z+zSize);

	glVertex3f(leftDown.x, leftDown.y + height, leftDown.z);
	glVertex3f(leftDown.x, leftDown.y, leftDown.z);

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
