#ifndef GL_WINDOW_H_
#define GL_WINDOW_H_

#define OPEND_WINDOW 0x01
#define FULL_SCREEN  0x02

#include <string>
#include "SDL.h"
#include "SDL_opengl.h"
#include "SDL_video.h"

///
/// class for initiating a new SDL-based OpenGL-window
class ApplicationWindow 
{
    public:
        ApplicationWindow(int width, int height, int bpp);
        virtual ~ApplicationWindow();
        bool create();
        bool destroy();
        void setResolution(int width, int height);
        void setColorDepth(int bpp);
        void setCaption(const std::string& caption);
        void setFullscreen(bool enable = true);
            
        SDL_Surface *getSurface();
            
    private:
        int _width, _height, _bpp;
        std::string _caption;
        SDL_Surface *_surface;
        char _state;

        ApplicationWindow(const ApplicationWindow& src);
        ApplicationWindow& operator=(const ApplicationWindow& src);
};

#endif
