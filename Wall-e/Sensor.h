#pragma once
#include "PMath.h"

class Sensor
{
public:
	Ori OriPosition = oCenter;
	Vector3f Position; 
	Vector3f Translation;
	Vector3f Origin ;
	Vector3f Rotation;
	Vector3f LeftWheel;
	Vector3f RightWheel;
	Vector3f Center;
	
	std::vector<Vector3f> laserPoints;
	Matrixf tmp;
	float oldRot = 0;
	void Draw();
	Sensor();
	~Sensor();
private:
	Vector3f lWheel = Vector3f(0, 0, 0);
	Vector3f rWheel = Vector3f(0, 0, 0);
	Vector3f center = Vector3f(0, 0, 0);

	int width;
	PMath pmath;
};

