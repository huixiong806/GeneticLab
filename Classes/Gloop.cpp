#include "Gloop.h"
#include "HelloWorldScene.h"
using namespace cocos2d;
Gloop::~Gloop()
{
}
void Gloop::initBrain()
{
	brain = ann::NeuralNetwork(true, 3, 2, std::vector<unsigned int>{4,3, 2});
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
}
void Gloop::init(Layer& layer, int ZOrder)
{
	initSprite(layer, "images\\bloop.png", ZOrder);
	shape = Shape::circle;
	setColor(Color3B(0, 255, 0));
	setRandomPosition(Vec2(0, 0), parameter::worldSize);
	setSize(dna.getSize());
	maxSpeed = speedCalcPrmA+size.width*speedCalcPrmB;
	noise = PerlinNoise(random<uint32_t>(0, UINT32_MAX));
	noiseOff = Vec2(random<double>(0.0, 10000.0), random<double>(0.0, 10000.0));
	die = false;
	cycle = maxCycle*parameter::gloopStartCycleCoefficient;
	bloopType = BloopType::gloop;
	initBrain();
}
float Gloop::FoodProvideRatePerTick()
{
	if (cycle < 70)return 0;
	else return 0.0008+cycle*0.000005;
}
std::pair<double,double> Gloop::getNearestBloop(World& world)
{
	std::vector<Chunk*> nearByChunks = getNineNearByChunks(world);
	std::shared_ptr<Bloop> nearestFSloop = nullptr;
	std::shared_ptr<Bloop> nearestGloop = nullptr;
	double fsSquareDistance = INFINITE,gSquareDistance = INFINITE;
	for (auto &chunk : nearByChunks)
	{
		for (auto &bloop : chunk->bloopSet())
		{
			Vec2 delPos = Vec2(bloop->getPosition().x - this->getPosition().x, bloop->getPosition().y - this->getPosition().y);
			if (bloop->bloopType == BloopType::floop || bloop->bloopType == BloopType::sloop)
			{
				if (fsSquareDistance > delPos.x*delPos.x + delPos.y*delPos.y)
				{
					fsSquareDistance = delPos.x*delPos.x + delPos.y*delPos.y;
					nearestFSloop = bloop;
				}
			}else{
				if (gSquareDistance > delPos.x*delPos.x + delPos.y*delPos.y)
				{
					gSquareDistance = delPos.x*delPos.x + delPos.y*delPos.y;
					nearestGloop = bloop;
				}
			}	
		}
	}
	int fsAngle = 0, gAngle = 0;
	if (nearestFSloop != nullptr)
	{
		Vec2 delPos = Vec2(nearestFSloop->getPosition().x - this->getPosition().x, nearestFSloop->getPosition().y - this->getPosition().y);
		fsAngle = atan2f(delPos.y, delPos.x);
	}
	if (nearestGloop != nullptr)
	{
		Vec2 delPos = Vec2(nearestGloop->getPosition().x - this->getPosition().x, nearestGloop->getPosition().y - this->getPosition().y);
		gAngle = atan2f(delPos.y, delPos.x);
	}
	return std::make_pair(fsAngle, gAngle);
}
void Gloop::move(World& world)
{
	Vec2 velocity = 
	Vec2(
		function::map(noise.noise(noiseOff.x += 0.003), -0.5f, 0.5f, -maxSpeed, maxSpeed),
		function::map(noise.noise(noiseOff.y += 0.003), -0.5f, 0.5f, -maxSpeed, maxSpeed)
	);
	double deltaAngle = 0;
	std::pair<double,double> nearestBloop = getNearestBloop(world);
	std::vector<double> brainInput = { nearestBloop.first,nearestBloop.second};
	brain.setAllInputs(brainInput);
	brain.calculate();
	deltaAngle = brain.allOutputs()[0];
	double speedPercent = brain.allOutputs()[1];
	Vec2 deltaPosition = Vec2(cosf(deltaAngle), sinf(deltaAngle))*maxSpeed*speedPercent;
	moveTo(getPosition() + deltaPosition, world);
}
void Gloop::tick(World& world)
{
	if (die)return;
	//移动
	move(world);
	//增加cycle
	cycle += parameter::sunEnergyPerTick / world.bloopCount[(int)BloopType::gloop];
	//绘制
	refreshPosition(world.camera);
	//掉落食物
	float randomNumber = random<float>(0,1);
	if (randomNumber < FoodProvideRatePerTick())
	{
		std::shared_ptr<Food> newFood = std::make_shared<Food>(world, 1);
		cycle -= Food::energy/ parameter::energyTransferEfficiency;
		world.food.insert(newFood);
		newFood->setPosition(getPosition());
		newFood->addToChunk(newFood->getChunk(world), newFood);
	}
	//分裂
	if (cycle >= maxCycle)
	{
		die = true;
		for (int i = 0; i < 2;++i)
		{
			std::shared_ptr<Gloop> newCell = std::make_shared<Gloop>(world, 1, *this);
			newCell->moveTo(getPosition(),world);
			world.addBloop(newCell);
		}
	}
}
Gloop::Gloop(Layer& layer, int ZOrder)
{
	dna = DNA(parameter::gloopSizeDNALength, parameter::gloopBrainDNALength,parameter::gloopMinSize);
	init(layer, ZOrder);
}
Gloop::Gloop(Layer& layer, int ZOrder, Gloop& parent)
{
	dna = parent.dna.crossOver(parent.dna);
	dna.mutate(parameter::gloopGeneMutationRate);
	init(layer, ZOrder);
}
Gloop::Gloop(Layer& layer, int ZOrder, Gloop& parentA, Gloop& parentB)
{
	dna = parentA.dna.crossOver(parentB.dna);
	dna.mutate(parameter::gloopGeneMutationRate);
	init(layer, ZOrder);
}
void Gloop::refreshPosition(Vec2 camera_)
{
	sprite->setPosition(position - camera_);
	sprite->setOpacity(cycle / maxCycle* 255.0f);
}