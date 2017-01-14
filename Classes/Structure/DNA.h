#ifndef DNA_H
#define DNA_H
#include "cocos2d.h"
class DNA
{
public:
	DNA() {}
	DNA(int SizeDNALength,int BrainDNALength,int MinSize);
	virtual ~DNA(){}
	DNA crossOver(DNA partner);
	virtual void mutate(float mutationRate);
	virtual cocos2d::Size getSize();
	virtual float getBrainGene(int index);
private:
	int sizeDNALength, brainDNALength;
	int minSize;
	std::vector<bool> sizeGene;
	std::vector<float> brainGene;
};
#endif
