#include "Floop.h"
#include "HelloWorldScene.h"
using namespace cocos2d;
Floop::~Floop()
{
}
void Floop::init(Layer& layer, int ZOrder)
{
	initSprite(layer, "images\\bloop.png", ZOrder);
	shape = Shape::circle;
	setColor(Color3B(255, 0, 0));
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
	bloopType = BloopType::floop;
}
void Floop::tick(World& world, std::shared_ptr<Bloop> this_)
{
	if (die)return;
	//移动
	move(world,this_);
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
				if (bloop->bloopType == BloopType::gloop && hit(*bloop) && size.width>bloop->getSize().width)
				{
					bloop->die = true;
					cycle += bloop->cycle * parameter::energyTransferEfficiency;
					eatCD = 500;
					break;
				}
			}
			if (eatCD)break;
		}
	}
	/*
	for (auto iter = world.food.begin(); iter != world.food.end();)
	{
		if (this->hit(**iter))
		{
			cycle += Food::energy;
			(*iter)->removeFromChunk((*iter)->getChunk(world), (*iter));
			iter = world.food.erase(iter);
		}
		else ++iter;
	}
	//吃gloop
	if (!eatCD)
	{ 
		for (auto iter = world.bloop.begin(); iter != world.bloop.end(); ++iter)
		{
			if ((*iter)->bloopType == BloopType::gloop && hit(**iter)&&size.width>(*iter)->getSize().width)
			{
				(*iter)->die = true;
				cycle += (*iter)->cycle * parameter::energyTransferEfficiency;
				eatCD = 500;
				break;
			}
		}
	}
	*/
	//分裂
	if (cycle >= maxCycle)
	{
		die = true;
		for (int i = 0; i < 2; ++i)
		{
			std::shared_ptr<Floop> newCell = std::make_shared<Floop>(world, 1, *this);
			world.bloop.insert(newCell);
			newCell->setPosition(getPosition());
		}
	}
}
Floop::Floop(Layer& layer, int ZOrder)
{
	dna = FloopDNA();
	init(layer, ZOrder);
	cycle = random<float>(maxCycle*1/6, maxCycle*1/4);
}
Floop::Floop(Layer& layer, int ZOrder, Floop& parent)
{
	dna = parent.dna.crossover(parent.dna);
	dna.mutate(0.02);
	init(layer, ZOrder);
}
Floop::Floop(Layer& layer, int ZOrder, Floop& parentA, Floop& parentB)
{
	dna = parentA.dna.crossover(parentB.dna);
	dna.mutate(0.02);
	init(layer, ZOrder);
}
void Floop::refreshPosition(Vec2 camera_)
{
	sprite->setPosition(position - camera_);
	label->setPosition(position - camera_);
	std::string str;
	std::ostringstream os;
	os << (int)cycle;
	str.append(os.str());
	label->setString(str);
}