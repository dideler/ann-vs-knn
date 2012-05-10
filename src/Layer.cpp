/* 
 * File:   Layer.cpp
 * Author: Dennis Ideler <di07ty at brocku.ca>
 * 
 * Created on April 2011
 */

#include "Layer.h"
#include "Neurode.h"

Layer::Layer(const int num_neurodes) : size_(num_neurodes) // Constructor initializer list
{
  nodes_ = new Neurode[size_];
}

Layer::Layer(const Layer& orig)
{
  size_ = orig.size_;
  nodes_ = new Neurode[size_];
  for (int i = 0; i < size_; ++i)
    nodes_[i] = orig.nodes_[i];
}

Layer::~Layer() { delete[] nodes_; }

/**
 * Creates a weight layer by initializing all weighted connections to all nodes
 * in the current layer (within a certain weight range).
 * Example use: calling this function on the first hidden layer will create the
 * weighted connections coming to that layer from the input layer.
 * 
 * @param num_connections   The number of incoming connections to each node
 * @param kLowerRange       The lower weight range
 * @param kUpperRange       The upper weight range
 */
void Layer::initWeightLayer(const int num_connections, const double kLowerRange,
                            const double kUpperRange)
{
  for (int i = 0; i < size_; ++i)
    nodes_[i].initConnections(num_connections, kLowerRange, kUpperRange);
}

/**
 * Layer activation is part of the forward propagation phase. Only hidden and
 * output layers should be activated. Every node in the layer is activated by
 * calling its respective activation function. The inputs are the outputs from
 * the previous layer.
 *
 * @param previous_layer       The preceding layer in the network's architecture
 * @param activation function  The activation function to use on the nodes
 */
void Layer::activateLayer(const Layer& previous_layer,
                          const char* activation_function)
{
  for (int i = 0; i < size_; ++i)
    nodes_[i].activate(previous_layer, activation_function);
}

/**
 * Computes the output errors of all output nodes. Only to be used on the output
 * layer. Assuming there is an output node for each possible classification, we
 * only want the matching node to have value 1, all others will have value 0.
 * 
 * @param target  The desired output for the current input pattern
 */
void Layer::computeOutputErrors(const int target)
{
  for (int i = 0; i < size_; ++i)
  {
    if (target == i+1) nodes_[i].computeOutputError(1);
    else nodes_[i].computeOutputError(0);
  }
}

/**
 * Computes the error for all hidden nodes in the hidden layer.
 * This is a step in the backprop phase.
 * NOTE: Only call this function from the hidden layer!
 *
 * @param output_layer                The output layer
 * @param hidden_activation_funcion   The activation function for hidden nodes
 */
void Layer::computeHiddenErrors(const Layer& output_layer,
                                const char* hidden_activation_function)
{
  for (int i = 0; i < size_; ++i)
    nodes_[i].computeHiddenError(output_layer, i, hidden_activation_function);
}

/**
 * Adjusts all the weights between the current layer and previous layer.
 *
 * @param learning_rate   The learning rate constant
 * @param momentum        The momentum constant
 * @param previous_layer  The preceding layer in the network's architecture
 */
void Layer::adjustAllWeights(const double learning_rate, const double momentum,
                             const Layer& previous_layer)
{
  for (int i = 0; i < size_; ++i)
    nodes_[i].adjustWeights(learning_rate, momentum, previous_layer);
}

/**
 * Resets all changes in weights for every node in the layer.
 */
void Layer::resetDeltaWeights()
{
  for (int i = 0; i < size_; ++i)
    nodes_[i].resetDeltaWeights();
}

/**
 * Returns the size of the layer.
 *
 * @return  The number of nodes in the layer
 */
int Layer::get_size() const { return size_; }
