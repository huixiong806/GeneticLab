#ifndef SLOOPDNA_H
#define SLOOPDNA_H
#include "cocos2d.h"
#include "DNA.h"
using namespace cocos2d;
class SloopDNA :public DNA
{
public:
	bool genes[8];
	SloopDNA();
	SloopDNA crossover(SloopDNA partner);
	virtual void mutate(float mutationRate);
	virtual Size getPhrase();
private:
	static const int SloopDNASize = 8;
};
#endif
