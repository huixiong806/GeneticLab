#ifndef BLOOP_H
#define BLOOP_H
#include "cocos2d.h"
#include "Entity.h"
#include "DNA.h"
#include "PerlinNoise.h"
#include "Food.h"
#include "NeuralNetwork.h"
class World;
class Chunk;
enum class BloopType
{
	gloop,floop,sloop
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
	//把自己加到某个chunk中
	virtual void addToChunk(Chunk& chunk);
	//从某个chunk中清除
	virtual void removeFromChunk(Chunk& chunk);
	//移动到某个位置
	virtual void moveTo(cocos2d::Vec2 newPosition, World& world);
	//获取临近的9个chunk
	virtual std::vector<Chunk*> getNineNearByChunks(World& world);
	bool die;
	BloopType bloopType;
	//细胞周期
	float cycle;
protected:
	float maxSpeed;
	PerlinNoise noise;
	cocos2d::Vec2 noiseOff;
	DNA dna;
	virtual void init(cocos2d::Layer& layer, int ZOrder) = 0;
};
#endif