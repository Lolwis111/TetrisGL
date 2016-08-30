#ifndef GL_WINDOW_H_
#define GL_WINDOW_H_

#define OPEND_WINDOW 0x01 // window was opened
#define FULL_SCREEN  0x02 // window is in fullscreen mode

#include <string>
#include "SDL.h"
#include "SDL_opengl.h"
#include "SDL_video.h"

///
/// class for initiating a new SDL-based OpenGL-window
class ApplicationWindow 
{
    public:
        ApplicationWindow(int width, int height, int bpp); // constructor taking size and color-depth

        virtual ~ApplicationWindow(); // destructor

        bool create(); // creates a new window
        bool destroy();// destroys the window

        void setResolution(int width, int height); // sets the resolutin (without applying it)
        void setColorDepth(int bpp); // sets the color depth (without applying it)
        void setCaption(const std::string& caption); // sets the caption (also applys)
        void setFullscreen(bool enable = true); // changes the fullscreen mode (without applying it)
            
        SDL_Surface *getSurface(); // the surface of window
            
    private:
        int _width, _height, _bpp; // resolution and color-depth
        std::string _caption; // caption of the window
        SDL_Surface *_surface; // surface of the window
        char _state; // inidicates the state of the window
};

#endif
