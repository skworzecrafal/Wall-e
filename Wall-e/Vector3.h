#pragma once
#include <iostream>
#include <string>
#include <math.h>
template<typename T>class Vector3
{
public:
	T x,y,z;
	Vector3()
	{
	}
	Vector3(T x, T y, T z)
	{
		this->x = x;
		this->y = y;
		this->z= z;
	}
	~Vector3()
	{
	}
};
struct Vector3f
{
	float x, y, z;
	Vector3f(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
	Vector3f(int x, int y, int z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
	Vector3f operator + (const Vector3f &second)
	{
		return Vector3f(x + second.x, y + second.y, z + second.z);
	}
	Vector3f operator * (const Vector3f &second)
	{
		return Vector3f(x*second.x, y*second.y, z*second.z);
	}

	Vector3f()
	{
		x = y = z = 0;
	}
	std::string ToString()
	{
		return std::string("x: "+std::to_string(x) +"y: "+ std::to_string(y) + "z: "+std::to_string(z));
	}
};
struct Vector3i
{
	int x, y, z;
	Vector3i(int x, int y, int z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
	Vector3i(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
	Vector3i()
	{
		x = y = z = 0;
	}
};
struct Vector4f
{
	Vector4f()
	{
		x = y = z = w = 0;
	}
	Vector4f(float x, float y, float z, float w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}
	float x, y, z, w;
	float operator * (const Vector4f &second)
	{
		return x*second.x+y*second.y+ z*second.z +w*second.w;
	}
};
struct Matrixf
{
	Vector4f a, b, c, d;
	
	Matrixf()
	{
	}
	//Y-axis Rotation
	Matrixf(float alfa)
	{
		alfa = (alfa / 180.0) * 3.14;
		a = Vector4f(cos(alfa), 0, sin(alfa), 0);
		b = Vector4f(0, 1, 0, 0);
		c = Vector4f(-sin(alfa), 0, cos(alfa), 0);
		d = Vector4f(0, 0, 0, 1);
	}
	//Translation
	Matrixf(Vector3f v)
	{
		a = Vector4f(1, 0, 0, v.x);
		b = Vector4f(0, 1, 0, v.y);
		c = Vector4f(0, 0, 1, v.z);
		d = Vector4f(0, 0, 0, 1);
	}
	Matrixf(float x, float y, float z)
	{
		a = Vector4f(1, 0, 0, x);
		b = Vector4f(0, 1, 0, y);
		c = Vector4f(0, 0, 1, z);
		d = Vector4f(0, 0, 0, 1);
	}
	Vector3f operator *(const Vector3f &right)
	{
		Vector4f tmp;
		tmp.x = a.x*right.x + a.y*right.y + a.z*right.z + a.w;
		tmp.y = b.x*right.x + b.y*right.y + b.z*right.z + b.w;
		tmp.z = c.x*right.x + c.y*right.y + c.z*right.z + c.w;
		tmp.w = d.x*right.x + d.y*right.y + d.z*right.z + d.w;
		Vector3f out(tmp.x, tmp.y, tmp.z);
		return out;
	}
	Matrixf operator *(const Matrixf &r)
	{
		Matrixf tmp;
		tmp.a.x = a*Vector4f(r.a.x, r.b.x, r.c.x, r.d.x);
		tmp.b.x = b*Vector4f(r.a.x, r.b.x, r.c.x, r.d.x);
		tmp.c.x = c*Vector4f(r.a.x, r.b.x, r.c.x, r.d.x);
		tmp.d.x = d*Vector4f(r.a.x, r.b.x, r.c.x, r.d.x);

		tmp.a.y = a*Vector4f(r.a.y, r.b.y, r.c.y, r.d.y);
		tmp.b.y = b*Vector4f(r.a.y, r.b.y, r.c.y, r.d.y);
		tmp.c.y = c*Vector4f(r.a.y, r.b.y, r.c.y, r.d.y);
		tmp.d.y = d*Vector4f(r.a.y, r.b.y, r.c.y, r.d.y);

		tmp.a.z = a*Vector4f(r.a.z, r.b.z, r.c.z, r.d.z);
		tmp.b.z = b*Vector4f(r.a.z, r.b.z, r.c.z, r.d.z);
		tmp.c.z = c*Vector4f(r.a.z, r.b.z, r.c.z, r.d.z);
		tmp.d.z = d*Vector4f(r.a.z, r.b.z, r.c.z, r.d.z);

		tmp.a.w = a*Vector4f(r.a.w, r.b.w, r.c.w, r.d.w);
		tmp.b.w = b*Vector4f(r.a.w, r.b.w, r.c.w, r.d.w);
		tmp.c.w = c*Vector4f(r.a.w, r.b.w, r.c.w, r.d.w);
		tmp.d.w = d*Vector4f(r.a.w, r.b.w, r.c.w, r.d.w);
		return tmp;
	}
};

