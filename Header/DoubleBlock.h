#ifndef DOUBLEBLOCK_H_
#define DOUBLEBLOCK_H_

#include "../Header/GameBlock.h"

///
/// A 1x2/2x1 block derrived from the basic-block
class DoubleBlock : public GameBlock
{
    public:
        DoubleBlock(const GameBlock &src) : GameBlock(src) { }
        DoubleBlock(GLfloat x, GLfloat y, GLfloat r, GLfloat g, GLfloat b) : GameBlock(x, y, r, g, b) { }
        ~DoubleBlock();

        void draw();
        int getBoundaryLeft();
        int getBoundaryRight();
        int getBoundaryTop();
        int getBoundaryBottom();
};

#endif
