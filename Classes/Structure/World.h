#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__
#include "cocos2d.h"
#include <Bloop.h>
#include <Food.h>
#include <Chunk.h>
#include <Recorder.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <unordered_set>
class Gloop;
class Floop;
class Sloop;
class World : public cocos2d::Layer
{
	friend Bloop;
	friend Gloop;
	friend Floop;
	friend Sloop;
	friend Entity;
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    // implement the "static create()" method manually
    CREATE_FUNC(World);
	cocos2d::Vec2 camera;
	void addBloop(std::shared_ptr<Bloop> bloop);
	unsigned long long bloopCount[3];
private:
	void outputData();
	void setChunkCount(cocos2d::Size chunkCount);
	//°´¼ü¼àÌýÆ÷
	cocos2d::EventListenerKeyboard* keyListener;
	//µ¥µã´¥Ãþ¼àÌýÆ÷
	cocos2d::EventListenerTouchOneByOne *touchListener;
	cocos2d::Sprite* backGround;
	cocos2d::Label* infoLabel;
	bool infoVisible;
	std::string infoString;
	std::ofstream dataOutPut;
	Recorder recorder;
	unsigned long long tick;
	bool keyGroupCamera[4];
	void eventProcessor(float dt);
	bloopPool bloop;
	foodPool food;
	std::vector<std::vector<Chunk>> chunk;
	std::shared_ptr<Bloop> trackedBloop;
	bloopPool::const_iterator eraseBloop(bloopPool::iterator target);
	void onTouchEnded(cocos2d::Touch * touch, cocos2d::Event * event);
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
}; 

#endif // __HELLOWORLD_SCENE_H__
