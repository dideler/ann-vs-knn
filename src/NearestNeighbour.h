/* 
 * File:   NearestNeighbour.h
 * Author: Dennis Ideler <di07ty at brocku.ca>
 *
 * Created on May 2012
 *
 */

#ifndef NEARESTNEIGHBOUR_H
#define	NEARESTNEIGHBOUR_H

// A macro to disallow the copy constructor and operator= functions
// This should be used in the private: declarations for a class
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&);               \
  void operator=(const TypeName&)

#include <vector>                                                                    
using std::vector;

struct neighbour;

class NearestNeighbour
{
 public:
  NearestNeighbour(const int k, const int num_attributes);
  ~NearestNeighbour();
  double learn(const vector< vector<float> > training_set,
               const vector< vector<float> > testing_set,
               const bool verbose) const;
 private:
  struct neighbour
  {
    double distance;
    int classification;
    // Overload the < operator for sorting neighbour structures.
    bool operator<(const neighbour& other) const
    {
      return distance < other.distance;
    }
  };
  int k_;
  int num_attributes_;
  int computeNearestNeighbours(const vector<float> query,
                               const vector< vector<float> > training_set) const;
  double dist(const vector<float> query, const vector<float> record) const;
  double distR(const vector<float> query, const vector<float> record) const;
  template<class T> T sqr(const T &x) const;
  DISALLOW_COPY_AND_ASSIGN(NearestNeighbour);
};

#endif
