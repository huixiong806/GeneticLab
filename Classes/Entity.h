#ifndef ENTITY_H
#define ENTITY_H
#include "cocos2d.h"
#include "publicVars.h"
using namespace cocos2d;
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
	void initSprite(Layer &layer, std::string picturePath, int ZOrder);
	void setRandomColor();
	void setColor(Color3B color);
	void setPosition(Vec2 position_);
	void setRandomPosition(Vec2 startPoint,Size mapSize);
	void setSize(Size size_);
	void setShape(Shape shape_);
	virtual void refreshPosition(Vec2 camera_);
	virtual bool hit(Entity& another);
	const Shape& getShape();
	const Size& getSize();
	const Vec2& getPosition();
protected:
	Vec2 position;
	//对于圆，直径。对于正方体，边长。
	Size size;
	float speed;
	Sprite* sprite;
	Shape shape;
};
#endif