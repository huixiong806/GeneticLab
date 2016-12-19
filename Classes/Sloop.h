#ifndef SLOOP_H
#define SLOOP_H
#include "cocos2d.h"
#include "Bloop.h"
#include "SloopDNA.h"
//Sloop:次级消费者，以Floop为食
class Sloop :public Bloop
{
public:
	~Sloop();
	//随机产生
	Sloop(cocos2d::Layer& layer, int ZOrder);
	//单亲繁殖
	Sloop(cocos2d::Layer& layer, int ZOrder, Sloop& parent);
	//双亲繁殖
	Sloop(cocos2d::Layer& layer, int ZOrder, Sloop& parentA, Sloop& parentB);
	//每tick要做的事
	virtual void tick(World& world, std::shared_ptr<Bloop> this_);
private:
	SloopDNA dna;
	//size的128~384线性映射到speed的7~2
	//根据size计算速度的参数A和B，speed=A+B*size
	const float speedCalcPrmA = 9.5;
	const float speedCalcPrmB = -0.0196;
	//tick的cycle增长速度
	const float cycleIncPerTick = -0.070;
	//进食周期,20秒钟(1000ticks)可以进食一次
	int eatCD;
	//最大细胞周期，超过则分裂
	const float maxCycle = 800;
	virtual void init(cocos2d::Layer& layer, int ZOrder);
	virtual void refreshPosition(cocos2d::Vec2 camera_);
};
#endif
