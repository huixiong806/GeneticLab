#ifndef BLOOP_H
#define BLOOP_H
#include "cocos2d.h"
#include "Entity.h"
#include "DNA.h"
#include "PerlinNoise.h"
#include "Food.h"
class World;
enum class BloopType
{
	gloop,floop,sloop
};
class Bloop :public Entity
{
public:
	virtual ~Bloop();
	virtual void refreshPosition(cocos2d::Vec2 camera_);
	virtual void tick(World& world) = 0;
	virtual void move();
	bool die;
	BloopType bloopType;
	//Ï¸°ûÖÜÆÚ
	float cycle;
protected:
	cocos2d::Label* label;
	PerlinNoise noise;
	unsigned long long noiseX;
	virtual void init(cocos2d::Layer& layer, int ZOrder) = 0;
};
#endif