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
	tmp.GLNormal_Vertex = new GLfloat[6];
	tmp.GLFace = new GLubyte[3];
	int sizeN=1, sizeF=1;
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
		//	cout << "Vertex "<<tmp.Vertex[tmp.Vertex.size()-1].ToString() << endl;
			//cout << "x "<<tmp.GLVertex[(sizeV - 1) * 3 - 3] <<"y "<< tmp.GLVertex[(sizeV - 1) * 3 - 2] <<"z "<< tmp.GLVertex[(sizeV - 1) * 3 - 1] << endl;
		}
		else if (type == "vn")
		{
			sizeN++;
			tmp.Normal.push_back(Vector3f());
			in >> tmp.Normal[tmp.Normal.size()-1].x >> tmp.Normal[tmp.Normal.size()-1].y >> tmp.Normal[tmp.Normal.size()-1].z;

			tmp.GLNormal_Vertex[(sizeN - 1) * 6 - 6] = tmp.Normal[tmp.Normal.size() - 1].x;
			tmp.GLNormal_Vertex[(sizeN - 1) * 6 - 5] = tmp.Normal[tmp.Normal.size() - 1].y;
			tmp.GLNormal_Vertex[(sizeN - 1) * 6 - 4] = tmp.Normal[tmp.Normal.size() - 1].z;
			tmp.GLNormal_Vertex[(sizeN - 1) * 6 - 3] = tmp.Vertex[tmp.Normal.size() - 1].x;
			tmp.GLNormal_Vertex[(sizeN - 1) * 6 - 2] = tmp.Vertex[tmp.Normal.size() - 1].y;
			tmp.GLNormal_Vertex[(sizeN - 1) * 6 - 1] = tmp.Vertex[tmp.Normal.size() - 1].z;
			
			/*tmp.GLNormal[(sizeN - 1) * 3 - 3] = tmp.Normal[tmp.Normal.size() - 1].x;
			tmp.GLNormal[(sizeN - 1) * 3 - 2] = tmp.Normal[tmp.Normal.size() - 1].y;
			tmp.GLNormal[(sizeN - 1) * 3 - 1] = tmp.Normal[tmp.Normal.size() - 1].z;*/
			//cout << "normal " <<tmp.Normal[tmp.Normal.size()-1].ToString() << endl;
			//cout << "x " << tmp.GLNormal[(sizeV - 1) * 3 - 3] << "y " << tmp.GLNormal[(sizeV - 1) * 3 - 2] << "z " << tmp.GLNormal[(sizeV - 1) * 3 - 1] << endl;
			GLfloat* temp = new GLfloat[sizeN * 6];
			std::_Copy_impl(tmp.GLNormal_Vertex, tmp.GLNormal_Vertex + (sizeN - 1) * 6, temp);
			delete[] tmp.GLNormal_Vertex;
			tmp.GLNormal_Vertex = temp;
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
			sizeF++;
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

			/*tmp.GLFace[(sizeF - 1) * 6 - 6] = tmp.Face[tmp.Face.size() - 1].x.second;
			tmp.GLFace[(sizeF - 1) * 6 - 5] = tmp.Face[tmp.Face.size() - 1].y.second;
			tmp.GLFace[(sizeF - 1) * 6 - 4] = tmp.Face[tmp.Face.size() - 1].z.second;*/
			tmp.GLFace[(sizeF - 1) * 3 - 3] = tmp.Face[tmp.Face.size() - 1].x.first;
			tmp.GLFace[(sizeF - 1) * 3 - 2] = tmp.Face[tmp.Face.size() - 1].y.first;
			tmp.GLFace[(sizeF - 1) * 3 - 1] = tmp.Face[tmp.Face.size() - 1].z.first;

			GLubyte* temp = new GLubyte[sizeF * 3];
			std::_Copy_impl(tmp.GLFace, tmp.GLFace + (sizeF - 1) * 3, temp);
			delete[] tmp.GLFace;
			tmp.GLFace = temp;

			/*cout << "Face " <<
				tmp.Face[tmp.Face.size() - 1].x.first << tmp.Face[tmp.Face.size() - 1].x.second <<
				tmp.Face[tmp.Face.size() - 1].y.first << tmp.Face[tmp.Face.size() - 1].y.second <<
				tmp.Face[tmp.Face.size() - 1].z.first << tmp.Face[tmp.Face.size() - 1].z.second <<
				endl;*/
		/*	cout << (sizeF - 1) * 6 - 6 <<" : "<< tmp.GLFace[(sizeF - 1) * 6 - 6]
				<< (sizeF - 1) * 6 - 5 << " : " << tmp.GLFace[(sizeF - 1) * 6 - 5]
				<< (sizeF - 1) * 6 - 4 << " : " << tmp.GLFace[(sizeF - 1) * 6 - 4]
				<< (sizeF - 1) * 6 - 3 << " : " << tmp.GLFace[(sizeF - 1) * 6 - 3]
				<< (sizeF - 1) * 6 - 2 << " : " << tmp.GLFace[(sizeF - 1) * 6 - 2]
				<< (sizeF - 1) * 6 - 1 << " : " << tmp.GLFace[(sizeF - 1) * 6 - 1]
				<< endl;*/
			

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
	glColor3f(1, 0, 0);
	glVertex3f(-300, 0, 0);
	glVertex3f(300, 0, 0);
	//y
	glColor3f(0, 0, 1);
	glVertex3f(0,-300, 0);
	glVertex3f(0,300, 0);
	//z
	glColor3f(0, 1, 0);
	glVertex3f(0,0,-300);
	glVertex3f(0,0,300);
	glEnd();


}