/* board_scene.hpp
 *
 * This scene carries an instance of the game state, and is in charge of rendering the game state,
 * getting user input, and updating the game state based on that input.
 */

#ifndef BOARD_SCENE_HPP
#define BOARD_SCENE_HPP

#include "scene.hpp"

class board_scene : public scene
{
  public :
    void init(game * g);
    void quit();
    void render();
    void update();
    void handle_input();
};

#endif
