#include"Entity.h"
using namespace cocos2d;
void Entity::setRandomColor()
{
	int R = random() % 256;
	int G = random() % 256;
	int B = random() % 256;
	setColor(Color3B(R, G, B));
}
bool Entity::hit(Entity& another)
{
	float r = getSize().width / 2 + another.getSize().width / 2;
	if (r < getPosition().distance(another.getPosition()))return false;
	return true;
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

