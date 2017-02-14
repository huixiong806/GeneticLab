#include <Entity.h>
#include <Chunk.h>
#include <World.h>
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
	if (sprite != nullptr)
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
	if(sprite!=nullptr)
		sprite->removeFromParent();
}
void Entity::initSprite(Layer& layer, std::string picturePath, int ZOrder)
{
	sprite = Sprite::create(picturePath);
	layer.addChild(sprite, ZOrder);
}
void Entity::setAbstract()
{
	sprite = nullptr;
}
//获取所在的chunk的引用
Chunk& Entity::getChunk(World& world)
{
	Vec2 position = this->getPosition();
	int indexX = position.x / const_parameter::chunkSize.width;
	int indexY = position.y / const_parameter::chunkSize.height;
	return world.chunk[indexX][indexY];
}

//获取临近的9个chunks
std::vector<Chunk*> Entity::getNineNearByChunks(World& world)
{
	if (position.x < 0)position.x += parameter::worldSize.width + const_parameter::chunkSize.width;
	if (position.y < 0)position.y += parameter::worldSize.height + const_parameter::chunkSize.height;
	int indexX = position.x / const_parameter::chunkSize.width;
	int indexY = position.y / const_parameter::chunkSize.height;
	std::vector<Chunk*> result;
	for (int i = -1; i <= 1; ++i)
	{
		for (int j = -1; j <= 1; ++j)
		{
			int targetX = indexX + i, targetY = indexY + j;
			if (targetX < 0)targetX += parameter::chunkCount.width + 1;
			if (targetX >= parameter::chunkCount.width + 1)targetX -= parameter::chunkCount.width + 1;
			if (targetY < 0)targetY += parameter::chunkCount.height + 1;
			if (targetY >= parameter::chunkCount.height + 1)targetY -= parameter::chunkCount.height + 1;
			result.push_back(&world.chunk[(int)targetX][(int)targetY]);
		}
	}
	return result;
}