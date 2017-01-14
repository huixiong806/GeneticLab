#ifndef PARAMETER_H
#define PARAMETER_H
#include <unordered_set>
#include "cocos2d.h"
class Bloop;
class Food;
constexpr double MATH_PI = 3.14159265358979;
constexpr double MATH_E = 2.71828182845905;
using bloopPool = std::unordered_set<std::shared_ptr<Bloop>>;
using foodPool = std::unordered_set<std::shared_ptr<Food>>;
namespace const_parameter
{	
	extern const cocos2d::Size smallSize;
	extern const cocos2d::Size mediumSize;
	extern const cocos2d::Size largeSize;
	extern const cocos2d::Size hugeSize;
	extern const cocos2d::Size superHugeSize;
	extern const cocos2d::Size chunkSize;
}
namespace parameter
{
	extern int gloopMinSize;
	extern int gloopSizeDNALength;
	extern int gloopBrainDNALength;
	extern int floopMinSize;
	extern int floopSizeDNALength ;
	extern int floopBrainDNALength;
	extern int sloopMinSize;
	extern int sloopSizeDNALength;
	extern int sloopBrainDNALength;
	extern float sunEnergyPerTick;//每tick流入生态系统的能量
	extern float energyTransferEfficiency;
	//初始cycle的系数,startCycle=startCycleCoefficient*maxCycle
	extern float gloopStartCycleCoefficient;
	extern float floopStartCycleCoefficient;
	extern float sloopStartCycleCoefficient;
	//基因突变率
	extern float gloopGeneMutationRate;
	extern float floopGeneMutationRate;
	extern float sloopGeneMutationRate;
	extern cocos2d::Size worldSize;
	extern cocos2d::Size chunkCount;
}
namespace function
{
	double sigmoid(double x);
	double halfStep(double x);
	double map(double value, double srcMin, double srcMax, double dstMin, double dstMax);
}
#endif
