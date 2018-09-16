CC=g++
CFLAGS= -std=c++11 -Wall -pedantic -g
SOURCES= main.cpp Matrix.cpp
DEPS= Matrix.h
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=main

all: $(EXECUTABLE)
	@echo Make has finished.

$(EXECUTABLE): $(OBJECTS)
	$(CC)  $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) -c $*.cpp

clean:
	$(RM) *.o *~ $(EXECUTABLE) CXX = g++
