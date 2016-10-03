#ifndef FLOOP_H
#define FLOOP_H
#include "cocos2d.h"
#include "Bloop.h"
#include "FloopDNA.h"
using namespace cocos2d;
//Floop:���������ߣ���GloopΪʳ
class Floop :public Bloop
{
public:
	~Floop();
	//�������
	Floop(Layer& layer, int ZOrder);
	//���׷�ֳ
	Floop(Layer& layer, int ZOrder, Floop& parent);
	//˫�׷�ֳ
	Floop(Layer& layer, int ZOrder, Floop& parentA, Floop& parentB);
	//ÿtickҪ������
	virtual void tick(World& world);
private:
	FloopDNA dna;
	//size��32~287����ӳ�䵽speed��5~1
	//����size�����ٶȵĲ���A��B��speed=A+B*size
	const float speedCalcPrmA = 5.502;
	const float speedCalcPrmB = -0.0157;
	//tick��cycle�����ٶ�
	const float cycleIncPerTick = -0.03;
	//��ʳ����,20����(1000ticks)���Խ�ʳһ��
	int eatCD;
	//���ϸ�����ڣ����������
	const float maxCycle = 500;
	virtual void init(Layer& layer, int ZOrder);
	virtual void refreshPosition(Vec2 camera_);
};
#endif
