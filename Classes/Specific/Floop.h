#ifndef FLOOP_H
#define FLOOP_H
#include "cocos2d.h"
#include <Bloop.h>
//Floop:���������ߣ���GloopΪʳ
class Floop :public Bloop
{
public:
	virtual ~Floop();
	//�������
	Floop(cocos2d::Layer& layer, int ZOrder);
	//���׷�ֳ
	Floop(cocos2d::Layer& layer, int ZOrder, Floop& parent);
	//˫�׷�ֳ
	Floop(cocos2d::Layer& layer, int ZOrder, Floop& parentA, Floop& parentB);
	//ÿtickҪ������
	virtual void tick(World& world);
private:
	//size��32~287����ӳ�䵽speed��10~2
	//����size�����ٶȵĲ���A��B��speed=A+B*size
	const float speedCalcPrmA = 11.004f;
	const float speedCalcPrmB = -0.0314f;
	//tick��cycle�����ٶ�
	const float cycleIncPerTick = -0.03f;
	//��ʳ����,20����(1000ticks)���Խ�ʳһ��
	int eatCD;
	//���ϸ�����ڣ����������
	const float maxCycle = 500.0f;
	//�������繹�ɵĴ���
	ann::NeuralNetwork brain;
	virtual void initBrain();
	std::tuple<double, double, double, double>getNearByInformations(World& world);
	virtual void move(World& world);
	virtual void init(cocos2d::Layer& layer, int ZOrder);
	virtual void refreshPosition(cocos2d::Vec2 camera_);
};
#endif