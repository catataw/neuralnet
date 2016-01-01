#ifndef WEIGHT_H
#define WEIGHT_H

/**
* Prototype of connection class
*/
class Connection;

#ifdef _BOX_CLASS_NAME 
#undef _BOX_CLASS_NAME
#endif

#define _BOX_CLASS_NAME Connection
#include "prop.h"


/**
* Class describing connection between two neurons in two different layers in the network
*
* @author Marek Magdziak
*/
class Connection {
public:

	/**
	* Creates a Connection instance with a sourceNeuronIndex
	*
	* @param sourceNeuronIndex	Unsigned integer pointing to an index of a source neuron for this connection
	*/
	Connection(unsigned sourceNeuronIndex);

	/**
	* Copy constructor for the Connection class
	*
	* @param connection	Reference to the original instance
	*/
	Connection(const Connection& connection);

	/**
	* Destructor cleaning up all resources
	*/
    ~Connection() { };

	/**
	* Gets or sets the weight for this connection
	*/
	PROP<double> Weight;

	/**
	* Gets or sets the delta for this connection
	*/
	PROP<double> Delta;

	/**
	* Gets or sets the source neuron index for this connection
	*/
	PROP<unsigned> SourceNeuronIndex;

private:
    double m_Weight;
    double m_Delta;
    unsigned m_SourceNeuronIndex;

	double const _getWeight();
	void _setWeight(double const value);
	double const _getDelta();
	void _setDelta(double const value);
	unsigned const _getSourceNeuronIndex();
    void _setSourceNeuronIndex(unsigned const value);

	void initProperties();
};

#endif