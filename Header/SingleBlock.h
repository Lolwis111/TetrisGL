#ifndef SINGLEBLOCK_H_
#define SINGLEBLOCK_H_
#include "../Header/GameBlock.h"

// a 1x1 block derrived from the base-block
class SingleBlock : public GameBlock
{
    public:
        SingleBlock(const GameBlock &src) : GameBlock(src) { }
        SingleBlock(GLfloat x, GLfloat y, GLfloat r, GLfloat g, GLfloat b);
        ~SingleBlock();

        void draw();
        int getBoundaryLeft();
        int getBoundaryRight();
        int getBoundaryTop();
        int getBoundaryBottom();
};
#endif
