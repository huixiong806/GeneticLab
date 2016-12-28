#include "NeuralNetwork.h"
using namespace std;
NS_ANN_BEGIN
NeuralNetwork::NeuralNetwork(){}
NeuralNetwork::NeuralNetwork(bool fullConnection, unsigned int layerSize,unsigned int inputSize,std::vector<unsigned int>neuronSize)
{
	input.resize(inputSize);
	for (auto &i : input)
		i = make_shared<double>(0);
	neuron.resize(layerSize);
	for (int i = 0; i < layerSize; ++i)
		for (int j = 0; j < neuronSize[i]; ++j)
			neuron[i].emplace_back(Neuron());
	if (fullConnection)setToFull();
}
void NeuralNetwork::setToFree()
{
	for (auto &i : neuron)
		for (auto &j : i)
			j.clearInput();
}
void NeuralNetwork::setToFull()
{
	setToFree();
	for (auto &i : neuron[0])
		for (auto &j : input)
			i.addInput(j);
	for (int i = 1; i < neuron.size(); ++i)
		for (auto &j : neuron[i])
			for (auto &k : neuron[i - 1])
				j.addInput(shared_ptr<double>(std::addressof(k.Output()), [](void*){}));
}

/** connect A's axon to B's dendron.If already exist,do nothing. */
void NeuralNetwork::connect(unsigned int axonLayerIndex, unsigned int axonIndex, unsigned int dendronIndex)
{
	neuron[axonLayerIndex + 1][dendronIndex].addInput(shared_ptr<double>(&neuron[axonLayerIndex][axonIndex].Output(), [](void*){}));
}

/** disconnect. If not exist,do nothing.*/
void NeuralNetwork::disconnect(unsigned int axonLayerIndex, unsigned int axonIndex, unsigned int dendronIndex)
{
	neuron[axonLayerIndex + 1][dendronIndex].deleteInput(shared_ptr<double>(&neuron[axonLayerIndex][axonIndex].Output(), [](void*){}));
}

/** set the size of layers */
void NeuralNetwork::setLayerSize(unsigned int size)
{
	neuron.resize(size);
}
/** set the size of neurons of given layer */
void NeuralNetwork::setNeuronSize(unsigned int layerIndex, unsigned int size)
{
	neuron[layerIndex].resize(size);
}

/** set the value of a given input */
void NeuralNetwork::resetInput(unsigned int index, double value)
{
	input[index] = make_shared<double>(value);
}

/** add an input
*  warning:it is unsafe not to use smart pointer.
*/
void NeuralNetwork::addInput(shared_ptr<double> value)
{
	input.push_back(value);
}

/** clear all inputs */
void NeuralNetwork::clearInput()
{
	input.clear();
}

/** set the value of all inputs
*   warning:it is unsafe not to use smart pointer.
*/
void NeuralNetwork::setAllInputs(vector<double> value)
{
	for (int i = 0; i < value.size(); ++i)
		*input[i]=value[i];
}

/** get the value of given output */
double NeuralNetwork::output(unsigned int index)
{
	return neuron[neuron.size() - 1][index].Output();
}

/** get the value of all outputs */
vector<double> NeuralNetwork::allOutputs()
{
	vector<double> res;
	for (auto i : neuron[neuron.size() - 1])
		res.push_back(i.Output());
	return res;
}

/** get the pointer of given output */
double* NeuralNetwork::outputPtr(unsigned int index)
{
	return &neuron[neuron.size() - 1][index].Output();
}

/** get a vector includes pointers of all outputs */
std::vector<double*> NeuralNetwork::allOutputPtrs()
{
	vector<double*> res;
	for (auto i : neuron[neuron.size() - 1])
		res.push_back(&i.Output());
	return res;
}

/** calculate */
void NeuralNetwork::calculate()
{
	for (auto &i : neuron)
		for (auto &j : i)
			j.calculate();
}
std::vector<std::vector<Neuron>>& NeuralNetwork::getNeuron()
{
	return neuron;
}
std::vector<std::shared_ptr<double>>& NeuralNetwork::getInput()
{
	return input;
}
NS_ANN_END