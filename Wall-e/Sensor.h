#pragma once
#include "Vector3.h"
class Sensor
{
public:
	Vector3f Position;
	Vector3f Translation;
	Vector3f Origin;
	Vector3f Rotation;
	Vector3f DownLeft = Position;
	Vector3f DownRight = Position + Vector3f(10, 0, 0);
	Vector3f UpLeft  = Position + Vector3f(0, 0, -10);
	Vector3f UpRight = Position + Vector3f(10, 0, -10);

	void Draw();
	Sensor();
	~Sensor();
private:
};

