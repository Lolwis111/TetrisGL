CC=g++
CFLAGS=-c -Wall -ggdb
CINCLUDES=-I/usr/include/SDL -I/usr/include/GL
LIBS=-L/usr/lib/x86_64-linux-gnu -lSDL -lGL -lGLU

all: doall

tetris: glwindow.o main.o gameblock.o singleblock.o doubleblock.o blockmanager.o program.o
	$(CC) Blocks/GameBlock.o Blocks/SingleBlock.o Blocks/DoubleBlock.o BlockManager.o GLWindow.o program.o main.o -o TetrisGL $(LIBS)

doall: init tetris cleanRoot cleanBlocks

init:
	rm -f TetrisGL

main.o: main.cpp
	$(CC) $(CFLAGS) $(CINCLUDES) -c main.cpp

program.o: program.cpp
	$(CC) $(CFLAGS) $(CINCLUDES) -c program.cpp

glwindow.o: GLWindow.cpp
	$(CC) $(CFLAGS) $(CINCLUDES) -c GLWindow.cpp

gameblock.o: Blocks/GameBlock.cpp
	$(CC) $(CFLAGS) $(CINCLUDES) -c Blocks/GameBlock.cpp -o Blocks/GameBlock.o

singleblock.o: Blocks/SingleBlock.cpp
	$(CC) $(CFLAGS) $(CINCLUDES) -c Blocks/SingleBlock.cpp -o Blocks/SingleBlock.o

doubleblock.o: Blocks/DoubleBlock.cpp
	$(CC) $(CFLAGS) $(CINCLUDES) -c Blocks/DoubleBlock.cpp -o Blocks/DoubleBlock.o

blockmanager.o: BlockManager.cpp
	$(CC) $(CFLAGS) $(CINCLUDES) -c BlockManager.cpp

cleanRoot:
	rm -rf *.o

cleanBlocks:
	rm -rf Blocks/*.o
