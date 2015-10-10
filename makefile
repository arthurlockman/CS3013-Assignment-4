all: main

main: server.o main.o
	g++ main.o server.o -lpthread -o proj4
	rm *.o

main.o: main.cpp server.h
	g++ -std=c++0x -c main.cpp

server.o: server.h
	g++ -std=c++0x -c server.cpp

clean:
	rm proj4
