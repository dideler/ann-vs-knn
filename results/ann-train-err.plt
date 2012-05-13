#!/usr/bin/gnuplot -persist

# @author ideler.dennis@gmail.com (Dennis Ideler)

set autoscale
unset log
unset label
set title "Network Error over Time"
set xlabel "Time (epochs)"
set ylabel "Network Error (sum of squared output errors)"
set grid
plot    "avg_ann_error_faults.dat" using 1:2 title 'ANN Average Error on Faults Diagnosis' with lines, \
        "avg_ann_error_faults-subset.dat" using 1:2 title 'ANN Average Error on Faults Diagnosis (subset)' with lines, \
        "avg_ann_error_digits.dat" using 1:2 title 'ANN Average Erroron Digit Recognition' with lines
