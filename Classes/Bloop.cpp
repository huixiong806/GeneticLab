#include "Bloop.h"
#include "Chunk.h"
#include "HelloWorldScene.h"
#include "publicVars.h"
using namespace cocos2d;
Bloop::~Bloop()
{
	label->removeFromParent();
}
void Bloop::OutOfRangeCheck()
{
	Size& chunkSize = parameter::chunkSize;
	if (getPosition().x < -chunkSize.width)setPosition(getPosition() + Vec2(parameter::worldSize.width+chunkSize.width/2, 0));
	if (getPosition().x > parameter::worldSize.width + chunkSize.width)setPosition(getPosition() + Vec2(-parameter::worldSize.width-chunkSize.width/2, 0));
	if (getPosition().y < -chunkSize.height)setPosition(getPosition() + Vec2(0, parameter::worldSize.height + chunkSize.height / 2));
	if (getPosition().y > parameter::worldSize.height + chunkSize.height)setPosition(getPosition() + Vec2(0, -parameter::worldSize.height - chunkSize.height / 2));
}
void Bloop::move(World& world,std::shared_ptr<Bloop> this_)
{
	Chunk& nowChunk = getChunk(world);
	float rad = noise.perlin_noise(noiseX);
	rad -= (int(rad / (2.0 * PI))) * 2.0 * PI;
	Vec2 deltaPosition= Vec2(cosf(rad),sinf(rad))*speed;
	setPosition(getPosition() + deltaPosition);
	noiseX++;
	OutOfRangeCheck();
	Chunk& nextChunk = getChunk(world);
	if (std::addressof(nowChunk) != std::addressof(nextChunk))
	{
		removeFromChunk(nowChunk, this_);
		addToChunk(nextChunk, this_);
	}
}
void Bloop::refreshPosition(Vec2 camera_)
{
	sprite->setPosition(position - camera_);
	label->setPosition(position - camera_);
}
//把自己加到某个chunk中
void Bloop::addToChunk(Chunk& chunk, std::shared_ptr<Bloop> this_)
{
	chunk.addBloop(this_);
}
//从某个chunk中清除
void Bloop::removeFromChunk(Chunk& chunk, std::shared_ptr<Bloop> this_)
{
	chunk.removeBloop(this_);
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