#ifndef CUBE_H
#define CUBE_H

#include <SFML/Graphics.hpp>
#include "SFML/OpenGL.hpp"

class Cube
{
public:
  Cube(int xpos = 10, int ypos = 10, int size = 10);
  ~Cube();
  void showCube(bool, float);
private:
  int sz;
  float x;
  float y;
  float z;
};

#endif //CUBE_H
