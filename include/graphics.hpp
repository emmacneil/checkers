/* graphics.hpp
 *
 * A virtual class representing the graphics subsystem. This class should be made concrete via
 * a subclass dependent on a graphics library. If one wants to use the Vulkan library, e.g.,
 * create a subclass vulkan_graphics. Or a separate one for SDL or OpenGL.
 *
 * Init() and quit() initialize and shut down the chosen graphics library. Other subroutines
 * for basic drawing subroutines should be added later.
 */

#ifndef __GRAPHICS_HPP__
#define __GRAPHICS_HPP__

class graphics
{
  public:
    //virtual graphics(){};
    //virtual ~graphics(){};
    virtual bool init() = 0;
    virtual void quit() = 0;
};

#endif
