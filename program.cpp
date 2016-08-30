#include "SDL.h"
#include "SDL_opengl.h"
#include "gl.h"
#include "glu.h"
#include "stdio.h"

#include "Header/Program.h"
#include "Header/GLWindow.h"
#include "Header/SingleBlock.h"
#include "Header/DoubleBlock.h"
#include "Header/GameBlock.h"
#include "Header/BlockManager.h"

int Program::run(int argc, char **argv)
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0) // check if SDL/OpenGL is available
    {
        printf("SDL couldn't be initialized (%s)!\n", SDL_GetError()); //
        return 1;
    }

    ApplicationWindow window = ApplicationWindow(575, 650, 32); // set up a openGL-Window using SDL

    window.setCaption("Tetris"); // set windowtitle to "Tetris"
    window.create(); // create the window

    manager = BlockManager(); // initialize the BlockManager (contains gamelogic)

    bool init = false; // for setting up the matrix
    GLfloat i = 0.0;   // for drawing the field of lines

    while(true)
    {
        if(!pollEvents()) break; // handle all events (escape usually returns false here)

        glClearColor(0, 0, 0, 1);     // set the color
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT); // override the screen with the color
        
        if(!init) // check if this was run before
        {
            glLoadIdentity(); // load standart matrix 
            gluPerspective(72.5, 575/650, 0, 10); // set the perspective
            glRotatef(30, -1, 0, 0); // rotate everything 30 degrees back
            init = true; // don't run this again
        }
        
        glBegin(GL_LINES);      // draw the field
            glColor3f(1, 1, 1); // white color
                
            i = -0.7;       // from x = -0.7
            while(i < 0.7)  // to x = 0.7
            {
                glVertex3f(i, 3.2, -1.5); // draw a vertical line
                glVertex3f(i, 0.0, -1.5);
                i += 0.2; // jump to next line
            }
            
            i = 0.0;        // from y = 0
            while(i < 3.2)  // to y = 3.2
            {
                glVertex3f(-0.7, i, -1.5); //draw a horizontal line
                glVertex3f(0.7, i, -1.5);
                i += 0.2; // jump to the next line
            }
        glEnd();
        
        manager.update(); // update the gamelogic (including the blocks)

        if(manager.getLost()) // check if the game was lost
        {
            printf("Punkte: %i", manager.getScore()); // if yes print the score
            break; // and exit the game
        }
        
        SDL_GL_SwapBuffers(); // swap buffers to actually show whats going on
    }

    manager.~BlockManager(); // free the resources

    window.destroy(); // destroy the window
    window.~ApplicationWindow(); // free its resources

    SDL_Quit(); // quit the SDL
    exit(0); // exit
    
    return 0;
}

bool Program::pollEvents()
{
    SDL_Event event;
    
    while(SDL_PollEvent(&event)) // get the next event
    {
        switch(event.type)
        {
            case SDL_QUIT: // request to quit 
                return false;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym) // handle the keycodes
                {
                    // arrowkeys are used to play
                    case SDLK_LEFT:
                        manager.moveLeft();
                        break;
                    case SDLK_RIGHT:
                        manager.moveRight();
                        break;
                    case SDLK_UP:
                        manager.rotate();
                        break;
                    case SDLK_DOWN:
                        manager.drop();
                        break;
                    case SDLK_ESCAPE: // escape exits
                        return false;
                        
                        break;
                    default:
                        break;
                }
    
                break;
            default:
                break;
        }
    }

    return true;
}
