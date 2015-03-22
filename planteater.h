#ifndef PLANTEATER_H
#define PLANTEATER_H



#include "livingelement.h"
#include "element.h"
#include "meateater.h"
#include "planteater.h"
#include "plantelement.h"


class PlantEater : public LivingElement
{
public:
    PlantEater(Brain* brain);

    //Inherited from LivingElement
    virtual void checkoutEnviroment(Map& map);
    virtual void reactToEnviroment();
    std::vector<float> structoreGene() const;
    std::vector<float> behaviourGene() const;
    void updateStructure(const std::vector<float>& gene);
    void updateBehaviour(const std::vector<float>* gene);

protected:

    //Inherited from Element
    virtual void handleIntersection(Element *e);
    virtual void handleIntersection(MeatEater *e);
    virtual void handleIntersection(PlantEater *e);
    virtual void handleIntersection(PlantElement *e);
};

#endif // PLANTEATER_H
