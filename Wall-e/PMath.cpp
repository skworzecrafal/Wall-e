#include "PMath.h"

double PMath::x = 0;
double PMath::y = 0;
double PMath::a = 0;
double PMath::b = 0;
double PMath::length;
std::vector<double> PMath::Evalues;
std::vector<double> PMath::values;
PMath::PMath()
{
	length = 0; a = 0; b = 0; x = 0; y = 0;
	for (int i = 0; i < 1024; i++)
	{
		Evalues.push_back(exp((6.93049 / 1023) * i));
		values.push_back((double)((40.0 / 1023.0)*i) + 25);
	}
	std::reverse(Evalues.begin(), Evalues.end());
}


PMath::~PMath()
{
}
int PMath::GetEValue(double value)
{
	double mindiff = abs(value - values[0]);
	int index = 0;
	for (int i = 0; i < 1024; i++)
	{
		if (mindiff> abs(value - values[i]))
		{
			mindiff = abs(value - values[i]);
			index = i;
		}
	}
	return (int)(Evalues[index]);


}
double PMath::Plength(Vector3f P1, Vector3f P2)
{
	if (P1.x != P2.x && P1.y != P2.y && P1.z != P2.z)
	{
		Vector3f point = Vector3f(P1.x, P2.y, P1.z);
		a = (P1.z > point.z) ? P1.z - point.z : point.z - P1.z;
		b = (P2.y > point.y) ? P2.y - point.y : point.y - P2.y;
		return length = sqrt((a * a) + (b * b));
	}
	else if (P1.x == P2.x && P1.z == P2.z)
	{
		return length = (P1.y > P2.y) ? P1.y - P2.y : P2.y - P1.y;
	}
	else if(P1.x == P2.x && P1.y == P2.y)
	{
		return length = (P1.z > P2.z) ? P1.z - P2.z : P2.z - P1.z;
	}
	else if(P1.z == P2.z && P1.y == P2.y)
	{
		return length = (P1.x > P2.x) ? P1.x - P2.x : P2.x - P1.x;
	}
	else if (P1.x != P2.x && P1.y != P2.y)
	{
		Vector3f point = Vector3f(P1.x, P2.y, P1.z);
		a = (P1.x > point.x) ? P1.x - point.x : point.x - P1.x;
		b = (P2.y > point.y) ? P2.y - point.y : point.y - P2.y;
		return length = sqrt((a * a) + (b * b));
	}
	else if (P1.x != P2.x && P1.z != P2.z)
	{
		Vector3f point = Vector3f(P1.x, P2.y, P2.z);
		a = (P1.z > point.z) ? P1.z - point.z : point.z - P1.z;
		b = (P2.x > point.x) ? P2.x - point.x : point.x - P2.x;
		return length = sqrt((a * a) + (b * b));
	}
	else if (P1.z != P2.z && P1.y != P2.y)
	{
		Vector3f point = Vector3f(P1.x, P2.y, P1.z);
		a = (P1.z > point.z) ? P1.z - point.z : point.z - P1.z;
		b = (P2.y > point.y) ? P2.y - point.y : point.y - P2.y;
		return length = sqrt((a * a) + (b * b));
	}
	

}
int PMath::Clamp(int value, int lower, int upper)
{
	if (value <= lower)
		return lower;
	if (value >= upper)
		return upper;
	return value;
}