#pragma once
#include <iostream>
#include <string>
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
	Vector3f operator + (const Vector3f &left)
	{
		return Vector3f(x + left.x, y + left.y, z + left.z);
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

