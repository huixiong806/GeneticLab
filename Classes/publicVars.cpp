#include"publicVars.h"
cocos2d::Size parameter::worldSize = cocos2d::Size(0,0);
cocos2d::Size parameter::chunkCount = cocos2d::Size(0,0);
double function::sigmoid(double x)
{
	return 2*PI / (1.0 + pow(E, -x));
}
double function::halfStep(double x)
{
	return x > 0 ? x : 0;
}
double function::map(double value, double srcMin, double srcMax, double dstMin, double dstMax)
{
	return	((value - srcMin)*(dstMax - dstMin) / (srcMax - srcMin)) + dstMin;
}