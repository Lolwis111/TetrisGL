#ifndef GAMEBLOCK_H_
#define GAMEBLOCK_H_
#include "gl.h"
#include "glu.h"

class GameBlock
{
    private:
        GLfloat _speed;
        GLfloat _fallLimit;

        bool _isFalling, _isFree;       

    protected:
        GLfloat _x, _y;
        GLfloat _r, _g, _b;
        bool _isVertical;

    public:
        GameBlock(GLfloat x, GLfloat y, GLfloat r, GLfloat g, GLfloat b);
        GameBlock(const GameBlock &src);

        virtual ~GameBlock();

        GLfloat getX() { return _x; }
        void setX(GLfloat x);

        GLfloat getY() { return _y; }
        void setY(GLfloat y);

        GLfloat getR() { return _r; }
        void setR(GLfloat r);
            
        GLfloat getG() { return _g; }
        void setG(GLfloat g);
            
        GLfloat getB() { return _b; }
        void setB(GLfloat b);

        void setColor(GLfloat r, GLfloat g, GLfloat b);
        void setPosition(GLfloat x, GLfloat y);

        bool isFalling() { return _isFalling; }
        void setFalling(bool isfalling);
            
        bool isFree() { return _isFree; }
        void setFree(bool isfree);
            
        bool isVertical() { return _isVertical; }
        void setVertical(bool isvertical);

        GLfloat getSpeed() { return _speed; }
        void setSpeed(GLfloat speed);    
            
        GLfloat getFallLimit() { return _fallLimit; }
        void setFallLimit(GLfloat limit);

        virtual void draw() = 0;
        virtual int getBoundaryLeft(void) = 0;
        virtual int getBoundaryRight(void) = 0;
        virtual int getBoundaryTop(void) = 0;
        virtual int getBoundaryBottom(void) = 0;

        GLfloat getDistance();
        void update(); 
};

#endif
