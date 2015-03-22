#ifndef BASICMUTATOR_H
#define BASICMUTATOR_H

#include "mutator.h"
class BasicMutator : public Mutator
{
public:
    BasicMutator();

    //Set some params
    // ...()


    virtual Population* mutate(const std::vector<LivingElement*>& animals);

    virtual std::vector<float> crossover(const std::vector<float>& geneOne, const std::vector<float>& geneTwo) const;
    virtual void mutate(std::vector<float>& gene ) const;

};

#endif // BASICMUTATOR_H
