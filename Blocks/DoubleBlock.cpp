/*
 * Class derriving from GameBlock for drawing a 1x2/2x1 block
 */

#include "../Header/Base.h"

#ifdef DOUBLEBLOCKS

#include "../Header/DoubleBlock.h"
#include "gl.h"
#include "glu.h"
#include "math.h"

DoubleBlock::~DoubleBlock()
{
    
}

///
/// draws the block accordingly
void DoubleBlock::draw()
{
    glPushMatrix(); // save the current matrix (to only move the block)
    
    glTranslatef(_x, _y, -1.4); // move to the given coordinates
    glColor3f(_r, _g, _b);      // set the color

    // a 2x1/1x2 block consists of two 1x1 blocks

    glBegin(GL_QUADS); // draw the first block
        // down 1
        glVertex3f(-0.1, -0.1, +0.1);
        glVertex3f(+0.1, -0.1, +0.1);
        glVertex3f(+0.1, -0.1, -0.1);
        glVertex3f(-0.1, -0.1, -0.1);

        // up 1
        glVertex3f(-0.1, +0.1, +0.1);
        glVertex3f(+0.1, +0.1, +0.1);
        glVertex3f(+0.1, +0.1, -0.1);
        glVertex3f(-0.1, +0.1, -0.1);

        // front 1
        glVertex3f(-0.1, +0.1, +0.1);
        glVertex3f(+0.1, +0.1, +0.1);
        glVertex3f(+0.1, -0.1, +0.1);
        glVertex3f(-0.1, -0.1, +0.1);

        // back 1
        glVertex3f(-0.1, +0.1, -0.1);
        glVertex3f(+0.1, +0.1, -0.1);
        glVertex3f(+0.1, -0.1, -0.1);
        glVertex3f(-0.1, -0.1, -0.1);

        // left 1
        glVertex3f(+0.1, -0.1, +0.1);
        glVertex3f(+0.1, +0.1, +0.1);
        glVertex3f(+0.1, +0.1, -0.1);
        glVertex3f(+0.1, -0.1, -0.1);

        // right 1
        glVertex3f(-0.1, -0.1, +0.1);
        glVertex3f(-0.1, +0.1, +0.1);
        glVertex3f(-0.1, +0.1, -0.1);
        glVertex3f(-0.1, -0.1, -0.1);
    glEnd();

    glPopMatrix(); // restore the matrix

    glPushMatrix(); // save the matrix again

    // determine wether to draw the second next to the first one or on top of it
    if(_isVertical) glTranslatef(_x, _y + 0.2f, -1.4f);  
    else glTranslatef(_x + 0.2f, _y, -1.4f);

    glBegin(GL_QUADS);
        // down 2
        glVertex3f(-0.1, -0.1, +0.1);
        glVertex3f(+0.1, -0.1, +0.1);
        glVertex3f(+0.1, -0.1, -0.1);
        glVertex3f(-0.1, -0.1, -0.1);

        // up 2
        glVertex3f(-0.1, +0.1, +0.1);
        glVertex3f(+0.1, +0.1, +0.1);
        glVertex3f(+0.1, +0.1, -0.1);
        glVertex3f(-0.1, +0.1, -0.1);

        // front 2
        glVertex3f(-0.1, +0.1, +0.1);
        glVertex3f(+0.1, +0.1, +0.1);
        glVertex3f(+0.1, -0.1, +0.1);
        glVertex3f(-0.1, -0.1, +0.1);

        // back 2
        glVertex3f(-0.1, +0.1, -0.1);
        glVertex3f(+0.1, +0.1, -0.1);
        glVertex3f(+0.1, -0.1, -0.1);
        glVertex3f(-0.1, -0.1, -0.1);

        // left 2
        glVertex3f(+0.1, -0.1, +0.1);
        glVertex3f(+0.1, +0.1, +0.1);
        glVertex3f(+0.1, +0.1, -0.1);
        glVertex3f(+0.1, -0.1, -0.1);

        // right 2
        glVertex3f(-0.1, -0.1, +0.1);
        glVertex3f(-0.1, +0.1, +0.1);
        glVertex3f(-0.1, +0.1, -0.1);
        glVertex3f(-0.1, -0.1, -0.1);
    glEnd();

    glPopMatrix(); // restore the matrix from the second block

}

int DoubleBlock::getBoundaryLeft() const
{
    return (int)(ceil((_x + 0.6) * 5)); // remap the x-coordinate to a column
}

int DoubleBlock::getBoundaryRight() const
{
    if(this->_isVertical) 
    {
        return getBoundaryLeft(); // left rightcolumn is usually the same as the right
    }
    else 
    {
        return getBoundaryLeft() + 1; // in horizontal-mode the rightcolumn is next to the left one
    }
}

int DoubleBlock::getBoundaryTop() const
{
    if(this->_isVertical) 
    {
        return getBoundaryBottom() + 1; // usually the upper row is above the bottom one
    }
    else 
    {
        return getBoundaryBottom(); // in horizontal-mode its the same as the lower one
    }
}

int DoubleBlock::getBoundaryBottom() const
{
    if(_y <= 0.101) return 0;       // remap the y-coordinate to a row
    else if(_y <= 0.301) return 1;
    else if(_y <= 0.501) return 2;
    else if(_y <= 0.701) return 3;
    else if(_y <= 0.901) return 4;
    else if(_y <= 1.101) return 5;
    else if(_y <= 1.301) return 6;
    else if(_y <= 1.501) return 7;
    else return 8;
}

bool DoubleBlock::registerBlock(bool* field)
{
    //TODO not registering correctly

    bool ret = false;
    int index = 0;

    if(this->_isVertical)
    {
        index = (getBoundaryBottom() * Y_BLOCKS) + getBoundaryLeft(); // register a block at x;y and x;y+1

        if(field[index] == false && field[index + Y_BLOCKS] == false)
        {
            field[index] = true;
            field[index + Y_BLOCKS] = true;

            ret = true;
        }
        else
        {
            ret = false;
        }
    }
    else
    {
        index = (getBoundaryBottom() * Y_BLOCKS) + getBoundaryLeft(); // register a block at x;y and x+1;y

        if(field[index] == false && field[index + 1] == false)
        {
            field[index] = true;
            field[index + 1] = true;

            ret = true;
        }
        else
        {
            ret = false;
        }
    }

    return ret;
}

DoubleBlock* DoubleBlock::clone() const
{
    return new DoubleBlock(*this); // returns a copy of the block
}

GLfloat DoubleBlock::getDistance() const // calculates the distance from the center of the block to 0;0 based on the orientation
{
    if(this->_isVertical) return sqrt((_x * _x) + ((_y + 0.1) * (_y + 0.1)));
   
    return sqrt(((_x + 0.1) * (_x + 0.1)) + (_y * _y));
}

#endif
