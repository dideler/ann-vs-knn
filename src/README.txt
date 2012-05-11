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

-e ann_train_error_filename
  Name of the file where you want the ANN's training error data to be saved to.
  Optional tag, but argument required if provided.
  Default is ann-train-error.out
  Ex: -e train-error.out

-a ann_train_accuracy_filename
  Name of the file where you want the ANN's training accuracy data to be saved to.
  Optional tag, but argument required if provided.
  Default is ann-train-accuracy.out
  Ex: -a train-accuracy.out

-z ann_test_accuracy_filename
  Name of the file where you want the ANN's testing accuracy data to be saved to.
  Optional tag, but argument required if provided.
  Default is ann-test-accuracy.out
  Ex: -z test-accuracy.out

-k knn_accuracy_filename
  Name of the file where you want the k-NN's accuracy data to be saved to.
  Optional tag, but argument required if provided.
  Default is knn-error.out
  Ex: -k knn-acc-steel.out

-p
  Flag for writing results to files that are ready to be plotted with gnuplot.
  Optional tag. Does not accept arguments.
  Default is not set.

-o
  Flag for program output. Displays things such as accuracy of each epoch.
  Redundant to enable if you are also printing to file with -p tag.
  Useful to enable when doing multiple runs, to not clutter stdout.
  Optional tag. Does not accept arguments.
  Default is not set.

-v
  Flag for verbose output. Displays the results of each classification attempt.
  Optional tag. Does not accept arguments.
  Default is not set.
