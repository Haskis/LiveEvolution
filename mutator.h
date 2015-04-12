#ifndef MUTATOR_H
#define MUTATOR_H

#include <vector>

class LivingElement;

class Mutator
{
public:
    Mutator();
    virtual ~Mutator();

    // Update gene of animal based on population in animals vector
    virtual void mutate(const std::vector<LivingElement*>& animals, LivingElement* animal) = 0;

protected:
    virtual std::vector<float> crossover(const std::vector<float>& geneOne, const std::vector<float>& geneTwo) const = 0;
    virtual void mutate(std::vector<float>& gene ) const = 0;
};

#endif // MUTATOR_H
