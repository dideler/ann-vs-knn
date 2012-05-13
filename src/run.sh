#!/usr/bin/env bash

# (C) 2012 Dennis Ideler
#
# Performs a single run on the ANN and K-NN.
# Example:
#   $ bash run.sh 1 75 ann-err.out ann-acc.out knn-acc.out
#
# See README.txt for more info on parameters.

set -e # Error checking.
set -u # Parameter checking.

CONF="$1"
DATA="$2"
SEED="$3"
RATIO="$4"
ANN_ERROR="$5"
ANN_ACCURACY="$6"
ANN_TEST_ACCURACY="$7"
KNN_ACCURACY="$8"

# For verbose output, use the -o and -v tags (warning: running time will increase).
./ann-vs-knn -c $CONF -d $DATA -s $SEED -t $RATIO -e $ANN_ERROR -a $ANN_ACCURACY -z $ANN_TEST_ACCURACY -k $KNN_ACCURACY -p
