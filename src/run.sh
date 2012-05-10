#!/usr/bin/env bash

# (C) 2012 Dennis Ideler
#
# Example:
#   $ bash run.sh 1 75 ann-err.out ann-acc.out knn-acc.out
#
# See README.txt for more info on parameters.

set -e # Error checking.
set -u # Parameter checking.

SEED="$1"
RATIO="$2"
ERROR="$3"
ACCURACY="$4"
KNN_ACCURACY="$5"

echo "Random number generator seed = $SEED"
echo "Training samples percentage = $RATIO"
echo "Output filename for network error = $ERROR"
echo "Output filename for network accuracy = $ACCURACY"
echo "Output filename for k-NN accuracy = $KNN_ACCURACY"
read -p "Are these values correct? (y/n) " -n 1
echo
echo

function run()
{
  # Experiment 1 (steel dataset)
  # For verbose output, use the -v tag (warning: running time will be extra long).
  ./ann-vs-knn -c steel.conf -d ./data/faults-simple.data -s $SEED -t $RATIO -e $ERROR -a $ACCURACY -k $KNN_ACCURACY -p
  ./ann-vs-knn -c steel-subset.conf -d ./data/faults-subset-simple.data -s $SEED -t $RATIO -e $ERROR -a $ACCURACY -k $KNN_ACCURACY -p

  # Experiment 2 (digit dataset)
  #./ann-vs-knn -c digits.conf -d ./data/digits-simple.data -s $SEED -t $RATIO -e $ERROR -a $ACCURACY -p
}

if [[ $REPLY =~ ^[Yy]$ ]]; then
  run
fi

unset run
