#ifndef MUTATOR_H
#define MUTATOR_H

#include <vector>
class LivingElement;
class Population;
class Mutator
{
public:
    Mutator();

    virtual Population* mutate(const std::vector<LivingElement*>& animals) = 0;

    virtual std::vector<float> crossover(const std::vector<float>& geneOne, const std::vector<float>& geneTwo) const = 0;
    virtual void mutate(std::vector<float>& gene ) const = 0;
};

#endif // MUTATOR_H
