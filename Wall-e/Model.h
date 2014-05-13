#pragma once
#include <vector>
#include "Vector3.h"

class Model
{
public:
	std::vector<Vector3f> Vertex;
	std::vector<Vector3f> Normal;
	std::vector<Vector3<std::pair<int, int>>> Face;
	std::vector<std::pair<int, int>> as;
	Model();
	~Model();
};

