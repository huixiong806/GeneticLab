#ifndef PUBLIC_VARS_H
#define PUBLIC_VARS_H
#include"cocos2d.h"
#define PI 3.14159265358979
#define E  2.71828182845905
namespace parameter
{
	static cocos2d::Size smallSize = cocos2d::Size(512, 384);
	static cocos2d::Size mediumSize = cocos2d::Size(1024, 768);
	static cocos2d::Size largeSize = cocos2d::Size(2048, 1536);
	static cocos2d::Size hugeSize = cocos2d::Size(4096, 3072);
	static cocos2d::Size superHugeSize = cocos2d::Size(8192, 6144);
	static cocos2d::Size chunkSize = cocos2d::Size(384, 384);
	static const int gloopMinSize = 32;
	static const int gloopSizeDNALength = 5;
	static const int gloopBrainDNALength = 35;
	static const int floopMinSize = 32;
	static const int floopSizeDNALength = 8;
	static const int floopBrainDNALength = 43;
	static const int sloopMinSize = 128;
	static const int sloopSizeDNALength = 8;
	static const int sloopBrainDNALength = 35;
	static float sunEnergyPerTick = 40.0f;//每tick流入生态系统的能量
	static float energyTransferEfficiency = 0.3f;
	//初始cycle的系数,startCycle=startCycleCoefficient*maxCycle
	static float gloopStartCycleCoefficient = 1.0f/4.0f;
	static float floopStartCycleCoefficient = 1.0f/6.0f;
	static float sloopStartCycleCoefficient = 1.0f/6.0f;
	//基因突变率
	static float gloopGeneMutationRate = 0.02f;
	static float floopGeneMutationRate = 0.02f;
	static float sloopGeneMutationRate = 0.02f;
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
