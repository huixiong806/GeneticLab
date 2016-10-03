#ifndef FLOOP_H
#define FLOOP_H
#include "cocos2d.h"
#include "Bloop.h"
#include "FloopDNA.h"
using namespace cocos2d;
//Floop:初级消费者，以Gloop为食
class Floop :public Bloop
{
public:
	~Floop();
	//随机产生
	Floop(Layer& layer, int ZOrder);
	//单亲繁殖
	Floop(Layer& layer, int ZOrder, Floop& parent);
	//双亲繁殖
	Floop(Layer& layer, int ZOrder, Floop& parentA, Floop& parentB);
	//每tick要做的事
	virtual void tick(World& world);
private:
	FloopDNA dna;
	//size的32~287线性映射到speed的5~1
	//根据size计算速度的参数A和B，speed=A+B*size
	const float speedCalcPrmA = 5.502;
	const float speedCalcPrmB = -0.0157;
	//tick的cycle增长速度
	const float cycleIncPerTick = -0.03;
	//进食周期,20秒钟(1000ticks)可以进食一次
	int eatCD;
	//最大细胞周期，超过则分裂
	const float maxCycle = 500;
	virtual void init(Layer& layer, int ZOrder);
	virtual void refreshPosition(Vec2 camera_);
};
#endif
