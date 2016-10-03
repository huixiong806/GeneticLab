#ifndef GLOOP_H
#define GLOOP_H
#include "cocos2d.h"
#include "Bloop.h"
#include "GloopDNA.h"
using namespace cocos2d;
//Gloop:������,�ṩʳ��
class Gloop :public Bloop
{
public:
	~Gloop();
	//�������
	Gloop(Layer& layer, int ZOrder);
	//���׷�ֳ
	Gloop(Layer& layer, int ZOrder, Gloop& parent);
	//˫�׷�ֳ
	Gloop(Layer& layer, int ZOrder, Gloop& parentA, Gloop& parentB);
	//ÿtickҪ������
	virtual void tick(World& world);
	
private:
	GloopDNA dna;
	//size��32~63����ӳ�䵽speed��6~4.5
	//����size�����ٶȵĲ���A��B��speed=A+B*size
	const float speedCalcPrmA = 7.54839 ;
	const float speedCalcPrmB = -0.04839;
	//tick��cycle�����ٶ�
	const float cycleIncPerTick = 0.1;
	//���ϸ�����ڣ����������
	const float maxCycle = 265;
	//ÿtick����ʳ��ĸ��ʣ���Χ��0~1֮�䡣
	float FoodProvideRatePerTick();
	virtual void init(Layer& layer, int ZOrder);
	virtual void refreshPosition(Vec2 camera_);
};
#endif
