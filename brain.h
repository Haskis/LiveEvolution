#ifndef BRAIN_H
#define BRAIN_H


#include "vector"
class Brain
{
public:
    Brain();

    virtual void think(std::vector<float>& input, std::vector<float>& output) = 0;

    virtual std::vector<float> gene() const = 0;
    virtual void updateGene(const std::vector<float>& gene) = 0;

private:
    //Brainstructure

};

#endif // BRAIN_H
