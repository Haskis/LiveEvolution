#include "simulation.h"

#include "livingelement.h"
#include "population.h"
#include "map.h"

Simulation::Simulation(Map* map, Mutator *mutator, PhysicsEngine* engine)
{
}

void Simulation::start()
{

}

void Simulation::stop()
{

}

void Simulation::setStepInterval(int ms)
{

}

void Simulation::evolveAnimals()
{

}

void Simulation::setNewPhysicsEngine(PhysicsEngine* engine)
{

}

void Simulation::setNewMutator(Mutator* mutator)
{

}

void Simulation::setNewMap(Map* map)
{

}

void Simulation::goOneStep()
{
    const std::vector<LivingElement*> animals = _map->getAnimalElemensts();

    //Population is not ready to evolve, continue
    if(!populationReady()){
        //For each animal let him checkout this enviroment and update sensors
        for(LivingElement* animal: animals){
            animal->checkoutEnviroment(*_map);
        }

        //For each animal let him set outputs according to his sensors
        for(LivingElement* animal: animals){
            animal->reactToEnviroment();
        }

        //Update position and velocity of each LivingElement based on element outputs (motors)
        _pEngine->updateEnviroment(*_map);


    }
    //Population is ready to evolve
    else{
        //Log population info into file
        _map->logPopulation();


        //Mutate previous population
        Population* population =_mutator->mutate(animals);

        //Redistribute elements on the map
        for(LivingElement *animal: animals){
            animal->setRandomPosition(_map->boundingRect());
        }
        for(Element* food: _map->getFoodElements() ){
            food->setRandomPosition(_map->boundingRect());
        }
    }
}

bool Simulation::populationReady()
{

}
