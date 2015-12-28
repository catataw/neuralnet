#include "layer.h"

Layer::Layer(unsigned numberOfNeurons) {

    for (unsigned i = 0; i < numberOfNeurons; i++) {
        this->m_Neurons.push_back(Neuron(i));
    }

    this->m_Neurons.push_back(Neuron(numberOfNeurons)); // + one neuron to be a bias neuron
    Neuron& biasNeuron = this->m_Neurons.back();
    biasNeuron.setOutputValue(1.0); //set bias value to be one
}

Layer::Layer(unsigned numberOfNeurons, Layer& previousLayer) : Layer(numberOfNeurons) {

    for (unsigned i = 0; i < numberOfNeurons; i++) {
        unsigned numberOfNeuronsInPreviousLayer = previousLayer.getNeuronCount();
        for (unsigned y = 0; y < numberOfNeuronsInPreviousLayer; y++) {
            this->m_Weights[i].push_back(Weight(y));

            double weight = ((double) rand() / (RAND_MAX)) + 1;

            this->m_Weights[i].back().setValue(weight);
        }
    }
}

void Layer::setValues(std::vector<double> &values) {

    //if the value size isn't equal to the neuron size don't do a thing
    if (values.size() != this->m_Neurons.size() - 1) {
        throw "The number of neurons aren't matching the number of values.";
    }

    for (unsigned i = 0; i < values.size(); i++) {
        this->m_Neurons[i].setOutputValue(values[i]);
    }
}


void Layer::getValues(std::vector<double> &values, bool bias) {

    values.clear();

    unsigned count = bias ? m_Neurons.size() : m_Neurons.size() - 1;

    for (unsigned i = 0; i < count; i++) {
        values.push_back(this->m_Neurons[i].getOutputValue());
    }
}

unsigned Layer::getNeuronCount() {
    return (unsigned)this->m_Neurons.size();
}

void Layer::feedForward(Layer& sourceLayer) {

    std::vector<double> previousValues;
    sourceLayer.getValues(previousValues);

    for (unsigned i = 0; i < this->m_Neurons.size() - 1; i++) { // ignore the last bias neuron
        std::vector<Weight> &weights = this->m_Weights[i];

        this->m_Neurons[i].calculateOutputValue(previousValues, weights);
    }
}