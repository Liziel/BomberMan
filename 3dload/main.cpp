#include "Cube.hpp"
#include "Model.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/OpenGL.hpp"
#include <iostream>

void setGL()
{
  //prepare OpenGL surface for HSR
  glClearDepth(1.f);
  glClearColor(1.0f, 1.0f, 1.0f, 0.f);
  glEnable(GL_BLEND);
  glDepthMask(GL_TRUE);
 
  //// Setup a perspective projection & Camera position
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(90.f, 1.f, 1.f, 300.0f);//fov, aspect, zNear, zFar
}
 
int main()
{
  sf::RenderWindow App(sf::VideoMode(800, 600, 32), "SFML OpenGL");
  sf::Clock Clock;
  Model test("ss.obj");
  bool rotate=true;
  float angle;

  setGL();
  test.load();
  while (App.isOpen())
    {
      sf::Event Event;
      while (App.pollEvent(Event))
        {
	  if (Event.type == sf::Event::Closed)
	    App.close();
	  if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape))
	    App.close();
	  if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::A)){
	    rotate=!rotate;
	  }
	}
      if (rotate)
	angle=Clock.getElapsedTime().asSeconds();
      test.show(angle);
      App.display();
    }
 
  return EXIT_SUCCESS;
}
