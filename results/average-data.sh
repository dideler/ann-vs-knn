#!/usr/bin/env bash

./rob_average avg *ann-err-faults.out > avg_ann_error_faults.dat
./rob_average avg *ann-err-faults-subset.out > avg_ann_error_faults-subset.dat
./rob_average avg *ann-err-digits.out > avg_ann_error_digits.dat

./rob_average avg *ann-acc-faults.out > avg_ann_accuracy_faults.dat
./rob_average avg *ann-acc-faults-subset.out > avg_ann_accuracy_faults-subset.dat
./rob_average avg *ann-acc-digits.out > avg_ann_accuracy_digits.dat
