#ifndef PROGRAM_H_
#define PROGRAM_H_

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
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("Die SDL konnte nicht initalisiert werden (%s)!\n", SDL_GetError());
        return 1;
    }

    ApplicationWindow *window = 
        new ApplicationWindow(575, 650, 32);

    window->setCaption("Tetris");
    window->create();

    manager = new BlockManager();

    bool init = false;
    GLfloat i = 0.0;

    while(true)
    {
        if(!pollEvents()) break;

        glClearColor(0, 0, 0, 1);
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        
        if(!init)
        {
            glLoadIdentity();
            gluPerspective(72.5, 800/600, 0, 10);
            glRotatef(30, -1, 0, 0);
            init = true;
        }
        
        glBegin(GL_LINES);
            glColor3f(1, 1, 1);
                
            i = -0.7;
            while(i < 0.7)
            {
                glVertex3f(i, 3.2, -1.5);
                glVertex3f(i, 0.0, -1.5);
                i += 0.2;
            }
            
            i = 0.0;
            while(i < 3.2)
            {
                glVertex3f(-0.7, i, -1.5);
                glVertex3f(0.7, i, -1.5);
                i += 0.2;
            }
        glEnd();
        
        manager->update();

        if(manager->getLost())
        {
            printf("Punkte: %i", manager->getScore());
            break;
        }

        //glFlush();
        
        SDL_GL_SwapBuffers();
    }

    //manager->~BlockManager();
    delete(manager);

    window->destroy();
    window->~ApplicationWindow();
    delete(window);

    SDL_Quit();
    exit(0);
    
    return 0;
}

bool Program::pollEvents()
{
    SDL_Event event;
    
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_QUIT:
                return false;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_LEFT:
                        manager->moveLeft();
                        break;
                    case SDLK_RIGHT:
                        manager->moveRight();
                        break;
                    case SDLK_UP:
                        manager->rotate();
                        break;
                    case SDLK_DOWN:
                        manager->drop();
                        break;
                    case SDLK_ESCAPE:
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
#endif
