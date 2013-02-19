CC = g++

LIBS = -lglut -lGLU -lGL -I.
OBJS = matrix.o vector.o transformations.o
CFLAGS = -Wall

all: $(OBJS)
	$(CC) main.cpp $(LIBS) $(OBJS) $(CFLAGS) -o cgprog

matrix.o: matrix.cpp matrix.h
	$(CC) -c matrix.cpp $(CFLAGS) -o matrix.o

vector.o: vector.cpp vector.h
	$(CC) -c vector.cpp $(CFLAGS) -o vector.o

transformations.o: transformations.cpp transformations.h
	$(CC) -c transformations.cpp $(CFLAGS) -o transformations.o

refer: refer.cpp
	$(CC) refer.cpp $(LIBS) $(CFLAGS) -o refer

clean:
	rm cgprog

