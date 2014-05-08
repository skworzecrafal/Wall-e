#include "Robo_AI.h"
#include <math.h>

Robo_AI::Robo_AI()
{
}
double* Robo_AI::Dodge(short left, short front, short right, const char* path)
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
	double ret[] = { out(1, 1), out(1, 2) };
	return ret;
}
void Robo_AI::Movement(Sensor object, float Left, float Right)
{
	if (Left == Right)
	{
		object.Translation.z += Left;
	}
	else if (Left + Right <= 0.01)
	{
		object.Rotation.y += (int)Left;
		if ((int)Left == 0 && Left < 0)
			object.Rotation.y += -1;
		if ((int)Left == 0 && Left > 0)
			object.Rotation.y += 1;
	}
	else if (Left > 0 && Right > 0)
	{
		object.Translation.z += (Right > Left) ? (float)Left : (float)Right;
		object.Origin = (Right > Left) ? object.RightWheel : object.LeftWheel;
		object.Rotation.y += (Right > Left) ? -(int)(Right - Left) : (int)(Left - Right);
		object.Origin = object.Center;
	}
	else if ((Left > 0 && Right < 0) || (Right > 0 && Left < 0))
	{
		if (abs(Left) < abs(Right))
		{
			
			object.Rotation.y += (int)Left;
			if ((int)Left == 0 && Left < 0)
				object.Rotation.y += -1;
			if ((int)Left == 0 && Left > 0)
				object.Rotation.y += 1;
		}
		if (abs(Left) > abs(Right))
		{
			object.Rotation.y -= (int)Right;
			if ((int)Right == 0 && Right < 0)
				object.Rotation.y -= -1;
			if ((int)Right == 0 && Right > 0)
				object.Rotation.y -= 1;
		}
		object.Origin = (abs(Right) > abs(Left)) ? object.LeftWheel : object.RightWheel;
		object.Rotation.y += (abs(Right) > abs(Left)) ? -(int)(Right - Left) : (int)(Left - Right);
		object.Origin = object.Center;

	}
}

Robo_AI::~Robo_AI()
{
}
