#pragma once
#include <vector>
#include "Vector3.h"

class Model
{
public:
	std::vector<Vector3f> Vertex;
	std::vector<Vector3f> Normal;
	std::vector<std::pair<Vector3f,Vector3f>> Face;
	Model();
	~Model();
};

