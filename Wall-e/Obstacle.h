#pragma once
#include <GL\glut.h>
#include <GL\gl.h>
#include <GL\glu.h>
#include "Vector3.h"
class Obstacle
{
public:
	Vector3f leftUp;
	Vector3f leftDown;
	Vector3f rightUp;
	Vector3f rightDown;
	Obstacle();
	void Draw();
	~Obstacle();
};

