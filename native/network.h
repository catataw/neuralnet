#ifndef NETWORK_H
#define NETWORK_H

#include "Layer.h"
#include <vector>

/**
* Network class describes the neural netowrk overlay
*/
class Network {
public:
    /**
    * Contructor for the neural network class
    * @param topology Vector of unsigned integers describing the number of neurons in a different layers
    *                 the minimum amount of layers is three - input layer, hidden layer, output layer
    */
    Network(std::vector<unsigned> &topology);

    /**
    * Destructor cleaning up all resources
    */
    ~Network() {}

    void setInputValues(std::vector<double> &inputValue);
    void getOutputValues(std::vector<double> &outputValues);
    void getValuesFromLayer(std::vector<double> &outputValues, unsigned index);
    void backPropagation(std::vector<double> &targetValues);
private:
    /**
    * Vector containing all layers defined for this neural network
    */
    std::vector<Layer> m_Layers;
    double m_Error;
    double m_RecentAverageError;
    double m_RecentAverageSmoothingFactor;
    double m_Eta;
    double m_Alpha;
};

#endif