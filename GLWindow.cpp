/*
 *  Class for initiating an SDL-based OpenGL-window
 */

#include "Header/GLWindow.h"
#include "SDL.h"
#include "SDL_opengl.h"

///
/// Constructor taking arguments for position and color
ApplicationWindow::ApplicationWindow(int width, int height, int bpp) :
    _width(width), _height(height), _bpp(bpp), _caption("Tetris"), _state(0)
{
        
}  

///
/// Destructor destroying the window
ApplicationWindow::~ApplicationWindow()
{
    destroy();
}

///
/// Creates an new OpenGL-window
bool ApplicationWindow::create()
{
    int error = 0;
    if(_state & OPEND_WINDOW) destroy(); // check wether a window was allready created

    if(!SDL_WasInit(SDL_INIT_VIDEO)) 
        error = SDL_InitSubSystem(SDL_INIT_VIDEO); // if init was never run do it now

    if(error != 0)
        return false;

    SDL_WM_SetCaption(_caption.c_str(), NULL);   // set the window- and taskbarcaption
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // use a doublebuffer
        
    _surface = SDL_SetVideoMode(_width, _height, _bpp, 
                SDL_OPENGL | ((_state & FULL_SCREEN) ? SDL_FULLSCREEN : 0)); // set the videomode to specified resolution and bpp
                                                                             // also determine wether fullscreen is enabled or not

    if(!_surface) return false;  // check if the window was created correctly

    SDL_ShowCursor(0); // hide the mousecursor  

    return true; // everything ok
}      

///
/// destroys the window
bool ApplicationWindow::destroy()
{
    if(!(_state & OPEND_WINDOW)) return true; // check if the window was destoryed before
      
    SDL_FreeSurface(_surface); // release the resources
    _state &= ~OPEND_WINDOW; // set state to not-open

    delete(_surface);  
      
    return true; // all ok
}

///
/// saves the given resolution (but won't initate it)
void ApplicationWindow::setResolution(int width, int height)
{
    _width = width; // save x and y resolution
    _height = height;
}
    
///
/// saves the given bpp (but won't initate it)
void ApplicationWindow::setColorDepth(int bpp)
{
    _bpp = bpp; // set bpp
}

///
/// saves and initates a caption    
void ApplicationWindow::setCaption(const std::string& caption)
{
    _caption = caption; // save the caption
    SDL_WM_SetCaption(_caption.c_str(), NULL); //set the caption
}

///
/// sets the window-mode
void ApplicationWindow::setFullscreen(bool enable)
{
    if(enable) // set fullscreen to true
    {
        _state |= FULL_SCREEN;
        return;
    }

    _state &= ~FULL_SCREEN; //set fullscreen to false
}

///
/// returns a pointer to the surface
SDL_Surface *ApplicationWindow::getSurface()
{
    return _surface; // return the surfacepointer
}  
