#include "Header/Base.h"
#include "Header/BlockManager.h"
#include "Header/GameBlock.h"
#include "Header/SingleBlock.h"

#ifdef DOUBLEBLOCKS
#include "Header/DoubleBlock.h"
#endif

#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <vector>

BlockManager::BlockManager()
{
    int r = 0, g = 0, b = 0; // generate a color for the next block
    createColor(&r, &g, &b);

#ifdef DOUBLEBLOCKS
    if((rand() % 100) < 60) // decide what type of block is generated next
    {
        _activeBlock = new SingleBlock(0, 3, r, g, b); // set up a new block at x=0;y=3 with the generated color
    }
    else
    {   
        _activeBlock = new DoubleBlock(0, 3, r, g, b); // - " -

        if((rand() % 100) < 50) _activeBlock->setVertical(true); // decide wether the block is vertical
        else _activeBlock->setVertical(false); // or horizontal
    }
#else
    _activeBlock = new SingleBlock(0, 3, r, g, b); // set up a new block at x=0;y=3 with the generated color
#endif


    _score = 0; // reset the game
    _lost = false;
    
    for(int x = 0; x < X_BLOCKS; x++) // initiate the whole field (clear each block)
    {
        for(int y = 0; y < Y_BLOCKS; y++)
        {
            _blockField[x][y] = false;
        }
    }
}

BlockManager::~BlockManager()
{
    while(!_blocks.empty()) // delete every block in the game
    {
        delete _blocks.back();
        _blocks.pop_back();
    }
}

void BlockManager::setScore(unsigned int score) // sets the score to the given value
{
    _score = score;
}

void BlockManager::setLost(bool lost) // sets the status
{
    _lost = lost;
}

bool BlockManager::moveRight() // moves the current block one column to the right
{
    bool result = false; // return value

    int row = _activeBlock->getBoundaryBottom(); // get its bottom-row
    int right = _activeBlock->getBoundaryRight(); // get its right-column

    if(right < X_BLOCKS-1 && _activeBlock->isFree() == false) // check if there is space on the right side and if the block is still controlable
    {
        if(row < Y_BLOCKS && right < X_BLOCKS-2) // check if its within the field
        {
            if(_blockField[row][right + 1] == true) // check if there is a block next to it
            {
                result = false;
            }
            else
            {
                _activeBlock->setX((_activeBlock->getX() + 0.2)); // move the block

                result = true;
            }
        }
        else
        {          
            _activeBlock->setX((_activeBlock->getX() + 0.2)); // move the block

            result = true;
        }
    }
    else result = false;

    return result; // true = move succesful, false = move not possible
}
bool BlockManager::moveLeft() // moves the current block one column to the left
{
    bool result = false; // return value

    int row = _activeBlock->getBoundaryBottom(); // get its bottom-row
    int left = _activeBlock->getBoundaryLeft(); // get the left column

    if(left > 0 && _activeBlock->isFree() == false) // check if there is space on the left side and if the block is still controlable
    {
        if(row < Y_BLOCKS && left > 1) // check if the block is within the field
        {
            if(_blockField[row][left - 1] == true) //check if there is block next to it
            {
                result = false;
            }
            else
            { 
                _activeBlock->setX((_activeBlock->getX() - 0.2)); // if no move the block
                result = true;
            }
        }
        else
        {
            _activeBlock->setX((_activeBlock->getX() - 0.2)); // move the block
            result = true;
        }
    }
    else 
    {
        result = false;
    }

    return result; // true = move succesful, false move not possible
}

void BlockManager::drop() // drops the current block
{
    _activeBlock->setSpeed(_activeBlock->getSpeed() * 2); // double the falling speed
    _activeBlock->setFree(true); // set the block to free-mode (not controlable)
}

void BlockManager::rotate() // rotates the block
{
    _activeBlock->setVertical(!_activeBlock->isVertical()); // just switch between vertical or not vertical
}

void BlockManager::processCollision(GameBlock *block) // calculates how far the block can fall
{
    int rowB = block->getBoundaryBottom(); // get the bottom-row
  
    int columnL = block->getBoundaryLeft(); // get the left column
    int columnR = block->getBoundaryRight(); // get the right column

    if(rowB > 0 && rowB < Y_BLOCKS) // check if the block is in the range of the field
    {
        if(_blockField[rowB - 1][columnL] == true || // if one block is allready under the block
            _blockField[rowB - 1][columnR] == true)
        {
            block->setFallLimit(calcYCoordinateFromRow(rowB)); // set its falllimit to the row above it
        }
    }
}

