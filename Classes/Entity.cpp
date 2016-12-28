#include "Entity.h"
#include "Chunk.h"
#include "HelloWorldScene.h"
using namespace cocos2d;
void Entity::setRandomColor()
{
	int R = random<int>(0, 255);
	int G = random<int>(0, 255);
	int B = random<int>(0, 255);
	setColor(Color3B(R, G, B));
}
bool Entity::hit(Entity& another)
{
	float r = getSize().width / 2 + another.getSize().width / 2;
	Vec2 posA = this->getPosition();
	Vec2 posB = another.getPosition();
	return (r*r >= (posA.x - posB.x)*(posA.x - posB.x) + (posA.y - posB.y)*(posA.y - posB.y));
}
void Entity::setColor(Color3B color)
{
	sprite->setColor(color);
}
void Entity::setPosition(Vec2 position_)
{
	position = position_;
}
void Entity::setRandomPosition(Vec2 startPoint,Size mapSize)
{
	Vec2 position_;
	position_.x = random<float>(startPoint.x, mapSize.width);
	position_.y = random<float>(startPoint.y, mapSize.height);
	setPosition(position_);
}
void Entity::refreshPosition(Vec2 camera_)
{
	sprite->setPosition(position - camera_);
}
void Entity::setSize(Size size_)
{
	size = size_;
	sprite->setScale(size.width/100.0,size.height/100.0);
}
void Entity::setShape(Shape shape_)
{
	shape = shape_;
}
const Vec2& Entity::getPosition()
{
	return position;
}
const Size& Entity::getSize()
{
	return size;
}
const Shape& Entity::getShape()
{
	return shape;
}
Entity::Entity()
{
}
Entity::~Entity()
{
	sprite->removeFromParent();
}
void Entity::initSprite(Layer& layer, std::string picturePath, int ZOrder)
{
	sprite = Sprite::create(picturePath);
	layer.addChild(sprite, ZOrder);
}
//获取所在的chunk的引用
Chunk& Entity::getChunk(World& world)
{
	Vec2 position = this->getPosition();
	int indexX = position.x / parameter::chunkSize.width;
	int indexY = position.y / parameter::chunkSize.height;
	return world.chunk[indexX][indexY];
}

