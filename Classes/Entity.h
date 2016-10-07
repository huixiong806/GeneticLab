#ifndef ENTITY_H
#define ENTITY_H
#include "cocos2d.h"
#include "publicVars.h"
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
	void setPosition(cocos2d::Vec2 position_);
	void setRandomPosition(cocos2d::Vec2 startPoint, cocos2d::Size mapSize);
	void setSize(cocos2d::Size size_);
	void setShape(Shape shape_);
	virtual void refreshPosition(cocos2d::Vec2 camera_);
	virtual bool hit(Entity& another);
	const Shape& getShape();
	const cocos2d::Size& getSize();
	const cocos2d::Vec2& getPosition();
protected:
	cocos2d::Vec2 position;
	//对于圆，直径。对于正方体，边长。
	cocos2d::Size size;
	float speed;
	cocos2d::Sprite* sprite;
	Shape shape;
};
#endif