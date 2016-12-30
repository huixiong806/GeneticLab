#include "DNA.h"
DNA::DNA(int SizeDNALength, int BrainDNALength,int MinSize)
{
	sizeDNALength = SizeDNALength;
	brainDNALength = BrainDNALength;
	sizeGene.resize(SizeDNALength);
	brainGene.resize(BrainDNALength);
	minSize = MinSize;
	for (auto &item : sizeGene)
	{
		item = (bool)cocos2d::random<int>(0, 1);
	}
	for (auto &item : brainGene)
	{
		item = cocos2d::random<float>(-1.0, 1.0);
	}
}
DNA DNA::crossOver(DNA partner)
{
	DNA child = DNA(sizeDNALength, brainDNALength, minSize);
	for (int i = 0; i<sizeDNALength; i++)
	{
		if ((bool)cocos2d::random<int>(0, 1))
			child.sizeGene[i] = sizeGene[i];
		else 
			child.sizeGene[i] = partner.sizeGene[i];
	}
	for (int i = 0; i < brainDNALength; i++)
	{
		if ((bool)cocos2d::random<int>(0, 1))
			child.brainGene[i] = brainGene[i];
		else 
			child.brainGene[i] = partner.brainGene[i];
	}
	return child;
}
void DNA::mutate(float mutationRate)
{
	for (int i = 0; i<sizeDNALength; i++)
	{
		if (cocos2d::random<float>(0.0, 1.0) <= mutationRate)
			sizeGene[i] = sizeGene[i] ? false : true;
	}
	for (int i = 0; i < brainDNALength; ++i)
	{
		if (cocos2d::random<float>(0.0, 1.0) <= mutationRate)
			brainGene[i] = cocos2d::random<float>(-1.0, 1.0);
	}
}
cocos2d::Size DNA::getSize()
{
	int d = 0;
	for (int i = 0; i<sizeDNALength; i++)
		d += sizeGene[i] << i;
	d += minSize;
	return cocos2d::Size(d, d);
}
float DNA::getBrainGene(int index)
{
	return brainGene[index];
}