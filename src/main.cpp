/* Artificial Neural Networks for a Classification Problem.
 * Assignment 2 for COSC 4P76 - Machine Learning
 *
 * File:   main.cpp
 * Author: Dennis Ideler <di07ty at brocku.ca>
 *
 * Created on April 2011
 * Modified on April 2012
 * 
 * Style guides used (in order of preference):
 * http://google-styleguide.googlecode.com/svn/trunk/cppguide.xml
 * http://geosoft.no/development/cppstyle.html
 */

#include <cstdlib>  // abort et al
#include <fstream>  // File stream (in and out)
#include <string>
#include <cstring>
#include <cstdio>
#include <limits>  // numeric_limits
#include <sstream>  // stringstream
#include <algorithm>  // random_shuffle
#include <deque>
#include <cassert>
#include <vector>
#include <cmath>
#include <iostream>
#include <unistd.h>  // getopt
#include "NeuralNet.h"
using namespace std;

// NOTE: Remember to use -> when referencing a pointer to an object.
//       Use . when referencing the object.

struct UserParameters
{
  double lower_weight_range;
  double upper_weight_range;
  double learning_rate;
  double momentum;
  double max_error;
  int num_instances;
  int num_epochs;
  int num_features;  // Also the number of input nodes.
  int num_hidden_nodes;
  int num_classes;  // Also the number of output nodes.
  int training_ratio;
  int seed;
  string learning_rule;
  string hidden_activation_function;
  string output_activation_function;
  bool bias;  // TODO: Implement bias.
  bool plot;  // Graph data.
  
  UserParameters()  // Set default values.
  {
    lower_weight_range = -1.0;
    upper_weight_range = 1.0;
    learning_rate = 0.1;
    momentum = 0.05;
    max_error = 0.1;
    num_epochs = 800;
    num_features = 27;
    num_hidden_nodes = 50;
    num_classes = 7;
    training_ratio = 80;
    seed = time(NULL);
    learning_rule = "backprop";
    hidden_activation_function = "logistic";
    output_activation_function = "logistic";
    bias = false;
    plot = false;
  }
} params;  // A global struct object is much easier than passing many args.


/**
 * Writes results to an output file in a gnuplot friendly format.
 * 
 * @param data   Array of stored data from each epoch which needs to be printed
 */
void writePlotData(const double* data, string file_name)
{
  ofstream file_stream;  // Output file stream - collects data to graph runs.

  file_stream.open(file_name.c_str());
  if (file_stream.is_open())
  {
//    file_stream << "# Percentage of correctly classified digits per training"
//                   "epoch\n#\tEpoch\tHit-Percentage\n";
    for (int epoch = 0; epoch < params.num_epochs; ++epoch)
    {
      file_stream << "\t" << epoch+1 << "\t\t" << data[epoch] << "\n";
    }
  }
  else
  {
    cerr << "(!) Unable to open file\n";
  }
  file_stream.close();
}


/**
 * Initialize the ANN and its weights. Train it, then test the trained ANN.
 *
 * @param error_file    The output file where network error will be saved to.
 * @param accuracy_file The output file where network accuracy will be saved to.
 * @param training_set  The set of data that the neural net will train on
 * @param testing_set   The set of data that the neural net will be tested on
 */
void runNeuralNet(string network_error_file, string accuracy_file,
                  vector< vector<float> > training_set,
                  vector< vector<float> > testing_set)
{
  //  Construct the Artificial Neural Net and initialize weighted connections.
  NeuralNet* ann = new NeuralNet(params.num_features,
                                 params.num_hidden_nodes,
                                 params.num_classes);

  ann->initWeights(params.num_features,
                   params.num_hidden_nodes,
                   params.lower_weight_range,
                   params.upper_weight_range);

  cout << "=== Training Neural Net\n";
  ann->train(training_set,
             params.num_epochs,
             params.hidden_activation_function.c_str(),
             params.output_activation_function.c_str(),
             params.learning_rate,
             params.momentum,
             params.max_error);
  cout << "\n=== Testing Neural Net\n";
  ann->test(testing_set,
            params.hidden_activation_function.c_str(),
            params.output_activation_function.c_str());
  
  if (params.plot)  // Write plot data if flag is set.
    writePlotData(ann->get_all_hit_percentage(), accuracy_file);
  writePlotData(ann->get_all_network_error(), network_error_file);
  
  ann->~NeuralNet();  // Le delete.
}


