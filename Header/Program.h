#ifndef PROGRAM_H_
#define PROGRAM_H_

#include "BlockManager.h"

class Program
{
    public:
        int run(int argc, char **argv); // main-function of the game
    private:
        bool pollEvents(void); // processes the SDL events
        BlockManager manager;  // instance of the BlockManager
};

#endif
