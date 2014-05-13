#include "glWrap.h"

glWrap::glWrap()
{
}
glWrap::~glWrap()
{
}
void glWrap::Print(int x, int y, std::string str)
{
	glColor3f(1, 0, 0);
	glRasterPos2f(x, y);
	int len, i;
	std::vector<char> chars(str.c_str(), str.c_str() + str.size() + 1u);
	len = chars.size();
	for (i = 0; i < len; i++) {
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, chars[i]);
	}
}

Model glWrap::LoadModel(std::string filepath)
{

	std::ifstream infile(filepath);
	Model tmp;
	std::string line;
	while (std::getline(infile, line))
	{
		std::istringstream in(line);      //make a stream for the line itself
		std::string type;
		in >> type;                  //and read the first whitespace-separated token
		if (type == "v")       //and check its value
		{
			tmp.Vertex.push_back(Vector3f());
			in >> tmp.Vertex[tmp.Vertex.size()-1].x >> tmp.Vertex[tmp.Vertex.size()-1].y >> tmp.Vertex[tmp.Vertex.size()-1].z;       //now read the whitespace-separated floats
			cout << "Vertex "<<tmp.Vertex[tmp.Vertex.size()-1].ToString() << endl;
		}
		else if (type == "vn")
		{
			tmp.Normal.push_back(Vector3f());
			in >> tmp.Normal[tmp.Normal.size()-1].x >> tmp.Normal[tmp.Normal.size()-1].y >> tmp.Normal[tmp.Normal.size()-1].z;
			cout << "normal " <<tmp.Normal[tmp.Normal.size()-1].ToString() << endl;
		}
		else if (type == "f")
		{
			for (int i = 0; i < line.length(); i++)
			{
				if (line[i] == '/')
				{
					if (line[i + 1] == '/')
					{
						line[i] =' ';
						line.erase(i + 1, 1);
					}
				}
			}
			std::stringstream in(line);
			char a;
			tmp.Face.push_back(Vector3<std::pair<int,int>>());
			cout << line << endl;
			in >> a >> 
				tmp.Face[tmp.Face.size() - 1].x.first >> tmp.Face[tmp.Face.size() - 1].x.second >>
				tmp.Face[tmp.Face.size() - 1].y.first >> tmp.Face[tmp.Face.size() - 1].y.second >>
				tmp.Face[tmp.Face.size() - 1].z.first >> tmp.Face[tmp.Face.size() - 1].z.second;
			tmp.Face[tmp.Face.size() - 1].x.first -= 1;
			tmp.Face[tmp.Face.size() - 1].x.second -= 1;
			tmp.Face[tmp.Face.size() - 1].y.first -= 1;
			tmp.Face[tmp.Face.size() - 1].y.second -= 1;
			tmp.Face[tmp.Face.size() - 1].z.first -= 1;
			tmp.Face[tmp.Face.size() - 1].z.second -= 1;
			cout << "Face " <<
				tmp.Face[tmp.Face.size() - 1].x.first << tmp.Face[tmp.Face.size() - 1].x.second <<
				tmp.Face[tmp.Face.size() - 1].y.first << tmp.Face[tmp.Face.size() - 1].y.second <<
				tmp.Face[tmp.Face.size() - 1].z.first << tmp.Face[tmp.Face.size() - 1].z.second <<
				endl;
			

		}
	}
	return tmp;
}
std::vector<Vector3f> glWrap::LineOfPoints(Vector3f A, Vector3f B)
{
	glBegin(GL_POINTS);
	glColor3b(100, 0, 100);
	std::vector<Vector3f> vec;
	for (float t = 0; t < 10; t = t + 10.0/60.0)
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