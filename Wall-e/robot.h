#pragma once
#include "PMath.h"
#include "Sensor.h"
#include "LoadOBJ.h"
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
	std::vector<Vector3f> laserPointsLeft1;
	std::vector<Vector3f> laserPointsLeft2;
	std::vector<Vector3f> laserPointsRight1;
	std::vector<Vector3f> laserPointsRight2;
	std::vector<Vector3f> laserPointsFront1;
	std::vector<Vector3f> laserPointsFront2;
	Matrixf leftSensorTranslation1;
	Matrixf leftSensorTranslation2;
	Matrixf frontSensorTranslation1;
	Matrixf frontSensorTranslation2;
	Matrixf rightSensorTranslation1;
	Matrixf rightSensorTranslation2;
	Matrixf tmp;
	
	int leftValue1;
	int leftValue2;
	int frontValue1;
	int frontValue2;
	int rightValue1;
	int rightValue2;
	Sensor SensorLeft1;
	Sensor SensorLeft2;
	Sensor SensorFront1;
	Sensor SensorFront2;
	Sensor SensorRight1;
	Sensor SensorRight2;
	WFObject model[17];
	float oldRot = 0;
	void Draw(int obrotL, int obrotR);
	void Draw();
	void Rysuj(float vl, float vr, int heado, int llr, int lud, int rlr, int rud);
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
	void head(int obrot);
	void lArm(int lr, int ud);
	void rArm(int lr, int ud);
	void naped(float vl, float vr);
};

