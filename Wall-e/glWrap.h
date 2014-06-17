#pragma once
#include <vector>
#include <sstream>
#include <fstream>
#include "Model.h"
#include <GL\glut.h>
class glWrap
{
public:
	
	~glWrap();
	
	static std::vector<Vector3f> LineOfPoints(Vector3f A, Vector3f B,int length);
	static void Print(int x, int y, std::string);
	//x-red,y-blue,z-green
	static void Axis();
	static Model LoadModel(std::string filename);
private:
	glWrap();
};

