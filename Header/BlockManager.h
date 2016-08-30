#ifndef BLOCKMANAGER_H_
#define BLOCKMANAGER_H_
#include "GameBlock.h"
#include "Base.h"
#include "gl.h"
#include "glu.h"
#include <vector>

bool sortBlocks(const GameBlock *src1, const GameBlock *src2); // used by std::sort to sort the blocks

class BlockManager // BlockManager contains the gamelogic and the blocks
{
    private:
        std::vector<GameBlock*> _blocks;     // contains all blocks (except for _activeBlock)
        std::vector<GameBlock*> _deleteThis; // contains the blocks which can be removed (used when a row is full)

        bool _blockField[X_BLOCKS][Y_BLOCKS]; // contains the information wether or not a block is registered at certain position

        bool _lost; // indicates if the game was lost
        unsigned int _score; // the score of the current game

        GameBlock *_activeBlock; // the block that is currently falling

        GLfloat calcYCoordinateFromRow(int row); // remaps the row to a coordinate

        bool checkRow(int row); // checks if one row is full

        void processCollision(GameBlock *block); // calculates the fallLimit for the block

        void createColor(int *r, int *g, int *b); // generates a random color represented by r/g/b
        
    public:
        BlockManager();  // constructor
        ~BlockManager(); // destructor

        void update();   // updates gamelogic
        bool moveRight();// moves the current block to the right
        bool moveLeft(); // moves the current block to the left
        void drop();     // drops the current block
        void rotate();   // rotates the current block (90 degrees)

        unsigned int getScore() const { return _score; } // returns the score of the game
        void setScore(unsigned int score); // sets the score of the game

        bool getLost() const { return _lost; } // returns the lost-status
        void setLost(bool lost); // sets the lost status
};

#endif
