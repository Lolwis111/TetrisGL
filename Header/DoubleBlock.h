#ifndef DOUBLEBLOCK_H_
#define DOUBLEBLOCK_H_

#include "../Header/GameBlock.h"
#include <vector>

///
/// A 1x2/2x1 block derrived from the basic-block
class DoubleBlock : public GameBlock
{
    public:
        DoubleBlock(const GameBlock &src) : GameBlock(src) { }
        DoubleBlock(GLfloat x, GLfloat y, GLfloat r, GLfloat g, GLfloat b) : GameBlock(x, y, r, g, b) { }
        ~DoubleBlock();
       
        void draw();
        int getBoundaryLeft() const;
        int getBoundaryRight() const;
        int getBoundaryTop() const;
        int getBoundaryBottom() const;
        bool registerBlock(bool *field);
        
        DoubleBlock* clone() const;

        GLfloat getDistance() const;
};

#endif
