#!/usr/bin/env bash

# (C) 2012 Dennis Ideler
#
# Example:
#   $ sh run.sh 1 75 err.out acc.out
#
# See README.txt for more info on parameters.

set -e # Error checking.
set -u # Parameter checking.

SEED="$1"
RATIO="$2"
ERROR="$3"
ACCURACY="$4"

echo "Random number generator seed = $SEED"
echo "Training samples percentage = $RATIO"
echo "Output filename for network error = $ERROR"
echo "Output filename for network accuracy = $ACCURACY"
read -p "Are these values correct? (y/n) " -n 1
echo
echo

function run()
{
  # Experiment 1 (steel dataset)
  ./ann-vs-knn -c steel.conf -d ./data/faults-simple.data -s $SEED -t $RATIO -e $ERROR -a $ACCURACY -p
  ./ann-vs-knn -c steel-subset.conf -d ./data/faults-subset-simple.data -s $SEED -t $RATIO -e $ERROR -a $ACCURACY -p

  # Experiment 2 (digit dataset)
  #./ann-vs-knn -c digits.conf -d ./data/digits-simple.data -s $SEED -t $RATIO -e $ERROR -a $ACCURACY -p
}

if [[ $REPLY =~ ^[Yy]$ ]]; then
  run
fi

unset run
