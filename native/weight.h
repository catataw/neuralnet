#ifndef WEIGHT_H
#define WEIGHT_H

class Weight {
public:
    Weight(unsigned sourceNeuronIndex);
    ~Weight() {};

    void setValue(double weight);
    double getValue();
    unsigned getSourceNeuronIndex();
private:
    double m_Value;
    unsigned m_SourceNeuronIndex;
};

#endif