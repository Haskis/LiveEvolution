#ifndef ANNBRAIN_H
#define ANNBRAIN_H

#include <floatfann.h>

#include <fann_cpp.h>
#include "brain.h"

class ANNBrain : public Brain
{
public:
    ANNBrain();
    virtual ~ANNBrain();

    virtual void think(std::vector<float>& input, std::vector<float>& output);

    virtual std::vector<float> gene();
    virtual void updateGene(const std::vector<int>& gene);


private:
    FANN::neural_net _neuralNet;
    FANN::connection *_connections;
};

#endif // ANNBRAIN_H
