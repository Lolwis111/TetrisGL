/*
 * Class derriving from GameBlock for drawing a 1x2/2x1 block
 */

#include "../Header/DoubleBlock.h"
#include "../Header/Base.h"
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

int DoubleBlock::getBoundaryLeft()
{
    return (int)(ceil((_x + 0.6) * 5)); // remap the x-coordinate to a column
}

int DoubleBlock::getBoundaryRight()
{
    if(this->_isVertical) 
    {
        return getBoundaryLeft(); // left rightcolumn is usually the same as the right
    }
    else 
    {
        return getBoundaryRight() + 1; // in horizontal-mode the rightcolumn is next to the left one
    }
}

int DoubleBlock::getBoundaryTop()
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

int DoubleBlock::getBoundaryBottom()
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
    bool ret = false;
    int index = 0;

    if(this->_isVertical)
    {
        index = (getBoundaryBottom() * Y_BLOCKS) + getBoundaryLeft();
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
        index = (getBoundaryBottom() * Y_BLOCKS) + getBoundaryLeft();
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
