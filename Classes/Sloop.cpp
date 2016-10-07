#include "Sloop.h"
#include "HelloWorldScene.h"
Sloop::~Sloop()
{
}
void Sloop::init(Layer& layer, int ZOrder)
{
	initSprite(layer, "images\\bloop.png", ZOrder);
	shape = Shape::circle;
	setColor(Color3B(0, 0, 255));
	setRandomPosition(Vec2(0, 0), publicVars::superHugeSize);
	setSize(dna.getPhrase());
	label = Label::createWithTTF("", "fonts/Marker Felt.ttf", 0.6*size.width);
	layer.addChild(label, ZOrder + 1);
	speed = speedCalcPrmA+size.width*speedCalcPrmB;
	noise.seed = rand() % 2147483648;
	noise.amplitude = 1;
	noise.frequency = 0.0025*(speed);
	noiseX = 0;
	cycle = maxCycle/6;
	eatCD = 0;
	die = false;
	bloopType = BloopType::sloop;
}
void Sloop::tick(World& world)
{
	if (die)return;
	//移动
	move();
	//增加cycle，减少eatCD
	cycle += cycleIncPerTick;
	if(eatCD>0)eatCD--;
	//死亡
	if (cycle <= 0)
	{
		die = true;
		return;
	}
	//绘制
	refreshPosition(world.camera);
	//吃食物
	for (auto iter = world.food.begin(); iter != world.food.end();)
	{
		if (hit(**iter))
		{
			cycle += Food::energy;
			iter = world.food.erase(iter);
		}
		else ++iter;
	}
	//吃floop和gloop
	if (!eatCD)
	{ 
		for (auto iter = world.bloop.begin();iter != world.bloop.end();++iter)
		{
			if (((*iter)->bloopType == BloopType::floop || (*iter)->bloopType == BloopType::gloop) && hit(**iter) && size.width>(*iter)->getSize().width)
			{
				(*iter)->die = true;
				cycle += (*iter)->cycle*publicVars::energyTransferEfficiency;
				eatCD = (*iter)->bloopType == BloopType::floop ? 500 : 250;
				break;
			}
		}
	}
	//分裂
	if (cycle >= maxCycle)
	{
		die = true;
		for (int i = 0; i < 2; ++i)
		{
			world.bloop.emplace_back(std::make_shared<Sloop>(world, 1, *this));
			(*(world.bloop.end() - 1))->setPosition(getPosition());
		}
	}
}
Sloop::Sloop(Layer& layer, int ZOrder)
{
	dna = SloopDNA();
	init(layer, ZOrder);
	cycle = random<int>(maxCycle * 1 / 6, maxCycle*1/4);
}
Sloop::Sloop(Layer& layer, int ZOrder, Sloop& parent)
{
	dna = parent.dna.crossover(parent.dna);
	dna.mutate(0.02);
	init(layer, ZOrder);
}
Sloop::Sloop(Layer& layer, int ZOrder, Sloop& parentA, Sloop& parentB)
{
	dna = parentA.dna.crossover(parentB.dna);
	dna.mutate(0.02);
	init(layer, ZOrder);
}
void Sloop::refreshPosition(Vec2 camera_)
{
	sprite->setPosition(position - camera_);
	label->setPosition(position - camera_);
	std::string str;
	std::ostringstream os;
	os << (int)cycle;
	str.append(os.str());
	label->setString(str);
}