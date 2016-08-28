/*
 * Baseclass for all the blocks of the tetris-game
 */

#include "gl.h"
#include "glu.h"
#include "math.h"
#include "../Header/GameBlock.h"

///
/// Constructor setting up all the needed values
GameBlock::GameBlock(GLfloat x, GLfloat y, GLfloat r, GLfloat g, GLfloat b)
{
    _x = x;
    _y = y;

    _r = r;
    _b = b;
    _g = g;

    _isFalling = true;
    _isFree = false;
    _speed = 0.01;
    _fallLimit = 0.1;
    _isVertical = false;
}

GameBlock::GameBlock(const GameBlock &src)
{
    this->_x = src._x;
    this->_y = src._y;
    
    this->_r = src._r;
    this->_g = src._g;
    this->_b = src._b;
    
    this->_isFalling = src._isFalling;
    this->_isFree = src._isFree;
    this->_speed = src._speed;
    this->_fallLimit = src._fallLimit;
    this->_isVertical = src._isVertical;
}

GameBlock::~GameBlock()
{
    // Destroy stuff here
}

// ========================================================
// Property area, just setting certain values

void GameBlock::setX(GLfloat x)
{
    _x = x;
}

void GameBlock::setY(GLfloat y)
{
    _y = y;
}

void GameBlock::setR(GLfloat r)
{
    if(r < 0.0) _r = 0.0;
    else if(r > 1.0) r = 1.0;
    else _r = r;
}

void GameBlock::setG(GLfloat g)
{
    if(g < 0.0) _g = 0.0;
    else if(g > 1.0) _g = 1.0;
    else _g = g;
}

void GameBlock::setB(GLfloat b)
{
    if(b < 0.0) _b = 0.0;
    else if(b > 1.0) _b = 1.0;
    else _b = b;
}

void GameBlock::setColor(GLfloat r, GLfloat g, GLfloat b)
{
    setR(r);
    setG(g);
    setB(b);
}

void GameBlock::setPosition(GLfloat x, GLfloat y)
{
    setX(x);
    setY(y);
}

void GameBlock::setFalling(bool isfalling)
{
    _isFalling = isfalling;
}

void GameBlock::setFree(bool isfree)
{
    _isFree = isfree;
}

void GameBlock::setVertical(bool isvertical)
{
    _isVertical = isvertical;
}

void GameBlock::setSpeed(GLfloat speed)
{
    _speed = speed;
}

void GameBlock::setFallLimit(GLfloat limit)
{
    _fallLimit = limit;
}
// ===================================================


///
/// Calculating the distance of the block to the origin 
/// of OpenGLs virtual coordinate system 
GLfloat GameBlock::getDistance()
{
    return sqrt((_x * _x) + (_y * _y));
}

///
/// updates the physics of the block
void GameBlock::update()
{
    if(_isFalling) // if a block is falling
    {
        _y = _y - _speed; // update its position

        if(_y < _fallLimit) // if the limit is reached
        {
            _isFalling = false;         // stop the block
            _speed = 0.01;              // reset the speed
            _isFree = false;            // make sure the player can't move it no more
            _y = _fallLimit;  // move it slightly underneath the limit to make sure it mathmatically smaller
        }
    }
}
