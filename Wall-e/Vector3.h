#pragma once
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
	Vector3f()
	{
		x = y = z = 0;
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


