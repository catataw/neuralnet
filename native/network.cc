#include "network.h"

Network::Network(std::vector<unsigned> &topology) {
    std::size_t numberOfLayers = topology.size();

    //The number of layers has to be at least three
    if (numberOfLayers < 3)
        throw "Network::Network: The number of layers has to be at least three!";

    this->m_Layers.push_back(Layer(topology[0]));

    //Iterate through the topology and create one layer after another
    for (unsigned i = 1; i < numberOfLayers; i++) {
        this->m_Layers.push_back(Layer(topology[i], this->m_Layers.back()));
    }
}

void Network::setInputValues(std::vector<double> &inputValues) {
    Layer& inputLayer = this->m_Layers.front();

    inputLayer.setValues(inputValues);
}

void Network::getValuesFromLayer(std::vector<double> &outputValues, unsigned index) {

    Layer& outputLayer = this->m_Layers[index];
    outputLayer.getValues(outputValues);
}

void Network::getOutputValues(std::vector<double> &outputValues) {

    for (unsigned i = 1; i < this->m_Layers.size(); i++) {
        this->m_Layers[i].feedForward(this->m_Layers[i-1]);
    }

    Layer& outputLayer = this->m_Layers.back();
    outputLayer.getValues(outputValues, false);
}