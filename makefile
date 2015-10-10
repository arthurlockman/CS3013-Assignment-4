all: main

main: server.o crawler.o main.o
	g++ main.o server.o crawler.o -lpthread -o proj4
	rm *.o

main.o: main.cpp server.h
	g++ -std=c++0x -c main.cpp

server.o: server.h crawler.h
	g++ -std=c++0x -c server.cpp

crawler.o: crawler.h server.h
	g++ -std=c++0x -c crawler.cpp

clean:
	rm proj4
