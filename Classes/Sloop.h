#ifndef SLOOP_H
#define SLOOP_H
#include "cocos2d.h"
#include "Bloop.h"
#include "SloopDNA.h"
using namespace cocos2d;
//Sloop:�μ������ߣ���FloopΪʳ
class Sloop :public Bloop
{
public:
	~Sloop();
	//�������
	Sloop(Layer& layer, int ZOrder);
	//���׷�ֳ
	Sloop(Layer& layer, int ZOrder, Sloop& parent);
	//˫�׷�ֳ
	Sloop(Layer& layer, int ZOrder, Sloop& parentA, Sloop& parentB);
	//ÿtickҪ������
	virtual void tick(World& world);
private:
	SloopDNA dna;
	//size��128~384����ӳ�䵽speed��3.5~1
	//����size�����ٶȵĲ���A��B��speed=A+B*size
	const float speedCalcPrmA = 4.75;
	const float speedCalcPrmB = -0.0098;
	//tick��cycle�����ٶ�
	const float cycleIncPerTick = -0.06;
	//��ʳ����,20����(1000ticks)���Խ�ʳһ��
	int eatCD;
	//���ϸ�����ڣ����������
	const float maxCycle = 800;
	virtual void init(Layer& layer, int ZOrder);
	virtual void refreshPosition(Vec2 camera_);
};
#endif
