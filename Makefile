CC=g++
AR=ar
CFLAGS=-c -Wall -g #-O3 -ggdb
CINCLUDES=-I/usr/include/SDL -I/usr/include/GL
LIBS=-L/usr/lib/x86_64-linux-gnu -lSDL -lGL -lGLU

all: init tetris cleanRoot cleanBlocks


tetris: glwindow.o main.o blocks blockmanager.o program.o
	$(CC) BlockManager.o GLWindow.o program.o main.o Blocks/Blocks.a -o TetrisGL $(LIBS)


main.o: main.cpp
	$(CC) $(CFLAGS) $(CINCLUDES) -c main.cpp

program.o: program.cpp
	$(CC) $(CFLAGS) $(CINCLUDES) -c program.cpp

glwindow.o: GLWindow.cpp
	$(CC) $(CFLAGS) $(CINCLUDES) -c GLWindow.cpp



blocks: gameblock.o singleblock.o doubleblock.o
	$(AR) rvs Blocks/Blocks.a Blocks/GameBlock.o Blocks/SingleBlock.o Blocks/DoubleBlock.o


gameblock.o: Blocks/GameBlock.cpp
	$(CC) $(CFLAGS) $(CINCLUDES) -c Blocks/GameBlock.cpp -o Blocks/GameBlock.o

singleblock.o: Blocks/SingleBlock.cpp
	$(CC) $(CFLAGS) $(CINCLUDES) -c Blocks/SingleBlock.cpp -o Blocks/SingleBlock.o

doubleblock.o: Blocks/DoubleBlock.cpp
	$(CC) $(CFLAGS) $(CINCLUDES) -c Blocks/DoubleBlock.cpp -o Blocks/DoubleBlock.o


blockmanager.o: BlockManager.cpp
	$(CC) $(CFLAGS) $(CINCLUDES) -c BlockManager.cpp



init:
	rm -f TetrisGL

cleanRoot:
	rm -rf *.o

cleanBlocks:
	rm -rf Blocks/*.o;rm -rf Blocks/Blocks.a
