#ifndef NETWORK_H
#define NETWORK_H

#include "Layer.h"
#include <vector>

/**
* Prototype of Network class
*/
class Network;

#ifdef _BOX_CLASS_NAME 
#undef _BOX_CLASS_NAME
#endif

#define _BOX_CLASS_NAME Network
#include "prop.h"

/**
* Feed forward neural network. This class represents an entry point for all neural network operations.
*
* @author Marek Magdziak
*/
class Network {
public:

    /**
    * Contructor for the neural network class
	*
    * @param topology	Vector of unsigned integers describing the number of neurons in a different layers
    *					the minimum amount of layers is three - input layer, hidden layer, output layer.
	*					The minimum amount of neurons in each layer is one.
    */
    Network(std::vector<unsigned> &topology);

    /**
    * Destructor cleaning up all resources
    */
    ~Network() {}

	/**
	* Sets values to the input neuron layer
	*
	* @param inputValues	Reference to a vector of doubles which will be used as a source.
	*						The amount of input values has to match the setup amount 
	*						of neurons in the input layer.
	*/
    void setInputValues(std::vector<double> &inputValues);

	/**
	* Invokes the feed forward procedure and returns values form the output layer
	*
	* @param outputValues	Reference to a vector of doubles which will be used as a destination
	*						for values from the output layer
	*/
    void getOutputValues(std::vector<double> &outputValues);

	/**
	* Gets values from a specific layer specified by index parameter
	*
	* @param outputValues	Reference to a vector of doubles which will be used as a destination
	*						for values from the specified layer
	*
	* @param index			Specifies the source layer. Layers are indexed from the left where
	*						input layer is the first one and output layer the last one.
	*/
    void getValuesFromLayer(std::vector<double> &outputValues, unsigned index);

	/**
	* Propagates backwards error from the difference of values from the output layer 
	* and the target values to all weights between neurons from all setup layers
	*
	* @param targetValues	Reference to a vector of doubles which is containing the desired output
	*						for the defined input. The amount of values has to be the same as a number
	*						of neurons in the output layer.
	*/
    void backPropagation(std::vector<double> &targetValues);

private:

    /**
    * Vector containing all layers defined for this neural network
    */
    std::vector<Layer> m_Layers;

    double m_Error;
    double m_RecentAverageError;
    double m_RecentAverageSmoothingFactor;
    double m_Eta;
    double m_Alpha;


};

#endif