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
	switch (OriPosition)
	{
	case oLeftWheel:
		Origin = lWheel;
		glTranslatef(LeftWheel.x, LeftWheel.y, LeftWheel.z);
		glRotatef(oldRot, 0, 1, 0);
		glRotatef(Rotation.y, 0, 1, 0);
		glTranslatef(-Origin.x, -Origin.y, -Origin.z);
		glTranslatef(Translation.x, Translation.y, Translation.z);
		tmp = Matrixf(LeftWheel)*Matrixf(oldRot)*Matrixf(Rotation.y)*Matrixf(-Origin.x, -Origin.y, -Origin.z)*Matrixf(Translation);
		break;
	case oRightWheel:
		Origin = rWheel;
		glTranslatef(RightWheel.x, RightWheel.y, RightWheel.z);
		glRotatef(oldRot, 0, 1, 0);
		glRotatef(Rotation.y, 0, 1, 0);
		glTranslatef(-Origin.x, -Origin.y, -Origin.z);
		glTranslatef(Translation.x, Translation.y, Translation.z);
		tmp = Matrixf(RightWheel)*Matrixf(oldRot)*Matrixf(Rotation.y)*Matrixf(-Origin.x, -Origin.y, -Origin.z)*Matrixf(Translation);
		break;
	case oCenter:
		Origin = center;
		glTranslatef(Center.x, Center.y, Center.z);
		glRotatef(oldRot, 0, 1, 0);
		glRotatef(Rotation.y, 0, 1, 0);
		glTranslatef(-Origin.x, -Origin.y, -Origin.z);
		glTranslatef(Translation.x, Translation.y, Translation.z);
		tmp = Matrixf(Center)*Matrixf(oldRot)*Matrixf(Rotation.y)*Matrixf(-Origin.x, -Origin.y, -Origin.z)*Matrixf(Translation);
		break;
	}
	LeftWheel = tmp *lWheel;
	RightWheel = tmp*rWheel;
	Center = tmp*center;
	oldRot += Rotation.y;
	
	Translation.x = 0;
	Translation.y = 0;
	Translation.z = 0;
	Rotation.y = 0;


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
	laserPoints = tmp*laserPoints;
	glWrap::Print(-60, 50, laserPoints[0].ToString());
	glWrap::Print(-60, 40, laserPoints[laserPoints.size() - 1].ToString());
	glPopMatrix();
	

	
}