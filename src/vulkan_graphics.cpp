#include <iostream>
#include <vector>

#include "vulkan_graphics.hpp"



vulkan_graphics::vulkan_graphics()
{
}



bool vulkan_graphics::init()
{
  // Initialize GLFW library
  std::cout << "Initializing GLFW library." << std::endl;
  std::cout << "GLFW version: " << glfwGetVersionString() << std::endl;
  if (!init_glfw())
  {
    std::cout << "Could not initialize GLFW library." << std::endl;
    return false;
  }

  // Initialize Vulkan library
  std::cout << "Initializing Vulkan library." << std::endl;
  std::cout << "Vulkan version: N/A" << std::endl;
  if (!init_vulkan())
  {
    std::cout << "Could not initialize Vulkan library." << std::endl;
    return false;
  }

  return true;
}



bool vulkan_graphics::init_glfw()
{
  // TODO: Read settings from file
  const int WIDTH = 800;
  const int HEIGHT = 600;
  const char * err; // Stores potential error strings
  
  if (!glfwInit())
  {
    glfwGetError(&err);
    std::cout << "Could not initialize GLFW." << std::endl;
    std::cout << "GLFW error: " << err << std::endl;
    return false;
  }
  
  // Create GLFW window
  window = glfwCreateWindow(WIDTH, HEIGHT, "Checkers", nullptr, nullptr);
  if (window == nullptr)
  {
    glfwGetError(&err);
    std::cout << "Could not create GLFW window." << std::endl;
    std::cout << "GLFW error: " << err << std::endl;
  }
  return true;
}



bool vulkan_graphics::init_vulkan()
{
  uint32_t glfw_extension_count = 0;
  uint32_t vk_extension_count = 0;
  const char ** glfw_extensions;
  VkApplicationInfo app_info = {};
  VkInstanceCreateInfo create_info = {};
  std::vector<VkExtensionProperties> vk_extensions;

  // Get list of extensions required by GLFW
  glfw_extensions = glfwGetRequiredInstanceExtensions(&glfw_extension_count);
  std::cout << "Required GLFW extensions: " << std::endl;
  for (int i = 0; i < glfw_extension_count; i++)
    std::cout << "\t" << glfw_extensions[i] << std::endl;
  
  // Get list of extensions supported by Vulkan
  vkEnumerateInstanceExtensionProperties(nullptr, &vk_extension_count, nullptr);
  vk_extensions.resize(vk_extension_count);
  vkEnumerateInstanceExtensionProperties(nullptr, &vk_extension_count, vk_extensions.data());
  std::cout << "Available Vulkan extensions:" << std::endl;
  for (const auto & e : vk_extensions)
    std::cout << "\t" << e.extensionName << std::endl;

  // Fill in some info on this app. This part is optional.
  app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  app_info.pApplicationName = "BOTS";
  app_info.applicationVersion = VK_MAKE_VERSION(0, 0, 0);
  app_info.pEngineName = "No Engine";
  app_info.engineVersion = VK_MAKE_VERSION(0, 0, 0);
  app_info.apiVersion = VK_API_VERSION_1_0;

  // Fill in some info required for creating the Vulkan instance. Not optional.
  create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  create_info.pApplicationInfo = &app_info;
  create_info.enabledExtensionCount = glfw_extension_count;
  create_info.ppEnabledExtensionNames = glfw_extensions;
  create_info.enabledLayerCount = 0; // Number of global validation layers (??)

  VkResult result = vkCreateInstance(&create_info, nullptr, &vk_instance);
  if (result != VK_SUCCESS)
    std::cout << "Could not create Vulkan instance." << std::endl << "VK Error: ";
  switch (result)
  {
    case VK_ERROR_OUT_OF_HOST_MEMORY: 
      std::cout << "Out of host memory."    << std::endl; return false;
    case VK_ERROR_OUT_OF_DEVICE_MEMORY: 
      std::cout << "Out of deive memory."   << std::endl; return false;
    case VK_ERROR_INITIALIZATION_FAILED:
      std::cout << "Initialization failed." << std::endl; return false;
    case VK_ERROR_LAYER_NOT_PRESENT: 
      std::cout << "Layer not present."     << std::endl; return false;
    case VK_ERROR_EXTENSION_NOT_PRESENT:
      std::cout << "Extension not present." << std::endl; return false;
    case VK_ERROR_INCOMPATIBLE_DRIVER: 
      std::cout << "Incompatible driver."   << std::endl; return false;
  }

  // Count physical devices
  uint32_t device_count = 0;
  vkEnumeratePhysicalDevices(vk_instance, &device_count, nullptr);
  std::vector<VkPhysicalDevice> devices(device_count);
  vkEnumeratePhysicalDevices(vk_instance, &device_count, devices.data());
  if (device_count == 0)
  {
    std::cout << "Failed to find GPU with Vulkan support." << std::endl;
    return false;
  }

  // Output info on physical devices
  std::cout << "Found " << device_count << " device(s): " << std::endl;
  for (auto d : devices)
  {
    VkPhysicalDeviceProperties p;
    vkGetPhysicalDeviceProperties(d, &p);
    std::cout << p.deviceName << std::endl;
  }

  // Just pick the first physical device.
  physical_device = devices[0];
  std::cout << "Selected device: ";
  VkPhysicalDeviceProperties p;
  vkGetPhysicalDeviceProperties(physical_device, &p);
  std::cout << p.deviceName << std::endl;

  return true;
}



void vulkan_graphics::quit()
{
  if (vk_instance != nullptr)
    vkDestroyInstance(vk_instance, nullptr);
  if (window != nullptr)
    glfwDestroyWindow(window);
  glfwTerminate();
}
