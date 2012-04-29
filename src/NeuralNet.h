/* 
 * File:   NeuralNet.h
 * Author: Dennis Ideler <di07ty at brocku.ca>
 *
 * Created on April 2011
 */

#ifndef NEURALNET_H
#define	NEURALNET_H

#include <vector>
using std::vector; // Import portion of std namespace into current namespace.
class Layer;

// Neural Net consists of all the Neurodes and Layers and Connection Weights.
// Num weight layers = total layers - 1 (e.g. 3 node layers, 2 weight layers)
// Num total weights = (previous layer size) * (previous layer size)
class NeuralNet
{
 public:
// NOTE: The input layer size is static. Future work can be making it dynamic.
//       A dynamic input layer is more flexible and is one less user parameter.
  NeuralNet(const int num_input, const int num_hidden, const int num_output);
  NeuralNet(const NeuralNet& orig);
  virtual ~NeuralNet();
  void initWeights(const int num_connections_input_hidden,
                   const int num_connections_hidden_output,
                   const double kLowerRange,
                   const double kUpperRange);
  void train(vector< vector<float> > training_set,
             const int num_epochs,
             const char* hidden_activation_function,
             const char* output_activation_function,
             const double learning_rate,
             const double momentum,
             const double max_error);
  void test(vector< vector<float> > testing_set,
            const char* hidden_activation_function,
            const char* output_activation_function);
  double* get_all_network_error(void) const;
  double* get_all_hit_percentage(void) const;

 private:
  void loadPatterns(const vector< vector<float> > sample_set,
                    const char* hidden_activation_function,
                    const char* output_activation_function,
                    const double learning_rate,
                    const double momentum,
                    const bool train,
                    const int epoch_num);
  void forwardprop(const char* hidden_activation_function,
                   const char* output_activation_function);
  void backprop(const char* hidden_activation_function,
                const int target,
                const double learning_rate,
                const double momentum);
  void resetDeltaWeights(void);
  int get_result(void) const;
  double get_output(int output_node) const;
  double get_output_error(int output_node) const;
  double get_network_error(void) const;
  Layer* input_layer_;
  Layer* hidden_layer_;
  Layer* output_layer_;
  double* all_network_error_;  // Holds the network error of each epoch.
  double* all_hit_percentage_;
};

#endif	/* NEURALNET_H */

/* Training the ANN:
 *  Idea = iterate through the training set and ajust the weights to minimize
 *         the gradient of the error.
 *
 *  - Read in randomized inputs
 *  - Perform forwardprop phase for an input pattern
 *  - Compute error value (for output and hidden units) and backpropagate
 *
 *  Main idea of backprop: distribute the error function across the hidden
 *                         layers, corresponding their effect on the output.
 */
