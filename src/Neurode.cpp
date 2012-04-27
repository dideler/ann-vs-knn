/* 
 * File:   Neurode.cpp
 * Author: Dennis Ideler <di07ty at brocku.ca>
 * 
 * Created on April 2011
 */

#include "Neurode.h"
#include "connections.h"
#include "Layer.h"
#include "NeuralNet.h"
#include <cmath>  // For exp(); the e number raised to the power x.
#include <cstring>  // For strcmp().

// NOTE: It is legal, though unnecessary, to explicitly use the 'this' pointer
//       when referring to members of the class. It can be explicitly used to
//       emphasize which variables are local and which are members.
//       Usually avoided because it can overcomplicate code.
//       In NetBeans, member variables are green, so no need for 'this->'.

Neurode::Neurode() : output_(0.0) { links_ = NULL; }

Neurode::Neurode(const Neurode& orig)
{
  output_ = orig.output_;
  error_ = orig.error_;
  links_ = new connections(*orig.links_);
}

Neurode::~Neurode()
{
  if (links_ != NULL)
    delete links_;
}

/**
 * Creates a new vector of weighted connections.
 * All (incoming) weighted connections to the node are initialized within a
 * certain weight range. Do not call this function on input layer nodes!
 *
 * @param num_connections   The number of incoming connections to each node
 * @param kLowerRange       The lower weight range
 * @param kUpperRange       The upper weight range
 */
void Neurode::initConnections(const int num_connections,
                              const double kLowerRange,
                              const double kUpperRange)
{
  links_ = new connections(num_connections, kLowerRange, kUpperRange);
}

/**
 * A node is "activated" when it has its weighted inputs summed and then the
 * activation function applied to that sum. Activating nodes is a process of
 * forward-propagation.
 * 
 * @param previous_layer      The preceding layer in the network's architecture
 * @param activation_function The activation function to be used on the node
 */
void Neurode::activate(const Layer& previous_layer,  // the layer with inputs
                       const char* activation_function) // logistic or tanh
{
  output_ = sumWeightedInputs(previous_layer);

  if (strcmp(activation_function, "logistic") == 0)
    output_ = logisticFunction(output_);
  else if(strcmp(activation_function, "tanh") == 0)
    output_ = tanhFunction(output_);
}

/**
 * The integration or combination function.
 * For example: weighted sum = (x_1 * w_1) + ... + (x_n * w_n)
 * It multiplies the input to the node (which is the output from a node in the
 * previous layer) with the weight of the connection between the two nodes, and
 * adds it to the sum.
 *
 * @param previous_layer  The preceding layer in the network's architecture
 * @return  The sum of the weighted inputs
 */
double Neurode::sumWeightedInputs(const Layer& previous_layer)
{
  double sum = 0.0;
  for(int i = 0; i < links_->size; ++i)
    sum += previous_layer.nodes_[i].get_output() * links_->weights[i];
  return sum;
}

/**
 * The logistic activation function (aka sigmoid function): f(x) = 1 / 1 + e^-x
 * http://en.wikipedia.org/wiki/Logistic_function
 *
 * @param x The output of the combination function (summed weights & inputs)
 * @return  The output of the logistic activation function
 */
double Neurode::logisticFunction(const double x)
{
  // To avoid floating-point overflow, we add a safety measure.
  // ftp://ftp.sas.com/pub/neural/FAQ2.html#A_overflow
  if (x < -45) return 0;
  else if (x > 45) return 1;
  else return (1 / (1 + exp(-x)));
}

/**
 * The tanh activation function (aka hyperbolic tangent function).
 * tanh x = sinh x / cosh x
 *        = (exp(x) - exp(-x)) / (exp(x) + exp(-x))
 *        = (exp(2x) - 1) / (exp(2x) + 1)
 * http://en.wikipedia.org/wiki/Tanh
 *
 * @param x The output of the combination function (summed weights & inputs)
 * @return  The output of the tanh activation function
 */
double Neurode::tanhFunction(const double x) { return tanh(x); }

/**
 * Output nodes need to have their error computed if using Supervised Learning.
 * Note: Many error functions exist. A common error function is the "squared
 * error" -- the squared error between the computed output and the desired
 * output for each output node across all patterns in the data set.
 * 
 * @note Tutorials on calculating error are conflicting. Some say to simply use
 * target - output, others say to use the derivative of the sigmoid.
 * e.g. http://www.nnwj.de/forwardpropagation.html
 *
 * @param target  The desired output for the current input pattern
 */
void Neurode::computeOutputError(const int target)
{
  //error_ = target - output_;  // Simple error, uses no derivative of sigmoid.
  error_ = output_ * (1 - output_) * (target - output_);
}