void BlockManager::update() // updates the gamelogic
{
    processCollision(_activeBlock); // calculate collision

    _activeBlock->update(); // update the block
    _activeBlock->draw();   // render the block

    if(!_activeBlock->isFalling()) // if the block stops falling
    {
        int r = 0, g = 0, b = 0; // generate the color of the next block
        createColor(&r, &g, &b);
        
        _blocks.push_back(_activeBlock->clone()); // save the current block to the static blocks
        delete(_activeBlock); // delete the instance

#ifdef DOUBLEBLOCKS
        if((rand() % 100) < 60) // determine the type of the next block
        {
            _activeBlock = new SingleBlock(0, 3, r, g, b); // set up a new block at x=0;y=3 with color rgb
        }
        else 
        {   
            _activeBlock = new DoubleBlock(0, 3, r, g, b); // -"-
            if((rand() % 100) < 50) _activeBlock->setVertical(true); // randomize the orientation
            else _activeBlock->setVertical(false);
        }
#else
        _activeBlock = new SingleBlock(0, 3, r, g, b); // set up a new block 
#endif

    }

    for(unsigned int i = 0; i < _blocks.size(); i++) // update all the static blocks
    {
        GameBlock *tmpB = _blocks[i]; // get the instance

        tmpB->update(); // update the physics
        tmpB->draw();   // render the block
        
        if(!tmpB->isFalling()) // check if its falling
        {
            int rowB = tmpB->getBoundaryBottom(); // if no
           
            if(rowB < Y_BLOCKS) // check if it is in the field
            {
                tmpB->registerBlock(((bool*)_blockField)); // and register it in the field
            }
            else 
            {   
                _lost = true; // if no -> you loose
            }
        }
    }

    for(int row = 0; row < Y_BLOCKS; row++) // iterate through all rows
    {
        if(checkRow(row)) // check if the player filled one row
        {
            _score += 2; // if yes -> you earn 2 points
            _deleteThis.clear(); // reset temporary list

            for(int c = 0; c < X_BLOCKS; c++) // unregister the blocks of the row
                _blockField[row][c] = false;

            for(unsigned int i = 0; i < _blocks.size(); i++) // look the blocks of the row
            {
                // blocks who are in the row
                if(_blocks[i]->getBoundaryBottom() == row || _blocks[i]->getBoundaryTop() == row) 
                {
                    //TODO DoubleBlock add SingleBlock in case of vertical and one gets removed

                    _deleteThis.push_back(_blocks[i]); // move the block to blocks who should be deleted
                }
            }       


            //TODO make this a little more effizient
            for(unsigned int i = 0; i < _deleteThis.size(); i++) // all blocks who should be deleted
            {
                for(unsigned int j = 0; j < _blocks.size(); j++) // work through all blocks
                {
                    if(_blocks[j] == _deleteThis[i]) // if the block is found
                    {
                        _blocks.erase(_blocks.begin() + j); // delete it from the main-list
                    }
                }
            }

            // iterate through all remaining rows
            for(int r = row; r < Y_BLOCKS; r++)
            {
                for(int c = 0; c < X_BLOCKS; c++) // and each registered block
                {
                    if(_blockField[r][c]) // if one block is registered at x=r;y=c
                    {
                        _blockField[r][c] = false; // move the block one row down
                        _blockField[r - 1][c] = true;
                    }

                    for(unsigned int k = 0; k < _blocks.size(); k++) // initate the movement in all blocks which are concerned 
                    {
                        int rowB = _blocks[k]->getBoundaryBottom();
                        if(rowB - 1 == r) //
                        {
                            _blocks[k]->setFallLimit(calcYCoordinateFromRow(rowB - 1)); // set falling-limit to the row below
                            _blocks[k]->setFalling(true); // initate falling
                        }
                    }
                }
            }
        }
    }

    std::sort(_blocks.begin(), _blocks.end(), sortBlocks); // sort the blocks according to their position
}

bool sortBlocks(const GameBlock *src1, const GameBlock *src2) // sortmethod
{
    return src1->getDistance() > src2->getDistance(); // the block closests to x=0;y=0 gets painted last
}

bool BlockManager::checkRow(int row) // checks if a row is full
{
    bool result = true; // start is true
    for(int s = 0; s < X_BLOCKS; s++) // iterate through all blocks of the given row
    {
        result = result && _blockField[row][s]; // if one field is not registered this will end up in false
    }

    return result;
}


GLfloat BlockManager::calcYCoordinateFromRow(int row) // remap the integer based row to an floating point y-coordinate
{
    GLfloat ret = 0.1;
    
    switch(row)
    {
        case 0: ret = 0.1; break;
        case 1: ret = 0.3; break;
        case 2: ret = 0.5; break;
        case 3: ret = 0.7; break;
        case 4: ret = 0.9; break;
        case 5: ret = 1.1; break;
        case 6: ret = 1.3; break;
        case 7: ret = 1.5; break;
        default: ret = 0.1; break;
    }

    return ret;
}

void BlockManager::createColor(int *r, int *g, int *b) // randomize a color
{
    int rnd = rand() % 60;
    
    if(rnd < 10)
    {
        *r = 1;
        *g = 0;
        *b = 0;
    }  
    else if(rnd < 20)
    {
        *r = 0;
        *g = 1;
        *b = 0;
    }
    else if(rnd < 30)
    {
        *r = 0;
        *g = 0;
        *b = 1;
    }
    else if(rnd < 40)
    {
        *r = 1;
        *g = 1;
        *b = 0;
    }
    else if(rnd < 50)
    {
        *r = 1;
        *g = 0;
        *b = 1;   
    }
    else if(rnd < 60)
    {
        *r = 0;
        *g = 1;
        *b = 1;
    }  
}
