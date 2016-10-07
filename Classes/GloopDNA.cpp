#include "GloopDNA.h"
using namespace cocos2d;
GloopDNA::GloopDNA()
{
	for (int i = 0; i < GloopDNASize; i++)
	{
		genes[i] = random() % 2;
	}
}
GloopDNA GloopDNA::crossover(GloopDNA partner)
{
	GloopDNA child = GloopDNA();
	for (int i = 0; i<GloopDNASize; i++)
	{
		if (random() % 100 + 1 >= 50)child.genes[i] = genes[i];
		else child.genes[i] = partner.genes[i];
	}
	return child;
}
void GloopDNA::mutate(float mutationRate)
{
	for (int i = 0; i<GloopDNASize; i++)
	{
		if (random() % 10000 / 10000.0 <= mutationRate)
			genes[i] = random() % 2;
	}
}
Size GloopDNA::getPhrase()
{
	Size s = Size(0, 0);
	for (int i = 0; i<GloopDNASize; i++)
		s.height += genes[i] << i;
	s.height += 32;
	s.width = s.height;
	return s;
}