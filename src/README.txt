This version is specially compiled to run on the lab computers in J-block.

README.txt
  This masterpiece of a document.

Makefile
  Used to build the program.

compile.sh (deprecated - do not use)
  Used to compile the program.

run.sh
  Used to run the program. View script for more info.

*.conf
  Configuration files for the classifiers.

TODO: example compilation and execution

Program arguments:

-c config_file
  The configuration file with the ANN parameters.
  Required tag and argument. (TODO: make optional)
  Ex: -c ann.conf

-d dataset
  The problem dataset that you want to create a learning model for.
  Required tag and argument.
  Ex: -d steelfaults.data

-s seed
  Seed for the random number generator.
  Optional tag, but argument required if provided.
  Default is system time.
  Ex: -s 4

-t training_ratio
  Training ratio in the training/testing split.
  Optional tag, but argument required if provided.
  Default is 80%.
  Ex: -t 70

-e error_output_filename
  Name of the file where you want the ANN's training error data to be saved to.
  Optional tag, but argument required if provided.
  Default is error.dat.
  Ex: -e error1.dat

-a accuracy_output_filename
  Name of the file where you want the ANN's accuracy data to be saved to.
  Optional tag, but argument required if provided.
  Default is accuracy.dat.
  Ex: -a accuracy2.dat

-p
  Flag for writing results to files that are ready to be plotted with gnuplot.
  Optional tag.
  Default is not set.
  Ex: -p  

