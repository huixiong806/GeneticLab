#ifndef FLOOP_H
#define FLOOP_H
#include "cocos2d.h"
#include "Bloop.h"
#include "FloopDNA.h"
//Floop:���������ߣ���GloopΪʳ
class Floop :public Bloop
{
public:
	~Floop();
	//�������
	Floop(cocos2d::Layer& layer, int ZOrder);
	//���׷�ֳ
	Floop(cocos2d::Layer& layer, int ZOrder, Floop& parent);
	//˫�׷�ֳ
	Floop(cocos2d::Layer& layer, int ZOrder, Floop& parentA, Floop& parentB);
	//ÿtickҪ������
	virtual void tick(World& world, std::shared_ptr<Bloop> this_);
private:
	FloopDNA dna;
	//size��32~287����ӳ�䵽speed��10~2
	//����size�����ٶȵĲ���A��B��speed=A+B*size
	const float speedCalcPrmA = 11.004;
	const float speedCalcPrmB = -0.0314;
	//tick��cycle�����ٶ�
	const float cycleIncPerTick = -0.03;
	//��ʳ����,20����(1000ticks)���Խ�ʳһ��
	int eatCD;
	//���ϸ�����ڣ����������
	const float maxCycle = 500;
	virtual void init(cocos2d::Layer& layer, int ZOrder);
	virtual void refreshPosition(cocos2d::Vec2 camera_);
};
#endif
