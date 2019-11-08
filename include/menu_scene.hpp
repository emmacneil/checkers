/* menu_scene.hpp
 *
 * This scene, if possible, should be treated like an overlay, rendered on top of the board_scene
 * (or whatever scene is below it in the stack). It is a menu with options
 *
 *  [  New Game ]
 *  [Resume Game]
 *  [ Exit Game ]
 *
 * The option to resume should be greyed out if no game is in progress.
 */

#ifndef MENU_SCENE_HPP
#define MENU_SCENE_HPP

#include "scene.hpp"

class menu_scene : public scene
{
  public :
    void init(game * g);
    void quit();
    void render();
    void update();
    void handle_input();
};

#endif
