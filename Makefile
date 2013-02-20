CC = g++

LIBS = -lglut -lGLU -lGL -I.
OBJS = matrix.o vector.o transformations.o \
	objLoader.o obj_parser.o list.o string_extra.o
CFLAGS = -Wall

all: $(OBJS)
	$(CC) main.cpp $(LIBS) $(OBJS) $(CFLAGS) -o cgprog

matrix.o: matrix.cpp matrix.h
	$(CC) -c matrix.cpp $(CFLAGS) -o matrix.o

vector.o: vector.cpp vector.h
	$(CC) -c vector.cpp $(CFLAGS) -o vector.o

transformations.o: transformations.cpp transformations.h
	$(CC) -c transformations.cpp $(CFLAGS) -o transformations.o

objLoader.o: objLoader.h objLoader.cpp
	$(CC) -c objLoader.cpp $(CFLAGS) -o objLoader.o

obj_parser.o: obj_parser.h obj_parser.cpp
	$(CC) -c obj_parser.cpp $(CFLAGS) -o obj_parser.o

list.o: list.h list.cpp
	$(CC) -c list.cpp $(CFLAGS) -o list.o

string_extra.o: string_extra.h string_extra.cpp
	$(CC) -c string_extra.cpp $(CFLAGS) -o string_extra.o

refer: refer.cpp
	$(CC) refer.cpp $(LIBS) $(CFLAGS) -o refer

clean:
	rm cgprog

