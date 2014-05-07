#include "Sensor.h"
#include <GL\glut.h>

Sensor::Sensor()
{
}
Sensor::~Sensor()
{
}

//fajny efekt Matrixf(Translation)*Matrixf(-Origin.x, -Origin.y, -Origin.z)*
//Matrixf(Rotation.y)*Matrixf(Origin.x, Origin.y, Origin.z)*(Vector3f(0, 0, -10));
void Sensor::Draw()
{

	Matrixf tmp = Matrixf(Rotation.y);


	UpLeft = tmp*(Vector3f(0, 0, -10));
	DownLeft = tmp* Vector3f(0, 0, 0);
	DownRight = tmp*Vector3f(10, 0, 0);
	UpRight = tmp*Vector3f(10, 0, -10);

	switch (OriPosition)
	{
	case oDownLeft:
		Origin = DownLeft;
		break;
	case oDownRight:
		Origin = DownRight;
		break;
	case oUpLeft:
		Origin = UpLeft;
		break;
	case oUpRight:
		Origin = UpRight;
		break;
	}
	int a, b, c = b = a = 10;


	glPushMatrix();
	
	glTranslatef(Origin.x, Origin.y, Origin.z);
	glRotatef(Rotation.y, 0, 1, 0); 
	glTranslatef(-Origin.x, -Origin.y, -Origin.z);
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