/**
 * Reads in the user parameters from a specialized configuration file.
 *
 * @param file_name   Name of the configuration file to be read
 */
void readUserParameters(string file_name)
{
  char line[256];
  ifstream file_stream(file_name.c_str());
  if (file_stream.is_open())
  {
    cout << "\n== Loading the following network parameters:\n\n";
    for (int i = 1; file_stream.good();)
    {
      file_stream.getline(line, 256);
      if (line[0] != '#' && line[0] != '\0')  // If not a comment or empty line.
      {
        switch (i)  // Extract all user parameters, one at a time.
        {
          case 1:  // Number of input units.
            params.num_features = atoi(line);
            cout << "Number of inputs:\t\t" << params.num_features << "\n";
            break;
          case 2:  // Number of hidden units.
            params.num_hidden_nodes = atoi(line);
            cout << "Number of hiddens:\t\t" << params.num_hidden_nodes << "\n";
            break;
          case 3:  // Number of output units.
            params.num_classes = atoi(line);
            cout << "Number of outputs:\t\t" << params.num_classes << "\n";
            break;
          case 4:  // Learning rule.
            params.learning_rule = line;
            cout << "Learning rule:\t\t\t" << params.learning_rule << "\n";
            break;
          case 5:  // Lower weight range.
            params.lower_weight_range = atof(line);
            cout << "Lower weight range:\t\t" << params.lower_weight_range << "\n";
            break;
          case 6:  // Upper weight range.
            params.upper_weight_range = atof(line);
            cout << "Upper weight range:\t\t" << params.upper_weight_range << "\n";
            break;
          case 7: // Learning rate.
            params.learning_rate = atof(line);
            cout << "Learning rate:\t\t\t" << params.learning_rate << "\n";
            break;
          case 8:  // Momentum.
            params.momentum = atof(line);
            cout << "Momentum:\t\t\t" << params.momentum << "\n";
            break;
          case 9:  // Bias.
            params.bias = atoi(line);
            cout << "Bias:\t\t\t\t" << params.bias << "\n";
            break;
          case 10:  // Activation function for hidden units.
            params.hidden_activation_function = line;
            cout << "Activation for hidden units:\t"
                 << params.hidden_activation_function << "\n";
            break;
          case 11:  // Activation function for output units.
            params.output_activation_function = line;
            cout << "Activation for output units:\t"
                 << params.output_activation_function << "\n";
            break;
          case 12:  // Number of epochs.
            // 1 epoch is the presentation of the entire training set to the NN.
            params.num_epochs = atoi(line);
            cout << "Number of epochs:\t\t" << params.num_epochs << "\n";
            break;
          case 13:  // Max error.
            params.max_error = atof(line);
            cout << "Max error:\t\t\t" << params.max_error << "%\n\n";
            break;
          default:
            cerr << "(!) Too many parameters specified or comment without tag.\n";
            assert(false);
        }
        ++i;
      }
    }
  }
  else
  {
    cerr << "(!) Unable to open file.\n";
    abort();
  }
}


/**
 * Normalizes the sample data. All numeric variables are scaled to a range of
 * [0,1]. All parameters should have the same scale for a fair comparison.
 * Note: More efficient if done within readData(), but complicates the code.
 * See: ftp://ftp.sas.com/pub/neural/FAQ2.html#A_std
 * See: http://www.dataminingblog.com/standardization-vs-normalization
 * 
 * @param db_table  Database table with all the example cases to be normalized.
 */
