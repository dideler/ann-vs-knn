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

class NearestNeighbour
{
 public:
  NearestNeighbour(const int k, const int num_attributes);
  ~NearestNeighbour();
  void learn(const vector< vector<float> > training_set,
             const vector< vector<float> > testing_set);
 private:
  struct neighbour
  {
    double distance;
    int classification;
  };
  int k_;
  int num_attributes_;
  int computeNearestNeighbours(const vector<float> query,
                               const vector< vector<float> > training_set);
  double dist(const vector<float> query, const vector<float> record);
  double distR(const vector<float> query, const vector<float> record);
  template<class T> T sqr(const T &x);
  bool compareDist(const neighbour &a, const neighbour &b);
  DISALLOW_COPY_AND_ASSIGN(NearestNeighbour);
};

#endif
