// board_state.cpp

#include "board_state.hpp"



board_state::board_state()
{
  current_player = 1;
  capture_flag = false;
}



bool board_state::can_capture()
{
  for (int row = 0; row < GRID_SIZE; row++)
    for (int col = 0; col < GRID_SIZE; col++)
      if (can_capture(row, col))
        return true;
  return false;
}



bool board_state::can_capture(int row, int col)
{
  piece p; // piece to move

  p = get_piece(row, col);
  if (p == piece::NONE)
    return false;

  switch (p)
  {
  case piece::RED_KING:

    if (current_player == BLACK) return false;

    // Left backward capture
    if ( (get_piece(row + 1, col - 1) == piece::BLACK_MAN) || (get_piece(row + 1, col - 1) == piece::BLACK_KING) )
      if ( (row + 2 < GRID_SIZE) && (col - 2 >= 0) )
        if (get_piece(row + 2, col - 2) == piece::NONE)
          return true;
    // Right backward capture
    if ( (get_piece(row + 1, col + 1) == piece::BLACK_MAN) || (get_piece(row + 1, col + 1) == piece::BLACK_KING) )
      if ( (row + 2 < GRID_SIZE) && (col + 2 < GRID_SIZE) )
        if (get_piece(row + 2, col + 2) == piece::NONE)
          return true;

    // Carry through to next case

  case piece::RED_MAN:

    if (current_player == BLACK) return false;

    // Left forward capture
    if ( (get_piece(row - 1, col - 1) == piece::BLACK_MAN) || (get_piece(row - 1, col - 1) == piece::BLACK_KING) )
      if ( (row - 2 >= 0) && (col - 2 >= 0) )
        if (get_piece(row - 2, col - 2) == piece::NONE)
          return true;
    // Right forward capture
    if ( (get_piece(row - 1, col + 1) == piece::BLACK_MAN) || (get_piece(row - 1, col + 1) == piece::BLACK_KING) )
      if ( (row - 2 >= 0) && (col + 2 < GRID_SIZE) )
        if (get_piece(row - 2, col + 2) == piece::NONE)
          return true;

    break;

  case piece::BLACK_KING:

    if (current_player == RED) return false;

    // Left backward capture
    if ( (get_piece(row - 1, col + 1) == piece::RED_MAN) || (get_piece(row - 1, col + 1) == piece::RED_KING) )
      if ( (row - 2 >= 0) && (col + 2 < GRID_SIZE) )
        if (get_piece(row - 2, col + 2) == piece::NONE)
          return true;
    // Right backward capture
    if ( (get_piece(row - 1, col - 1) == piece::RED_MAN) || (get_piece(row - 1, col - 1) == piece::RED_KING) )
      if ( (row - 2 >= 0) && (col - 2 >= 0) )
        if (get_piece(row - 2, col - 2) == piece::NONE)
          return true;

    // Carry through to next case

  case piece::BLACK_MAN:

    if (current_player == RED) return false;

    // Left forward capture
    if ( (get_piece(row + 1, col + 1) == piece::RED_MAN) || (get_piece(row + 1, col + 1) == piece::RED_KING) )
      if ( (row + 2 < GRID_SIZE) && (col + 2 < GRID_SIZE) )
        if (get_piece(row + 2, col + 2) == piece::NONE)
          return true;
    // Right forward capture
    if ( (get_piece(row + 1, col - 1) == piece::RED_MAN) || (get_piece(row + 1, col - 1) == piece::RED_KING) )
      if ( (row + 2 < GRID_SIZE) && (col - 2 >= 0) )
        if (get_piece(row + 2, col - 2) == piece::NONE)
          return true;

    break;

  default:
    break;
  }

  return false;
}



std::vector<move_t> board_state::get_all_moves()
{
  std::vector<move_t> vec;
  for (int r1 = 0; r1 < GRID_SIZE; r1++)
    for (int c1 = 0; c1 < GRID_SIZE; c1++)
      for (int r2 = r1 - 2; r2 <= r1 + 2; r2++)
        for (int c2 = c1 - 2; c2 <= c1 + 2; c2++)
          if (is_valid_move(r1, c1, r2, c2))
            vec.push_back(std::make_pair(std::make_pair(r1, c1), std::make_pair(r2, c2)));
  return vec;
}



int board_state::get_current_player()
{
  return current_player;
}



board_state::piece board_state::get_piece(int row, int col)
{
  if ( (row < 0) || (row >= GRID_SIZE) ||
       (col < 0) || (col >= GRID_SIZE) )
    return piece::NONE;
  return board[row][col];
}



