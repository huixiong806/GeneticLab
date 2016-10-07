#ifndef FOOD_H
#define FOOD_H
#include "cocos2d.h"
#include "Entity.h"
class Food:public Entity
{
public:
	Food(cocos2d::Layer& layer, int ZOrder);
	virtual bool hit(Entity* another);
	static const int energy = 10;
};
#endif