#pragma once
#include "Vector3.h"
enum Ori
{
	oLeftWheel,
	oRightWheel,
	oCenter
};
class Sensor
{
public:
	Ori OriPosition = oCenter;
	Vector3f Position; 
	Vector3f Translation;
	Vector3f Origin ;
	Vector3f Rotation;

	Vector3f DownLeft ;
	Vector3f DownRight;
	Vector3f UpLeft ;
	Vector3f UpRight;
	Vector3f LeftWheel;
	Vector3f RightWheel;
	Vector3f Center;
	
	Matrixf tmp;
	float oldRot = 0;
	void Draw();
	Sensor();
	~Sensor();
private:
	Vector3f downL = Vector3f(0, 0, 0);
	Vector3f downR = Vector3f(0, 0, 0);
	Vector3f upL = Vector3f(0, 0, 0);
	Vector3f upR = Vector3f(0, 0, 0);
	Vector3f lWheel = Vector3f(0, 0, 0);
	Vector3f rWheel = Vector3f(0, 0, 0);
	Vector3f center = Vector3f(0, 0, 0);
	int width;
};

