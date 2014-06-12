#include "Obstacle.h"


Obstacle::Obstacle()
{
}

void Obstacle::Draw()
{
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


Obstacle::~Obstacle()
{
}
