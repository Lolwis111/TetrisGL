#ifndef PROGRAM_H_
#define PROGRAM_H_

#include "BlockManager.h"

class Program
{
    public:
        int run(int argc, char **argv);
    private:
        bool pollEvents(void);
        bool isPaused;
        bool blink;
        BlockManager *manager;
};

#endif
