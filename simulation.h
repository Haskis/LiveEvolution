#ifndef SIMULATION_H
#define SIMULATION_H

#include "map.h"

#include "basicmutator.h"
#include "simplephysicsengine.h"
#include <QTimer>

class Simulation
{
public:
    Simulation(Map *map, Mutator *mutator, PhysicsEngine* engine);

    ///
    /// \brief start starts simulation
    ///
    /// This function starts timer. On each timer interrupt goOneStep function in called
    void start();

    ///
    /// \brief stop stops simulation
    ///
    /// This function stops simulation timer. Simulation is paused and can be resumed by start()
    void stop();

    ///
    /// \brief setStepInterval function to set simulation speed
    /// \param ms time between intervals in milliseconds
    ///
    void setStepInterval(int ms);

    ///
    /// \brief evolveAnimals used to create new population from an old one
    ///
    /// If populationReady() returns true, then in means that population is ready to be evaluated and
    /// modified by Mutator. This function is used to create new population and switch it with an old one
    void evolveAnimals();

    ///
    /// \brief setNewPhysicsEngine set new physcis engine in a dynamic way
    /// \param engine pointer to new PhysicsEngine, class manages and destroys this object
    ///
    ///
    void setNewPhysicsEngine(PhysicsEngine* engine);

    ///
    /// \brief setNewMutator set new Mutator in a dynamic way
    /// \param mutator pointer to new Mutator, class manages and destroys this object
    ///
    void setNewMutator(Mutator *mutator);

    ///
    /// \brief setNewMap set new Map in a dynamic way
    /// \param map pointer to new Map, class manages and destroys this object
    ///
    void setNewMap(Map* map);

public slots:

    ///
    /// \brief goOneStep update simulation by little amout of time
    ///
    /// This function is called by timer overflow when simulation is started. Elements position and
    /// internal state is updated. If population is ready evolveAnimals function is called
    ///
    void goOneStep();

protected:

    ///
    /// \brief populationReady checks if population is ready to evolve
    /// \return true if population is ready to evolve
    ///
    /// Population is ready to evolve if some condtion is fulfilled, eg. all LivingElements died
    bool populationReady();

private:

    Map *_map;
    Mutator *_mutator;
    PhysicsEngine* _pEngine;
    QTimer _timer;
};

#endif // SIMULATION_H