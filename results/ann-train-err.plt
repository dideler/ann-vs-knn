#!/usr/bin/gnuplot -persist

# @author ideler.dennis@gmail.com (Dennis Ideler)

#set terminal postscript eps color lw 1.5 "Helvetica" 18
#set out 'network-error.eps'
set autoscale
unset log
unset label
set title "Average Network Error over Time"
set xlabel "Time (epochs)"
set ylabel "Network Error (sum of squared output errors)"
set grid
plot    "avg_ann_error_faults.dat" using 1:2 title 'Faults Diagnosis' with lines, \
        "avg_ann_error_faults-subset.dat" using 1:2 title 'Faults Diagnosis (subset)' with lines, \
        "avg_ann_error_digits.dat" using 1:2 title 'Digit Recognition' with lines
