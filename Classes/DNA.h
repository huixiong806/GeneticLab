#ifndef DNA_H
#define DNA_H
#include "cocos2d.h"
using namespace cocos2d;
class DNA
{
public:
	virtual void mutate(float mutationRate) = 0;
	virtual Size getPhrase() = 0;
};
#endif
