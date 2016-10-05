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
	//��ʼ��ʳ��
	for (int i = 0; i < food.size(); i++)
	{
		food[i] = new Food(*this, 1);
	}
	//��ʼ��bloops
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
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	const Vec2 deltaPos[4] = { Vec2(0,1),Vec2(0,-1), Vec2(-1,0), Vec2(1,0) };
	//�ƶ���Ұ
	for (int i = 0; i <= 3; i++)
		if (keyGroupCamera[i])camera += deltaPos[i]*(int)(glview->getDesignResolutionSize().width/204.8);
	//���������bloop
	for (auto iter = bloop.begin(); iter != bloop.end();)
	{
		if ((*iter)->die)
		{
			delete *iter;
			iter = bloop.erase(iter);
		}
		else ++iter;
	}
	//ÿ��bloopִ��tick����
	for (auto &i : bloop)
		i->tick(*this);
	//����ʳ��
	for (auto &i : food)
		i->refreshPosition(camera);
	//����ͳ�����,20s����һ��
	if (statCD == 0)
	{
		statCD = 999;
		int GloopCount=0, FloopCount=0, SloopCount=0;
		for (auto &i:bloop)
		{
			if (i->die)continue;
			switch (i->bloopType)
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
		dataOutPut << tick << "," << food.size() <<",";
		dataOutPut << GloopCount << "," << FloopCount << "," << SloopCount << endl;
	}
	else statCD--;
	tick++;
}
/************************************************
������:�����ͷ��¼�
����:�����ͷ�ʱ������ִ��һϵ�ж���
��ע:��
************************************************/
void World::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW)  //�����ϼ�
		keyGroupCamera[0] = false;
	if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)  //�����¼�
		keyGroupCamera[1] = false;
	if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)  //�������
		keyGroupCamera[2] = false;
	if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)  //�����Ҽ�
		keyGroupCamera[3] = false;
}
/************************************************
������:���̰����¼�
����:���̰���ʱ������ִ��һϵ�ж���
��ע:��
************************************************/
void World::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	Size curResolutionSize = glview->getDesignResolutionSize();
	if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW)  //�����ϼ�
		keyGroupCamera[0] = true;
	else if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)  //�����¼�
		keyGroupCamera[1] = true;
	else if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)  //�������
		keyGroupCamera[2] = true;
	else if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)  //�����Ҽ�
		keyGroupCamera[3] = true;
	else if (keyCode == EventKeyboard::KeyCode::KEY_F)  //F��������screensize
	{
		if (curResolutionSize.height < 8192)
			glview->setDesignResolutionSize(curResolutionSize.width+512, curResolutionSize.height+384, ResolutionPolicy::NO_BORDER);
		curResolutionSize = glview->getDesignResolutionSize();
		backGround->setScale(curResolutionSize.width/backGround->getContentSize().width);
		backGround->setPosition(curResolutionSize / 2);
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_D)  //D������Сscreensize
	{
		if (curResolutionSize.height > 512)
			glview->setDesignResolutionSize(curResolutionSize.width-512, curResolutionSize.height-384, ResolutionPolicy::NO_BORDER);
		curResolutionSize = glview->getDesignResolutionSize();
		backGround->setScale(curResolutionSize.width / backGround->getContentSize().width);
		backGround->setPosition(curResolutionSize / 2);
	}
}