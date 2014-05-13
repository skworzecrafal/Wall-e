#pragma once
#include <vector>
#include <GL\glut.h>
#include <GL\gl.h>
#include <GL\glu.h>
#include "Vector3.h"

class Model
{
public:
	std::vector<Vector3f> Vertex;
	std::vector<Vector3f> Normal;
	//pair<Vertex,Normal> przesuniete o -1 by miec index 0
	std::vector<Vector3<std::pair<int, int>>> Face;
	GLfloat *GLNormal_Vertex;
	GLubyte *GLFace;

	Model();
	~Model();
};

