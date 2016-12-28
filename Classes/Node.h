#ifndef NODE_H
#define NODE_H
#include<vector>
#include<memory>
#include"Functions.hpp"
NS_ANN_BEGIN
class Node
{
public:
	Node(){}
	virtual ~Node(){}
protected:
	/** output value */
	double output;
};
NS_ANN_END
#endif