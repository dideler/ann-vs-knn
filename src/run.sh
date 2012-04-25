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

function run()
{
  # Experiment 1 (steel dataset)
  ./ann -c ann.conf -d ./data/Faults.dat -s $SEED -t $RATIO -e $ERROR -a $ACCURACY -p

  # Experiment 2 (digit dataset)
  #./ann -c digits.conf -d digits.dat -s $SEED -t $RATIO -e $ERROR -a $ACCURACY -p
}

if [[ $REPLY =~ ^[Yy]$ ]]; then
  run
fi

unset run
