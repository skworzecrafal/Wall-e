#include "Robo_AI.h"


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


Robo_AI::~Robo_AI()
{
}
