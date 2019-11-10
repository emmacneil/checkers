/* vulkan_graphics.hpp
 *
 * A concrete subclass of graphics. Implements the methods set out in graphics by making calls
 * to the Vulkan library.
 */

#ifndef __VULKAN_GRAPHICS_HPP__
#define __VULKAN_GRAPHICS_HPP__

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include "graphics.hpp"



class vulkan_graphics : public graphics
{
  public:
    vulkan_graphics();

    /* Initializes the Vulkan library. */
    bool init();

    /* Cleans up the Vulkan library, frees memory, etc. */
    void quit();
  private:
    bool init_glfw();
    bool init_vulkan();

    GLFWwindow * window;
    VkInstance vk_instance;
    VkPhysicalDevice physical_device = VK_NULL_HANDLE;
};

#endif
