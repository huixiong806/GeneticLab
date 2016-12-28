#include "HelloWorldScene.h"
#include "Gloop.h"
#include "Bloop.h"
#include "Floop.h"
#include "Sloop.h"
#include "publicVars.h"
USING_NS_CC;
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
	//设置地图大小
	this->setChunkCount(Size(88,88));
	//初始化食物
	for (int i = 0; i < 700*16; i++)
	{
		std::shared_ptr<Food> newFood = std::make_shared<Food>(*this, 1);
		food.insert(newFood);
		newFood->addToChunk(newFood->getChunk(*this), newFood);
	}
	bloopCount[(int)BloopType::gloop] = 0;
	bloopCount[(int)BloopType::floop] = 0;
	bloopCount[(int)BloopType::sloop] = 0;
	//初始化bloops
	for (int i = 0; i < 90 * 16; i++)
	{
		if (i < 2 * 16)
			addBloop(std::make_shared<Sloop>(*this, 1));
		else if (i<16 * 16)
			addBloop(std::make_shared<Floop>(*this, 1));
		else 
			addBloop(std::make_shared<Gloop>(*this, 1));
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
	backGround->setColor(Color3B::WHITE);
	backGround->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(backGround, 0);
	info = "KeyControl\nD:Zoom In\nF:Zoom Out\nX:Hide/Show information\nVersion1.5\ncopyright 2016 orangebird.\nPublished with MIT licence.";
	information = Label::createWithTTF(info,"fonts/Marker Felt.ttf", 60);
	information->setColor(Color3B(104,209,255));
	information->setPosition(origin + Vec2(visibleSize.width / 5.0*4.0, visibleSize.height / 4.0));
	showInformation = true;
	this->addChild(information,2);
	recorder = Recorder();
	recorder.setFrequency(500);
	tick = 0;
	schedule(schedule_selector(World::eventProcessor), 0.02f);
    return true;
}
//数据统计输出
void World::outputData()
{
	if (bloopCount[(int)BloopType::floop] < 160)
		for (int i = 0; i < 100; i++)
			addBloop(std::make_shared<Floop>(*this, 1));
	if (bloopCount[(int)BloopType::sloop] < 10)
		for (int i = 0; i < 10; i++)
			addBloop(std::make_shared<Sloop>(*this, 1));
	recorder.tick(std::vector<unsigned long long>
	{
		food.size(),
		bloopCount[(int)BloopType::gloop],
		bloopCount[(int)BloopType::floop],
		bloopCount[(int)BloopType::sloop],
	});
	std::stringstream str;
	str << "Tick:" << tick << "\nFood:"<< food.size() << "\nGloop:" << bloopCount[(int)BloopType::gloop] << " Floop:" << bloopCount[(int)BloopType::floop] << " Sloop:" << bloopCount[(int)BloopType::sloop] << '\n' << info;
	information->setString(str.str());
}
void World::setChunkCount(Size chunkCount)
{
	parameter::chunkCount = chunkCount;
	parameter::worldSize.width = parameter::chunkSize.width * chunkCount.width;
	parameter::worldSize.height = parameter::chunkSize.height * chunkCount.height;
	chunk.resize(chunkCount.width+1);
	for (auto &i : chunk)
		i.resize(chunkCount.height+1);
}
void World::addBloop(std::shared_ptr<Bloop> bloop)
{
	this->bloop.insert(bloop);
	bloop->addToChunk(bloop->getChunk(*this));
	++bloopCount[(int)bloop->bloopType];
}
std::unordered_set<std::shared_ptr<Bloop>>::const_iterator 
	World::eraseBloop(std::unordered_set<std::shared_ptr<Bloop>>::const_iterator target)
{
	(*target)->removeFromChunk((*target)->getChunk(*this));
	--bloopCount[(int)(*target)->bloopType];
	return bloop.erase(target);
}
void World::eventProcessor(float dt)
{
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	const Vec2 deltaPos[4] = { Vec2(0,1),Vec2(0,-1), Vec2(-1,0), Vec2(1,0) };
	//增加tick
	++tick;
	//移动视野
	for (int i = 0; i <= 3; i++)
		if (keyGroupCamera[i])camera += deltaPos[i]*(int)(glview->getDesignResolutionSize().width/204.8*1.2);
	//清除死亡的bloop
	for (auto iter = bloop.begin(); iter != bloop.end();)
	{
		if ((*iter)->die)
			iter = eraseBloop(iter);
		else ++iter;
	}
	//每个bloop执行tick动作
	for (auto &item : bloop)
		item->tick(*this);
	//绘制食物
	for (auto &i : food)
		i->refreshPosition(camera);
	//数据统计输出,500ticks进行一次
	outputData();
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
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	Size curResolutionSize = glview->getDesignResolutionSize();
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
		if (curResolutionSize.height < 8192)
			glview->setDesignResolutionSize(curResolutionSize.width+512, curResolutionSize.height+384, ResolutionPolicy::NO_BORDER);
		curResolutionSize = glview->getDesignResolutionSize();
		backGround->setScale(curResolutionSize.width/backGround->getContentSize().width);
		information->setScale(curResolutionSize.width / backGround->getContentSize().width);
		information->setPosition(Vec2(curResolutionSize.width / 5.0*4.0, curResolutionSize.height / 4.0));
		backGround->setPosition(curResolutionSize / 2);
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_D)  //D键，减小screensize
	{
		if (curResolutionSize.height > 512)
			glview->setDesignResolutionSize(curResolutionSize.width-512, curResolutionSize.height-384, ResolutionPolicy::NO_BORDER);
		curResolutionSize = glview->getDesignResolutionSize();
		backGround->setScale(curResolutionSize.width / backGround->getContentSize().width);
		information->setScale(curResolutionSize.width / backGround->getContentSize().width);
		information->setPosition(Vec2(curResolutionSize.width / 5.0*4.0, curResolutionSize.height / 4.0));
		backGround->setPosition(curResolutionSize / 2);
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_X)
	{
		if (showInformation)
			showInformation = 0;
		else  showInformation = 1;
		information->setOpacity(showInformation?255:0);
	}
}