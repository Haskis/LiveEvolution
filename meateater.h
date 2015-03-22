#ifndef MEATEATER_H
#define MEATEATER_H

#include "livingelement.h"
#include "element.h"
#include "meateater.h"
#include "planteater.h"
#include "plantelement.h"

class MeatEater : public LivingElement
{
public:

    MeatEater(Brain* brain);


    //Inherited from LivingElement
    virtual void checkoutEnviroment(Map& map);
    virtual void reactToEnviroment();
    std::vector<float> structoreGene() const;
    std::vector<float> behaviourGene() const;
    void updateStructure(const std::vector<float>& gene);
    void updateBehaviour(const std::vector<float>* gene);

    //Inherited from Element
    virtual void handleIntersection(Element *e);
    virtual void handleIntersection(MeatEater *e);
    virtual void handleIntersection(PlantEater *e);
    virtual void handleIntersection(PlantElement *e);

};

#endif // MEATEATER_H
