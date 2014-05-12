#pragma once
#include "PMath.h"
#include "Sensor.h"
class Robot
{
public:
	Ori OriPosition = oCenter;
	Vector3f Position;
	Vector3f Translation;
	Vector3f Origin;
	Vector3f Rotation;
	Vector3f LeftWheel;
	Vector3f RightWheel;
	Vector3f Center;
	Matrixf tmp;
	Sensor Sensor1;
	float oldRot = 0;
	void Draw(int obrotL, int obrotR);
	void Draw();
	Robot();
	~Robot();
private:
	Vector3f lWheel = Vector3f(0, 0, 0);
	Vector3f rWheel = Vector3f(0, 0, 0);
	Vector3f center = Vector3f(0, 0, 0);
	int width;
	void figura1(float a, float b, float c);
	void ramie(double r1, double r2, double h, double d);
	void gasienica(int obrot);
};

