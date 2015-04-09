#include "simulation.h"

#include "livingelement.h"
#include "plantelement.h"
#include "population.h"
#include "map.h"

Simulation::Simulation(Map* map, Mutator *mutator, PhysicsEngine* engine):
    QObject(nullptr),
    _map(map),
    _mutator(mutator),
    _pEngine(engine)
{
    _timer.setInterval(10);
    connect(&_timer,SIGNAL(timeout()),this,SLOT(goOneStep()));
    connect(this,SIGNAL(upadate()),this,SLOT(goOneStep()),Qt::QueuedConnection);
}

Simulation::~Simulation()
{

}

void Simulation::start()
{
    _timer.start();
}

void Simulation::stop()
{
    _timer.stop();
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

        //Move dead animals to other container
        _map->cleanDead();
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
        for(PlantElement* food: _map->getFoodElements() ){
            food->setRandomPosition(_map->boundingRect());
        }
    }
    //emit upadate();
}

bool Simulation::populationReady(){
    return false;
}
