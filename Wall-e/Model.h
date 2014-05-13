#pragma once
#include <vector>
#include "Vector3.h"

class Model
{
public:
	std::vector<Vector3f> Vertex;
	std::vector<Vector3f> Normal;
	std::vector<Vector3<std::pair<int, int>>> Face;
	//pair<Vertex,Normal> przesuniete o -1 by miec index 0
	std::vector<std::pair<int, int>> as;
	Model();
	~Model();
};