bool board_state::is_valid_move(int r1, int c1, int r2, int c2)
{
  // Make sure coordinates are valid
  if ( (r1 < 0) || (r1 >= GRID_SIZE) ||
       (c1 < 0) || (c1 >= GRID_SIZE) ||
       (r2 < 0) || (r2 >= GRID_SIZE) ||
       (c2 < 0) || (c2 >= GRID_SIZE) )
    return false;

  // If a piece is already being moved (in the middle of a sequence of jumps)
  if ( (current_row != -1) && (current_col != -1) )
    if ( (r1 != current_row) || (c1 != current_col) )
      return false;

  // Get the pieces at (r1, c1) and (r2, c2)
  piece p1 = get_piece(r1, c1);
  piece p2 = get_piece(r2, c2);

  // Get piece between (r1, c1) and (r2, c2) (in case it is a capture move)
  piece p3 = get_piece((r1 + r2)/2, (c1 + c2)/2);

  // If there is no piece (r1, c1), or if there is another piece at (r2, c2), this is not a valid move.
  if ( (p1 == piece::NONE) || (p2 != piece::NONE) ) 
    return false;

  switch (p1)
  {
  case piece::RED_MAN:

    if (current_player != RED)
      return false;

    // Red forward move
    if ( (r2 - r1 == -1) && (std::abs(c2 - c1) == 1) )
      return !capture_flag;

    // Red forward capture
    if ( (r2 - r1 == -2) && (std::abs(c2 - c1) == 2) )
      if ( (p3 == piece::BLACK_MAN) || (p3 == piece::BLACK_KING) )
        return true;

    break;

  case piece::RED_KING:

    if (current_player != RED)
      return false;

    // Red move
    if ( (std::abs(r2 - r1) == 1) && (std::abs(c2 - c1) == 1) )
      return !capture_flag;

    // Red capture
    if ( (std::abs(r2 - r1) == 2) && (std::abs(c2 - c1) == 2) )
      if ( (p3 == piece::BLACK_MAN) || (p3 == piece::BLACK_KING) )
        return true;

    break;

  case piece::BLACK_MAN:

    if (current_player != BLACK)
      return false;

    // Black forward move
    if ( (r2 - r1 == 1) && (std::abs(c2 - c1) == 1) )
      return !capture_flag;

    // Black forward capture
    if ( (r2 - r1 == 2) && (std::abs(c2 - c1) == 2) )
      if ( (p3 == piece::RED_MAN) || (p3 == piece::RED_KING) )
        return true;

    break;

  case piece::BLACK_KING:

    if (current_player != BLACK)
      return false;

    // Black move
    if ( (std::abs(r2 - r1) == 1) && (std::abs(c2 - c1) == 1) )
      return !capture_flag;

    // Black capture
    if ( (std::abs(r2 - r1) == 2) && (std::abs(c2 - c1) == 2) )
      if ( (p3 == piece::RED_MAN) || (p3 == piece::RED_KING) )
        return true;

    break;

  default:
    return false;
    break;
  }

  return false;
}



void board_state::move(int r1, int c1, int r2, int c2)
{
  if (!is_valid_move(r1, c1, r2, c2))
    return;
  
  // Put piece in new location
  set_piece(r2, c2, get_piece(r1, c1));

  // Remove piece from old location
  set_piece(r1, c1, piece::NONE);

  // If move was a jump
  if (std::abs(r2 - r1) == 2)
    set_piece((r1 + r2) / 2, (c1 + c2) / 2, piece::NONE);

  current_row = r2;
  current_col = c2;

  // If player was able to capture, they may be required to capture more pieces
  if (capture_flag)
  {
    capture_flag = can_capture(r2, c2);
  }

  // Check for promotion
  if ( ((current_player == RED) && (r2 == 0)) ||
       ((current_player == BLACK) && (r2 == GRID_SIZE - 1)) )
    promote(r2, c2);

  if (!capture_flag)
  {
    // Toggle current player
    current_player = (current_player == RED ? BLACK : RED);
    current_row = current_col = -1;
    capture_flag = can_capture();

    std::vector<move_t> vec = get_all_moves();
  }
}

void board_state::move(move_t m)
{
  move(m.first.first, m.first.second, m.second.first, m.second.second);
}



void board_state::promote(int row, int col)
{
  if (get_piece(row, col) == piece::RED_MAN)
    set_piece(row, col, piece::RED_KING);
  if (get_piece(row, col) == piece::BLACK_MAN)
    set_piece(row, col, piece::BLACK_KING);
}



void board_state::set_piece(int row, int col, board_state::piece p)
{
  if ( (row >= 0) && (row < GRID_SIZE) &&
       (col >= 0) && (col < GRID_SIZE) )
    board[row][col] = p;
}



void board_state::setup()
{
  // Clear board
  for (int row = 0; row < GRID_SIZE; row++)
    for (int col = 0; col < GRID_SIZE; col++)
      board[row][col] = piece::NONE;
      
  // Place black pieces
  for (int row = 0; row < 3; row++)
    for (int col = 0; col < GRID_SIZE; col++)
      board[row][col] = (row + col) % 2 ? piece::BLACK_MAN : piece::NONE;

  // Place red pieces
  for (int row = 5; row < GRID_SIZE; row++)
    for (int col = 0; col < GRID_SIZE; col++)
      board[row][col] = (row + col) % 2 ? piece::RED_MAN : piece::NONE;

  current_player = RED;
  current_row = current_col = -1;
  capture_flag = false;
}

