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
	//���Լ��ӵ�ĳ��chunk��
	virtual void addToChunk(Chunk& chunk, std::shared_ptr<Food> this_);
	//��ĳ��chunk�����
	virtual void removeFromChunk(Chunk& chunk, std::shared_ptr<Food> this_);
};
#endif