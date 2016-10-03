#ifndef PUBLIC_VARS_H
#define PUBLIC_VARS_H
#include"cocos2d.h"
#define PI 3.14159265358979
#define worldSizeX 16384
#define worldSizeY 12288
namespace publicVars
{
	static cocos2d::Size smallSize = cocos2d::Size(512, 384);
	static cocos2d::Size mediumSize = cocos2d::Size(1024, 768);
	static cocos2d::Size largeSize = cocos2d::Size(2048, 1536);
	static cocos2d::Size hugeSize = cocos2d::Size(4096, 3072);
	static cocos2d::Size superHugeSize = cocos2d::Size(8192, 6144);
	extern cocos2d::Director* director;
	extern cocos2d::GLView* glview;
	static float energyTransferEfficiency = 0.3;
}
#endif
