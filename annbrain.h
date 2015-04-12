#ifndef ANNBRAIN_H
#define ANNBRAIN_H

#include <floatfann.h>
#include <fann_cpp.h>

#include "brain.h"

///
/// \brief The ANNBrain class implements brain using artificial neural networks
///
/// Neural networks are provided by FANN library, Neural network have static structure.
/// Weights of connection between network nodes can be changed using updateGene function
///
class ANNBrain : public Brain
{
public:
    explicit ANNBrain();
    virtual ~ANNBrain();

    virtual void think(std::vector<float>& input, std::vector<float>& output);

    ///
    /// \brief gene
    /// \return array of floats representing connections weights
    ///
    virtual const std::vector<float>& gene() const;

    ///
    /// \brief updateGene updates connections in neural network using gene array
    ///
    /// \param gene
    ///
    virtual void updateGene(const std::vector<float>& gene);

private:
    FANN::neural_net m_neuralNet;

    //Life time managed by ANNBrain
    FANN::connection* m_connections;

    std::vector<float> m_gene;
};

#endif // ANNBRAIN_H
