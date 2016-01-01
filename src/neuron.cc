#include "neuron.h"

Neuron::Neuron(const Neuron& neuron) 
	:	m_Value(neuron.m_Value),
		m_Gradient(neuron.m_Gradient),
		m_MyIndex(neuron.m_MyIndex)
{

	this->initProperties();
}

Neuron::Neuron(unsigned index) : m_MyIndex(index) {

	this->initProperties();
}

void Neuron::initProperties() {
	this->Gradient.set(&Neuron::_setGradient, this);
	this->Gradient.get(&Neuron::_getGradient, this);
	this->Value.set(&Neuron::_setValue, this);
	this->Value.get(&Neuron::_getValue, this);
	this->Index.set(&Neuron::_setIndex, this);
	this->Index.get(&Neuron::_getIndex, this);
}

double Neuron::transferFunction(double x)
{
	if (x < -45.0) return 0.0;
	else if (x > 45.0) return 1.0;
	else return 1.0 / (1.0 + exp(-x));
}

double Neuron::transferFunctionDerivative(double x)
{
    return ( 1.0 - x) * x;
}

void Neuron::calculateOutputValue(std::vector<double> &values, std::vector<Connection> &weights){

    double sum = 0.0;

    for (unsigned i = 0; i < weights.size(); i++) {
        unsigned neuronIdx = weights[i].SourceNeuronIndex();

        sum += weights[i].Weight() * values[neuronIdx];
    }

    this->m_Value = transferFunction(sum);
}

void Neuron::_setGradient(const double gradient) {
	this->m_Gradient = gradient;
}

const double Neuron::_getGradient() {
	return this->m_Gradient;
}

void Neuron::_setValue(const double outputValue) {
	this->m_Value = outputValue;
}

const double Neuron::_getValue() {
	return this->m_Value;
}

void Neuron::_setIndex(const unsigned outputValue) {
	this->m_MyIndex = outputValue;
}

const unsigned Neuron::_getIndex() {
	return this->m_MyIndex;
}