#ifndef BLOCKMANAGER_H_
#define BLOCKMANAGER_H_
#include "GameBlock.h"
#include "Base.h"
#include "gl.h"
#include "glu.h"
#include <vector>

class BlockManager
{
    private:
        std::vector<GameBlock*> _blocks;
        std::vector<GameBlock*> _deleteThis;

        bool _blockField[X_BLOCKS][Y_BLOCKS];
        bool _lost;
        int _score;
        GameBlock *_activeBlock;

        GLfloat calcYCoordinateFromRow(int row);
        bool checkRow(int row);
        void processCollision(GameBlock *block);
        void sortBlocks();
        void createColor(int *r, int *g, int *b);
        
    public:
        BlockManager();
        ~BlockManager();

        void update();
        bool moveRight();
        bool moveLeft();
        void drop();
        void rotate();

        int getScore() { return _score; } 
        void setScore(int score);

        bool getLost() { return _lost; }
        void setLost(bool lost);
};

#endif
