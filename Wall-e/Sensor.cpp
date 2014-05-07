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
	glPushMatrix();
	UpLeft = Vector3f(0, 0, -10);
	DownLeft = Vector3f(0, 0, 0);
	DownRight = Vector3f(10, 0, 0);
	UpRight = Vector3f(10, 0, -10);
		
	switch (OriPosition)
	{
	case oDownLeft:
		Origin = DownLeft;
		glTranslatef(downL.x, downL.y, downL.z);
		glRotatef(oldRot, 0, 1, 0);
		glRotatef(Rotation.y, 0, 1, 0);
		glTranslatef(-Origin.x, -Origin.y, -Origin.z);
		glTranslatef(Translation.x, Translation.y, Translation.z);
		tmp = Matrixf(downL)*Matrixf(oldRot)*Matrixf(Rotation.y)*Matrixf(Translation);
		break;
	case oDownRight:
		Origin = DownRight;
		glTranslatef(downR.x, downR.y, downR.z);
		glRotatef(oldRot, 0, 1, 0);
		glRotatef(Rotation.y, 0, 1, 0);
		glTranslatef(-Origin.x, -Origin.y, -Origin.z);
		glTranslatef(Translation.x, Translation.y, Translation.z);
		tmp = Matrixf(downR)*Matrixf(oldRot)*Matrixf(Rotation.y)*Matrixf(-Origin.x, -Origin.y, -Origin.z)*Matrixf(Translation);
		break;
	case oUpLeft:
		Origin = UpLeft;
		glTranslatef(upL.x, upL.y, upL.z);
		glRotatef(oldRot, 0, 1, 0);
		glRotatef(Rotation.y, 0, 1, 0);
		glTranslatef(-Origin.x, -Origin.y, -Origin.z);
		glTranslatef(Translation.x, Translation.y, Translation.z);
		tmp = Matrixf(upL)*Matrixf(oldRot)*Matrixf(Rotation.y)*Matrixf(-Origin.x, -Origin.y, -Origin.z)*Matrixf(Translation);
		break;
	case oUpRight:
		Origin = UpRight;
		glTranslatef(upR.x, upR.y, upR.z);
		glRotatef(oldRot, 0, 1, 0);
		glRotatef(Rotation.y, 0, 1, 0);
		glTranslatef(-Origin.x, -Origin.y, -Origin.z);
		glTranslatef(Translation.x, Translation.y, Translation.z);
		tmp = Matrixf(upR)*Matrixf(oldRot)*Matrixf(Rotation.y)*Matrixf(-Origin.x, -Origin.y, -Origin.z)*Matrixf(Translation);
		break;
	}
	
	int a, b, c = b = a = 10;

	/*glTranslatef(downL.x, downL.y, downL.z);
	glTranslatef(Origin.x, Origin.y, Origin.z);
	glRotatef(oldRot, 0, 1, 0);


	glRotatef(Rotation.y, 0, 1, 0);
	glTranslatef(-Origin.x, -Origin.y, -Origin.z);
	glTranslatef(Translation.x, Translation.y, Translation.z);
	tmp = Matrixf(downL)*Matrixf(oldRot)*Matrixf(Rotation.y)*Matrixf(Translation);*/
	

	

	//Matrixf tmp = Matrixf(DownLeft.x, DownLeft.y, DownLeft.z)*Matrixf(Origin.x, Origin.y, Origin.z)*Matrixf(Rotation.y)*Matrixf(-Origin.x, -Origin.y, -Origin.z)*Matrixf(Translation);
	UpLeft = tmp*Vector3f(0, 0, -10);
	DownLeft = tmp* Vector3f(0, 0, 0);
	DownRight = tmp*Vector3f(10, 0, 0);
	UpRight = tmp*Vector3f(10, 0, -10);
	downL = Vector3f(DownLeft);
	downR = Vector3f(DownRight);
	upL = Vector3f(UpLeft);
	upR = Vector3f(UpRight);
	oldRot += Rotation.y;
	//test:
	/*glPushMatrix();
	glLoadIdentity();
	glTranslatef(Origin.x, Origin.y, Origin.z);
	glRotatef(Rotation.y, 0, 1, 0);
	glTranslatef(-Origin.x, -Origin.y, -Origin.z);
	glTranslatef(Translation.x, Translation.y, Translation.z);
	czy = 1;
	glGetFloatv(GL_MODELVIEW_MATRIX, test);
	glPopMatrix();*/

	Translation.x = 0;
	Translation.y = 0;
	Translation.z = 0;
	Rotation.y = 0;


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