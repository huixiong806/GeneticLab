#include "HelloWorldScene.h"
#include "Gloop.h"
#include "Bloop.h"
#include "Floop.h"
#include "Sloop.h"
#include "publicVars.h"
#include<windows.h>
#include<sstream>
USING_NS_CC;
using namespace std;
Scene* World::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = World::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool World::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	srand((unsigned)time(NULL));
    //auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    //
    //// position the label on the center of the screen
    //label->setPosition(Vec2(origin.x + visibleSize.width/2,
    //                        origin.y + visibleSize.height - label->getContentSize().height));

    //// add the label as a child to this layer
    //this->addChild(label, 1);
	bloop.resize(60);
	food.resize(700);
	//初始化食物
	for (int i = 0; i < food.size(); i++)
	{
		food[i] = new Food(*this, 1);
	}
	//初始化bloops
	for (int i = 0; i < bloop.size(); i++)
	{
		if(i<3)
			bloop[i] = new Sloop(*this, 1);
		else if (i<17)
			bloop[i] = new Floop(*this, 1);
		else 
			bloop[i] = new Gloop(*this, 1);
	}
	camera = Vec2(0, 0);
	for (int i = 0; i <= 3; i++)
		keyGroupCamera[i] = false;
	keyListener = EventListenerKeyboard::create();
	keyListener->setEnabled(true);
	keyListener->onKeyReleased = CC_CALLBACK_2(World::onKeyReleased, this);
	keyListener->onKeyPressed = CC_CALLBACK_2(World::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);
	backGround = Sprite::create("images\\White.png");
	backGround->setColor(Color3B(255,255,255));
	backGround->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(backGround, 0);
	statCD = 0;
	tick = 0;
	SYSTEMTIME sysTime;
	ZeroMemory(&sysTime, sizeof(sysTime));
	GetLocalTime(&sysTime);
	stringstream filePath;
	filePath << "data\\experiment" << (int)sysTime.wYear << "." << (int)sysTime.wMonth << "." << (int)sysTime.wDay<<".";
	filePath << (int)sysTime.wHour << "_" << (int)sysTime.wMinute << "_" << (int)sysTime.wSecond << ".csv";
	dataOutPut.open(filePath.str().c_str(), ios::out);
	dataOutPut << "tick,food,Gloop,Floop,Sloop" << endl;
	schedule(schedule_selector(World::eventProcessor), 0.02f);
    return true;
}
void World::eventProcessor(float dt)
{
	const Vec2 deltaPos[4] = { Vec2(0,1),Vec2(0,-1), Vec2(-1,0), Vec2(1,0) };
	//移动视野
	for (int i = 0; i <= 3; i++)
		if (keyGroupCamera[i])camera += deltaPos[i]*(int)(publicVars::glview->getDesignResolutionSize().width/204.8);
	//清除死亡的bloop
	int bloopSize = bloop.size();
	for (int i = 0; i < bloopSize; i++)
	{
		if (bloop[i]->die)
		{
			delete bloop[i];
			bloop.erase(bloop.begin() + i);
			if (i)i--;
			bloopSize--;
		}
	}
	//每个bloop执行tick动作
	bloopSize = bloop.size();
	for (int i = 0; i < bloopSize; i++)
	{
		bloop[i]->tick(*this);
	}
	////生成食物
	//float randomNumber = random<float>(0, 1);
	//if (randomNumber < 0.00025)
	//{
	//	food.resize(food.size() + 1);
	//	food[food.size() - 1] = new Food(*this, 1);
	//	food[food.size() - 1]->setPosition(getPosition());
	//}
	//绘制食物
	int foodSize = food.size();
	for (int i = 0; i < foodSize; i++)
	{
		food[i]->refreshPosition(camera);
	}
	//数据统计输出,20s进行一次
	if (statCD == 0)
	{
		statCD = 999;
		int GloopCount=0, FloopCount=0, SloopCount=0;
		bloopSize = bloop.size();
		for (int i = 0; i < bloopSize; i++)
		{
			if (bloop[i]->die)continue;
			switch (bloop[i]->bloopType)
			{
			case BloopType::gloop:
				GloopCount++;
				break;
			case BloopType::floop:
				FloopCount++;
				break;
			case BloopType::sloop:
				SloopCount++;
				break;
			}
		}
		dataOutPut << tick << "," << foodSize <<",";
		dataOutPut << GloopCount << "," << FloopCount << "," << SloopCount << endl;
	}
	else statCD--;
	tick++;
}
/************************************************
函数名:键盘释放事件
功能:键盘释放时触发，执行一系列动作
备注:无
************************************************/
void World::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW)  //方向上键
		keyGroupCamera[0] = false;
	if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)  //方向下键
		keyGroupCamera[1] = false;
	if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)  //方向左键
		keyGroupCamera[2] = false;
	if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)  //方向右键
		keyGroupCamera[3] = false;
}
/************************************************
函数名:键盘按下事件
功能:键盘按下时触发，执行一系列动作
备注:无
************************************************/
void World::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW)  //方向上键
		keyGroupCamera[0] = true;
	else if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)  //方向下键
		keyGroupCamera[1] = true;
	else if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)  //方向左键
		keyGroupCamera[2] = true;
	else if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)  //方向右键
		keyGroupCamera[3] = true;
	else if (keyCode == EventKeyboard::KeyCode::KEY_F)  //F键，增大screensize
	{
		Size curSize = publicVars::glview->getDesignResolutionSize();
		if (curSize.height < 8192)
			publicVars::glview->setDesignResolutionSize(curSize.width+512, curSize.height+384, ResolutionPolicy::NO_BORDER);
		curSize = publicVars::glview->getDesignResolutionSize();
		backGround->setScale(curSize.width/backGround->getContentSize().width);
		backGround->setPosition(curSize / 2);
	
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_D)  //D键，减小screensize
	{
		Size curSize = publicVars::glview->getDesignResolutionSize();
		if (curSize.height > 512)
			publicVars::glview->setDesignResolutionSize(curSize.width-512, curSize.height-384, ResolutionPolicy::NO_BORDER);
		curSize = publicVars::glview->getDesignResolutionSize();
		backGround->setScale(curSize.width / backGround->getContentSize().width);
		backGround->setPosition(curSize / 2);
	}
}