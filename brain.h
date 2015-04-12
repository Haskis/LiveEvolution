#ifndef BRAIN_H
#define BRAIN_H

#include <vector>

class Brain
{
public:
    explicit Brain();
    virtual ~Brain();

    virtual void think(std::vector<float>& input, std::vector<float>& output) = 0;

    virtual const std::vector<float>& gene() const = 0;

    virtual void updateGene(const std::vector<float>& gene) = 0;
};

#endif // BRAIN_H
