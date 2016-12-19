#include "Food.h"
#include "Chunk.h"
using namespace cocos2d;
Food::Food(Layer& layer, int ZOrder)
{
	shape = Shape::square;
	initSprite(layer, "images\\food.png", ZOrder);
	setRandomColor();
	setRandomPosition(Vec2(0, 0), parameter::worldSize);
	setSize(Size(10, 10));
}
bool Food::hit(Entity* another)
{
	if (getSize().width / 2 + another->getSize().width / 2 <= sqrt(getPosition().distance(another->getPosition())))return false;
	return true;
}
//把自己加到某个chunk中
void Food::addToChunk(Chunk& chunk, std::shared_ptr<Food> this_)
{
	chunk.addFood(this_);
}
//从某个chunk中清除
void Food::removeFromChunk(Chunk& chunk, std::shared_ptr<Food> this_)
{
	chunk.removeFood(this_);
}