/* 
 * File:   NearestNeighbour.cpp
 * Author: Dennis Ideler <di07ty at brocku.ca>
 *
 * Created on May 2012
 *
 */

#include "NearestNeighbour.h"
#include <cassert>
#include <cmath>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <iostream> // TODO remove
using namespace std;

NearestNeighbour::NearestNeighbour(const int k, const int num_attributes)
    : k_(k), num_attributes_(num_attributes) {}

NearestNeighbour::~NearestNeighbour()
{
  // check if any heap allocated memory is not null
  // then delete it
}

/**
 * Performs the lazy learning phase of kNN.
 * Unweighted k-nearest neighbour for classification.
 * Finds the k closest instances and takes the majority class.
 *
 * @param training_set The set of labeled examples to compare against.
 * @param testing_set The set of "unlabeled" examples to test accuracy.
 * @param verbose Boolean for outputting extra classification information.
 * @return The classification accuracy.
 */
double NearestNeighbour::learn(const vector< vector<float> > training_set,
                             const vector< vector<float> > testing_set,
                             const bool verbose) const
{
  // For each unclassified example (ie instance in testing set),                     
  int total_hits = 0;
  int total_cases = testing_set.size();
  for (int i = 0; i < total_cases; ++i)
  {
    int classification = computeNearestNeighbours(testing_set[i], training_set);
    int target = testing_set[i][num_attributes_];

    if (classification == target) ++total_hits;

    if (verbose)
    {
      cout << "Expected outcome: " << target
           << "\nActual outcome: " << classification << "\n\n";
    }
  }
  
  double accuracy = (static_cast<float>(total_hits) / total_cases) * 100;
  cout << "Correctly classified " << total_hits << " out of " << total_cases
       << " = " << accuracy << "%\n\n";
  return accuracy;
}

/**
 * Computes the distance to each classified example.
 * Sorts the distances and chooses the k nearest.
 * Returns the majority vote of the k nearest neighbours.
 *
 * @param query The unclassified example.
 * @param training_set The dataset to compare against.
 * @return The predicted classification of the query.
 */
int NearestNeighbour::computeNearestNeighbours(
    const vector<float> query,
    const vector< vector<float> > training_set) const
{
  int size = training_set.size();
  vector<neighbour> neighbours;
  for (int i = 0; i < size; ++i)
  {
    neighbour n;
    n.distance = distR(query, training_set[i]); // dist() not being used atm.
    n.classification = training_set[i][num_attributes_];
    neighbours.push_back(n);
  }

  sort(neighbours.begin(), neighbours.end());
 
  // Tally up the votes from the k nearest neighbours.
  map<int, int> votes;
  set<int> classes;
  for (int i = 0; i < k_; ++i)
  {
//    cout << "neighbour " << i+1 << ":  " << neighbours[i].classification
//         << " " << neighbours[i].distance << "\n";
    votes[neighbours[i].classification]++;
    classes.insert(neighbours[i].classification);
  }

  // Determine which class has the highest vote.
  set<int>::iterator it;
  int majority_vote = -99999999;
  int majority_class = -1;
  for (it = classes.begin(); it != classes.end(); ++it)
  {
    int classification = *it;
    if (votes[classification] > majority_vote)
    {
      majority_vote = votes[classification];
      majority_class = classification;
    }
  }
  return majority_class;
}


/**
 * Euclidean distance metric.
 *
 * @param query The unclassified example.
 * @param record The classified example.
 * @return The distance between the two examples.
 */
double NearestNeighbour::dist(const vector<float> query,
                              const vector<float> record) const
{
  assert(query.size() == record.size());
  double temp = 0;
  for (int i = 0; i < static_cast<int>(query.size()); ++i)
  {
    temp += sqr(query[i] - record[i]);
  }
  return sqrt(temp);
}

/**
 * Euclidean squared distance metric. More efficient than the actual distance.
 * Use when you need distance for comparisons, not the actual distance.
 *
 * @param query The unclassified example.
 * @param record The classified example.
 * @return The squared "distance" between the two examples.
 */
double NearestNeighbour::distR(const vector<float> query,
                               const vector<float> record) const
{
  assert(query.size() == record.size());
  double temp = 0;
  for (int i = 0; i < static_cast<int>(query.size()); ++i)
  {
    temp += sqr(query[i] - record[i]);
  }
  return temp;
}

/**
 * A generic function to square a value.
 */
template<class T> inline T NearestNeighbour::sqr(const T &x) const
{
  return x * x;
}
