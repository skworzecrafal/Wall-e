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
	GLfloat *GLVertex;
	GLfloat *GLNormal;
	GLfloat *GLFace;



	std::vector<std::pair<int, int>> as;
	Model();
	~Model();
};

