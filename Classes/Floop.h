#ifndef FLOOP_H
#define FLOOP_H
#include "cocos2d.h"
#include "Bloop.h"
//Floop:初级消费者，以Gloop为食
class Floop :public Bloop
{
public:
	virtual ~Floop();
	//随机产生
	Floop(cocos2d::Layer& layer, int ZOrder);
	//单亲繁殖
	Floop(cocos2d::Layer& layer, int ZOrder, Floop& parent);
	//双亲繁殖
	Floop(cocos2d::Layer& layer, int ZOrder, Floop& parentA, Floop& parentB);
	//每tick要做的事
	virtual void tick(World& world);
private:
	//size的32~287线性映射到speed的10~2
	//根据size计算速度的参数A和B，speed=A+B*size
	const float speedCalcPrmA = 11.004f;
	const float speedCalcPrmB = -0.0314f;
	//tick的cycle增长速度
	const float cycleIncPerTick = -0.03f;
	//进食周期,20秒钟(1000ticks)可以进食一次
	int eatCD;
	//最大细胞周期，超过则分裂
	const float maxCycle = 500.0f;
	//由神经网络构成的大脑
	ann::NeuralNetwork brain;
	virtual void initBrain();
	std::tuple<double, double, double, double>getNearByInformations(World& world);
	virtual void move(World& world);
	virtual void init(cocos2d::Layer& layer, int ZOrder);
	virtual void refreshPosition(cocos2d::Vec2 camera_);
};
#endif