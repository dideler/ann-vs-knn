# Artificial Neural Network v0.1 Makefile
# 
# (C) 2012 Dennis Ideler <ideler.dennis at gmail>
# 
# www.cs.umd.edu/class/fall2002/cmsc214/Tutorial/makefile.html
#
# TODO: remove debug from cflags and include separately.
# 			allows for optimized and debugged versions.

#CC = gcc
CC = g++
OBJS = Neurode.o Layer.o NeuralNet.o
DEBUG = -g
OPTIMIZE = -O3
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

all: ann knn clean

ann: $(OBJS)
	$(CC) main.cpp $(LFLAGS) $(OBJS) -o ann

knn:
	@echo TODO

Neurode.o: Neurode.h Neurode.cpp connections.h Layer.h NeuralNet.h
	$(CC) $(CFLAGS) Neurode.cpp

Layer.o: Layer.h Layer.cpp Neurode.h
	$(CC) $(CFLAGS) Layer.cpp

NeuralNet.o: NeuralNet.h NeuralNet.cpp Layer.h Neurode.h
	$(CC) $(CFLAGS) NeuralNet.cpp

clean:
	\rm *.o

# Also remove the executables and the output files.
cleanest: clean
	\rm ann knn *.dat
