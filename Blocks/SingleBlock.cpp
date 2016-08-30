/*
 * Class derriving from GameBlock for drawing a 1x1 cube
 */

#include "../Header/SingleBlock.h"
#include "../Header/Base.h"
#include <gl.h>
#include <glu.h>
#include <math.h>
#include <stdio.h>
#include <vector>

SingleBlock::SingleBlock(GLfloat x, GLfloat y, GLfloat r, GLfloat g, GLfloat b) :
    GameBlock(x, y, r, g, b)
{
    
}

SingleBlock::~SingleBlock()
{
    
}

/// 
/// draws the block accordingly
void SingleBlock::draw()
{
    glPushMatrix(); // save the current matrix (to only move the block)

    glTranslatef(_x, _y, -1.4f);

    glColor3f(_r, _g, _b); // set the color
    glBegin(GL_QUADS);      // draw the cube  
        // downside
        glVertex3f(-0.1, -0.1, +0.1);
        glVertex3f(+0.1, -0.1, +0.1);
        glVertex3f(+0.1, -0.1, -0.1);
        glVertex3f(-0.1, -0.1, -0.1);
 
        // upside
        glVertex3f(-0.1, +0.1, +0.1);
        glVertex3f(+0.1, +0.1, +0.1);
        glVertex3f(+0.1, +0.1, -0.1);
        glVertex3f(-0.1, +0.1, -0.1);

        // front
        glVertex3f(-0.1, +0.1, +0.1);
        glVertex3f(+0.1, +0.1, +0.1);
        glVertex3f(+0.1, -0.1, +0.1);
        glVertex3f(-0.1, -0.1, +0.1);

        // back
        glVertex3f(-0.1, +0.1, -0.1);
        glVertex3f(+0.1, +0.1, -0.1);
        glVertex3f(+0.1, -0.1, -0.1);
        glVertex3f(-0.1, -0.1, -0.1);

        // left
        glVertex3f(+0.1, -0.1, +0.1);
        glVertex3f(+0.1, +0.1, +0.1);
        glVertex3f(+0.1, +0.1, -0.1);
        glVertex3f(+0.1, -0.1, -0.1);

        // right
        glVertex3f(-0.1, -0.1, +0.1);
        glVertex3f(-0.1, +0.1, +0.1);
        glVertex3f(-0.1, +0.1, -0.1);
        glVertex3f(-0.1, -0.1, -0.1);
    glEnd();

    glPopMatrix(); // restore the global matrix
}

int SingleBlock::getBoundaryLeft() const
{
    return nearbyint((_x + 0.6) * 5); //remap the x-coordinate to a column
}

int SingleBlock::getBoundaryRight() const
{
    return getBoundaryLeft(); //remap the x-coordinate to a column
}

int SingleBlock::getBoundaryTop() const // on a single block the row is the same on both ends
{
    return getBoundaryBottom();
}

int SingleBlock::getBoundaryBottom() const // remap the y-coordinate to a row
{
    int ret = 0;
    if(_y <= 0.101) ret = 0; 
    else if(_y <= 0.301) ret = 1;
    else if(_y <= 0.501) ret = 2;
    else if(_y <= 0.701) ret = 3;
    else if(_y <= 0.901) ret = 4;
    else if(_y <= 1.101) ret = 5;
    else if(_y <= 1.301) ret = 6;
    else if(_y <= 1.501) ret = 7;
    else ret = 8;

    return ret;
}

bool SingleBlock::registerBlock(bool *field)
{
    int index = (getBoundaryBottom() * Y_BLOCKS) + getBoundaryLeft(); // registers the block at the position x;y in the field

    if(field[index] == false)
    {
        field[index] = true;
        return true;
    }
    
    return false;
}

SingleBlock* SingleBlock::clone() const
{
    return new SingleBlock(*this); //returns a copy of the block
}

GLfloat SingleBlock::getDistance() const
{
    return sqrt((_x * _x) + (_y * _y)); // calculate distance to 0;0
}
