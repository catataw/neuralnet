#ifndef LAYER_H
#define LAYER_H

#include "connection.h"
#include "neuron.h"

#include <vector>
#include <map>

/**
* Class describing a layer in the neural network. Each layer contains a number of neurons
* and a number of weights connecting neurons from this layer to the previous layer.
* Each layer contains a bias neuron with fixed value of 1.0
*
* @author Marek Magdziak
*/
class Layer {

public:

	/**
	* Constructor creating a new layer with a specified number of neurons
	*
	* @param numberOfNeurons	Number of neurons which will be created in this specific layer
	*/
    Layer(unsigned numberOfNeurons);

	/**
	* Constructor creating a new layer with a specified number of neurons and using
	* previous layer to make connections
	*
	* @param numberOfNeurons	Number of neurons which will be created in this specific layer
	*
	* @param previousLayer		Reference to a previous layer used for creating connections from this layer's
	*							neurons to the previous ones
	*/
    Layer(unsigned numberOfNeurons, Layer& previousLayer);

	/**
	* Destructor cleaning up all resources
	*/
    ~Layer() {}

	/**
	* Sets values to all neurons in this layer
	*
	* @param values		Reference to a vector of doubles which will be used as a source.
	*					The amount of input values has to match the setup amount
	*					of neurons in this layer.
	*/
    void setValues(std::vector<double> &values);

	/**
	* Gets values from neurons in this layer
	*
	* @param values		Reference to a vector of doubles which will be used as a destination
	*					for values from neurons in this layer
	*
	* @param bias		Defines whether bias neuron values shall be included in the result set
	*/
    void getValues(std::vector<double> &values, bool bias = true);

	/**
	* Gets the total number of neurons in this layer including the bias neuron
	*
	* @returns Unsigned integer containing information about the total number of neurons
	*/
    unsigned getNeuronCount();

	/**
	* Gets values from the specified layer and using available connections to its neurons
	* calculates values for each neuron in this layer
	*
	* @param sourceLayer	Reference to the previous layer in the network
	*/
    void feedForward(Layer& sourceLayer);

	/**
	* Calculates error gradients based on the current values and the desired values
	*
	* @param values		Reference to a vector of doubles which will be used as a source for
	*					specifying the desired values based on which it will write gradients into
	*					the current layer neurons.
	*
	* @param bias		Defines whether to take bias neuron into account when calculating gradients
	*/
    void calculateGradients(std::vector<double> &values, bool bias = false);

	/**
	* Calculates error gradients based on the current values and values from the next layer
	* in the network layout
	*
	* @param nextLayer	Reference to the next layer in the network
	*/
    void calculateGradients(Layer &nextLayer);

	/**
	* Gets all connection weights from a specific neuron from the previous layer int the network
	*
	* @param sourceNeuronIdx	Identifier of the neuron from the previous layer
	*
	* @param weights			Vector of doubles which will be populated with weights 
	*							from all the connections going from the specified neuron
	*/
    void getWeights(unsigned sourceNeuronIdx, std::vector<double>& weights);

	/**
	* Gets all connections from a specific neuron from the previous layer int the network
	*
	* @param sourceNeuronIdx	Identifier of the neuron from the previous layer
	*
	* @param weights			Vector of pointers to a Weight instance which will be 
	*							populated with weights from all the connections going 
	*							from the specified neuron
	*/
    void getWeights(unsigned sourceNeuronIdx, std::vector<Connection*>& weights);

	/**
	* Updates input weights based on the gradients from this layer and output values from the previous
	* layer in the network
	*
	* @param previousLayer	Reference to the previous layer on the network
	*
	* @param eta			The learning rate of the neural network. This is a number from 0.0 to 1.0
	*
	* @param alpha			Defines the momentum of a neural network learning
	*/
    void updateInputWeights(Layer &previousLayer, double eta, double alpha);

	/**
	* Gets a neuron by its index in this layer
	*
	* @param index	A numeric identifier of a neuron in this layer
	*
	* @returns		Reference to a neuron instance based on the index
	*/
	Neuron& getNeuron(unsigned index);

private:
    std::vector<Neuron> m_Neurons;
    std::vector<std::vector<Connection>> m_InputWeights;
};

#endif