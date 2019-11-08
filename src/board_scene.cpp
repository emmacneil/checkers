#include "board_scene.hpp"

void board_scene::init(game * g)
{
  m_game = g;
}

void board_scene::quit()
{
}

void board_scene::render()
{
  // Render squares
  // Render pieces
  //   Pieces might be moved independently of their board position
  //   E.g. dragging a piece across the screen should not change
  //   its recorded board position unless it is dropped to a valid space
}

void board_scene::update()
{
}

void board_scene::handle_input()
{
  // If ESC is pressed, open menu
  // Handle mouse click events
  //   On LMB down, pick up piece
  //   On mouse move, move picked up piece
  //   On LMB up, drop piece
}
