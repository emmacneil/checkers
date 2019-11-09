#include "board_scene.hpp"
#include <iostream>

void board_scene::init(game * g)
{
  m_game = g;

  std::cout << "Initializing board." << std::endl;
  m_board_state = new board_state();
  if (!m_board_state)
    std::cout << "Failed to initialize board." << std::endl;
  else
  {
    m_board_state->setup();
    for (int i = 0; i < 8; i++)
    {
      for (int j = 0; j < 8; j++)
        std::cout << m_board_state->get_piece(i, j);
      std::cout << std::endl;
    }
  }

}

void board_scene::quit()
{
  if (m_board_state)
    delete m_board_state;
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
  // Do nothing for now. Just quit
  m_game->pop_scene();
}

void board_scene::handle_input()
{
  // If ESC is pressed, open menu
  // Handle mouse click events
  //   On LMB down, pick up piece
  //   On mouse move, move picked up piece
  //   On LMB up, drop piece
}
