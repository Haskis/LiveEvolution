#include "simulation.h"

#include "livingelement.h"
#include "plantelement.h"
#include "population.h"
#include "map.h"

Simulation::Simulation(Map* map, Mutator *mutator, PhysicsEngine* engine):
    QObject(nullptr),
    m_map(map),
    m_mutator(mutator),
    m_pEngine(engine),
    m_timePassed(0)
{
    m_timer.setInterval(10);
    connect(&m_timer,SIGNAL(timeout()),this,SLOT(goOneStep()));
    connect(this,SIGNAL(upadate()),this,SLOT(goOneStep()),Qt::QueuedConnection);
}

Simulation::~Simulation()
{
    delete m_map;
    delete m_mutator;
    delete m_pEngine;
}

int Simulation::timePassed(){
    return m_timePassed;
}
void Simulation::start(){
    m_timer.start();
}

void Simulation::stop(){
    m_timer.stop();
}

void Simulation::setStepInterval(int ms){
    m_timer.setInterval(ms);
}

void Simulation::setNewPhysicsEngine(PhysicsEngine* engine){
    m_pEngine = engine;
}

void Simulation::setNewMutator(Mutator* mutator){
    m_mutator = mutator;
}

void Simulation::setNewMap(Map* map){
    m_map = map;
}

void Simulation::goOneStep()
{
    const std::vector<LivingElement*> animals = m_map->getAnimalElemensts();

    //For each animal let him checkout this enviroment and update sensors
    for(LivingElement* animal: animals){
        animal->checkoutEnviroment(*m_map);
    }

    //For each animal let him set outputs according to his sensors
    for(LivingElement* animal: animals){
        animal->reactToEnviroment();
    }

    //Update position and velocity of each LivingElement based on element outputs (motors)
    m_pEngine->updateEnviroment(*m_map);

    //Delete dead animals, create new animals using mutator
    m_map->cleanDead(m_mutator);

    timePassedChanged(++m_timePassed);

    //To speed up begin phase
    //if(m_timePassed<100000)
        //emit upadate();
}
