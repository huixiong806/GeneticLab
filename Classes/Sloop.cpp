#include "Sloop.h"
#include "HelloWorldScene.h"
using namespace cocos2d;
Sloop::~Sloop()
{
}
void Sloop::init(Layer& layer, int ZOrder)
{
	initSprite(layer, "images\\bloop.png", ZOrder);
	shape = Shape::circle;
	setColor(Color3B(0, 0, 255));
	setRandomPosition(Vec2(0, 0), parameter::worldSize);
	setSize(dna.getPhrase());
	label = Label::createWithTTF("", "fonts/Marker Felt.ttf", 0.5*size.width);
	layer.addChild(label, ZOrder + 1);
	speed = speedCalcPrmA+size.width*speedCalcPrmB;
	noise.seed = random<unsigned long long>(0ULL, ULLONG_MAX);
	noise.amplitude = 1;
	noise.frequency = 0.0025*(speed);
	noiseX = 0;
	cycle = maxCycle/6;
	eatCD = 0;
	die = false;
	bloopType = BloopType::sloop;
}
void Sloop::tick(World& world, std::shared_ptr<Bloop> this_)
{
	if (die)return;
	//移动
	move(world, this_);
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
	//获取周围所有的chunk
	std::vector<Chunk*>nearByChunks = getNineNearByChunks(world);
	//吃食物
	for (auto &chunk : nearByChunks)
	{
		for (auto food = chunk->food.begin(); food != chunk->food.end();)
		{
			if (this->hit(**food))
			{
				cycle += Food::energy;
				world.food.erase(*food);
				food = chunk->food.erase(food);
			}
			else ++food;
		}
	}
	//吃bloop
	if (!eatCD)
	{
		for (auto &chunk : nearByChunks)
		{
			for (auto &bloop : chunk->bloop)
			{
				if ((bloop->bloopType == BloopType::floop || bloop->bloopType == BloopType::gloop) && hit(*bloop) && size.width>bloop->getSize().width)
				{
					bloop->die = true;
					cycle += bloop->cycle*parameter::energyTransferEfficiency;
					eatCD = bloop->bloopType == BloopType::floop ? 500 : 250;
					break;
				}
			}
			if (eatCD)break;
		}
	}
	//分裂
	if (cycle >= maxCycle)
	{
		die = true;
		for (int i = 0; i < 2; ++i)
		{
			std::shared_ptr<Sloop> newCell = std::make_shared<Sloop>(world, 1, *this);
			world.bloop.insert(newCell);
			newCell->setPosition(getPosition());
		}
	}
}
Sloop::Sloop(Layer& layer, int ZOrder)
{
	dna = SloopDNA();
	init(layer, ZOrder);
	cycle = random<float>(maxCycle * 1 / 6, maxCycle*1/4);
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