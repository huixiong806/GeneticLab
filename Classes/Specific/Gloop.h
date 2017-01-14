#ifndef GLOOP_H
#define GLOOP_H
#include "cocos2d.h"
#include "Bloop.h"
//Gloop:生产者,提供食物
class Gloop :public Bloop
{
public:
	~Gloop();
	//随机产生
	Gloop(cocos2d::Layer& layer, int ZOrder);
	//单亲繁殖
	Gloop(cocos2d::Layer& layer, int ZOrder, Gloop& parent);
	//双亲繁殖
	Gloop(cocos2d::Layer& layer, int ZOrder, Gloop& parentA, Gloop& parentB);
	//每tick要做的事
	virtual void tick(World& world);
private:
	//size的32~63线性映射到speed的12~9
	//根据size计算速度的参数A和B，speed=A+B*size
	const float speedCalcPrmA = 15.09678f;
	const float speedCalcPrmB = -0.09678f;
	//tick的cycle增长速度
	const float cycleIncPerTick = 0.1f;
	//最大细胞周期，超过则分裂
	const float maxCycle = 265.0f;
	//每tick产生食物的概率，范围在0~1之间。
	float FoodProvideRatePerTick();
	//由神经网络构成的大脑
	ann::NeuralNetwork brain;
	virtual void initBrain();
	virtual void init(cocos2d::Layer& layer, int ZOrder);
	virtual void move(World& world);
	virtual std::pair<double,double> getNearestBloop(World& world);
	virtual void refreshPosition(cocos2d::Vec2 camera_);
};
#endif
