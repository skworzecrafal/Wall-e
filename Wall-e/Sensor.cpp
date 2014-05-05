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
	DownLeft = Position;
	DownRight = Position + Vector3f(10, 0, 0);
	UpLeft = Position + Vector3f(0, 0, -10);
	UpRight = Position + Vector3f(10, 0, -10);
	float ptr[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, ptr);
	DownLeft.x = DownLeft.x * ptr[0];
	DownLeft.z = DownLeft.z * ptr[8];
	int a, b, c = b = a = 10;
	glPushMatrix();
	glTranslatef(Origin.x, Origin.y, Origin.z);
	glRotatef(Rotation.x, 1, 0, 0);
	glRotatef(Rotation.y, 0, 1, 0);
	glRotatef(Rotation.z, 0, 0, 1);
	glTranslatef(-Origin.x, -Origin.y, -Origin.z);
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