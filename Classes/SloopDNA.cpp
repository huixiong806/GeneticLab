#include "SloopDNA.h"
using namespace cocos2d;
SloopDNA::SloopDNA()
{
	for (int i = 0; i < SloopDNASize; i++)
	{
		genes[i] = random() % 2;
	}
}
SloopDNA SloopDNA::crossover(SloopDNA partner)
{
	SloopDNA child = SloopDNA();
	for (int i = 0; i<SloopDNASize; i++)
	{
		if (random() % 100 + 1 >= 50)child.genes[i] = genes[i];
		else child.genes[i] = partner.genes[i];
	}
	return child;
}
void SloopDNA::mutate(float mutationRate)
{
	for (int i = 0; i<SloopDNASize; i++)
	{
		if (random() % 10000 / 10000.0 <= mutationRate)
			genes[i] = random() % 2;
	}
}
Size SloopDNA::getPhrase()
{
	Size s = Size(0, 0);
	for (int i = 0; i<SloopDNASize; i++)
		s.height += genes[i] << i;
	s.height += 128;
	s.width = s.height;
	return s;
}