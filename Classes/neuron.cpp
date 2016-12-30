#include "neuron.h"
#include <cstdlib>
#define RANDNUM (rand()/(double)RAND_MAX)*2.0-1.0
using namespace std;
NS_ANN_BEGIN
/** initalize */
Neuron::Neuron()
{
	bias = -1.0;
	inputSize = 0;
}
/** initalize 2 */
Neuron::Neuron(unsigned int InputCount)
{
	bias = -1.0;
	inputSize = InputCount;
	for(int i=0;i<(int)InputCount;++i)
	{
		weight.emplace_back(RANDNUM);
		value.emplace_back(nullptr);
	}
}

/** set activation function */
void Neuron::setActivationFun(double(*funType)(double))
{
	activationFun = funType;
}

/** calculate */
void Neuron::calculate()
{
	double sum = 0;
	for(int i=0;i<(int)inputSize;++i)
		sum+=weight[i]*(*value[i]);
	sum += bias;
	output = activationFun(sum);
}

double& Neuron::Output()
{
	return output;
}

/** calculate and return the output*/
double Neuron::getOutput()
{
	calculate();
	return output;
}

/** set the input */
void Neuron::setInput(unsigned int index,double input)
{
	value[index] = make_shared<double>(input);
}
	
/** bind the input */
void Neuron::bindInput(unsigned int index,shared_ptr<double> input)
{
	value[index] = input;
}

/** add an input (pointer),if already exist,do nothing.*/
void Neuron::addInput(std::shared_ptr<double> input)
{
	for (auto iter = value.begin(); iter != value.end(); ++iter)
		if (std::addressof(**iter) == std::addressof(*input)) return;
	value.push_back(input);
	weight.emplace_back(RANDNUM);
	++inputSize;
}
	
/** delete input,if not exist,do nothing.*/
void Neuron::deleteInput(std::shared_ptr<double> target)
{
	for(int i=0;i<(int)inputSize;++i)
	{
		if(value[i] == target)
		{
			value.erase(value.begin()+i);
			weight.erase(weight.begin()+i);
			--inputSize;
			return; 
		}
	}
}
	
/** clear input */
void Neuron::clearInput()
{
	value.clear();
}
	
/** get input size */
unsigned int Neuron::getInputSize()
{
	return inputSize;
}

void Neuron::setWeight(std::vector<double>& weight)
{
	this->bias = weight.back();
	weight.pop_back();
	this->weight = weight;
}
NS_ANN_END
