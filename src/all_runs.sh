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

RESULTS_DIR="../results/"
DATA_DIR="../data/"

# Variables for the first experiment.
CONF1="steel.conf"
DATA1=$DATA_DIR"faults-simple.data"
RATIO1="75"
ANN_ERROR1="ann-err-faults.out"
ANN_ACCURACY1="ann-acc-faults.out"
KNN_ACCURACY1="knn-acc-faults.out"

# Variables for the second experiment.
CONF2="steel-subset.conf"
DATA2=$DATA_DIR"faults-subset-simple.data"
RATIO2="75"
ANN_ERROR2="ann-err-faults-subset.out"
ANN_ACCURACY2="ann-acc-faults-subset.out"
KNN_ACCURACY2="knn-acc-faults-subset.out"

# Variables for the third experiment.
CONF3="digits.conf"
DATA3=$DATA_DIR"digits-simple.data"
RATIO3="75"
ANN_ERROR3="ann-err-digits.out"
ANN_ACCURACY3="ann-acc-digits.out"
KNN_ACCURACY3="knn-acc-digits.out"

echo
echo "== Parameters for experiment #1 =="
echo "Configuration file = $CONF1"
echo "Dataset = $DATA1"
echo "Training samples percentage = $RATIO1"
echo "Output filename for network error = $RESULTS_DIR$ANN_ERROR1"
echo "Output filename for network accuracy = $RESULTS_DIR$ANN_ACCURACY1"
echo "Output filename for k-NN accuracy = $RESULTS_DIR$KNN_ACCURACY1"
echo
echo "== Parameters for experiment #2 =="
echo "Configuration file = $CONF2"
echo "Dataset = $DATA2"
echo "Training samples percentage = $RATIO2"
echo "Output filename for network error = $RESULTS_DIR$ANN_ERROR2"
echo "Output filename for network accuracy = $RESULTS_DIR$ANN_ACCURACY2"
echo "Output filename for k-NN accuracy = $RESULTS_DIR$KNN_ACCURACY2"
echo
echo "== Parameters for experiment #3 =="
echo "Configuration file = $CONF3"
echo "Dataset = $DATA3"
echo "Training samples percentage = $RATIO3"
echo "Output filename for network error = $RESULTS_DIR$ANN_ERROR3"
echo "Output filename for network accuracy = $RESULTS_DIR$ANN_ACCURACY3"
echo "Output filename for k-NN accuracy = $RESULTS_DIR$KNN_ACCURACY3"
echo
read -p "Are these values correct? (y/n) " -n 1
echo
echo

function run()
{
  echo "Startins runs for steel faults dataset."
  for SEED in {1..30}
  do
    bash run.sh $CONF1 $DATA1 $SEED $RATIO1 $RESULTS_DIR$SEED$ANN_ERROR1 $RESULTS_DIR$SEED$ANN_ACCURACY1 $RESULTS_DIR$KNN_ACCURACY1
  done

  echo "Startins runs for steel faults datasubset."
  for SEED in {1..30}
  do
    bash run.sh $CONF2 $DATA2 $SEED $RATIO2 $RESULTS_DIR$SEED$ANN_ERROR2 $RESULTS_DIR$SEED$ANN_ACCURACY2 $RESULTS_DIR$KNN_ACCURACY2
  done

  echo "Startins runs for digit recognition dataset."
  for SEED in {1..30}
  do
    bash run.sh $CONF3 $DATA3 $SEED $RATIO3 $RESULTS_DIR$SEED$ANN_ERROR3 $RESULTS_DIR$SEED$ANN_ACCURACY3 $RESULTS_DIR$KNN_ACCURACY3
  done
}

if [[ $REPLY =~ ^[Yy]$ ]]; then
  run
fi

unset run
