#ifndef WEIGHT_H
#define WEIGHT_H

class Weight {
public:
    Weight(unsigned sourceNeuronIndex);
    ~Weight() {};

    void setValue(double weight);
    double getValue();
    void setDelta(double delta);
    double getDelta();
    unsigned getSourceNeuronIndex();
private:
    double m_Value;
    double m_Delta;
    unsigned m_SourceNeuronIndex;
};

#endif