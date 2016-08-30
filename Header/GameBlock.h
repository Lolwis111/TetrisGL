#ifndef GAMEBLOCK_H_
#define GAMEBLOCK_H_
#include <gl.h>
#include <glu.h>
#include <vector>

class GameBlock // Baseclass of blocks
{
    private:
        GLfloat _speed;      // fall speed of the block
        GLfloat _fallLimit;  // how far the block can fall

        bool _isFalling,     // indicates if the block is moving
             _isFree;        // indicates if the block was droped

    protected:
        GLfloat _x, _y;      // position
        GLfloat _r, _g, _b;  // color
        bool _isVertical;    // orientation of the block

    public:
        GameBlock(GLfloat x, GLfloat y, GLfloat r, GLfloat g, GLfloat b); // constructor (takes position and color)
        GameBlock(const GameBlock &src); // copy-constructor

        virtual GameBlock *clone() const = 0; // returns a copy of the block

        virtual ~GameBlock(); // destructor

        GLfloat getX() const { return _x; } // returns the x-coordinate
        void setX(GLfloat x); // sets the x-coordinate

        GLfloat getY() const { return _y; } // returns the y-coordinate
        void setY(GLfloat y); // sets the y-coordinate

        GLfloat getR() const { return _r; } // returns the red part of the color
        void setR(GLfloat r); // sets the red part of the color (clamp)
            
        GLfloat getG() const { return _g; } // returns the green part of the color
        void setG(GLfloat g); // sets the green part of the color (clamp)
            
        GLfloat getB() const { return _b; } // returns the blue part of the color
        void setB(GLfloat b); // sets the blue part of the color (clamp)

        void setColor(GLfloat r, GLfloat g, GLfloat b); // sets all color parts at once
        void setPosition(GLfloat x, GLfloat y); // set a position based on coordinates

        bool isFalling() const { return _isFalling; } // return the falling-status
        void setFalling(bool isfalling); // sets the falling-status
            
        bool isFree() const { return _isFree; } // inidactes if the block was dropped
        void setFree(bool isfree); // drops or "undrops" the block
            
        bool isVertical() const { return _isVertical; } // returns the orientation
        void setVertical(bool isvertical); // sets the orientation

        GLfloat getSpeed() const { return _speed; } // returns the falling speed
        void setSpeed(GLfloat speed); // sets the falling speed
            
        GLfloat getFallLimit() const { return _fallLimit; } // returns the limit of falling (as coordinate)
        void setFallLimit(GLfloat limit); // set the limit of falling (coordinate)

        virtual void draw() = 0; // used to draw a block (needs to be overriden)
        virtual int getBoundaryLeft(void) const = 0; // used to indicate the boundarys of the block (each needs to be overriden)
        virtual int getBoundaryRight(void) const = 0;
        virtual int getBoundaryTop(void) const = 0;
        virtual int getBoundaryBottom(void) const = 0;
        virtual bool registerBlock(bool*) = 0; // registers the block in the two dimensional array based on the size of the block (needs to be overriden)

        virtual GLfloat getDistance() const = 0; // calculates the distance between 0;0 and x;y (needs to be overriden)
        void update(); // updates the physics of the block
};

#endif
