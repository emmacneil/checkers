/* sdl_graphics.hpp
 *
 * A concrete subclass of graphics. Implements the methods set out in graphics by making calls
 * to the SDL library.
 */

#ifndef __SDL_GRAPHICS_HPP__
#define __SDL_GRAPHICS_HPP__

#include "graphics.hpp"

class sdl_graphics : public graphics
{
  public:
    sdl_graphics(){}
    bool init() {return false;}
    void quit(){}
};

#endif