/**
 * Before we adjust the weights, we need to calculate the error of the hidden
 * nodes. Each hidden node's error is a proportionally weighted sum of the
 * errors produced at the output layer. Only call function for hidden neurodes!
 *
 * Formula: error_i = output_i (1 - output_i) sum(w_ij * output_error_j)
 * error_i is error of current hidden node; output_i is output of current hidden
 * node; w_ij is weight between output node j and hidden node i; etc...
 * 
 * @param output_layer  The output layer in the network
 * @param node_i        Position of the hidden node relative to the output layer
 * @param hidden_activation_function  The activation function for hidden nodes
 */
void Neurode::computeHiddenError(const Layer& output_layer, const int node_i,
                                 const char* hidden_activation_function)
{
  double sum = 0.0;
  for (int j = 0; j < output_layer.get_size(); ++j)
    sum += output_layer.nodes_[j].get_weight(node_i) *
           output_layer.nodes_[j].get_error();

  // http://www.codeproject.com/KB/cs/BackPropagationNeuralNet.aspx
  // That tutorial simply uses 'error = sum'. Results seem to be the same.
  if (strcmp(hidden_activation_function, "logistic") == 0)
    error_ = output_ * (1 - output_) * sum;
  else if (strcmp(hidden_activation_function, "tanh") == 0)
    error_ = ((2 * cosh(output_)) / (cosh(2 * output_) + 1)) *
             ((2 * cosh(output_)) / (cosh(2 * output_) + 1)) * sum;
//    error_ = ((4 * (cosh(output_) * cosh(output_))) /
//             ((1 + cosh(2 * output_)) * (1 + cosh(2 * output_)))) * sum;

  // TODO: should be using the derivative during backprop
  //       logisticDerivative(x) = e^x / (e^x + 1)^2
  //       tanhDerivative(x) = sech^2(x) = (2 cosh(x)) / (cosh(2 x)+1)^2
  //       according to wolfram          = (4 cosh^2(x)) / (1+cosh(2 x))^2
}

/**
 * Adjusts all the connection weights of the current neurode (during backprop).
 * Note that delta weight is the same thing as weight-change.
 *
 * weight_ij = weight_ij + delta weight_ij + (momentum * prev delta weight_ij)
 * Where delta weight_ij = learning rate * output_i * error_j
 *
 * We use the previous layer for its output values. Remember, the connections to
 * the previous layer are stored in nodes from the current layer.
 *
 * Momentum simply adds a fraction m of the previous weight update to the
 * current one. The momentum term helps the network get out of local minima.
 * This is probably the most popular extension of the backprop algorithm.
 * When the gradient keeps changing direction, momentum will smooth out the
 * variations. Useful when the network is not well-conditioned.
 * Also see: http://www.shiffman.net/teaching/nature/nn/
 *
 * @param learning_rate   The learning rate constant
 * @param momentum        The momentum constant
 * @param previous_layer  The preceding layer in the network's architecture
 */
void Neurode::adjustWeights(const double learning_rate, const double momentum,
                            const Layer& previous_layer)
{
  double delta_weight = 0.0;
  for (int i = 0; i < links_->size; ++i)
  {
    delta_weight = learning_rate * previous_layer.nodes_[i].get_output() *
                   error_;
    links_->weights[i] += delta_weight + (momentum * links_->delta_weights[i]);
    links_->delta_weights[i] = delta_weight; // Update previous delta weight.
  }
//  Example: adjusting connections from Fc to Fb:
//    These connections are on the Fc layer (due to program design).
//    For every connection on Fc (where i is a Fb node, j is a Fc node):
//      w_ij = learning rate * output_i * error_j
//    so we need to get the output values from the hidden node connected to the current weight.
//    we need to pass in the hidden layer!
//  Then for Fb to Fa, we pass in the input layer!
}

/**
 * Resets the change in weight to 0.0 for every incoming connection to the node.
 * Change in weight needs to be reset at every epoch.
 */
void Neurode::resetDeltaWeights()
{
  for (int i = 0; i < links_->size; ++i)
    links_->delta_weights[i] = 0.0;
}

/**
 * Sets the input (which if unprocessed will also be the output) of the node.
 * Used for input layer nodes only.
 *
 * @param input   The input value (pattern) that the node will have
 */
void Neurode::set_input(const double input) { output_ = input; }

/**
 * Returns the output value of the node.
 *
 * @return  The output value of the node
 */
double Neurode::get_output() const { return output_; }

/**
 * Returns the output error of the node.
 *
 * @return  The error of the current node
 */
double Neurode::get_error() const { return error_; }

/**
 * Returns the specified connection weight that's attached to the node.
 *
 * @param connection  The connection whose weight will be returned
 * @return  The weight of the given connection
 */
double Neurode::get_weight(const int connection) const
{
  return links_->weights[connection];
}
