#ifndef NEURON_H
#define NEURON_H

#include "weight.h"
#include <vector>

class Neuron {
public:
    Neuron(unsigned index);
    ~Neuron() {}

    void setOutputValue(double outputValue);
    double getOutputValue();
    void calculateOutputValue(std::vector<double> &values, std::vector<Weight> &weights);
private:
    double m_outputValue;
    unsigned m_myIndex;
};

#endif