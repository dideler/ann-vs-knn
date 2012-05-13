#!/usr/bin/gnuplot -persist

# The -persist option keeps the graph on the screen, while gnuplot exits.
#
# A gnuplot script for plotting the training results per network epoch.
# To generate the plot:
#   $ gnuplot
#   > load 'filename.plt'
# or
#   $ gnuplot -persist filename.plt
# or (if script has a shebang line and executable permissions)
#   $ ./filename.plt
#
# @author ideler.dennis@gmail.com (Dennis Ideler)

set autoscale  # Scale axes automatically.
unset log  # Remove any log-scaling.
unset label  # Remove any previous labels.
set title "Network Accuracy over Time"
set xlabel "Time (epochs)"
set ylabel "Accuracy (% classified correctly)"
#set xrange [:]
#set yrange [0:] # Set y-axis lowerbound to 0, let gnuplot determine upperbound.
set grid
#set label "start of convergence" at 54,32
#set arrow from 57,30 to 55,22
#set arrow from 202,20 to 202,11
plot    "avg_ann_accuracy_digits.dat" using 1:2 title 'ANN Average Accuracy on Digit Recognition' with lines \
        "avg_ann_accuracy_faults.dat" using 1:2 title 'ANN Average Accuracy on Faults Diagnosis' with lines \
        "avg_ann_accuracy_faults-subset.dat" using 1:2 title 'ANN Average Accuracy on Faults Diagnosis (subset)' with lines

# To plot multiple files, use '\' at the end of the line (with no space behind)
# and continue with the next file on a new line.
