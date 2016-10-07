#ifndef FLOOPDNA_H
#define FLOOPDNA_H
#include "cocos2d.h"
#include "DNA.h"
class FloopDNA :public DNA
{
public:
	bool genes[8];
	FloopDNA();
	FloopDNA crossover(FloopDNA partner);
	virtual void mutate(float mutationRate);
	virtual cocos2d::Size getPhrase();
private:
	static const int FloopDNASize = 8;
};
#endif
