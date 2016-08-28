#include "Header/BlockManager.h"
#include "Header/GameBlock.h"
#include "Header/SingleBlock.h"
#include "Header/DoubleBlock.h"
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <vector>

BlockManager::BlockManager()
{
    int r = 0, g = 0, b = 0;
    createColor(&r, &g, &b);

    _activeBlock = new SingleBlock(0, 3, r, g, b);

    /*if((rand() % 100) < 60) 
    {
        _activeBlock = new SingleBlock(0, 3, r, g, b);
    }
    else
    {   
        _activeBlock = new DoubleBlock(0, 3, r, g, b);

        if((rand() % 100) < 50) _activeBlock->setVertical(true);
        else _activeBlock->setVertical(false);
    }*/

    _score = 0;
    _lost = false;
    
    for(int x = 0; x < X_BLOCKS; x++)
    {
        for(int y = 0; y < Y_BLOCKS; y++)
        {
            _blockField[x][y] = false;
        }
    }
}

BlockManager::~BlockManager()
{
    while(!_blocks.empty())
    {
        delete _blocks.back();
        _blocks.pop_back();
    }
}

void BlockManager::setScore(int score)
{
    if(score < 0) 
    {
        _score = 0;
    }
    else 
    {
        _score = score;
    }
}

void BlockManager::setLost(bool lost)
{
    _lost = lost;
}

bool BlockManager::moveRight()
{
    bool result = false;
    int row = _activeBlock->getBoundaryBottom();
    int right = _activeBlock->getBoundaryRight();

    if(right < X_BLOCKS-1 && _activeBlock->isFree() == false)
    {
        if(row < Y_BLOCKS && right < X_BLOCKS-2)
        {
            if(_blockField[row][right + 1] == true) 
            {
                result = false;
            }
            else
            {
                _activeBlock->setX((_activeBlock->getX() + 0.2));

                result = true;
            }
        }
        else
        {          
            _activeBlock->setX((_activeBlock->getX() + 0.2));

            result = true;
        }
    }
    else result = false;

    return result;
}
bool BlockManager::moveLeft()
{
    bool result = false;
    int row = _activeBlock->getBoundaryBottom();
    int left = _activeBlock->getBoundaryLeft();

    if(left > 0 && _activeBlock->isFree() == false)
    {
        if(row < Y_BLOCKS && left > 1)
        {
            if(_blockField[row][left - 1] == true)
            {
                result = false;
            }
            else
            {
                _activeBlock->setX((_activeBlock->getX() - 0.2));
                result = true;
            }
        }
        else
        {
            _activeBlock->setX((_activeBlock->getX() - 0.2));
            result = true;
        }
    }
    else 
    {
        result = false;
    }

    return result;
}

void BlockManager::drop()
{
    _activeBlock->setSpeed(0.04f);
    _activeBlock->setFree(true);
}

void BlockManager::rotate()
{
    _activeBlock->setVertical(!_activeBlock->isVertical());
}

void BlockManager::processCollision(GameBlock *block)
{
    int rowB = block->getBoundaryBottom();
  
    int columnL = block->getBoundaryLeft();
    int columnR = block->getBoundaryRight();

    if(rowB > 0 && rowB < Y_BLOCKS)
    {
        if(_blockField[rowB - 1][columnL] == true ||
            _blockField[rowB - 1][columnR] == true)
        {
            block->setFallLimit(calcYCoordinateFromRow(rowB));
        }
    }
}

