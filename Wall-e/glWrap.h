#pragma once
#include <vector>
#include "Vector3.h"

class glWrap
{
public:
	
	~glWrap();
	//template<typename T>
	//static void LineOfPoints(std::vector < Vector3<T> Points)
	//{
		//float A[] = { 0, 0, 0 };
		//float B[] = { 5, 5, 5 };
		//glBegin(GL_POINTS);
		//glColor3b(100, 0, 100);
		//for (float t = 0; t < 100; t = t + 0.05)
		//{
		//	float x = (B[0] - A[0]) * t + A[0];
		//	float y = (B[0] - A[0]) * t + A[1];
		//	float z = (B[0] - A[0]) * t + A[2];
		//	glVertex3f(x, y, z);
		//}
		//glEnd();
	//}
	//x-red,y-blue,z-green
	static void Axis();
private:
	glWrap();
};

