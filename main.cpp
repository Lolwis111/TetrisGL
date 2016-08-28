#include "Header/Program.h"

int main(int argc, char **argv)
{
    Program *tetris = new Program();
    int r = tetris->run(argc, argv);
    delete(tetris);

    return r;
}