void normalizeData(vector< vector<float> >& db_table)
{
  // TODO: consider Winsorizing the data.
  // “Winsorizing” data simlpy means clamping the extreme values.
  // Similar to trimming the data, except that instead of discarding data:
  // values greater than the specified upper limit are replaced with the
  // upper limit, those below the lower limit are replaced with the lower limit.
  // Often, the specified range is indicate in terms of percentiles of the
  // original distribution (like the 5th and 95th percentile).
  // This process is sometimes used to make conventional measures more robust,
  // as in the Winsorized variance.
  
  // If you have outliers in your data set, normalizing your data will certainly
  // scale the “normal” data to a very small interval. Generally, most data sets
  // have outliers. If your data contains several outliers, use standardization.
  
  vector<float> min_values, max_values;
  for (int i = 0; i < params.num_features; ++i)
  {
    min_values.push_back(numeric_limits<float>::max());
    max_values.push_back(numeric_limits<float>::min());
  }
  
  // Search all instances to find the min and max values for each attribute.
  for (int i = 0; i < params.num_instances; ++i)
  {
    // Note: ignores the class data at the end of each instance.
    for (int j = 0; j < params.num_features; ++j)
    { 
      if (db_table[i][j] < min_values[j])  // Update min value for attribute.
        min_values[j] = db_table[i][j];
      if (db_table[i][j] > max_values[j])  // Update max value for attribute.
        max_values[j] = db_table[i][j];
    }
  }
  
  // Scale each attribute value:  x = (x - x_min) / (x_max - x_min)
  for (int i = 0; i < params.num_instances; ++i)
  {
    for (int j = 0; j < params.num_features; ++j)
    {
      db_table[i][j] = (db_table[i][j] - min_values[j]) /
                       (max_values[j] - min_values[j]);
    }
  }
}


/**
 * Shuffles the data set (the instances, not the values) and splits it into
 * a training and testing set. Also ensures that the training set equally covers
 * all the different classifications (to avoid overtraining a certain type).
 *
 * @param db_table        Database table with all the example cases.
 * @param training_set    Training set to be populated with data.
 * @param testing_set     Testing set to be populated with data.
 */
void prepareData(const vector< vector<float> >& db_table,
                 vector< vector<float> >& training_set,
                 vector< vector<float> >& testing_set)
{
  // Assuming the data is ordered by classification type, the data can be
  // partitioned into sets of multiple types. Those sets can then be shuffled.
  // The training set is made by repeatedly choosing a case from each partition
  // until its ratio (training : testing) is covered -- each type will have
  // contributed approximately the same amount of training cases.
  // The remaining cases will then be used for the testing set.

  // Create a table partitioned by classification type.
  vector< deque< vector<float> > > parted_db_table;
  deque< vector<float> > cases; // The cases for every classification type.

  // Make room for all the classes within the parted table.
  for (int i = 0; i < params.num_classes; ++i)
    parted_db_table.push_back(cases);

  // Insert each case into the appropriate partition based on its type.
  int example;
  for (example = 0; example < params.num_instances; ++example)
  {
    // Get the classification of the current instance. Classification data for
    // each example is located after all attribute values.
    int classification;
    for (int i = 0; i < params.num_classes; ++i)
    {
      if (db_table[example][params.num_features + i] == 1)
      {
        classification = i + 1;
        break;
      }
    }
    // Push the instance in the appropriate partition.
    parted_db_table.at(classification - 1).push_back(db_table.at(example));
  }

  // Shuffle every partition.
  for (int i = 0; i < params.num_classes; ++i)
    random_shuffle(parted_db_table.at(i).begin(), parted_db_table.at(i).end());

  // Calculate how many cases (out of the total) each data set gets.
  int num_training_cases = example * (params.training_ratio / 100.0);
  int num_testing_cases = example - num_training_cases;
  cout << "Training cases: " << num_training_cases << "\nTesting cases: "
       << num_testing_cases << "\n";

  // Fills the training set with an equal amount of cases from each partition,
  // by grabbing the first case from each partition and then popping it.
  // Popping used cases ensures they won't be used in the testing set.
  for (int count = 0; count < num_training_cases;)
  {
    for (int i = 0; i < params.num_classes && count < num_training_cases; ++i)
    {
      if (!parted_db_table.at(i).empty()) // Add instance if any left.
      {
        ++count;
        training_set.push_back(parted_db_table.at(i).front());
        parted_db_table.at(i).pop_front();
      }
    }
  }

  // Fill the testing set with the leftover cases in each of the partitions.
  // Order doesn't matter for testing.
  for (int i = 0; i < params.num_classes; ++i)
  {
    while (!parted_db_table.at(i).empty()) 
    {
      testing_set.push_back(parted_db_table.at(i).front());
      parted_db_table.at(i).pop_front();
    }
  }
}


