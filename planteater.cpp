#include "planteater.h"

PlantEater::PlantEater(Brain *brain):
    LivingElement(brain)
{
}

void PlantEater::checkoutEnviroment(Map& map)
{

}

void PlantEater::reactToEnviroment()
{

}

std::vector<float> PlantEater::structoreGene() const
{

}

std::vector<float> PlantEater::behaviourGene() const
{

}

void PlantEater::updateStructure(const std::vector<float>& gene)
{

}

void PlantEater::updateBehaviour(const std::vector<float>* gene)
{

}

void PlantEater::handleIntersection(Element* e)
{

}

void PlantEater::handleIntersection(MeatEater* e)
{

}

void PlantEater::handleIntersection(PlantElement* e)
{

}

void PlantEater::handleIntersection(PlantEater* e)
{

}
