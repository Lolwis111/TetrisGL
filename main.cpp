#include "Header/Program.h"

int main(int argc, char **argv)
{
    Program *tetris = new Program(); // create new instance of the game

    int r = tetris->run(argc, argv); // run the game

    delete(tetris); // delete the instance after execution

    return r; // return error code
}
