/* board_state.h
 */

#ifndef BOARD_STATE_H
#define BOARD_STATE_H



#include <cmath>
#include <utility>
#include <vector>



typedef std::pair<std::pair<int,int>,std::pair<int,int> > move_t;



class board_state
{
public:
  enum piece {NONE=0, RED_MAN, RED_KING, BLACK_MAN, BLACK_KING};
  static const int RED = 1;
  static const int BLACK = 2;

  /* The number of tiles in each row and column. */
  static const int GRID_SIZE = 8;
  
  /* Creates an empty board. */
  board_state();
  
  /* Returns true if any piece can capture a nearby piece. */
  bool can_capture();

  /* Returns true if the piece at (row, col) can capture a nearby piece. */
  bool can_capture(int row, int col);

  /* Returns a std::vector containing all legal moves. */
  std::vector<move_t> get_all_moves();

  /* Returns whose turn it is. */
  int get_current_player();

  /* Returns the type of piece at location (row, col). */
  piece get_piece(int row, int col);

  /* Returns true if moving a piece from (r1, c1) to (r2, c2) is a valid move. */
  bool is_valid_move(int r1, int c1, int r2, int c2);

  /* Moves a piece from (r1, c1) to (r2, c2), if it is a valid move. */
  void move(int r1, int c1, int r2, int c2);
  void move(move_t m);

  /* Turns a man into a king. */
  void promote(int row, int col);

  /* Sets the piece at (row, col) to the type p. */  
  void set_piece(int row, int col, piece p);

  /* Sets up the board for a new game. */
  void setup();
  
private:
  /* 2-D array representing the game board. [0][0] is the top-left corner. */
  piece board[GRID_SIZE][GRID_SIZE];
  
  /* Indicates whose turn it is. */
  int current_player;

  /* True if the current player can make a capture. */
  bool capture_flag;

  /* Coordinates of piece currently being moved -- relevant when a single piece must make a sequence of captures. */
  int current_row, current_col;
};

#endif
