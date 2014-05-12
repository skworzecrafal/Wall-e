#pragma once
#include "RobotSI1.h"
#include "Sensor.h"
#include "Robot.h"
//before using any function initiate dll and mcl // at the end of the program terminate
class Robo_AI
{
public:
	Robo_AI();
	~Robo_AI();
	//return double[2] [0]-left move Vector [1]-right move Vector
	static double* Dodge(short left, short front, short right, const char* path);
	static void Movement(Robot* object, float left, float right);

};

