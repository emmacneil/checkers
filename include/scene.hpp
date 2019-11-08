/* scene.hpp
 *
 * An abstract class representing a scene in the game. Examples of scenes may include the splash
 * screen, the main menu, the typical game view, in-game menus, mini-games, closing credits, etc.
 *
 * Each scene has its own render, update, and handle_input methods.
 */

#ifndef SCENE_HPP
#define SCENE_HPP

#include "game.hpp"

class game;

class scene
{
  public :
    // Setup for the scene.
    virtual void init(game *) = 0;

    // Tear down the scene.
    virtual void quit() = 0;

    // Render the scene.
    virtual void render() = 0;

    // Update the scene.
    virtual void update() = 0;

    // Handle input for the scene.
    virtual void handle_input() = 0;
  protected :
    game * m_game;
};

#endif
