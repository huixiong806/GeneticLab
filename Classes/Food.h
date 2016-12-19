#ifndef FOOD_H
#define FOOD_H
#include "cocos2d.h"
#include "Entity.h"
class World;
class Chunk;
class Food:public Entity
{
public:
	Food(cocos2d::Layer& layer, int ZOrder);
	virtual bool hit(Entity* another);
	static const int energy = 10;
	//把自己加到某个chunk中
	virtual void addToChunk(Chunk& chunk, std::shared_ptr<Food> this_);
	//从某个chunk中清除
	virtual void removeFromChunk(Chunk& chunk, std::shared_ptr<Food> this_);
};
#endif