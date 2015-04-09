#include "annbrain.h"
#include <QDebug>

const unsigned int layers[] = {18, 15, 15, 2};

ANNBrain::ANNBrain():
    _neuralNet()
{
    _neuralNet.create_standard_array(4,layers);
    _connections = new FANN::connection[_neuralNet.get_total_connections()];
    _neuralNet.randomize_weights(-10,10);

}

ANNBrain::~ANNBrain()
{

}

void ANNBrain::think(std::vector<float>& input, std::vector<float>& output){

    //Input, data from 6 sensors, 3 numbers in each sensor (red, green, blue) (0-255)
    //qDebug()<<input.at(0);

    qDebug()<<input.size();
    float *outputN;
    static int i=0;
    //qDebug()<<input[0];
    outputN = _neuralNet.run((fann_type*)&input[0]);
   // qDebug()<<_neuralNet.

    output.clear();
    output.push_back(outputN[0]*2-1);
    output.push_back(outputN[1]*2-1);

    //Output data to motors, 2 motors, 1 number for each motor (power  0-100(%))
}

void ANNBrain::updateGene(const std::vector<int>& gene){
    for(int i=0;i<_neuralNet.get_total_connections(); i++){
        _connections[i].weight = gene[i];
    }
    _neuralNet.set_weight_array(_connections, _neuralNet.get_total_connections());

}

std::vector<float> ANNBrain::gene() {

//    // Update connections array
//    _neuralNet.get_connection_array(_connections);

//    //Gene is represeneded as vector of floats representing connection wages
//    std::vector<float> gene = std::vector<float>(_neuralNet.get_total_connections());
//    for(int i=0; i< _neuralNet.get_total_connections(); i++){
//        gene[i] = _connections[i]->weight;
//    }

}
