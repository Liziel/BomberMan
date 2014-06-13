#ifndef __GROUNDDISPLAY_H__
# define __GROUNDDISPLAY_H__

# include "Component.hh"

# include "cubeVertex.hh"
# define __GROUNDTEXTURE "./textures/ground/lava.tga"
# define __INDESTEXTURE "./textures/diamond/Diamond.tga"
# define __BOOKSHELFTEXTURE "./textures/bookshelf/bookshelf.tga"

namespace Component{
  class groundDisplay : public Component::abstract{
  private:
    object3d::cubeVertex	*cube;
    Engine::Graphic*		engine;

  public:
    groundDisplay(Entity::GameObject*, Engine::Graphic*);
    ~groundDisplay();

  public:
    std::string serialization() { return (""); }
    void	setBySerial(const Tokenizer&) {}
  };

  class indestructibleDisplay : public Component::abstract {
  private:
    object3d::cubeVertex	*cube;
    Engine::Graphic*		engine;

  public:
    indestructibleDisplay(Entity::GameObject*, Engine::Graphic*);
    ~indestructibleDisplay();

  public:
    std::string serialization() { return (""); }
    void	setBySerial(const Tokenizer&) {}
  };

  class bookshelfDisplay : public Component::abstract {
  private:
    object3d::cubeVertex	*cube;
    Engine::Graphic*		engine;

  public:
    bookshelfDisplay(Entity::GameObject*, Engine::Graphic*);
    ~bookshelfDisplay();

  public:
    std::string serialization() { return (""); }
    void	setBySerial(const Tokenizer&) {}
  };

  class playerDisplay : public Component::abstract {
  private:
    object3d::cubeVertex	*cube;
    Engine::Graphic*		engine;

  private:
    double x,y;
  public:
    playerDisplay(Entity::GameObject*, Engine::Graphic*);
    ~playerDisplay();

  public:
    std::string serialization() { return (""); }
    void	setBySerial(const Tokenizer&) {}
  };
};

#endif
