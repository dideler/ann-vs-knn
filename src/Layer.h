/* 
 * File:   Layer.h
 * Author: Dennis Ideler <di07ty at brocku.ca>
 *
 * Created on April 2011
 */

#ifndef LAYER_H
#define	LAYER_H

class Neurode;

// Layer class represents a single layer in the ANN. This can be the input,
// hidden, or output layer. A layer consists of Neurodes.
// The number of neurodes is determined by the user.

class Layer
{
 public:
  explicit Layer(const int num_neurodes);  // Only takes one arg, thus explicit
  Layer(const Layer& orig);
  virtual ~Layer();
  void initWeightLayer(const int num_connections, const double kLowerRange,
                       const double kUpperRange);
  void activateLayer(const Layer& previous_layer,
                     const char* activation_function);
  void computeOutputErrors(const int target);
  void computeHiddenErrors(const Layer& output_layer,
                           const char* hidden_activation_function);
  void adjustAllWeights(const double learning_rate, const double momentum,
                        const Layer& previous_layer);
  void resetDeltaWeights();
  int get_size() const;  // Returns the size of the layer (number of nodes).
  Neurode* nodes_;  // All the neurodes in the layer.

 private:
  int size_;  // Number of nodes in the layer. -1 means size is not yet known.
//  DISALLOW_COPY_AND_ASSIGN(Layer);  // Enable if copy constructor not needed
};

#endif	/* LAYER_H */

