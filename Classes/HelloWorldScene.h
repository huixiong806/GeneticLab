#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__
#include "cocos2d.h"
#include "Entity.h"
#include "Food.h"
#include "Chunk.h"
#include <vector>
#include <fstream>
#include <unordered_set>
class Bloop;
class Entity;
class World : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    // implement the "static create()" method manually
    CREATE_FUNC(World);
	cocos2d::Vec2 camera;
	std::unordered_set<std::shared_ptr<Bloop>> bloop;
	std::unordered_set<std::shared_ptr<Food>> food;
	std::vector<std::vector<Chunk>> chunk;
	int statCD;
private:
	void outputData();
	void setChunkCount(cocos2d::Size chunkCount);
	//°´¼ü¼àÌýÆ÷
	cocos2d::EventListenerKeyboard* keyListener;
	cocos2d::Sprite* backGround;
	cocos2d::Label* information;
	bool showInformation;
	std::string info;
	std::ofstream dataOutPut;
	unsigned __int64 tick;
	void eventProcessor(float dt);
	bool keyGroupCamera[4];
	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
}; 

#endif // __HELLOWORLD_SCENE_H__
