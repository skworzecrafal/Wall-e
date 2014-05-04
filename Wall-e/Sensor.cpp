#include "Sensor.h"
#include <GL\glut.h>

Sensor::Sensor()
{
}


Sensor::~Sensor()
{
}
void Sensor::Draw()
{
	int a, b, c = b = a = 10;
	glPushMatrix();
	glRotatef(Rotation.x, 1, 0, 0);
	glRotatef(Rotation.y, 0, 1, 0);
	glRotatef(Rotation.z, 0, 0, 1);
	glTranslatef(Translation.x, Translation.y, Translation.z);
	glBegin(GL_QUADS);

	glNormal3d(0, 0, 1);
	glVertex3d(Position.x, Position.y, Position.z);
	glVertex3d(Position.x + a, Position.y, Position.z);
	glVertex3d(Position.x + (a - a / 8.0), Position.y + b, Position.z);
	glVertex3d(Position.x + (a / 8.0), Position.y + b, Position.z);

	glColor3d(0, 0.5, 1);
	glNormal3d(1, 0, 0);
	glVertex3d(Position.x + a, Position.y, Position.z);
	glVertex3d(Position.x + a, Position.y, Position.z - c);
	glVertex3d(Position.x + (a - a / 8.0), Position.y + b, Position.z - c);
	glVertex3d(Position.x + (a - a / 8.0), Position.y + b, Position.z);

	glColor3d(0.0, 1, 0.5);
	glNormal3d(0, 0, -1);
	glVertex3d(Position.x + a, Position.y, Position.z - c);
	glVertex3d(Position.x, Position.y, Position.z - c);
	glVertex3d(Position.x + (a / 8.0), Position.y + b, Position.z - c);
	glVertex3d(Position.x + (a - a / 8.0), Position.y + b, Position.z - c);

	glColor3d(0.0, 1, 1);
	glNormal3d(-1, 0, 0);
	glVertex3d(Position.x  , Position.y, Position.z - c);
	glVertex3d(Position.x , Position.y, Position.z);
	glVertex3d(Position.x + a / 8.0, Position.y + b, Position.z);
	glVertex3d(Position.x + a / 8.0, Position.y + b, Position.z - c);

	glColor3d(1.0, 0, 1);
	glNormal3d(0, 1, 0);
	glVertex3d(Position.x + a / 8.0, Position.y + b, Position.z);
	glVertex3d(Position.x + a - a / 8.0, Position.y + b, Position.z);
	glVertex3d(Position.x + a - a / 8.0, Position.y + b, Position.z - c);
	glVertex3d(Position.x + a / 8.0, Position.y + b, Position.z - c);

	glColor3d(1.0, 1, 0);
	glNormal3d(0, -1, 0);
	glVertex3d(Position.x, Position.y, Position.z);
	glVertex3d(Position.x, Position.y, Position.z - c);
	glVertex3d(Position.x + a, Position.y, Position.z - c);
	glVertex3d(Position.x + a, Position.y, Position.z);
	glEnd();
	glPopMatrix();
}