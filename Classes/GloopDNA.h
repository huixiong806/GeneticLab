#ifndef GLOOPDNA_H
#define GLOOPDNA_H
#include "cocos2d.h"
#include "DNA.h"
class GloopDNA :public DNA
{
public:
	bool genes[5];
	GloopDNA();
	GloopDNA crossover(GloopDNA partner);
	virtual void mutate(float mutationRate);
	virtual cocos2d::Size getPhrase();
private:
	static const int GloopDNASize = 5;
};
#endif
