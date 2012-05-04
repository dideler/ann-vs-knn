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
 * Performs the lazy learning phase.
 * Unweighted k-nearest neighbour for classification.
 * Finds the k closest instances and takes the majority class.
 */
void NearestNeighbour::learn(const vector< vector<float> > training_set,
                             const vector< vector<float> > testing_set) const
{
  // For each unclassified example (ie instance in testing set),                     
  int total_hits = 0;
  int total_cases = testing_set.size();
  for (int i = 0; i < total_cases; ++i)
  {
    int classification = computeNearestNeighbours(testing_set[i], training_set);
    int target = testing_set[i][num_attributes_];

    if (classification == target) ++total_hits;
    cout << "Expected outcome: " << target << "\n" // TODO: remove after testing
            "Actual outcome: " << classification << "\n\n";
  }
  
  float percentage = (static_cast<float>(total_hits) / total_cases) * 100;
  cout << "Correctly classified " << total_hits << " out of " << total_cases
       << " = " << percentage << "%\n\n";
  // TODO: save hit percentage to file?
}

/**
 * Computes the distance to each classified example.
 * Sorts the distances and chooses the k nearest.
 * Returns the majority vote of the k nearest neighbours.
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
    n.distance = dist(query, training_set[i]); // TODO: Also try distR.
    // TODO: weighted knn
    // If weighted, multiply each examples vote (i.e. distance) by a weight.           
    // weight_i = 1 / dist(query, record_i)^2
    n.classification = training_set[i][num_attributes_];
    neighbours.push_back(n);
  }

  sort(neighbours.begin(), neighbours.end());
 
  // Tally up the votes from the k nearest neighbours.
  map<int, int> votes;
  set<int> classes;
  for (int i = 0; i < k_; ++i)
  {
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
