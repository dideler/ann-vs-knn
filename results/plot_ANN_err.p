# gnuplot script for plotting the training results per epoch.
# To generate the plot, use the command: gnuplot> load 'filename.p'

set autoscale   # scale axes automatically
unset log       # remove any log-scaling
unset label     # remove any previous labels
set title "Network Error over Time"
set xlabel "Time (epochs)"
set ylabel "Network Error (sum of squared output errors)"
#set xrange [:]
#set yrange [0:] # set the y-axis lowerbound to 0, and let gnuplot determine upperbound
set grid
#set label "start of convergence" at 54,32 # indicates convergence on mean fitness of run 1 -TODO use label and arrow in final graphs!
#set arrow from 57,30 to 55,22
#set arrow from 202,20 to 202,11
plot    "avg_nn_error.dat" using 1:2 title 'Error' with lines

# to plot more files, use \ (without a space behind it) to continue on a new line
# using tells gnuplot which columns to take and use for x and yi
