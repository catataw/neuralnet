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
private:
    std::vector<Neuron> m_Neurons;
    std::map<unsigned, std::vector<Weight>> m_Weights;
};

#endif