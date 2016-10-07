#ifndef DNA_H
#define DNA_H
#include "cocos2d.h"
class DNA
{
public:
	virtual void mutate(float mutationRate) = 0;
	virtual cocos2d::Size getPhrase() = 0;
};
#endif
