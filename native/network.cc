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

    this->m_Alpha = 0.5;
    this->m_Eta = 0.2;
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

void Network::backPropagation(std::vector<double> &targetValues) {
    unsigned i;

    //Overall net error
    this->m_Error = 0.0;

    std::vector<double> outputValues;
    Layer& outputLayer = this->m_Layers.back();
    outputLayer.getValues(outputValues, false); //get output values without bias value

    for (i = 0; i < outputValues.size(); i++) {
        double delta = targetValues[i] - outputValues[i];
        this->m_Error += delta * delta;
    }

    this->m_Error /= outputValues.size();
    this->m_Error = sqrt(this->m_Error); //RMS (Root mean square)


    //printf("mError: %f \n", this->m_Error);

    //Recent average measurement
    this->m_RecentAverageError = (this->m_RecentAverageError * this->m_RecentAverageSmoothingFactor + this->m_Error )
                                    / (this->m_RecentAverageSmoothingFactor + 1);

    //Output layer gradients
    std::map<unsigned, std::vector<double>> gradients;
    outputLayer.calculateGradients(targetValues, gradients[this->m_Layers.size()-1]);

    //Calculate gradients on hidden layers
    for (i = this->m_Layers.size() - 2; i > 0; i--) {
        Layer& hiddenLayer = this->m_Layers[i];
        Layer& nextLayer = this->m_Layers[i+1];

        hiddenLayer.calculateGradients(nextLayer, gradients[i+1], gradients[i]);

    }


    //Update weights
    for (i = this->m_Layers.size() - 1; i > 0; i--) {
        Layer& hiddenLayer = this->m_Layers[i];
        Layer& previousLayer = this->m_Layers[i-1];

        hiddenLayer.updateInputWeights(previousLayer, this->m_Eta, this->m_Alpha, gradients[i]);
    }
}