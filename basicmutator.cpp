#include "basicmutator.h"

#include "livingelement.h"
BasicMutator::BasicMutator()
{
}

void BasicMutator::mutate(const std::vector<LivingElement*>& animals, LivingElement* animal)
{
    //Not ready
    //animal->updateBehaviour(animals[0]->behaviourGene());
}

void BasicMutator::mutate(std::vector<float>& gene) const
{

}

std::vector<float> BasicMutator::crossover(const std::vector<float>& geneOne, const std::vector<float>& geneTwo) const
{

}
