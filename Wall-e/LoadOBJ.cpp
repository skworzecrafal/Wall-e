#define _CRT_SECURE_NO_WARNINGS
#include "LoadOBJ.h"

WFObject::WFObject()
{

}

WFObject::~WFObject()
{

}

int WFObject::load(char *filename)
{
	fstream objFile;
	objFile.open(filename);

	if (objFile.is_open())
	{
		char line[255];

		// Parse object file line by line
		while (objFile.good())
		{
			objFile.getline(line, 255);
			parseLine(line);
		}

		objFile.close();
	}
	else
	{
		cout << "Could not open WFObject file '" << filename << "'\n";
		return false;
	}

	return true;
}

void WFObject::parseLine(char *line)
{
	if (!strlen(line))
	{
		return;
	}

	char *lineType;
	lineType = strtok(_strdup(line), " ");

	// Decide what to do
	if (!strcmp(lineType, "v"))		// Vertex
	{
		parseVertex(line);
	}
	else if (!strcmp(lineType, "vn"))	// Normal
	{
		parseNormal(line);
	}
	else if (!strcmp(lineType, "f"))	// Face
	{
		parseFace(line);
	}

	return;
}
void ReduceToUnit(float vector[3])
{
	float length;

	// Calculate the length of the vector		
	length = (float)sqrt((vector[0] * vector[0]) +
		(vector[1] * vector[1]) +
		(vector[2] * vector[2]));

	// Keep the program from blowing up by providing an exceptable
	// value for vectors that may calculated too close to zero.
	if (length == 0.0f)
		length = 1.0f;

	// Dividing each element by the length will result in a
	// unit normal vector.
	vector[0] /= length;
	vector[1] /= length;
	vector[2] /= length;
}


// Points p1, p2, & p3 specified in counter clock-wise order
void calcNormal(float v[3][3], float out[3])
{
	float v1[3], v2[3];
	static const int x = 0;
	static const int y = 1;
	static const int z = 2;

	// Calculate two vectors from the three points
	v1[x] = v[0][x] - v[1][x];
	v1[y] = v[0][y] - v[1][y];
	v1[z] = v[0][z] - v[1][z];

	v2[x] = v[1][x] - v[2][x];
	v2[y] = v[1][y] - v[2][y];
	v2[z] = v[1][z] - v[2][z];

	// Take the cross product of the two vectors to get
	// the normal vector which will be stored in out
	out[x] = v1[y] * v2[z] - v1[z] * v2[y];
	out[y] = v1[z] * v2[x] - v1[x] * v2[z];
	out[z] = v1[x] * v2[y] - v1[y] * v2[x];

	// Normalize the vector (shorten length to one)
	ReduceToUnit(out);
}
// Draw object
void WFObject::draw()
{
	glBegin(GL_TRIANGLES);

	for (int f = 0; f < faces.size(); f++)
	{
		/*float v[3][3]; float out[3];
		v[0][0] = vertices[faces[f].v1 - 1].x;
		v[0][1] = vertices[faces[f].v2 - 1].y;
		v[0][2] = vertices[faces[f].v3 - 1].z;
		v[1][0] = vertices[faces[f].v1 - 1].x;
		v[1][1] = vertices[faces[f].v2 - 1].y;
		v[1][2] = vertices[faces[f].v3 - 1].z;
		v[2][0] = vertices[faces[f].v1 - 1].x;
		v[2][1] = vertices[faces[f].v2 - 1].y;
		v[2][2] = vertices[faces[f].v3 - 1].z;
		calcNormal(v, out);
		glNormal3f(out[0], out[1], out[2]);*/
		glNormal3f(normals[faces[f].vn1 - 1].x, normals[faces[f].vn1 - 1].y, normals[faces[f].vn1 - 1].z);
		glVertex3f(vertices[faces[f].v1 - 1].x, vertices[faces[f].v1 - 1].y, vertices[faces[f].v1 - 1].z);

		glNormal3f(normals[faces[f].vn2 - 1].x, normals[faces[f].vn2 - 1].y, normals[faces[f].vn2 - 1].z);
		glVertex3f(vertices[faces[f].v2 - 1].x, vertices[faces[f].v2 - 1].y, vertices[faces[f].v2 - 1].z);

		glNormal3f(normals[faces[f].vn3 - 1].x, normals[faces[f].vn3 - 1].y, normals[faces[f].vn3 - 1].z);
		glVertex3f(vertices[faces[f].v3 - 1].x, vertices[faces[f].v3 - 1].y, vertices[faces[f].v3 - 1].z);
	}

	glEnd();
}

// Parse a "v" vertex line of the file into our vertices array
void WFObject::parseVertex(char *line)
{
	vertices.push_back(Vector());		// Add a new element to the vertices array

	sscanf(line, "v %f %f %f", &vertices.back().x, &vertices.back().y, &vertices.back().z);

	return;
}

// Parse a "vn" normal line of the file into the normals array
void WFObject::parseNormal(char *line)
{
	normals.push_back(Vector());

	sscanf(line, "vn %f %f %f", &normals.back().x, &normals.back().y, &normals.back().z);

	return;
}

// Parse a "f" face line into the faces array. This gets complex due to there being different line formats.
void WFObject::parseFace(char *line)
{
	int fill = 0;

	faces.push_back(Face());

	// Read face line. If texture indicies aren't present, don't read them.
	if (sscanf(line, "f %d//%d %d//%d %d//%d", &faces.back().v1,
		&faces.back().vn1,
		&faces.back().v2,
		&faces.back().vn2,
		&faces.back().v3,
		&faces.back().vn3) <= 1)
	{
		sscanf(line, "f %d/%d/%d %d/%d/%d %d/%d/%d", &faces.back().v1,
			&fill,
			&faces.back().vn1,
			&faces.back().v2,
			&fill,
			&faces.back().vn2,
			&faces.back().v3,
			&fill,
			&faces.back().vn3);
	}

	return;
}
