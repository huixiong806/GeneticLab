#ifndef ENTITY_H
#define ENTITY_H
#include "cocos2d.h"
#include "publicVars.h"
class World;
class Chunk;
enum class Shape : int
{
	circle,
	square
};
class Entity
{
public:
	Entity();
	virtual ~Entity();
	void initSprite(cocos2d::Layer &layer, std::string picturePath, int ZOrder);
	void setRandomColor();
	void setColor(cocos2d::Color3B color);
	void setRandomPosition(cocos2d::Vec2 startPoint, cocos2d::Size mapSize);
	void setSize(cocos2d::Size size_);
	void setShape(Shape shape_);
	void setPosition(cocos2d::Vec2 position_);
	//virtual void moveTo(cocos2d::Vec2 newPosition, World& world) = 0;
	virtual void refreshPosition(cocos2d::Vec2 camera_);
	virtual bool hit(Entity& another);
	//获取所在的chunk的引用
	virtual Chunk& getChunk(World& world);
	const Shape& getShape();
	const cocos2d::Size& getSize();
	const cocos2d::Vec2& getPosition();
protected:
	cocos2d::Vec2 position;
	//对于圆，直径。对于正方体，边长。
	cocos2d::Size size;
	cocos2d::Sprite* sprite;
	Shape shape;
};
#endif