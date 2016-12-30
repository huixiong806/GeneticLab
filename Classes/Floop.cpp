#include "Floop.h"
#include "HelloWorldScene.h"
using namespace cocos2d;
Floop::~Floop()
{
}
void Floop::initBrain()
{
	brain = ann::NeuralNetwork(true, 3, 4, std::vector<unsigned int>{4,3, 2});
	std::vector<std::vector<ann::Neuron>>& neuron = brain.getNeuron();
	int geneIndex = 0;
	for (auto &i : neuron)
	{
		for (auto &j : i)
		{
			//+1 is because bias
			int needSize = j.getInputSize() + 1;
			std::vector<double>input;
			while (needSize--)
				input.push_back(dna.getBrainGene(geneIndex++));
			j.setWeight(input);
			j.setActivationFun(function::sigmoid);
		}
	}
	for (auto &i : neuron[0])
		i.setActivationFun(function::halfStep);
}
void Floop::init(Layer& layer, int ZOrder)
{
	initSprite(layer, "images\\bloop.png", ZOrder);
	shape = Shape::circle;
	setColor(Color3B(255, 0, 0));
	setRandomPosition(Vec2(0, 0), parameter::worldSize);
	setSize(dna.getSize());
	maxSpeed = speedCalcPrmA+size.width*speedCalcPrmB;
	//noise.seed = random<unsigned long long>(0ULL, ULLONG_MAX);
	//noise.amplitude = 1;
	//noise.frequency = 0.0025*(speed);
	//noiseX = 0;
	eatCD = 0;
	die = false;
	cycle = maxCycle*parameter::floopStartCycleCoefficient;	
	bloopType = BloopType::floop;
	initBrain();
}
std::tuple<double,double,double,double> Floop::getNearByInformations(World& world)
{
	std::vector<Chunk*> nearByChunks = getNineNearByChunks(world);
	std::shared_ptr<Bloop> nearestSloop = nullptr;
	std::shared_ptr<Bloop> nearestGloop = nullptr;
	std::shared_ptr<Bloop> nearestFloop = nullptr;
	std::shared_ptr<Food> nearestFood = nullptr;
	double squareDistanceSloop = INFINITE, squareDistanceGloop = INFINITE;
	double squareDistanceFloop = INFINITE, squareDistanceFood = INFINITE;
	for (auto &chunk : nearByChunks)
	{
		for (auto &bloop : chunk->bloopSet())
		{
			Vec2 delPos = Vec2(bloop->getPosition().x - this->getPosition().x, bloop->getPosition().y - this->getPosition().y);
			if (bloop->bloopType == BloopType::gloop)
			{
				if (squareDistanceGloop > delPos.x*delPos.x + delPos.y*delPos.y)
				{
					squareDistanceGloop = delPos.x*delPos.x + delPos.y*delPos.y;
					nearestGloop = bloop;
				}
			}else if (bloop->bloopType == BloopType::sloop)
			{
				if (squareDistanceSloop > delPos.x*delPos.x + delPos.y*delPos.y)
				{
					squareDistanceSloop = delPos.x*delPos.x + delPos.y*delPos.y;
					nearestSloop = bloop;
				}
			}else
			{
				if (squareDistanceFloop > delPos.x*delPos.x + delPos.y*delPos.y)
				{
					squareDistanceFloop = delPos.x*delPos.x + delPos.y*delPos.y;
					nearestFloop = bloop;
				}
			}
		}
		for (auto &food : chunk->foodSet())
		{
			Vec2 delPos = Vec2(food->getPosition().x - this->getPosition().x, food->getPosition().y - this->getPosition().y);
			if (squareDistanceFood > delPos.x*delPos.x + delPos.y*delPos.y)
			{
				squareDistanceFood = delPos.x*delPos.x + delPos.y*delPos.y;
				nearestFood = food;
			}
		}
	}
	double foodAngle, gloopAngle, sloopAngle,floopAngle;
	if (nearestGloop == nullptr)gloopAngle = 0;
	else
	{
		Vec2 delPos = Vec2(nearestGloop->getPosition().x - this->getPosition().x, nearestGloop->getPosition().y - this->getPosition().y);
		gloopAngle = atan2f(delPos.y, delPos.x);
	}
	if (nearestSloop == nullptr)sloopAngle = 0;
	else
	{
		Vec2 delPos = Vec2(nearestSloop->getPosition().x - this->getPosition().x, nearestSloop->getPosition().y - this->getPosition().y);
		sloopAngle = atan2f(delPos.y, delPos.x);
	}
	if (nearestFood == nullptr)foodAngle = 0;
	else
	{
		Vec2 delPos = Vec2(nearestFood->getPosition().x - this->getPosition().x, nearestFood->getPosition().y - this->getPosition().y);
		foodAngle = atan2f(delPos.y, delPos.x);
	}
	if (nearestFloop == nullptr)floopAngle = 0;
	else
	{
		Vec2 delPos = Vec2(nearestFloop->getPosition().x - this->getPosition().x, nearestFloop->getPosition().y - this->getPosition().y);
		floopAngle = atan2f(delPos.y, delPos.x);
	}
	return std::make_tuple(foodAngle, floopAngle, gloopAngle, sloopAngle);
}
void Floop::move(World& world)
{
	//double randomAngle = noise.perlin_noise(noiseX);
	//randomAngle -= (int(randomAngle / (2.0 * PI))) * 2.0 * PI;
	std::tuple<double, double, double, double> nearByInformation = getNearByInformations(world);
	std::vector<double> brainInput=
	{
		std::get<0>(nearByInformation),
		std::get<1>(nearByInformation),
		std::get<2>(nearByInformation),
		std::get<3>(nearByInformation)
	};
	brain.setAllInputs(brainInput);
	brain.calculate();
	std::vector<double> allOutPuts = brain.allOutputs();
	double rad = allOutPuts[0];
	double speedPercent = allOutPuts[1];
	Vec2 deltaPosition = Vec2(cosf(rad), sinf(rad))*3.0f*maxSpeed*speedPercent/(2.0f*PI);
	cycle += cycleIncPerTick / 2 + speedPercent * cycleIncPerTick * 0.7;
	moveTo(getPosition() + deltaPosition, world);
	//noiseX++;
}
void Floop::tick(World& world)
{
	if (die)return;
	//移动
	move(world);
	//增加cycle，减少eatCD
	//cycle += cycleIncPerTick;
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
		for (auto food = chunk->foodSet().begin(); food != chunk->foodSet().end();)
		{
			if (this->hit(**food))
			{
				cycle += Food::energy;
				world.food.erase(*food);
				food = chunk->foodSet().erase(food);
			}
			else ++food;
		}
	}
	//吃bloop
	if (!eatCD)
	{
		for (auto &chunk : nearByChunks)
		{
			for (auto &bloop : chunk->bloopSet())
			{
				if (bloop->bloopType == BloopType::gloop && hit(*bloop) && size.width>bloop->getSize().width)
				{
					bloop->die = true;
					cycle += bloop->cycle * parameter::energyTransferEfficiency;
					eatCD = 100;
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
			std::shared_ptr<Floop> newCell = std::make_shared<Floop>(world, 1, *this);
			newCell->moveTo(getPosition(),world);
			world.addBloop(newCell);
		}
	}
}
Floop::Floop(Layer& layer, int ZOrder)
{
	dna = DNA(parameter::floopSizeDNALength, parameter::floopBrainDNALength, parameter::floopMinSize);
	init(layer, ZOrder);
}
Floop::Floop(Layer& layer, int ZOrder, Floop& parent)
{
	dna = parent.dna.crossOver(parent.dna);
	dna.mutate(parameter::floopGeneMutationRate);
	init(layer, ZOrder);
}
Floop::Floop(Layer& layer, int ZOrder, Floop& parentA, Floop& parentB)
{
	dna = parentA.dna.crossOver(parentB.dna);
	dna.mutate(parameter::floopGeneMutationRate);
	init(layer, ZOrder);
}
void Floop::refreshPosition(Vec2 camera_)
{
	sprite->setPosition(position - camera_);
	sprite->setOpacity(cycle / maxCycle* 255.0f);
}