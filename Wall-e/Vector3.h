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


