#include "Sloop.h"
#include "HelloWorldScene.h"
using namespace cocos2d;
Sloop::~Sloop()
{
}
void Sloop::initBrain()
{
	brain = ann::NeuralNetwork(true, 3, 2, std::vector<unsigned int>{4,3, 2});
	std::vector<std::vector<ann::Neuron>>& neuron = brain.getNeuron();
	int geneIndex = 0;
	for (auto &i : neuron)
	{
		for (auto &j : i)
		{
			//+1 is because bias
			int needSize = j.getInputSize()+1;
			std::vector<double>input;
			while (needSize--)
				input.push_back(dna.getBrainGene(geneIndex++));
			j.setWeight(input);
			j.setActivationFun(function::sigmoid);
		}
	}
}
void Sloop::init(Layer& layer, int ZOrder)
{
	initSprite(layer, "images\\bloop.png", ZOrder);
	shape = Shape::circle;
	setColor(Color3B(0, 0, 255));
	setRandomPosition(Vec2(0, 0), parameter::worldSize);
	setSize(dna.getSize());
	maxSpeed = speedCalcPrmA+size.width*speedCalcPrmB;
	//noise.seed = random<unsigned long long>(0ULL, ULLONG_MAX);
	//noise.amplitude = 1;
	//noise.frequency = 0.0025*(speed);
	//noiseX = 0;
	cycle = maxCycle*parameter::sloopStartCycleCoefficient;
	eatCD = 0;
	die = false;
	bloopType = BloopType::sloop;
	initBrain();
}
std::tuple<double,double> Sloop::getNearByInformation(World& world)
{
	std::vector<Chunk*> nearByChunks = getNineNearByChunks(world);
	std::shared_ptr<Bloop> nearestFGloop = nullptr;
	std::shared_ptr<Bloop> nearestSloop = nullptr;
	std::shared_ptr<Food> nearestFood = nullptr;
	double squareDistanceBloop = INFINITE,squareDistanceFood = INFINITE, squareDistanceSloop = INFINITE;
	for (auto &chunk : nearByChunks)
	{
		for (auto &bloop : chunk->bloopSet())
		{
			if (bloop->bloopType == BloopType::floop|| bloop->bloopType == BloopType::gloop)
			{
				Vec2 delPos = Vec2(bloop->getPosition().x - this->getPosition().x, bloop->getPosition().y - this->getPosition().y);
				if (squareDistanceBloop > delPos.x*delPos.x + delPos.y*delPos.y)
				{
					squareDistanceBloop = delPos.x*delPos.x + delPos.y*delPos.y;
					nearestFGloop = bloop;
				}
			}
			else
			{
				Vec2 delPos = Vec2(bloop->getPosition().x - this->getPosition().x, bloop->getPosition().y - this->getPosition().y);
				if (squareDistanceSloop > delPos.x*delPos.x + delPos.y*delPos.y)
				{
					squareDistanceSloop = delPos.x*delPos.x + delPos.y*delPos.y;
					nearestSloop = bloop;
				}
			}
		}
		/*
		for (auto &food : chunk->foodSet())
		{
			Vec2 delPos = Vec2(food->getPosition().x - this->getPosition().x, food->getPosition().y - this->getPosition().y);
			if (squareDistanceFood > delPos.x*delPos.x + delPos.y*delPos.y)
			{
				squareDistanceFood = delPos.x*delPos.x + delPos.y*delPos.y;
				nearestFood = food;
			}
		}
		*/
	}
	double foodAngle=0, fsloopAngle=0,sloopAngle=0;
	if (nearestFGloop != nullptr)
	{
		Vec2 delPos = Vec2(nearestFGloop->getPosition().x - this->getPosition().x, nearestFGloop->getPosition().y - this->getPosition().y);
		fsloopAngle = atan2f(delPos.y, delPos.x);
	}
	/*
	if (nearestFood == nullptr)foodAngle = 0;
	else
	{
		Vec2 delPos = Vec2(nearestFood->getPosition().x - this->getPosition().x, nearestFood->getPosition().y - this->getPosition().y);
		foodAngle = atan2f(delPos.y, delPos.x);
	}
	*/
	if (nearestSloop != nullptr)
	{
		Vec2 delPos = Vec2(nearestSloop->getPosition().x - this->getPosition().x, nearestSloop->getPosition().y - this->getPosition().y);
		sloopAngle = atan2f(delPos.y, delPos.x);
	}
	return std::make_tuple(sloopAngle, fsloopAngle);
}
void Sloop::move(World& world)
{
	//double randomAngle = noise.perlin_noise(noiseX);
	//randomAngle -= (int(randomAngle / (2.0 * PI))) * 2.0 * PI;
	std::tuple<double, double> neayByinfodmation = getNearByInformation(world);
	std::vector<double> brainInput = 
	{
		std::get<0>(neayByinfodmation),
		std::get<1>(neayByinfodmation),
	};
	brain.setAllInputs(brainInput);
	brain.calculate();
	double rad = brain.allOutputs()[0];
	double speedPercent = brain.allOutputs()[1];
	Vec2 deltaPosition = Vec2(cosf(rad), sinf(rad)) * 4 * maxSpeed*speedPercent;
	cycle += cycleIncPerTick / 2 + speedPercent * cycleIncPerTick * 0.7;
	moveTo(getPosition() + deltaPosition, world);
	//noiseX++;
}
void Sloop::tick(World& world)
{
	if(die)return;
	//移动，增加cycle
	move(world);
	//减少eatCD
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
	/*
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
	*/
	//吃bloop
	if (!eatCD)
	{
		for (auto &chunk : nearByChunks)
		{
			for (auto &bloop : chunk->bloopSet())
			{
				if ((bloop->bloopType == BloopType::floop || bloop->bloopType == BloopType::gloop) && hit(*bloop) && size.width>bloop->getSize().width)
				{
					bloop->die = true;
					cycle += bloop->cycle*parameter::energyTransferEfficiency;
					eatCD = bloop->bloopType == BloopType::floop ? 350 : 150;
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
			newCell->moveTo(getPosition(), world);
			world.addBloop(newCell);
		}
	}
}
Sloop::Sloop(Layer& layer, int ZOrder)
{
	dna = DNA(parameter::sloopSizeDNALength, parameter::sloopBrainDNALength, parameter::sloopMinSize);
	init(layer, ZOrder);
}
Sloop::Sloop(Layer& layer, int ZOrder, Sloop& parent)
{
	dna = parent.dna.crossOver(parent.dna);
	dna.mutate(parameter::sloopGeneMutationRate);
	init(layer, ZOrder);
}
Sloop::Sloop(Layer& layer, int ZOrder, Sloop& parentA, Sloop& parentB)
{
	dna = parentA.dna.crossOver(parentB.dna);
	dna.mutate(parameter::sloopGeneMutationRate);
	init(layer, ZOrder);
}
void Sloop::refreshPosition(Vec2 camera_)
{
	sprite->setPosition(position - camera_);
	sprite->setOpacity(cycle / maxCycle* 255.0f);
}