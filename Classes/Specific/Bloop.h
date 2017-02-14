#ifndef BLOOP_H
#define BLOOP_H
#include "cocos2d.h"
#include <Entity.h>
#include <DNA.h>
#include <PerlinNoise.h>
#include <Food.h>
#include <NeuralNetwork.h>
class World;
class Chunk;
enum class BloopType
{
	gloop, floop, sloop
};
class Bloop :public Entity,std::enable_shared_from_this<Bloop>
{
public:
	Bloop(){}
	virtual ~Bloop();
	virtual void refreshPosition(cocos2d::Vec2 camera_);
	virtual void tick(World& world) = 0;
	virtual void move(World& world);
	virtual void OutOfRangeCheck();
	//���Լ��ӵ�ĳ��chunk��
	virtual void addToChunk(Chunk& chunk);
	//��ĳ��chunk�����
	virtual void removeFromChunk(Chunk& chunk);
	//�ƶ���ĳ��λ��
	virtual void moveTo(cocos2d::Vec2 newPosition, World& world);
	bool die;
	BloopType bloopType;
	//ϸ������
	float cycle;
protected:
	float maxSpeed;
	PerlinNoise noise;
	cocos2d::Vec2 noiseOff;
	DNA dna;
	virtual void init(cocos2d::Layer& layer, int ZOrder) = 0;
};
#endif