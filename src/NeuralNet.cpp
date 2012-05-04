/* 
 * File:   NeuralNet.cpp
 * Author: Dennis Ideler <di07ty at brocku.ca>
 * 
 * Created on April 2011
 */

#include "NeuralNet.h"
#include "Layer.h"
#include "Neurode.h"
#include <string>
#include <vector>
#include <algorithm> // For random_shuffle.
#include <cstdlib>  // For atof.
#include <iostream> // TODO remove
using std::cout;

/**
 * Constructor inits a NN with 3 layers (1 input, 1 hidden, 1 output).
 * Constructors should merely set member variables to their initial values.
 * Any complex initialization should go in an explicit Init() method.
 *
 * @param num_input   Number of nodes in the input layer
 * @param num_hidden  Number of nodes in the hidden layer
 * @param num_output  Number of nodes in the output layer
 */
NeuralNet::NeuralNet(const int num_input, const int num_hidden,
                     const int num_output)
{
  input_layer_ = new Layer(num_input);
  hidden_layer_ = new Layer(num_hidden);
  output_layer_ = new Layer(num_output);
}

NeuralNet::NeuralNet(const NeuralNet& orig) { /*TODO*/ }

NeuralNet::~NeuralNet()
{
  delete input_layer_;
  delete hidden_layer_;
  delete output_layer_;
}

/**
 * Initializes the weighted connections between the network layers. Only the
 * hidden and output layers have incoming connections, so they are initiated
 * from those layers. For each node in the given layer, a vector of connections
 * is created (ultimately in the Neurode class). So each node in a layer has an
 * incoming weighted connection from _each_ node in the preceding layer.
 *
 * @param num_connections_input_hidden  Number of connections from input to hidden layer
 * @param num_connections_hidden_output Number of connections from hidden to output layer
 * @param kLowerRange                   Lower weight range
 * @param kUpperRange                   Upper weight range
 */
void NeuralNet::initWeights(const int num_connections_input_hidden,
                            const int num_connections_hidden_output,
                            const double kLowerRange, const double kUpperRange)
{
  hidden_layer_->initWeightLayer(num_connections_input_hidden, kLowerRange,
                                 kUpperRange);
  output_layer_->initWeightLayer(num_connections_hidden_output, kLowerRange,
                                 kUpperRange);
}

/**
 * Forward propagate an input pattern to calculate the network output.
 * For the hidden & output layers, each node in the layer is activated by
 * summing the weighted connections with the inputs and then passing the sum
 * through an activation function. The output of a node in one layer will be the
 * input for a node in a succeeding layer.
 *
 * @param hidden_activation_function  Activation function used on hidden units
 * @param output_activation_function  Activation function used on output units
 */
void NeuralNet::forwardprop(const char* hidden_activation_function,
                            const char* output_activation_function)
{
  hidden_layer_->activateLayer(*input_layer_, hidden_activation_function);
  output_layer_->activateLayer(*hidden_layer_, output_activation_function);
}

/**
 * Backpropagate the error to adjust the weights.
 * Main idea of backprop is to distribute the error function across the hidden
 * layers, corresponding their effect on the output.
 *
 * @param hidden_activation_function  Activation function used on hidden units
 * @param output_activation_function  Activation function used on output units
 * @param target                      Desired output for the input pattern
 * @param learning_rate               Learning rate constant
 * @param momentum                    Momentum constant
 */
void NeuralNet::backprop(const char* hidden_activation_function,
                         const int target, const double learning_rate,
                         const double momentum)
{
  // After the forward prop, we calculate the errors in the output and hidden
  // layers. Then we adjust the weights between each, going backwards.

  output_layer_->computeOutputErrors(target);
  output_layer_->adjustAllWeights(learning_rate, momentum, *hidden_layer_);
  hidden_layer_->computeHiddenErrors(*output_layer_, hidden_activation_function);
  hidden_layer_->adjustAllWeights(learning_rate, momentum, *input_layer_);
}

/**
 * Resets the change in weights for every weight. Called after each epoch.
 */
void NeuralNet::resetDeltaWeights()
{
  hidden_layer_->resetDeltaWeights();
  output_layer_->resetDeltaWeights();
}

/**
 * Performs one epoch (i.e. for each example, loads all input patterns and
 * propagates them). Backpropagation is performed when training.
 * This function is used for training and testing the ANN.
 *
 * @param sample_set  The dataset used for training or testing.
 * @param train  Performs backprop and calculates network accuracy if true.
 */
