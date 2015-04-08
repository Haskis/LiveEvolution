#include "annbrain.h"
#include <QDebug>
ANNBrain::ANNBrain()
{
}

void ANNBrain::think(std::vector<float>& input, std::vector<float>& output){

    //Input, data from 6 sensors, 3 numbers in each sensor (red, green, blue) (0-255)
    //qDebug()<<input.at(0);

    if(input.at(0>0)){
        output.push_back(-0.2);
        output.push_back(0.5);
    }
    else{
        output.push_back(0.5);
        output.push_back(0.5);

    }
    //Output data to motors, 2 motors, 1 number for each motor (power  0-100(%))
}

void ANNBrain::updateGene(const std::vector<int>& gene){

}

std::vector<float> ANNBrain::gene() const{

}
