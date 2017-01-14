#ifndef SLOOP_H
#define SLOOP_H
#include "cocos2d.h"
#include "Bloop.h"
//Sloop:�μ������ߣ���FloopΪʳ
class Sloop :public Bloop
{
public:
	~Sloop();
	//�������
	Sloop(cocos2d::Layer& layer, int ZOrder);
	//���׷�ֳ
	Sloop(cocos2d::Layer& layer, int ZOrder, Sloop& parent);
	//˫�׷�ֳ
	Sloop(cocos2d::Layer& layer, int ZOrder, Sloop& parentA, Sloop& parentB);
	//ÿtickҪ������
	virtual void tick(World& world);
private:
	//size��128~384����ӳ�䵽speed��7~2
	//����size�����ٶȵĲ���A��B��speed=A+B*size
	const float speedCalcPrmA = 9.5f;
	const float speedCalcPrmB = -0.0196f;
	//tick��cycle�����ٶ�
	const float cycleIncPerTick = -0.050f;
	//��ʳ����,20����(1000ticks)���Խ�ʳһ��
	int eatCD;
	//���ϸ�����ڣ����������
	const float maxCycle = 800.0f;
	//�������繹�ɵĴ���
	ann::NeuralNetwork brain;
	virtual void initBrain();
	std::tuple<double, double> getNearByInformation(World& world);
	virtual void init(cocos2d::Layer& layer, int ZOrder);
	virtual void move(World& world);
	virtual void refreshPosition(cocos2d::Vec2 camera_);
};
#endif
