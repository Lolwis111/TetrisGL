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

        bool operator<(const GameBlock &src) const { return getDistance() < src.getDistance(); }

        virtual ~GameBlock();

        GLfloat getX() const { return _x; }
        void setX(GLfloat x);

        GLfloat getY() const { return _y; }
        void setY(GLfloat y);

        GLfloat getR() const { return _r; }
        void setR(GLfloat r);
            
        GLfloat getG() const { return _g; }
        void setG(GLfloat g);
            
        GLfloat getB() const { return _b; }
        void setB(GLfloat b);

        void setColor(GLfloat r, GLfloat g, GLfloat b);
        void setPosition(GLfloat x, GLfloat y);

        bool isFalling() const { return _isFalling; }
        void setFalling(bool isfalling);
            
        bool isFree() const { return _isFree; }
        void setFree(bool isfree);
            
        bool isVertical() const { return _isVertical; }
        void setVertical(bool isvertical);

        GLfloat getSpeed() const { return _speed; }
        void setSpeed(GLfloat speed);    
            
        GLfloat getFallLimit() const { return _fallLimit; }
        void setFallLimit(GLfloat limit);

        virtual void draw() = 0;
        virtual int getBoundaryLeft(void) = 0;
        virtual int getBoundaryRight(void) = 0;
        virtual int getBoundaryTop(void) = 0;
        virtual int getBoundaryBottom(void) = 0;
        virtual bool registerBlock(bool*) = 0;

        GLfloat getDistance() const;
        void update(); 
};

#endif
