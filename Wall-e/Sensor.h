#pragma once
#include "Vector3.h"
class Sensor
{
public:
	Vector3f Position;
	Vector3f Translation;
	Vector3f Rotation;

	void Draw();
	Sensor();
	~Sensor();
private:
};

