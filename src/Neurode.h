/* 
 * File:   Neurode.h
 * Author: Dennis Ideler <di07ty at brocku.ca>
 *
 * Created on April 2011
 *
 * The Neurode class is an abstract base class because it contains at least one
 * pure virtual function. Some functions here do not have any functionality
 * implemented, because they are implemented in its subclasses (node specific).
 * Because at least one of its members lacks implementation, we cannot create
 * instances (objects) of it, which is perfect for our needs.
 * Even though we cannot instantiate an object from it, we can have
 * superclass pointers referencing subclass objects.
 * http://www.cplusplus.com/doc/tutorial/polymorphism/
 */

#ifndef NEURODE_H
#define	NEURODE_H

struct connections;
class Layer; // Do not use an #include when a forward declaration would suffice!

// Neurodes (Neurons/Nodes/Processing Units/Cells/etc) have an input and output.
// Input neurodes (i.e. neurodes in the input layer) are dummy nodes; they just
// contain some stimuli (input) to present to the hidden layer.
// All other neurodes contain a summing (integration) and activation function.
class Neurode
{
 public:
  Neurode();
  Neurode(const Neurode& orig);
  virtual ~Neurode();
  void initConnections(const int num_connections, const double kLowerRange,
                       const double kUpperRange);
  void activate(const Layer& previous_layer, const char* activation_function);
  void computeOutputError(const int target);
  void computeHiddenError(const Layer& output_layer, const int node_i,
                          const char* hidden_activation_function);
  void adjustWeights(const double learning_rate, const double momentum,
                     const Layer& previous_layer);
  void resetDeltaWeights();
  void set_input(const double input);
  double get_output() const;
  double get_error() const;
  double get_weight(const int connection) const;

 private:
  double sumWeightedInputs(const Layer& previous_layer);
  double logisticFunction(const double x);
  double tanhFunction(const double x);
  double softmaxFunction(const double x, const Layer& previous_layer); // TODO
  connections* links_;  // The incoming connections to the node.
  double output_;  // The output value of the node.
  double error_;  // The error of the output node's output value.
//  DISALLOW_COPY_AND_ASSIGN(Neurode);  // Enable if copy constructor not needed
};

#endif	/* NEURODE_H */

// REVIEW: use thresholds?
// TODO: Have subclasses with overridden activation functions
// Subclasses for input neurode, hidden neurode, output neurode.
// Input nodes only have an output value.
// Hidden nodes have weights, activation, weight change, error computation, output.
// Output nodes have weights, activation, weight change, error computation, output.
