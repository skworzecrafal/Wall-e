#pragma once
#include "Vector3.h"
enum Ori
{
	oDownLeft,
	oDownRight,
	oUpLeft,
	oUpRight
};
class Sensor
{
public:
	Ori OriPosition = oDownLeft;
	Vector3f Position; 
	Vector3f Translation;
	Vector3f Origin ;
	Vector3f Rotation;
	Vector3f DownLeft = Position;
	Vector3f DownRight = Position + Vector3f(10, 0, 0);
	Vector3f UpLeft  = Position + Vector3f(0, 0, -10);
	Vector3f UpRight = Position + Vector3f(10, 0, -10);
	Vector3f downL = Vector3f(0, 0, 0);
	Vector3f downR = Vector3f(0, 0, 0);
	Vector3f upL = Vector3f(0, 0, 0);
	Vector3f upR = Vector3f(0, 0, 0);
	Matrixf tmp;
	float oldRot = 0;
	int czy = 0;
	float test[16];
	float ptr[16];
	void Draw();
	Sensor();
	~Sensor();
private:
};

