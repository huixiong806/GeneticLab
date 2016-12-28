#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H
#include "neuron.h"
NS_ANN_BEGIN
class NeuralNetwork
{
public:
	/** start as an empty network*/
	NeuralNetwork();
	
	/** init (1=full type=full connections,0=free type=no connection)*/
	NeuralNetwork(bool fullConnection,unsigned int layerSize,unsigned int inputSize,std::vector<unsigned int>neuronSize);
	
	/** set to full connections */
	void setToFull();
	
	/** set to no connection */
	void setToFree();
	
	/** connect A's axon to B's dendron.If already exist,do nothing. */
	void connect(unsigned int axonLayerIndex ,unsigned int axonIndex,unsigned int dendronIndex);
	
	/** disconnect. If not exist,do nothing.*/
	void disconnect(unsigned int axonLayerIndex ,unsigned int axonIndex,unsigned int dendronIndex);
	
	/** set the size of layers
	 *	warning:this could make some connections illegal.
	*/
	void setLayerSize(unsigned int size);
	
	/** set the size of neurons of given layer 
	 *	warning:this could make some connections illegal.
	*/
	void setNeuronSize(unsigned int layerIndex, unsigned int size);
	
	/** set the value of a given input
	 *	warning:this could make some connections illegal.
	*/
	void resetInput(unsigned int index,double value);
	
	/** add an input
	 *  warning:it is unsafe not to use smart pointer.
	*/
	void addInput(std::shared_ptr<double> value);

	/** clear all inputs 
	 *	warning:this could make some connections illegal.
	*/
	void clearInput();

	/** set the value of all inputs
	 *  warning:it is unsafe not to use smart pointer.
	*/
	void setAllInputs(std::vector<double> value);
	
	/** get the value of given output */
	double output(unsigned int index);
	
	/** get the value of all outputs */
	std::vector<double> allOutputs();
	
	/** get the pointer of given output */
	double* outputPtr(unsigned int index);
	
	/** get a vector includes pointers of all outputs */
	std::vector<double*> allOutputPtrs();
	
	/** calculate */
	void calculate();

	std::vector<std::vector<Neuron>>& getNeuron();

	std::vector<std::shared_ptr<double>>& getInput();
protected:
	/** input layer */
	std::vector<std::shared_ptr<double>> input;
	/** hidden and output layer */
	std::vector<std::vector<Neuron>> neuron;
};
NS_ANN_END
#endif

