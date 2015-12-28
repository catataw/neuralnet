#include "neuron.h"

double transferFunction(double x) {
    return x / (1 + abs(x));
}

Neuron::Neuron(unsigned index) {
    this->m_myIndex = index;
}

void Neuron::setOutputValue(double outputValue) {
    this->m_outputValue = outputValue;
}

double Neuron::getOutputValue() {
    return this->m_outputValue;
}

void Neuron::calculateOutputValue(std::vector<double> &values, std::vector<Weight> &weights){

    double sum = 0.0;

    for (unsigned i = 0; i < weights.size(); i++) {
        unsigned neuronIdx = weights[i].getSourceNeuronIndex();

        sum += weights[i].getValue() * values[neuronIdx];
    }

    this->m_outputValue = transferFunction(sum);
}