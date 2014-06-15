#include "Robo_AI.h"
#include <math.h>

Robo_AI::Robo_AI()
{
}
vector<double> Robo_AI::Dodge(short left, short front, short right, const char* path)
{
	double data[] = { 0 };
	mwArray mLeft(1, 1, mxDOUBLE_CLASS, mxREAL);
	mwArray mFront(1, 1, mxDOUBLE_CLASS, mxREAL);
	mwArray mRight(1, 1, mxDOUBLE_CLASS, mxREAL);
	mwArray mPath(path);
	data[0] = left;
	mLeft.SetData(data, 1);
	data[0] = front;

	mFront.SetData(data, 1);
	data[0] = right;
	mRight.SetData(data, 1);
	mwArray out;
	robot1(1, out, mLeft, mFront, mRight, mPath);
	vector<double> ret;
	ret.push_back(out(1, 1));
	ret.push_back(out(1, 2));
	std::cout << "left" << ret[0];
	return ret;
}
void Robo_AI::Movement(Robot* object, float Left, float Right)
{
	
	if (Left == Right)
	{
		cout << "rowne\n";
		object->Translation.z -= Left;
		return;
	}
	else if (Right == -Left)
	{
		cout << "zero\n";
		object->Rotation.y -= Left;
		/*if ((int)Left == 0 && Left < 0)
			object->Rotation.y -= -1;
		if ((int)Left == 0 && Left > 0)
			object->Rotation.y -= 1;*/
		return;
	}
	else if (Left >= 0 && Right >= 0)
	{
		cout << "wieksze \n";
		object->Translation.z -= (Right > Left) ? Left : Right;
		object->Origin = (Right > Left) ? object->RightWheel : object->LeftWheel;
		object->OriPosition = (Right > Left) ? oLeftWheel : oRightWheel;
		object->Rotation.y -= (Right > Left) ? -(Right - Left) : (Left - Right);
		object->Origin = object->Center;
		return;
	}
	else if ((Left >= 0 && Right <= 0) || (Right >= 0 && Left <= 0))
	{
		cout << "rozne\n";
		if (abs(Left) < abs(Right))
		{
			
			object->Rotation.y -= Left;
		/*	if ((int)Left == 0 && Left < 0)
				object->Rotation.y -= -1;
			if ((int)Left == 0 && Left > 0)
				object->Rotation.y -= 1;*/
		}
		if (abs(Left) > abs(Right))
		{
			object->Rotation.y += Right;
			//if ((int)Right == 0 && Right < 0)
			//	object->Rotation.y += -1;
			//if ((int)Right == 0 && Right > 0)
			//	object->Rotation.y += 1;
		}
		object->Origin = (abs(Right) >= abs(Left)) ? object->LeftWheel : object->RightWheel;
		object->OriPosition = (abs(Right) >= abs(Left)) ? oLeftWheel : oRightWheel;
		object->Rotation.y -= (abs(Right) >= abs(Left)) ? -(Right - Left) : (Left - Right);
		object->Origin = object->Center;
		return;
	}
}

Robo_AI::~Robo_AI()
{
}
