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
	





	
	laserPoints = glWrap::LineOfPoints(Vector3f(width / 2, width / 2, 0), Vector3f(width / 2, width / 2, -width / 2), 50);

	
	
	

	
}