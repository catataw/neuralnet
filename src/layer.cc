#include "layer.h"

/**
* After adding all of the desired neurons adds one additional bias neuron
* and sets its value to 1.0 this value shouldn't be changed during feed forward
*/
Layer::Layer(unsigned numberOfNeurons) 
{

    for (unsigned i = 0; i <= numberOfNeurons; i++) {
		this->m_Neurons.push_back(Neuron(i));
    }

    Neuron& biasNeuron = this->m_Neurons.back();
    biasNeuron.Value(1.0); //set bias value to be one
}

/**
* Inheriting functionality from Layer::Layer(unsigned numberOfNeurons)
*
* based on the information obtained from the previous layer this constructor also creates
* connections between these two layers and randomly assigns weights as a random value between 0.0 and 1.0
*/
Layer::Layer(unsigned numberOfNeurons, Layer& previousLayer) : Layer(numberOfNeurons) {

	for (unsigned i = 0; i < numberOfNeurons; i++) {
		unsigned numberOfNeuronsInPreviousLayer = previousLayer.getNeuronCount();

		this->m_InputWeights.push_back(std::vector<Connection>());

		for (unsigned y = 0; y < numberOfNeuronsInPreviousLayer; y++) {
			this->m_InputWeights[i].push_back(Connection(y));

			double weight = ((double)rand() / (RAND_MAX)); //Between 0.0 and 1.0

			this->m_InputWeights[i][y].Weight(weight);
			this->m_InputWeights[i][y].Delta(0);
		}
	}
}

/**
* If the neuron count and the input value count matches iterates through all the passed values
* and using the setOutputValue method in each neuron assigns the desired value to each neuron in the layer.
*/
void Layer::setValues(std::vector<double> &values) {

	//if the value size isn't equal to the neuron size don't do a thing
	if (values.size() != this->m_Neurons.size() - 1) { 
		//size() -1 because of the bias neuron. We can't set value to that one
		throw "The number of neurons aren't matching the number of values.";
	}

	for (unsigned i = 0; i < values.size(); i++) {
		this->m_Neurons[i].Value(values[i]);
	}
}

/**
* The bias neuron is always the last one.
* So always for getting all values with the bias neuron the full size is taken
* When getting neurons without the bias neuron we can just take all neurons except the last one
*/
void Layer::getValues(std::vector<double> &values, bool bias) {

	values.clear();

	unsigned count = bias ? (unsigned)this->m_Neurons.size() : (unsigned)this->m_Neurons.size() - 1;

	for (unsigned i = 0; i < count; i++) {
		values.push_back(this->m_Neurons[i].Value());
	}
}

unsigned Layer::getNeuronCount() {
	return (unsigned)this->m_Neurons.size();
}

/**
* The feed forward calculation logic is located in the Neuron class 
* here we're just calling that logic for each neuron
*/
void Layer::feedForward(Layer& sourceLayer) {

	std::vector<double> previousValues;
	sourceLayer.getValues(previousValues);

	for (unsigned i = 0; i < this->m_Neurons.size() - 1; i++) { // ignore the last bias neuron
		std::vector<Connection> &weights = this->m_InputWeights[i];

		this->m_Neurons[i].calculateOutputValue(previousValues, weights);
	}
}

/**
* This method is used for the output layer gradient calculation.
*
* Following these equasions:
*
* delta = desired_value - real_output_value
* gradient = delta * transfer_foo_derivative(real_output_value)
*/
void Layer::calculateGradients(std::vector<double> &values, bool bias) {

	unsigned count = bias ? (unsigned)this->m_Neurons.size() : (unsigned)this->m_Neurons.size() - 1;

	for (unsigned i = 0; i < count; i++) {

		double delta = values[i] - this->m_Neurons[i].Value();

		this->m_Neurons[i].Gradient(
			delta 
			* this->m_Neurons[i].transferFunctionDerivative(this->m_Neurons[i].Value()));
	}
}

/**
* This method is used for calculating gradients for all the hidden layers
* For each neuron in the hidden layer:
*	Calculates the contribution on error by doing a 
*	SUM of multiplications between output weight and the next layers value
*	Then it takes that sum and multiplies it by the transfer function derivate and that's saved
*	as current neuron gradient
*/
void Layer::calculateGradients(Layer &nextLayer) {

	for (unsigned i = 0; i < this->m_Neurons.size(); i++) {
		std::vector<double> outputWeights;
		nextLayer.getWeights(i, outputWeights);

		double dow = 0.0;

		for (unsigned y = 0; y < outputWeights.size(); y++) {
			dow += outputWeights[y] * nextLayer.m_Neurons[y].Gradient();
		}

		this->m_Neurons[i].Gradient(
			dow 
			* this->m_Neurons[i].transferFunctionDerivative(this->m_Neurons[i].Value()));
	}
}

void Layer::getWeights(unsigned sourceNeuronIdx, std::vector<double>& weights) {
    for (unsigned i = 0; i < this->m_InputWeights.size(); i++) {
		weights.push_back(this->m_InputWeights[i][sourceNeuronIdx].Weight());
    }
}

void Layer::getWeights(unsigned sourceNeuronIdx, std::vector<Connection*>& weights) {
    for (unsigned i = 0; i < this->m_InputWeights.size(); i++) {
		weights.push_back(&this->m_InputWeights[i][sourceNeuronIdx]);
    }
}

void Layer::updateInputWeights(Layer &previousLayer, double eta, double alpha) {
    for (unsigned i = 0; i < this->m_Neurons.size() - 1; i++) { 
		//ignore the bias neuron no connections are going to the bias neuron

        Neuron& neuron = this->m_Neurons[i];

        std::vector<Connection>& weights = this->m_InputWeights[i];

        for (unsigned y = 0; y < previousLayer.getNeuronCount(); y++) {

            double oldDelta = weights[y].Delta();

            double newDelta =
                eta
                * previousLayer.getNeuron(y).Value()
                * neuron.Gradient()
                + alpha
                * oldDelta;

            weights[y].Delta(newDelta);
            weights[y].Weight(weights[y].Weight() + newDelta);
        }
    }
}

Neuron& Layer::getNeuron(unsigned index) {
	return this->m_Neurons[index];
}