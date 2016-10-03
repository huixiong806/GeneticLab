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
	noise.frequency = 0.005*(speed);
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
	int foodSize = world.food.size();
	for (int i = 0; i < foodSize;i++)
	{
		if (hit(*world.food[i]))
		{
			cycle += Food::energy;
			delete world.food[i];
			world.food.erase(world.food.begin()+i);
			break;
		}
	}
	//吃floop和gloop
	if (!eatCD)
	{ 
		int bloopSize = world.bloop.size();
		for (int i = 0; i < bloopSize; i++)
		{
			if ((world.bloop[i]->bloopType == BloopType::floop || world.bloop[i]->bloopType == BloopType::gloop)&& hit(*world.bloop[i])&&size.width>world.bloop[i]->getSize().width)
			{
				world.bloop[i]->die = true;
				cycle += world.bloop[i]->cycle*publicVars::energyTransferEfficiency;
				eatCD = world.bloop[i]->bloopType == BloopType::floop ? 500:250;
				break;
			}
		}
	}
	//分裂
	if (cycle >= maxCycle)
	{
		die = true;
		world.bloop.resize(world.bloop.size() + 2);
		world.bloop[world.bloop.size() - 2] = new Sloop(world, 1,*this);
		world.bloop[world.bloop.size() - 2]->setPosition(getPosition());
		world.bloop[world.bloop.size() - 1] = new Sloop(world, 1, *this);
		world.bloop[world.bloop.size() - 1]->setPosition(getPosition());
	}
}
Sloop::Sloop(Layer& layer, int ZOrder)
{
	dna = SloopDNA();
	init(layer, ZOrder);
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