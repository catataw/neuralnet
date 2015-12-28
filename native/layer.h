#ifndef LAYER_H
#define LAYER_H

#include "neuron.h"
#include "weight.h"
#include <vector>
#include <map>

class Layer {
public:
    Layer(unsigned numberOfNeurons);
    Layer(unsigned numberOfNeurons, Layer& previousLayer);
    ~Layer() {}

    void setValues(std::vector<double> &values);
    void getValues(std::vector<double> &values, bool bias = true);
    unsigned getNeuronCount();
    void feedForward(Layer& sourceLayer);
    void calculateGradients(std::vector<double> &values, std::vector<double> &vectors);
    void calculateGradients(Layer &nextLayer, std::vector<double> &nextLayerGradients, std::vector<double> &vectors);
    void getWeights(unsigned sourceNeuronIdx, std::vector<double>& weights);
    void getWeights(unsigned sourceNeuronIdx, std::vector<Weight*>& weights);
    void updateInputWeights(Layer &previousLayer, double eta, double alpha, std::vector<double> &gradients);
private:
    std::vector<Neuron> m_Neurons;
    std::map<unsigned, std::vector<Weight>> m_Weights;
};

#endif