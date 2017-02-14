#include <World.h>
#include <Gloop.h>
#include <Floop.h>
#include <Sloop.h>
#include <Parameter.h>
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
	camera = Vec2(2048,2048);
	for (int i = 0; i <= 3; i++)
		keyGroupCamera[i] = false;
	//初始化一堆其他的东西
	keyListener = EventListenerKeyboard::create();
	keyListener->setEnabled(true);
	keyListener->onKeyReleased = CC_CALLBACK_2(World::onKeyReleased, this);
	keyListener->onKeyPressed = CC_CALLBACK_2(World::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);
	touchListener = EventListenerTouchOneByOne::create();
	touchListener->setEnabled(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(World::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(World::onTouchEnded, this);
	touchListener->setSwallowTouches(true);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
	backGround = Sprite::create("images\\White.png");
	backGround->setColor(Color3B::WHITE);
	backGround->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(backGround, 0);
	infoString = "KeyControl\nD:Zoom In\nF:Zoom Out\nX:Hide/Show information\nVersion1.5.4\ncopyright 2016-2017 orangebird.";
	infoLabel = Label::createWithTTF(infoString,"fonts/Marker Felt.ttf", 60);
	infoLabel->setColor(Color3B(104,209,255));
	infoLabel->setPosition(origin + Vec2(visibleSize.width / 5.0*4.0, visibleSize.height / 4.0));
	infoVisible = true;
	this->addChild(infoLabel,2);
	recorder = Recorder();
	recorder.setFrequency(500);
	tick = 0;
	trackedBloop = nullptr;
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
	str << "Tick:" << tick << "\nLocation:" << camera.x << "," << camera.y << std::endl << (trackedBloop != nullptr ? "Flowing mode" : "Free mode")
		<<"\nFood:"<< food.size() 
		<< "\nGloop:" << bloopCount[(int)BloopType::gloop] << " Floop:" 
		<< bloopCount[(int)BloopType::floop] << " Sloop:" << bloopCount[(int)BloopType::sloop] 
		<< '\n' << infoString;
	infoLabel->setString(str.str());
}
//设置地图大小(有多少个chunks)
void World::setChunkCount(Size chunkCount)
{
	parameter::chunkCount = chunkCount;
	parameter::worldSize.width = const_parameter::chunkSize.width * chunkCount.width;
	parameter::worldSize.height = const_parameter::chunkSize.height * chunkCount.height;
	chunk.resize(chunkCount.width+1);
	for (auto &i : chunk)
		i.resize(chunkCount.height+1);
}
//添加一个bloop
void World::addBloop(std::shared_ptr<Bloop> bloop)
{
	this->bloop.insert(bloop);
	bloop->addToChunk(bloop->getChunk(*this));
	++bloopCount[(int)bloop->bloopType];
}
//移除一个bloop
bloopPool::const_iterator World::eraseBloop(bloopPool::iterator target)
{
	(*target)->removeFromChunk((*target)->getChunk(*this));
	--bloopCount[(int)(*target)->bloopType];
	return bloop.erase(target);
}
//事件处理器,1tick触发一次
void World::eventProcessor(float dt)
{
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	const Vec2 deltaPos[4] = { Vec2(0,1),Vec2(0,-1), Vec2(-1,0), Vec2(1,0) };
	//增加tick
	++tick;
	//移动视野
	if (trackedBloop!=nullptr&&trackedBloop->die)trackedBloop = nullptr;
	if (trackedBloop == nullptr)
	{
		for (int i = 0; i <= 3; i++)
			if (keyGroupCamera[i])camera += deltaPos[i] * (int)(glview->getDesignResolutionSize().width / 204.8*1.2);
	}
	else camera = trackedBloop->getPosition() - visibleSize / 2;
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
		infoLabel->setScale(curResolutionSize.width / backGround->getContentSize().width);
		infoLabel->setPosition(Vec2(curResolutionSize.width / 5.0*4.0, curResolutionSize.height / 4.0));
		backGround->setPosition(curResolutionSize / 2);
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_D)  //D键，减小screensize
	{
		if (curResolutionSize.height > 512)
			glview->setDesignResolutionSize(curResolutionSize.width-512, curResolutionSize.height-384, ResolutionPolicy::NO_BORDER);
		curResolutionSize = glview->getDesignResolutionSize();
		backGround->setScale(curResolutionSize.width / backGround->getContentSize().width);
		infoLabel->setScale(curResolutionSize.width / backGround->getContentSize().width);
		infoLabel->setPosition(Vec2(curResolutionSize.width / 5.0*4.0, curResolutionSize.height / 4.0));
		backGround->setPosition(curResolutionSize / 2);
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_X)
	{
		if (infoVisible)
			infoVisible = 0;
		else  infoVisible = 1;
		infoLabel->setOpacity(infoVisible ?255:0);
	}
}

bool World::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
	Entity mouse = Entity();
	mouse.setAbstract();
	mouse.setSize(Size(15, 15));
	mouse.setPosition(touch->getLocation()+ camera);
	std::vector<Chunk*> nearByChunks = mouse.getNineNearByChunks(*this);
	for (auto& chunk : nearByChunks)
	{
		for (auto& bloop : chunk->bloopSet())
		{
			if (bloop->hit(mouse))
			{
				trackedBloop = bloop;
				return true;
			}
		}
	}
	trackedBloop = nullptr;
	return true;
}
void World::onTouchEnded(cocos2d::Touch * touch, cocos2d::Event * event)
{
}