void NeuralNet::loadPatterns(const vector< vector<float> > sample_set,
                             const char* hidden_activation_function,
                             const char* output_activation_function,
                             const double learning_rate,
                             const double momentum,
                             const bool train,
                             const int epoch_num)
{
  // Load each pattern into neural net, one at a time.
  int total_hits = 0;
  int total_cases = sample_set.size();
  double network_error = 0.0;
  for (int example = 0; example < total_cases; ++example)
  {
    // Present the inputs to the input layer nodes.
    int size = input_layer_->get_size();
    for (int attribute = 0; attribute < size; ++attribute)
    {
      double input = sample_set[example][attribute];
      input_layer_->nodes_[attribute].set_input(input);
    }

    // Forwardpropagate the input pattern.
    forwardprop(hidden_activation_function, output_activation_function);

    // Get the classification target.
    int target = sample_set[example][size];
#if 0
    for (int i = 0; i < output_layer_->get_size(); ++i) 
    {
      if (sample_set[example][size + i] == 1)
      {
        target = i + 1;
        break;
      }
    }
#endif

    // Backpropagate the error (adjusts the weights).
    if (train)
    {
      backprop(hidden_activation_function, target, learning_rate, momentum);
      network_error += get_network_error();  // Squared network error.
    }

    if (get_result() == target)
      ++total_hits;

//      cout << "Expected outcome: " << target << "\n"
//              "Actual outcome: " << get_result() << "\n\n";
//      for (int m = 0; m < output_layer_->get_size(); ++m)
//        cout << "node " << m+1 << ": " << get_output(m)
//             << "\terror: " << get_output_error(m) << "\n";
//      cout << "\n";
  }
  
  float percentage = (static_cast<float>(total_hits) / total_cases) * 100;
  if (train)
  {
    all_hit_percentage_[epoch_num] = percentage;
    all_network_error_[epoch_num] = network_error;
    cout << "epoch: " << epoch_num + 1 << "  error: " << network_error << "\n";
  }
  cout << "Correctly classified " << total_hits << " out of " << total_cases
       << " = " << percentage << "%\n\n";
}

/**
 * Trains the neural network on the training set (i.e. all training cases).
 *
 * @param training_set  The set of data that the Neural Net will train on
 * @param num_epochs    Number of epochs (i.e. learning cycles)
 */
void NeuralNet::train(vector< vector<float> > training_set,
                      const int num_epochs,
                      const char* hidden_activation_function,
                      const char* output_activation_function,
                      const double learning_rate, const double momentum,
                      const double max_error)
{
  all_hit_percentage_ = new double[num_epochs];
  all_network_error_ = new double[num_epochs];

  // Reminder: one epoch is equal to training the NN on the entire training set.
  // Train the network for every epoch.
  for (int epoch = 0; epoch < num_epochs; ++epoch)
  {
    // Shuffle all training cases.
    std::random_shuffle(training_set.begin(), training_set.end());

    // Load patterns, propagate them, then back-propagate them.
    loadPatterns(training_set, hidden_activation_function,
                 output_activation_function, learning_rate, momentum, true,
                 epoch);

    if (all_network_error_[epoch] <= max_error)
      break;

    resetDeltaWeights();
  }
}

/**
 * Tests the NN by presenting test cases to the NN which haven't trained on.
 * The percentage of error indicates how well the NN performs.
 *
 * @param testing_set   The set of data that the network will be tested on
 */
void NeuralNet::test(vector< vector<float> > testing_set,
                     const char* hidden_activation_function,
                     const char* output_activation_function)
{
  loadPatterns(testing_set, hidden_activation_function,
               output_activation_function, 0.0, 0.0, false, 0);
}

/**
 * The winning output node is the node with an output closest to 1, or in other
 * words, the node with the highest output value.
 * The position of the node determines its classification type.
 *
 * @return The predicted result of the network
 */
int NeuralNet::get_result() const
{
  double current_output;
  double max_output = -999999999.99;
  int result = -1;
  for (int i = 0; i < output_layer_->get_size(); ++i)
  {
    current_output = output_layer_->nodes_[i].get_output();
    if (current_output > max_output)
    {
      max_output = current_output;
      result = i;
    }
  }
  return result + 1; // +1 because our classification types start at 1, not 0.
}

/**
 * Returns the output value from the specified output layer node.
 *
 * @param output_node   The output node to retrieve the output value from
 * @return  The output value of the given output node
 */
double NeuralNet::get_output(int output_node) const
{
  return output_layer_->nodes_[output_node].get_output();
}

/**
 * Returns the error from the specified output layer node.
 *
 * @param output_node   The output node to retrieve the error from
 * @return  The error of the given output node
 */
double NeuralNet::get_output_error(int output_node) const
{
  return output_layer_->nodes_[output_node].get_error();
}

/**
 * Returns the squared error of the network.
 * The error of the network is calculated by adding up the squared values of the
 * output errors of each pattern (for one epoch). Other error functions that can
 * be used are the mean squared error and the root mean squared error.
 *
 * @return The network's squared error
 * @TODO calculate mean squared error, root mean squared error, or mean error?
 */
double NeuralNet::get_network_error() const
{
  double error = 0.0;
  for (int i = 0; i < output_layer_->get_size(); ++i)
    error += get_output_error(i) * get_output_error(i);
  return error;
}

/**
 * Returns an array of the network error during training of each epoch.
 *
 * @return All the recorded error of the network
 */
double* NeuralNet::get_all_network_error() const
{
  return all_network_error_;
}

/**
 * Returns an array of the network hit percentage during training of each epoch.
 *
 * @return All the recorded hit percentages of the network
 */
double* NeuralNet::get_all_hit_percentage() const
{
  return all_hit_percentage_;
}
