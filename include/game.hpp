/* game.hpp
 *
 * The game class is in charge of intializing subsystems (graphics, logs, etc.), running the
 * main game loop, and managing the scene stack. Each scene has its own render/update/handle_input
 * method and the game class calls the render/update/handle_input of whatever scene is on top
 * of the stack.
 */

#ifndef GAME_HPP
#define GAME_HPP

#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <thread>
#include <stack>

#include "scene.hpp"
#include "graphics.hpp"

class scene;

class game
{
public :
  game();
  bool init();
  void run();
  void quit();

  void render();
  void update();
  void handle_input();

  void push_scene(scene *);
  void pop_scene();
  void change_scene(scene *);

private :
  graphics * _graphics_system;
  std::chrono::high_resolution_clock::time_point _t0, _t1;
  bool _quit;
  int n_updates = 0;
  int n_frames = 0;
  std::stack<scene*> _scene_stack;
};

#endif
