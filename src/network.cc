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

	this->m_Alpha = 0.7;
	this->m_Eta = 0.05;
}

void Network::setInputValues(std::vector<double> &inputValues) {
	Layer& inputLayer = this->m_Layers.front();

	inputLayer.setValues(inputValues);
}

void Network::getOutputValues(std::vector<double> &outputValues) {

	for (unsigned i = 1; i < this->m_Layers.size(); i++) {
		this->m_Layers[i].feedForward(this->m_Layers[i - 1]);
	}

	Layer& outputLayer = this->m_Layers.back();
	outputLayer.getValues(outputValues, false);
}

void Network::getValuesFromLayer(std::vector<double> &outputValues, unsigned index) {

	Layer& outputLayer = this->m_Layers[index];
	outputLayer.getValues(outputValues);
}

void Network::backPropagation(std::vector<double> &targetValues) {
	unsigned i;

	//Overall net error
	this->m_Error = 0.0;

	Layer& outputLayer = this->m_Layers.back();

	for (i = 0; i <  outputLayer.getNeuronCount() -1; i++) {
		double delta = targetValues[i] - outputLayer.getNeuron(i).Value();
		this->m_Error += delta * delta;
	}

	this->m_Error /= outputLayer.getNeuronCount();
	this->m_Error = sqrt(this->m_Error); //RMS (Root mean square)

	//Recent average measurement
	this->m_RecentAverageError = (this->m_RecentAverageError * this->m_RecentAverageSmoothingFactor + this->m_Error)
		/ (this->m_RecentAverageSmoothingFactor + 1);

	//Output layer gradients
	outputLayer.calculateGradients(targetValues);

	//Calculate gradients on hidden layers
	for (i = (unsigned)this->m_Layers.size() - 2; i > 0; i--) {
		Layer& hiddenLayer = this->m_Layers[i];
		Layer& nextLayer = this->m_Layers[i + 1];

		hiddenLayer.calculateGradients(nextLayer);

	}

	//Update weights
	for (i = (unsigned)this->m_Layers.size() - 1; i > 0; i--) {
		Layer& hiddenLayer = this->m_Layers[i];
		Layer& previousLayer = this->m_Layers[i - 1];

		hiddenLayer.updateInputWeights(previousLayer, this->m_Eta, this->m_Alpha);
	}
}