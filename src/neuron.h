#ifndef NEURON_H
#define NEURON_H

#include "connection.h"
#include <vector>

/**
* Prototype of neuron class
*/
class Neuron;

#ifdef _BOX_CLASS_NAME 
#undef _BOX_CLASS_NAME
#endif

#define _BOX_CLASS_NAME Neuron
#include "prop.h"

/**
* Class describing a single neuron in the network
*
* @author Marek Magdziak
*/
class Neuron {
public:

	/**
	* Contructor for the neuron class
	*
	* @param index	Index of this particular neuron in a layer
	*/
    Neuron(unsigned index);

	/**
	* The copy constructor for the neuron class
	*
	* @param neuron	The source 
	*/
	Neuron(const Neuron& neuron);

	/**
	* Destructor cleaning up all resources
	*/
    ~Neuron() { }

	/**
	* Calculates the neuron output value based on the values from previous layer and connections towards it
	*
	* @param values			Vector of doubles containing values from the previous layer in the network
	*
	* @param connections	Vector containing all connections towards a previous layer for this neuron
	*/
    void calculateOutputValue(std::vector<double> &values, std::vector<Connection> &connections);

	/**
	* The activation or transfer function. For this neuron we're using approximated sigmoid function
	*
	* @param x	Value in double which should go through the activation function
	* @returns	Result of a sigmoid function for the input parameter
	*/
    double transferFunction(double x);

	/**
	* The derivative of an activation or transfer function. 
	* For this neuron we're using approximated sigmoid function
	*
	* @param x	Value in double which should go through the derivative of an activation function
	* @returns	Result of a derivative of a sigmoid function for the input parameter
	*/
    double transferFunctionDerivative(double x);

	/**
	* Gets or sets the gradient for this neuron
	*/
	PROP<double> Gradient;

	/**
	* Gets or sets the output value for this neuron
	*/
	PROP<double> Value;

	/**
	* Gets or sets the neuron order index in a layer
	*/
	PROP<unsigned> Index;
private:
    double m_Value;
	double m_Gradient;
    unsigned m_MyIndex;

	void _setGradient(const double gradient);
	const double _getGradient();
	void _setValue(const double outputValue);
	const double _getValue();
	void _setIndex(const unsigned outputValue);
	const unsigned _getIndex();

	void initProperties();
};

#endif