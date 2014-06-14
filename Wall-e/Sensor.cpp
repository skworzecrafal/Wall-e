#include "Sensor.h"
#include "glWrap.h"

#include <GL\glut.h>

Sensor::Sensor()
{
	width = 2;
	lWheel = Vector3f(0, 0, -width/2);
	rWheel = Vector3f(width, 0, -width / 2);
	center = Vector3f(width/2, 0, -width / 2);
}
Sensor::~Sensor()
{
}

//fajny efekt Matrixf(Translation)*Matrixf(-Origin.x, -Origin.y, -Origin.z)*
//Matrixf(Rotation.y)*Matrixf(Origin.x, Origin.y, Origin.z)*(Vector3f(0, 0, -10));
void Sensor::Draw()
{
	glPushMatrix();		



	glBegin(GL_QUADS);

	glNormal3d(0, 0, 1);
	glVertex3d(Position.x, Position.y, Position.z);
	glVertex3d(Position.x + width, Position.y, Position.z);
	glVertex3d(Position.x + (width - width / 8.0), Position.y + width, Position.z);
	glVertex3d(Position.x + (width / 8.0), Position.y + width, Position.z);

	glColor3d(0, 0.5, 1);
	glNormal3d(1, 0, 0);
	glVertex3d(Position.x + width, Position.y, Position.z);
	glVertex3d(Position.x + width, Position.y, Position.z - width);
	glVertex3d(Position.x + (width - width / 8.0), Position.y + width, Position.z - width);
	glVertex3d(Position.x + (width - width / 8.0), Position.y + width, Position.z);

	glColor3d(0.0, 1, 0.5);
	glNormal3d(0, 0, -1);
	glVertex3d(Position.x + width, Position.y, Position.z - width);
	glVertex3d(Position.x, Position.y, Position.z - width);
	glVertex3d(Position.x + (width / 8.0), Position.y + width, Position.z - width);
	glVertex3d(Position.x + (width - width / 8.0), Position.y + width, Position.z - width);

	glColor3d(0.0, 1, 1);
	glNormal3d(-1, 0, 0);
	glVertex3d(Position.x, Position.y, Position.z - width);
	glVertex3d(Position.x , Position.y, Position.z);
	glVertex3d(Position.x + width / 8.0, Position.y + width, Position.z);
	glVertex3d(Position.x + width / 8.0, Position.y + width, Position.z - width);

	glColor3d(1.0, 0, 1);
	glNormal3d(0, 1, 0);
	glVertex3d(Position.x + width / 8.0, Position.y + width, Position.z);
	glVertex3d(Position.x + width - width / 8.0, Position.y + width, Position.z);
	glVertex3d(Position.x + width - width / 8.0, Position.y + width, Position.z - width);
	glVertex3d(Position.x + width / 8.0, Position.y + width, Position.z - width);

	glColor3d(1.0, 1, 0);
	glNormal3d(0, -1, 0);
	glVertex3d(Position.x, Position.y, Position.z);
	glVertex3d(Position.x, Position.y, Position.z - width);
	glVertex3d(Position.x + width, Position.y, Position.z - width);
	glVertex3d(Position.x + width, Position.y, Position.z);
	glEnd();

	
	laserPoints = glWrap::LineOfPoints(Vector3f(width / 2, width / 2, 0), Vector3f(width / 2, width / 2, -width / 2), 30);

	
	glPopMatrix();
	

	
}