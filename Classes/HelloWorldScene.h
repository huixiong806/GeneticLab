#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__
#include "cocos2d.h"
#include "Entity.h"
#include "Food.h"
#include <vector>
#include <queue>
#include <fstream>
class Bloop;
class World : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    // implement the "static create()" method manually
    CREATE_FUNC(World);
	Vec2 camera;
	std::vector<Bloop*> bloop;
	std::vector<Food*> food;
	int statCD;
private:
	//°´¼ü¼àÌýÆ÷
	EventListenerKeyboard* keyListener;
	Sprite* backGround;
	std::ofstream dataOutPut;
	unsigned __int64 tick;
	void eventProcessor(float dt);
	bool keyGroupCamera[4];
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
};

#endif // __HELLOWORLD_SCENE_H__
