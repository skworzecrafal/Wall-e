#include "glWrap.h"

glWrap::glWrap()
{
}
glWrap::~glWrap()
{
}


std::vector<Vector3f> glWrap::LineOfPoints(Vector3f A, Vector3f B)
{
	glBegin(GL_POINTS);
	glColor3b(100, 0, 100);
	std::vector<Vector3f> vec;
	for (float t = 0; t < 30; t = t + 0.005)
	{
		float x = (B.x - A.x) * t + A.x;
		float y = (B.y - A.y) * t + A.y;
		float z = (B.z - A.z) * t + A.z;
		glVertex3f(x, y, z);
		vec.push_back(Vector3f(x, y, z));
	}

	glEnd();
	return vec;
}
void glWrap::Axis()
{
	glBegin(GL_LINES);
	//x
	glColor3f(100, 0, 0);
	glVertex3f(-300, 0, 0);
	glVertex3f(300, 0, 0);
	//y
	glColor3f(0, 0, 100);
	glVertex3f(0,-300, 0);
	glVertex3f(0,300, 0);
	//z
	glColor3f(0, 100, 0);
	glVertex3f(0,0,-300);
	glVertex3f(0,0,300);
	glEnd();


}