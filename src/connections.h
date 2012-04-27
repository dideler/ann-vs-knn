/* 
 * File:   connections.h
 * Author: Dennis Ideler <di07ty at brocku.ca>
 *
 * Created on April 2011
 *
 * Structs should be used for passive objects that carry data,
 * and may have associated constants, but lack any functionality other than
 * access/setting the data members. The accessing/setting of fields is done by
 * directly accessing the fields rather than through method invocations.
 * Methods should not provide behavior but should only be used to set up the data
 * members, e.g., constructor, destructor, Initialize(), Reset(), Validate().
 *
 * If more functionality is required, a class is more appropriate.
 * If in doubt, make it a class.
 */

#ifndef CONNECTIONS_H
#define	CONNECTIONS_H

#include <cstdlib>

/**
 * In a weighted network, every node connection has a weight.
 * Weights are initialized with some random value in a user-defined range.
 * This range is typically [-1, +1] or [-0.5, +0.5]
 * 
 * This structure is for the incoming connections of a node.
 * All nodes have incoming connections except the input layer nodes.
 * Connections have weights (connection strengths).
 * Example: input layer has 3 nodes, then every node on the next layer (hidden
 *          layer nodes) has 3 incoming weighted connections.
 */
struct connections
{
  int size;  // Number of weighted connections on the node.
  double* weights;  // Pointer to the connection weights.
  double* delta_weights;  // Pointer to the change in connection weights.

  // TODO: add bias? see link for more info
  // http://fbim.fh-regensburg.de/~saj39122/jfroehl/diplom/e-13-text.html#Backpropagation

  // Constructor - inits weights
  connections(const int num_connections, const double kLowerRange,
              const double kUpperRange) : size(num_connections)
  {
      // size = num_connections; <- is replaced by initializer list.
      weights = new double[size];
      delta_weights = new double[size];

      const double kRange = kUpperRange - kLowerRange;

      // Initialize all weights to small random values. Set delta weights to 0.
      for (int i = 0; i < size; ++i)
      {
          weights[i] = kLowerRange + static_cast<double> (kRange * rand() /
                       (RAND_MAX + 1.0));
          delta_weights[i] = 0.0;
      }
  }

  // Copy constructor
  connections(const connections & orig)
  {
      weights = new double[size];
      for (int i = 0; i < size; ++i)
          weights[i] = orig.weights[i];

      size = orig.size;
  }

  // Destructor - cleans up weights
  ~connections()
  {
      delete[] weights;
  }
};

#endif	/* CONNECTIONS_H */
