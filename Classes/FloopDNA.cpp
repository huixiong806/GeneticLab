#include "FloopDNA.h"
using namespace cocos2d;
FloopDNA::FloopDNA()
{
	for (int i = 0; i < FloopDNASize; i++)
	{
		genes[i] = random() % 2;
	}
}
FloopDNA FloopDNA::crossover(FloopDNA partner)
{
	FloopDNA child = FloopDNA();
	for (int i = 0; i<FloopDNASize; i++)
	{
		if (random() % 100 + 1 >= 50)child.genes[i] = genes[i];
		else child.genes[i] = partner.genes[i];
	}
	return child;
}
void FloopDNA::mutate(float mutationRate)
{
	for (int i = 0; i<FloopDNASize; i++)
	{
		if (random() % 10000 / 10000.0 <= mutationRate)
			genes[i] = random() % 2;
	}
}
Size FloopDNA::getPhrase()
{
	Size s = Size(0, 0);
	for (int i = 0; i<FloopDNASize; i++)
		s.height += genes[i] << i;
	s.height += 32;
	s.width = s.height;
	return s;
}