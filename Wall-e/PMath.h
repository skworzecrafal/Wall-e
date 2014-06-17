#pragma once
#include "Vector3.h"
enum Ori
{
	oLeftWheel,
	oRightWheel,
	oCenter
};
class PMath
{
public:

	~PMath();
	PMath();
	static int GetEValue(double value);
	static double Plength(Vector3f P1, Vector3f P2);
	static int Clamp(int value, int lower, int upper);
private:

	static double x;
	static double y;
	static double a;
	static double b;
	static double length;
	static std::vector<double> Evalues;
	static std::vector<double> values;
};

