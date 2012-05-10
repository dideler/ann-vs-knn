#!/usr/bin/env bash

# (C) 2012 Dennis Ideler
#
# Performs enough runs to be statistically significant, on various datasets.
# Example:
#   $ bash all_runs.sh
#
# See README.txt for more info on parameters.

set -e
set -u

# Variables for the first experiment.
CONF1="steel.conf"
DATA1="../data/faults-simple.data"
RATIO1="75"
ANN_ERROR1="../results/ann-err-faults.out"
ANN_ACCURACY1="../results/ann-acc-faults.out"
KNN_ACCURACY1="../results/knn-acc-faults.out"

# Variables for the second experiment.
CONF2="steel-subset.conf"
DATA2="../data/faults-subset-simple.data"
RATIO2="75"
ANN_ERROR2="../results/ann-err-faults-subset.out"
ANN_ACCURACY2="../results/ann-acc-faults-subset.out"
KNN_ACCURACY2="../results/knn-acc-faults-subset.out"

# Variables for the third experiment.
CONF3="digits.conf"
DATA3="../data/digits-simple.data"
RATIO3="75"
ANN_ERROR3="../results/ann-err-digits.out"
ANN_ACCURACY3="../results/ann-acc-digits.out"
KNN_ACCURACY3="../results/knn-acc-digits.out"

echo "== Parameters for experiment #1 =="
echo "Configuration file = $CONF1"
echo "Dataset = $DATA1"
echo "Training samples percentage = $RATIO1"
echo "Output filename for network error = $ANN_ERROR1"
echo "Output filename for network accuracy = $ANN_ACCURACY1"
echo "Output filename for k-NN accuracy = $KNN_ACCURACY1"
echo
echo "== Parameters for experiment #2 =="
echo "Configuration file = $CONF2"
echo "Dataset = $DATA2"
echo "Training samples percentage = $RATIO2"
echo "Output filename for network error = $ANN_ERROR2"
echo "Output filename for network accuracy = $AN__ACCURACY2"
echo "Output filename for k-NN accuracy = $KNN_ACCURACY2"
echo
echo "== Parameters for experiment #3 =="
echo "Configuration file = $CONF3"
echo "Dataset = $DATA3"
echo "Training samples percentage = $RATIO3"
echo "Output filename for network error = $ANN_ERROR3"
echo "Output filename for network accuracy = $ANN_ACCURACY3"
echo "Output filename for k-NN accuracy = $KNN_ACCURACY3"
echo
read -p "Are these values correct? (y/n) " -n 1
echo
echo

function run()
{
  echo "Startins runs for steel faults dataset."
  for SEED in {1..30}
  do
    bash run.sh $CONF1 $DATA1 $SEED $RATIO1 $ANN_ERROR1 $ANN_ACCURACY1 $KNN_ACCURACY1
  done

  echo "Startins runs for steel faults datasubset."
  for SEED in {1..30}
  do
    bash run.sh $CONF2 $DATA2 $SEED $RATIO2 $ANN_ERROR2 $ANN_ACCURACY2 $KNN_ACCURACY2
  done

  echo "Startins runs for digit recognition dataset."
  for SEED in {1..30}
  do
    bash run.sh $CONF2 $DATA2 $SEED $RATIO2 $ANN_ERROR2 $ANN_ACCURACY2 $KNN_ACCURACY2
  done
}

if [[ $REPLY =~ ^[Yy]$ ]]; then
  run
fi

unset run
