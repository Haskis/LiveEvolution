#include "meateater.h"

MeatEater::MeatEater(Brain* brain):
    LivingElement(brain)
{
}

void MeatEater::checkoutEnviroment(Map& map)
{

}

void MeatEater::reactToEnviroment()
{

}

std::vector<float> MeatEater::structoreGene() const
{

}

std::vector<float> MeatEater::behaviourGene() const
{

}

void MeatEater::updateStructure(const std::vector<float>& gene)
{

}

void MeatEater::updateBehaviour(const std::vector<float>* gene)
{

}

void MeatEater::handleIntersection(PlantElement* e)
{
    e->handleIntersection(this);
}

void MeatEater::handleIntersection(PlantEater* e)
{

}

void MeatEater::handleIntersection(MeatEater* e)
{

}

void MeatEater::handleIntersection(Element* e)
{

}
