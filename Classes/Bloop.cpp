#include "Bloop.h"
#include "HelloWorldScene.h"
#include "publicVars.h"
using namespace cocos2d;
Bloop::~Bloop()
{
	label->removeFromParent();
}
void Bloop::move()
{
	float rad = noise.perlin_noise(noiseX);
	rad -= ((int)(rad / (2.0 * PI))) * 2.0 * PI;
	Vec2 deltaPosition= Vec2(cosf(rad),sinf(rad))*speed;
	setPosition(getPosition() + deltaPosition);
	if (getPosition().x < -100)setPosition(getPosition()+Vec2(worldSizeX+150,0));
	if (getPosition().x > worldSizeX+100)setPosition(getPosition() + Vec2(-1 * worldSizeX-150, 0));
	if (getPosition().y < -100)setPosition(getPosition() + Vec2(0, worldSizeY + 150));
	if (getPosition().y > worldSizeY+100)setPosition(getPosition() + Vec2(0, -1 * worldSizeY - 150));
	noiseX++;
}
void Bloop::refreshPosition(Vec2 camera_)
{
	sprite->setPosition(position - camera_);
	label->setPosition(position - camera_);
}
