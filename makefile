CC=g++
DEPS = bowling_frame.h

all: bowling_frame.o main.o
	$(CC) -std=c++11 bowling_frame.o main.o

bowling: bowling_frame.o $(DEPS)
	$(CC) -c -std=c++11 bowling_frame.cpp

main: main.o $(DEPS)
	$(CC) -c -std=c++11 main.cpp

clean: 
	rm *.o *.out
