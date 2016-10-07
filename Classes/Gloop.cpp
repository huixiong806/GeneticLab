#include "Gloop.h"
#include "HelloWorldScene.h"
Gloop::~Gloop()
{
}
void Gloop::init(Layer& layer, int ZOrder)
{
	initSprite(layer, "images\\bloop.png", ZOrder);
	shape = Shape::circle;
	setColor(Color3B(0, 255, 0));
	setRandomPosition(Vec2(0, 0), publicVars::superHugeSize);
	setSize(dna.getPhrase());
	label = Label::createWithTTF("", "fonts/Marker Felt.ttf", 0.6*size.width);
	layer.addChild(label, ZOrder + 1);
	speed = speedCalcPrmA+size.width*speedCalcPrmB;
	noise.seed = rand() % 2147483648;
	noise.amplitude = 1;
	noise.frequency = 0.0025*(speed);
	noiseX = 0;
	cycle = maxCycle/4;
	die = false;
	bloopType = BloopType::gloop;
}
float Gloop::FoodProvideRatePerTick()
{
	if (cycle < 70)return 0;
	else return 0.0008+cycle*0.000005;
}
void Gloop::tick(World& world)
{
	//移动
	move();
	//增加cycle
	int gloopCount = 0;
	for (auto i : world.bloop)
	{
		if (i->bloopType == BloopType::gloop)
			++gloopCount;
	}
	cycle += publicVars::sunEnergyPerTick / gloopCount;
	//绘制
	refreshPosition(world.camera);
	//掉落食物
	float randomNumber = random<float>(0,1);
	if (randomNumber < FoodProvideRatePerTick())
	{
		cycle -= Food::energy/publicVars::energyTransferEfficiency;
		world.food.emplace_back(std::make_shared<Food>(world, 1));
		(*(world.food.end()-1))->setPosition(getPosition());
	}
	//分裂
	if (cycle >= maxCycle)
	{
		die = true;
		for (int i = 0; i < 2;++i)
		{
			world.bloop.emplace_back(std::make_shared<Gloop>(world, 1,*this));
			(*(world.bloop.end() - 1))->setPosition(getPosition());
		}
	}
}
Gloop::Gloop(Layer& layer, int ZOrder)
{
	dna = GloopDNA();
	init(layer, ZOrder);
	cycle = random<int>(maxCycle * 1 / 6, maxCycle * 1 / 4);
}
Gloop::Gloop(Layer& layer, int ZOrder, Gloop& parent)
{
	dna = parent.dna.crossover(parent.dna);
	dna.mutate(0.02);
	init(layer, ZOrder);
}
Gloop::Gloop(Layer& layer, int ZOrder, Gloop& parentA, Gloop& parentB)
{
	dna = parentA.dna.crossover(parentB.dna);
	dna.mutate(0.02);
	init(layer, ZOrder);
}
void Gloop::refreshPosition(Vec2 camera_)
{
	sprite->setPosition(position - camera_);
	label->setPosition(position - camera_);
	std::string str;
	std::ostringstream os;
	os << (int)cycle;
	str.append(os.str());
	label->setString(str);
}