void BlockManager::update()
{
    processCollision(_activeBlock);

    _activeBlock->update();
    _activeBlock->draw();

    if(!_activeBlock->isFalling())
    {
        int r = 0, g = 0, b = 0;
        createColor(&r, &g, &b);

        if (dynamic_cast<SingleBlock*>(_activeBlock) != NULL) 
        {
            _blocks.push_back(new SingleBlock(*_activeBlock));
        }
        else if(dynamic_cast<DoubleBlock*>(_activeBlock) != NULL)
        {
            _blocks.push_back(new DoubleBlock(*_activeBlock));
        }

        _activeBlock = new SingleBlock(0.0, 3, r, g, b);

        /*if((rand() % 100) < 60) 
        {
            delete(_activeBlock);

            _activeBlock = new SingleBlock(0, 3, r, g, b);
        }
        else 
        {
            delete(_activeBlock);
            
            _activeBlock = new DoubleBlock(0, 3, r, g, b);
            if((rand() % 100) < 50) _activeBlock->setVertical(true);
            else _activeBlock->setVertical(false);
        }*/
    }

    for(unsigned int i = 0; i < _blocks.size(); i++)
    {
        GameBlock *tmpB = _blocks[i];

        tmpB->update();
        tmpB->draw();
        
        if(!tmpB->isFalling())
        {
            int rowB = tmpB->getBoundaryBottom();
            /*int rowT = tmpB->getBoundaryTop();
            int columnL = tmpB->getBoundaryLeft();
            int columnR = tmpB->getBoundaryRight();*/

            if(rowB < Y_BLOCKS)
            {
                tmpB->registerBlock(((bool*)_blockField));

                /*if(dynamic_cast<SingleBlock*>(tmpB) != NULL)
                {
                    _blockField[rowB][columnL] = true;
                }
                else if(dynamic_cast<DoubleBlock*>(tmpB) != NULL)
                {
                    if(tmpB->isVertical())
                    {
                        if(rowB < Y_BLOCKS-1)
                        {
                            _blockField[rowB][columnL] = true;
                            _blockField[rowT][columnL] = true;
                        }
                        else 
                        {
                            _lost = true;
                        }
                    }
                    else
                    {
                        _blockField[rowB][columnL] = true;
                        _blockField[rowB][columnR] = true;
                    }
                }*/
            }
            else 
            {   
                _lost = true;
            }
        }
    }

    for(int row = 0; row < Y_BLOCKS; row++)
    {
        if(checkRow(row))
        {
            _score += 2;
            _deleteThis.clear();

            for(int c = 0; c < X_BLOCKS; c++) 
                _blockField[row][c] = false;

            for(unsigned int i = 0; i < _blocks.size(); i++)
            {
                if(_blocks[i]->getBoundaryBottom() == row || _blocks[i]->getBoundaryTop() == row)
                {
                    /*if(dynamic_cast<DoubleBlock*>(_blocks[i]) != NULL && _blocks[i]->isVertical())
                    {
                        SingleBlock *b = new SingleBlock(_blocks[i]->getX(), _blocks[i]->getY() + 0.2,
                                         _blocks[i]->getR(), _blocks[i]->getG(), _blocks[i]->getB());

                        b->setFalling(true);
                        b->setFallLimit(_blocks[i]->getFallLimit());
                        _blocks.push_back(b);
                    }*/

                    _deleteThis.push_back(_blocks[i]);
                }
            }       

            for(unsigned int i = 0; i < _deleteThis.size(); i++)
            {
                for(unsigned int j = 0; j < _blocks.size(); j++)
                {
                    /*if(_blocks[j].getX() == _deleteThis[i].getX() &&
                        _blocks[j].getY() == _deleteThis[i].getY())*/
                    if(_blocks[j] == _deleteThis[i])
                    {
                        _blocks.erase(_blocks.begin() + j);
                    }
                }

                //delete(_deleteThis[i]);
            }
            _deleteThis.clear();

            for(int r = row; r < Y_BLOCKS; r++)
            {
                for(int c = 0; c < X_BLOCKS; c++)
                {
                    if(_blockField[r][c])
                    {
                        _blockField[r][c] = false;
                        _blockField[r - 1][c] = true;
                    }

                    for(unsigned int k = 0; k < _blocks.size(); k++)
                    {
                        int rowB = _blocks[k]->getBoundaryBottom();
                        if(rowB - 1 == r)
                        {
                            _blocks[k]->setFallLimit(calcYCoordinateFromRow(rowB - 1));
                            _blocks[k]->setFalling(true);
                        }
                    }
                }
            }
        }
    }

    std::sort(_blocks.begin(), _blocks.end());
}

bool BlockManager::checkRow(int row)
{
    bool result = true;
    for(int s = 0; s < X_BLOCKS; s++)
    {
        result = result && _blockField[row][s];
    }

    return result;
}


GLfloat BlockManager::calcYCoordinateFromRow(int row)
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

/*void BlockManager::sortBlocks()
{
    for(unsigned int i = 0; i < _blocks.size() - ; i++)
    {
        if(_blocks[i]->getDistance() < _blocks[i + 1]->getDistance())
        {
            GameBlock *t = _blocks[i + 1];
            _blocks[i + 1] = _blocks[i];
            _blocks[i] = t;
        }
    }
}*/

void BlockManager::createColor(int *r, int *g, int *b)
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
