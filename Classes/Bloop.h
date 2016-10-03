#ifndef BLOOP_H
#define BLOOP_H
#include "cocos2d.h"
#include "Entity.h"
#include "DNA.h"
#include "PerlinNoise.h"
#include "Food.h"
using namespace cocos2d;
class World;
enum class BloopType
{
	gloop,floop,sloop
};
class Bloop :public Entity
{
public:
	virtual ~Bloop();
	virtual void refreshPosition(Vec2 camera_);
	virtual void tick(World& world) = 0;
	virtual void move();
	bool die;
	BloopType bloopType;
	//Ï¸°ûÖÜÆÚ
	float cycle;
protected:
	Label* label;
	PerlinNoise noise;
	unsigned long long noiseX;
	virtual void init(Layer& layer, int ZOrder) = 0;
};
#endif