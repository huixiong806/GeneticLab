#ifndef PUBLIC_VARS_H
#define PUBLIC_VARS_H
#include"cocos2d.h"
#define PI 3.14159265358979
//#define worldSizeX 8192
//#define worldSizeY 6144
namespace parameter
{
	static cocos2d::Size smallSize = cocos2d::Size(512, 384);
	static cocos2d::Size mediumSize = cocos2d::Size(1024, 768);
	static cocos2d::Size largeSize = cocos2d::Size(2048, 1536);
	static cocos2d::Size hugeSize = cocos2d::Size(4096, 3072);
	static cocos2d::Size superHugeSize = cocos2d::Size(8192, 6144);
	static cocos2d::Size chunkSize = cocos2d::Size(384, 384);
	extern cocos2d::Size worldSize;
	extern cocos2d::Size chunkCount;
	static float sunEnergyPerTick = 60.0;//每tick流入生态系统的能量
	static float energyTransferEfficiency = 0.3;
	extern int gloopCount;
}
#endif
