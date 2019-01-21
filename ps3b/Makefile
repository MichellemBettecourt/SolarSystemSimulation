BODY = body.cpp body.hpp
MAIN = main.cpp
NBODY = body.o main.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -Werror -ansi -pedantic
LFLAGS = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system

all: body.o main.o NBody

clean:
	rm -f *.o NBody

body.o: $(BODY)
	g++ $(CFLAGS) -c body.cpp

main.o: $(MAIN)
	g++ $(CFLAGS) -c main.cpp

NBody: $(NBODY)
	$(CC) $(NBODY) -o NBody $(LFLAGS)
