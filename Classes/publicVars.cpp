#include"publicVars.h"
namespace const_parameter
{
	const cocos2d::Size smallSize(512, 384);
	const cocos2d::Size mediumSize(1024, 768);
	const cocos2d::Size largeSize(2048, 1536);
	const cocos2d::Size hugeSize(4096, 3072);
	const cocos2d::Size superHugeSize(8192, 6144);
	const cocos2d::Size chunkSize(384, 384);
}
namespace parameter
{
	cocos2d::Size worldSize = cocos2d::Size(0, 0);
	cocos2d::Size chunkCount = cocos2d::Size(0, 0);
	int gloopMinSize = 32;
	int gloopSizeDNALength = 5;
	int gloopBrainDNALength = 35;
	int floopMinSize = 32;
	int floopSizeDNALength = 8;
	int floopBrainDNALength = 43;
	int sloopMinSize = 128;
	int sloopSizeDNALength = 8;
	int sloopBrainDNALength = 35;
	float sunEnergyPerTick = 40.0f;//每tick流入生态系统的能量
	float energyTransferEfficiency = 0.3f;
	//初始cycle的系数,startCycle=startCycleCoefficient*maxCycle
	float gloopStartCycleCoefficient = 1.0f / 4.0f;
	float floopStartCycleCoefficient = 1.0f / 6.0f;
	float sloopStartCycleCoefficient = 1.0f / 6.0f;
	//基因突变率
	float gloopGeneMutationRate = 0.02f;
	float floopGeneMutationRate = 0.02f;
	float sloopGeneMutationRate = 0.02f;
}
double function::sigmoid(double x)
{
	return 2 * MATH_PI / (1.0 + pow(MATH_E, -x));
}
double function::halfStep(double x)
{
	return x > 0 ? x : 0;
}
double function::map(double value, double srcMin, double srcMax, double dstMin, double dstMax)
{
	return	((value - srcMin)*(dstMax - dstMin) / (srcMax - srcMin)) + dstMin;
}