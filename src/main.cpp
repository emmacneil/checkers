// main.cpp

#include <iostream>

#include "game.hpp"



int main(int argc, char * argv[])
{
  game g;

  if (g.init())
  {
    g.run();
    g.quit();
  }
  else
  {
    std::cout << "Could not initialize game." << std::endl;
  }
  std::cout << "Exiting." << std::endl;

  return 0;
}
