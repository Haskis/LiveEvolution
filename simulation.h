#ifndef SIMULATION_H
#define SIMULATION_H

#include <QObject>
#include <QTimer>

#include "map.h"
#include "basicmutator.h"
#include "simplephysicsengine.h"

///
/// \brief The Simulation class responsible for enviroment updates
///
/// This class enables to start and stop simulation. Function goOneStep
/// is called in some predefined time intervals to update enviroment and
/// population. Physics Engine object is used to update animals position on map
/// according to rules defined in it and according to animal currnet state.
/// When population is ready to evolve Mutator object is used to create new
/// population and whole cycle goes again.
///
///
class Simulation: public QObject
{
    Q_OBJECT

    Q_PROPERTY(int timePassed READ timePassed NOTIFY timePassedChanged)

public:

    ///
    /// \brief Simulation constructor must initialize internal objects
    /// \param map object with population and enviroment data
    /// \param mutator object used to evolve population
    /// \param engine object used to update position according to defined laws of physics
    ///
    explicit Simulation(Map *map, Mutator *mutator, PhysicsEngine* engine);
    ~Simulation();

    int timePassed();

public slots:
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

public:
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

private slots:

    ///
    /// \brief goOneStep update simulation by little amout of time
    ///
    /// This function is called by timer overflow when simulation is started. Elements position and
    /// internal state is updated
    ///
    void goOneStep();

signals:
    void upadate();

    void timePassedChanged(int timePassed);
private:

    Map *m_map;
    Mutator *m_mutator;
    PhysicsEngine* m_pEngine;
    QTimer m_timer;

    int m_timePassed;
};

#endif // SIMULATION_H
