#include "annbrain.h"

#include <assert.h>

//Predefined neural network structure
const unsigned int layers[] = {18, 15, 15, 2};

ANNBrain::ANNBrain():
    m_neuralNet()
{
    m_neuralNet.create_standard_array(4,layers);
    m_neuralNet.randomize_weights(-10,10);

    m_connections = new FANN::connection[m_neuralNet.get_total_connections()];

    m_neuralNet.get_connection_array(m_connections);

    //Update gene vector from wages in neural network
    m_gene.resize(m_neuralNet.get_total_connections());
    for(unsigned int i=0; i<m_neuralNet.get_total_connections(); i++){
        m_gene[i] = m_connections[i].weight;
    }
}

ANNBrain::~ANNBrain()
{
    delete m_connections;
}

void ANNBrain::think(std::vector<float>& input, std::vector<float>& output){

    //Input, data from 6 sensors, 3 numbers in each sensor (red, green, blue) (0-255)

    float *outputN;
    outputN = m_neuralNet.run((fann_type*)&input[0]);


    //Output data to motors, 2 motors, 1 number for each motor (power  -100:100( in %))
    output.clear();
    output.push_back(outputN[0]*2-1);
    output.push_back(outputN[1]*2-1);
}

void ANNBrain::updateGene(const std::vector<float>& gene){

    assert(gene.size() == m_gene.size());

    m_gene = std::vector<float>(gene);

    for(unsigned int i=0;i<m_neuralNet.get_total_connections(); i++){
        m_connections[i].weight = gene[i];
    }
    m_neuralNet.set_weight_array(m_connections, m_neuralNet.get_total_connections());
}

const std::vector<float>& ANNBrain::gene() const {
    return m_gene;
}
