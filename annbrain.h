#ifndef ANNBRAIN_H
#define ANNBRAIN_H


#include "brain.h"

class ANNBrain : public Brain
{
public:
    ANNBrain();

    virtual void think(std::vector<float>& input, std::vector<float>& output);

    virtual std::vector<float> gene() const;
    virtual void updateGene(const std::vector<float>& gene);

};

#endif // ANNBRAIN_H
