#ifndef SLOOP_H
#define SLOOP_H
#include "cocos2d.h"
#include "Bloop.h"
#include "SloopDNA.h"
using namespace cocos2d;
//Sloop:次级消费者，以Floop为食
class Sloop :public Bloop
{
public:
	~Sloop();
	//随机产生
	Sloop(Layer& layer, int ZOrder);
	//单亲繁殖
	Sloop(Layer& layer, int ZOrder, Sloop& parent);
	//双亲繁殖
	Sloop(Layer& layer, int ZOrder, Sloop& parentA, Sloop& parentB);
	//每tick要做的事
	virtual void tick(World& world);
private:
	SloopDNA dna;
	//size的128~384线性映射到speed的7~2
	//根据size计算速度的参数A和B，speed=A+B*size
	const float speedCalcPrmA = 9.5;
	const float speedCalcPrmB = -0.0196;
	//tick的cycle增长速度
	const float cycleIncPerTick = -0.06;
	//进食周期,20秒钟(1000ticks)可以进食一次
	int eatCD;
	//最大细胞周期，超过则分裂
	const float maxCycle = 800;
	virtual void init(Layer& layer, int ZOrder);
	virtual void refreshPosition(Vec2 camera_);
};
#endif
