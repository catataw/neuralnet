#include "weight.h"

Weight::Weight(unsigned sourceNeuronIndex) {
    this->m_SourceNeuronIndex = sourceNeuronIndex;
}

void Weight::setValue(double weight) {
    this->m_Value = weight;
}

double Weight::getValue() {
    return this->m_Value;
}

unsigned Weight::getSourceNeuronIndex() {
    return this->m_SourceNeuronIndex;
}

void Weight::setDelta(double delta) {
    this->m_Delta = delta;
}

double Weight::getDelta() {
    return this->m_Delta;
}