/**
 * Reads in the data from a file and stores it in the table.
 * Expects data to have one instance per line and attribute values separated
 * by whitespace (e.g. tab).
 *
 * @param file      File that contains the dataset.
 * @param db_table	Database that will hold all cases and their input patterns
 */
void readData(string file, vector< vector<float> >& db_table)
{ 
  ifstream file_stream(file.c_str());
  if (file_stream.is_open())
  {
    string line;
    for (int line_num = 0; file_stream.good(); ++line_num)
    {
      getline(file_stream,line);  // Read a single training instance.
      if (line == "") break;
      db_table.push_back(vector<float>()); // Create space for current instance.

      // Split the line into numeric values.
      float attribute;
      istringstream iss(line, istringstream::in);
      while (iss >> attribute)
        db_table.at(line_num).push_back(attribute);
    }
    params.num_instances = static_cast<int>(db_table.size());
    file_stream.close();
  }
  else
  {
    cerr << "(!) Failed to read file - correct path given?\n";
    assert(false);
  }
}


/**
 * @todo FINAL = RELEASE MODE!
 * @todo autoformat code (ALT+SHIFT+F)
 */
int main(int argc, char** argv)
{
  try
  {
    cout << "******************************************************************"
            "*******\nANN for steel classification problem.  "
            "Copyright (C) 2012  Dennis Ideler\n\n"
            "This program comes with ABSOLUTELY NO WARRANTY. "
            "This is free software,\nand you are welcome to redistribute it "
            "under certain conditions.\n**************************************"
            "***********************************\n" << endl;
    
    cout.precision(10);  // Should be enough to not trim values when printing.
    cin.sync_with_stdio(false);  // Increase input speed.

    string config_file = "";
    string dataset_file = "";
    string error_file = "error.dat";
    string accuracy_file = "accuracy.dat";
    int c;

    while ((c = getopt(argc, argv, "c:d:s:t:e:a:p")) != -1)
    {
      switch (c)
      {
        case 'c':  // Configuration file for the ANN.
          config_file = optarg;
          break;
        case 'd':  // Dataset file.
          dataset_file = optarg;
          break;
        case 's':  // Seed for random number generator.
          params.seed = atoi(optarg);
          break;
        case 't':  // Training ratio.
          params.training_ratio = atoi(optarg);
          break;
        case 'e':  // Filename for network error during training (per epoch).
          error_file = optarg;
          break;
        case 'a':  // Filename for network accuracy during training (per epoch).
          accuracy_file = optarg;
          break;
        case 'p':
          params.plot = true;
          break;
        default:
          abort();
      }
    }

    // Arguments that do not require an option (e.g. grep PATTERN).
    for (int index = optind; index < argc; index++)
      printf("Non-option argument %s\n", argv[index]);

    srand(params.seed);

    cout << "config file = " << config_file << ", dataset file = "
         << dataset_file << ", error output file = " << error_file
         << ", accuracy output file = " << accuracy_file << "\n";
    printf("Using random number seed %d\n", params.seed);
    printf("Using training/testing ratio %d : %d\n", params.training_ratio,
           100 - params.training_ratio);

    if (config_file != "") readUserParameters(config_file);
    // Tables to store the complete database, training set, and testing set.
    vector< vector<float> > db_table, training_set, testing_set;
    readData(dataset_file, db_table);
    cout << "Number of instances = " << params.num_instances << "\n";
    normalizeData(db_table);
    prepareData(db_table, training_set, testing_set);
    runNeuralNet(error_file, accuracy_file, training_set, testing_set);
  }
  catch (exception& ex) // TODO: improve exception handling.
  {
    cout << "Some exception occurred!" << endl;
  }

  return 0;
}
