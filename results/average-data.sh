#!/usr/bin/env bash

# Average the network training error files.
./rob_average avg *ann-err-faults.out > avg_ann_error_faults.dat
./rob_average avg *ann-err-faults-subset.out > avg_ann_error_faults-subset.dat
./rob_average avg *ann-err-digits.out > avg_ann_error_digits.dat

# Average the network testing accuracy files.
./rob_average avg *ann-acc-faults.out > avg_ann_accuracy_faults.dat
./rob_average avg *ann-acc-faults-subset.out > avg_ann_accuracy_faults-subset.dat
./rob_average avg *ann-acc-digits.out > avg_ann_accuracy_digits.dat

# Average the network testing accuracy files.
./avg.py ann-test-acc-faults.out
./avg.py ann-test-acc-faults-subset.out
./avg.py ann-test-acc-digits.out

# Average the k-nn accuracy files.
./avg.py knn-acc-faults.out
./avg.py knn-acc-faults-subset.out
./avg.py knn-acc-digits.out
