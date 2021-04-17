
CC = g++
LIBS = `pkg-config --libs opencv`
CFLAGS = `pkg-config --cflags opencv` -Iheaders #-Wall -Wextra -funroll-loops
OBJS = main.o image.o card.o place.o kernel.o table.o blur.o edge.o player.o shape.o

all: edgetest

edgetest: $(OBJS)
	$(CC) $(OBJS) -o edgetest $(LIBS)

place.o:  headers/place.hpp place.cpp
	$(CC) $(CFLAGS) $(LIBS) -c place.cpp -o place.o

kernel.o: headers/Kernel.hpp kernel.cpp
	$(CC) $(CFLAGS) $(LIBS) -c kernel.cpp

blur.o: headers/BlurKernel.hpp BlurKernel.cpp
	$(CC) $(CFLAGS) $(LIBS) -c BlurKernel.cpp -o blur.o

edge.o: headers/EdgeKernel.hpp EdgeKernel.cpp
	$(CC) $(CFLAGS) $(LIBS) -c EdgeKernel.cpp -o edge.o

main.o: main.cpp
	$(CC) $(CFLAGS) $(LIBS) -c main.cpp

image.o: headers/image.hpp image.cpp
	$(CC) $(CFLAGS) $(LIBS) -c image.cpp

card.o: card.cpp headers/card.hpp
	$(CC) $(CFLAGS) $(LIBS)  -c card.cpp

table.o: Table.cpp headers/Table.hpp
	$(CC) $(CFLAGS) $(LIBS) -c Table.cpp -o table.o

player.o: headers/Player.hpp Player.cpp
	$(CC) $(CFLAGS) $(LIBS) -c Player.cpp -o player.o

shape.o: headers/Shape.hpp Shape.cpp
	$(CC) $(CFLAGS) $(LIBS) -c Shape.cpp -o shape.o

clean:
	rm *.o edgetest
