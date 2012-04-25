#!/usr/bin/env bash

gcc -O3 -c Neurode.cpp Layer.cpp NeuralNet.cpp
g++ main.cpp -O3 NeuralNet.o Neurode.o Layer.o -g
