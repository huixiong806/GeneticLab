#ifndef NEURON_H
#define NEURON_H
#include<vector>
#include"Node.h"
NS_ANN_BEGIN
class Neuron:public Node
{
public:
	Neuron();

	Neuron(unsigned int InputCount);

	/** set activation function */
	void setActivationFun(double(*funType)(double));
	
	/** calculate */
	void calculate();
	
	/** return the output */
	double& Output();

	/** calculate and return the output */
	double getOutput();
	
	/** set the input */
	void setInput(unsigned int index,double input);
	
	/** bind the input 
	 *  warning:It is unsafe not to use smart pointer.
	*/
	void bindInput(unsigned int index,std::shared_ptr<double> input);
	
	/** add an input (pointer),if already exist,do nothing.
	 *  warning:It is unsafe not to use smart pointer.
	*/
	void addInput(std::shared_ptr<double> input);
	
	/** delete input,if not exist,do nothing.
	 *  warning:It is unsafe not to use smart pointer.
	*/
	void deleteInput(std::shared_ptr<double> target);
	
	/** clear input */
	void clearInput();
	
	/** get input size */
	unsigned int getInputSize();

	void setWeight(std::vector<double>& weight);
protected:
	/** bias value */
	double bias;

	/** weights */
	std::vector<double>weight;

	/** values */
	std::vector<std::shared_ptr<double>>value;

	/** return the size of inputs */
	unsigned int inputSize;
	
	/** pointer of activation function */
	double(*activationFun)(double);
};
NS_ANN_END
#endif
