#include "layer.h"

Layer::Layer(unsigned numberOfNeurons) {

    for (unsigned i = 0; i < numberOfNeurons; i++) {
        this->m_Neurons.push_back(Neuron(i));
    }

    this->m_Neurons.push_back(Neuron(numberOfNeurons)); // + one neuron to be a bias neuron
    Neuron& biasNeuron = this->m_Neurons.back();
    biasNeuron.setOutputValue(1.0); //set bias value to be one
}

void Layer::getWeights(unsigned sourceNeuronIdx, std::vector<double>& weights) {
    for (unsigned i = 0; i < this->m_Weights.size(); i++) {
        for (unsigned y = 0; y < this->m_Weights[i].size(); y++) {
           if (this->m_Weights[i][y].getSourceNeuronIndex() == sourceNeuronIdx) {
                weights.push_back(this->m_Weights[i][y].getValue());
           }
       }
    }
}

void Layer::getWeights(unsigned sourceNeuronIdx, std::vector<Weight*>& weights) {
    for (unsigned i = 0; i < this->m_Weights.size(); i++) {
        for (unsigned y = 0; y < this->m_Weights[i].size(); y++) {
           if (this->m_Weights[i][y].getSourceNeuronIndex() == sourceNeuronIdx) {
                weights.push_back(&(this->m_Weights[i][y]));
           }
       }
    }
}

Layer::Layer(unsigned numberOfNeurons, Layer& previousLayer) : Layer(numberOfNeurons) {

    for (unsigned i = 0; i < numberOfNeurons + 1; i++) {
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

    unsigned count = bias ? this->m_Neurons.size() : this->m_Neurons.size() - 1;

    for (unsigned i = 0; i < count; i++) {
        values.push_back(this->m_Neurons[i].getOutputValue());
    }
}

void Layer::calculateGradients(std::vector<double> &values, std::vector<double> &vectors) {
    for (unsigned i = 0; i < this->m_Neurons.size() - 1; i++) {
        double delta = values[i] - this->m_Neurons[i].getOutputValue();

        vectors.push_back(delta * this->m_Neurons[i].transferFunctionDerivative(this->m_Neurons[i].getOutputValue()));
    }
}

void Layer::calculateGradients(Layer &nextLayer, std::vector<double> &nextLayerGradients, std::vector<double> &vectors) {

    std::vector<double> dows;

    for (unsigned i = 0; i < this->m_Neurons.size(); i++) {
        std::vector<double> outputWeights;
        nextLayer.getWeights(i, outputWeights);

        double dow = 0.0;

        if (nextLayerGradients.size() > outputWeights.size()) {
            throw "The number of weights aren't corresponding with the number of input gradients.";
        }

        for (unsigned y = 0; y < nextLayerGradients.size(); y++) {
            dow += outputWeights[y] * nextLayerGradients[y];
        }

        dows.push_back(dow);
    }



    for (unsigned i = 0; i < this->m_Neurons.size() ; i++) {

        double delta = dows[i];

        vectors.push_back(delta * this->m_Neurons[i].transferFunctionDerivative(this->m_Neurons[i].getOutputValue()));
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

void Layer::updateInputWeights(Layer &previousLayer, double eta, double alpha, std::vector<double> &gradients) {
    std::vector<double> previousValues;

    previousLayer.getValues(previousValues);

    for (unsigned i = 0; i < this->m_Neurons.size(); i++) {

        Neuron& neuron = this->m_Neurons[i];

        std::vector<Weight>& weights = this->m_Weights[i];

        for (unsigned y = 0; y < previousValues.size(); y++) {

            double oldDelta = weights[y].getDelta();


            double newDelta =
                eta
                * previousValues[y]
                * gradients[i]
                + alpha
                * oldDelta;

            weights[y].setDelta(newDelta);
            weights[y].setValue(weights[y].getValue() + newDelta);
        }
    }
}