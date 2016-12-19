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
//���Լ��ӵ�ĳ��chunk��
void Food::addToChunk(Chunk& chunk, std::shared_ptr<Food> this_)
{
	chunk.addFood(this_);
}
//��ĳ��chunk�����
void Food::removeFromChunk(Chunk& chunk, std::shared_ptr<Food> this_)
{
	chunk.removeFood(this_);
}