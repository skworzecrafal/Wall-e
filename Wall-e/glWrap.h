#pragma once
#include <vector>
#include "Vector3.h"
#include <GL\glut.h>
class glWrap
{
public:
	
	~glWrap();
	
	static std::vector<Vector3f> LineOfPoints(Vector3f A, Vector3f B);
	static void Print(int x, int y, std::string);
	//x-red,y-blue,z-green
	static void Axis();
private:
	glWrap();
};

