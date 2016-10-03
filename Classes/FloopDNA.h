#ifndef FLOOPDNA_H
#define FLOOPDNA_H
#include "cocos2d.h"
#include "DNA.h"
using namespace cocos2d;
class FloopDNA :public DNA
{
public:
	bool genes[8];
	FloopDNA();
	FloopDNA crossover(FloopDNA partner);
	virtual void mutate(float mutationRate);
	virtual Size getPhrase();
private:
	static const int FloopDNASize = 8;
};
#endif
