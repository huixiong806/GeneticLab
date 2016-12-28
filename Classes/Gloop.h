#ifndef GLOOP_H
#define GLOOP_H
#include "cocos2d.h"
#include "Bloop.h"
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
	virtual void tick(World& world);
private:
	//size��32~63����ӳ�䵽speed��12~9
	//����size�����ٶȵĲ���A��B��speed=A+B*size
	const float speedCalcPrmA = 15.09678f;
	const float speedCalcPrmB = -0.09678f;
	//tick��cycle�����ٶ�
	const float cycleIncPerTick = 0.1f;
	//���ϸ�����ڣ����������
	const float maxCycle = 265.0f;
	//ÿtick����ʳ��ĸ��ʣ���Χ��0~1֮�䡣
	float FoodProvideRatePerTick();
	//�������繹�ɵĴ���
	ann::NeuralNetwork brain;
	virtual void initBrain();
	virtual void init(cocos2d::Layer& layer, int ZOrder);
	virtual void move(World& world);
	virtual std::pair<double,double> getNearestBloop(World& world);
	virtual void refreshPosition(cocos2d::Vec2 camera_);
};
#endif
