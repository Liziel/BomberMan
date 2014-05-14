#include "SFML/OpenGL.hpp"
#include "Cube.hpp"

Cube::Cube(int xpos, int ypos, int size)
{
  this->sz = size;
  this->x = xpos;
  this->y = ypos;
  this->z = size;
}

Cube::~Cube()
{
  //
}

void Cube::showCube(bool rotate, float angle)
{
  //Prepare for drawing
  // Clear color and depth buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
  // Apply some transformations for the cube
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0.f, 0.f, -200.f);
      
  glRotatef(angle * 50, 1.f, 0.f, 0.f);
  glRotatef(angle * 30, 0.f, 1.f, 0.f);
  glRotatef(angle * 90, 0.f, 0.f, 1.f);

  //Draw a cube
  glBegin(GL_QUADS);//draw some squares
  glColor3ub(50, 50, 50);
  glVertex3f(-x, -y, -z);
  glVertex3f(-x,  y, -z);
  glVertex3f( x,  y, -z);
  glVertex3f( x, -y, -z);

  glColor3ub(85, 85, 85);
  glVertex3f(-x, -y, z);
  glVertex3f(-x,  y, z);
  glVertex3f( x,  y, z);
  glVertex3f( x, -y, z);
 
  glColor3ub(110, 110, 110);
  glVertex3f(-x, -y, -z);
  glVertex3f(-x,  y, -z);
  glVertex3f(-x,  y,  z);
  glVertex3f(-x, -y,  z);
 
  glColor3ub(145, 145, 145);
  glVertex3f(x, -y, -z);
  glVertex3f(x,  y, -z);
  glVertex3f(x,  y,  z);
  glVertex3f(x, -y,  z);
 
  glColor3ub(180, 180, 180);
  glVertex3f(-x, -y,  z);
  glVertex3f(-x, -y, -z);
  glVertex3f( x, -y, -z);
  glVertex3f( x, -y,  z);
 
  glColor3ub(205, 205, 205);
  glVertex3f(-x, y,  z);
  glVertex3f(-x, y, -z);
  glVertex3f( x, y, -z);
  glVertex3f( x, y,  z);
 
  glEnd();
}
