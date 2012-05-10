# Artificial Neural Network vs K-Nearest Neighbour v1.0 Makefile
# 
# (C) 2012 Dennis Ideler <ideler.dennis at gmail>
# 
# www.cs.umd.edu/class/fall2002/cmsc214/Tutorial/makefile.html
#
# TODO: remove debug from cflags, make it its own variable.

#CC = gcc
CC = g++
OBJS = Neurode.o Layer.o NeuralNet.o NearestNeighbour.o
DEBUG = -g
OPTIMIZE = -O3
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

all: ann-vs-knn clean

all-optimized: ann-vs-knn-optimized clean

ann-vs-knn: $(OBJS)
	$(CC) main.cpp $(LFLAGS) $(OBJS) -o ann-vs-knn

ann-vs-knn-optimized: $(OBJS)
	$(CC) main.cpp $(LFLAGS) $(OPTIMIZE) $(OBJS) -o ann-vs-knn

Neurode.o: Neurode.h Neurode.cpp connections.h Layer.h NeuralNet.h
	$(CC) $(CFLAGS) $(OPTIMIZE) Neurode.cpp

Layer.o: Layer.h Layer.cpp Neurode.h
	$(CC) $(CFLAGS) $(OPTIMIZE) Layer.cpp

NeuralNet.o: NeuralNet.h NeuralNet.cpp Layer.h Neurode.h
	$(CC) $(CFLAGS) $(OPTIMIZE) NeuralNet.cpp

NearestNeighbour.o: NearestNeighbour.h
	$(CC) $(CFLAGS) $(OPTIMIZE) NearestNeighbour.cpp

clean:
	\rm *.o ../results/*.out

# Also remove the executables and the output files.
cleanest: clean
	\rm ann-vs-knn
