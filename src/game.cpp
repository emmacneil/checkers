#include <iostream>

#include "game.hpp"
#include "board_scene.hpp"
//#include "opening_scene.hpp"
#ifdef SDL_GRAPHICS
#include "sdl_graphics.hpp"
#endif
#ifdef VULKAN_GRAPHICS
#include "vulkan_graphics.hpp"
#endif



game::game()
{
  _quit = false;
  _graphics_system = nullptr;
}



bool game::init()
{
  // Initialize Graphics
#ifdef SDL_GRAPHICS
  std::cout << "Initializing SDL graphics subsystem." << std::endl;
  _graphics_system = new sdl_graphics();
#endif
#ifdef VULKAN_GRAPHICS
  std::cout << "Initializing Vulkan graphics subsystem." << std::endl;
  _graphics_system = new vulkan_graphics();
#endif
  if (_graphics_system == nullptr)
  {
    std::cout << "Could not allocate memory for graphics subsytem." << std::endl;
    return false;
  }
  if (!_graphics_system->init())
  {
    std::cout << "Could not initialize graphics subsystem." << std::endl;
    return false;
  }
  
  board_scene * s = new board_scene();
  if (s == nullptr)
  {
    printf("Could not create board scene.\n");
    return false;
  }
  push_scene(s);
  
  return true;
}



void game::run()
{
  using clock = std::chrono::high_resolution_clock;
  typedef std::chrono::nanoseconds ns;

  const int fps = 60;  // Frames per second
  const int ups = 200; // Updates per second
  constexpr ns nspu((int)(1.0e9/(double)ups)); // nanoseconds per update
  constexpr ns nspf((int)(1.0e9/(double)fps)); // nanoseconds per update
  auto t0 = clock::now();
  ns t_until_update(0);
  ns t_until_render(0);

  // Main game loop
  while (!_quit)
  {
    // Get elapsed time (in nanoseconds) since last loop iteration.
    ns elapsed = std::chrono::duration_cast<ns>(clock::now() - t0);
    t0 = clock::now();
    
    // Update time until next update and render
    t_until_update -= elapsed;
    t_until_render -= elapsed;
    
    // Check for input
    handle_input();


    // If it is time to update, update.
    if (t_until_update <= ns::zero())
    {
      update();
      t_until_update += nspu;
    }

    // If it is time to render, render.
    if (t_until_render <= ns::zero())
    {
      render();
      t_until_render += nspf;
    }
    
    // Sleep until next update or render.
    std::this_thread::sleep_for(std::min(t_until_update, t_until_render));

    if (_scene_stack.empty())
      _quit = true;
  }
}



void game::quit()
{
  std::cout << "Quiting graphics subsystem." << std::endl;
  _graphics_system->quit();
  delete _graphics_system;
}



void game::render()
{
  /*SDL_FillRect(_screenSurface, NULL, SDL_MapRGB(_screenSurface->format, 255, 255, 255));
  SDL_UpdateWindowSurface(_window);*/
  if (!_scene_stack.empty())
    _scene_stack.top()->render();
  n_frames++;
}



void game::update()
{
  /*_timer -= 5;
  if (_timer <= 0)
    _quit = true;*/
  if (!_scene_stack.empty())
    _scene_stack.top()->update();
  n_updates++;
}



void game::handle_input()
{
  if (!_scene_stack.empty())
    _scene_stack.top()->handle_input();
}



void game::pop_scene()
{
  // TODO : Error handling for nullptrs
  scene * s = _scene_stack.top();
  _scene_stack.pop();
  s->quit();
  delete s;
}




void game::push_scene(scene * s)
{
  s->init(this);
  _scene_stack.push(s);
}



void game::change_scene(scene * s)
{
  pop_scene();
  push_scene(s);
}


