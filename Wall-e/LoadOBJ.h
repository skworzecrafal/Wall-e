#ifndef _WAVEFRONT_LOADER_H_
#define _WAVEFRONT_LOADER_H_

#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <GL/glut.h>
using namespace std;



typedef struct
{
	float x;
	float y;
	float z;
}
Vector;

typedef struct
{
	int v1, v2, v3;
	int vn1, vn2, vn3;
}
Face;

class WFObject
{
private:
	// Dynamic variables to keep our object data in
	vector<Vector> vertices;
	vector<Vector> normals;
	vector<Face> faces;

	void parseLine(char *line);

	void parseVertex(char *line);
	void parseNormal(char *line);
	void parseFace(char *line);

public:
	WFObject();
	~WFObject();

	int load(char *filename);
	void draw();
};

#endif