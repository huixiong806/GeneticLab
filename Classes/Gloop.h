#ifndef GLOOP_H
#define GLOOP_H
#include "cocos2d.h"
#include "Bloop.h"
#include "GloopDNA.h"

//Gloop:������,�ṩʳ��
class Gloop :public Bloop
{
public:
	~Gloop();
	//�������
	Gloop(cocos2d::Layer& layer, int ZOrder);
	//���׷�ֳ
	Gloop(cocos2d::Layer& layer, int ZOrder, Gloop& parent);
	//˫�׷�ֳ
	Gloop(cocos2d::Layer& layer, int ZOrder, Gloop& parentA, Gloop& parentB);
	//ÿtickҪ������
	virtual void tick(World& world, std::shared_ptr<Bloop> this_);
private:
	GloopDNA dna;
	//size��32~63����ӳ�䵽speed��12~9
	//����size�����ٶȵĲ���A��B��speed=A+B*size
	const float speedCalcPrmA = 15.09678;
	const float speedCalcPrmB = -0.09678;
	//tick��cycle�����ٶ�
	const float cycleIncPerTick = 0.1;
	//���ϸ�����ڣ����������
	const float maxCycle = 265;
	//ÿtick����ʳ��ĸ��ʣ���Χ��0~1֮�䡣
	float FoodProvideRatePerTick();
	virtual void init(cocos2d::Layer& layer, int ZOrder);
	virtual void refreshPosition(cocos2d::Vec2 camera_);
};
#endif
