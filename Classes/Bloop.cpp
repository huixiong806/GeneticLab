#include "Bloop.h"
#include "Chunk.h"
#include "HelloWorldScene.h"
#include "publicVars.h"
using namespace cocos2d;
Bloop::~Bloop()
{
}
void Bloop::OutOfRangeCheck()
{
	Size& chunkSize = parameter::chunkSize;
	if (getPosition().x < chunkSize.width*0.5)setPosition(getPosition() + Vec2(parameter::worldSize.width, 0));
	if (getPosition().x > parameter::worldSize.width + chunkSize.width*0.5)setPosition(getPosition() + Vec2(-parameter::worldSize.width, 0));
	if (getPosition().y < chunkSize.height*0.5)setPosition(getPosition() + Vec2(0, parameter::worldSize.height));
	if (getPosition().y > parameter::worldSize.height + chunkSize.height*0.5)setPosition(getPosition() + Vec2(0, -parameter::worldSize.height));
}
void Bloop::moveTo(cocos2d::Vec2 newPosition, World& world)
{
	Chunk& nowChunk = getChunk(world);
	setPosition(newPosition);
	OutOfRangeCheck();
	Chunk& nextChunk = getChunk(world);
	if (std::addressof(nowChunk) != std::addressof(nextChunk))
	{
		removeFromChunk(nowChunk);
		addToChunk(nextChunk);
	}
}
void Bloop::move(World& world)
{
	//float rad = noise.perlin_noise(noiseX);
	//rad -= (int(rad / (2.0 * PI))) * 2.0 * PI;
	//Vec2 deltaPosition= Vec2(cosf(rad),sinf(rad))*speed;
	//moveTo(getPosition() + deltaPosition,world);
	//noiseX++;
}
void Bloop::refreshPosition(Vec2 camera_)
{
	sprite->setPosition(position - camera_);
}
//把自己加到某个chunk中
void Bloop::addToChunk(Chunk& chunk)
{
	chunk.addBloop(shared_from_this());
}
//从某个chunk中清除
void Bloop::removeFromChunk(Chunk& chunk)
{
	chunk.removeBloop(shared_from_this());
}
//获取临近的9个chunks
std::vector<Chunk*> Bloop::getNineNearByChunks(World& world)
{
	Vec2 position = this->getPosition();
	if (position.x < 0)position.x += parameter::worldSize.width+ parameter::chunkSize.width;
	if (position.y < 0)position.y += parameter::worldSize.height + parameter::chunkSize.height;
	int indexX = position.x / parameter::chunkSize.width;
	int indexY = position.y / parameter::chunkSize.height;
	std::vector<Chunk*> result;
	for (int i = -1; i <= 1; ++i)
	{
		for (int j = -1; j <= 1; ++j)
		{
			int targetX = indexX + i, targetY = indexY + j;
			if (targetX < 0)targetX += parameter::chunkCount.width+1;
			if (targetX >= parameter::chunkCount.width+1)targetX -= parameter::chunkCount.width+1;
			if (targetY < 0)targetY += parameter::chunkCount.height+1;
			if (targetY >= parameter::chunkCount.height +1)targetY -= parameter::chunkCount.height +1;
			result.push_back(&world.chunk[(int)targetX][(int)targetY]);
		}
	}
	return result;
}