#ifndef BLOOP_H
#define BLOOP_H
#include "cocos2d.h"
#include "Entity.h"
#include "DNA.h"
#include "PerlinNoise.h"
#include "Food.h"
class World;
class Chunk;
enum class BloopType
{
	gloop,floop,sloop
};
class Bloop :public Entity
{
public:
	virtual ~Bloop();
	virtual void refreshPosition(cocos2d::Vec2 camera_);
	virtual void tick(World& world, std::shared_ptr<Bloop> this_) = 0;
	virtual void move(World& world, std::shared_ptr<Bloop> this_);
	virtual void OutOfRangeCheck();
	//���Լ��ӵ�ĳ��chunk��
	virtual void addToChunk(Chunk& chunk, std::shared_ptr<Bloop> this_);
	//��ĳ��chunk�����
	virtual void removeFromChunk(Chunk& chunk, std::shared_ptr<Bloop> this_);
	//��ȡ�ٽ���9��chunk
	virtual std::vector<Chunk*> getNineNearByChunks(World& world);
	bool die;
	BloopType bloopType;
	//ϸ������
	float cycle;
protected:
	cocos2d::Label* label;
	PerlinNoise noise;
	unsigned long long noiseX;
	virtual void init(cocos2d::Layer& layer, int ZOrder) = 0;
};
#endif