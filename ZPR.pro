TEMPLATE = app

QT += qml quick widgets


CONFIG += c++11

LIBS += -lfann
SOURCES += main.cpp \
    element.cpp \
    livingelement.cpp \
    planteater.cpp \
    meateater.cpp \
    plantelement.cpp \
    brain.cpp \
    annbrain.cpp \
    map.cpp \
    simulation.cpp \
    mutator.cpp \
    basicmutator.cpp \
    physicsengine.cpp \
    simplephysicsengine.cpp \
    logger.cpp \
    mapview.cpp \
    animalnode.cpp \
    shader.cpp \
    foodnode.cpp \
    basenode.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    element.h \
    livingelement.h \
    planteater.h \
    meateater.h \
    plantelement.h \
    brain.h \
    annbrain.h \
    map.h \
    simulation.h \
    mutator.h \
    basicmutator.h \
    physicsengine.h \
    simplephysicsengine.h \
    logger.h \
    mapview.h \
    animalnode.h \
    shader.h \
    foodnode.h \
    basenode.h
